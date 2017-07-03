#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger AreaData::log = Logger("AreaData");


AreaData::AreaData()
{ //=========================================================================================================================
}

AreaData::AreaData
(
	int id,
	const string& name,
	int mapXPixels1X,
	int mapYPixels1X,
	int widthPixels1X,
	int heightPixels1X,
	const string& destinationTYPEID,
	int arrivalXPixels1X,
	int arrivalYPixels1X,
	bool randomPointOfInterestOrExit,
	bool randomNPCSpawnPoint,
	int standSpawnDirection,
	int waitHereTicks,
	bool randomWaitTime,
	bool onlyOneAllowed,
	bool randomNPCStayHere,
	float randomSpawnChance,
	bool randomSpawnOnlyTryOnce,
	bool randomSpawnOnlyOffscreen,
	int randomSpawnDelay,
	bool randomSpawnKids,
	bool randomSpawnAdults,
	bool randomSpawnMales,
	bool randomSpawnFemales,
	bool randomSpawnCars,
	bool autoPilot,
	bool playerFaceDirection,
	bool suckPlayerIntoMiddle,
	EventData* eventData,
	const string& comment
)
{ //=========================================================================================================================

	AssetData(id, name);
	this->mapXPixels1X = mapXPixels1X;
	this->mapYPixels1X = mapYPixels1X;
	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;
	this->randomPointOfInterestOrExit = randomPointOfInterestOrExit;
	this->randomNPCSpawnPoint = randomNPCSpawnPoint;
	this->standSpawnDirection = standSpawnDirection;
	this->waitHereTicks = waitHereTicks;
	this->randomWaitTime = randomWaitTime;
	this->onlyOneAllowed = onlyOneAllowed;
	this->randomNPCStayHere = randomNPCStayHere;
	this->randomSpawnChance = randomSpawnChance;
	this->randomSpawnOnlyTryOnce = randomSpawnOnlyTryOnce;
	this->randomSpawnOnlyOffscreen = randomSpawnOnlyOffscreen;
	this->randomSpawnDelay = randomSpawnDelay;
	this->randomSpawnKids = randomSpawnKids;
	this->randomSpawnAdults = randomSpawnAdults;
	this->randomSpawnMales = randomSpawnMales;
	this->randomSpawnFemales = randomSpawnFemales;
	this->randomSpawnCars = randomSpawnCars;
	this->autoPilot = autoPilot;
	this->playerFaceDirection = playerFaceDirection;
	this->suckPlayerIntoMiddle = suckPlayerIntoMiddle;
	this->eventData = eventData;


	this->destinationTYPEID = destinationTYPEID;
	this->arrivalXPixels1X = arrivalXPixels1X;
	this->arrivalYPixels1X = arrivalYPixels1X;
	isWarpArea = true;
}

AreaData::AreaData(int id, const string& name)
{ //=========================================================================================================================
	AssetData(id, name);
}

AreaData::AreaData
(
	int id,
	const string& name,
	int mapXPixels1X,
	int mapYPixels1X,
	int widthPixels1X,
	int heightPixels1X,
	bool randomPointOfInterestOrExit,
	bool randomNPCSpawnPoint,
	int standSpawnDirection,
	int waitHereTicks,
	bool randomWaitTime,
	bool onlyOneAllowed,
	bool randomNPCStayHere,
	float randomSpawnChance,
	bool randomSpawnOnlyTryOnce,
	bool randomSpawnOnlyOffscreen,
	int randomSpawnDelay,
	bool randomSpawnKids,
	bool randomSpawnAdults,
	bool randomSpawnMales,
	bool randomSpawnFemales,
	bool randomSpawnCars,
	bool autoPilot,
	bool playerFaceDirection,
	bool suckPlayerIntoMiddle,
	EventData* eventData,
	const string& comment
)
{ //=========================================================================================================================


	AssetData(id, name);


	this->mapXPixels1X = mapXPixels1X;
	this->mapYPixels1X = mapYPixels1X;
	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;
	this->randomPointOfInterestOrExit = randomPointOfInterestOrExit;
	this->randomNPCSpawnPoint = randomNPCSpawnPoint;
	this->standSpawnDirection = standSpawnDirection;
	this->waitHereTicks = waitHereTicks;
	this->randomWaitTime = randomWaitTime;
	this->onlyOneAllowed = onlyOneAllowed;
	this->randomNPCStayHere = randomNPCStayHere;
	this->randomSpawnChance = randomSpawnChance;
	this->randomSpawnOnlyTryOnce = randomSpawnOnlyTryOnce;
	this->randomSpawnOnlyOffscreen = randomSpawnOnlyOffscreen;
	this->randomSpawnDelay = randomSpawnDelay;
	this->randomSpawnKids = randomSpawnKids;
	this->randomSpawnAdults = randomSpawnAdults;
	this->randomSpawnMales = randomSpawnMales;
	this->randomSpawnFemales = randomSpawnFemales;
	this->randomSpawnCars = randomSpawnCars;
	this->autoPilot = autoPilot;
	this->playerFaceDirection = playerFaceDirection;
	this->suckPlayerIntoMiddle = suckPlayerIntoMiddle;
	this->eventData = eventData;
}

void AreaData::addConnectionString(const string& s)
{ //=========================================================================================================================
	connectionTYPEIDList->add(s);
}

//AreaData* AreaData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = new Gson();
//	//AreaData data = gson.fromJson(json,AreaData.class);
//
//
//	return fromJSON(json);
//}
//
//AreaData* AreaData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//Gson* gson = new Gson();
//	AreaData* data = nullptr;// gson->fromJson(json, AreaData::typeid);
//
//
//	return data;
//}




////===============================================================================================
//string toString()
//{//===============================================================================================
//
//	string s = "";
//
//	s = super.toString();
//
//	while (comment.contains("`"))
//	{
//		string front = comment.substr(0, comment.find("`"));
//		string back = comment.substr(comment.find("`") + 1);
//		comment = front + back;
//	}
//
//	while (destinationTYPEID.contains("`"))
//	{
//		string front = destinationTYPEID.substr(0, destinationTYPEID.find("`"));
//		string back = destinationTYPEID.substr(destinationTYPEID.find("`") + 1);
//		destinationTYPEID = front + back;
//	}
//
//	while (destinationMapName.contains("`"))
//	{
//		string front = destinationMapName.substr(0, destinationMapName.find("`"));
//		string back = destinationMapName.substr(destinationMapName.find("`") + 1);
//		destinationMapName = front + back;
//	}
//
//	while (destinationWarpAreaName.contains("`"))
//	{
//		string front = destinationWarpAreaName.substr(0, destinationWarpAreaName.find("`"));
//		string back = destinationWarpAreaName.substr(destinationWarpAreaName.find("`") + 1);
//		destinationWarpAreaName = front + back;
//	}
//
//
//
//	for (int i = 0; i<connectionTYPEIDList.size(); i++)
//	{
//
//		string t = connectionTYPEIDList.get(i);
//
//		while (t.contains("`"))
//		{
//			string front = t.substr(0, t.find("`"));
//			string back = t.substr(t.find("`") + 1);
//			t = front + back;
//		}
//		connectionTYPEIDList.remove(i);
//		connectionTYPEIDList.add(i, t);
//
//	}
//
//
//	s += "mapXPixels1X:`" + mapXPixels1X + "`,";
//	s += "mapYPixels1X:`" + mapYPixels1X + "`,";
//	s += "widthPixels1X:`" + widthPixels1X + "`,";
//	s += "heightPixels1X:`" + heightPixels1X + "`,";
//	s += "randomPointOfInterestOrExit:`" + randomPointOfInterestOrExit + "`,";
//	s += "randomNPCSpawnPoint:`" + randomNPCSpawnPoint + "`,";
//	s += "standSpawnDirection:`" + standSpawnDirection + "`,";
//	s += "waitHereTicks:`" + waitHereTicks + "`,";
//	s += "randomWaitTime:`" + randomWaitTime + "`,";
//	s += "onlyOneAllowed:`" + onlyOneAllowed + "`,";
//	s += "randomNPCStayHere:`" + randomNPCStayHere + "`,";
//	s += "randomSpawnChance:`" + randomSpawnChance + "`,";
//	s += "randomSpawnOnlyTryOnce:`" + randomSpawnOnlyTryOnce + "`,";
//	s += "randomSpawnOnlyOffscreen:`" + randomSpawnOnlyOffscreen + "`,";
//	s += "randomSpawnDelay:`" + randomSpawnDelay + "`,";
//	s += "randomSpawnKids:`" + randomSpawnKids + "`,";
//	s += "randomSpawnAdults:`" + randomSpawnAdults + "`,";
//	s += "randomSpawnMales:`" + randomSpawnMales + "`,";
//	s += "randomSpawnFemales:`" + randomSpawnFemales + "`,";
//	s += "randomSpawnCars:`" + randomSpawnCars + "`,";
//	s += "autoPilot:`" + autoPilot + "`,";
//	s += "playerFaceDirection:`" + playerFaceDirection + "`,";
//	s += "suckPlayerIntoMiddle:`" + suckPlayerIntoMiddle + "`,";
//	s += "eventID:`" + eventID + "`,";
//	s += "comment:`" + comment + "`,";
//	s += "mapID:`" + mapID + "`,";
//	s += "stateID:`" + stateID + "`,";
//	for (int i = 0; i<connectionTYPEIDList.size(); i++)
//	{
//		s += "connectionTYPEIDList:`" + connectionTYPEIDList.get(i) + "`,";
//	}
//	s += "destinationTYPEID:`" + destinationTYPEID + "`,";
//	s += "arrivalXPixels1X:`" + arrivalXPixels1X + "`,";
//	s += "arrivalYPixels1X:`" + arrivalYPixels1X + "`,";
//	s += "isWarpArea:`" + isWarpArea + "`,";
//	s += "destinationMapName:`" + destinationMapName + "`,";
//	s += "destinationWarpAreaName:`" + destinationWarpAreaName + "`,";
//
//
//
//	return s;
//}





string& AreaData::initFromString(string& t)
{
	t = super::initFromString(t);


	t = t.substr(t.find("mapXPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	mapXPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("mapYPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	mapYPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("widthPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	widthPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("heightPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	heightPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomPointOfInterestOrExit:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomPointOfInterestOrExit = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomNPCSpawnPoint:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomNPCSpawnPoint = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("standSpawnDirection:`") + 1);
	t = t.substr(t.find("`") + 1);
	standSpawnDirection = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("waitHereTicks:`") + 1);
	t = t.substr(t.find("`") + 1);
	waitHereTicks = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomWaitTime:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomWaitTime = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("onlyOneAllowed:`") + 1);
	t = t.substr(t.find("`") + 1);
	onlyOneAllowed = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomNPCStayHere:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomNPCStayHere = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnChance:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnChance = stof(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnOnlyTryOnce:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnOnlyTryOnce = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnOnlyOffscreen:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnOnlyOffscreen = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnDelay:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnDelay = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnKids:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnKids = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnAdults:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnAdults = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnMales:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnMales = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnFemales:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnFemales = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("randomSpawnCars:`") + 1);
	t = t.substr(t.find("`") + 1);
	randomSpawnCars = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("autoPilot:`") + 1);
	t = t.substr(t.find("`") + 1);
	autoPilot = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("playerFaceDirection:`") + 1);
	t = t.substr(t.find("`") + 1);
	playerFaceDirection = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("suckPlayerIntoMiddle:`") + 1);
	t = t.substr(t.find("`") + 1);
	suckPlayerIntoMiddle = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

//	t = t.substr(t.find("eventID:`") + 1);
//	t = t.substr(t.find("`") + 1);
//	eventID = stoi(t.substr(0, t.find("`")));
//	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("comment:`") + 1);
	t = t.substr(t.find("`") + 1);
	comment = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

//	t = t.substr(t.find("mapID:`") + 1);
//	t = t.substr(t.find("`") + 1);
//	mapID = stoi(t.substr(0, t.find("`")));
//	t = t.substr(t.find("`,") + 2);
//
//	t = t.substr(t.find("stateID:`") + 1);
//	t = t.substr(t.find("`") + 1);
//	stateID = stoi(t.substr(0, t.find("`")));
//	t = t.substr(t.find("`,") + 2);

	while(String::startsWith(t,"connectionTYPEIDList:`"))
	{
		t = t.substr(t.find("connectionTYPEIDList:`") + 1);
		t = t.substr(t.find("`") + 1);
		connectionTYPEIDList->add(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);
	}

	t = t.substr(t.find("destinationTYPEID:`") + 1);
	t = t.substr(t.find("`") + 1);
	destinationTYPEID = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("arrivalXPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	arrivalXPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("arrivalYPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	arrivalYPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isWarpArea:`") + 1);
	t = t.substr(t.find("`") + 1);
	isWarpArea = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("destinationMapName:`") + 1);
	t = t.substr(t.find("`") + 1);
	destinationMapName = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("destinationWarpAreaName:`") + 1);
	t = t.substr(t.find("`") + 1);
	destinationWarpAreaName = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);


	t = t.substr(t.find("eventData:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (String::startsWith(t,"}") == false)
	{
		EventData* data = new EventData();
		t = data->initFromString(t);
		eventData = data;
	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);

	return t;
}




string AreaData::getTYPEIDString()
{ //===============================================================================================

	if (isWarpArea == true)
	{
		return "AREA." + to_string(getID());
	}
	return "AREA." + to_string(getID());
}

int AreaData::getMapXPixels1X()
{
	return mapXPixels1X;
}

int AreaData::getMapYPixels1X()
{
	return mapYPixels1X;
}

float AreaData::getMapXPixelsHQ()
{
	return (float)mapXPixels1X * 2;
}

float AreaData::getMapYPixelsHQ()
{
	return (float)mapYPixels1X * 2;
}

int AreaData::getWidthPixels1X()
{
	return widthPixels1X;
}

int AreaData::getHeightPixels1X()
{
	return heightPixels1X;
}

int AreaData::getWidthPixelsHQ()
{
	return widthPixels1X * 2;
}

int AreaData::getHeightPixelsHQ()
{
	return heightPixels1X * 2;
}

int AreaData::getArrivalXPixels1X()
{
	return arrivalXPixels1X;
}

int AreaData::getArrivalYPixels1X()
{
	return arrivalYPixels1X;
}

float AreaData::getArrivalXPixelsHQ()
{
	return (float)arrivalXPixels1X * 2;
}

float AreaData::getArrivalYPixelsHQ()
{
	return (float)arrivalYPixels1X * 2;
}

bool AreaData::getIsWarpArea()
{
	return isWarpArea;
}

bool AreaData::getRandomPointOfInterestOrExit()
{
	return randomPointOfInterestOrExit;
}

bool AreaData::getRandomNPCSpawnPoint()
{
	return randomNPCSpawnPoint;
}

int AreaData::getStandSpawnDirection()
{
	return standSpawnDirection;
}

int AreaData::getWaitHereTicks()
{
	return waitHereTicks;
}

bool AreaData::getRandomWaitTime()
{
	return randomWaitTime;
}

bool AreaData::getOnlyOneAllowed()
{
	return onlyOneAllowed;
}

bool AreaData::getRandomNPCStayHere()
{
	return randomNPCStayHere;
}

float AreaData::getRandomSpawnChance()
{
	return randomSpawnChance;
}

bool AreaData::getRandomSpawnOnlyTryOnce()
{
	return randomSpawnOnlyTryOnce;
}

bool AreaData::getRandomSpawnOnlyOffscreen()
{
	return randomSpawnOnlyOffscreen;
}

int AreaData::getRandomSpawnDelay()
{
	return randomSpawnDelay;
}

bool AreaData::getRandomSpawnKids()
{
	return randomSpawnKids;
}

bool AreaData::getRandomSpawnAdults()
{
	return randomSpawnAdults;
}

bool AreaData::getRandomSpawnMales()
{
	return randomSpawnMales;
}

bool AreaData::getRandomSpawnFemales()
{
	return randomSpawnFemales;
}

bool AreaData::getRandomSpawnCars()
{
	return randomSpawnCars;
}

bool AreaData::getAutoPilot()
{
	return autoPilot;
}

bool AreaData::getPlayerFaceDirection()
{
	return playerFaceDirection;
}

bool AreaData::getSuckPlayerIntoMiddle()
{
	return suckPlayerIntoMiddle;
}

EventData* AreaData::getEventData()
{
	return eventData;
}

ArrayList<string>* AreaData::getConnectionTYPEIDList()
{
	return connectionTYPEIDList;
}


string& AreaData::getComment()
{
	return comment;
}


string& AreaData::getDestinationTYPEIDString()
{
	return destinationTYPEID;
}


string& AreaData::getDestinationMapName()
{
	return destinationMapName;
}


string& AreaData::getDestinationWarpAreaName()
{
	return destinationWarpAreaName;
}

//int AreaData::getMapID()
//{
//	return mapID;
//}
//
//int AreaData::getStateID()
//{
//	return stateID;
//}

void AreaData::setDestinationMapName(const string& s)
{
	destinationMapName = s;
}

void AreaData::setDestinationWarpAreaName(const string& s)
{
	destinationWarpAreaName = s;
}

void AreaData::setDestinationTYPEIDString(const string& s)
{
	destinationTYPEID = s;
}

void AreaData::setRandomPointOfInterestOrExit(bool s)
{
	randomPointOfInterestOrExit = s;
}

void AreaData::setRandomNPCSpawnPoint(bool s)
{
	randomNPCSpawnPoint = s;
}

void AreaData::setStandSpawnDirection(int s)
{
	standSpawnDirection = s;
}

void AreaData::setWaitHereTicks(int s)
{
	waitHereTicks = s;
}

void AreaData::setRandomWaitTime(bool s)
{
	randomWaitTime = s;
}

void AreaData::setOnlyOneAllowed(bool s)
{
	onlyOneAllowed = s;
}

void AreaData::setRandomNPCStayHere(bool s)
{
	randomNPCStayHere = s;
}

void AreaData::setRandomSpawnChance(float s)
{
	randomSpawnChance = s;
}

void AreaData::setRandomSpawnOnlyTryOnce(bool s)
{
	randomSpawnOnlyTryOnce = s;
}

void AreaData::setRandomSpawnOnlyOffscreen(bool s)
{
	randomSpawnOnlyOffscreen = s;
}

void AreaData::setRandomSpawnDelay(int s)
{
	randomSpawnDelay = s;
}

void AreaData::setRandomSpawnKids(bool s)
{
	randomSpawnKids = s;
}

void AreaData::setRandomSpawnAdults(bool s)
{
	randomSpawnAdults = s;
}

void AreaData::setRandomSpawnMales(bool s)
{
	randomSpawnMales = s;
}

void AreaData::setRandomSpawnFemales(bool s)
{
	randomSpawnFemales = s;
}

void AreaData::setRandomSpawnCars(bool s)
{
	randomSpawnCars = s;
}

void AreaData::setAutoPilot(bool s)
{
	autoPilot = s;
}

void AreaData::setPlayerFaceDirection(bool s)
{
	playerFaceDirection = s;
}

void AreaData::setSuckPlayerIntoMiddle(bool s)
{
	suckPlayerIntoMiddle = s;
}

void AreaData::setIsWarpArea(bool s)
{
	isWarpArea = s;
}

//void AreaData::setEventID(int s)
//{
//	eventID = s;
//}

void AreaData::setComment(const string& s)
{
	comment = s;
}

void AreaData::setMapXPixels1X(int s)
{
	mapXPixels1X = s;
}

void AreaData::setMapYPixels1X(int s)
{
	mapYPixels1X = s;
}

void AreaData::setArrivalXPixels1X(int s)
{
	arrivalXPixels1X = s;
}

void AreaData::setArrivalYPixels1X(int s)
{
	arrivalYPixels1X = s;
}

void AreaData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void AreaData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

//void AreaData::setMapID(int s)
//{
//	mapID = s;
//}
//
//void AreaData::setStateID(int s)
//{
//	stateID = s;
//}

