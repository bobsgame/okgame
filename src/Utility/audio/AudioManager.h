//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../../Engine/Engine.h"
#include "../../Engine/EnginePart.h"
#include "./Sound.h"
#include "./Music.h"
class Logger;


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

	static ArrayList<Music*>* musicList;
	static ArrayList<Sound*>* soundList;
	static HashMap<string, Sound*>* soundByNameHashMap;

	//not global, used to do stop all music for only this engine etc
	ArrayList<Music*>* playingMusicList = new ArrayList<Music*>();

#ifdef USE_SOLOUD
	static SoLoud::Soloud *soLoud;// = nullptr;
#endif



	AudioManager();
	AudioManager(Engine* g);
	void init();
	static void initAudioLibrary();
	static void cleanup();

	//Sound* loadSoundFileByName(const string& name);
	
	
	void update();

	static Music* getMusicByName(const string& musicName);
	void setAllPlayingMusicVolume(float v);
	bool isAnyMusicPlaying();
	void pauseAnyPlayingMusic();
	void playAnyPausedMusic();
	bool isMusicPlaying(Music* m);
	bool isMusicPlaying(const string& musicName);
	void playMusic(Music* m);
	Music* playMusic(const string& musicName);
	void playMusic(Music* m, float volume, float pitch, bool loop);
	Music* playMusic(const string& musicName, float volume, float pitch, bool loop);
	void stopMusic(Music* m);
	void stopMusic(const string& musicName);
	void fadeOutMusic(const string& musicName, int ticks);
	void fadeOutMusic(Music* m, int ticks);
	void stopAllMusic();
	void fadeOutAllMusic(int ticks);
	void setAllLoopingMusicThatIsNotFadingOutToNotLoop();
	void pauseAllMusic();
	void unpauseAllMusic();



	static Sound* getSoundByName(const string& soundName);
	void playSound(const string& soundName, float volume, float pitch); //, int times)
	void playSound(const string& soundName, float volume, float pitch, int times);
	void playSound(const string& soundName);
	void playSound(Sound* s);
	void playSound(Sound* s, float vol);
	void playSound(Sound* s, float vol, float pitch); //, int times)
	void playSound(Sound* s, float vol, float pitch, int times);
	Music* getMusicByIDCreateIfNotExist(int id);
	Sound* getSoundByIDCreateIfNotExist(int id);
};
