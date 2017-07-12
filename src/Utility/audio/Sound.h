//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;

#include "src/Engine/network/ServerObject.h"


class Logger;

class Sound : EnginePart
{
public:
	static Logger log;

	AudioFile* audioFile = nullptr;



	int channel = -1;

#ifdef USE_SOLOUD
	SoLoud::Wav *soLoudWave = nullptr;
#endif
#ifdef USE_SDL_MIXER
	Mix_Chunk* mixChunk = nullptr;
#endif

	Sound::Sound(Engine* g, AudioFile *f);



	void update();

	void initFromByteData();

	string getName();
	int getID();
	void setID(int id);
	protected:
		bool shouldBePlaying = false;
		bool playingStarted = false;
		float pitch = 1.0f;
		float volume = 1.0f;
		bool loop = false;

		bool paused = false;

		int ticksToFadeOutTotal = -1;
		int ticksToFadeOutCounter = -1;
		float volumeWhenStartedFade = 0;

	public:
		int timesToPlay = 1;
		//bool deleting = false;



		void stop();

		void playOnce();
		void playLoop();

		void play(float pitch, float volume, int timesToPlay);

		void play(float pitch, float volume, bool loop);

		void fadeOutAndStop(int ticksToFadeOut);

		bool isFadingOut();

		void pause();

		void unpause();


		void setLoop(bool b);

		bool getLoop();


		bool isPlaying();

		void setVolume(float v);
		float getVolume();
		float getPitch();

		void setPitch(float p);

};

