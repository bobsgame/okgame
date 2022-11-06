//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

class DoorData;


class Door : public Entity
{
	//private DoorData data;

public:

	static Logger log;

	int doorknobX = 0;
	int doorknobY = 0;

private:
	bool open = false;
	bool stayOpen = false;


public:
	bool showActionIcon = true;


	Door(shared_ptr<Engine> g, shared_ptr<DoorData> doorAsset, shared_ptr<Map> m);


	bool isOpen();

	void setOpenManually(bool b);

	void setOpenAnimation(bool b);

	long long lastRequestedMapDataTime = 0;

	long long ticksSinceSpawnTry = 0;


	virtual void update() override;


	bool openingButtonHeld = false;


	void enter();


	void renderActionIcon();


	virtual void renderDebugBoxes() override;


	virtual void renderDebugInfo() override;


	virtual shared_ptr<EntityData> getData() override;//was return DoorData but covarient problem
	shared_ptr<DoorData> getDoorData();


	float arrivalXPixelsHQ();
	float arrivalYPixelsHQ();

	string& destinationTYPEIDString();

	string& destinationMapName();
	string& destinationDoorName();


	bool randomPointOfInterestOrExit();
	bool randomNPCSpawnPoint();
	float randomSpawnChance();
	int randomSpawnDelay();
	bool randomSpawnKids();
	bool randomSpawnAdults();
	bool randomSpawnMales();
	bool randomSpawnFemales();


	void setDestinationTYPEIDString(const string& typeID);

	void setRandomPointOfInterestOrExit(bool s);
	void setRandomNPCSpawnPoint(bool s);
	void setRandomSpawnChance(float s);
	void setRandomSpawnDelay(int s);
	void setRandomSpawnKids(bool s);
	void setRandomSpawnAdults(bool s);
	void setRandomSpawnMales(bool s);
	void setRandomSpawnFemales(bool s);


	void setArrivalXPixels(int s);
	void setArrivalYPixels(int s);
};

