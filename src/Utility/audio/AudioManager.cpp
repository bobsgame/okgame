
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
ArrayList<shared_ptr<AudioFile>> AudioManager::globalAudioFileList;
bool AudioManager::loadedBuiltIn = false;

//=========================================================================================================================
AudioManager::AudioManager()
{ //=========================================================================================================================


}

//=========================================================================================================================
AudioManager::AudioManager(shared_ptr<Engine> g)
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

	log->debug("Init SDL Mixer");

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
	{
		log->error("Couldn't set up audio: " + string(SDL_GetError()));
	}
	Mix_AllocateChannels(32);

#endif

	GLUtils::checkSDLError("AudioManager::initAudioLibrary()");

#ifdef USE_SOLOUD
	soLoud = make_shared<SoLoud>::Soloud();
	soLoud->init();
#endif


	now = SDL_GetPerformanceCounter();
	log->debug("Init SDL Mixer took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();



	if (loadedBuiltIn == false)
	{
		loadedBuiltIn = true;


		Uint64 start = 0, now = 0, totalStart = 0, totalNow = 0;
		start = SDL_GetPerformanceCounter();
		totalStart = SDL_GetPerformanceCounter();

		log->debug("Loading built in sounds");
		{
			log->debug("get path");
			string spriteFolderString = Main::getPath() + "data/sounds/";
			//log->debug("create path");
			//Path spriteFolderPath(spriteFolderString);
			log->debug("create file");
			File spriteFolderPathDir(spriteFolderString);
			log->debug("createDirectories");
			if (spriteFolderPathDir.exists() == false)spriteFolderPathDir.createDirectories();
			vector<string> files;
			log->debug("list");
			spriteFolderPathDir.list(files);
			vector<string>::iterator it = files.begin();
			for (; it != files.end(); ++it)
			{
				//cout << *it << endl;
				string name = *it;
				if (name.find(".ogg") != string::npos)
				{
					make_shared<AudioFile>("data/sounds/" + name);
				}
			}
		}

		now = SDL_GetPerformanceCounter();
		log->debug("Loading sounds took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
		start = SDL_GetPerformanceCounter();


		log->debug("Loading built in music");
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
					make_shared<AudioFile>("data/music/" + name);
				}
			}
		}

		now = SDL_GetPerformanceCounter();
		log->debug("Loading music took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
		start = SDL_GetPerformanceCounter();

		totalNow = SDL_GetPerformanceCounter();
		log->debug("initAudioLibrary took " + to_string((double)((totalNow - totalStart) * 1000) / SDL_GetPerformanceFrequency()) + "ms");


		//GLUtils::e();
	}

	//	//load sounds/index.txt
	//	//for each line, load ogg file
	//	ArrayList<string>* stringList = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/sounds/index.txt");
	//	if (stringList->size() > 0)
	//	{
	//		for (int i = 0; i < stringList->size(); i++)
	//		{
	//			string s = stringList->get(i);
	//
	//			if (s.length() > 0)
	//			{
	//				//shared_ptr<Sound>sound =
	//				make_shared<Sound>(this, "data/sounds/" + s);
	//				//sound.byteData = dataFile.readBytes();
	//			}
	//		}
	//	}


}





//=========================================================================================================================
void AudioManager::cleanup()
{//=========================================================================================================================

	log->info("Cleaning up audio");
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

//shared_ptr<Sound> AudioManager::loadSoundFileByName(const string& fileName)
//{ //=========================================================================================================================
//
//	shared_ptr<Sound> s = nullptr;
//
//	for(int i=0;i<soundList.size();i++)if(soundList.get(i)->getName() == fileName)s = soundList.get(i);
//
//	if (s == nullptr)
//	{
//		HashMap<string, shared_ptr<Sound>>::const_iterator got = soundByNameHashMap->find(fileName);
//		if (got != soundByNameHashMap->end())
//			s = soundByNameHashMap->get(fileName);
//	}
//
//	if (s == nullptr)
//	{
//	    s = make_shared<Sound>(fileName);
//	    soundByNameHashMap->insert_or_assign(s->getName(),s);
//	}
//
//	return s;
//}



void AudioManager::globalUpdate()
{
	
	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		globalAudioFileList.get(i)->update();
	}
}


void AudioManager::update()
{ //=========================================================================================================================



	for (int i = 0; i < playingAudioList.size(); i++)
	{
		playingAudioList.get(i)->update();
	}
}

shared_ptr<Sound> AudioManager::getSoundByName(const string& musicName)
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
		string name = playingAudioList.get(i)->getName();

		if (OKString::startsWith(name, clippedName))
		{
			
			return playingAudioList.get(i);
		}
	}


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		string name = globalAudioFileList.get(i)->getName();

		if (OKString::startsWith(name, clippedName))
		{
			shared_ptr<Sound> s = make_shared<Sound>(getEngine(), globalAudioFileList.get(i));
			playingAudioList.add(s);
			return s;
		}
	}






	return nullptr;
}


//=========================================================================================================================
void AudioManager::playMusic(shared_ptr<Sound> s, float vol, float pitch, bool loop)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.add(s);
		s->play(pitch, vol, loop);
	}
}

shared_ptr<Sound> AudioManager::playMusic(const string& musicName, float volume, float pitch, bool loop)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->play(pitch, volume, loop);
		if (playingAudioList.contains(m) == false)playingAudioList.add(m);
		return m;
	}
	return nullptr;
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch)
{ //=========================================================================================================================

	return playSound(soundName,volume,pitch,1);

}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName)
{ //=========================================================================================================================
	return playSound(soundName, 1, 1, 1);
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::playSound(const string& soundName, float volume, float pitch, int times)
{ //=========================================================================================================================

	shared_ptr<Sound> s = getSoundByName(soundName);
	if (s != nullptr)
	{
		s->play(pitch, volume, times);
		return s;
	}
	return nullptr;

	//Exception e = make_shared<Exception>();e.printStackTrace();
}


//=========================================================================================================================
void AudioManager::playSound(shared_ptr<Sound> s, float vol, float pitch, int times)
{ //=========================================================================================================================
	if (s != nullptr)
	{
		if (playingAudioList.contains(s) == false)playingAudioList.add(s);
		s->play(pitch, vol, times);
	}
}

void AudioManager::playMusic(shared_ptr<Sound> m)
{ //=========================================================================================================================
	playSoundLoop(m);
}
void AudioManager::playSoundLoop(shared_ptr<Sound> m)
{ //=========================================================================================================================
	m->playLoop();
	if (playingAudioList.contains(m) == false)playingAudioList.add(m);
}

shared_ptr<Sound> AudioManager::playMusic(const string& musicName)
{ //=========================================================================================================================
	return playSoundLoop(musicName);
}
shared_ptr<Sound> AudioManager::playSoundLoop(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		m->playLoop();
		return m;
	}
	return nullptr;
}




bool AudioManager::isSoundPlaying(shared_ptr<Sound> m)
{ //=========================================================================================================================

	if (playingAudioList.contains(m) == false)return false;
	return m->isPlaying();
}

bool AudioManager::isSoundPlaying(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);
	if (m != nullptr)
	{
		if (playingAudioList.contains(m) == false)return false;
		return m->isPlaying();
	}
	return false;
}

void AudioManager::stopMusic(shared_ptr<Sound> m)
{ //=========================================================================================================================
	stopSound(m);
}
void AudioManager::stopSound(shared_ptr<Sound> m)
{ //=========================================================================================================================
	m->stop();
}

void AudioManager::stopMusic(const string& musicName)
{ //=========================================================================================================================
	stopSound(musicName);
}

void AudioManager::stopSound(const string& musicName)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->stop();
	}
}



void AudioManager::fadeOutSound(const string& musicName, int ticks)
{ //=========================================================================================================================
	shared_ptr<Sound> m = getSoundByName(musicName);

	if (m != nullptr)
	{
		m->fadeOutAndStop(ticks);
	}
	
}

void AudioManager::fadeOutSound(shared_ptr<Sound> m, int ticks)
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound>m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);

		if (m->getLoop())m->fadeOutAndStop(ticks);
		
	}
	
}
void AudioManager::fadeOutAllSounds(int ticks)
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);

		m->fadeOutAndStop(ticks);
		
	}
	
}

void AudioManager::setAllLoopingSoundsThatAreNotFadingOutToNotLoop()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
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
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop())m->pause();
	}
}

void AudioManager::unpauseAllLoopingSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		if (m->getLoop())m->unpause();
	}
}
void AudioManager::pauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		m->pause();
	}
}

void AudioManager::unpauseAllSounds()
{ //=========================================================================================================================
	for (int i = 0; i < playingAudioList.size(); i++)
	{
		shared_ptr<Sound> m = playingAudioList.get(i);
		m->unpause();
	}
}


//=========================================================================================================================
shared_ptr<AudioFile> AudioManager::getAudioFileByName(string name)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getName() == name)return s;
	}
	return nullptr;
}


//=========================================================================================================================
shared_ptr<AudioFile> AudioManager::getAudioFileByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getID() == id)return s;
	}
	return make_shared<AudioFile>(make_shared<AudioData>(id,"",""));
}

//=========================================================================================================================
shared_ptr<Sound> AudioManager::getSoundByIDCreateIfNotExist(int id)
{//=========================================================================================================================


	for (int i = 0; i < playingAudioList.size(); i++)
	{
		if (playingAudioList.get(i)->getID()==id)
		{

			return playingAudioList.get(i);
		}
	}

	for (int i = 0; i < globalAudioFileList.size(); i++)
	{
		shared_ptr<AudioFile> s = globalAudioFileList.get(i);
		if (s->getID() == id)return make_shared<Sound>(e, s);
	}
	return make_shared<Sound>(e, make_shared<AudioFile>(make_shared<AudioData>(id,"","")));
}





































































int G_mute = 0;//GLOBAL MUTE

int current_bgm_volume = 0;

Mix_shared_ptr<Music> song_playing = nullptr;


int* current_mod_data_pointer = nullptr;


string playingname = "";// [128];


Mix_shared_ptr<Chunk> mixchunks[32] = { nullptr };
string mixchunkfilename[32] = { "" };



//==========================================================================================================================
char* HARDWARE_get_sound_filename_from_name(string &name, int freq)
{//==========================================================================================================================

	char* filename = NULL;

	//if(strcmp(name,"footstep")==0)filename=footstep_FileName;

	return filename;
}


//==========================================================================================================================
Mix_shared_ptr<Chunk> HARDWARE_get_sound_data_pointer_from_name(string &name, int freq)
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


	Mix_shared_ptr<Chunk> data = NULL;
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

	Mix_shared_ptr<Chunk> data = NULL;
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

 //go through each mixchunk->get(d)
 //see if still playing
 //if not playing, unload mixchunk->get(d) and set mixchunkfilename->get(d) to NULL

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
