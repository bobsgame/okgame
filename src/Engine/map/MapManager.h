//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapManager : public EnginePart
{
public:
	ArrayList<Map*> mapList;
	HashMap<string, Map*> mapByNameHashMap;//new HashMap<string, Map*>();
	HashMap<int, Map*> mapByIDHashMap;//new HashMap<int, Map*>();

	static Logger log;
	

	Map* currentMap = nullptr;
private:
	Map* lastMap = nullptr;


	//	private final KahluaConverterManager converterManager = new KahluaConverterManager();
	//	private final J2SEPlatform platform = new J2SEPlatform();
	//	private final KahluaTable env = platform.newEnvironment();
	//	private final KahluaThread thread = new KahluaThread(platform, env);
	//	private final LuaCaller caller = new LuaCaller(converterManager);
	//
	//	private final LuaJavaClassExposer exposer = new LuaJavaClassExposer(converterManager, platform, env);

public:
	static bool useThreads;
	static bool generateHQ2XChunks;
	static bool loadTexturesOnDemand;


	//textures mapped to light filenames
	static HashMap<string, BobTexture*> lightTextureHashMap;//new HashMap<string, Texture*>();


	//hashtable (threadsafe) mapped to light filename, and boolean array[1] set whether it exists (so multiple threads don't check if file exists at same time)
	static HashMap<string, BobBool*> lightTextureFileExistsHashtable;//new HashMap<string, BobBool*>();


	Door* doorEntered = nullptr;
	Door* doorExited = nullptr;

	WarpArea* warpEntered = nullptr;
	WarpArea* warpExited = nullptr;


	float drawAngle = 0; //TODO

	float hue = 1.0f;
	float saturation = 1.0f;
	float brightness = 1.0f;
	float contrast = 1.0f;
	float gamma = 1.0f;
	bool grayscale = false;
	bool effects8Bit = false; //TODO
	bool effectsInverted = false; //TODO
	bool effectsBlackAndWhite = false; //TODO


	MapManager(Engine* g);
	~MapManager();


	void update();





	void render();


	void renderLastMap();


	/// <summary>
	///for drawing any map entities over getText </summary>
	void renderEntities(RenderOrder layer);


	void setFBOEffects();


	void setNonFBOEffects();


	void setEffectsShaderEffects();


	void setTextureRotation();


	void rotateMap(int rotateDegrees);


	void renderDebug();


	bool isDayTime();


	bool isNightTime();


	bool isRaining();


	bool isSnowing();


	bool isWindy();


	bool isFoggy();


	//used to keep track of the camera offset so we can scroll the last map along with the new one
	static float lastMapCameraOffsetX;
	static float lastMapCameraOffsetY;
	static float lastMapScreenX;
	static float lastMapScreenY;


	void fadeOutAndReleaseLastMap();


	void setTransitionOffsets();


	void changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ);


	void changeMap(const string& mapName, int mapXPixelsHQ, int mapYPixelsHQ, bool updateGameSave);


	void changeMap(Map* m, int mapXTiles1X, int mapYTiles1X);


	void changeMap(Map* m, Door* door);


	void changeMap(Map* m, Area* area);


	void changeMap(Map* m, WarpArea* area);


	void changeMap(const string& mapName, const string& areaName);


	Map* getMapByIDBlockUntilLoaded(int id);


	Map* getMapByNameBlockUntilLoaded(const string& name);


	void requestMapDataIfNotLoadedYet(const string& name);


	MapState* getMapStateByID(int id);


	Area* getAreaByID(int id);


	Entity* getEntityByID(int id);


	Light* getLightByID(int id);


	Door* getDoorByID(int id);
};

