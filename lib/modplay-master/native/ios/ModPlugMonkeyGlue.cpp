#include <AudioUnit/AudioUnit.h>
#include "modplug.h"

#define kOutputBus 0
#define kInputBus  1 
#define SAMPLE_RATE 11025

///////////////////////////////////////////////////////////////////////////////
// Software Mixer Interrupt
///////////////////////////////////////////////////////////////////////////////

static ModPlugFile* currentFile;
static bool sessionInitialized = false;

void checkStatus(OSStatus status) {
	if(status == 0)
		//printf("success");
        return;
	else if(status == errSecNotAvailable)
		NSLog(@"no trust results available");
	else if(status == errSecItemNotFound)
		NSLog(@"the item cannot be found");
	else if(status == errSecParam)
		NSLog(@"parameter error");
	else if(status == errSecAllocate)
		NSLog(@"memory allocation error");
	else if(status == errSecInteractionNotAllowed)
		NSLog(@"user interaction not allowd");
	else if(status == errSecUnimplemented)
		NSLog(@"not implemented");
	else if(status == errSecDuplicateItem)
		NSLog(@"item already exists");
	else if(status == errSecDecode)
		NSLog(@"unable to decode data");
	else
		NSLog(@"unknown: %ld", status);
}

static OSStatus playbackCallback(void *inRefCon, 
								 AudioUnitRenderActionFlags* ioActionFlags, 
								 const AudioTimeStamp*       inTimeStamp, 
								 UInt32                      inBusNumber, 
								 UInt32                      inNumberFrames, 
								 AudioBufferList             *ioDataList) 
{
	if (ioDataList->mNumberBuffers != 1) {
		NSLog(@"oh dear\n");
	}

	AudioBuffer *ioData = &ioDataList->mBuffers[0];

    void *buffer = (short int *)ioData->mData;
    int size = inNumberFrames * sizeof(short) * 2;
    
    memset(buffer, 0, size);
    //if (Active() && m_IsPushingAudio) {
    if (currentFile) {
        int read = ModPlug_Read(currentFile, buffer, size);
        //LOGV("audio %d %d\n", ((short *)buffer)[0], ((short *)buffer)[(size / sizeof(float)) + 1]);
        if (read == 0) {
            ModPlug_Seek(currentFile, 0);
        }
    }

    return noErr;
}

void interruptionListenerCallback (void *inUserData,UInt32 interruptionState ) {
	if (interruptionState == kAudioSessionBeginInterruption) {
		//TODO: phone call interuption, pause game?
	} else if (interruptionState == kAudioSessionEndInterruption) {
		// if the interruption was removed, and the app had been playing, resume playback
		UInt32 sessionCategory = kAudioSessionCategory_MediaPlayback;
		AudioSessionSetProperty(kAudioSessionProperty_AudioCategory,
                                sizeof (sessionCategory),
                                &sessionCategory
                                );
		AudioSessionSetActive(true);
	}
}

    
class ModPlugMonkeyGlue : public Object {

	// Handle to audio component instance (for mixer callback)
	AudioComponentInstance m_audio_unit;
	// Volume
	float   m_volume;
    bool    debug;
        
public:

    void Init(int rate);
    void Play(NativeModFile *file);
    void Stop();
    void Pause();
    void Unpause();
    void SetVolume(float volume);
    void SetLoopCount(int loopCount);
    void SetCurrentPattern(int pattern);
    void ChangePattern(int pattern);
    void SetDebug(bool debug) { this->debug = debug; }
};

void ModPlugMonkeyGlue::Init(int rate) {
    //NSLog(@"Init ModPlayer");
    m_volume = 1;
    debug = false;
    OSStatus status;
    
    if (!sessionInitialized) {
	    AudioSessionInitialize (NULL, NULL, interruptionListenerCallback, NULL);
    	status = AudioSessionSetActive (true);
    	checkStatus(status);
    	UInt32 sessionCategory = kAudioSessionCategory_AmbientSound;
    	AudioSessionSetProperty (kAudioSessionProperty_AudioCategory, sizeof (sessionCategory), &sessionCategory);
        sessionInitialized = true;
    }

    // Describe audio component
    AudioComponentDescription desc;
    memset(&desc, 0, sizeof(AudioComponentDescription));
    desc.componentType         = kAudioUnitType_Output;
    desc.componentSubType      = kAudioUnitSubType_RemoteIO;
    desc.componentFlags        = 0;
    desc.componentFlagsMask    = 0;
    desc.componentManufacturer = kAudioUnitManufacturer_Apple;
    
    // Get component
    AudioComponent inputComponent = AudioComponentFindNext(NULL, &desc);
    
    // Get audio units
    status = AudioComponentInstanceNew(inputComponent, &m_audio_unit);
    if (status != noErr) {
        NSLog(@"Failed to get audio component instance: %d", (int)status);
    }
    
    // Enable IO for playback
    UInt32 flag = 1;
    status = AudioUnitSetProperty(m_audio_unit, 
    					  kAudioOutputUnitProperty_EnableIO, 
    					  kAudioUnitScope_Output, 
    					  kOutputBus,
    					  &flag, 
    					  sizeof(flag));
    if (status != noErr) {
        NSLog(@"Failed to enable audio i/o for playback: %d", (int)status);
    }
    
    if (rate == 0) {
        rate = 44100;
    }
    
    // Describe format
    AudioStreamBasicDescription audioFormat;
    memset(&audioFormat, 0, sizeof(AudioStreamBasicDescription));
    audioFormat.mSampleRate       = rate;
    audioFormat.mFormatID	      = kAudioFormatLinearPCM;
    audioFormat.mFormatFlags      = kAudioFormatFlagsCanonical;
    audioFormat.mFramesPerPacket  = 1;		
    audioFormat.mChannelsPerFrame = 2;
    audioFormat.mBitsPerChannel   = 16;
    audioFormat.mBytesPerPacket   = 4;
    audioFormat.mBytesPerFrame    = 4;		
    
    // Apply format
    status = AudioUnitSetProperty(m_audio_unit, 
    					  kAudioUnitProperty_StreamFormat, 
    					  kAudioUnitScope_Input, 
    					  kOutputBus, 
    					  &audioFormat, 
    					  sizeof(audioFormat));
    if (status != noErr) {
        NSLog(@"Failed to set format descriptor: %d", (int)status);
    }
    
    // Set output callback
    AURenderCallbackStruct callbackStruct;
    memset(&callbackStruct, 0, sizeof(AURenderCallbackStruct));
    callbackStruct.inputProc       = playbackCallback;
    callbackStruct.inputProcRefCon = &m_volume;
    status = AudioUnitSetProperty(m_audio_unit, 
    					  kAudioUnitProperty_SetRenderCallback, 
    					  kAudioUnitScope_Global, 
    					  kOutputBus,
    					  &callbackStruct, 
    					  sizeof(callbackStruct));
    if (status != noErr) {
        NSLog(@"Failed to set output callback: %d", (int)status);
    }
    
	Float32 aBufferLength; // In seconds
	UInt32 size = sizeof(aBufferLength);

    status = AudioSessionGetProperty(kAudioSessionProperty_CurrentHardwareIOBufferDuration, &size, &aBufferLength);
	checkStatus(status);
  
    // Initialize
    status = AudioUnitInitialize(m_audio_unit);
    if (status != noErr) {
        NSLog(@"Failed to initialise audio unit: %d", (int)status);
    }
        
}

void ModPlugMonkeyGlue::Play(NativeModFile *file) {
    Pause();
    currentFile = file->GetData();
    // this gives the same behaviour as the android version. whether it is the right thing or not is a matter for discussion...
    ModPlug_Seek(currentFile,0);
    AudioOutputUnitStart(m_audio_unit);
}

void ModPlugMonkeyGlue::Stop() {
    if (currentFile) {
        ModPlug_Unload(currentFile);
        currentFile = NULL;
        
        // TODO: Cleanup Audio resources
		AudioSessionSetActive(false);
        AudioOutputUnitStop(m_audio_unit);
        AudioUnitUninitialize(m_audio_unit);
    }
}

void ModPlugMonkeyGlue::Pause() {
    AudioOutputUnitStop(m_audio_unit);
}

void ModPlugMonkeyGlue::Unpause() {
    AudioOutputUnitStart(m_audio_unit);
}

void ModPlugMonkeyGlue::SetVolume(float volume) {
    if (volume < 0) volume = 0.0f;
    if (volume > 1) volume = 1.0f;
    m_volume = volume;
    AudioUnitSetParameter(m_audio_unit, kMultiChannelMixerParam_Volume, kAudioUnitScope_Output, 0, m_volume, 0);
}

void ModPlugMonkeyGlue::SetLoopCount(int loopCount) {
    ModPlug_Settings settings;
    ModPlug_GetSettings(&settings);
    settings.mLoopCount = loopCount;
    ModPlug_SetSettings(&settings);
}

/*void ModPlugMonkeyGlue::SetCurrentPattern(int pattern) {
    ModPlug_SetCurrentPattern(pattern);
}

void ModPlugMonkeyGlue::ChangePattern(int pattern) {
    ModPlug_ChangePattern(newpattern);
}
*/