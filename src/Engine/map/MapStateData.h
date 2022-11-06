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
	
	ArrayList<shared_ptr<LightData>> lightDataList;

	
	ArrayList<shared_ptr<EntityData>> entityDataList;

	//public ArrayList<EntityData> characterDataList = make_shared<ArrayList><EntityData>();

	
	ArrayList<shared_ptr<AreaData>> areaDataList;


	
	int mapID = -1;


public:
	MapStateData();


	MapStateData(int id, const string& name);


	//static shared_ptr<MapStateData> fromBase64ZippedJSON(const string& b64);
	//static shared_ptr<MapStateData> fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();

	ArrayList<shared_ptr<LightData>>* getLightDataList();
	ArrayList<shared_ptr<EntityData>>* getEntityDataList();
	ArrayList<shared_ptr<AreaData>>* getAreaDataList();


	int getMapID();

	void setMapID(int s);
};

