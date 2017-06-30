//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <src/Engine/rpg/event/EventData.h>
class Logger;




class SpriteData : public AssetData
{
private:
	typedef AssetData super;

	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------

private:
	
	string comment = "";

	
	string displayName = "";

	
	int widthPixels1X = 0;
	
	int heightPixels1X = 0;

	
	int frames = 1;

	
	bool isNPC = false; //not used for anything yet

	
	bool isKid = false;
	
	bool isAdult = false;
	
	bool isMale = false;
	
	bool isFemale = false;
	
	bool isCar = false;
	
	bool isAnimal = false;


	
	bool hasShadow = false;
	
	bool isRandom = false;


	//TODO: handle these
	
	bool isDoor = false;
	
	bool isGame = false;
	
	bool isItem = false;

	
	bool forceHQ2X = false;
	
	bool forceMD5Export = false;

	
	//int eventID = -1;
	
	string itemGameDescription = "";
	
	float gamePrice = 0.0f;


	
	int utilityOffsetXPixels1X = 0; //used for spawn point, doorknob marking, hands?
	
	int utilityOffsetYPixels1X = 0;


	
	string dataMD5 = "";
	
	string paletteMD5 = "";


	
	ArrayList<SpriteAnimationSequence*>* animationList = new ArrayList<SpriteAnimationSequence*>();

	EventData* eventData = nullptr;

public:

	SpriteData(int id = -1, const string& name = "none", const string& displayName = "", int widthPixels1X = 0, int heightPixels1X = 0, int frames = 1, bool isNPC = false, bool isKid = false, bool isAdult = false, bool isMale = false, bool isFemale = false, bool isCar = false, bool isAnimal = false, bool hasShadow = false, bool isRandom = false, bool isDoor = false, bool isGame = false, bool isItem = false, bool forceHQ2X = false, bool forceClientMD5Export = false, EventData* eventData = nullptr, const string& itemGameDescription = "", float gamePrice = 0, int utilityOffsetXPixels1X = 0, int utilityOffsetYPixels1X = 0, const string& dataMD5 = "", const string& paletteMD5 = "");


	void addAnimation(const string& frameSequenceName, int frameStart, int hitBoxOffsetLeft1X, int hitBoxOffsetRight1X, int hitBoxOffsetTop1X, int hitBoxOffsetBottom1X);


//	static SpriteData* fromBase64ZippedJSON(const string& b64);
//
//
//	static SpriteData* fromJSON(const string& json);
//
	//string toString();
	string& initFromString(string& t);


	string getTYPEIDString();


	string& getDisplayName();
	int getWidthPixels1X();
	int getHeightPixels1X();
//	int getWidthPixelsHQ();
//	int getHeightPixelsHQ();
	int getNumFrames();
	bool getIsNPC();
	bool getIsKid();
	bool getIsAdult();
	bool getIsMale();
	bool getIsFemale();
	bool getIsCar();
	bool getIsAnimal();
	bool getHasShadow();
	bool getIsRandom();
	bool getIsDoor();
	bool getIsGame();
	bool getIsItem();
	bool getForceHQ2X();
	EventData* getEventData();
	string& getItemGameDescription();
	float getGamePrice();
	int getUtilityOffsetXPixels1X();
	int getUtilityOffsetYPixels1X();
	int getUtilityOffsetXPixelsHQ();
	int getUtilityOffsetYPixelsHQ();
	string& getDataMD5();
	string& getPaletteMD5();
	ArrayList<SpriteAnimationSequence*>* getAnimationList();
	string& getComment();
	bool getForceMD5Export();


	void setComment(const string& s);
	void setWidthPixels1X(int s);
	void setHeightPixels1X(int s);
	void setFrames(int s);
	void setDisplayName(const string& s);
	void setIsNPC(bool s);
	void setIsKid(bool s);
	void setIsAdult(bool s);
	void setIsMale(bool s);
	void setIsFemale(bool s);
	void setIsCar(bool s);
	void setIsAnimal(bool s);
	void setHasShadow(bool s);
	void setIsRandom(bool s);
	void setIsDoor(bool s);
	void setIsGame(bool s);
	void setIsItem(bool s);
	void setForceHQ2X(bool s);
	void setForceMD5Export(bool s);
	//void setEventID(int s);
	void setItemGameDescription(const string& s);
	void setGamePrice(float s);
	void setUtilityOffsetXPixels1X(int s);
	void setUtilityOffsetYPixels1X(int s);
	void setDataMD5(const string& s);
	void setPaletteMD5(const string& s);
};

