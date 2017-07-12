//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class AudioData : public AssetData
{

private:
	typedef AssetData super;



	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

protected:

	string fileName = "";

	string fullFilePath = "";



	string md5Name = ""; //for use in client


	bool preload = false;


public:
	AudioData();


	AudioData(int id, const string& name, const string& filename);


	//static AudioData* fromBase64ZippedJSON(const string& b64);


	//static AudioData* fromJSON(const string& json);

	string& initFromString(string& t);


	string& getFileName();
	string& getFullFilePath();
	string& getMD5Name();
	bool getPreload();

	void setFileName(const string& s);
	void setFullFilePath(const string& s);
	void setMD5Name(const string& s);
	void setPreload(bool s);
};

