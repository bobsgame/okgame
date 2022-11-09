#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger DialogueData::log = Logger("DialogueData");


DialogueData::DialogueData()
{ //=========================================================================================================================
}

DialogueData::DialogueData(int id, const string& name, const string& caption, const string& comment, const string& text)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->caption = caption;
	this->comment = comment;
	this->text = text;
}

//sp<DialogueData> DialogueData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = ms<Gson>();
//	//DialogueData data = gson.fromJson(json,DialogueData.class);
//
//	return fromJSON(json);
//}
//
//sp<DialogueData> DialogueData::fromJSON(const string& json)
//{ //===============================================================================================
//
//	// sp<Gson> gson = ms<Gson>();
//	sp<DialogueData> data = nullptr;// gson->fromJson(json, DialogueData::typeid);
//
//
//	return data;
//}




string& DialogueData::initFromString(string& t)
{
	t = super::initFromString(t);


	t = t.substr(t.find("caption:`") + 1);
	t = t.substr(t.find("`") + 1);
	caption = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("comment:`") + 1);
	t = t.substr(t.find("`") + 1);
	comment = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("text:`") + 1);
	t = t.substr(t.find("`") + 1);
	text = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);


	return t;
}




string DialogueData::getTYPEIDString()
{ //===============================================================================================
	return "DIALOGUE." + to_string(getID());
}


string& DialogueData::getCaption()
{
	return caption;
}


string& DialogueData::getComment()
{
	return comment;
}


string& DialogueData::getText()
{
	return text;
}

void DialogueData::setCaption(const string& s)
{
	this->caption = s;
}

void DialogueData::setComment(const string& s)
{
	this->comment = s;
}

void DialogueData::setText(const string& s)
{
	this->text = s;
}

