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

	static ArrayList<shared_ptr<AudioFile>> globalAudioFileList;

	static bool loadedBuiltIn;
	ArrayList<shared_ptr<Sound>> playingAudioList;

	

#ifdef USE_SOLOUD
	static SoLoud::Soloud *soLoud;// = nullptr;
#endif


	AudioManager();
	AudioManager(shared_ptr<Engine> g);
	
	static void initAudioLibrary();
	static void cleanup();

	static void globalUpdate();

	//shared_ptr<Sound> loadSoundFileByName(const string& name);
	
	
	void update();

	shared_ptr<Sound> getSoundByName(const string& musicName);

	void playMusic(shared_ptr<Sound> s, float vol, float pitch, bool loop);
	shared_ptr<Sound> playMusic(const string& musicName, float volume, float pitch, bool loop);

	shared_ptr<Sound> playSound(const string& soundName);
	shared_ptr<Sound> playSound(const string& soundName, float volume, float pitch, int times);
	shared_ptr<Sound> playSound(const string& soundName, float volume, float pitch);
	void playSound(shared_ptr<Sound> s, float vol, float pitch, int times);

	void playMusic(shared_ptr<Sound> m);
	void playSoundLoop(shared_ptr<Sound> m);

	shared_ptr<Sound> playMusic(const string& musicName);
	shared_ptr<Sound> playSoundLoop(const string& musicName);



	bool isSoundPlaying(shared_ptr<Sound> m);

	bool isSoundPlaying(const string& musicName);

	void stopMusic(shared_ptr<Sound> m);
	void stopSound(shared_ptr<Sound> m);

	void stopMusic(const string& musicName);
	void stopSound(const string& musicName);

	void fadeOutSound(const string& musicName, int ticks);

	void fadeOutSound(shared_ptr<Sound> m, int ticks);



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

	static shared_ptr<AudioFile> getAudioFileByName(string name);
	static shared_ptr<AudioFile> getAudioFileByIDCreateIfNotExist(int id);
	shared_ptr<Sound> getSoundByIDCreateIfNotExist(int id);


};
