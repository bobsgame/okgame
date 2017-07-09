//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;



class LightData : public EntityData
{

private:
	typedef EntityData super;

private:
	
	int widthPixels1X = 2;
	
	int heightPixels1X = 2;

	
	u8 redColorByte = 0;
	
	u8 greenColorByte = 0;
	
	u8 blueColorByte = 0;
	
	u8 alphaColorByte = 0;

	
	int radiusPixels1X = 2;

	
	float blendFalloff = 2.0f;

	
	float decayExponent = 1.0f;
	int focusRadius1X = 0;
	
	bool isDayLight = true;
	
	bool isNightLight = false;

	
	bool flickers = false;
	
	bool changesColor = false;
	
	bool toggleable = false;
	
	int toggleXPixels1X = -1;
	
	int toggleYPixels1X = -1;
	
	int flickerOnTicks = 0;
	
	int flickerOffTicks = 0;
	
	bool flickerRandomUpToOnTicks = false;
	
	bool flickerRandomUpToOffTicks = false;

public:
	LightData();

	LightData(int id, const string& mapName, const string& stateName, const string& name, int spawnXPixels1X, int spawnYPixels1X, int widthPixels1X, int heightPixels1X, int redColorByte, int greenColorByte, int blueColorByte, int alphaColorByte, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight, bool flickers, bool changesColor, bool toggleable, int toggleXPixels1X, int toggleYPixels1X, int flickerOnTicks, int flickerOffTicks, bool flickerRandomUpToOnTicks, bool flickerRandomUpToOffTicks);

	LightData(int id, const string& name);

	//static LightData* fromBase64ZippedJSON(const string& b64);

	//static LightData* fromJSON(const string& json);

	string& initFromString(string& t) override;

	virtual string getTYPEIDString() override;

	int getWidthPixels1X();
	int getHeightPixels1X();
	int getWidthPixelsHQ();
	int getHeightPixelsHQ();

	int getRadiusPixels1X();
	int getRadiusPixelsHQ();

	int getFocusRadiusPixels1X();
	int getFocusRadiusPixelsHQ();

	int getToggleXPixels1X();
	int getToggleYPixels1X();
	int getToggleXPixelsHQ();
	int getToggleYPixelsHQ();

	u8 getRedColorByte();
	u8 getGreenColorByte();
	u8 getBlueColorByte();
	u8 getAlphaColorByte();

	u8 r();
	u8 g();
	u8 b();
	u8 a();

	float getBlendFalloff();
	float getDecayExponent();
	bool getIsDayLight();
	bool getIsNightLight();
	bool getFlickers();
	bool getChangesColor();
	bool getToggleable();
	int getFlickerOnTicks();
	int getFlickerOffTicks();
	bool getFlickerRandomUpToOnTicks();
	bool getFlickerRandomUpToOffTicks();

	//set

	void setWidthPixels1X(int s);
	void setHeightPixels1X(int s);

	void setRadiusPixels1X(int s);

	void setFocusRadiusPixels1X(int s);

	void setToggleXPixels1X(int s);
	void setToggleYPixels1X(int s);

	void setRedColorByte(u8 s);
	void setGreenColorByte(u8 s);
	void setBlueColorByte(u8 s);
	void setAlphaColorByte(u8 s);

	void setBlendFalloff(float s);
	void setDecayExponent(float s);
	void setIsDayLight(bool s);
	void setIsNightLight(bool s);
	void setFlickers(bool s);
	void setChangesColor(bool s);
	void setToggleable(bool s);
	void setFlickerOnTicks(int s);
	void setFlickerOffTicks(int s);
	void setFlickerRandomUpToOnTicks(bool s);
	void setFlickerRandomUpToOffTicks(bool s);
};

