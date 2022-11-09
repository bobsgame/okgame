#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



//Logger SkillData::log = Logger("SkillData");


SkillData::SkillData()
{ //=========================================================================================================================
}

SkillData::SkillData(int id, const string& name)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;
}
//
//sp<SkillData> SkillData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = ms<Gson>();
//	//SkillData data = gson.fromJson(json,SkillData.class);
//
//
//	return fromJSON(json);
//}
//
//sp<SkillData> SkillData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//sp<Gson> gson = ms<Gson>();
//	sp<SkillData> data = nullptr;// gson->fromJson(json, SkillData::typeid);
//
//
//	return data;
//}





string& SkillData::initFromString(string& t)
{
	t = super::initFromString(t);

	return t;
}




string SkillData::getTYPEIDString()
{ //===============================================================================================
	return "SKILL." + to_string(getID());
}

