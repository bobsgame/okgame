//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "src/Engine/network/ServerObject.h"

class SoundData;
class Logger;

class Sound : public ServerObject
{
public:
	static Logger log;

protected:
	bool fileExists = false;
	bool _fileExists = false;
	bool startedDownloadThread = false;


private:
	SoundData* data = nullptr;
public:
	vector<u8>* byteData = nullptr;


private:
	int channel = 0;

#ifdef USE_SOLOUD
	SoLoud::Wav *soLoudWave = nullptr;
#endif
#ifdef USE_SDL_MIXER
	Mix_Chunk* mixChunk = nullptr;
#endif
protected:
	//ArrayList<SoundChannel*>* soundChannels;


public:
	//Sound(Engine* g, int id);


	Sound(Engine* g, SoundData* data);


	//Only for use for preloading sound files not on server, they do not have IDs
	Sound(Engine* g, string filename);


	SoundData* getData();

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
	vector<u8>* getByteData();


	//The following method was originally marked 'synchronized':
	void setData_S(SoundData* data);

	//Thread* downloadThread = nullptr;


	virtual void update() override;


	void play();


	void play(float pitch, float volume, int timesToPlay);





	protected:
		bool shouldBePlaying = false;
		bool playingStarted = false;
		float pitch = 1.0f;
		float volume = 1.0f;
		//bool loop = false;
	public:
		int timesToPlay = 1;
		//bool deleting = false;




		void handlePlaying();

		void stop();

};

