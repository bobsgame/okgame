#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------




Logger AudioFile::log = Logger("AudioFile");



AudioFile::AudioFile(shared_ptr<AudioData> data)
{ //=========================================================================================================================


	this->data = data;
	setInitialized_S(true);


	for (int i = 0; i < (int)AudioManager::globalAudioFileList.size(); i++)
	{
		if (AudioManager::globalAudioFileList.get(i)->getName() == data->getName())
		{
			if (AudioManager::globalAudioFileList.get(i)->getID() == -1)AudioManager::globalAudioFileList.get(i)->setID(data->getID());
			//log.warn("Sound already exists:" + data->getName());
			return;
		}
	}
	AudioManager::globalAudioFileList.add(this);
}


AudioFile::AudioFile(string filename)
{ //=========================================================================================================================

#ifdef _DEBUG
	log.info("Loading " + filename);
#endif
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

	this->data = make_shared<AudioData>(-1, name, filename);

	byteData = FileUtils::loadByteFileFromExePath(filename);



	loadedInfoDataFromServer = true;
	_fileExists = true;
	setInitialized_S(true);

	AudioManager::globalAudioFileList.add(this);

	log.info("Loaded " + filename);

}

shared_ptr<AudioData> AudioFile::getData()
{ //=========================================================================================================================
	return data;
}

int AudioFile::getID()
{
	return data->getID();
}


string& AudioFile::getName()
{
	return data->getName();
}


string& AudioFile::getFileName()
{
	return data->getFileName();
}


string& AudioFile::getMD5Name()
{
	return data->getMD5Name();
}



void AudioFile::setID(int id)
{
	data->setID(id);
}

void AudioFile::setName(const string& name)
{
	data->setName(name);
}

void AudioFile::setFileName(const string& fileName)
{
	data->setFileName(fileName);
}

void AudioFile::setMD5Name(const string& s)
{
	data->setMD5Name(s);
}

bool AudioFile::getFileExists()
{ //=========================================================================================================================
	return _fileExists;
}

void AudioFile::setFileExists(bool i)
{ //=========================================================================================================================
	_fileExists = i;
}

shared_ptr<ByteArray> AudioFile::getByteData()
{ //=========================================================================================================================
	return byteData;
}

//The following method was originally marked 'synchronized':
void AudioFile::setData_S(shared_ptr<AudioData> data)
{ //=========================================================================================================================

	this->data = data;
	setInitialized_S(true);
}

void AudioFile::update()
{ //=========================================================================================================================

  //get the name and filename from the server
	ServerObject::update();

	if (loadedInfoDataFromServer == false)
	{
		return;
	}

	//download the file to the cache if it doesnt exist
	if (getByteData() == nullptr)
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
					//               downloadThread = make_shared<Thread>([&] ()
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

	}




}
