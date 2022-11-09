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


	shared_ptr<AudioData> data = nullptr;

	shared_ptr<ByteArray> byteData = nullptr;



public:


	AudioFile(shared_ptr<AudioData> data);

	//Only for use for preloading sound files not on server, they do not have IDs
	AudioFile(string filename);

	shared_ptr<AudioData> getData();

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
	shared_ptr<ByteArray> getByteData();


	void setData_S(shared_ptr<AudioData> data);


	virtual void update() override;



};

