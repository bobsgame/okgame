//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
#include "AudioData.h"
class Logger;

#include "src/Engine/network/ServerObject.h"


class Logger;

class AudioFile : public ServerObject, public std::enable_shared_from_this<AudioFile>
{
public:
	static Logger log;

protected:

	bool _fileExists = false;
	bool startedDownloadThread = false;


	sp<AudioData> data = nullptr;

	sp<ByteArray> byteData = nullptr;



public:


	AudioFile(sp<AudioData> data);

	//Only for use for preloading sound files not on server, they do not have IDs
	AudioFile(string filename);

	sp<AudioData> getData();

	int getID();
	string& getName();
	string& getFileName();
	//public String getFullFilePath(){return data.getFullFilePath();}
	string& getMD5Name();

	

	void setID(int id);
	void setName(const string& name);
	void setFileName(const string& fileName);
	//public void setFullFilePath(String getFullFilePath){data.setFullFilePath(getFullFilePath);}
	void setMD5Name(const string& s);

public:
	bool getFileExists();

	void setFileExists(bool i);

public:
	sp<ByteArray> getByteData();


	void setData_S(sp<AudioData> data);


	virtual void update() override;



};

