//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class AreaData : public AssetData
{
private:
	typedef AssetData super;

private:
	
	int mapXPixels1X = 0;
	int mapYPixels1X = 0;
	int widthPixels1X = 0;
	int heightPixels1X = 0;
	bool randomPointOfInterestOrExit = false;
	bool randomNPCSpawnPoint = false;
	int standSpawnDirection = -1;
	int waitHereTicks = 0; //see random stay here
	bool randomWaitTime = false;
	bool onlyOneAllowed = false;
	bool randomNPCStayHere = false; //for cars, audience//the reason there are BOTH stay here and wait here==-1 is that i might want a spawned NPC to walk away from a chair, but a new NPC come and sit down permanently. just a little more lively! :-) I don't know if i thought of this when i put them in, but i could presumably use it for that.
	float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	bool randomSpawnOnlyTryOnce = false; //one shot spawn chance for cars, audience
	bool randomSpawnOnlyOffscreen = false;
	int randomSpawnDelay = 1000;
	bool randomSpawnKids = true;
	bool randomSpawnAdults = true;
	bool randomSpawnMales = true;
	bool randomSpawnFemales = true;
	bool randomSpawnCars = false;

	//TODO: handle these
	bool autoPilot = false; //player will enable autopilot, show autopilot getCaption, follow connections
	bool playerFaceDirection = false; //for couches, chairs
	bool suckPlayerIntoMiddle = false; //for chairs
	//int eventID = -1;
	string comment = "";
	//int mapID = -1;
	//int stateID = -1;


	//can pull connections from sprites to areas and doors, should add these to points of interest list inside sprite.
	//automatically connect lines from all random points to any random spawn points, when click on random spawn point, should go to other spawn points as well
	ArrayList<string>* connectionTYPEIDList = new ArrayList<string>(); //should ALWAYS be by ID


	//warp area specific
	string destinationTYPEID = ""; //AREA.ID

	int arrivalXPixels1X = -1;
	int arrivalYPixels1X = -1;
	bool isWarpArea = false;


	//ONLY USED FOR EXPORT
	string destinationMapName = "";
	string destinationWarpAreaName = "";

	EventData* eventData = nullptr;

public:
	AreaData();


	AreaData(int id, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, const string& destinationTYPEID, int arrivalXPixels1X, int arrivalYPixels1X, bool randomPointOfInterestOrExit, bool randomNPCSpawnPoint, int standSpawnDirection, int waitHereTicks, bool randomWaitTime, bool onlyOneAllowed, bool randomNPCStayHere, float randomSpawnChance, bool randomSpawnOnlyTryOnce, bool randomSpawnOnlyOffscreen, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, bool randomSpawnCars, bool autoPilot, bool playerFaceDirection, bool suckPlayerIntoMiddle, EventData* eventData, const string& comment);


	AreaData(int id, const string& name);


	AreaData(int id, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, bool randomPointOfInterestOrExit, bool randomNPCSpawnPoint, int standSpawnDirection, int waitHereTicks, bool randomWaitTime, bool onlyOneAllowed, bool randomNPCStayHere, float randomSpawnChance, bool randomSpawnOnlyTryOnce, bool randomSpawnOnlyOffscreen, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, bool randomSpawnCars, bool autoPilot, bool playerFaceDirection, bool suckPlayerIntoMiddle, EventData* eventData, const string& comment);


	void addConnectionString(const string& s);


//	static AreaData* fromBase64ZippedJSON(const string& b64);
//
//
//	static AreaData* fromJSON(const string& json);


	string& initFromString(string& t);

	string getTYPEIDString();


	int getMapXPixels1X();
	int getMapYPixels1X();
	float getMapXPixelsHQ();
	float getMapYPixelsHQ();
	int getWidthPixels1X();
	int getHeightPixels1X();
	int getWidthPixelsHQ();
	int getHeightPixelsHQ();
	int getArrivalXPixels1X();
	int getArrivalYPixels1X();
	float getArrivalXPixelsHQ();
	float getArrivalYPixelsHQ();

	bool getIsWarpArea();
	bool getRandomPointOfInterestOrExit();
	bool getRandomNPCSpawnPoint();
	int getStandSpawnDirection();
	int getWaitHereTicks();
	bool getRandomWaitTime();
	bool getOnlyOneAllowed();
	bool getRandomNPCStayHere();
	float getRandomSpawnChance();
	bool getRandomSpawnOnlyTryOnce();
	bool getRandomSpawnOnlyOffscreen();
	int getRandomSpawnDelay();
	bool getRandomSpawnKids();
	bool getRandomSpawnAdults();
	bool getRandomSpawnMales();
	bool getRandomSpawnFemales();
	bool getRandomSpawnCars();
	bool getAutoPilot();
	bool getPlayerFaceDirection();
	bool getSuckPlayerIntoMiddle();
	EventData* getEventData();
	//public String stateName(){return data.stateName;}
	ArrayList<string>* getConnectionTYPEIDList();
	string& getComment();
	string& getDestinationTYPEIDString();
	string& getDestinationMapName();
	string& getDestinationWarpAreaName();
	//int getMapID();
	//int getStateID();


	void setDestinationMapName(const string& s);
	void setDestinationWarpAreaName(const string& s);
	void setDestinationTYPEIDString(const string& s);
	void setRandomPointOfInterestOrExit(bool s);
	void setRandomNPCSpawnPoint(bool s);
	void setStandSpawnDirection(int s);
	void setWaitHereTicks(int s);
	void setRandomWaitTime(bool s);
	void setOnlyOneAllowed(bool s);
	void setRandomNPCStayHere(bool s);
	void setRandomSpawnChance(float s);
	void setRandomSpawnOnlyTryOnce(bool s);
	void setRandomSpawnOnlyOffscreen(bool s);
	void setRandomSpawnDelay(int s);
	void setRandomSpawnKids(bool s);
	void setRandomSpawnAdults(bool s);
	void setRandomSpawnMales(bool s);
	void setRandomSpawnFemales(bool s);
	void setRandomSpawnCars(bool s);
	void setAutoPilot(bool s);
	void setPlayerFaceDirection(bool s);
	void setSuckPlayerIntoMiddle(bool s);
	void setIsWarpArea(bool s);
	//void setEventID(int s);
	void setComment(const string& s);
	void setMapXPixels1X(int s);
	void setMapYPixels1X(int s);
	void setArrivalXPixels1X(int s);
	void setArrivalYPixels1X(int s);
	void setWidthPixels1X(int s);
	void setHeightPixels1X(int s);
	//void setMapID(int s);
	//void setStateID(int s);
};

