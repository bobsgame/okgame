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
	ArrayList<shared_ptr<Map>> mapList;
	HashMap<string, shared_ptr<Map>> mapByNameHashMap;//make_shared<HashMap><string, shared_ptr<Map>>();
	HashMap<int, shared_ptr<Map>> mapByIDHashMap;//make_shared<HashMap><int, shared_ptr<Map>>();

	static Logger log;
	

	shared_ptr<Map> currentMap = nullptr;
private:
	shared_ptr<Map> lastMap = nullptr;


	//	private final KahluaConverterManager converterManager = make_shared<KahluaConverterManager>();
	//	private final J2SEPlatform platform = new J2SEPlatform();
	//	private final KahluaTable env = platform.newEnvironment();
	//	private final KahluaThread thread = make_shared<KahluaThread>(platform, env);
	//	private final LuaCaller caller = make_shared<LuaCaller>(converterManager);
	//
	//	private final LuaJavaClassExposer exposer = make_shared<LuaJavaClassExposer>(converterManager, platform, env);

public:
	static bool useThreads;
	static bool generateHQ2XChunks;
	static bool loadTexturesOnDemand;


	//textures mapped to light filenames
	static HashMap<string, shared_ptr<OKTexture>> lightTextureHashMap;//make_shared<HashMap><string, shared_ptr<Texture>>();




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



	shared_ptr<Door> doorEntered = nullptr;
	shared_ptr<Door> doorExited = nullptr;

	shared_ptr<WarpArea> warpEntered = nullptr;
	shared_ptr<WarpArea> warpExited = nullptr;


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


	MapManager(shared_ptr<Engine> g);
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


	void changeMap(shared_ptr<Map> m, int mapXTiles1X, int mapYTiles1X);


	void changeMap(shared_ptr<Map> m, shared_ptr<Door> door);


	void changeMap(shared_ptr<Map> m, shared_ptr<Area> area);


	void changeMap(shared_ptr<Map> m, shared_ptr<WarpArea> area);


	void changeMap(const string& mapName, const string& areaName);


	shared_ptr<Map> getMapByIDBlockUntilLoaded(int id);


	shared_ptr<Map> getMapByNameBlockUntilLoaded(const string& name);


	void requestMapDataIfNotLoadedYet(const string& name);


	shared_ptr<MapState> getMapStateByID(int id);


	shared_ptr<Area> getAreaByID(int id);


	shared_ptr<Entity> getEntityByID(int id);


	shared_ptr<Light> getLightByID(int id);


	shared_ptr<Door> getDoorByID(int id);
};

