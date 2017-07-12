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

Sound::Sound(Engine* g, AudioFile *f)
{ //=========================================================================================================================
	this->e = g;

	this->audioFile = f;

	for (int i = 0; i < (int)getAudioManager()->playingAudioList.size(); i++)
	{
		if (getAudioManager()->playingAudioList.get(i)->getName() == f->getName())
		{
			if (getAudioManager()->playingAudioList.get(i)->getID() == -1)getAudioManager()->playingAudioList.get(i)->setID(f->getID());
			//log.warn("Sound already exists:" + data->getName());
			return;
		}
	}
	getAudioManager()->playingAudioList.add(this);


	if (f->getByteData() != nullptr)initFromByteData();
}



void Sound::initFromByteData()
{//=========================================================================================================================
	
#ifdef USE_SOLOUD
	filename = Main::getPath() + filename;
	soLoudWave = new SoLoud::Wav();
	//log.debug(filename);
	soLoudWave->load(filename.c_str());
#endif
#ifdef USE_SDL_MIXER

	SDL_RWops* file = SDL_RWFromMem(audioFile->getByteData()->data(), audioFile->getByteData()->size());
	mixChunk = Mix_LoadWAV_RW(file, 0);
	file->close(file);

#endif

}


string Sound::getName()
{
	return audioFile->getName();

}

int Sound::getID()
{
	return audioFile->getID();

}
void Sound::setID(int id)
{
	return audioFile->setID(id);

}



void Sound::update()
{ //=========================================================================================================================

	//get the name and filename from the server



	if (audioFile->getFileExists() == true || audioFile->getByteData() != nullptr)
	{

		if (mixChunk == nullptr)initFromByteData();

		if (paused)
		{

		}
		else
		if (shouldBePlaying == true)
		{

	

			if (playingStarted)
			{
				if (Mix_Playing(channel) == false)
				{


					//music
					if (loop == false)
					{
						if (timesToPlay > 1)
						{
							timesToPlay--;
							channel = Mix_PlayChannel(-1, mixChunk, 0);
						}
						else
						{
							stop();
						}
					}
					else
					{
						channel = Mix_PlayChannel(-1, mixChunk, 0);
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

		if (ticksToFadeOutTotal != -1)
		{
			ticksToFadeOutCounter -= (int)getEngine()->engineTicksPassed();

			if (ticksToFadeOutCounter <= 0)
			{
				stop();
			}
			else
			{
				setVolume(((float)(ticksToFadeOutCounter) / (float)(ticksToFadeOutTotal)) * volumeWhenStartedFade);
			}
		}

	}


}




void Sound::playOnce()
{ //=========================================================================================================================
	play(1.0f, getVolume(), 1);
}
void Sound::playLoop()
{ //=========================================================================================================================
	play(1.0f, getVolume(), true);
}


void Sound::play(float pitch, float volume, int timesToPlay)
{ //=========================================================================================================================

	if (timesToPlay < 0)
	{
		timesToPlay = 1;
		// log.error("Trying to play sound -1 times. Sounds cannot be infinitely looped, only music can.");
	}

	if (timesToPlay == 1)
	{
		timesToPlay = 1;
	}

	this->pitch = pitch;
	this->volume = volume;
	this->timesToPlay = timesToPlay;

	playImmediately();
}




void Sound::play(float pitch, float volume, bool loop)
{ //=========================================================================================================================

	if (this->pitch != pitch || this->volume != volume || this->loop != loop)
	{
		this->pitch = pitch;
		this->volume = volume;
		this->loop = loop;
	}

	shouldBePlaying = true;

	playImmediately();
}

void Sound::playImmediately()
{//=========================================================================================================================
	shouldBePlaying = true;


#ifdef USE_SOLOUD
	AudioManager::soLoud->play(*soLoudWave);
#endif
#ifdef USE_SDL_MIXER
	channel = Mix_PlayChannel(-1, mixChunk, 0);
	//could maybe use the callback function to replay the music without any delay due to frame skipping etc which may happen when doing it this way
#endif
	playingStarted = true;


	update();

}


void Sound::fadeOutAndStop(int ticksToFadeOut)
{ //=========================================================================================================================

	this->ticksToFadeOutTotal = ticksToFadeOut;
	this->ticksToFadeOutCounter = ticksToFadeOut;
	this->volumeWhenStartedFade = volume;
}

bool Sound::isFadingOut()
{ //=========================================================================================================================
	if (ticksToFadeOutTotal != -1)
	{
		return true;
	}

	return false;
}

void Sound::pause()
{ //=========================================================================================================================

	Mix_Pause(channel);
	paused = true;

}

void Sound::unpause()
{ //=========================================================================================================================

	Mix_Resume(channel);
	paused = false;

}


//=========================================================================================================================
void Sound::stop()
{//=========================================================================================================================

	pitch = 1.0f;
	volume = 1.0f;
	timesToPlay = 1;

	loop = false;
	ticksToFadeOutCounter = -1;
	ticksToFadeOutTotal = -1;
	volumeWhenStartedFade = 0;

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




void Sound::setLoop(bool b)
{ //=========================================================================================================================
	this->loop = b;
}

bool Sound::getLoop()
{ //=========================================================================================================================
	return loop;
}

bool Sound::isPlaying()
{ //=========================================================================================================================

	return shouldBePlaying;

}

void Sound::setVolume(float v)
{ //=========================================================================================================================
	volume = v;
#ifdef USE_SDL_MIXER
	if (isPlaying()) Mix_Volume(channel, (int)(volume * 128));

#endif
}
float Sound::getVolume()
{
	return volume;

}
float Sound::getPitch()
{
	return pitch;

}
void Sound::setPitch(float p)
{ //=========================================================================================================================

	pitch = p;
	//   if (channel != nullptr)
	//   {
	//      channel->setPitch(p);
	//   }
}


