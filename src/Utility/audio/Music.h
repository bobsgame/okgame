//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class MusicData;
class Logger;

class Music : public ServerObject
{
public:
	static Logger log;

protected:
	bool fileExists = false;
	bool _fileExists = false;
	bool startedDownloadThread = false;

private:
	MusicData* data = nullptr;
public:
	ByteArray* byteData = nullptr;

	

#ifdef USE_SOLOUD
		SoLoud::WavStream *soLoudWave = nullptr;
		SoLoud::Modplug *soLoudMod = nullptr;
#endif
#ifdef USE_SDL_MIXER
		Mix_Chunk* mixChunk = nullptr;
#endif


protected:
	//AudioChannel *channel = nullptr;
private:
	float pitch = 1.0f;
	float volume = 1.0f;
	bool loop = false;

	bool paused = false;

	bool shouldBePlaying = false;
	bool playingStarted = false;
	int ticksToFadeOutTotal = -1;
	int ticksToFadeOutCounter = -1;
	float volumeWhenStartedFade = 0;

	int channel = -1;

public:
	//Music(Engine* g, int id);

	Music(Engine* g, MusicData* data);
	Music(Engine *g, string filename);

	MusicData* getData();

	int getID();
	string& getName();
	string& getFileName();
	//public String getFullFilePath(){return data.getFullFilePath();}
	string& getMD5Name();

	string getTYPEIDString();

	void setID(int id);
	void setName(const string& name);
	void setFileName(const string& fileName);
	//public void setFullFilePath(String getFullFilePath){data.setFullFilePath(getFullFilePath);}
	void setMD5Name(const string& s);

protected:
	bool getFileExists();

	void setFileExists(bool i);

public:
	ByteArray* getByteData();

	//The following method was originally marked 'synchronized':
	void setData_S(MusicData* data);

	//Thread* downloadThread = nullptr;

	virtual void update() override;


	void play();

	void play(float pitch, float volume, bool loop);

	void fadeOutAndStop(int ticksToFadeOut);

	bool isFadingOut();

	void pause();

	void unpause();

	void stop();

	void setLoop(bool b);

	bool getLoop();


	bool isPlaying();

	void setVolume(float v);
	float getVolume();
	float getPitch();

	void setPitch(float p);
};

