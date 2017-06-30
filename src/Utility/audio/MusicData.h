//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MusicData : public AssetData
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
	
	string fullFilePath = ""; //for use in editor

	
	string md5Name = ""; //for use in client

	
	bool preload = false;


public:
	MusicData();


	MusicData(int id, const string& name, const string& filename);


	//static MusicData* fromBase64ZippedJSON(const string& b64);
	//static MusicData* fromJSON(const string& json);

	string& initFromString(string& t);


	string getTYPEIDString();


	string& getFileName();
	string& getFullFilePath();
	string& getMD5Name();
	bool getPreload();


	void setFileName(const string& s);
	void setFullFilePath(const string& s);
	void setMD5Name(const string& s);
	void setPreload(bool s);
};

