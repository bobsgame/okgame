#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger AudioData::log = Logger("AudioData");


AudioData::AudioData()
{ //=========================================================================================================================
}

AudioData::AudioData(int id, const string& name, const string& filename)
{ //=========================================================================================================================

  //AssetData(id, name);
	this->id = id;
	this->name = name;

	this->fileName = filename;
}
//
//AudioData* AudioData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = new Gson();
//	//AudioData data = gson.fromJson(json,AudioData.class);
//
//
//	return fromJSON(json);
//}
//
//AudioData* AudioData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//Gson* gson = new Gson();
//	AudioData* data = nullptr;// gson->fromJson(json, AudioData::typeid);
//
//
//	return data;
//}



string& AudioData::initFromString(string& t)
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

	if (String::startsWith(t, "preload:"))
	{
		t = t.substr(t.find("preload:`") + 1);
		t = t.substr(t.find("`") + 1);
		preload = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);
	}





	return t;


}



string& AudioData::getFileName()
{
	return fileName;
}


string& AudioData::getFullFilePath()
{
	return fullFilePath;
}


string& AudioData::getMD5Name()
{
	return md5Name;
}


bool AudioData::getPreload()
{
	return preload;
}


void AudioData::setFileName(const string& s)
{
	fileName = s;
}

void AudioData::setFullFilePath(const string& s)
{
	fullFilePath = s;
}

void AudioData::setMD5Name(const string& s)
{
	md5Name = s;
}

void AudioData::setPreload(bool s)
{
	preload = s;
}

