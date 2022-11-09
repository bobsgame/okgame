#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MapStateData::log = Logger("MapStateData");


MapStateData::MapStateData()
{ //=========================================================================================================================
}

MapStateData::MapStateData(int id, const string& name)
{ //===============================================================================================
	AssetData(id, name);
}

//sp<MapStateData> MapStateData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = ms<Gson>();
//	//MapStateData data = gson.fromJson(json,MapStateData.class);
//
//
//	return fromJSON(json);
//}
//
//sp<MapStateData> MapStateData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//sp<Gson> gson = ms<Gson>();
//	sp<MapStateData> data = nullptr;// gson->fromJson(json, MapStateData::typeid);
//
//
//	return data;
//}



string& MapStateData::initFromString(string& t)
{
	t = super::initFromString(t);


	t = t.substr(t.find("mapID:`") + 1);
	t = t.substr(t.find("`") + 1);
	mapID = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);



	t = t.substr(t.find("lightDataList:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (OKString::startsWith(t,"}") == false)
	{

		sp<LightData>data = ms<LightData>();
		t = data->initFromString(t);
		lightDataList.add(data);
	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);


	t = t.substr(t.find("entityDataList:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (OKString::startsWith(t,"}") == false)
	{
		sp<EntityData>data = ms<EntityData>();
		t = data->initFromString(t);
		entityDataList.add(data);

	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);


	t = t.substr(t.find("areaDataList:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (OKString::startsWith(t,"}") == false)
	{
		sp<AreaData>data = ms<AreaData>();
		t = data->initFromString(t);
		areaDataList.add(data);

	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);


	return t;


}



string MapStateData::getTYPEIDString()
{ //===============================================================================================
	return "STATE." + to_string(getID());
}

sp<vector<sp<LightData>>> MapStateData::getLightDataList()
{
	return &lightDataList;
}

sp<vector<sp<EntityData>>> MapStateData::getEntityDataList()
{
	return &entityDataList;
}

sp<vector<sp<AreaData>>> MapStateData::getAreaDataList()
{
	return &areaDataList;
}

int MapStateData::getMapID()
{
	return mapID;
}

void MapStateData::setMapID(int s)
{
	mapID = s;
}

