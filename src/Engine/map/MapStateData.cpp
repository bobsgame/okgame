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

//shared_ptr<MapStateData> MapStateData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = make_shared<Gson>();
//	//MapStateData data = gson.fromJson(json,MapStateData.class);
//
//
//	return fromJSON(json);
//}
//
//shared_ptr<MapStateData> MapStateData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//shared_ptr<Gson> gson = make_shared<Gson>();
//	shared_ptr<MapStateData> data = nullptr;// gson->fromJson(json, MapStateData::typeid);
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

		shared_ptr<LightData>data = make_shared<LightData>();
		t = data->initFromString(t);
		lightDataList.add(data);
	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);


	t = t.substr(t.find("entityDataList:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (OKString::startsWith(t,"}") == false)
	{
		shared_ptr<EntityData>data = make_shared<EntityData>();
		t = data->initFromString(t);
		entityDataList.add(data);

	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);


	t = t.substr(t.find("areaDataList:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (OKString::startsWith(t,"}") == false)
	{
		shared_ptr<AreaData>data = make_shared<AreaData>();
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

ArrayList<shared_ptr<LightData>>* MapStateData::getLightDataList()
{
	return &lightDataList;
}

ArrayList<shared_ptr<EntityData>>* MapStateData::getEntityDataList()
{
	return &entityDataList;
}

ArrayList<shared_ptr<AreaData>>* MapStateData::getAreaDataList()
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

