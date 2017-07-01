//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../../Engine/map/EntityData.h"


class DoorData : public EntityData
{
private:
	typedef EntityData super;



private:
	string destinationTYPEID = "";


	
	int arrivalXPixels1X = -1;
	
	int arrivalYPixels1X = -1;

	
	bool randomNPCSpawnPoint = false;
	
	float randomSpawnChance = 1.0f; //will distribute max randoms across spawn points based on chance.
	
	bool randomPointOfInterestOrExit = false;
	
	int randomSpawnDelay = 1000;
	
	bool randomSpawnKids = true;
	
	bool randomSpawnAdults = true;
	
	bool randomSpawnMales = true;
	
	bool randomSpawnFemales = true;


	//ONLY USED FOR EXPORT
	
	string destinationMapName = "";
	
	string destinationDoorName = "";


public:
	DoorData();


	DoorData(int id, const string& name, const string& spriteAssetName, int spawnXPixels1X, int spawnYPixels1X, const string& destinationTYPEID, int arrivalXPixels, int arrivalYPixels, bool randomNPCSpawnPoint, float randomSpawnChance, bool randomExitPoint, int randomSpawnDelay, bool randomSpawnKids, bool randomSpawnAdults, bool randomSpawnMales, bool randomSpawnFemales, EventData* eventData, const string& comment);


	DoorData(int id, const string& name);


	//static DoorData* fromBase64ZippedJSON(const string& b64);
	//static DoorData* fromJSON(const string& json);


	string& initFromString(string& t) override;


	string getTYPEIDString() override;


	string& getDestinationTYPEIDString();
	string& getDestinationMapName();
	string& getDestinationDoorName();

	int getArrivalXPixels1X();
	int getArrivalYPixels1X();
	float getArrivalXPixelsHQ();
	float getArrivalYPixelsHQ();

	bool getRandomNPCSpawnPoint();
	float getRandomSpawnChance();
	bool getRandomPointOfInterestOrExit();
	int getRandomSpawnDelay();
	bool getRandomSpawnKids();
	bool getRandomSpawnAdults();
	bool getRandomSpawnMales();
	bool getRandomSpawnFemales();


	void setDestinationTYPEIDString(const string& s);
	void setDestinationMapName(const string& s);
	void setDestinationDoorName(const string& s);

	void setRandomPointOfInterestOrExit(bool s);
	void setRandomNPCSpawnPoint(bool s);
	void setRandomSpawnChance(float s);
	void setRandomSpawnDelay(int s);
	void setRandomSpawnKids(bool s);
	void setRandomSpawnAdults(bool s);
	void setRandomSpawnMales(bool s);
	void setRandomSpawnFemales(bool s);


	void setArrivalXPixels1X(int s);
	void setArrivalYPixels1X(int s);
};

