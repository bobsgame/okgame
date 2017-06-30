//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class SoundData : public AssetData
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

private:
	
	string fileName = "";
	
	string fullFilePath = "";


	
	string md5Name = ""; //for use in client


public:
	SoundData();


	SoundData(int id, const string& name, const string& filename);


	//static SoundData* fromBase64ZippedJSON(const string& b64);


	//static SoundData* fromJSON(const string& json);

	string& initFromString(string& t);


	string getTYPEIDString();

	string& getFileName();
	string& getFullFilePath();
	string& getMD5Name();


	void setFileName(const string& s);
	void setFullFilePath(const string& s);
	void setMD5Name(const string& s);
};

