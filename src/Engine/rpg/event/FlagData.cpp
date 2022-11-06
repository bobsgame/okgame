#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger FlagData::log = Logger("FlagData");


FlagData::FlagData()
{ //=========================================================================================================================
}

FlagData::FlagData(int id, const string& name)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;
}

//shared_ptr<FlagData> FlagData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = make_shared<Gson>();
//	//FlagData data = gson.fromJson(json,FlagData.class);
//
//	return fromJSON(json);
//}
//
//shared_ptr<FlagData> FlagData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//shared_ptr<Gson> gson = make_shared<Gson>();
//	shared_ptr<FlagData> data = nullptr;// gson->fromJson(json, FlagData::typeid);
//
//
//	return data;
//}



string& FlagData::initFromString(string& t)
{
	t = super::initFromString(t);

	return t;
}



string FlagData::getTYPEIDString()
{ //===============================================================================================
	return "FLAG." + to_string(getID());
}

