//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class MapManager : public EnginePart
{
public:
	vector<sp<Map>> mapList;
	HashMap<string, sp<Map>> mapByNameHashMap;//ms<HashMap><string, sp<Map>>();
	HashMap<int, sp<Map>> mapByIDHashMap;//ms<HashMap><int, sp<Map>>();

	static Logger log;
	

	sp<Map> currentMap = nullptr;
private:
	sp<Map> lastMap = nullptr;


	//	private final KahluaConverterManager converterManager = ms<KahluaConverterManager>();
	//	private final J2SEPlatform platform = new J2SEPlatform();
	//	private final KahluaTable env = platform.newEnvironment();
	//	private final KahluaThread thread = ms<KahluaThread>(platform, env);
	//	private final LuaCaller caller = ms<LuaCaller>(converterManager);
	//
	//	private final LuaJavaClassExposer exposer = ms<LuaJavaClassExposer>(converterManager, platform, env);

public:
	static bool useThreads;
	static bool generateHQ2XChunks;
	static bool loadTexturesOnDemand;


	//textures mapped to light filenames
	static HashMap<string, sp<OKTexture>> lightTextureHashMap;//ms<HashMap><string, sp<Texture>>();




	//threadsafe HashMap mapped to light filename, and boolean set whether it exists (so multiple threads don't check if file exists at same time)
	static HashMap<string, bool> _lightTextureFileExistsHashtable;
	static mutex _lightTextureFileExistsHashtable_Mutex;
																  
	static void setLightTexturePNGFileExists_S(string filename, bool exists)
	{ //===============================================================================================

		lock_guard<mutex> lock(_lightTextureFileExistsHashtable_Mutex);
		_lightTextureFileExistsHashtable.put(filename, exists);
	}

	static bool getLightTexturePNGFileExists_S(string filename)
	{ //===============================================================================================

		lock_guard<mutex> lock(_lightTextureFileExistsHashtable_Mutex);
		bool existsInHashtable = false;


		if (_lightTextureFileExistsHashtable.containsKey(filename))
		{
			existsInHashtable = _lightTextureFileExistsHashtable.get(filename);

		}

		return existsInHashtable;

	}



	sp<Door> doorEntered = nullptr;
	sp<Door> doorExited = nullptr;

	sp<WarpArea> warpEntered = nullptr;
	sp<WarpArea> warpExited = nullptr;


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


	MapManager(sp<Engine> g);
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


	void changeMap(sp<Map> m, int mapXTiles1X, int mapYTiles1X);


	void changeMap(sp<Map> m, sp<Door> door);


	void changeMap(sp<Map> m, sp<Area> area);


	void changeMap(sp<Map> m, sp<WarpArea> area);


	void changeMap(const string& mapName, const string& areaName);


	sp<Map> getMapByIDBlockUntilLoaded(int id);


	sp<Map> getMapByNameBlockUntilLoaded(const string& name);


	void requestMapDataIfNotLoadedYet(const string& name);


	sp<MapState> getMapStateByID(int id);


	sp<Area> getAreaByID(int id);


	sp<Entity> getEntityByID(int id);


	sp<Light> getLightByID(int id);


	sp<Door> getDoorByID(int id);
};

