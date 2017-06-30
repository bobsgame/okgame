//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapStateData : public AssetData
{

private:
	typedef AssetData super;




private:
	
	ArrayList<LightData*> lightDataList;

	
	ArrayList<EntityData*> entityDataList;

	//public ArrayList<EntityData> characterDataList = new ArrayList<EntityData>();

	
	ArrayList<AreaData*> areaDataList;


	
	int mapID = -1;


public:
	MapStateData();


	MapStateData(int id, const string& name);


	//static MapStateData* fromBase64ZippedJSON(const string& b64);
	//static MapStateData* fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();

	ArrayList<LightData*>* getLightDataList();
	ArrayList<EntityData*>* getEntityDataList();
	ArrayList<AreaData*>* getAreaDataList();


	int getMapID();

	void setMapID(int s);
};

