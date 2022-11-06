#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger MapState::log = Logger("MapState");


MapState::MapState(shared_ptr<MapStateData> mapStateData, shared_ptr<Map> m)
{ //=========================================================================================================================
	
	this->data = mapStateData;

	this->map = m;

	//lightByNameHashtable = make_shared<HashMap><string, shared_ptr<Light>>();
	//entityByNameHashtable = make_shared<HashMap><string, shared_ptr<Entity>>();
	//characterByNameHashtable = make_shared<HashMap><string, shared_ptr<Character>>();
	//areaByNameHashtable = make_shared<HashMap><string, shared_ptr<Area>>();
	//areaByTYPEIDHashtable = make_shared<HashMap><string, shared_ptr<Area>>();
}

shared_ptr<MapStateData> MapState::getData()
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

