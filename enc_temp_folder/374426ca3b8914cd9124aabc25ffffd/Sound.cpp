#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------




Logger Sound::log = Logger("Sound");

//Sound::Sound(Engine* g, int id)
//{ //=========================================================================================================================
//
//	this->e = g;
//	this->data = new SoundData(id, "", "");
//
//	for (int i = 0; i < (int)Main::audioManager->soundList->size(); i++)
//	{
//		if (Main::audioManager->soundList->get(i)->getName() == data->getName())
//		{
//			log.warn("Sound already exists:" + data->getName());
//			return;
//		}
//	}
//	Main::audioManager->soundList->add(this);
//}

Sound::Sound(Engine* g, SoundData* data)
{ //=========================================================================================================================
	this->e = g;

	this->data = data;
	setInitialized_S(true);

	for (int i = 0; i < (int)AudioManager::soundList->size(); i++)
	{
		if (AudioManager::soundList->get(i)->getName() == data->getName())
		{
			if (AudioManager::soundList->get(i)->getID() == -1)AudioManager::soundList->get(i)->setID(data->getID());
			//log.warn("Sound already exists:" + data->getName());
			return;
		}
	}
	AudioManager::soundList->add(this);
}


Sound::Sound(Engine *g, string filename)
{ //=========================================================================================================================
	
	this->e = g;

	string name = string(filename);
	int found = (int)name.find('/');
	while (found != string::npos)
	{
		name = name.substr(found + 1, name.length());
		found = (int)name.find('/');
	}

	found = (int)name.find('.');
	if (found != string::npos)
		name = name.substr(0, found);

	this->data = new SoundData(-1, name, filename);

	byteData = FileUtils::loadByteFileFromExePath(filename);

#ifdef USE_SOLOUD
	filename = Main::getPath() + filename;
	soLoudWave = new SoLoud::Wav();
	//log.debug(filename);
	soLoudWave->load(filename.c_str());
#endif
#ifdef USE_SDL_MIXER
	filename = Main::getPath() + filename;
	mixChunk = Mix_LoadWAV(filename.c_str());
#endif

	loadedInfoDataFromServer = true;
	fileExists = true;
	setInitialized_S(true);

	AudioManager::soundList->add(this);

}

SoundData* Sound::getData()
{ //=========================================================================================================================
	return data;
}

int Sound::getID()
{
	return data->getID();
}

string& Sound::getName()
{
	return data->getName();
}

string& Sound::getFileName()
{
	return data->getFileName();
}

string& Sound::getMD5Name()
{
	return data->getMD5Name();
}

string Sound::getTYPEIDString()
{
	return data->getTYPEIDString();
}

void Sound::setID(int id)
{
	data->setID(id);
}

void Sound::setName(const string& name)
{
	data->setName(name);
}

void Sound::setFileName(const string& fileName)
{
	data->setFileName(fileName);
}

void Sound::setMD5Name(const string& s)
{
	data->setMD5Name(s);
}

bool Sound::getFileExists()
{ //=========================================================================================================================
	return _fileExists;
}

void Sound::setFileExists(bool i)
{ //=========================================================================================================================
	_fileExists = i;
}

vector<u8>* Sound::getByteData()
{ //=========================================================================================================================
	return byteData;
}

//The following method was originally marked 'synchronized':
void Sound::setData_S(SoundData* data)
{ //=========================================================================================================================

	this->data = data;
	setInitialized_S(true);
}

void Sound::update()
{ //=========================================================================================================================

	//get the name and filename from the server
	ServerObject::update();

	if (loadedInfoDataFromServer == false)
	{
		return;
	}

	//download the file to the cache if it doesnt exist
	if (fileExists == false && getByteData() == nullptr)
	{
		if (getFileExists() == false)
		{
			if (startedDownloadThread == false)
			{
				startedDownloadThread = true;

				//check cache FIRST before start thread.
				//only start thread if not in cache.
				if (FileUtils::checkIfFileExistsInCache(getMD5Name()))
				{
					setFileExists(true);
				}
				else
				{
					//               downloadThread = new Thread([&] ()
					//                  {
					//                     try
					//                     {
					//                        Thread::currentThread().setName("Sound_downloadToCache");
					//                     }
					//                     catch (SecurityException e)
					//                     {
					//                        e->printStackTrace();
					//                     }
					//                     //now check the cache and download the mp3/ogg/xm/s3m from the s3 bucket in a new thread if not exist.
					//                     Cache::downloadBigFileToCacheIfNotExist(getMD5Name());
					//                  }
					//               );
					//
					//               downloadThread->start();
				}
			}
			else
			{
				//            if (downloadThread != nullptr && downloadThread->isAlive() == false)
				//            {
				if (FileUtils::checkIfFileExistsInCache(getMD5Name()))
				{
					setFileExists(true);
				}
				//               else
				//               {
				//                  log.warn("Download thread timed out for Sound: " + name());
				//                  downloadThread->start();
				//               }
				//            }
			}
		}
		else
		{
			fileExists = true;
		}
	}

	if (fileExists == true || getByteData() != nullptr)
	{
		handlePlaying();

	}


}

void Sound::play()
{ //=========================================================================================================================
	play(1.0f, 1.0f, 0);
}



void Sound::play(float pitch, float volume, int timesToPlay)
{ //=========================================================================================================================

	if (timesToPlay < 0)
	{
		log.error("Trying to play sound -1 times. Sounds cannot be infinitely looped, only music can.");
	}

	if (timesToPlay == 1)
	{
		timesToPlay = 0;
	}

	this->pitch = pitch;
	this->volume = volume;
	this->timesToPlay = timesToPlay;

	shouldBePlaying = true;

	update();
}

void Sound::handlePlaying()
{ //=========================================================================================================================
	   if (shouldBePlaying == true)
	   {

	         if (getByteData() == nullptr)
	         {
	            //channel = AudioUtils::open(outerInstance->getFileName(), Cache::cacheDir + outerInstance->getMD5Name());
	         }
	         else
	         {
	            //channel = AudioUtils::open(outerInstance->getFileName(), outerInstance->getMD5Name(), outerInstance->getByteData());
	         }
	      

	         if (playingStarted == false)
	         {

#ifdef USE_SOLOUD
				 AudioManager::soLoud->play(*soLoudWave);
#endif
#ifdef USE_SDL_MIXER
				 channel = Mix_PlayChannel(-1, mixChunk, false);
#endif
				
	            playingStarted = true;
				
	         }
	         else
	         {
				 if (Mix_Playing(channel) == false) 
				 {
					 if (timesToPlay > 0)
					 {
					    timesToPlay--;
					    playingStarted = false;
					 }
					 else
					 {
						 stop();
					 }

				 }
	         }	      
	   }
	   else
	   {
		   if (playingStarted == true)
		   {
			   stop();
		   }
	   }
}

//=========================================================================================================================
void Sound::stop()
{//=========================================================================================================================

	pitch = 1.0f;
	volume = 1.0f;
	timesToPlay = 1;

	shouldBePlaying = false;

	if (playingStarted)
	{
		if (channel != -1)
		{
			Mix_HaltChannel(channel);
		}

		playingStarted = false;
	}

	channel = -1;
}