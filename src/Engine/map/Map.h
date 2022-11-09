//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
#include "CTPL-master/ctpl_stl.h"

class Logger;




//import com.bobsgame.server.BGSharedNetworkObjects.MapDataMD5sObject;

class MapState;
class WarpArea;


class Map : public EnginePart
{
public:
	static Logger log;


	sp<MapState> currentState = nullptr;
	bool randomSpawnEnabled = true;


	vector<sp<MapState>> stateList;
	vector<sp<Event>> mapEventList;
	//ArrayList<int> mapEventIDList;


	float lastKnownScreenX = 0;
	float lastKnownScreenY = 0;


	float alpha = 1.0f;


	//this is a ArrayList of ArrayLists of sorted lights per layer. this is filled in on map first load.
	vector<ArrayList<sp<Light>>> sortedLightsLayers;


	//these are entities that exist in this map
	vector<sp<Entity>> activeEntityList;
	//this gets filled in once per frame with entities from entityList that are on the screen
	vector<sp<Entity>> drawList;
	//that gets sorted into zList which is drawn in sequence.
	vector<sp<Entity>> zList;

	//door/warp list
	vector<sp<Door>> doorList;
	vector<sp<WarpArea>> warpAreaList;


	sp<IntArray> hitLayer = nullptr;
	sp<IntArray> cameraLayer = nullptr;
	sp<IntArray> groundShaderLayer = nullptr;
	sp<IntArray> lightMaskLayer = nullptr;


	HashMap<int,sp<OKTexture>> chunkTexture;//= ms<HashMap><int, sp<Texture>>();

	sp<vector<bool>> usingHQ2XTexture = nullptr;


	//these are accessed by threads but not modified by threads so it's probably OK
	sp<IntArray> tilesetIntArray = nullptr;
	sp<ByteArray> paletteRGBByteArray = nullptr;

	//when this happens i can delete the indexed data and palette data but until then they are being accessed by threads
	bool allChunkPNGsLoadedAsTextures = false;
	bool allLightsLoadedAsTextures = false;
	bool allHQ2XChunkPNGsLoadedAsTextures = false;


	const static int chunkSizePixelsHQ2X = 512;
	const static int chunkSizePixels1X = chunkSizePixelsHQ2X / 2;
	const static int chunkSizeTiles1X = chunkSizePixels1X / 8;


	//static sp<ExecutorService> generatePNGExecutorService;
	//static sp<ExecutorService> generateLightPNGExecutorService;
	//public ExecutorService generateHQ2XPNGExecutorService = null;



	static ctpl::thread_pool* generatePNGThreadPool;
	static ctpl::thread_pool* generateLightPNGThreadPool;
	//static ctpl::thread_pool* generateHQ2XPNGThreadPool;


	

	int maxHq2xChunkPNGThreadsCreated = 0;
	int hq2xChunkPNGThreadsCreated = 0;

	int maxChunkPNGThreadsCreated = 0;
	int chunkPNGThreadsCreated = 0;

	int maxLightPNGThreadsCreated = 0;
	int lightPNGThreadsCreated = 0;

	sp<ConsoleText> texturesLoadedDebugText = nullptr;
	sp<ConsoleText> hq2xChunkPNGThreadsDebugText = nullptr;
	sp<ConsoleText> chunkPNGThreadsDebugText = nullptr;
	sp<ConsoleText> lightPNGThreadsDebugText = nullptr;


	int chunksWidth = 0;
	int chunksHeight = 0;


	bool startedMissingChunkPNGThreads = false;
	bool startedMissingLightPNGThreads = false;
	bool startedMissingHQ2XChunkPNGThreads = false;



	bool utilityLayersLoaded = false;

	bool miniMapGenerated = false;

	long long lastTimeMD5sRequested = 0;


	sp<Notification> generatingAreaNotification = nullptr;


	bool addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = false;

	bool eventsAllLoadedFromServer = false;


private:
	sp<MapData> data = nullptr;


public:
	Map();
	Map(sp<Engine> g, sp<MapData> mapData);
	void initMap(sp<Engine> g, sp<MapData> mapData);


	sp<Entity> getEntityByName(const string& name);

	sp<Character> getCharacterByName(const string& name);


	sp<Light> getLightByName(const string& name);


	sp<Area> getAreaOrWarpAreaByName(string name);


	sp<Area> getAreaOrWarpAreaByTYPEID(string typeID);

	sp<Door> getDoorByTYPEID(const string& typeID);

	sp<Door> getDoorByName(const string& name);

	//public MapState getStateByName(String name){return getMapStateByName(name);}

	sp<MapState> getMapStateByName(const string& name);


	sp<MapState> getMapStateByID(int id);


	sp<vector<string>> getListOfRandomPointsOfInterestTYPEIDs();


	//public Tile getTileByName(String name)
	//{
	//return tileHashtable.get(name);
	//}


	void fadeIn();


	void fadeOut();


	void loadMapState(sp<MapState> s);


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


	void saveDataToCache(sp<IntArray> intArrayAllLayers, sp<IntArray> tiles, sp<ByteArray> pal);


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
	sp<OKTexture> getChunkTexture(int index);

	//The following method was originally marked 'synchronized':
	void setChunkTexture(int index, sp<OKTexture> t);


	//The following method was originally marked 'synchronized':
	void releaseChunkTexture(int index);








	//------------------------------------
	sp<vector<bool>> _chunkPNGFileExists = nullptr;
	mutex _chunkPNGFileExists_Mutex;
	bool getChunkPNGFileExists_S(int index)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkPNGFileExists_Mutex);
		return (*_chunkPNGFileExists)[index];
	}


	void setChunkPNGFileExists_S(int index, bool done)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkPNGFileExists_Mutex);
		(*_chunkPNGFileExists)[index] = done;
	}


	//------------------------------------
	sp<vector<bool>> _hq2xChunkPNGFileExists = nullptr;
	mutex _hq2xChunkPNGFileExists_Mutex;
	bool getHQ2XChunkPNGFileExists_S(int index)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_hq2xChunkPNGFileExists_Mutex);
		return (*_hq2xChunkPNGFileExists)[index];
	}


	void setHQ2XChunkFileExists_S(int index, bool done)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_hq2xChunkPNGFileExists_Mutex);
		(*_hq2xChunkPNGFileExists)[index] = done;
	}

	//------------------------------------
	int _chunkTexturesLoaded = 0;
	mutex _chunkTexturesLoaded_Mutex;
	void incrementChunkTexturesLoaded_S()
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkTexturesLoaded_Mutex);
		_chunkTexturesLoaded++;
	}


	void decrementChunkTexturesLoaded_S()
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkTexturesLoaded_Mutex);
		_chunkTexturesLoaded--;
	}

	int getChunkTexturesLoaded_S()
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkTexturesLoaded_Mutex);
		return _chunkTexturesLoaded;
	}

	void setChunkTexturesLoaded_S(int s)
	{ //=========================================================================================================================
		lock_guard<mutex> lock(_chunkTexturesLoaded_Mutex);
		_chunkTexturesLoaded = s;
	}
	//------------------------------------













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


	void createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex);


	/// <summary>
	/// returns false if no image is needed
	/// </summary>
	bool drawTileLayerIntoBufferedImage(const string& layerFileName, sp<BufferedImage> chunkImage, sp<BufferedImage> chunkImageBorder, int chunkX, int chunkY, sp<IntArray> layerChunkBuffer, bool shadowLayer);


	void createHQ2XTexturePNG_THREAD(int chunkX, int chunkY);


	void antialiasBufferedImage(sp<BufferedImage> bufferedImage);

	void setHQ2XAlphaFromOriginal(sp<BufferedImage> hq2xBufferedImage, sp<BufferedImage> bufferedImage);


	void addEntitiesAndCharactersFromCurrentStateToActiveEntityList();


	void clearActiveEntityList();


	bool isAnyoneOverlappingXY(float x, float y);

	bool isAnyoneOverlappingXYXY(float x, float y, float x2, float y2);


	bool isAnyRandomCharacterTryingToGoToXY(float x, float y);


	int* findOpenSpaceInArea(sp<Area> a, int w, int h);


	bool isAnyCharacterTouchingArea(sp<Area> a);


	bool isAnyEntityTouchingArea(sp<Area> a);


	sp<vector<sp<Entity>>> getAllEntitiesTouchingArea(sp<Area> a);


	sp<vector<sp<Entity>>> getAllEntitiesPlayerIsTouching();


	bool isAnyoneTryingToGoToArea(sp<Area> a);


	bool isAnyEntityUsingSpriteAsset(sp<Sprite> s);


	sp<vector<sp<Entity>>> getAllEntitiesUsingSpriteAsset(sp<Sprite> s);


	sp<Entity> createEntity(const string& spriteName, sp<Sprite> spriteAsset, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE.. X AND Y ARE UPPER LEFT CORNER NOT FEET


	sp<Entity> createEntityFeetAtXY(const string& spriteName, sp<Sprite> sprite, float mapX, float mapY); // SIZE X AND Y ARE ACTUAL Entity HEIGHT AND WIDTH NOT SPRITE SIZE,X AND Y ARE FEET PLACEMENT


	sp<Entity> createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(sp<Entity> e, const string& spriteName, sp<Sprite> sprite, float mapX, float mapY, int amt);


	sp<Entity> createEntityAtArea(const string& spriteName, sp<Sprite> spriteAsset, sp<Area> a);


	sp<MapData> getData();


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

