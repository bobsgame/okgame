//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




//import com.bobsgame.server.BGSharedNetworkObjects.MapDataMD5sObject;

class MapState;
class WarpArea;


class Map : public EnginePart
{
public:
	static Logger log;


	MapState* currentState = nullptr;
	bool randomSpawnEnabled = true;


	ArrayList<MapState*> stateList;
	ArrayList<Event*> mapEventList;
	//ArrayList<int> mapEventIDList;


	float lastKnownScreenX = 0;
	float lastKnownScreenY = 0;


	float alpha = 1.0f;


	//this is a ArrayList of ArrayLists of sorted lights per layer. this is filled in on map first load.
	ArrayList<ArrayList<Light*>*> sortedLightsLayers;


	//these are entities that exist in this map
	ArrayList<Entity*> activeEntityList;
	//this gets filled in once per frame with entities from entityList that are on the screen
	ArrayList<Entity*> drawList;
	//that gets sorted into zList which is drawn in sequence.
	ArrayList<Entity*> zList;

	//door/warp list
	ArrayList<Door*> doorList;
	ArrayList<WarpArea*> warpAreaList;


	vector<int>* hitLayer = nullptr;
	vector<int>* cameraLayer = nullptr;
	vector<int>* groundShaderLayer = nullptr;
	vector<int>* lightMaskLayer = nullptr;


	HashMap<int,BobTexture*> chunkTexture;//= new HashMap<int, Texture*>();
	vector<bool>* chunkPNGFileExists = nullptr;
	vector<bool>* hq2xChunkPNGFileExists = nullptr;
	vector<bool>* usingHQ2XTexture = nullptr;

	vector<int>* tilesetIntArray = nullptr;
	vector<u8>* paletteRGBByteArray = nullptr;


	const static int chunkSizePixelsHQ2X = 512;
	const static int chunkSizePixels1X = chunkSizePixelsHQ2X / 2;
	const static int chunkSizeTiles1X = chunkSizePixels1X / 8;


	//static ExecutorService* generatePNGExecutorService;
	//static ExecutorService* generateLightPNGExecutorService;
	//public ExecutorService generateHQ2XPNGExecutorService = null;


	int chunkTexturesLoaded = 0;

	int maxHq2xChunkPNGThreadsCreated = 0;
	int hq2xChunkPNGThreadsCreated = 0;

	int maxChunkPNGThreadsCreated = 0;
	int chunkPNGThreadsCreated = 0;

	int maxLightPNGThreadsCreated = 0;
	int lightPNGThreadsCreated = 0;

	ConsoleText* texturesLoadedDebugText = nullptr;
	ConsoleText* hq2xChunkPNGThreadsDebugText = nullptr;
	ConsoleText* chunkPNGThreadsDebugText = nullptr;
	ConsoleText* lightPNGThreadsDebugText = nullptr;


	int chunksWidth = 0;
	int chunksHeight = 0;


	bool startedMissingChunkPNGThreads = false;
	bool startedMissingLightPNGThreads = false;
	bool startedMissingHQ2XChunkPNGThreads = false;

	bool allChunkPNGsLoadedAsTextures = false;
	bool allLightsLoadedAsTextures = false;
	bool allHQ2XChunkPNGsLoadedAsTextures = false;

	bool utilityLayersLoaded = false;

	bool miniMapGenerated = false;

	long long lastTimeMD5sRequested = 0;


	Notification* generatingAreaNotification = nullptr;


	bool addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = false;

	bool eventsAllLoadedFromServer = false;


private:
	MapData* data = nullptr;


public:
	Map();
	Map(Engine* g, MapData* mapData);
	void initMap(Engine* g, MapData* mapData);


	Entity* getEntityByName(const string& name);

	Character* getCharacterByName(const string& name);


	Light* getLightByName(const string& name);


	Area* getAreaOrWarpAreaByName(string name);


	Area* getAreaOrWarpAreaByTYPEID(string typeID);

	Door* getDoorByTYPEID(const string& typeID);

	Door* getDoorByName(const string& name);

	//public MapState getStateByName(String name){return getMapStateByName(name);}

	MapState* getMapStateByName(const string& name);


	MapState* getMapStateByID(int id);


	ArrayList<string>* getListOfRandomPointsOfInterestTYPEIDs();


	//public Tile getTileByName(String name)
	//{
	//return tileHashtable.get(name);
	//}


	void fadeIn();


	void fadeOut();


	void loadMapState(MapState* s);


private:
	long long lastLoadEventRequestTime = 0;

public:
	void update();


	void updateLoadingStatus();


	void updateEntities();


	void updateDoors();


	void updateAreas();


	void updateWarpAreas();


	void updateLights();


	void zOrderEntities();


	void sortLightLayers();


	bool defaultDisableClip = false;
	bool defaultDisableFloorOffset = false;


	void render(RenderOrder renderOrder);


	void render(RenderOrder renderOrder, bool disableClip);


	void render(RenderOrder renderOrder, bool disableClip, bool disableFloorOffset);


	void renderEntities(RenderOrder layer);


	void renderAllLightsUnsorted();


	void renderAreaActionIcons();


	void renderChunkBoxes();

	void renderHitLayer();


	void renderLightBoxes();


	void renderAreaDebugBoxes();


	void renderAreaDebugInfo();


	void renderWarpAreaDebugBoxes();


	void renderWarpAreaDebugInfo();


	//
	//	
	//	public void run()
	//	{
	//		//for map script use
	//
	//
	//	}
	//	
	//	public void load()
	//	{
	//		//for map script use
	//	}
	//
	//	
	//	public void unload()
	//	{
	//		//for map script use
	//	}


	void loadUtilityLayers();


	void saveDataToCache(vector<int>* intArrayAllLayers, vector<int>* tiles, vector<u8>* pal);


	void unloadArea(const string& s);

	void unloadLight(const string& s);

	void unloadMapEntity(const string& s);


	void releaseAllTextures();


	/// <summary>
	/// Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	/// If the camera is left of the map, it is negative.
	/// </summary>
	float mapCamX();


	/// <summary>
	/// Returns the position of the upper left of the screen relative to the map, in HQ2X equivalent pixels.
	/// If the camera is left of the map, it is negative.
	/// </summary>
	float mapCamY();


	float getScreenX(float mapX, float width);


	float getScreenY(float mapY, float height);


	float screenX();

	float screenY();


	void updateLastKnownScreenXYBasedOnCamera();


	bool getHitLayerValueAtXYTile1X(int xTile1X, int yTile1X);


	bool getHitLayerValueAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ);


	int getCameraBoundsFXLayerAtXYTile1X(int xTile1X, int yTile1X);


	int getCameraBoundsFXLayerAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ);


	bool isXYWithinScreenByAmt(float x, float y, int amt);


	bool isXYXYWithinScreenByAmount(float x, float y, float x2, float y2, float amt);


	bool isXYWithinScreen(float x, float y);


	//The following method was originally marked 'synchronized':
	BobTexture* getChunkTexture(int index);

	//The following method was originally marked 'synchronized':
	void setChunkTexture(int index, BobTexture* t);


	//The following method was originally marked 'synchronized':
	void releaseChunkTexture(int index);


	//The following method was originally marked 'synchronized':
	bool getChunkPNGFileExists(int index);

	//The following method was originally marked 'synchronized':
	void setChunkPNGFileExists_S(int index, bool done);


	//The following method was originally marked 'synchronized':
	bool getHQ2XChunkPNGFileExists(int index);

	//The following method was originally marked 'synchronized':
	void setHQ2XChunkFileExists_S(int index, bool done);


	//The following method was originally marked 'synchronized':
	void incrementChunkTexturesLoaded();

	//The following method was originally marked 'synchronized':
	void decrementChunkTexturesLoaded();

	bool loadChunkTexturesFromCachePNGs();


	bool loadLightTexturesFromCachePNGs();


	bool loadHQ2XTexturesFromCachePNGs();


	//The following method was originally marked 'synchronized':
	void incrementChunkPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	void decrementChunkPNGThreadsCreated_S();


	void startThreadsForMissingChunkPNGs();


	//The following method was originally marked 'synchronized':
	void incrementLightPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	void decrementLightPNGThreadsCreated_S();


	void startThreadsForMissingLightPNGs();


	//The following method was originally marked 'synchronized':
	void incrementHQ2XChunkPNGThreadsCreated();


	//The following method was originally marked 'synchronized':
	void decrementHQ2XChunkPNGThreadsCreated();


	void startThreadsForMissingHQ2XChunkPNGs();


	void createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex, vector<int>* tilesetIntArray, vector<u8>* paletteRGBByteArray);


	/// <summary>
	/// returns false if no image is needed
	/// </summary>
	bool drawTileLayerIntoBufferedImage(const string& layerFileName, BufferedImage* chunkImage, BufferedImage* chunkImageBorder, int chunkX, int chunkY, vector<int>* layerChunkBuffer, bool shadowLayer, vector<int>* tilesetIntArray, vector<u8>* paletteRGBByteArray);


	void createHQ2XTexturePNG_THREAD(int chunkX, int chunkY);


	void antialiasBufferedImage(BufferedImage* bufferedImage);

	void setHQ2XAlphaFromOriginal(BufferedImage* hq2xBufferedImage, BufferedImage* bufferedImage);


	void addEntitiesAndCharactersFromCurrentStateToActiveEntityList();


	void clearActiveEntityList();


	bool isAnyoneOverlappingXY(float x, float y);

	bool isAnyoneOverlappingXYXY(float x, float y, float x2, float y2);


	bool isAnyRandomCharacterTryingToGoToXY(float x, float y);


	int* findOpenSpaceInArea(Area* a, int w, int h);


	bool isAnyCharacterTouchingArea(Area* a);


	bool isAnyEntityTouchingArea(Area* a);


	ArrayList<Entity*>* getAllEntitiesTouchingArea(Area* a);


	ArrayList<Entity*>* getAllEntitiesPlayerIsTouching();


	bool isAnyoneTryingToGoToArea(Area* a);


	bool isAnyEntityUsingSpriteAsset(Sprite* s);


	ArrayList<Entity*>* getAllEntitiesUsingSpriteAsset(Sprite* s);


	Entity* createEntity(const string& spriteName, Sprite* spriteAsset, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE.. X AND Y ARE UPPER LEFT CORNER NOT FEET


	Entity* createEntityFeetAtXY(const string& spriteName, Sprite* sprite, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE,X AND Y ARE FEET PLACEMENT


	Entity* createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(Entity* e, const string& spriteName, Sprite* sprite, float mapX, float mapY, int amt);


	Entity* createEntityAtArea(const string& spriteName, Sprite* spriteAsset, Area* a);


	MapData* getData();


	int getID();
	string& getName();
	string& getMapNote();

	int getWidthTiles1X();
	int getHeightTiles1X();

	int getWidthPixelsHQ();
	int getHeightPixelsHQ();


	int getMaxRandoms();
	bool getIsOutside();

	string getTYPEIDString();

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

	//	public Vector<MapStateData> getStateDataList(){return getData().getStateDataList();}
	//	public Vector<EventData> getEventDataList(){return getData().getEventDataList();}
	//	public Vector<DoorData> getDoorDataList(){return getData().getDoorDataList();}


	//set


	//	public void setWidthTiles(int s){getData().setWidthTiles1X(s);}
	//	public void setHeightTiles(int s){getData().setHeightTiles1X(s);}
	//
	//	public void setID(int s){getData().setID(s);}
	//	public void setMapNote(String s){getData().setMapNote(s);}
	//
	//	public void setMaxRandoms(int s){getData().setMaxRandoms(s);}
	//	public void setIsOutside(boolean s){getData().setIsOutside(s);}
	//

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
};

