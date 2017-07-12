//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "AudioFile.h"
class Logger;

#include "../../Engine/Engine.h"
#include "../../Engine/EnginePart.h"
#include "./Sound.h"


#define MAX_SOUNDS_PLAYING 32

extern int G_mute;//GLOBAL MUTE

bool HARDWARE_play_sound(string &name, int vol, int freq, int loop);
void HARDWARE_stop_music();
void HARDWARE_play_music(string &name, int vol);
void HARDWARE_stop_sound(string &name);
void HARDWARE_set_music_volume(int vol);
bool HARDWARE_play_sound_if_not_playing(string &name, int vol, int freq, int loop);
void HARDWARE_unload_wavs_done_playing();
void HARDWARE_sound_init();

class AudioManager : EnginePart
{
public:
	static Logger log;

	static ArrayList<AudioFile*> globalAudioFileList;

	static bool loadedBuiltIn;
	ArrayList<Sound*> playingAudioList;

	

#ifdef USE_SOLOUD
	static SoLoud::Soloud *soLoud;// = nullptr;
#endif


	AudioManager();
	AudioManager(Engine* g);
	void init();
	static void initAudioLibrary();
	static void cleanup();

	static void globalUpdate();

	//Sound* loadSoundFileByName(const string& name);
	
	
	void update();

	Sound* getSoundByName(const string& musicName);

	void playMusic(Sound* s, float vol, float pitch, bool loop);
	Sound* playMusic(const string& musicName, float volume, float pitch, bool loop);

	Sound* playSound(const string& soundName);
	Sound* playSound(const string& soundName, float volume, float pitch, int times);
	Sound* playSound(const string& soundName, float volume, float pitch);
	void playSound(Sound* s, float vol, float pitch, int times);

	void playMusic(Sound* m);
	void playSoundLoop(Sound* m);

	Sound* playMusic(const string& musicName);
	Sound* playSoundLoop(const string& musicName);



	bool isSoundPlaying(Sound* m);

	bool isSoundPlaying(const string& musicName);

	void stopMusic(Sound* m);
	void stopSound(Sound* m);

	void stopMusic(const string& musicName);
	void stopSound(const string& musicName);

	void fadeOutSound(const string& musicName, int ticks);

	void fadeOutSound(Sound* m, int ticks);



	bool isAnyMusicPlaying();
	bool isAnyLoopingSoundPlaying();

	void pauseAnyPlayingLoopingSounds();
	void playAnyPausedLoopingSounds();
	void setAllPlayingSoundsVolume(float v);
	void setAllPlayingLoopingSoundsVolume(float v);


	void stopAllMusic();
	void stopAllLoopingSounds();

	void fadeOutAllMusic(int ticks);
	void fadeOutAllLoopingSounds(int ticks);
	void fadeOutAllSounds(int ticks);

	void setAllLoopingSoundsThatAreNotFadingOutToNotLoop();

	void setAllLoopingSoundsToNotLoop();

	void pauseAllLoopingSounds();

	void unpauseAllLoopingSounds();
	void pauseAllSounds();

	void unpauseAllSounds();

	static AudioFile* getAudioFileByName(string name);
	static AudioFile* getAudioFileByIDCreateIfNotExist(int id);
	Sound* getSoundByIDCreateIfNotExist(int id);


};
