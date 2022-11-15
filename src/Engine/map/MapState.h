//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class MapState
{
	//these hold the Light objects themselves, created in the constructor for this map.
	//these both hold the same thing for convenience.
public:
	sp<vector<sp<Light>>>lightList;
	HashMap<string, sp<Light>> lightByNameHashtable;//ms<HashMap><string, sp<Light>>();


	sp<vector<sp<Entity>>>entityList;
	HashMap<string, sp<Entity>> entityByNameHashtable;//ms<HashMap><string, sp<Entity>>();

	sp<vector<sp<Character>>>characterList;
	HashMap<string, sp<Character>> characterByNameHashtable;//ms<HashMap><string, sp<Character>>();


	sp<vector<sp<Area>>>areaList;
	HashMap<string, sp<Area>> areaByNameHashtable;//ms<HashMap><string, sp<Area>>();
	HashMap<string, sp<Area>> areaByTYPEIDHashtable;//ms<HashMap><string, sp<Area>>();



	sp<Map> map = nullptr;

private:
	sp<MapStateData> data = nullptr;


public:
	MapState(sp<MapStateData> mapStateData, sp<Map> m);


	sp<MapStateData> getData();

	int getID();
	string& getName();
};

