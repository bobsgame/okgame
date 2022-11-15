//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class MapStateData : public AssetData
{

private:
	typedef AssetData super;




private:
	
	sp<vector<sp<LightData>>>lightDataList;

	
	sp<vector<sp<EntityData>>>entityDataList;

	//public sp<vector<EntityData>>characterDataList = ms<vector><EntityData>();

	
	sp<vector<sp<AreaData>>>areaDataList;


	
	int mapID = -1;


public:
	MapStateData();


	MapStateData(int id, const string& name);


	//static sp<MapStateData> fromBase64ZippedJSON(const string& b64);
	//static sp<MapStateData> fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();

	sp<vector<sp<LightData>>> getLightDataList();
	sp<vector<sp<EntityData>>> getEntityDataList();
	sp<vector<sp<AreaData>>> getAreaDataList();


	int getMapID();

	void setMapID(int s);
};

