//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "AudioData.h"
class Logger;

#include "src/Engine/network/ServerObject.h"


class Logger;

class AudioFile : public ServerObject
{
public:
	static Logger log;

protected:

	bool _fileExists = false;
	bool startedDownloadThread = false;


	AudioData* data = nullptr;

	ByteArray* byteData = nullptr;



public:


	AudioFile(AudioData* data);

	//Only for use for preloading sound files not on server, they do not have IDs
	AudioFile(string filename);

	AudioData* getData();

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
	ByteArray* getByteData();


	void setData_S(AudioData* data);


	virtual void update() override;



};

