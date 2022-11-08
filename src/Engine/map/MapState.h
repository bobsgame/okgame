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
	vector<shared_ptr<Light>> lightList;
	HashMap<string, shared_ptr<Light>> lightByNameHashtable;//make_shared<HashMap><string, shared_ptr<Light>>();


	vector<shared_ptr<Entity>> entityList;
	HashMap<string, shared_ptr<Entity>> entityByNameHashtable;//make_shared<HashMap><string, shared_ptr<Entity>>();

	vector<shared_ptr<Character>> characterList;
	HashMap<string, shared_ptr<Character>> characterByNameHashtable;//make_shared<HashMap><string, shared_ptr<Character>>();


	vector<shared_ptr<Area>> areaList;
	HashMap<string, shared_ptr<Area>> areaByNameHashtable;//make_shared<HashMap><string, shared_ptr<Area>>();
	HashMap<string, shared_ptr<Area>> areaByTYPEIDHashtable;//make_shared<HashMap><string, shared_ptr<Area>>();



	shared_ptr<Map> map = nullptr;

private:
	shared_ptr<MapStateData> data = nullptr;


public:
	MapState(shared_ptr<MapStateData> mapStateData, shared_ptr<Map> m);


	shared_ptr<MapStateData> getData();

	int getID();
	string& getName();
};

