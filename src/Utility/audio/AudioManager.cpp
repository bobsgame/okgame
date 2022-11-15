
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





#include "SDL_mixer.h"

Logger AudioManager::log = Logger("AudioManager");



#ifdef USE_SOLOUD
SoLoud::Soloud *AudioManager::soLoud = nullptr;
#endif

//global and static, shared between all audiomanagers
vector<sp<AudioFile>> AudioManager::globalAudioFileList;
bool AudioManager::loadedBuiltIn = false;

//=========================================================================================================================
AudioManager::AudioManager()
{ //=========================================================================================================================


}

//=========================================================================================================================
AudioManager::AudioManager(sp<Engine> g)
{ //=========================================================================================================================

	this->e = g;

}


#include <fstream>
#include <iostream>
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/Delegate.h"
#include "Poco/Zip/Decompress.h"
#include "Poco/Process.h"
#include "Poco/DirectoryIterator.h"
using Poco::DirectoryIterator;
using Poco::File;
using Poco::Process;
using Poco::Path;


//=========================================================================================================================
void AudioManager::initAudioLibrary()
{//=========================================================================================================================

	Uint64 start=0, now=0;// , totalStart, totalNow;
	start = SDL_GetPerformanceCounter();
	//totalStart = SDL_GetPerformanceCounter();
	

#ifdef USE_SDL_MIXER

	log.debug("Init SDL Mixer");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		log.error("Couldn't set up audio: " + string(SDL_GetError()));
	}
	Mix_AllocateChannels(32);

#endif

	GLUtils::checkSDLError("AudioManager::initAudioLibrary()");

#ifdef USE_SOLOUD
	soLoud = ms<SoLoud>::Soloud();
	soLoud->init();
#endif


	now = SDL_GetPerformanceCounter();
	log.debug("Init SDL Mixer took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();



	if (loadedBuiltIn == false)
	{
		loadedBuiltIn = true;


		Uint64 start = 0, now = 0, totalStart = 0, totalNow = 0;
		start = SDL_GetPerformanceCounter();
		totalStart = SDL_GetPerformanceCounter();

		log.debug("Loading built in sounds");
		{
			log.debug("get path");
			string spriteFolderString = Main::getPath() + "data/sounds/";
			//log.debug("create path");
			//Path spriteFolderPath(spriteFolderString);
			log.debug("create file");
			File spriteFolderPathDir(spriteFolderString);
			log.debug("createDirectories");
			if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
			vector<string> files;
			log.debug("list");
			spriteFolderPathDir.list(files);
			vector<string>::iterator it = files.begin();
			for (; it != files.end(); ++it)
			{
				//cout << *it << endl;
				string name = *it;
				if (name.find(".ogg") != string::npos)
				{
					ms<AudioFile>("data/sounds/" + name);
				}
			}
		}

		now = SDL_GetPerformanceCounter();
		log.debug("Loading sounds took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
		start = SDL_GetPerformanceCounter();


		log.debug("Loading built in music");
		{
			string spriteFolderString = Main::getPath() + "data/music/";
			Path spriteFolderPath(spriteFolderString);
			File spriteFolderPathDir(spriteFolderPath);
			if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
			vector<string> files;
			spriteFolderPathDir.list(files);
			vector<string>::iterator it = files.begin();
			for (; it != files.end(); ++it)
			{
				//cout << *it << endl;
				string name = *it;
				if (name.find(".ogg") != string::npos)
				{
					ms<AudioFile>("data/music/" + name);
				}
			}
		}

		now = SDL_GetPerformanceCounter();
		log.debug("Loading music took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
		start = SDL_GetPerformanceCounter();

		totalNow = SDL_GetPerformanceCounter();
		log.debug("initAudioLibrary took " + to_string((double)((totalNow - totalStart) * 1000) / SDL_GetPerformanceFrequency()) + "ms");


		//GLUtils::e();
	}

	//	//load sounds/index.txt
	//	//for each line, load ogg file
	//	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/sounds/index.txt");
	//	if (stringList->size() > 0)
	//	{
	//		for (int i = 0; i < stringList->size(); i++)
	//		{
	//			string s = stringList->at(i);
	//
	//			if (s.length() > 0)
	//			{
	//				//sp<Sound>sound =
	//				ms<Sound>(this, "data/sounds/" + s);
	//				//sound.byteData = dataFile.readBytes();
	//			}
	//		}
	//	}


}





//=========================================================================================================================
void AudioManager::cleanup()
{//=========================================================================================================================

	log.info("Cleaning up audio");
#ifdef USE_SDL_MIXER
 //	if(Mix_PlayingMusic())
 //	{
 //		Mix_FadeOutMusic(1000);
 //		Mix_FreeMusic(background_MUS);
 //	}
	int numtimesopened, frequency, channels;
	Uint16 format;
	numtimesopened=Mix_QuerySpec(&frequency, &format, &channels);
	for(int i=0;i<numtimesopened;i++)Mix_CloseAudio();
#endif
#ifdef USE_SOLOUD
	soLoud->deinit();
#endif

}

//sp<Sound> AudioManager::loadSoundFileByName(const string& fileName)
//{ //=========================================================================================================================
//
//	sp<Sound> s = nullptr;
//
//	for(int i=0;i<soundList.size();i++)if(soundList.at(i)->getName() == fileName)s = soundList.at(i);
//
//	if (s == nullptr)
//	{
//		HashMap<string, sp<Sound>>::const_iterator got = soundByNameHashMap->find(fileName);
//		if (got != soundByNameHashMap->end())
//			s = soundByNameHashMap->at(fileName);
//	}
//
//	if (s == nullptr)
//	{
//	    s = ms<Sound>(fileName);
//	    soundByNameHashMap->insert_or_assign(s->getName(),s);
//	}
//
//	return s;
//}



void AudioManager::globalUpdate()
{
	
	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		globalAudioFileList.at(i)->update();
	}
}


void AudioManager::update()
{ //=========================================================================================================================



	for (int i = 0; i < playingAudioList.size(); i++)
	{
		playingAudioList.at(i)->update();
	}
}

sp<Sound> AudioManager::getSoundByName(const string& musicName)
{ //=========================================================================================================================
	if (musicName == "" || musicName.length() == 0)
	{
		return nullptr;
	}



	string clippedName = musicName;
	if (clippedName.find("_v") != -1)
	{
		clippedName.substr(0, clippedName.find("_v"));
	}	
	
	if (clippedName.find(".") != -1)
	{
		clippedName.substr(0, clippedName.find("."));
	}

	for (int i = 0; i < playingAudioList.size(); i++)
	{
		string name = playingAudioList.at(i)->getName();

		if (OKString::startsWith(name, clippedName))
		{
			
			return playingAudioList.at(i);
		}
	}


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		string name = globalAudioFileList.at(i)->getName();

		if (OKString::startsWith(name, clippedName))
		{
			sp<Sound> s = ms<Sound>(getEngine(), globalAudioFileList.at(i));
			playingAudioList.push_back(s);
			return s;
		}
	}






	return nullptr;
}


//=========================================================================================================================
void AudioManager::playMusic(sp<Sound> s, float vol, float pitch, bool loop)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.push_back(s);
		s->play(pitch, vol, loop);
	}
}

sp<Sound> AudioManager::playMusic(const string& musicName, float volume, float pitch, bool loop)
{ //=========================================================================================================================
	sp<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->play(pitch, volume, loop);
		if (playingAudioList.contains(m) == false)playingAudioList.push_back(m);
		return m;
	}
	return nullptr;
}

//=========================================================================================================================
sp<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch)
{ //=========================================================================================================================

	return playSound(soundName,volume,pitch,1);

}

//=========================================================================================================================
sp<Sound> AudioManager::playSound(const string& soundName)
{ //=========================================================================================================================
	return playSound(soundName, 1, 1, 1);
}

//=========================================================================================================================
sp<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch, int times)
{ //=========================================================================================================================

	sp<Sound> s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play(pitch, volume, times);
		return s;
	}
	return nullptr;

	//Exception e = ms<Exception>();e.printStackTrace();
}


//=========================================================================================================================
void AudioManager::playSound(sp<Sound> s, float vol, float pitch, int times)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.push_back(s);
		s->play(pitch, vol, times);
	}
}

void AudioManager::playMusic(sp<Sound> m)
{ //=========================================================================================================================
	playSoundLoop(m);
}
void AudioManager::playSoundLoop(sp<Sound> m)
{ //=========================================================================================================================
	m->playLoop();
	if (playingAudioList.contains(m) == false)playingAudioList.push_back(m);
}

sp<Sound> AudioManager::playMusic(const string& musicName)
{ //=========================================================================================================================
	return playSoundLoop(musicName);
}
sp<Sound> AudioManager::playSoundLoop(const string& musicName)
{ //=========================================================================================================================
	sp<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->playLoop();
		return m;
	}
	return nullptr;
}




bool AudioManager::isSoundPlaying(sp<Sound> m)
{ //=========================================================================================================================

	if (playingAudioList.contains(m) == false)return false;
	return m->isPlaying();
}

bool AudioManager::isSoundPlaying(const string& musicName)
{ //=========================================================================================================================
	sp<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		if (playingAudioList.contains(m) == false)return false;
		return m->isPlaying();
	}
	return false;
}

void AudioManager::stopMusic(sp<Sound> m)
{ //=========================================================================================================================
	stopSound(m);
}
void AudioManager::stopSound(sp<Sound> m)
{ //=========================================================================================================================
	m->stop();
}

void AudioManager::stopMusic(const string& musicName)
{ //=========================================================================================================================
	stopSound(musicName);
}

void AudioManager::stopSound(const string& musicName)
{ //=========================================================================================================================
	sp<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->stop();
	}
}



void AudioManager::fadeOutSound(const string& musicName, int ticks)
{ //=========================================================================================================================
	sp<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->fadeOutAndStop(ticks);
	}
	
}

void AudioManager::fadeOutSound(sp<Sound> m, int ticks)
{ //=========================================================================================================================
	if (m != nullptr)
	{
		m->fadeOutAndStop(ticks);
	}
}



bool AudioManager::isAnyMusicPlaying()
{ //=========================================================================================================================
	return isAnyLoopingSoundPlaying();
}

bool AudioManager::isAnyLoopingSoundPlaying()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop() && m->isPlaying())
		{
			return true;
		}
	}
	return false;
}
//=========================================================================================================================
void AudioManager::pauseAnyPlayingLoopingSounds()
{//=========================================================================================================================

	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop() && m->isPlaying())
		{
			m->pause();
		}
	}
}
//=========================================================================================================================
void AudioManager::playAnyPausedLoopingSounds()
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop() && m->isPlaying())
		{
			m->unpause();
		}
	}

}
//=========================================================================================================================
void AudioManager::setAllPlayingSoundsVolume(float v)
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->isPlaying())
		{
			m->setVolume(v);
		}
	}
}
//=========================================================================================================================
void AudioManager::setAllPlayingLoopingSoundsVolume(float v)
{//=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->isPlaying() && m->getLoop())
		{
			m->setVolume(v);
		}
	}
}


void AudioManager::stopAllMusic()
{ //=========================================================================================================================
	stopAllLoopingSounds();
}
void AudioManager::stopAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound>m = playingAudioList.at(i);
		if(m->getLoop())m->stop();
	}
	
}

void AudioManager::fadeOutAllMusic(int ticks)
{ //=========================================================================================================================
	fadeOutAllLoopingSounds(ticks);
}

void AudioManager::fadeOutAllLoopingSounds(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);

		if (m->getLoop())m->fadeOutAndStop(ticks);
		
	}
	
}
void AudioManager::fadeOutAllSounds(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);

		m->fadeOutAndStop(ticks);
		
	}
	
}

void AudioManager::setAllLoopingSoundsThatAreNotFadingOutToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop() && m->isPlaying() == true)
		{
			if (m->isFadingOut() == false)
			{
				m->setLoop(false);
			}
		}
	}
}

void AudioManager::setAllLoopingSoundsToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop() && m->isPlaying() == true)
		{
			
				m->setLoop(false);
			
		}
	}
}

void AudioManager::pauseAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop())m->pause();
	}
}

void AudioManager::unpauseAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		if (m->getLoop())m->unpause();
	}
}
void AudioManager::pauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		m->pause();
	}
}

void AudioManager::unpauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		sp<Sound> m = playingAudioList.at(i);
		m->unpause();
	}
}


//=========================================================================================================================
sp<AudioFile> AudioManager::getAudioFileByName(string name)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		sp<AudioFile> s = globalAudioFileList.at(i);
		if (s->getName() == name)return s;
	}
	return nullptr;
}


//=========================================================================================================================
sp<AudioFile> AudioManager::getAudioFileByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		sp<AudioFile> s = globalAudioFileList.at(i);
		if (s->getID() == id)return s;
	}
	return ms<AudioFile>(ms<AudioData>(id,"",""));
}

//=========================================================================================================================
sp<Sound> AudioManager::getSoundByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < playingAudioList.size(); i++)
	{
		if (playingAudioList.at(i)->getID()==id)
		{

			return playingAudioList.at(i);
		}
	}

	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		sp<AudioFile> s = globalAudioFileList.at(i);
		if (s->getID() == id)return ms<Sound>(e, s);
	}
	return ms<Sound>(e, ms<AudioFile>(ms<AudioData>(id,"","")));
}





































































int G_mute = 0;//GLOBAL MUTE

int current_bgm_volume = 0;

Mix_Music* song_playing = nullptr;


int* current_mod_data_pointer = nullptr;


string playingname = "";// [128];


Mix_Chunk* mixchunks[32] = { nullptr };
string mixchunkfilename[32] = { "" };



//==========================================================================================================================
char* HARDWARE_get_sound_filename_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;

	//if(strcmp(name,"footstep")==0)filename=footstep_FileName;

	return filename;
}


//==========================================================================================================================
Mix_Chunk* HARDWARE_get_sound_data_pointer_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;


	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == NULL)return NULL;

	//search mixchunkfilenames 0-31 for matches with filename
	int d = -1;
	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] == filename)
		{
			d = x;
			x = MAX_SOUNDS_PLAYING;
			break;
		}
	}

	if (d == -1)
	{
		//find open filename slot
		for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
		{
			if (mixchunkfilename[x] == "")
			{
				d = x;
				mixchunkfilename[d] = filename;//set slot to filename
				mixchunks[d] = Mix_LoadWAV(mixchunkfilename[d].c_str());//load wav
				x = MAX_SOUNDS_PLAYING;
				break;
			}
		}
	}

	return mixchunks[d];
}


//==========================================================================================================================
bool HARDWARE_play_sound(string &name, int vol, int freq, int loop)//if(!HARDWARE_is_sound_channel_busy(chan))//HARDWARE_PlayFSSoundEx2(chan,HARDWARE_FSGetFile(0,name,""),vol,freq,0,loop,0);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	Mix_Chunk* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, freq);

	if (data != NULL)
	{
		if (loop == 1)loop = -1;//infinite loops
		Mix_VolumeChunk(data, (int)(MIX_MAX_VOLUME * ((float)((float)vol / 256.0f))));
		Mix_PlayChannel(-1, data, loop);
	}
	else
	{
		ERROR_set_error(name);
		ERROR_set_error(" could not be played.\n");
	}


	return true;
}

//==========================================================================================================================
bool HARDWARE_play_sound_if_not_playing(string &name, int vol, int freq, int loop)
{//==========================================================================================================================


	if (G_mute)vol = 0;


	char* filename = nullptr;
	filename = HARDWARE_get_sound_filename_from_name(name, freq);
	if (filename == nullptr)return 0;

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunkfilename[x] != "")
			if (mixchunkfilename[x] == filename)
			{
				return 0;
			}
	}

	HARDWARE_play_sound(name, vol, freq, loop);


	return 1;
}

//==========================================================================================================================
void HARDWARE_stop_sound(string &name)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	Mix_Chunk* data = NULL;
	data = HARDWARE_get_sound_data_pointer_from_name(name, 44100);

	//go through all playing channels, if channel is playing data, stop channel
	if (data != NULL)
	{
		int channel = 0;
		int maxchannels = Mix_AllocateChannels(-1);

		for (channel = 0; channel < maxchannels; channel++)
		{
			if (data == Mix_GetChunk(channel))Mix_HaltChannel(channel);
		}
	}
}

//==========================================================================================================================
void HARDWARE_unload_wavs_done_playing()
{//==========================================================================================================================

 //go through each mixchunk->at(d)
 //see if still playing
 //if not playing, unload mixchunk->at(d) and set mixchunkfilename->at(d) to NULL

	int x = 0;
	for (x = 0; x < MAX_SOUNDS_PLAYING; x++)
	{
		if (mixchunks[x] != nullptr && mixchunkfilename[x] != "")
		{
			int channel = 0;
			int playing = 0;
			int maxchannels = Mix_AllocateChannels(-1);
			for (channel = 0; channel < maxchannels; channel++)
			{
				if (mixchunks[x] == Mix_GetChunk(channel))playing = 1;
			}

			if (playing == 0)
			{
				if (
					mixchunkfilename[x] == "data/sfx/footstepnormal.wav"//dont unload footstep, its used a lot
					)
				{
					Mix_FreeChunk(mixchunks[x]);
					mixchunks[x] = nullptr;
					mixchunkfilename[x] = "";
				}
			}
		}
	}
}

//==========================================================================================================================
void HARDWARE_set_channel_volume(int chan, int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;
	else
		Mix_Volume(chan, (int)(MIX_MAX_VOLUME * ((float)((float)vol / 256.0f))));
}


//==========================================================================================================================
void HARDWARE_set_music_volume(int vol)//if(HARDWARE_is_sound_channel_busy(chan))HARDWARE_StopSound(chan);
{//==========================================================================================================================

	if (G_mute)vol = 0;

	if (current_bgm_volume != vol)
	{
		current_bgm_volume = vol;
		if (song_playing != NULL)Mix_VolumeMusic((int)(MIX_MAX_VOLUME * ((float)((float)vol / 64.0f))));
	}
}


//==========================================================================================================================
void HARDWARE_play_music(string &name, int vol)//HARDWARE_PlayFSMod(mod);
{//==========================================================================================================================

	if (G_mute)vol = 0;


	if (name == playingname || song_playing == NULL)
	{
		//copy string into playing string
		//strcpy(playingname, name);
		playingname = name;

		//free the previous song
		if (song_playing != NULL)
		{
			Mix_HookMusicFinished(NULL);
			Mix_HaltMusic();
			while (Mix_PlayingMusic())
			{
			};
			Mix_FreeMusic(song_playing);
			while (Mix_PlayingMusic())
			{
			};
			song_playing = NULL;
		}

		//load the new one
		if (name == "nice") song_playing = Mix_LoadMUS("data/bgm/snappy_nice_v01.s3m");

		if (song_playing == NULL)
		{
			ERROR_set_error(name);
			ERROR_set_error(" could not be loaded.\n");
		}
		else
			Mix_PlayMusic(song_playing, -1);
	}


	if (vol != current_bgm_volume)
	{
		current_bgm_volume = vol;
		if (song_playing != NULL)Mix_VolumeMusic((int)(MIX_MAX_VOLUME * ((float)((float)vol / 64.0f))));
	}
}


//==========================================================================================================================
void HARDWARE_stop_music()//HARDWARE_StopMod();
{//==========================================================================================================================

	if (song_playing != NULL)
	{
		Mix_HookMusicFinished(NULL);
		Mix_HaltMusic();
		while (Mix_PlayingMusic())
		{

		}

		Mix_FreeMusic(song_playing);
		while (Mix_PlayingMusic())
		{

		}

		song_playing = NULL;
	}
}
