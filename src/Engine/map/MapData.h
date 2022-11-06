//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;



class MapStateData;
class EventData;
class DoorData;



class MapData : public AssetData
{
private:
	typedef AssetData super;



public:
	static int MAP_GROUND_LAYER;
	static int MAP_GROUND_DETAIL_LAYER;
	static int MAP_SHADER_LAYER;
	static int MAP_GROUND_SHADOW_LAYER;

	static int MAP_OBJECT_LAYER;
	static int MAP_OBJECT_DETAIL_LAYER;
	static int MAP_OBJECT_SHADOW_LAYER;

	static int MAP_ENTITY_LAYER;
	static int MAP_DOOR_LAYER;

	//TODO: need a shadow layer here that affects sprite but not overlayer

	static int MAP_ABOVE_LAYER;
	static int MAP_ABOVE_DETAIL_LAYER;
	static int MAP_SPRITE_SHADOW_LAYER;

	static int MAP_CAMERA_BOUNDS_LAYER;
	static int MAP_HIT_LAYER;


	static int MAP_LIGHT_LAYER;
	static int MAP_AREA_LAYER;
	static int MAP_LIGHT_MASK_LAYER;


	static int MAP_ENTITY_LAYER_ABOVE; //not a real layer, just used to draw entity layer with priority

	static int layers;


	static bool isTileLayer(int l);


	static bool isTransparentLayer(int l);


	//DONE clean up layers in mapAsset and Entity to make more sense in game.render()

public:


	/*
	   ----------------------MAP
	   currentMap.render(RenderOrder.GROUND);//layer 0 1 3s 4 5 6s
	
	   currentMap.renderEntities(RenderOrder.GROUND);
	   getCaptionManager()->render(RenderOrder.GROUND);
	
	   currentMap.render(RenderOrder.ABOVE); //includes above shadows, layer 9 - layers 7,8,9
	   currentMap.renderEntities(RenderOrder.ABOVE);
	   currentMap.renderEntities(RenderOrder.ABOVE_TOP);//birds? //TODO should have something OVER lights as well!
	   CinematicsManager().render(RenderOrder.ABOVE);//screen overlay under lights
	
	   getGameEngine()->stadiumScreen.render();
	
	   //LIGHTS HERE
	
	   ---------------------------ENGINE
	   getSpriteManager()->renderScreenSprites(RenderOrder.ABOVE);
	
	   getCaptionManager()->render(RenderOrder.ABOVE);
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.ABOVE_TOP);
	
	   getCaptionManager()->render(RenderOrder.ABOVE_TOP);
	
	   CinematicsManager().render(RenderOrder.ABOVE_TOP);
	
	   getTextManager()->render();
	
	   getMapManager()->renderEntities(RenderOrder.OVER_TEXT);
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.OVER_TEXT);//screensprites
	
	   getCaptionManager()->render(RenderOrder.OVER_TEXT);
	
	   getMapManager()->renderDebug();
	
	   getSpriteManager()->renderScreenSprites(RenderOrder.OVER_GUI);
	
	   getCaptionManager()->render(RenderOrder.OVER_GUI);
	
	
	   ---------------GAME ENGINE
	   nD
	   StatusBar
	   GUI
	
	
	*/

	//	public static final int SPRITE_LAYER_DEBUG_INFO = -2;
	//	public static final int SPRITE_LAYER_DEBUG_BOXES = -1;
	//
	//
	//	public static final int SPRITE_LAYER_UNDERNEATH_MAP = 0;
	//	public static final int MAP_LAYER_GROUND = 0;
	//	public static final int SPRITE_LAYER_GROUND = 1;
	//	public static final int MAP_LAYER_ABOVE = 1;
	//	public static final int SPRITE_LAYER_ABOVE_OVERLAYER = 2;
	//	public static final int SPRITE_LAYER_ABOVE_TEXT = 3;


private:
	
	string mapNote = "";


	
	int widthTiles1X = 40; //1x tile width
	
	int heightTiles1X = 30; //1x tile width
	//	public int getWidthPixels1X = 240; //1x pixel width
	//	public int getHeightPixels1X = 160; //1x pixel width
	//	public int widthTilesHQ2X = 60; //hq2x tile width
	//	public int heightTilesHQ2X = 40; //hq2x tile width
	//	public int widthPixelsHQ2X = 480; //hq2x pixel width
	//	public int heightPixelsHQ2X = 320; //hq2x pixel width

	
	int maxRandoms = 10;
	
	bool isOutside = false;
	
	bool preload = false;

	
	string groundLayerMD5 = "";
	
	string groundObjectsMD5 = "";
	
	string groundShadowMD5 = "";
	
	string objectsMD5 = "";
	
	string objects2MD5 = "";
	
	string objectShadowMD5 = "";
	
	string aboveMD5 = "";
	
	string above2MD5 = "";
	
	string spriteShadowMD5 = "";
	
	string groundShaderMD5 = "";
	
	string cameraBoundsMD5 = "";
	
	string hitBoundsMD5 = "";
	
	string lightMaskMD5 = "";
	
	string paletteMD5 = "";
	
	string tilesMD5 = "";


	//these are ASSET lists only populated with objectDatas to convert into JSON and fill the regular Map lists at runtime with.
	
	ArrayList<shared_ptr<MapStateData>> stateDataList;// = make_shared<ArrayList><shared_ptr<MapStateData>>();
	
	ArrayList<shared_ptr<EventData>> eventDataList;// = make_shared<ArrayList><shared_ptr<EventData>>();
	
	ArrayList<shared_ptr<DoorData>> doorDataList;// = make_shared<ArrayList><shared_ptr<DoorData>>();


public:
	MapData();


	MapData(int id, const string& name, int widthTiles1X, int heightTiles1X);


	//static shared_ptr<MapData> fromBase64ZippedJSON(const string& b64);
	//static shared_ptr<MapData> fromJSON(const string& json);

	string& initFromString(string& t);


	string getTYPEIDString();


	int getWidthTiles1X();
	int getHeightTiles1X();


	int getMaxRandoms();
	bool getIsOutside();
	bool getPreload();

	string& getMapNote();

	string& getGroundLayerMD5();
	string& getGroundObjectsMD5();
	string& getGroundShadowMD5();
	string& getObjectsMD5();
	string& getObjects2MD5();
	string& getObjectShadowMD5();
	string& getAboveMD5();
	string& getAbove2MD5();
	string& getSpriteShadowMD5();
	string& getGroundShaderMD5();
	string& getCameraBoundsMD5();
	string& getHitBoundsMD5();
	string& getLightMaskMD5();
	string& getPaletteMD5();
	string& getTilesMD5();


	int getWidthPixelsHQ();
	int getHeightPixelsHQ();


	ArrayList<shared_ptr<MapStateData>>* getStateDataList();
	ArrayList<shared_ptr<EventData>>* getEventDataList();
	ArrayList<shared_ptr<DoorData>>* getDoorDataList();


	void setGroundLayerMD5(const string& s);
	void setGroundObjectsMD5(const string& s);
	void setGroundShadowMD5(const string& s);
	void setObjectsMD5(const string& s);
	void setObjects2MD5(const string& s);
	void setObjectShadowMD5(const string& s);
	void setAboveMD5(const string& s);
	void setAbove2MD5(const string& s);
	void setSpriteShadowMD5(const string& s);
	void setGroundShaderMD5(const string& s);
	void setCameraBoundsMD5(const string& s);
	void setHitBoundsMD5(const string& s);
	void setLightMaskMD5(const string& s);
	void setPaletteMD5(const string& s);
	void setTilesMD5(const string& s);


	void setMapNote(const string& s);

	void setWidthTiles1X(int s);
	void setHeightTiles1X(int s);


	void setMaxRandoms(int s);
	void setIsOutside(bool s);
	void setPreload(bool s);
};

