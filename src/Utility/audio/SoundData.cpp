#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger SoundData::log = Logger("SoundData");


SoundData::SoundData()
{ //=========================================================================================================================
}

SoundData::SoundData(int id, const string& name, const string& filename)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->fileName = filename;
}
//
//SoundData* SoundData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = new Gson();
//	//SoundData data = gson.fromJson(json,SoundData.class);
//
//
//	return fromJSON(json);
//}
//
//SoundData* SoundData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//Gson* gson = new Gson();
//	SoundData* data = nullptr;// gson->fromJson(json, SoundData::typeid);
//
//
//	return data;
//}



string& SoundData::initFromString(string& t)
{
	t = super::initFromString(t);


	t = t.substr(t.find("fileName:`") + 1);
	t = t.substr(t.find("`") + 1);
	fileName = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("fullFilePath:`") + 1);
	t = t.substr(t.find("`") + 1);
	fullFilePath = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("md5Name:`") + 1);
	t = t.substr(t.find("`") + 1);
	md5Name = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);





	return t;


}




string SoundData::getTYPEIDString()
{ //===============================================================================================
	return "SOUND." + to_string(getID());
}


string& SoundData::getFileName()
{
	return fileName;
}


string& SoundData::getFullFilePath()
{
	return fullFilePath;
}


string& SoundData::getMD5Name()
{
	return md5Name;
}

void SoundData::setFileName(const string& s)
{
	fileName = s;
}

void SoundData::setFullFilePath(const string& s)
{
	fullFilePath = s;
}

void SoundData::setMD5Name(const string& s)
{
	md5Name = s;
}

