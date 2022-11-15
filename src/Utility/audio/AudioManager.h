//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
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

	static sp<vector<sp<AudioFile>>>globalAudioFileList;

	static bool loadedBuiltIn;
	sp<vector<sp<Sound>>>playingAudioList;

	

#ifdef USE_SOLOUD
	static SoLoud::Soloud *soLoud;// = nullptr;
#endif


	AudioManager();
	AudioManager(sp<Engine> g);
	
	static void initAudioLibrary();
	static void cleanup();

	static void globalUpdate();

	//sp<Sound> loadSoundFileByName(const string& name);
	
	
	void update();

	sp<Sound> getSoundByName(const string& musicName);

	void playMusic(sp<Sound> s, float vol, float pitch, bool loop);
	sp<Sound> playMusic(const string& musicName, float volume, float pitch, bool loop);

	sp<Sound> playSound(const string& soundName);
	sp<Sound> playSound(const string& soundName, float volume, float pitch, int times);
	sp<Sound> playSound(const string& soundName, float volume, float pitch);
	void playSound(sp<Sound> s, float vol, float pitch, int times);

	void playMusic(sp<Sound> m);
	void playSoundLoop(sp<Sound> m);

	sp<Sound> playMusic(const string& musicName);
	sp<Sound> playSoundLoop(const string& musicName);



	bool isSoundPlaying(sp<Sound> m);

	bool isSoundPlaying(const string& musicName);

	void stopMusic(sp<Sound> m);
	void stopSound(sp<Sound> m);

	void stopMusic(const string& musicName);
	void stopSound(const string& musicName);

	void fadeOutSound(const string& musicName, int ticks);

	void fadeOutSound(sp<Sound> m, int ticks);



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

	static sp<AudioFile> getAudioFileByName(string name);
	static sp<AudioFile> getAudioFileByIDCreateIfNotExist(int id);
	sp<Sound> getSoundByIDCreateIfNotExist(int id);


};
