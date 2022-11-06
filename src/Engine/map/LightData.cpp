#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




//Logger LightData::log = Logger("LightData");


LightData::LightData()
{ //=========================================================================================================================
}

LightData::LightData(int id, const string& mapName, const string& stateName, const string& name, int spawnXPixels1X, int spawnYPixels1X, int widthPixels1X, int heightPixels1X, int redColorByte, int greenColorByte, int blueColorByte, int alphaColorByte, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight, bool flickers, bool changesColor, bool toggleable, int toggleXPixels1X, int toggleYPixels1X, int flickerOnTicks, int flickerOffTicks, bool flickerRandomUpToOnTicks, bool flickerRandomUpToOffTicks)
{ //=========================================================================================================================


	initEntityData(id, name, "", spawnXPixels1X, spawnYPixels1X, 0, false, false, 255, 1.0f, 12, false, false, false, false, false, 0, 0, false, false, true, nullptr, ""); //spriteAssetName


	this->widthPixels1X = widthPixels1X;
	this->heightPixels1X = heightPixels1X;

	this->redColorByte = redColorByte;
	this->greenColorByte = greenColorByte;
	this->blueColorByte = blueColorByte;
	this->alphaColorByte = alphaColorByte;

	this->radiusPixels1X = radiusPixels1X;
	this->blendFalloff = blendFalloff;
	this->decayExponent = decayExponent;
	this->focusRadius1X = focusRadius1X;
	this->isDayLight = isDayLight;
	this->isNightLight = isNightLight;


	this->flickers = flickers;
	this->changesColor = changesColor;
	this->toggleable = toggleable;
	this->toggleXPixels1X = toggleXPixels1X;
	this->toggleYPixels1X = toggleYPixels1X;
	this->flickerOnTicks = flickerOnTicks;
	this->flickerOffTicks = flickerOffTicks;
	this->flickerRandomUpToOnTicks = flickerRandomUpToOnTicks;
	this->flickerRandomUpToOffTicks = flickerRandomUpToOffTicks;
}

LightData::LightData(int id, const string& name)
{ //=========================================================================================================================
	EntityData(id, name, "", 0, 0, 0, false, true, 255, 1.0f, 12, false, false, false, false, false, 0, 0, false, false, true, nullptr, ""); //int eventID, - boolean getDisableShadow, - boolean getRandomFrames, - boolean getOnlyHereDuringEvent, - int ticksBetweenAnimation, - int getTicksBetweenFrames, - boolean randomTimeBetweenAnimation, - boolean animateThroughFrames, - boolean getAlwaysOnBottom, - boolean getAboveWhenEqual, - boolean getAboveTopLayer, - float getScale, - int alphaByte, - boolean getNonWalkable, - boolean getPushable, - int getInitialFrame, - int getSpawnYPixels1X, - int getSpawnXPixels1X, - String spriteAssetName, - String name, - int id,
}

//shared_ptr<LightData> LightData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = make_shared<Gson>();
//	//LightData data = gson.fromJson(json,LightData.class);
//
//
//	return fromJSON(json);
//}
//
//shared_ptr<LightData> LightData::fromJSON(const string& json)
//{ //===============================================================================================
//
//
//	//shared_ptr<Gson> gson = make_shared<Gson>();
//	shared_ptr<LightData> data = nullptr;// gson->fromJson(json, LightData::typeid);
//
//
//	return data;
//}

//===============================================================================================

string& LightData::initFromString(string& t)
{//===============================================================================================
	t = super::initFromString(t);



	t = t.substr(t.find("widthPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	widthPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("heightPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	heightPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("redColorByte:`") + 1);
	t = t.substr(t.find("`") + 1);
	redColorByte = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("greenColorByte:`") + 1);
	t = t.substr(t.find("`") + 1);
	greenColorByte = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("blueColorByte:`") + 1);
	t = t.substr(t.find("`") + 1);
	blueColorByte = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("alphaColorByte:`") + 1);
	t = t.substr(t.find("`") + 1);
	alphaColorByte = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("radiusPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	radiusPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("blendFalloff:`") + 1);
	t = t.substr(t.find("`") + 1);
	blendFalloff = stof(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("decayExponent:`") + 1);
	t = t.substr(t.find("`") + 1);
	decayExponent = stof(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("focusRadius1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	focusRadius1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isDayLight:`") + 1);
	t = t.substr(t.find("`") + 1);
	isDayLight = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("isNightLight:`") + 1);
	t = t.substr(t.find("`") + 1);
	isNightLight = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("flickers:`") + 1);
	t = t.substr(t.find("`") + 1);
	flickers = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("changesColor:`") + 1);
	t = t.substr(t.find("`") + 1);
	changesColor = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("toggleable:`") + 1);
	t = t.substr(t.find("`") + 1);
	toggleable = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("toggleXPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	toggleXPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("toggleYPixels1X:`") + 1);
	t = t.substr(t.find("`") + 1);
	toggleYPixels1X = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("flickerOnTicks:`") + 1);
	t = t.substr(t.find("`") + 1);
	flickerOnTicks = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("flickerOffTicks:`") + 1);
	t = t.substr(t.find("`") + 1);
	flickerOffTicks = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("flickerRandomUpToOnTicks:`") + 1);
	t = t.substr(t.find("`") + 1);
	flickerRandomUpToOnTicks = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("flickerRandomUpToOffTicks:`") + 1);
	t = t.substr(t.find("`") + 1);
	flickerRandomUpToOffTicks = BobBoolean::parseBoolean(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);



	return t;


}





string LightData::getTYPEIDString()
{ //===============================================================================================
	return "LIGHT." + to_string(getID());
}

int LightData::getWidthPixels1X()
{
	return widthPixels1X;
}

int LightData::getHeightPixels1X()
{
	return heightPixels1X;
}

int LightData::getWidthPixelsHQ()
{
	return widthPixels1X * 2;
}

int LightData::getHeightPixelsHQ()
{
	return heightPixels1X * 2;
}

int LightData::getRadiusPixels1X()
{
	return radiusPixels1X;
}

int LightData::getRadiusPixelsHQ()
{
	return radiusPixels1X * 2;
}

int LightData::getFocusRadiusPixels1X()
{
	return focusRadius1X;
}

int LightData::getFocusRadiusPixelsHQ()
{
	return focusRadius1X * 2;
}

int LightData::getToggleXPixels1X()
{
	return toggleXPixels1X;
}

int LightData::getToggleYPixels1X()
{
	return toggleYPixels1X;
}

int LightData::getToggleXPixelsHQ()
{
	return toggleXPixels1X * 2;
}

int LightData::getToggleYPixelsHQ()
{
	return toggleYPixels1X * 2;
}

u8 LightData::getRedColorByte()
{
	return redColorByte;
}

u8 LightData::getGreenColorByte()
{
	return greenColorByte;
}

u8 LightData::getBlueColorByte()
{
	return blueColorByte;
}

u8 LightData::getAlphaColorByte()
{
	return alphaColorByte;
}

u8 LightData::r()
{
	return redColorByte;
}

u8 LightData::g()
{
	return greenColorByte;
}

u8 LightData::b()
{
	return blueColorByte;
}

u8 LightData::a()
{
	return alphaColorByte;
}

float LightData::getBlendFalloff()
{
	return blendFalloff;
}

float LightData::getDecayExponent()
{
	return decayExponent;
}

bool LightData::getIsDayLight()
{
	return isDayLight;
}

bool LightData::getIsNightLight()
{
	return isNightLight;
}

bool LightData::getFlickers()
{
	return flickers;
}

bool LightData::getChangesColor()
{
	return changesColor;
}

bool LightData::getToggleable()
{
	return toggleable;
}

int LightData::getFlickerOnTicks()
{
	return flickerOnTicks;
}

int LightData::getFlickerOffTicks()
{
	return flickerOffTicks;
}

bool LightData::getFlickerRandomUpToOnTicks()
{
	return flickerRandomUpToOnTicks;
}

bool LightData::getFlickerRandomUpToOffTicks()
{
	return flickerRandomUpToOffTicks;
}

void LightData::setWidthPixels1X(int s)
{
	widthPixels1X = s;
}

void LightData::setHeightPixels1X(int s)
{
	heightPixels1X = s;
}

void LightData::setRadiusPixels1X(int s)
{
	radiusPixels1X = s;
}

void LightData::setFocusRadiusPixels1X(int s)
{
	focusRadius1X = s;
}

void LightData::setToggleXPixels1X(int s)
{
	toggleXPixels1X = s;
}

void LightData::setToggleYPixels1X(int s)
{
	toggleYPixels1X = s;
}

void LightData::setRedColorByte(u8 s)
{
	redColorByte = s;
}

void LightData::setGreenColorByte(u8 s)
{
	greenColorByte = s;
}

void LightData::setBlueColorByte(u8 s)
{
	blueColorByte = s;
}

void LightData::setAlphaColorByte(u8 s)
{
	alphaColorByte = s;
}

void LightData::setBlendFalloff(float s)
{
	blendFalloff = s;
}

void LightData::setDecayExponent(float s)
{
	decayExponent = s;
}

void LightData::setIsDayLight(bool s)
{
	isDayLight = s;
}

void LightData::setIsNightLight(bool s)
{
	isNightLight = s;
}

void LightData::setFlickers(bool s)
{
	flickers = s;
}

void LightData::setChangesColor(bool s)
{
	changesColor = s;
}

void LightData::setToggleable(bool s)
{
	toggleable = s;
}

void LightData::setFlickerOnTicks(int s)
{
	flickerOnTicks = s;
}

void LightData::setFlickerOffTicks(int s)
{
	flickerOffTicks = s;
}

void LightData::setFlickerRandomUpToOnTicks(bool s)
{
	flickerRandomUpToOnTicks = s;
}

void LightData::setFlickerRandomUpToOffTicks(bool s)
{
	flickerRandomUpToOffTicks = s;
}

