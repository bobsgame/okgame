//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"

class Logger;
class MapManager;

class LightData;
class Light;

class ImageData
{
};

//class BufferedImageData : public ImageData
//{
//private:
//	Light* outerInstance = nullptr;
//
//	int width = 0;
//	int height = 0;
//
//	u8* byteArray = nullptr;
//	u8* byteBuffer = nullptr;
//
//	int texWidth = 0;
//	int texHeight = 0;
//
//public:
//	BufferedImageData(Light* outerInstance, BufferedImage* bufferedImage);
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getDepth() </seealso>
//	int getDepth();
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getHeight() </seealso>
//	int getHeight();
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getImageBufferData() </seealso>
//	u8* getImageBufferData();
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getTexHeight() </seealso>
//	int getTexHeight();
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getTexWidth() </seealso>
//	int getTexWidth();
//
//	/// <seealso cref= org.newdawn.slick.opengl.ImageData#getWidth() </seealso>
//	int getWidth();
//};

class Light : public Entity
{
public:
	static Logger log;

	static int NOT_DRAWN;
	static int DRAWING;
	static int OVERLAPS_SOMETHING;
	static int DRAWN;

	BobTexture* texture = nullptr;

	int sortingState = 0;

	//private LightData data;

	//TO DO: handle these

	//public int id = -1;
	//public String stateName = "";

	bool isScreenLight = false;

	/// <summary>
	/// This constructor is specifically for creating lights not bound to the map, but to the screen instead. The mapX and mapY coords will be used as screen coords.
	/// </summary>
	Light(Engine* g, const string& name, int mapXPixels1X, int mapYPixels1X, int widthPixels1X, int heightPixels1X, int red, int green, int blue, int alpha, int radiusPixels1X, float blendFalloff, float decayExponent, int focusRadius1X, bool isDayLight, bool isNightLight);

	Light(Engine* g, LightData* lightAsset, Map* m);

	bool flickerOnOffToggle = true;
	int onTicks = 0;
	int offTicks = 0;
	long long ticksCounter = 0;
	bool toggleOnOffToggle = true;

	bool drawLightThisFrame = true;

	virtual void update() override;	
	void initLight(LightData* lightAsset);
	void toggle();
	void setOnOff(bool b);
	void setFlicker(bool b);






	string getFileName();
	bool checkEdgeAgainstHitLayerAndOtherLightsInDirection(int dir);
	void bounceAroundRoom();
	bool isOnScreen();
	virtual void renderDebugBoxes() override;
	virtual void render(float alpha) override;
	bool renderLight();
	bool renderLight(float screenX0, float screenX1, float screenY0, float screenY1, float alpha);
	void createLightTexturePNG(const string& fileName);
	static void createLightTexturePNG(string fileName, u8 r, u8 g, u8 b, u8 a, float w, float h, float rad, float focusRad, float decayExp);
public:
	virtual float getLeft() override;
	virtual float getRight() override;
	virtual float getTop() override;
	virtual float getBottom() override;
	virtual float getScreenLeft() override;
	float screenRight();
	virtual float getScreenTop() override;
	float screenBottom();
	float screenMiddleX();
	float screenMiddleY();
	virtual float getHitBoxFromLeft() final override;
	virtual float getHitBoxFromRight() final override;
	virtual float getHitBoxFromTop() final override;
	virtual float getHitBoxFromBottom() final override;

	//virtual EntityData* getData() override;
	LightData* getLightData();

	virtual float getWidth() override;
	virtual float getHeight() override;

	int getRadiusPixelsHQ();
	int focusRadiusPixelsHQ();
	int toggleXPixelsHQ();
	int toggleYPixelsHQ();

	u8 redColorByte();
	u8 greenColorByte();
	u8 blueColorByte();
	u8 alphaColorByte();

	u8 r();
	u8 g();
	u8 b();
	u8 a();

	float blendFalloff();
	float decayExponent();
	bool isDayLight();
	bool isNightLight();
	bool flickers();
	bool changesColor();
	bool toggleable();
	int flickerOnTicks();
	int flickerOffTicks();
	bool flickerRandomUpToOnTicks();
	bool flickerRandomUpToOffTicks();

	//public String getTYPEIDString(){return getData().getTYPEIDString();}

	//set

	void setWidthPixels(int s);
	void setHeightPixels(int s);
	void setRadiusPixels(int s);
	void setFocusRadiusPixels(int s);
	void setToggleXPixels(int s);
	void setToggleYPixels(int s);

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

