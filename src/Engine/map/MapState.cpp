#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MapState::log = Logger("MapState");


MapState::MapState(sp<MapStateData> mapStateData, sp<Map> m)
{ //=========================================================================================================================
	
	this->data = mapStateData;

	this->map = m;

	//lightByNameHashtable = ms<HashMap><string, sp<Light>>();
	//entityByNameHashtable = ms<HashMap><string, sp<Entity>>();
	//characterByNameHashtable = ms<HashMap><string, sp<Character>>();
	//areaByNameHashtable = ms<HashMap><string, sp<Area>>();
	//areaByTYPEIDHashtable = ms<HashMap><string, sp<Area>>();
}

sp<MapStateData> MapState::getData()
{
	return data;
}

int MapState::getID()
{
	return getData()->getID();
}


string& MapState::getName()
{
	return getData()->getName();
}

