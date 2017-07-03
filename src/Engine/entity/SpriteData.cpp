#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



//Logger SpriteData::log = Logger("SpriteData");


SpriteData::SpriteData
(
	int id,
	const string& name,
	const string& displayName,
	int widthPixels1X,
	int heightPixels1X,
	int frames,
	bool isNPC,// = false, 
	bool isKid,// = false, 
	bool isAdult,// = false, 
	bool isMale,// = false, 
	bool isFemale,// = false, 
	bool isCar,// = false, 
	bool isAnimal,// = false, 
	bool hasShadow,// = false, 
	bool isRandom,// = false, 
	bool isDoor,// = false, 
	bool isGame,// = false, 
	bool isItem,// = false, 
	bool forceHQ2X,// = false, 
	bool forceClientMD5Export,// = false, 
	EventData* eventData,// = -1, 
	const string& itemGameDescription,// = "",
	float gamePrice,// = 0, 
	int utilityOffsetXPixels1X,// = 0, 
	int utilityOffsetYPixels1X,// = 0, 
	const string& dataMD5,// = "",
	const string& paletteMD5// = ""
)
{ //=========================================================================================================================


	//AssetData(id, name);
	this->id = id;
	this->name = name;


	this->displayName = displayName;

	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;


	this->frames = frames;

	this->isNPC = isNPC;

	this->isKid = isKid;
	this->isAdult = isAdult;
	this->isMale = isMale;
	this->isFemale = isFemale;
	this->isCar = isCar;
	this->isAnimal = isAnimal;

	this->hasShadow = hasShadow;
	this->isRandom = isRandom;

	this->isDoor = isDoor;
	this->isGame = isGame;
	this->isItem = isItem;

	this->forceHQ2X = forceHQ2X;
	this->forceMD5Export = forceClientMD5Export;

	this->eventData = eventData;
	this->itemGameDescription = itemGameDescription;
	this->gamePrice = gamePrice;

	this->utilityOffsetXPixels1X = utilityOffsetXPixels1X;
	this->utilityOffsetYPixels1X = utilityOffsetYPixels1X;

	this->dataMD5 = dataMD5;
	this->paletteMD5 = paletteMD5;
}


void SpriteData::addAnimation(const string& frameSequenceName, int frameStart, int hitBoxOffsetLeft1X, int hitBoxOffsetRight1X, int hitBoxOffsetTop1X, int hitBoxOffsetBottom1X)
{ //=========================================================================================================================
	animationList->add(new SpriteAnimationSequence(frameSequenceName, frameStart, hitBoxOffsetLeft1X, hitBoxOffsetRight1X, hitBoxOffsetTop1X, hitBoxOffsetBottom1X));
}

//SpriteData* SpriteData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//	//string decode64 = FileUtils::decodeBase64String(b64);
//	string json = "";// FileUtils::unzipBase64StringToString(decode64);
//
//
//	return fromJSON(json);
//}
//
//SpriteData* SpriteData::fromJSON(const string& json)
//{ //===============================================================================================
//
//	//Gson* gson = new Gson();
//	SpriteData* data = nullptr;// gson->fromJson(json, SpriteData::typeid);
//
//
//	return data;
//}




//
////===============================================================================================
//string SpriteData::toString()
//{//===============================================================================================
//
//	string s = "";
//
//	s = super::toString();
//
//
//	s += "comment:`" + comment + "`,";
//	s += "displayName:`" + displayName + "`,";
//	s += "widthPixels1X:`" + widthPixels1X + "`,";
//	s += "heightPixels1X:`" + heightPixels1X + "`,";
//	s += "frames:`" + frames + "`,";
//	s += "isNPC:`" + isNPC + "`,";
//	s += "isKid:`" + isKid + "`,";
//	s += "isAdult:`" + isAdult + "`,";
//	s += "isMale:`" + isMale + "`,";
//	s += "isFemale:`" + isFemale + "`,";
//	s += "isCar:`" + isCar + "`,";
//	s += "isAnimal:`" + isAnimal + "`,";
//	s += "hasShadow:`" + hasShadow + "`,";
//	s += "isRandom:`" + isRandom + "`,";
//	s += "isDoor:`" + isDoor + "`,";
//	s += "isGame:`" + isGame + "`,";
//	s += "isItem:`" + isItem + "`,";
//	s += "forceHQ2X:`" + forceHQ2X + "`,";
//	s += "forceMD5Export:`" + forceMD5Export + "`,";
//	s += "eventID:`" + eventID + "`,";
//	s += "itemGameDescription:`" + itemGameDescription + "`,";
//	s += "gamePrice:`" + gamePrice + "`,";
//	s += "utilityOffsetXPixels1X:`" + utilityOffsetXPixels1X + "`,";
//	s += "utilityOffsetYPixels1X:`" + utilityOffsetYPixels1X + "`,";
//	s += "dataMD5:`" + dataMD5 + "`,";
//	s += "paletteMD5:`" + paletteMD5 + "`,";
//	for (int i = 0; i<animationList->size(); i++)
//	{
//
//		s += "animationList:";
//		s += "frameSequenceName:`" + animationList->get(i)->frameSequenceName + "`,";
//		s += "frameStart:`" + animationList->get(i)->frameStart + "`,";
//		s += "hitBoxFromLeftPixels1X:`" + animationList->get(i)->hitBoxFromLeftPixels1X + "`,";
//		s += "hitBoxFromRightPixels1X:`" + animationList->get(i)->hitBoxFromRightPixels1X + "`,";
//		s += "hitBoxFromTopPixels1X:`" + animationList->get(i)->hitBoxFromTopPixels1X + "`,";
//		s += "hitBoxFromBottomPixels1X:`" + animationList->get(i)->hitBoxFromBottomPixels1X + "`,";
//	}
//
//
//
//	return s;
//}





string& SpriteData::initFromString(string& t)
{
	t = super::initFromString(t);



	t = t.substr(t.find("comment:`") + 1);
	t = t.substr(t.find("`") + 1);
	comment = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("displayName:`") + 1);
	t = t.substr(t.find("`") + 1);
	displayName = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("widthPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	widthPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("heightPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	heightPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("frames:`") + 1);
	t = t.substr(t.find("`") + 1);
	frames = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isNPC:`") + 1);
	t = t.substr(t.find("`") + 1);
	isNPC = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isKid:`") + 1);
	t = t.substr(t.find("`") + 1);
	isKid = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isAdult:`") + 1);
	t = t.substr(t.find("`") + 1);
	isAdult = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isMale:`") + 1);
	t = t.substr(t.find("`") + 1);
	isMale = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isFemale:`") + 1);
	t = t.substr(t.find("`") + 1);
	isFemale = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isCar:`") + 1);
	t = t.substr(t.find("`") + 1);
	isCar = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isAnimal:`") + 1);
	t = t.substr(t.find("`") + 1);
	isAnimal = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("hasShadow:`") + 1);
	t = t.substr(t.find("`") + 1);
	hasShadow = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isRandom:`") + 1);
	t = t.substr(t.find("`") + 1);
	isRandom = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isDoor:`") + 1);
	t = t.substr(t.find("`") + 1);
	isDoor = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isGame:`") + 1);
	t = t.substr(t.find("`") + 1);
	isGame = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isItem:`") + 1);
	t = t.substr(t.find("`") + 1);
	isItem = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("forceHQ2X:`") + 1);
	t = t.substr(t.find("`") + 1);
	forceHQ2X = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("forceMD5Export:`") + 1);
	t = t.substr(t.find("`") + 1);
	forceMD5Export = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);
//
//	t = t.substr(t.find("eventID:`") + 1);
//	t = t.substr(t.find("`") + 1);
//	eventID = stoi(t.substr(0, t.find("`")));
//	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("itemGameDescription:`") + 1);
	t = t.substr(t.find("`") + 1);
	itemGameDescription = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("gamePrice:`") + 1);
	t = t.substr(t.find("`") + 1);
	gamePrice = stof(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("utilityOffsetXPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	utilityOffsetXPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("utilityOffsetYPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	utilityOffsetYPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("dataMD5:`") + 1);
	t = t.substr(t.find("`") + 1);
	dataMD5 = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("paletteMD5:`") + 1);
	t = t.substr(t.find("`") + 1);
	paletteMD5 = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);


	while(String::startsWith(t,"animationList:"))
	{
		string frameSequenceName = "";
		int frameStart = 0;
		int hitBoxFromLeftPixels1X = 0;
		int hitBoxFromRightPixels1X = 0;
		int hitBoxFromTopPixels1X = 0;
		int hitBoxFromBottomPixels1X = 0;

		t = t.substr(t.find("frameSequenceName:`") + 1);
		t = t.substr(t.find("`") + 1);
		frameSequenceName = t.substr(0, t.find("`"));
		t = t.substr(t.find("`,") + 2);

		t = t.substr(t.find("frameStart:`") + 1);
		t = t.substr(t.find("`") + 1);
		frameStart = stoi(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);

		t = t.substr(t.find("hitBoxFromLeftPixels1X:`") + 1);
		t = t.substr(t.find("`") + 1);
		hitBoxFromLeftPixels1X = stoi(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);

		t = t.substr(t.find("hitBoxFromRightPixels1X:`") + 1);
		t = t.substr(t.find("`") + 1);
		hitBoxFromRightPixels1X = stoi(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);

		t = t.substr(t.find("hitBoxFromTopPixels1X:`") + 1);
		t = t.substr(t.find("`") + 1);
		hitBoxFromTopPixels1X = stoi(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);

		t = t.substr(t.find("hitBoxFromBottomPixels1X:`") + 1);
		t = t.substr(t.find("`") + 1);
		hitBoxFromBottomPixels1X = stoi(t.substr(0, t.find("`")));
		t = t.substr(t.find("`,") + 2);

		SpriteAnimationSequence *s = new SpriteAnimationSequence(frameSequenceName, frameStart, hitBoxFromLeftPixels1X, hitBoxFromRightPixels1X, hitBoxFromTopPixels1X, hitBoxFromBottomPixels1X);
		animationList->add(s);
	}


	t = t.substr(t.find("eventData:{") + 1);
	t = t.substr(t.find("{") + 1);
	while (String::startsWith(t, "}") == false)
	{
		EventData* data = new EventData();
		t = data->initFromString(t);
		eventData = data;
	}
	t = t.substr(t.find("}") + 1);
	t = t.substr(t.find(",") + 1);

	return t;


}
















string SpriteData::getTYPEIDString()
{ //===============================================================================================
	return "SPRITE." + to_string(getID());
}


string& SpriteData::getDisplayName()
{
	return displayName;
}

int SpriteData::getWidthPixels1X()
{
	return widthPixels1X;
}

int SpriteData::getHeightPixels1X()
{
	return heightPixels1X;
}

//int SpriteData::getWidthPixelsHQ()
//{
//	return widthPixels1X * 2;
//}
//
//int SpriteData::getHeightPixelsHQ()
//{
//	return heightPixels1X * 2;
//}

int SpriteData::getNumFrames()
{
	return frames;
}

bool SpriteData::getIsNPC()
{
	return isNPC;
}

bool SpriteData::getIsKid()
{
	return isKid;
}

bool SpriteData::getIsAdult()
{
	return isAdult;
}

bool SpriteData::getIsMale()
{
	return isMale;
}

bool SpriteData::getIsFemale()
{
	return isFemale;
}

bool SpriteData::getIsCar()
{
	return isCar;
}

bool SpriteData::getIsAnimal()
{
	return isAnimal;
}

bool SpriteData::getHasShadow()
{
	return hasShadow;
}

bool SpriteData::getIsRandom()
{
	return isRandom;
}

bool SpriteData::getIsDoor()
{
	return isDoor;
}

bool SpriteData::getIsGame()
{
	return isGame;
}

bool SpriteData::getIsItem()
{
	return isItem;
}

bool SpriteData::getForceHQ2X()
{
	return forceHQ2X;
}

EventData* SpriteData::getEventData()
{
	return eventData;
}


string& SpriteData::getItemGameDescription()
{
	return itemGameDescription;
}

float SpriteData::getGamePrice()
{
	return gamePrice;
}

int SpriteData::getUtilityOffsetXPixels1X()
{
	return utilityOffsetXPixels1X;
}

int SpriteData::getUtilityOffsetYPixels1X()
{
	return utilityOffsetYPixels1X;
}

int SpriteData::getUtilityOffsetXPixelsHQ()
{
	return utilityOffsetXPixels1X * 2;
}

int SpriteData::getUtilityOffsetYPixelsHQ()
{
	return utilityOffsetYPixels1X * 2;
}


string& SpriteData::getDataMD5()
{
	return dataMD5;
}


string& SpriteData::getPaletteMD5()
{
	return paletteMD5;
}

ArrayList<SpriteAnimationSequence*>* SpriteData::getAnimationList()
{
	return animationList;
}


string& SpriteData::getComment()
{
	return comment;
}

bool SpriteData::getForceMD5Export()
{
	return forceMD5Export;
}

void SpriteData::setComment(const string& s)
{
	comment = s;
}

void SpriteData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void SpriteData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

void SpriteData::setFrames(int s)
{
	frames = s;
}

void SpriteData::setDisplayName(const string& s)
{
	displayName = s;
}

void SpriteData::setIsNPC(bool s)
{
	isNPC = s;
}

void SpriteData::setIsKid(bool s)
{
	isKid = s;
}

void SpriteData::setIsAdult(bool s)
{
	isAdult = s;
}

void SpriteData::setIsMale(bool s)
{
	isMale = s;
}

void SpriteData::setIsFemale(bool s)
{
	isFemale = s;
}

void SpriteData::setIsCar(bool s)
{
	isCar = s;
}

void SpriteData::setIsAnimal(bool s)
{
	isAnimal = s;
}

void SpriteData::setHasShadow(bool s)
{
	hasShadow = s;
}

void SpriteData::setIsRandom(bool s)
{
	isRandom = s;
}

void SpriteData::setIsDoor(bool s)
{
	isDoor = s;
}

void SpriteData::setIsGame(bool s)
{
	isGame = s;
}

void SpriteData::setIsItem(bool s)
{
	isItem = s;
}

void SpriteData::setForceHQ2X(bool s)
{
	forceHQ2X = s;
}

void SpriteData::setForceMD5Export(bool s)
{
	forceMD5Export = s;
}

//void SpriteData::setEventID(int s)
//{
//	eventID = s;
//}

void SpriteData::setItemGameDescription(const string& s)
{
	itemGameDescription = s;
}

void SpriteData::setGamePrice(float s)
{
	gamePrice = s;
}

void SpriteData::setUtilityOffsetXPixels1X(int s)
{
	utilityOffsetXPixels1X = s;
}

void SpriteData::setUtilityOffsetYPixels1X(int s)
{
	utilityOffsetYPixels1X = s;
}

void SpriteData::setDataMD5(const string& s)
{
	dataMD5 = s;
}

void SpriteData::setPaletteMD5(const string& s)
{
	paletteMD5 = s;
}

