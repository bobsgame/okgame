
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once

#include "CTPL-master/ctpl_stl.h"


Logger Map::log = Logger("Map");



//java::util::concurrent::ExecutorService* Map::generatePNGExecutorService = nullptr;
//java::util::concurrent::ExecutorService* Map::generateLightPNGExecutorService = nullptr;
ctpl::thread_pool* Map::generatePNGThreadPool = nullptr;
ctpl::thread_pool* Map::generateLightPNGThreadPool = nullptr;
//ctpl::thread_pool* Map::generateHQ2XPNGThreadPool = nullptr;

//=========================================================================================================================
Map::Map()
{//=========================================================================================================================

	//chunkTexture = ms<HashMap><int, sp<OKTexture>>();
}


//=========================================================================================================================
Map::Map(sp<Engine> g, sp<MapData> mapData)
{ //=========================================================================================================================

	//chunkTexture = ms<HashMap><int, sp<OKTexture>>();

	initMap(g, mapData);

}


//=========================================================================================================================
void Map::initMap(sp<Engine> g, sp<MapData> mapData)
{
	e = g;

	data = mapData;


	//determine number of chunks horizontal and vertical

	//TODO: make this proper with modulus, if the split is even there will be one extra chunk
	chunksWidth = (mapData->getWidthTiles1X() / chunkSizeTiles1X) + 1;
	chunksHeight = (mapData->getHeightTiles1X() / chunkSizeTiles1X) + 1;

//	if (chunkTexture.isEmpty())
//	{
//	    //chunkTexture = ms<ArrayList><sp<Texture>>(chunksWidth * chunksHeight * 2); // *2 for over/under layer
//	    for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
//	    {
//	        delete chunkTexture.get(i);
//	    }
//	}


	//these are thread safe variables but it's OK here because it's only on init
	if (_chunkPNGFileExists == nullptr)
	{
		_chunkPNGFileExists = ms<vector<bool>>(new vector<bool>(chunksWidth * chunksHeight * 2));
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			(*_chunkPNGFileExists)[i] = false;
		}
	}

	if (_hq2xChunkPNGFileExists == nullptr)
	{
		_hq2xChunkPNGFileExists = ms<vector<bool>>(new vector<bool>(chunksWidth * chunksHeight * 2));
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			(*_hq2xChunkPNGFileExists)[i] = false;
		}
	}

	if (usingHQ2XTexture == nullptr)
	{
		usingHQ2XTexture = ms<vector<bool>>(new vector<bool>(chunksWidth * chunksHeight * 2));
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			(*usingHQ2XTexture)[i] = false;
		}
	}


	//need to run through mapData structure and create entities, events, lights, areas, doors, states, warpareas


	for (int i = 0; i < (int)mapData->getEventDataList()->size(); i++)
	{
		//create event, add to eventList
		sp<EventData> eventData = mapData->getEventDataList()->at(i);


		sp<Event> event = nullptr;

		for (int k = 0; k < (int)getEventManager()->eventList.size(); k++)
		{
			if (getEventManager()->eventList.at(k)->getID() == eventData->getID())
			{
				event = getEventManager()->eventList.at(k);
			}
		}

		if (event == nullptr)
		{
			event = ms<Event>(getEngine(), eventData, this);
		}


		mapEventList.push_back(event);

	}


	for (int i = 0; i < (int)mapData->getDoorDataList()->size(); i++)
	{
		//create door, add to doorList,

		sp<DoorData> doorData = mapData->getDoorDataList()->at(i);
		sp<Door> door = ms<Door>(getEngine(), doorData, this);


		//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
		//also check and make sure it is sending event update

		doorList.push_back(door);
	}


	for (int i = 0; i < (int)mapData->getStateDataList()->size(); i++)
	{
		sp<MapStateData> mapStateData = mapData->getStateDataList()->at(i);


		//create state, add to state list.
		sp<MapState> mapState = ms<MapState>(mapStateData, this);

		stateList.push_back(mapState);


		for (int n = 0; n < (int)mapStateData->getAreaDataList()->size(); n++)
		{
			sp<AreaData> areaData = mapStateData->getAreaDataList()->at(n);

			if (areaData->getIsWarpArea())
			{
				//create warparea, add to warpAreaList
				sp<WarpArea> warpArea = ms<WarpArea>(getEngine(), areaData, this);

				//TODO: in door update, send command to load door connecting map, it will return as a network thread, create the map object, block that thread until it is loaded.
				//also check and make sure it is sending event update

				warpAreaList.push_back(warpArea);
				//note that warp areas DON'T get added to the currentMap.areaHashmap.
				//i go through each map and search for the appropriate warparea in that list
			}
			else
			{
				sp<Area> area = ms<Area>(getEngine(), areaData, this);
				mapState->areaByNameHashtable.put(area->getName(), area);
				mapState->areaByTYPEIDHashtable.put(area->getTYPEIDString(), area);
				mapState->areaList.push_back(area);
			}
		}


		for (int n = 0; n < (int)mapStateData->getLightDataList()->size(); n++)
		{
			sp<LightData> lightData = mapStateData->getLightDataList()->at(n);
			sp<Light> light = ms<Light>(getEngine(), lightData, this);


			mapState->lightList.push_back(light);
			mapState->lightByNameHashtable.put(light->getName(), light);
		}


		for (int n = 0; n < (int)mapStateData->getEntityDataList()->size(); n++)
		{
			sp<EntityData> entityData = mapStateData->getEntityDataList()->at(n);

			if (entityData->getIsNPC())
			{
				sp<Character> character = ms<Character>(getEngine(), entityData, this);

				mapState->characterList.push_back(character);
				mapState->characterByNameHashtable.put(character->getName(), character);
			}
			else
			{
				sp<Entity> entity = ms<Entity>(getEngine(), entityData, this);

				mapState->entityList.push_back(entity);
				mapState->entityByNameHashtable.put(entity->getName(), entity);
			}
		}
	}


	//get load event, run it to determine which state to load. (done in update)
}


//=========================================================================================================================
sp<Entity> Map::getEntityByName(const string& name)
{ //=========================================================================================================================
	sp<Entity> e = nullptr;

	if(currentState->entityByNameHashtable.containsKey(name))
	e = currentState->entityByNameHashtable.get(name);

	if (e == nullptr)
	{
		e = getCharacterByName(name);
	}

	if (e == nullptr)
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			if (activeEntityList.at(i)->getName() == name)
			{
				e = activeEntityList.at(i);
			}
		}
	}

	if (e == nullptr)
	{
		for (int i = 0; i < (int)getSpriteManager()->screenSpriteList.size(); i++)
		{
			if (getSpriteManager()->screenSpriteList.at(i)->getName().compare(name) == 0)
			{
				e = getSpriteManager()->screenSpriteList.at(i);
			}
		}
	}

	if (e == nullptr)
	{
		e = getLightByName(name);
	}

	return e;
}


//=========================================================================================================================
sp<Character> Map::getCharacterByName(const string& name)
{ //=========================================================================================================================
	return currentState->characterByNameHashtable.get(name);
}


//=========================================================================================================================
sp<Light> Map::getLightByName(const string& name)
{ //=========================================================================================================================

	//log.debug("getLightByName: "+name);

	return currentState->lightByNameHashtable.get(name);
}


//=========================================================================================================================
sp<Area> Map::getAreaOrWarpAreaByName(string name)
{ //=========================================================================================================================


	//log.debug("getAreaOrWarpAreaByName: "+name);

	if (OKString::startsWith(name, "AREA."))
	{
		name = name.substr(name.find(".") + 1);
	}


	sp<Area> a = nullptr;
	if (currentState != nullptr)
	{
		if (currentState->areaByNameHashtable.containsKey(name))
		a = currentState->areaByNameHashtable.get(name);
	}

	if (a == nullptr)
	{
		for (int i = 0; i < stateList.size(); i++)
		{
			sp<MapState> s = stateList.at(i);
			if (s->areaByNameHashtable.containsKey(name))
			a = s->areaByNameHashtable.get(name);
			if (a != nullptr)
			{
				break;
			}
		}
	}

	if (a == nullptr)
	{
		for (int i = 0; i < warpAreaList.size(); i++)
		{
			if (warpAreaList.at(i)->getName() == name)
			{
				a = warpAreaList.at(i);
			}
		}
	}

	if (a == nullptr)
	{
		log.error("Could not find Area/WarpArea: getAreaOrWarpAreaByName() Name:" + name);
	}


	return a;
}

sp<Area> Map::getAreaOrWarpAreaByTYPEID(string typeID)
{ //=========================================================================================================================


	//log.debug("getAreaOrWarpAreaByName: "+name);

	if (OKString::startsWith(typeID, "AREA.") == false)
	{
		typeID = "AREA." + typeID;
	}


	sp<Area> a = nullptr;
	if (currentState != nullptr)
	{
		if (currentState->areaByTYPEIDHashtable.containsKey(typeID))
		a = currentState->areaByTYPEIDHashtable.get(typeID);
	}

	if (a == nullptr)
	{
		for (int i = 0; i < warpAreaList.size(); i++)
		{
			if (warpAreaList.at(i)->getTYPEIDString() == typeID)
			{
				a = warpAreaList.at(i);
			}
		}
	}

	if (a == nullptr)
	{
		for (int i = 0; i < stateList.size(); i++)
		{
			sp<MapState> s = stateList.at(i);

			if (s->areaByTYPEIDHashtable.containsKey(typeID))
			a = s->areaByTYPEIDHashtable.get(typeID);

			if (a != nullptr)
			{
				break;
			}
		}
	}


	if (a == nullptr)
	{
		log.debug("Could not find Area/WarpArea: getAreaOrWarpAreaByTYPEID() TypeID:" + typeID);
	}


	return a;
}

sp<Door> Map::getDoorByTYPEID(const string& typeID_in)
{ //=========================================================================================================================

	string typeID = typeID_in;
	//log.debug("getDoorByName: "+name);

	if (OKString::startsWith(typeID, "DOOR.") == false)
	{
		typeID = "DOOR." + typeID;
	}

	//doors
	//for(int n=0;n<MapAssetIndex.mapList.size();n++)
	{
		//MapAsset m = MapAssetIndex.mapList.at(n);

		for (int i = 0; i < doorList.size(); i++)
		{
			sp<Door> d = doorList.at(i);

			if (typeID == d->getTYPEIDString())
			{
				return d;
			}
		}
	}

	log.error("Could not find Door: getDoorByTYPEID() TypeID:" + typeID);

	return nullptr;
}

sp<Door> Map::getDoorByName(const string& name_in)
{ //=========================================================================================================================

	string name = name_in;

	//log.debug("getDoorByName: "+name);

	if (OKString::startsWith(name, "DOOR."))
	{
		name = name.substr(name.find(".") + 1);
	}

	//doors
	//for(int n=0;n<MapAssetIndex.mapList.size();n++)
	{
		//MapAsset m = MapAssetIndex.mapList.at(n);

		for (int i = 0; i < doorList.size(); i++)
		{
			sp<Door> d = doorList.at(i);

			if (name == d->getName())
			{
				return d;
			}
		}
	}

	log.error("Could not find Door: getDoorByName(): " + name);

	return nullptr;
}

sp<MapState> Map::getMapStateByName(const string& name)
{ //=========================================================================================================================
	for (int i = 0; i < stateList.size(); i++)
	{
		sp<MapState> mapState = stateList.at(i);

		if (name == mapState->getName())
		{
			return mapState;
		}
	}


	//we didn't find it. make a new one. throw an error.
	log.error("Could not find Map State:" + name + ". This should never happen.");

	//MapState s = ms<MapState>(-1,name);
	//stateList.push_back(s);


	return nullptr;
}

sp<MapState> Map::getMapStateByID(int id)
{ //=========================================================================================================================
	//this should look through the current map mapStateList first
	for (int i = 0; i < stateList.size(); i++)
	{
		sp<MapState> s = stateList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}


	log.error("Could not find State ID:" + to_string(id) + " in currentMap stateList. This should never happen.");
	//then it should look through every map mapStateList, since state ID is guaranteed to be unique.

	//MapState s = ms<MapState>(id,"????");
	//stateList.push_back(s);


	return nullptr;
}

sp<vector<string>> Map::getListOfRandomPointsOfInterestTYPEIDs()
{ //=========================================================================================================================

	sp<vector<string>> areaTYPEIDList;// = ms<ArrayList><string>();


	//areas
	//   java::util::Iterator<sp<Area>> aEnum = currentState->areaByNameHashtable.elements();
	//   while (aEnum->hasMoreElements())
	//   {
	//      sp<Area> a = aEnum->nextElement();

	sp<vector<sp<Area>>>areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		sp<Area> a = areas->at(i);


		if (a->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->push_back(a->getTYPEIDString());
		}
	}


	//warpareas
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		sp<Area> a = warpAreaList.at(i);
		if (a->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->push_back(a->getTYPEIDString());
		}
	}


	//doors
	for (int i = 0; i < doorList.size(); i++)
	{
		sp<Door> d = doorList.at(i);
		if (d->randomPointOfInterestOrExit())
		{
			areaTYPEIDList->push_back(d->getTYPEIDString()); //"DOOR."+d.getTYPEIDString());
		}
	}


	return areaTYPEIDList;
}

void Map::fadeIn()
{ //=========================================================================================================================
	if (alpha < 1.0f)
	{
		alpha += 0.002f * getEngine()->engineTicksPassed();
	}
	if (alpha > 1.0f)
	{
		alpha = 1.0f;
	}
}

void Map::fadeOut()
{ //=========================================================================================================================
	if (alpha > 0.0f)
	{
		alpha -= 0.003f * getEngine()->engineTicksPassed();
	}
	if (alpha < 0.0f)
	{
		alpha = 0.0f;
	}
}

void Map::loadMapState(sp<MapState> s)
{ //===============================================================================================
	currentState = s;
}

void Map::update()
{ //=========================================================================================================================

	
	long long currentTime = System::currentHighResTimer();



	//TODO: the server should always send all events related to a map before sending the map so the client will have the map on load
	//maybe do the same for sprites etc
	//could also look up all areas, entities, doors referenced by the map and send those events too
	//the point of doing this is so i can update map events without changing the md5
	//actually that doesnt matter because i will always get map data from server anyway
	//ok the server should probably fill event structures into maps, areas, entities, doors, etc before sending that data, instead of sending it separately
	//i guess looking at all the references and sending everything in a batch is fine
	//but maybe i could create a new object with the event structure filled in etc
	//and the map data structure itself could contain all its data
	//yeah why am i not doing that?
	//ok i think i know why, it was because i wanted to see all the events in one place in the project file
	//so i should export all events twice, once in the map data along with the event ID, and once in linear order in the project file
	//those should be exported from the same pointer data, so it's always the same
	//but i ignore the event data inside the map data on loading the project file so its easily editable?
	//or maybe i should just have events attached only to its appropriate object like i used to have?

	//ok, export mapdata which contains events, and areas which contain events, and sprites which contain events, and events can contain dialogues, flags, skills, music, sound, etc.
	//when those get loaded on the client it puts them in global arrays and then accesses the global array by ID


	//map, area, entity, door, sprite, cutscene events are held as eventID in those objects and they will load themselves after map is running.
	if (eventsAllLoadedFromServer == false)
	{
		long long startTime = lastLoadEventRequestTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 200)
		{
			lastLoadEventRequestTime = currentTime;
			//load all events

			bool eventsAllLoadedThisTime = false;

			if (mapEventList.size() > 0)
			{
				eventsAllLoadedThisTime = true;
				for (int i = 0; i < mapEventList.size(); i++)
				{
					//int eventID = mapEventList.at(i);
					sp<Event> event = mapEventList.at(i);// getEventManager()->getEventByIDCreateIfNotExist(eventID);
					event->map = shared_from_this();
					if (event->getInitialized_S() == false)
					{
						eventsAllLoadedThisTime = false;
					}
				}
			}

			if (eventsAllLoadedThisTime == true)
			{
				eventsAllLoadedFromServer = true;
			}
		}

		if (eventsAllLoadedFromServer == false)
		{
			return;
		}
	}


	//run load event to determine which map state to load.
	//DONE: need to choose a MapState here.
	//this is decided by the DEFAULT map Event, which should be loaded and run exactly once before the map loads.
	//so we need to go through currentMap's event list, find event type -1, and run that- before the map actually starts running. how to do that?
	//m.currentState = m.stateList.at(0);


	if (currentState == nullptr)
	{

		long long startTime = lastLoadEventRequestTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 200)
		{
			lastLoadEventRequestTime = currentTime;
			for (int i = 0; i < mapEventList.size(); i++)
			{
				sp<Event> event = mapEventList.at(i);// getEventManager()->getEventByIDCreateIfNotExist(mapEventIDList.at(i));
				event->map = shared_from_this();
				if (event->type() == EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD)
				{
					getEventManager()->addToEventQueueIfNotThere(event);
				}
			}
		}
		return;
	}


	fadeIn();


	if (utilityLayersLoaded == false)
	{
		utilityLayersLoaded = true;
		loadUtilityLayers();
	}


	if (startedMissingLightPNGThreads == false)
	{
		startedMissingLightPNGThreads = true;
		startThreadsForMissingLightPNGs();
	}
	else
	{
		if (allLightsLoadedAsTextures == false)
		{
			allLightsLoadedAsTextures = loadLightTexturesFromCachePNGs();
		}
	}


	if (sortedLightsLayers.empty())
	{
		sortLightLayers();
	}


	//load map entities into entitymanager
	if (addedEntitiesAndCharactersFromCurrentStateToActiveEntityList == false)
	{
		addEntitiesAndCharactersFromCurrentStateToActiveEntityList();
		addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = true;
	}


	//don't hammer eventList
	long long startTime = lastLoadEventRequestTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 200)
	{
		lastLoadEventRequestTime = currentTime;
		//run all events, **this will also run post-load events for this map, which stop executing after one loop.
		for (int i = 0; i < mapEventList.size(); i++)
		{
			sp<Event> event = mapEventList.at(i);// getEventManager()->getEventByIDCreateIfNotExist(mapEventIDList.at(i));
			event->map = this;
			if (event->type() != EventData::TYPE_MAP_DONT_RUN_UNTIL_CALLED && event->type() != EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD)
			{
				getEventManager()->addToEventQueueIfNotThere(event);
			}
		}
	}


	updateEntities();
	updateDoors();

	updateAreas();
	updateWarpAreas();

	//run();

	updateLights();

	zOrderEntities();


	if (startedMissingChunkPNGThreads == false)
	{
		startedMissingChunkPNGThreads = true;
		startThreadsForMissingChunkPNGs();
	}
	else
	{
		if (allChunkPNGsLoadedAsTextures == false || MapManager::loadTexturesOnDemand == true)
		{
			allChunkPNGsLoadedAsTextures = loadChunkTexturesFromCachePNGs();
		}
	}


	//else
	/*
	if(miniMapGenerated==false)
	{
	   miniMapGenerated=true;
	            
	   drawMiniMapIntoFBO();
	            
	}
	else
	*/

	if (MapManager::loadTexturesOnDemand == true && startedMissingChunkPNGThreads == true)
	{
		if (MapManager::generateHQ2XChunks == true)
		{
			if (startedMissingHQ2XChunkPNGThreads == false)
			{
				startedMissingHQ2XChunkPNGThreads = true;
				startThreadsForMissingHQ2XChunkPNGs();
			}
		}
	}


	if (allChunkPNGsLoadedAsTextures == true)
	{
		if (MapManager::generateHQ2XChunks == true)
		{
			//check here to see if we already loaded all hq2x textures while loading regular textures, no need to start threads if we have.
			//i don't really have to do this, but why start a thread pool if we don't have to?
			if (allHQ2XChunkPNGsLoadedAsTextures == false)
			{
				bool tempAllHQ2XChunkPNGsLoaded = true;

				for (int chunkY = 0; chunkY < chunksHeight; chunkY++)
				{
					for (int chunkX = 0; chunkX < chunksWidth; chunkX++)
					{
						for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
						{
							int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

							if ((*usingHQ2XTexture)[chunkIndex] == false)
							{
								tempAllHQ2XChunkPNGsLoaded = false;
							}
						}
					}
				}
				if (tempAllHQ2XChunkPNGsLoaded == true)
				{
					allHQ2XChunkPNGsLoadedAsTextures = true;

					if (tilesetIntArray != nullptr)
					{
						//delete tilesetIntArray;
						tilesetIntArray = nullptr;
					}

					if (paletteRGBByteArray != nullptr)
					{
						//delete paletteRGBByteArray;
						paletteRGBByteArray = nullptr;
					}

				}
			}


			//if we still havent loaded them all, they must not exist.
			//start the threads to create them and load them as the threads finish
			if (allHQ2XChunkPNGsLoadedAsTextures == false)
			{
				if (startedMissingHQ2XChunkPNGThreads == false)
				{
					//TODO: manage cpu usage of threads, make sure they don't lower the framerate, even on slow computers.

					startedMissingHQ2XChunkPNGThreads = true;
					startThreadsForMissingHQ2XChunkPNGs();
				}
				else
				{
					allHQ2XChunkPNGsLoadedAsTextures = loadHQ2XTexturesFromCachePNGs();
				}
			}
		}
		else
		{
			if (tilesetIntArray != nullptr)
			{
				//delete tilesetIntArray;
				tilesetIntArray = nullptr;
			}

			if (paletteRGBByteArray != nullptr)
			{
				//delete paletteRGBByteArray;
				paletteRGBByteArray = nullptr;
			}

		}
	}

	//nice percentage progress of chunk/light/hq2x PNG generation and chunk texture loading
	updateLoadingStatus();


//	if(
//	      MapManager::useThreads==true&&
//	      generatePNGThreadPool!=nullptr&&
//	      //startedMissingLightPNGThreads==true&&
//	      startedMissingChunkPNGThreads==true&&
//	      //startedMissingHQ2XChunkPNGThreads==true
//	)
//	{
//	   if(generatePNGThreadPool.isShutdown()==false)
//	   {
//		   generatePNGThreadPool.shutdown();
//	      log.debug("generatePNGExecutorService Shut Down");
//	   }
//	}
}

void Map::updateLoadingStatus()
{ //=========================================================================================================================
	if (maxHq2xChunkPNGThreadsCreated > 0)
	{
		if (hq2xChunkPNGThreadsDebugText == nullptr)
		{
			hq2xChunkPNGThreadsDebugText = Main::console->debug("hq2xChunkPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxHq2xChunkPNGThreadsCreated - hq2xChunkPNGThreadsCreated) / (float)(maxHq2xChunkPNGThreadsCreated)) * 100.0f;
			hq2xChunkPNGThreadsDebugText->text = "HQ2X Chunk PNG Threads: " + to_string(maxHq2xChunkPNGThreadsCreated - hq2xChunkPNGThreadsCreated) + " / " + to_string(maxHq2xChunkPNGThreadsCreated) + " ( " + to_string(percent) + " % )";
		}

		if (hq2xChunkPNGThreadsCreated == 0)
		{
			maxHq2xChunkPNGThreadsCreated = 0;
			hq2xChunkPNGThreadsDebugText->ticks = 1000;
			hq2xChunkPNGThreadsDebugText = nullptr;
		}
	}


	if (maxChunkPNGThreadsCreated > 0)
	{
		if (chunkPNGThreadsDebugText == nullptr)
		{
			chunkPNGThreadsDebugText = Main::console->debug("chunkPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxChunkPNGThreadsCreated - chunkPNGThreadsCreated) / (float)(maxChunkPNGThreadsCreated)) * 100.0f;
			chunkPNGThreadsDebugText->text = "1X Chunk PNG Threads: " + to_string(maxChunkPNGThreadsCreated - chunkPNGThreadsCreated) + " / " + to_string(maxChunkPNGThreadsCreated) + " ( " + to_string(percent) + " % )";
		}

		if (chunkPNGThreadsCreated == 0)
		{
			maxChunkPNGThreadsCreated = 0;
			chunkPNGThreadsDebugText->ticks = 1000;
			chunkPNGThreadsDebugText = nullptr;
		}
	}


	if (maxLightPNGThreadsCreated > 0)
	{
		if (lightPNGThreadsDebugText == nullptr)
		{
			lightPNGThreadsDebugText = Main::console->debug("lightPNGThreadsDebugText");
		}


		{
			float percent = ((float)(maxLightPNGThreadsCreated - lightPNGThreadsCreated) / (float)(maxLightPNGThreadsCreated)) * 100.0f;
			lightPNGThreadsDebugText->text = "Light PNG Threads: " + to_string(maxLightPNGThreadsCreated - lightPNGThreadsCreated) + " / " + to_string(maxLightPNGThreadsCreated) + " ( " + to_string(percent) + " % )";
		}

		if (lightPNGThreadsCreated == 0)
		{
			maxLightPNGThreadsCreated = 0;
			lightPNGThreadsDebugText->ticks = 1000;
			lightPNGThreadsDebugText = nullptr;
		}
	}


	int chunkTexturesLoaded = getChunkTexturesLoaded_S();
	if (chunkTexturesLoaded > 0 && MapManager::loadTexturesOnDemand == false)
	{
		int totalChunkTextures = (chunksWidth * chunksHeight * 2);

		if (texturesLoadedDebugText == nullptr)
		{
			texturesLoadedDebugText = Main::console->debug("texturesLoadedDebugText");
		}

		if (generatingAreaNotification == nullptr)
		{
			generatingAreaNotification = ms<Notification>(getEngine(), "Loading Area...");
		}


		{
			float percent = ((float)(chunkTexturesLoaded) / (float)(totalChunkTextures)) * 100.0f;
			texturesLoadedDebugText->text = "Textures Loaded: " + to_string(chunkTexturesLoaded) + " / " + to_string(totalChunkTextures) + " ( " + to_string(percent) + " % )";
			generatingAreaNotification->progress = percent / 100.0f;
		}

		if (chunkTexturesLoaded == totalChunkTextures)
		{
			setChunkTexturesLoaded_S(0);
			texturesLoadedDebugText->ticks = 1000;
			texturesLoadedDebugText = nullptr;

			if (generatingAreaNotification != nullptr)
			{
				generatingAreaNotification = generatingAreaNotification->fadeOutAndDelete();
			}
		}
	}

	if (MapManager::loadTexturesOnDemand == true)
	{
		if (generatingAreaNotification != nullptr)
		{
			generatingAreaNotification = generatingAreaNotification->fadeOutAndDelete();
		}
	}
}

void Map::updateEntities()
{ //=========================================================================================================================

	//for all entities update
	for (int n = 0; n < activeEntityList.size(); n++)
	{
		sp<Entity> e = activeEntityList.at(n);

		e->update();
	}
}

void Map::updateDoors()
{ //=========================================================================================================================

	for (int n = 0; n < doorList.size(); n++)
	{
		sp<Door> e = doorList.at(n);

		e->update();
	}
}

void Map::updateAreas()
{ //=========================================================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//		Enumeration<Area> aEnum = currentState.areaHashtable.elements();
	//		while(aEnum.hasMoreElements())
	//		{
	//			Area a = aEnum.nextElement();
	//			a.update();
	//		}

	for (int i = 0; i < (int)currentState->areaList.size(); i++)
	{
		sp<Area> a = currentState->areaList.at(i);
		a->update();
	}
}

void Map::updateWarpAreas()
{ //=========================================================================================================================
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.at(i).mapAsset==currentMap)
			warpAreaList.at(i)->update();
		}
	}
}

void Map::updateLights()
{ //=========================================================================================================================

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		currentState->lightList.at(i)->update();
	}
}

void Map::zOrderEntities()
{ //=========================================================================================================================


	drawList.clear();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		sp<Entity> e = activeEntityList.at(i);

		//decide which ones need rendering
		//add to new linked list of on-screen entities to z-order
		if (e->shouldDraw())
		{
			if (drawList.contains(e) == false)
			{
				drawList.push_back(e);
			}
		}
	}

	for (int i = 0; i < doorList.size(); i++)
	{
		sp<Door> e = doorList.at(i);

		//decide which ones need rendering
		//add to new linked list of on-screen entities to z-order
		if (e->shouldDraw())
		{
			if (drawList.contains(e) == false)
			{
				drawList.push_back(e);
			}
		}
	}

	if (getCurrentMap() != nullptr && getCurrentMap() == this)
	{
		if (getClientGameEngine() != nullptr && getClientGameEngine()->playerExistsInMap == false)
		{
			if (getPlayer() != nullptr && getPlayer()->shouldDraw())
			{
				if ((drawList.contains(getPlayer())) == false)
				{
					drawList.push_back(getPlayer());
				}
			}
		}
	}


	if (dynamic_cast<sp<BGClientEngine>>(getEngine()) != nullptr)
	{
		//add friends, they are not added to any entityList
		for (int i = 0; i < (int)getClientGameEngine()->friendManager->friendCharacters.size(); i++)
		{
			sp<FriendCharacter> f = getFriendManager()->friendCharacters.at(i);

			if (f->mapName == getName())
			{
				if (f->shouldDraw())
				{
					if (drawList.contains(f) == false)
					{
						drawList.push_back(f);
					}
				}
			}
		}
	}


	//z-order all entities

	//now we want to make a new list of all the on-screen entities, z-ordered starting at the top of the screen and working to the bottom
	//for each entity in the drawList, find the topmost one and add it to the new list, then remove it from the drawList


	zList.clear();

	while (drawList.size() != 0)
	{
		sp<Entity> highestOnScreenEntity = nullptr;

		for (int n = 0; n < drawList.size(); n++)
		{
			sp<Entity> e = drawList.at(n);

			//store topmost entity on screen
			//check for non-zordering entities, entities always on top, entities always on bottom here.


			if (e->getAlwaysOnBottom())
			{
				highestOnScreenEntity = e;
				break;
			}

			if (highestOnScreenEntity == nullptr || (e->getAlwaysOnTop() == false && (e->getMiddleY() < highestOnScreenEntity->getMiddleY() || (highestOnScreenEntity->getAboveWhenEqual() && (int)(floor(highestOnScreenEntity->getBottom())) == (int)(floor(e->getBottom()))))))
			{
				highestOnScreenEntity = e;
			}
		}

		drawList.remove(highestOnScreenEntity);
		zList.push_back(highestOnScreenEntity);
	}


	//		log.debug("---------------------");
	//
	//		for(int i=0;i<zList.size();i++)
	//		{
	//			Entity e = zList.at(i);
	//			log.debug(e.getSpriteName());
	//		}


	//TODO: if any part of the feet are under a tile on the above layer, dont draw the shadow
}

void Map::sortLightLayers()
{ //=========================================================================================================================


	//splarka wrote this in javascript and i ported, rewrote, and optimised it


	//for all lights
	//if light is not drawn

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		sp<Light> l = currentState->lightList.at(i);
		//if light is not drawn
		if (l->sortingState != Light::DRAWN)
		{
			sp<vector<sp<Light>>> thisLayerList;// = ms<ArrayList><sp<Light>>();

			//light is drawing
			l->sortingState = Light::DRAWING;

			//for all lights from this light to the end
			for (int a = i + 1; a < (int)currentState->lightList.size(); a++)
			{
				sp<Light> compareLight = currentState->lightList.at(a);

				//if that light isn't already drawn
				if (compareLight->sortingState != Light::DRAWN)
				{
					//for all lights
					for (int b = 0; b < (int)currentState->lightList.size(); b++)
					{
						sp<Light> overlapLight = currentState->lightList.at(b);

						//if this light isn't
						if (a != b && overlapLight->sortingState == Light::DRAWING)
						{
							float left1 = compareLight->getLeft();
							float right1 = compareLight->getRight();
							float top1 = compareLight->getTop();
							float bottom1 = compareLight->getBottom();

							float left2 = overlapLight->getLeft();
							float right2 = overlapLight->getRight();
							float top2 = overlapLight->getTop();
							float bottom2 = overlapLight->getBottom();

							if ((left1 < right2) && (right1 > left2) && (top1 < bottom2) && (bottom1 > top2))
							{
								compareLight->sortingState = Light::OVERLAPS_SOMETHING;
							}
						}
					}
					if (compareLight->sortingState != Light::OVERLAPS_SOMETHING)
					{
						compareLight->sortingState = Light::DRAWING;
					}
					else
					{
						compareLight->sortingState = Light::NOT_DRAWN;
					}
				}
			}


			for (int d = 0; d < (int)currentState->lightList.size(); d++)
			{
				sp<Light> drawLight = currentState->lightList.at(d);
				if (drawLight->sortingState == Light::DRAWING)
				{
					thisLayerList->push_back(drawLight);

					//draw light
					drawLight->sortingState = Light::DRAWN;
				}
			}

			//log.debug("Light layer "+layer);
			//layer++;
			sortedLightsLayers.push_back(thisLayerList.get());
		}
	}
}

void Map::render(RenderOrder renderOrder)
{ //=========================================================================================================================
	render(renderOrder, defaultDisableClip, defaultDisableFloorOffset);
}

void Map::render(RenderOrder renderOrder, bool disableClip)
{ //=========================================================================================================================
	render(renderOrder, disableClip, defaultDisableFloorOffset);
}

void Map::render(RenderOrder renderOrder, bool disableClip, bool disableFloorOffset)
{ //=========================================================================================================================

	if (renderOrder == RenderOrder::GROUND && getEngine()->underLayerEnabled == false)
	{
		return;
	}
	if (renderOrder == RenderOrder::ABOVE && getEngine()->overLayerEnabled == false)
	{
		return;
	}

	//only allow above or ground
	if (renderOrder != RenderOrder::GROUND && renderOrder != RenderOrder::ABOVE)
	{
		return;
	}


	int layerIndex = 0;
	if (renderOrder == RenderOrder::GROUND)
	{
		layerIndex = 0;
	}
	if (renderOrder == RenderOrder::ABOVE)
	{
		layerIndex = 1;
	}


	sp<OKTexture> texture = nullptr;

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int filter = GLUtils::FILTER_LINEAR;
	if (zoom == 1.0f || zoom >= 1.5f || zoom == 0.5f)
	{
		filter = GLUtils::FILTER_NEAREST;
	}




	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;


	float x0 = 0;
	float x1 = 0;
	float y0 = 0;
	float y1 = 0;


	//for each texture chunk starting at screen-chunksize*zoom
	//if texture isn't null, draw it at the correct place.


	//start at screen - chunksize

	int startChunkX = ((int)(floor(((mapCamX()) / (chunkSizePixelsHQ2X)))));
	int startChunkY = ((int)(floor(((mapCamY()) / (chunkSizePixelsHQ2X)))));

	if (startChunkX < 0)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0)
	{
		startChunkY = 0;
	}

	int screenChunkWidth = ((int)(floor(sw / (chunkSizePixelsHQ2X * zoom)))) + 1;
	int screenChunkHeight = ((int)(floor(sh / (chunkSizePixelsHQ2X * zoom)))) + 1;


	//for drawing the lastMap, we can't clip based on the camera so we have to draw the whole thing.
	if (disableClip == true)
	{
		startChunkX = 0;
		startChunkY = 0;
		screenChunkWidth = chunksWidth;
		screenChunkHeight = chunksHeight;
	}

	for (int chunkY = startChunkY; chunkY <= startChunkY + screenChunkHeight && chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = startChunkX; chunkX <= startChunkX + screenChunkWidth && chunkX < chunksWidth; chunkX++)
		{
			//old way, floor and ceil was good but had small line artifacts when zooming
			//if i make them all floor, the line artifacts are worse, same if i make ceil round
			//if i remove the floor and ceil, the grass is "shimmery" and vertical lines are clippy

			//float chunkMapScreenX = (float) Math.floor(map_screen_x*drawScale+(chunkX * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenY = (float) Math.floor(map_screen_y*drawScale+(chunkY * chunkSizePixelsHQ2X*drawScale));
			//float chunkMapScreenX2 = (float) Math.ceil(chunkMapScreenX+chunkSizePixelsHQ2X*drawScale);
			//float chunkMapScreenY2 = (float) Math.ceil(chunkMapScreenY+chunkSizePixelsHQ2X*drawScale);

			//this seems to work the best:
			//i am only flooring the map screen coords, then using that as an offset for all the other values.
			//this has no lines in between zoom levels
			float chunkMapScreenX = (float)(floor(screenX() * zoom)) + (chunkX * chunkSizePixelsHQ2X * zoom);
			float chunkMapScreenY = (float)(floor(screenY() * zoom)) + (chunkY * chunkSizePixelsHQ2X * zoom);

			if (disableFloorOffset)
			{
				chunkMapScreenX = (float)(screenX() * zoom) + (chunkX * chunkSizePixelsHQ2X * zoom);
				chunkMapScreenY = (float)(screenY() * zoom) + (chunkY * chunkSizePixelsHQ2X * zoom);
			}

			float chunkMapScreenX2 = (float)(chunkMapScreenX + chunkSizePixelsHQ2X * zoom);
			float chunkMapScreenY2 = (float)(chunkMapScreenY + chunkSizePixelsHQ2X * zoom);


			if (chunkMapScreenX >= sw || chunkMapScreenX2 < 0 || chunkMapScreenY >= sh || chunkMapScreenY2 < 0) //off the top - off the bottom
			{
				continue;
			}

			x0 = (chunkMapScreenX);
			y0 = (chunkMapScreenY);

			x1 = (chunkMapScreenX2);
			y1 = (chunkMapScreenY2);


			int chunkIndex = (chunksWidth * chunksHeight * layerIndex) + ((chunksWidth * chunkY) + chunkX);

			texture = getChunkTexture(chunkIndex);

			if (texture != nullptr && texture != GLUtils::blankTexture)
			{
				GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, filter);
			}
		}
	}


	//OLD WAY, SINGLE ROOM GRAPHICS

	//this only renders the clip that needs it


	/*
	      //if the map is offscreen, don't draw anything
	
	      if((map_screen_x*G.zoom)+(tw*G.zoom)<0)return;
	      if((map_screen_y*G.zoom)+(th*G.zoom)<0)return;
	
	      if((map_screen_x*G.zoom)>=sw)return;//this could still be on the screen :\
	      if((map_screen_y*G.zoom)>=sh)return;
	
	
	      if((map_screen_x*G.zoom)<0)
	      {
	         //tx0 is greater than 0
	         tx0 = (float)(0-(map_screen_x*G.zoom))/(float)(tw*G.zoom);
	         //x0 is 0
	         x0=0;
	      }
	
	      if(map_screen_x*G.zoom>=0)
	      {
	         //tx0 is 0
	         tx0=0.0f;
	         //x0 is map_cam_x/sw
	         x0=(int)(map_screen_x*G.zoom);
	      }
	
	      //if map extends off screen to the right
	      if((map_screen_x*G.zoom)+(tw*G.zoom)>=sw)
	      {
	         tx1=(float)(sw-(map_screen_x*G.zoom))/(float)(tw*G.zoom);
	
	         x1=sw;
	      }
	      else
	      {
	         tx1 = 1.0f;
	         x1 = (int)(map_screen_x*G.zoom)+(int)(tw*G.zoom);
	      }
	
	
	
	
	      if((map_screen_y*G.zoom)<0)
	      {
	         //ty0 is greater than 0
	         ty0 = (float)(0-(map_screen_y*G.zoom))/(float)(th*G.zoom);
	         //y0 is 0
	         y0=0;
	      }
	
	      if((map_screen_y*G.zoom)>=0)
	      {
	         //ty0 is 0
	         ty0=0.0f;
	         //y0 is map_cam_y
	         y0=(int)(map_screen_y*G.zoom);
	      }
	
	      //if map extends off screen to the bottom
	      if((map_screen_y*G.zoom)+(th*G.zoom)>=sh)
	      {
	         ty1=(float)(sh-(map_screen_y*G.zoom))/(float)(th*G.zoom);
	         y1=sh;
	      }
	      else
	      {
	         ty1 = 1.0f;
	         y1 = (int)(map_screen_y*G.zoom)+(int)(th*G.zoom);
	      }
	
	
	      */


	//this renders the whole thing and lets the card clip it
	/*
	float tx0 = 0.0f;// = (float)cam_x/(float)tw;
	float tx1 = 1.0f;//(float)(cam_x+ssx)/(float)tw;
	            
	float ty0 = 0.0f;
	float ty1 = 1.0f;
	            
	            
	int x0 = (int)(map_screen_x*G.zoom);
	int x1 = (int)((map_screen_x*G.zoom)+(tw*G.zoom));
	int y0 = (int)(map_screen_y*G.zoom);
	int y1 = (int)((map_screen_y*G.zoom)+(th*G.zoom));
	            
	            
	            
	            
	GL.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,0);
	            
	*/

	/*
	texture.bind();
	            
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	            
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	            
	            
	glBegin(GL_QUADS);
	            
	   //TL (0,0)
	   glTexCoord2f(tx0,ty0);
	   glVertex2i(x0,y0);
	            
	   //TR (1,0)
	   glTexCoord2f(tx1,ty0);
	   glVertex2i(x1,y0);
	            
	   //BR (1,1)
	   glTexCoord2f(tx1,ty1);
	   glVertex2i(x1,y1);
	            
	   //BL (0,1)
	   glTexCoord2f(tx0,ty1);
	   glVertex2i(x0,y1);
	            
	glEnd();
	*/
}

void Map::renderEntities(RenderOrder layer)
{ //=========================================================================================================================

	if (layer == RenderOrder::GROUND)
	{
		renderAreaActionIcons();
	}

	if (getEngine()->entityLayerEnabled)
	{
		//for all entities, render as needed, in proper order

		for (int n = 0; n < zList.size(); n++)
		{
			sp<Entity> e = zList.at(n);


			if (layer == RenderOrder::SPRITE_DEBUG_OUTLINES)
			{
				e->renderDebugBoxes();
			}
			else if (layer == RenderOrder::SPRITE_DEBUG_INFO)
			{
				e->renderDebugInfo();
			}
			else if (e->getRenderOrder() == layer)
			{
				e->render(alpha);
			}
		}
	}
}

void Map::renderAllLightsUnsorted()
{ //=========================================================================================================================

	if (getEngine()->lightsLayerEnabled == false)
	{
		return;
	}

	if (currentState != nullptr)
	{
		for (int i = 0; i < (int)currentState->lightList.size(); i++)
		{
			sp<Light> l = currentState->lightList.at(i);
			l->renderLight();
		}
	}
}

void Map::renderAreaActionIcons()
{ //=========================================================================================================================


	//TODO: go through all events currently running. each event will know whether it needs an action icon or not.

	if (currentState == nullptr)
	{
		return;
	}

	//areas
	//   java::util::Iterator<sp<Area>> aEnum = currentState->areaByNameHashtable.elements();
	//   while (aEnum->hasMoreElements())
	//   {
	//      sp<Area> a = aEnum->nextElement();

	sp<vector<sp<Area>>>areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		sp<Area> a = areas->at(i);

		//if(a.isAnAction)
		a->renderActionIcon();
	}


	//warpareas
	for (int i = 0; i < warpAreaList.size(); i++)
	{
		sp<Area> a = warpAreaList.at(i);
		//if(a.isAnAction)
		a->renderActionIcon();
	}
}

void Map::renderChunkBoxes()
{ //=========================================================================================================================


	//for each tile on screen
	//go through getHit detection


	//glcolor
	//glbegin

	//gl add quads

	//gl end
	glColor4f(1.0f, 0.5f, 0.0f, 0.4f);
	glBegin(GL_LINES);

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int startChunkX = ((int)(floor(((mapCamX()) / (chunkSizePixelsHQ2X)))));
	int startChunkY = ((int)(floor(((mapCamY()) / (chunkSizePixelsHQ2X)))));

	if (startChunkX < 0)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0)
	{
		startChunkY = 0;
	}

	int screenChunkWidth = ((int)(floor(sw / (chunkSizePixelsHQ2X * zoom)))) + 1;
	int screenChunkHeight = ((int)(floor(sh / (chunkSizePixelsHQ2X * zoom)))) + 1;


	for (int chunkY = startChunkY; chunkY <= startChunkY + screenChunkHeight && chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = startChunkX; chunkX <= startChunkX + screenChunkWidth && chunkX < chunksWidth; chunkX++)
		{
			float chunkMapScreenX = (float)(floor(screenX() * zoom + (chunkX * chunkSizePixelsHQ2X * zoom)));
			float chunkMapScreenY = (float)(floor(screenY() * zoom + (chunkY * chunkSizePixelsHQ2X * zoom)));
			float chunkMapScreenX2 = (float)(ceil(chunkMapScreenX + chunkSizePixelsHQ2X * zoom));
			float chunkMapScreenY2 = (float)(ceil(chunkMapScreenY + chunkSizePixelsHQ2X * zoom));


			//left
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);

			//right
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);

			//top
			glVertex2f(chunkMapScreenX, chunkMapScreenY);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY);

			//bottom
			glVertex2f(chunkMapScreenX, chunkMapScreenY2);
			glVertex2f(chunkMapScreenX2, chunkMapScreenY2);
		}
	}


	glEnd();
}

void Map::renderHitLayer()
{ //=========================================================================================================================
	glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
	glBegin(GL_QUADS);

	float sw = (float)getEngine()->getWidth();
	float sh = (float)getEngine()->getHeight();

	float zoom = getCameraman()->getZoom();

	int startTileX = ((int)(floor(((mapCamX()) / (16)))));
	int startTileY = ((int)(floor(((mapCamY()) / (16)))));

	if (startTileX < 0)
	{
		startTileX = 0;
	}
	if (startTileY < 0)
	{
		startTileY = 0;
	}

	int screenTileWidth = ((int)(floor(sw / (16 * zoom)))) + 1;
	int screenTileHeight = ((int)(floor(sh / (16 * zoom)))) + 1;


	for (int tileY = startTileY; tileY <= startTileY + screenTileHeight && tileY < getHeightTiles1X(); tileY++)
	{
		for (int tileX = startTileX; tileX <= startTileX + screenTileWidth && tileX < getWidthTiles1X(); tileX++)
		{
			if (getHitLayerValueAtXYPixels((float)(tileX) * 16, (float)(tileY) * 16) == false)
			{
				continue;
			}

			float tileMapScreenX = (float)(floor(screenX() * zoom + (tileX * 16 * zoom)));
			float tileMapScreenY = (float)(floor(screenY() * zoom + (tileY * 16 * zoom)));
			float tileMapScreenX2 = (float)(ceil(tileMapScreenX + 16 * zoom));
			float tileMapScreenY2 = (float)(ceil(tileMapScreenY + 16 * zoom));


			glVertex2f(tileMapScreenX, tileMapScreenY);
			glVertex2f(tileMapScreenX, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY2);
			glVertex2f(tileMapScreenX2, tileMapScreenY);
		}
	}


	glEnd();
}

void Map::renderLightBoxes()
{ //===============================================================================================
	//light boxes
	for (int i = 0; i < sortedLightsLayers.size(); i++)
	{
		sp<vector<sp<Light>>> thisLayer = ms<vector<sp<Light>>>(sortedLightsLayers.at(i));
		for (int n = 0; n < thisLayer->size(); n++)
		{
			thisLayer->at(n)->renderDebugBoxes();
		}
	}
}

void Map::renderAreaDebugBoxes()
{ //===============================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//   java::util::Iterator<sp<Area>> aEnum = currentState->areaByNameHashtable.elements();
	//   //areas
	//   while (aEnum->hasMoreElements())
	//   {
	//      sp<Area> a = aEnum->nextElement();

	sp<vector<sp<Area>>>areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		sp<Area> a = areas->at(i);



		a->renderDebugBoxes();
		//a.renderDebugInfo();
	}
}

void Map::renderAreaDebugInfo()
{ //===============================================================================================

	if (currentState == nullptr)
	{
		return;
	}

	//TODO: make these a manager in mapmanager
	//   java::util::Iterator<sp<Area>> aEnum = currentState->areaByNameHashtable.elements();
	//   //areas
	//   while (aEnum->hasMoreElements())
	//   {
	//      sp<Area> a = aEnum->nextElement();

	sp<vector<sp<Area>>>areas = currentState->areaByNameHashtable.getAllValues();
	for (int i = 0; i<areas->size(); i++)
	{
		sp<Area> a = areas->at(i);


		//a.renderDebugBoxes();
		a->renderDebugInfo();
	}
}

void Map::renderWarpAreaDebugBoxes()
{ //=========================================================================================================================

	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.at(i).mapAsset==currentMap)
			warpAreaList.at(i)->renderDebugBoxes();
		}
	}
}

void Map::renderWarpAreaDebugInfo()
{ //=========================================================================================================================

	for (int i = 0; i < warpAreaList.size(); i++)
	{
		{
			//if(warpAreaList.at(i).mapAsset==currentMap)
			warpAreaList.at(i)->renderDebugInfo();
		}
	}
}

void Map::loadUtilityLayers()
{ //=========================================================================================================================


	/*public String getGroundShaderMD5 = null;
	public String getCameraBoundsMD5 = null;
	public String getHitBoundsMD5 = null;
	public String getLightMaskMD5 = null;*/

	//-----------------------------------
	//load hitlayer
	//-----------------------------------
	//hitLayer = BufferUtils.createIntBuffer((mapWidth/8) * (mapHeight/8));

	if (hitLayer == nullptr)
	{
		hitLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist("" + getHitBoundsMD5());
		/*hitLayer = new byte[getWidthTiles1X * getHeightTiles1X];
		         
		BufferedInputStream hitBin = ms<BufferedInputStream>(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getHitBoundsMD5));
		         
		try
		{
		   hitBin.read(hitLayer);
		   hitBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}


	//-----------------------------------
	//load fx layer
	//-----------------------------------
	if (cameraLayer == nullptr)
	{
		cameraLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist("" + getCameraBoundsMD5());

		//			FileUtils.downloadSmallFileToCacheIfNotExist(""+getCameraBoundsMD5());
		//
		//
		//			cameraLayer = new byte[getWidthTiles1X() * getHeightTiles1X()];
		//			BufferedInputStream fxBin = ms<BufferedInputStream>(FileUtils::getResourceAsStream(""+FileUtils.cacheDir+getCameraBoundsMD5()));
		//
		//			//TODO: in map editor, output this as byte array instead of int array, then i don't have to skip every other byte here
		//			try
		//			{
		//				int data=fxBin.read();
		//				int notdata=fxBin.read();
		//				int i=0;
		//
		//				while(data!=-1||notdata!=-1)
		//				{
		//					cameraLayer->get(i)=(byte)data;
		//					i++;
		//					data=fxBin.read();
		//					notdata=fxBin.read();
		//				}
		//
		//				fxBin.close();
		//			}
		//			catch (IOException e)
		//			{
		//				e.printStackTrace();
		//			}
	}


	//-----------------------------------
	//load ground shader layer
	//-----------------------------------

	if (groundShaderLayer == nullptr)
	{
		groundShaderLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist("" + getGroundShaderMD5());

		/*groundShaderLayer = new int[getWidthTiles1X * getHeightTiles1X];
		BufferedInputStream shaderBin = ms<BufferedInputStream>(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getGroundShaderMD5));
		         
		try
		{
		   int sbyte1=shaderBin.read();
		   int sbyte2=shaderBin.read();
		   int i=0;
		         
		   while(sbyte1!=-1||sbyte2!=-1)
		   {
		         
		      int ubyte1 = sbyte1 & 0xFF;
		      int ubyte2 = sbyte2 & 0xFF;
		         
		      int result = (ubyte2<<8) + ubyte1;
		         
		      groundShaderLayer->get(i)=result;
		      i++;
		      sbyte1=shaderBin.read();
		      sbyte2=shaderBin.read();
		   }
		         
		   shaderBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}


	//-----------------------------------
	//load light mask layer
	//-----------------------------------
	if (groundShaderLayer == nullptr)
	{
		groundShaderLayer = FileUtils::loadIntFileFromCacheOrDownloadIfNotExist("" + getLightMaskMD5());

		/*lightMaskLayer = new int[getWidthTiles1X * getHeightTiles1X];
		BufferedInputStream lightMaskBin = ms<BufferedInputStream>(FileUtils::getResourceAsStream(""+CacheManager.cacheDir+getLightMaskMD5));
		         
		try
		{
		   int sbyte1=lightMaskBin.read();
		   int sbyte2=lightMaskBin.read();
		   int i=0;
		         
		   while(sbyte1!=-1||sbyte2!=-1)
		   {
		         
		      int ubyte1 = sbyte1 & 0xFF;
		      int ubyte2 = sbyte2 & 0xFF;
		         
		      int result = (ubyte2<<8) + ubyte1;
		         
		      lightMaskLayer->get(i)=result;
		      i++;
		      sbyte1=lightMaskBin.read();
		      sbyte2=lightMaskBin.read();
		   }
		         
		   lightMaskBin.close();
		}
		catch (IOException e)
		{
		   e.printStackTrace();
		}*/
	}
}

void Map::saveDataToCache(sp<IntArray> intArrayAllLayers, sp<IntArray> tiles, sp<ByteArray> pal)
{ //=========================================================================================================================

	//I should just save each layer as the MD5 in the cache folder
	//then set the appropriate md5 name in data

	for (int l = 0; l < MapData::layers; l++)
	{
		if (MapData::isTileLayer(l))
		{
			int index = (getWidthTiles1X() * getHeightTiles1X() * l);
			sp<IntArray> layer = ms<IntArray>(getWidthTiles1X() * getHeightTiles1X());
			for (int i = 0; i < getWidthTiles1X() * getHeightTiles1X(); i++)
			{
				layer->data()[i] = intArrayAllLayers->data()[index + i];
			}

			//save to cache folder as md5 name
			sp<ByteArray> byteArray = FileUtils::getByteArrayFromIntArray(layer);
			string md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
			FileUtils::saveByteArrayToCache(byteArray, md5FileName);

			//set layermd5 name to md5
			if (l == MapData::MAP_GROUND_LAYER)
			{
				setGroundLayerMD5(md5FileName);
			}
			if (l == MapData::MAP_GROUND_DETAIL_LAYER)
			{
				setGroundObjectsMD5(md5FileName);
			}
			if (l == MapData::MAP_GROUND_SHADOW_LAYER)
			{
				setGroundShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_LAYER)
			{
				setObjectsMD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_DETAIL_LAYER)
			{
				setObjects2MD5(md5FileName);
			}
			if (l == MapData::MAP_OBJECT_SHADOW_LAYER)
			{
				setObjectShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_ABOVE_LAYER)
			{
				setAboveMD5(md5FileName);
			}
			if (l == MapData::MAP_ABOVE_DETAIL_LAYER)
			{
				setAbove2MD5(md5FileName);
			}
			if (l == MapData::MAP_SPRITE_SHADOW_LAYER)
			{
				setSpriteShadowMD5(md5FileName);
			}
			if (l == MapData::MAP_SHADER_LAYER)
			{
				setGroundShaderMD5(md5FileName);
			}
			if (l == MapData::MAP_LIGHT_MASK_LAYER)
			{
				setLightMaskMD5(md5FileName);
			}
			if (l == MapData::MAP_CAMERA_BOUNDS_LAYER)
			{
				setCameraBoundsMD5(md5FileName);
			}
			if (l == MapData::MAP_HIT_LAYER)
			{
				setHitBoundsMD5(md5FileName);
			}
		}
	}
	//save tiles
	sp<ByteArray> byteArray = FileUtils::getByteArrayFromIntArray(tiles);
	string md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
	FileUtils::saveByteArrayToCache(byteArray, md5FileName);
	setTilesMD5(md5FileName);

	//save pal
	byteArray = pal;
	md5FileName = FileUtils::getByteArrayMD5Checksum(byteArray);
	FileUtils::saveByteArrayToCache(byteArray, md5FileName);
	setPaletteMD5(md5FileName);
}

void Map::unloadArea(const string& s)
{ //=========================================================================================================================

	//public Hashtable<String, Area> areaHashtable = ms<Hashtable><String, Area>();

	sp<Area> a = nullptr;
	if(currentState->areaByNameHashtable.containsKey(s))
	a = currentState->areaByNameHashtable.get(s);

	currentState->areaByNameHashtable.removeAt(s);

	if(currentState->areaByTYPEIDHashtable.containsKey(a->getTYPEIDString()))
	currentState->areaByTYPEIDHashtable.removeAt(a->getTYPEIDString());


	currentState->areaList.remove(a);
}

void Map::unloadLight(const string& s)
{ //=========================================================================================================================
	//public ArrayList<Light> lightList = ms<ArrayList><Light>();
	//public Hashtable<String,Light> lightHashtable = ms<Hashtable><String,Light>();


	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		if (currentState->lightList.at(i)->getName() == s)
		{
			currentState->lightList.erase(currentState->lightList.begin()+i);
			i--;
			if (i < 0)
			{
				i = 0;
			}
		}
	}

	currentState->lightByNameHashtable.removeAt(s);

	for (int i = 0; i < sortedLightsLayers.size(); i++)
	{
		for (int j = 0; j < (int)sortedLightsLayers.at(i).size(); j++)
		{
			if (sortedLightsLayers.at(i).at(j)->getName() == s)
			{
				sortedLightsLayers.at(i).erase(sortedLightsLayers.at(i).begin()+j);
				j--;
				if (j < 0)
				{
					j = 0;
				}
			}
		}
	}
}

void Map::unloadMapEntity(const string& s)
{ //=========================================================================================================================


	//public ArrayList<MapSprite> entityList = ms<ArrayList><MapSprite>();
	//public Hashtable<String, MapSprite> entityHashtable = ms<Hashtable><String, MapSprite>();

	for (int i = 0; i < (int)currentState->entityList.size(); i++)
	{
		if (currentState->entityList.at(i)->getName() == s)
		{
			currentState->entityList.erase(currentState->entityList.begin()+i);
			i--;
			if (i < 0)
			{
				i = 0;
			}
		}
	}

	currentState->entityByNameHashtable.removeAt(s);
}

void Map::releaseAllTextures()
{ //=========================================================================================================================
	//go through all chunkTexture[] and release each texture in video memory and set to null
	//then reset all arrays

	//don't reset started threads!!!
	//don't reset these, they will keep going into the next map, which is still useful. they contruct the PNG from raw data which will be loaded later.
	//startedThreads = false;
	//startedHQ2XThreads = false;
	//startedLightThreads=false;


	setChunkTexturesLoaded_S(0);

	//DO reset these, since we unload these textures.
	allChunkPNGsLoadedAsTextures = false;
	allHQ2XChunkPNGsLoadedAsTextures = false;

	//DO reset this, because we haven't necessarily loaded every light texture yet.
	allLightsLoadedAsTextures = false;


	//unload the utility layers
	//delete hitLayer;
	//delete cameraLayer;
	//delete groundShaderLayer;
	//delete lightMaskLayer;
	
	hitLayer = nullptr;
	cameraLayer = nullptr;
	groundShaderLayer = nullptr;
	lightMaskLayer = nullptr;



	//we need to reload the utility layers
	utilityLayersLoaded = false;



	
	sp<vector<sp<OKTexture>>> chunks = chunkTexture.getAllValues();
	{
		for (int i = 0; i < chunks->size(); i++)
		{
			sp<OKTexture>t = chunks->at(i);

			if (t != nullptr)
			{
				//don't release the blank texture
				if (t != GLUtils::blankTexture)
				{
					t->release();
					//delete t;
					t = nullptr;
				}
				
			}
		}
	}
	//delete chunks;
	chunks = nullptr;

	chunkTexture.clear();


	sortedLightsLayers.clear();


	/*if(chunkFileExists!=null)
	{
	   for(int i=0;i<chunksWidth*chunksHeight*2;i++)chunkFileExists->get(i)=false;
	}
	            
	if(HQ2XChunkFileExists!=null)
	{
	   for(int i=0;i<chunksWidth*chunksHeight*2;i++)HQ2XChunkFileExists->get(i)=false;
	}*/

	if (usingHQ2XTexture != nullptr)
	{
		for (int i = 0; i < chunksWidth * chunksHeight * 2; i++)
		{
			(*usingHQ2XTexture)[i] = false;
		}

		//delete usingHQ2XTexture;
		usingHQ2XTexture = nullptr;
	}

	//TODO: i can only delete these after all threads are done, which right now there is no real way to check this
	//i might want to continue updating the map and have a separate thread pool per map, and when all threads are finished, then i can delete these
	//or i can delete them if all png chunks have been generated

	//delete tilesetIntArray;
	//delete paletteRGBByteArray;

	//tilesetIntArray = nullptr;
	//paletteRGBByteArray = nullptr;

	//   tilesetIntArray = new int[];
	//   paletteRGBByteArray= new u8[];

	//System.gc();
}

float Map::mapCamX()
{ //=========================================================================================================================
	//centers the camera x and y on the screen and sets map cam to the upper left corner
	if (this == getCurrentMap().get())
	{
		return getCameraman()->getX() - (getEngine()->getWidthRelativeToZoom() / 2.0f); // divided by 2.0f because it is getting from the center to the upper left
	}
	else
	{
		return 0 - lastKnownScreenX;
	}
}

float Map::mapCamY()
{ //=========================================================================================================================
	if (this == getCurrentMap().get())
	{
		return getCameraman()->getY() - (getEngine()->getHeightRelativeToZoom() / 2.0f);
	}
	else
	{
		return 0 - lastKnownScreenY;
	}
}

float Map::getScreenX(float mapX, float width)
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	//flooring these fixes all the sprite jitter
	float left = (float)(floor(mapX));
	float right = (float)(floor(mapX + width));

	float mapCameraXPixelsHQ = mapCamX();
	float screenleft = mapCameraXPixelsHQ;
	float screenright = mapCameraXPixelsHQ + getEngine()->getWidthRelativeToZoom();

	float screenXPixelsHQ = left - screenleft;

	//if overlapping left side of screen
	if (right >= screenleft && left < screenleft)
	{
		screenXPixelsHQ = 0.0f - (screenleft - left);
	}

	//if onscreen and not overlapping the left side
	if (left >= screenleft && left < screenright)
	{
		screenXPixelsHQ = left - screenleft;
	}


	return screenXPixelsHQ * zoom;
}

float Map::getScreenY(float mapY, float height)
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	//flooring these fixes all the sprite jitter
	float top = (float)(floor(mapY));
	float bottom = (float)(floor(mapY + height));

	float mapCameraYPixelsHQ = mapCamY();
	float screentop = mapCameraYPixelsHQ;
	float screenbottom = mapCameraYPixelsHQ + getEngine()->getHeightRelativeToZoom();

	float screenYPixelsHQ = top - screentop;

	//if overlapping top side of screen
	if (bottom >= screentop && top < screentop)
	{
		screenYPixelsHQ = 0.0f - (screentop - top);
	}

	//if onscreen and not overlapping the top side
	if (top >= screentop && top < screenbottom)
	{
		screenYPixelsHQ = top - screentop;
	}


	return screenYPixelsHQ * zoom;
}

float Map::screenX()
{
	if (this == getCurrentMap().get())
	{
		return 0 - mapCamX();
	}
	else
	{
		return lastKnownScreenX;
	}
}

float Map::screenY()
{
	if (this == getCurrentMap().get())
	{
		return 0 - mapCamY();
	}
	else
	{
		return lastKnownScreenY;
	}
}

void Map::updateLastKnownScreenXYBasedOnCamera()
{ //=========================================================================================================================

	//set map screen x and y

	//if map_cam_x is -400, map_screen_x should be 400

	lastKnownScreenX = 0 - mapCamX();
	lastKnownScreenY = 0 - mapCamY();

	//TODO: can't get rid of these with functions because drawing the last map depends on them not being updated, and instead drawn with an offset.
	//figure out a way to fix this
}


//
//	
//	/**
//	 *
//	 * checks both getHit layer and any mapsprites that aren't characters
//	 *
//	 */
//	public boolean checkHitLayerAndHitSpritesXY(float x, float y)
//	{
//
//		boolean getHit = getHitLayerValueAtXYPixels(x,y);
//
//		if(getHit==false)
//		{
//			//go through all mapsprites, check if map characters
//			for(int i=0;i<activeEntityList.size();i++)
//			{
//				Entity m = activeEntityList.at(i);
//				if(m.getNonWalkable()==true
//						&&x<m.getRight()
//						&&x>m.getLeft()
//						&&y<m.getBottom()
//						&&y>m.getTop()
//				)return true;
//
//			}
//		}
//		return getHit;
//
//	}


bool Map::getHitLayerValueAtXYTile1X(int xTile1X, int yTile1X)
{ //=========================================================================================================================
	return getHitLayerValueAtXYPixels((float)xTile1X * 8 * 2, (float)yTile1X * 8 * 2);
}

bool Map::getHitLayerValueAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
{ //=========================================================================================================================

	if (getEngine()->hitLayerEnabled == false)
	{
		return false;
	}

	if (utilityLayersLoaded == false)
	{
		return true;
	}

	//return "getHit wall" if value is outside of the map
	if (mapYPixelsHQ >= getHeightPixelsHQ() || mapXPixelsHQ >= getWidthPixelsHQ() || mapYPixelsHQ < 0 || mapXPixelsHQ < 0)
	{
		return true;
	}


	int tilex = (((int)(floor(mapXPixelsHQ))) / 8) / 2;
	int tiley = (((int)(floor(mapYPixelsHQ))) / 8) / 2; // divided by 2 because map is getScale 2x. map_x and map_y are 2x as well, giving "subpixel" precision for maps i guess
	//NOTE: will have to float all the tile xy values for movement and placement if i keep it this way

	int tilew = (getWidthPixelsHQ() / 2) / 8; //also divided by 2, see above
	int index = (tiley * tilew) + tilex;


	if (hitLayer->data()[index] == 0)
	{
		return false;
	}
	return true;
}

int Map::getCameraBoundsFXLayerAtXYTile1X(int xTile1X, int yTile1X)
{ //=========================================================================================================================
	return getCameraBoundsFXLayerAtXYPixels((float)xTile1X * 8 * 2, (float)yTile1X * 8 * 2);
}

int Map::getCameraBoundsFXLayerAtXYPixels(float mapXPixelsHQ, float mapYPixelsHQ)
{ //=========================================================================================================================

	if (utilityLayersLoaded == false)
	{
		return 0;
	}

	//return 0 if value is outside of the map
	if (mapYPixelsHQ >= getHeightPixelsHQ() || mapXPixelsHQ >= getWidthPixelsHQ() || mapYPixelsHQ < 0 || mapXPixelsHQ < 0)
	{
		return 0;
	}


	int tilex = ((((int)(floor(mapXPixelsHQ)))) / 8) / 2;
	int tiley = (((int)(floor(mapYPixelsHQ))) / 8) / 2;

	int tilew = (getWidthPixelsHQ() / 2) / 8;
	int index = (tiley * tilew) + tilex;

	return cameraLayer->data()[index];
}

bool Map::isXYWithinScreenByAmt(float x, float y, int amt)
{ //=========================================================================================================================

	float displayWidth = getEngine()->getWidthRelativeToZoom();
	float displayHeight = getEngine()->getHeightRelativeToZoom();

	if (x == -1)
	{
		x = (mapCamX()) + displayWidth / 2;
	}
	if (y == -1)
	{
		y = (mapCamY()) + displayHeight / 2;
	}

	if ((x + amt >= mapCamX() || x >= mapCamX()) && (x - amt <= mapCamX() + displayWidth || x <= mapCamX() + displayWidth) && (y + amt >= mapCamY() || y >= mapCamY()) && (y - amt <= mapCamY() + displayHeight || y <= mapCamY() + displayHeight))
	{
		return true;
	}

	return false;
}

bool Map::isXYXYWithinScreenByAmount(float x, float y, float x2, float y2, float amt)
{ //=========================================================================================================================

	float displayWidth = getEngine()->getWidthRelativeToZoom();
	float displayHeight = getEngine()->getHeightRelativeToZoom();

	if (x == -1)
	{
		x = (mapCamX()) + displayWidth / 2;
	}
	if (y == -1)
	{
		y = (mapCamY()) + displayHeight / 2;
	}
	if (x2 == -1)
	{
		x2 = (mapCamX()) + displayWidth / 2;
	}
	if (y2 == -1)
	{
		y2 = (mapCamY()) + displayHeight / 2;
	}

	if (((mapCamX() >= x && mapCamX() <= x2) || (mapCamX() + displayWidth >= x && mapCamX() + displayWidth <= x2) || (x >= mapCamX() && x <= mapCamX() + displayWidth) || (x2 >= mapCamX() && x2 <= mapCamX() + displayWidth)) && ((mapCamY() >= y && mapCamY() <= y2) || (mapCamY() + displayHeight >= y && mapCamY() + displayHeight <= y2) || (y >= mapCamY() && y <= mapCamY() + displayHeight) || (y2 >= mapCamY() && y2 <= mapCamY() + displayHeight)))
	{
		return true;
	}

	return false;
}

bool Map::isXYWithinScreen(float x, float y)
{ //=========================================================================================================================

	return isXYWithinScreenByAmt(x, y, 0);
}


//
//	
//	public void setTextureMD5Names(String getGroundLayerMD5,String getGroundObjectsMD5,String getGroundShadowMD5,String getObjectsMD5,String getObjects2MD5,String getObjectShadowMD5,String getAboveMD5,String getAbove2MD5,String getSpriteShadowMD5,String getGroundShaderMD5,String getCameraBoundsMD5,String getHitBoundsMD5,String getLightMaskMD5,String paletteMD5,String getTilesMD5)
//	{
//
//
//		//name = object.name;
//		this.getGroundLayerMD5 = getGroundLayerMD5;
//		this.getGroundObjectsMD5 = getGroundObjectsMD5;
//		this.getGroundShadowMD5 = getGroundShadowMD5;
//		this.getObjectsMD5 = getObjectsMD5;
//		this.getObjects2MD5 = getObjects2MD5;
//		this.getObjectShadowMD5 = getObjectShadowMD5;
//		this.getAboveMD5 = getAboveMD5;
//		this.getAbove2MD5 = getAbove2MD5;
//		this.getSpriteShadowMD5 = getSpriteShadowMD5;
//		this.getGroundShaderMD5 = getGroundShaderMD5;
//		this.getCameraBoundsMD5 = getCameraBoundsMD5;
//		this.getHitBoundsMD5 = getHitBoundsMD5;
//		this.getLightMaskMD5 = getLightMaskMD5;
//		this.paletteMD5 = paletteMD5;
//		this.getTilesMD5 = getTilesMD5;
//
//	}


//The following method was originally marked 'synchronized':
sp<OKTexture> Map::getChunkTexture(int index)
{ //=========================================================================================================================

	if (chunkTexture.containsKey(index) == false)return nullptr;
	return chunkTexture.get(index);
}

//The following method was originally marked 'synchronized':
void Map::setChunkTexture(int index, sp<OKTexture> t)
{ //=========================================================================================================================
	chunkTexture.put(index, t);
}

//The following method was originally marked 'synchronized':
void Map::releaseChunkTexture(int index)
{ //=========================================================================================================================
	chunkTexture.get(index)->release();
	//delete chunkTexture.get(index);
	chunkTexture.get(index) = nullptr;
	chunkTexture.put(index, nullptr);
}

































bool Map::loadChunkTexturesFromCachePNGs()
{ //=========================================================================================================================

	bool tempAllChunksLoaded = true;

	//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

	//get chunkX and Y based on player location

	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;
	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}
	int chunkX = startChunkX;
	int chunkY = startChunkY;
	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;
	int dir = dir_RIGHT;
	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection


	int sw = (int)(getEngine()->getWidthRelativeToZoom());
	int sh = (int)(getEngine()->getHeightRelativeToZoom());

	int camX = ((int)(floor(((mapCamX())))));
	int camY = ((int)(floor(((mapCamY())))));

	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (MapManager::loadTexturesOnDemand == false || (((chunkX + 1) * chunkSizePixelsHQ2X) - 1 >= camX && chunkX * chunkSizePixelsHQ2X < camX + (sw) && ((chunkY + 1) * chunkSizePixelsHQ2X) - 1 >= camY && chunkY * chunkSizePixelsHQ2X < camY + (sh)))
		{
			if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
			{
				for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
				{
					int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

					//check if tile has texture already in gpu
					if (getChunkTexture(chunkIndex) == nullptr)
					{
						tempAllChunksLoaded = false;

						//if it doesnt have a texture, need to load the texture
						//check for existence of texture in groundMD5

						if (getChunkPNGFileExists_S(chunkIndex) == true || (MapManager::generateHQ2XChunks == true && getHQ2XChunkPNGFileExists_S(chunkIndex) == true))
						{
							sp<OKFile> textureFile = nullptr;

							if (MapManager::generateHQ2XChunks == true && getHQ2XChunkPNGFileExists_S(chunkIndex) == true)
							{
								textureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(chunkIndex));
								(*usingHQ2XTexture)[chunkIndex] = true;
							}
							else
							{
								textureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + to_string(chunkIndex));
							}

							if (textureFile->exists() == false)
							{
								//(exception())->printStackTrace();
								continue;
							}

							//if it exists:

							//if it is 0 bytes, just point texture to blank tile

							if (textureFile->length() < 1)
							{
								setChunkTexture(chunkIndex, GLUtils::blankTexture);
							}
							else
							{
								//************
								//there is no reason to do this, single threaded deferred loading one chunk per frame is fast enough
								//************
								//DONTNEEDTODO: create new thread for loading textures
								//however, this isn't possible with lwjgl without some hacks, so what CAN we do?
								//let's see why it gives the error it does...

								setChunkTexture(chunkIndex, GLUtils::getTextureFromPNGAbsolutePath(textureFile->getAbsolutePath()));
							}

							incrementChunkTexturesLoaded_S();
						}
					}
				}

				if (tempAllChunksLoaded == false)
				{
					break;
				}
			}
		}
		else
		{
			//unload texture
			if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
			{
				for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
				{
					int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

					if (getChunkTexture(chunkIndex) != nullptr && getChunkTexture(chunkIndex) != GLUtils::blankTexture) //fix WHITE TILE bug?
					{
						releaseChunkTexture(chunkIndex);


						decrementChunkTexturesLoaded_S();
					}
				}
			}
		}

		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}

			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}

			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}

	return false;
	//return tempAllChunksLoaded;
}

bool Map::loadLightTexturesFromCachePNGs()
{ //=========================================================================================================================

	bool tempAllLightTexturesLoaded = true;


	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		{
			//if(lightList.at(i).mapAsset==this)
			sp<Light> l = currentState->lightList.at(i);

			//check if tile has texture already in gpu
			if (l->texture == nullptr)
			{
				//see if it's in the hashmap loaded already from a different map

				if(getMapManager()->lightTextureHashMap.containsKey(l->getFileName()))
				l->texture = getMapManager()->lightTextureHashMap.get(l->getFileName());


				if (l->texture == nullptr)
				{
					tempAllLightTexturesLoaded = false;

					//if it doesnt have a texture, need to load the texture
					//check for existence of texture

					//check our PNG file hashmap which was filled when we started threads for missing textures.
					if (MapManager::getLightTexturePNGFileExists_S(l->getFileName()) == true)
					{
						//floatcheck it exists, this should never be false.
						sp<OKFile> textureFile = ms<OKFile>(FileUtils::cacheDir + "l" + "/" + l->getFileName());
						if (textureFile->exists() == false)
						{
							//(exception())->printStackTrace();
							continue;
						}


						sp<OKTexture> t = GLUtils::getTextureFromPNGAbsolutePath(FileUtils::cacheDir + "l" + "/" + l->getFileName());
						getMapManager()->lightTextureHashMap.put(l->getFileName(), t);

						l->texture = t;
					}
				}
			}
		}

		if (tempAllLightTexturesLoaded == false)
		{
			break; //only load one per frame
		}
	}

	return tempAllLightTexturesLoaded;
}

bool Map::loadHQ2XTexturesFromCachePNGs()
{ //=========================================================================================================================

	//run through all chunks
	//this can be linear (not spiral) because this is only called when they are being created by threads (in a spiral) so it will update in a spiral anyway.
	//it's actually probably slightly less efficient to use a spiral since it has to cover a lot of blank space outside the map

	bool tempAllHQ2XChunksLoaded = true;

	for (int chunkY = 0; chunkY < chunksHeight; chunkY++)
	{
		for (int chunkX = 0; chunkX < chunksWidth; chunkX++)
		{
			for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
			{
				int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);

				if ((*usingHQ2XTexture)[chunkIndex] == false)
				{
					tempAllHQ2XChunksLoaded = false;

					if (getHQ2XChunkPNGFileExists_S(chunkIndex) == true)
					{
						sp<OKFile> textureFile = nullptr;

						if (getHQ2XChunkPNGFileExists_S(chunkIndex) == true)
						{
							textureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(chunkIndex));
						}

						if (textureFile->exists() == false)
						{
							//(exception())->printStackTrace();
							continue;
						}

						sp<OKTexture> t = getChunkTexture(chunkIndex);

						if (t != nullptr)
						{
							//remove previous texture from GPU.
							if (t != GLUtils::blankTexture)
							{
								t->release();
								//delete t;
								t = nullptr;
							}
							setChunkTexture(chunkIndex, nullptr);
						}

						//set to new texture

						if (textureFile->length() < 1)
						{
							setChunkTexture(chunkIndex, GLUtils::blankTexture);
						}
						else
						{
							//DONE: create new thread: load it as a texture, set TileTexture to this texture, delete ByteBuffer
							setChunkTexture(chunkIndex, GLUtils::getTextureFromPNGAbsolutePath(textureFile->getAbsolutePath()));
						}

						(*usingHQ2XTexture)[chunkIndex] = true;
					}
				}
			}
		}
	}

	return tempAllHQ2XChunksLoaded;
}

//The following method was originally marked 'synchronized':
void Map::incrementChunkPNGThreadsCreated()
{ //=========================================================================================================================
	chunkPNGThreadsCreated++;
	if (chunkPNGThreadsCreated > maxChunkPNGThreadsCreated)
	{
		maxChunkPNGThreadsCreated = chunkPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementChunkPNGThreadsCreated_S()
{ //=========================================================================================================================
	chunkPNGThreadsCreated--;
}

void Map::startThreadsForMissingChunkPNGs()
{ //=========================================================================================================================


	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5());
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/");
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/");


	if (MapManager::useThreads == true && generatePNGThreadPool == nullptr)
	{
	    generatePNGThreadPool = new ctpl::thread_pool(3);
	}
	 


	//for each texture that needs to be on-screen, spiraling clockwise from CAMERA TARGET POSITION

	//get chunkX and Y based on player location

	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;

	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}

	int chunkX = startChunkX;
	int chunkY = startChunkY;

	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;

	int dir = dir_RIGHT;


	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection

	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
		{
			for (int chunkLayer = 0; chunkLayer < 2; chunkLayer++)
			{
				int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);


				//check for existence of texture in groundMD5
				sp<OKFile> textureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + to_string(chunkIndex));
				sp<OKFile> hq2xTextureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(chunkIndex));


				if (hq2xTextureFile->exists())
				{
					setHQ2XChunkFileExists_S(chunkIndex, true);
				}

				if (textureFile->exists())
				{
					setChunkPNGFileExists_S(chunkIndex, true);
				}
				else
				{
					//if it doesnt exist
					//load tileset and palette into memory if it is not already loaded into mem from another tile

					if (tilesetIntArray == nullptr)
					{
						tilesetIntArray = (FileUtils::loadIntFileFromCacheOrDownloadIfNotExist("" + getTilesMD5()));
					}

					if (paletteRGBByteArray == nullptr)
					{
						paletteRGBByteArray = (FileUtils::loadByteFileFromCacheOrDownloadIfNotExist("" + getPaletteMD5()));
					}


					//create new thread:
//					int threadChunkLayer = chunkLayer;
//					int threadChunkX = chunkX;
//					int threadChunkY = chunkY;
//					int threadChunkIndex = chunkIndex;
					//sp<sp<IntArray>> threadTilesetIntArray = tilesetIntArray; //we send in a final pointer to this because it is set to null when the map is unloaded, but the threads may still be creating map tile pngs and will release this pointer when they die.
					//sp<sp<ByteArray>> threadPaletteRGBByteArray = paletteRGBByteArray;


					if (MapManager::useThreads == true)
					{
						incrementChunkPNGThreadsCreated();
						

//						std::vector<std::future<void>> results;
//						results.push_back
//						(
							generatePNGThreadPool->push(
							
								[&, chunkLayer, chunkX, chunkY, chunkIndex](int)//[=] means capture by value, [&] means capture by reference
								{
									//Thread::currentThread().setName("MapAsset_startThreadsForMissingChunkPNGs");


									createChunkTexturePNG_S(chunkLayer, chunkX, chunkY, chunkIndex);
									setChunkPNGFileExists_S(chunkIndex, true);
									decrementChunkPNGThreadsCreated_S();
								}
							);
						//);


					}
					else
					{
						//do it linearly, waiting for all chunks to finish before continuing
						createChunkTexturePNG_S(chunkLayer, chunkX, chunkY, chunkIndex);
						setChunkPNGFileExists_S(chunkIndex, true);
					}
				}
			}
		}

		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}

			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}

			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}


	//unload tileset and palette if they were loaded

	//delete tilesetIntArray;//sp just set to null
	//delete paletteRGBByteArray;

	//tilesetIntArray = nullptr;
	//paletteRGBByteArray = nullptr;


	//if(MapManager::useThreads==true && generatePNGThreadPool != nullptr)generatePNGThreadPool.shutdown();
}

//The following method was originally marked 'synchronized':
void Map::incrementLightPNGThreadsCreated()
{ //=========================================================================================================================
	lightPNGThreadsCreated++;
	if (lightPNGThreadsCreated > maxLightPNGThreadsCreated)
	{
		maxLightPNGThreadsCreated = lightPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementLightPNGThreadsCreated_S()
{ //=========================================================================================================================
	lightPNGThreadsCreated--;
}

void Map::startThreadsForMissingLightPNGs()
{ //=========================================================================================================================


	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::cacheDir + "l" + "/");



	if (MapManager::useThreads == true && generateLightPNGThreadPool == nullptr)
	{
	    generateLightPNGThreadPool = new ctpl::thread_pool(3);
	}


	//go through all the lights in lightList
	//for all the lights see if there is a texture generated for it, stored in the light object itself
	//if there isn't, generate the light as a bufferedImage, create a texture for it, and set it in the light object

	for (int i = 0; i < (int)currentState->lightList.size(); i++)
	{
		{
			//if(lightList.at(i).mapAsset==this)
			sp<Light> l = currentState->lightList.at(i);


			//don't create a thread to generate a texture that is already being made.
			//this prevents collisions where a thread is overwriting a png that already exists while it is being loaded as a texture
			bool c = false;
			for (int j = 0; j < i; j++)
			{
				if (currentState->lightList.at(j)->getFileName() == l->getFileName())
				{
					c = true;
					break;
				}
			}
			if (c)
			{
				continue;
			}


			if (MapManager::getLightTexturePNGFileExists_S(l->getFileName()) == false)
			{
				//check for existence of texture in cache folder
				sp<OKFile> textureFile = ms<OKFile>(FileUtils::cacheDir + "l" + "/" + l->getFileName());
				if (textureFile->exists())
				{
					MapManager::setLightTexturePNGFileExists_S(l->getFileName(),true);
				}
				else
				{
					if (MapManager::useThreads == true)
					{
						
						string lightFilename = FileUtils::cacheDir + "l" + "/" + l->getFileName();
						u8 lr = l->r();
						u8 lg = l->g();
						u8 lb = l->b();
						u8 la = l->a();
						float lw = l->getWidth();
						float lh = l->getHeight();
						float lrad = l->getRadiusPixelsHQ();
						float lfocusRad = l->focusRadiusPixelsHQ();
						float ldecayExp = l->decayExponent();

						incrementLightPNGThreadsCreated();


//						std::vector<std::future<void>> results;
//						results.push_back
//						(
							generateLightPNGThreadPool->push
							(
								[&, lightFilename, lr, lg, lb, la, lw, lh, lrad, lfocusRad, ldecayExp](int)
								{
									//Thread::currentThread().setName("MapAsset_startThreadsForMissingLightPNGs");

									Light::createLightTexturePNG(lightFilename,lr,lg,lb,la,lw,lh,lrad,lfocusRad,ldecayExp);
									MapManager::setLightTexturePNGFileExists_S(lightFilename,true);

									decrementLightPNGThreadsCreated_S();
								}
							);
						//);
						

					}
					else
					{
						//do it linearly, waiting for all to finish before continuing
						l->createLightTexturePNG(FileUtils::cacheDir + "l" + "/" + l->getFileName());

						MapManager::setLightTexturePNGFileExists_S(l->getFileName(),true);
					}
				}
			}
		}
	}

	//if(MapManager::useThreads==true)generateLightPNGThreadPool.shutdown();
}

//The following method was originally marked 'synchronized':
void Map::incrementHQ2XChunkPNGThreadsCreated()
{ //=========================================================================================================================
	hq2xChunkPNGThreadsCreated++;
	if (hq2xChunkPNGThreadsCreated > maxHq2xChunkPNGThreadsCreated)
	{
		maxHq2xChunkPNGThreadsCreated = hq2xChunkPNGThreadsCreated;
	}
}

//The following method was originally marked 'synchronized':
void Map::decrementHQ2XChunkPNGThreadsCreated()
{ //=========================================================================================================================
	hq2xChunkPNGThreadsCreated--;
}

void Map::startThreadsForMissingHQ2XChunkPNGs()
{ //=========================================================================================================================

	//for each chunk, starting at player position

	//does cache/groundMD5/ exist?
	//if not, make it.
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5());
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/");
	FileUtils::makeDir(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/");


	if (MapManager::useThreads == true && generatePNGThreadPool == nullptr)
	{
	    generatePNGThreadPool = new ctpl::thread_pool(3);
	}



	int startChunkX = (int)(getCameraman()->getX()) / chunkSizePixelsHQ2X;
	int startChunkY = (int)(getCameraman()->getY()) / chunkSizePixelsHQ2X;

	if (startChunkX < 0 || startChunkX >= chunksWidth)
	{
		startChunkX = 0;
	}
	if (startChunkY < 0 || startChunkY >= chunksHeight)
	{
		startChunkY = 0;
	}

	int chunkX = startChunkX;
	int chunkY = startChunkY;

	int dir_UP = 0;
	int dir_DOWN = 1;
	int dir_LEFT = 2;
	int dir_RIGHT = 3;

	int dir = dir_RIGHT;


	int movementsUntilChangeDirection = 1;
	int movementsThisDirection = 0;
	int directionChangesUntilIncreaseMovements = 0; //when this is equal to 2, increase movementsUntilChangeDirection


	while (movementsUntilChangeDirection < chunksWidth * 2 || movementsUntilChangeDirection < chunksHeight * 2)
	{
		if (chunkX >= 0 && chunkX < chunksWidth && chunkY >= 0 && chunkY < chunksHeight)
		{
			//check hq2x exists only from bottom layer, since we generate both at the same time.
			int chunkLayer = 0;

			int chunkIndex = (chunksWidth * chunksHeight * chunkLayer) + ((chunkY * chunksWidth) + chunkX);
			int chunkIndexOverLayer = (chunksWidth * chunksHeight * 1) + ((chunkY * chunksWidth) + chunkX);

			//check for existence of texture in groundMD5
			sp<OKFile> hq2xTextureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(chunkIndex));

			if (hq2xTextureFile->exists())
			{
				setHQ2XChunkFileExists_S(chunkIndex, true);
				setHQ2XChunkFileExists_S(chunkIndexOverLayer, true);
			}
			else
			{
				//create new thread:
//				const int threadChunkX = chunkX;
//				const int threadChunkY = chunkY;
//				const int threadChunkIndex = chunkIndex;
//				const int threadChunkIndexOverLayer = chunkIndexOverLayer;

				if (MapManager::useThreads == true)
				{
					incrementHQ2XChunkPNGThreadsCreated();
					
//					std::vector<std::future<void>> results;
//					results.push_back
//					(
						generatePNGThreadPool->push
						(
							[&, chunkIndex, chunkIndexOverLayer, chunkX, chunkY](int)
							{
								//Thread::currentThread().setName("MapAsset_startThreadsForMissingHQ2XChunkPNGs");

								createHQ2XTexturePNG_THREAD(chunkX, chunkY);
								setHQ2XChunkFileExists_S(chunkIndex, true);
								setHQ2XChunkFileExists_S(chunkIndexOverLayer, true);

								decrementHQ2XChunkPNGThreadsCreated();
							}
						);
					//);

				}
				else
				{
					//do it linearly, waiting for all chunks to finish before continuing
					createHQ2XTexturePNG_THREAD(chunkX, chunkY);
					setHQ2XChunkFileExists_S(chunkIndex, true);
					setHQ2XChunkFileExists_S(chunkIndexOverLayer, true);
				}
			}
		}


		if (movementsThisDirection < movementsUntilChangeDirection)
		{
			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
		else
		{
			movementsThisDirection = 0;

			if (dir == dir_RIGHT)
			{
				dir = dir_DOWN;
			}
			else if (dir == dir_LEFT)
			{
				dir = dir_UP;
			}
			else if (dir == dir_DOWN)
			{
				dir = dir_LEFT;
			}
			else if (dir == dir_UP)
			{
				dir = dir_RIGHT;
			}


			directionChangesUntilIncreaseMovements++;

			if (directionChangesUntilIncreaseMovements >= 2)
			{
				directionChangesUntilIncreaseMovements = 0;
				movementsUntilChangeDirection++;
			}


			if (dir == dir_RIGHT)
			{
				chunkX++;
			}
			else if (dir == dir_LEFT)
			{
				chunkX--;
			}
			else if (dir == dir_DOWN)
			{
				chunkY++;
			}
			else if (dir == dir_UP)
			{
				chunkY--;
			}

			movementsThisDirection++;
		}
	}


	//if(MapManager::useThreads==true)generateHQ2XPNGThreadPool.shutdown();
}

void Map::createChunkTexturePNG_S(int chunkLayer, int chunkX, int chunkY, int chunkIndex)
{ //=========================================================================================================================

	//Thread.yield();

	//create chunkImage
	sp<BufferedImage> chunkImage = ms<BufferedImage>(chunkSizeTiles1X * 8, chunkSizeTiles1X * 8);
	sp<BufferedImage> chunkImageBorder = ms<BufferedImage>(chunkSizeTiles1X * 8 + 2, chunkSizeTiles1X * 8 + 2);


	//***************************************
	//if i don't init the graphics, the buffered image output has a random alpha jitter for a reason i can't figure out...
	//it actually looks nice, but i wanted to figure out what the heck was doing it!
	//NOPE this isn't why!
	//***************************************

	/*Graphics G = chunkImage.getGraphics();
	G.setColor(ms<Color>(0,0,0,0));
	G.fillRect(0, 0, chunkImage.getWidth(), chunkImage.getHeight());
	G.dispose();
	G = chunkImageBorder.getGraphics();
	G.setColor(ms<Color>(0,0,0,0));
	G.fillRect(0, 0, chunkImageBorder.getWidth(), chunkImageBorder.getHeight());
	G.dispose();*/

	sp<IntArray> layerChunkBuffer = ms<IntArray>((chunkSizeTiles1X + 2) * (chunkSizeTiles1X + 2));

	string layerFileName = "";

	bool blank = true;

	if (chunkLayer == 0)
	{
		blank = false;

		for (int l = 0; l < 6; l++)
		{
			bool shadowLayer = false;

			if (l == 0)
			{
				layerFileName = getGroundLayerMD5();
			}
			if (l == 1)
			{
				layerFileName = getGroundObjectsMD5();
			}
			if (l == 2)
			{
				layerFileName = getGroundShadowMD5();
				shadowLayer = true;
			}
			if (l == 3)
			{
				layerFileName = getObjectsMD5();
			}
			if (l == 4)
			{
				layerFileName = getObjects2MD5();
			}
			if (l == 5)
			{
				layerFileName = getObjectShadowMD5();
				shadowLayer = true;
			}

			drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer);
		}
	}
	else
	{
		if (chunkLayer == 1)
		{
			for (int l = 0; l < 3; l++)
			{
				bool shadowLayer = false;

				if (l == 0)
				{
					layerFileName = getAboveMD5();
				}
				if (l == 1)
				{
					layerFileName = getAbove2MD5();
				}
				if (l == 2)
				{
					layerFileName = getSpriteShadowMD5();
					shadowLayer = true;
				}

				bool changedImage = drawTileLayerIntoBufferedImage(layerFileName, chunkImage, chunkImageBorder, chunkX, chunkY, layerChunkBuffer, shadowLayer);
				if (changedImage == true)
				{
					blank = false;
				}
			}
		}
	}


	if (blank == true)
	{
		//log.debug("Made blank file: "+chunkLayer+"_"+chunkIndex);

		//save 0 byte placeholder, this will always load blank texture
		sp<OKFile> f = ms<OKFile>("" + FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + to_string(chunkIndex));
		sp<OKFile> f2 = ms<OKFile>("" + FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/" + to_string(chunkIndex));

		try
		{
			f->createNewFile();
			f2->createNewFile();
		}
		catch (exception e)//IOException e)
		{
			//e->printStackTrace();
		}
	}
	else
	{
		//save this as png in folder groundMD5/0_0_0
		FileUtils::saveImage("" + FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + to_string(chunkIndex), chunkImage);
		FileUtils::saveImage("" + FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/" + to_string(chunkIndex), chunkImageBorder);
	}

	//delete chunkImage;
	//delete chunkImageBorder;
	//delete layerChunkBuffer;

	chunkImage = nullptr;
	chunkImageBorder = nullptr;
	layerChunkBuffer = nullptr;

}

#include <fstream>

bool Map::drawTileLayerIntoBufferedImage(const string& layerFileName, sp<BufferedImage> chunkImage, sp<BufferedImage> chunkImageBorder, int chunkX, int chunkY, sp<IntArray> layerChunkBuffer, bool shadowLayer)
{ //=========================================================================================================================


	bool isBlank = true;

	//open layer as file, load chunk into memory, with 1 tile border, filling with 0 if it is on the map edge

	//fstream raf;
	//raf.open(FileUtils::cacheDir + layerFileName, std::ios::binary);

	
	ifstream raf(FileUtils::cacheDir + layerFileName, ios::in | ios::binary);
//	if (raf.is_open())
//	{
//
//	}


	bool groundLayer = false;
	if (layerFileName == getGroundLayerMD5())
	{
		groundLayer = true;
	}


	//*********
	//IMPORTANT: need to generate chunk sizes that are exactly the size of a power of two.
	//*********


	//at 512, actual chunks will be 256x256, or 32 x 32 tiles
	//but this has a 2 tile border around all sides, so actual tile chunk is 30 x 30
	//we want to get as close to 512x512 as we can for power of two textures, no wasted space


	//NO: can i hq2x as a shader in gpu memory? probably not, don't need to.

	//DONE: need framebuffer, need shader support


	//so:  here we want to load chunkSize + 2 tiles, so 34 x 34


	//so instead let's take 34x34 chunk to begin with, 272x272
	//then we generate a 258x258 png from this, with 1 pixel around border
	//then we save this as BOTH a 256x256 png and a 258x258 png

	//when loading textures into gpu for texture, use the 256x256 png

	//when loading into memory for hq2x, use the 258x258
	//hq2x this, producing 516x516
	//remove 2 from borders, producing 512x512
	//save this as nice clean 512x512 even DXT


	try
	{
		int startY = (chunkY * (chunkSizeTiles1X));
		int startX = (chunkX * (chunkSizeTiles1X));

		//startY - 1 because of border.
		for (int y = startY - 1; y < (startY + chunkSizeTiles1X) + 1; y++)
		{
			//if y is actually negative, fill it with 0 because it's off the map
			if (y >= getHeightTiles1X() || y < 0)
			{
				//fill with 0
			}
			else
			{
				if (chunkX == 0)
				{
					//seek to 0
					raf.seekg(((y * getWidthTiles1X()) + startX) * 4); //*4 for bytes -> int4

					//for -1 to +1
					//if x is -1, fill with 0

					for (int x = startX - 1; x < (startX + chunkSizeTiles1X) + 1; x++)
					{
						if (x >= getWidthTiles1X() || x < 0)
						{
							layerChunkBuffer->data()[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + ((x + 1) - startX)] = 0;
						}
						else
						{


							u8 byte1;
							u8 byte2;
							u8 byte3;
							u8 byte4;

							raf.read((char*)&byte1, 1);
							raf.read((char*)&byte2, 1);
							raf.read((char*)&byte3, 1);
							raf.read((char*)&byte4, 1);

							//u8 byte1 = sbyte1 & 0xFF;
							//u8 byte2 = sbyte2 & 0xFF;
							//u8 byte3 = sbyte3 & 0xFF;
							//u8 byte4 = sbyte4 & 0xFF;


							unsigned int result = (byte1 << 24) + (byte2 << 16) + (byte3 << 8) + byte4;


//							log.info("" + to_string(byte1) + " " + to_string(byte2) + " " + to_string(byte3) + " " + to_string(byte4) + " " + to_string(result));
//							log.info("" + to_string(sbyte1) + " " + to_string(sbyte2) + " " + to_string(sbyte3) + " " + to_string(sbyte4) + " " + to_string(result));
//
//							//int result;
//							//raf.read((char*)&result, 4);
//							if (result<0 || result > 1000 || byte1 > 0 || byte2 > 0 || byte3 > 0)
//							{
//								log.error("ok");
//							}
							

							if (result != 0)
							{
								isBlank = false;
							}

							layerChunkBuffer->data()[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + ((x + 1) - startX)] = result;
						}
					}
				}
				else
				{
					//seek to -1
					raf.seekg(((y * getWidthTiles1X()) + (startX - 1)) * 4);

					//for 0 to +2

					for (int x = (startX); x < (startX + chunkSizeTiles1X) + 2; x++)
					{
						if (x >= getWidthTiles1X() || x < 0)
						{
							layerChunkBuffer->data()[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + (x - startX)] = 0;
						}
						else
						{
							//uint32_t result;
							//raf.read(reinterpret_cast<char >(&result), sizeof(result));


							u8 byte1;
							u8 byte2;
							u8 byte3;
							u8 byte4;

							raf.read((char*)&byte1, 1);
							raf.read((char*)&byte2, 1);
							raf.read((char*)&byte3, 1);
							raf.read((char*)&byte4, 1);

//							u8 byte1 = sbyte1 & 0xFF;
//							u8 byte2 = sbyte2 & 0xFF;
//							u8 byte3 = sbyte3 & 0xFF;
//							u8 byte4 = sbyte4 & 0xFF;

							unsigned int result = (byte1 << 24) + (byte2 << 16) + (byte3 << 8) + byte4;


//							log.info("" + to_string(byte1) + " " + to_string(byte2) + " " + to_string(byte3) + " " + to_string(byte4) + " " + to_string(result));
//							log.info("" + to_string(sbyte1) + " " + to_string(sbyte2) + " " + to_string(sbyte3) + " " + to_string(sbyte4) + " " + to_string(result));
//
//
//							if(result < 0 || result > 1000 || byte1 > 0 || byte2 > 0 || byte3 > 0)
//							{
//								log.error("ok");
//							}

							//int result;
							//raf.read((char*)&result, 4);

							//int byte1 = raf.read() & 0xFF;
							//int byte2 = raf.read() & 0xFF;
							
							//int result = (byte2<<8) + byte1;

							if (result != 0)
							{
								isBlank = false;
							}

							layerChunkBuffer->data()[(((y + 1) - startY) * (chunkSizeTiles1X + 2)) + (x - startX)] = result;
						}
					}
				}
			}
		}
	}
	catch (exception e)//IOException e)
	{
		log.error("Could not read file");
	}

	raf.close();


	if (isBlank == true)
	{
		return false;
	}


	for (int ty = 0; ty < (chunkSizeTiles1X + 2); ty++)
	{
		for (int tx = 0; tx < (chunkSizeTiles1X + 2); tx++)
		{
			unsigned int tile = layerChunkBuffer->data()[(ty * (chunkSizeTiles1X + 2)) + tx];

			//skip black tiles on the ground layer
			if (groundLayer == true && tile == 1)
			{
				continue;
			}

			for (int py = 0; py < 8; py++)
			{
				for (int px = 0; px < 8; px++)
				{
					//skip all but one pixel of border
					if (tx == 0 && px < 7)
					{
						continue;
					}
					if (tx == chunkSizeTiles1X + 1 && px > 0)
					{
						continue;
					}
					if (ty == 0 && py < 7)
					{
						continue;
					}
					if (ty == chunkSizeTiles1X + 1 && py > 0)
					{
						continue;
					}


					unsigned int tilesetIndex = ((tile * 64) + (py * 8 + px)); //*2;

					unsigned int paletteIndex = tilesetIntArray->data()[tilesetIndex];

					//int byte1 = tileset[tilesetIndex] & 0xFF;
					//int byte2 = tileset[tilesetIndex+1] & 0xFF;
					//
					//int paletteIndex = (byte2<<8)+byte1;

					if (paletteIndex != 0)
					{
						u8 paletteR = paletteRGBByteArray->data()[(paletteIndex * 3) + (0)];
						u8 paletteG = paletteRGBByteArray->data()[(paletteIndex * 3) + (1)];
						u8 paletteB = paletteRGBByteArray->data()[(paletteIndex * 3) + (2)];

						sp<OKColor> c = ms<OKColor>(paletteR, paletteG, paletteB);

						if (shadowLayer) //shadow layer
						{
							int oldPixel = chunkImageBorder->getRGBA(((tx - 1) * 8 + px) + 1, ((ty - 1) * 8 + py) + 1);
							sp<OKColor> oldColor = ms<OKColor>(oldPixel);// , true);

							u8 alpha = 255;
							if (oldColor->getRGBA() == 0)
							{
								alpha = 150;
							}

							float shadowAlpha = 150.0f;
							u8 blendedRed = (u8)((shadowAlpha / 255.0f) * paletteR + (1.0f - (shadowAlpha / 255.0f)) * oldColor->ri());
							u8 blendedGreen = (u8)((shadowAlpha / 255.0f) * paletteG + (1.0f - (shadowAlpha / 255.0f)) * oldColor->gi());
							u8 blendedBlue = (u8)((shadowAlpha / 255.0f) * paletteB + (1.0f - (shadowAlpha / 255.0f)) * oldColor->bi());

							//delete oldColor;
							oldColor = nullptr;

							c = ms<OKColor>(blendedRed, blendedGreen, blendedBlue, alpha);
						}


						chunkImageBorder->setRGB(((tx - 1) * 8 + px) + 1, ((ty - 1) * 8 + py) + 1, c->getRGBA());

						if (tx > 0 && tx < chunkSizeTiles1X + 1 && ty > 0 && ty < chunkSizeTiles1X + 1)
						{
							chunkImage->setRGB((tx - 1) * 8 + px, (ty - 1) * 8 + py, c->getRGBA());
						}
					}
				}
			}
		}
	}

	return true;
}

void Map::createHQ2XTexturePNG_THREAD(int chunkX, int chunkY)
{ //=========================================================================================================================


	//Thread.currentThread().setPriority(Thread.MIN_PRIORITY);
	//Thread.yield();

	//load 1x png under and over into bitmap arrays


	int clear = 0;
	//int black = (ms<Color>(0, 0, 0, 255))->getRGB();


	int underChunkIndex = (chunksWidth * chunksHeight * 0) + ((chunkY * chunksWidth) + chunkX);
	int overChunkIndex = (chunksWidth * chunksHeight * 1) + ((chunkY * chunksWidth) + chunkX);

	sp<OKFile> underLayerTextureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/" + to_string(underChunkIndex));
	sp<OKFile> overLayerTextureFile = ms<OKFile>(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "1x_padded" + "/" + to_string(overChunkIndex));


	//TODO: handle if 1x file doesn't exist, make it again from md5!

	//TODO: check 1, 1x, hq2x file for being over 0 bytes, the correct width and height... if it isn't, delete it and remake it
	//nice fix for broken cache files


	sp<BufferedImage> bottom = nullptr;
	sp<BufferedImage> top = nullptr;


	//handle 0 byte files!
	if (underLayerTextureFile->length() < 1) //it is actually a completely isEmpty image, it was all 0 tiles
	{
		bottom = ms<BufferedImage>(chunkSizePixels1X + 2, chunkSizePixels1X + 2);


		//thought this would fix the hq2x grain glitch, but it was from hq2x being static.
		//dont need to initialize isEmpty graphics
		/*Graphics G = bottom.getGraphics();
		G.setColor(ms<Color>(0,0,0,0));
		G.fillRect(0,0,bottom.getWidth(), bottom.getHeight());
		G.dispose();
		G = null;*/
	}
	else
	{
		try
		{
			bottom = FileUtils::readBufferedImageFromFile(underLayerTextureFile);
		}
		catch (exception e)//IOException e)
		{
			log.error("Cannot read PNG file: " + underLayerTextureFile->getName() + " ");// +e->getMessage());
		}
	}


	if (overLayerTextureFile->length() < 1)
	{
		top = ms<BufferedImage>(chunkSizePixels1X + 2, chunkSizePixels1X + 2);
		/*Graphics G = top.getGraphics();
		G.setColor(ms<Color>(0,0,0,0));
		G.fillRect(0,0,top.getWidth(), top.getHeight());
		G.dispose();
		G = null;*/
	}
	else
	{
		try
		{
			top = FileUtils::readBufferedImageFromFile(overLayerTextureFile);
		}
		catch (exception e)//IOException e)
		{
			log.error("Cannot read PNG file: " + overLayerTextureFile->getName() + " ");// +e->getMessage());
		}
	}


	//create bottom + top image

	sp<BufferedImage> bottomAndTop = ms<BufferedImage>(chunkSizePixels1X + 2, chunkSizePixels1X + 2);

	//draw bottom, then top into bottomAndTop

	//draw bottom into bottomAndTop
	for (int y = 0; y < bottom->getHeight(); y++)
	{
		for (int x = 0; x < bottom->getWidth(); x++)
		{
			bottomAndTop->setRGB(x, y, bottom->getRGBA(x, y));
		}
	}

	//draw top into bottomAndTop
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			if (top->getRGBA(x, y) != clear)
			{
				bottomAndTop->setRGB(x, y, top->getRGBA(x, y));
			}
		}
	}

	//----------------------
	//TOP LAYER
	//----------------------

	//hq2x bottom+top
	sp<BufferedImage> hq2xBottomAndTop = (new HQ2X())->hq2x(bottomAndTop);
	//setHQ2XAlphaFromOriginal(hq2xBottomAndTop,bottomAndTop); //(shouldnt be transparent here)

	//dont need bottomandtop

	//delete bottomAndTop;
	bottomAndTop = nullptr;

	sp<BufferedImage> hq2xBottomAndTopCopy = ms<BufferedImage>(hq2xBottomAndTop->getWidth(), hq2xBottomAndTop->getHeight());
	for (int y = 0; y < hq2xBottomAndTop->getHeight(); y++)
	{
		for (int x = 0; x < hq2xBottomAndTop->getWidth(); x++)
		{
			//copy x,y into x-2,y-2
			hq2xBottomAndTopCopy->setRGB(x, y, hq2xBottomAndTop->getRGBA(x, y));
		}
	}


	//Masking 1x top layer from HQ2X bottom+top
	//go through top layer
	//for each transparent pixel set 2x (x+xx y+yy) transparent on hq2x bottom+top
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			//copy alpha pixels from top, including clear and transparent shadows
			//TODO: fix this in editor as well when outputting hq2x
			if (((top->getRGBA(x, y) >> 24) & 0xff) < 255)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBottomAndTop->setRGB((x * 2) + xx, ((y * 2) + yy), top->getRGBA(x, y));
					}
				}
			}


			//could do better antialiasing around edges here. since we're masking out the bottom layer, some of the edges on the top layer have gray pixels.
			//i could go through the top image, find clear pixels surrounded with black, and set the in-between pixel on the hq2x image with black alpha 127

			//this is kind of broken for negligible benefit, not worth working on at the moment

			/*if(top.getRGB(x, y)==clear)
			{
			   if(
			      (x<top.getWidth()-1&&x>0&&y<top.getHeight()-1&&y>0)
			      )
			   {
			      if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y-1)!=clear)//right up
			      {
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x+1, y)!=clear&&top.getRGB(x, y+1)!=clear)//right down
			      {
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y-1)!=clear)//left up
			      {
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			      }
			   
			      if(top.getRGB(x-1, y)!=clear&&top.getRGB(x, y+1)!=clear)//left down
			      {
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+0, ((y*2)+0), ms<Color>(0,255,0,127).getRGB());
			         hq2xBottomAndTop.setRGB((x*2)+1, ((y*2)+1), ms<Color>(0,255,0,127).getRGB());
			      }
			   }
			   
			}*/
		}
	}


	//could antialias black edges here. ****this algorithm doesn't really work because all the edges are already interpolated with the background color.
	//antialiasBufferedImage(hq2xBottomAndTop);

	//----------------------
	//output hq2x top layer fully
	//----------------------

	//Outputting full HQ2X top layer

	//make temp image size-4

	sp<BufferedImage> temp = ms<BufferedImage>(hq2xBottomAndTop->getWidth() - 4, hq2xBottomAndTop->getHeight() - 4);
	for (int y = 2; y < hq2xBottomAndTop->getHeight() - 2; y++)
	{
		for (int x = 2; x < hq2xBottomAndTop->getWidth() - 2; x++)
		{
			//copy x,y into x-2,y-2
			temp->setRGB(x - 2, y - 2, hq2xBottomAndTop->getRGBA(x, y));
		}
	}

	//save temp as hq2x_top
	FileUtils::saveImage(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(overChunkIndex), temp);

	//don't need temp
	//delete temp;
	temp = nullptr;

	//dont need hq2xBottomAndTop
	//delete hq2xBottomAndTop;
	hq2xBottomAndTop = nullptr;


	//----------------------
	//BOTTOM LAYER
	//----------------------

	//hq2x bottom+top again

	hq2xBottomAndTop = hq2xBottomAndTopCopy; //new HQ2X().HQ2X(bottomAndTop); //it is probably better to just copy the image above before i modify it


	//put back any transparent pixels from bottom (borders around map)
	setHQ2XAlphaFromOriginal(hq2xBottomAndTop, bottom);

	//hq2x bottom
	sp<BufferedImage> hq2xBottom = ms<BufferedImage>(new HQ2X())->hq2x(bottom);


	//dont need bottom
	//delete bottom;
	bottom = nullptr;


	//Masking HQ2X bottom layer into HQ2X bottom+top layer
	//go through top layer
	//for each NON-transparent pixel 2x (x+xx y+yy ) take pixel from hq2x bottom, copy into hq2x bottom_top
	for (int y = 0; y < top->getHeight(); y++)
	{
		for (int x = 0; x < top->getWidth(); x++)
		{
			if (top->getRGBA(x, y) != clear)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBottomAndTop->setRGB((x * 2) + xx, ((y * 2) + yy), hq2xBottom->getRGBA((x * 2) + xx, ((y * 2) + yy)));
					}
				}
			}
		}
	}


	//dont need top
	//delete top;
	top = nullptr;

	//dont need hq2xBottom
	//delete hq2xBottom;
	hq2xBottom = nullptr;


	//----------------------
	//output hq2x bottom layer full
	//----------------------

	temp = ms<BufferedImage>(hq2xBottomAndTop->getWidth() - 4, hq2xBottomAndTop->getHeight() - 4);
	for (int y = 2; y < hq2xBottomAndTop->getHeight() - 2; y++)
	{
		for (int x = 2; x < hq2xBottomAndTop->getWidth() - 2; x++)
		{
			//copy x,y into x-2,y-2
			temp->setRGB(x - 2, y - 2, hq2xBottomAndTop->getRGBA(x, y));
		}
	}

	//Outputting full HQ2X bottom layer
	//save as hq2x bottom
	FileUtils::saveImage(FileUtils::cacheDir + "_" + getGroundLayerMD5() + "/" + "2x" + "/" + to_string(underChunkIndex), temp);

	//don't need temp
	//delete temp;
	temp = nullptr;

	//dont need hq2xBottomAndTop
	//delete hq2xBottomAndTop;
	hq2xBottomAndTop = nullptr;

	//delete hq2xBottomAndTopCopy;
	hq2xBottomAndTopCopy = nullptr;


	//DONE: set chunkTexture to hq2x chunk

	//need to do this in main thread, can't release textures in a secondary thread.
	//set a thing textureIsHQ2X, allHQ2XLoaded

	//Texture t = getChunkTexture(underChunkIndex);
	//setChunkTexture(underChunkIndex,null);
	//t.release();
	//t=null;


	//t = getChunkTexture(overChunkIndex);
	//setChunkTexture(overChunkIndex,null);
	//t.release();
	//t=null;


	//delete 1x pngs top and bottom
	underLayerTextureFile->deleteFile();
	overLayerTextureFile->deleteFile();

	//delete underLayerTextureFile;
	underLayerTextureFile = nullptr;
	//delete overLayerTextureFile;
	overLayerTextureFile = nullptr;
}

void Map::antialiasBufferedImage(sp<BufferedImage> bufferedImage)
{ //===============================================================================================

	//go through hq2x image
	//if pixel is transparent, and the pixel right and down, down and left, left and up, or up and right are black, this one is black

	//have to make a copy otherwise the algorithm becomes recursive
	sp<BufferedImage> copy = ms<BufferedImage>(bufferedImage->getWidth(), bufferedImage->getHeight());
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			copy->setRGB(x, y, bufferedImage->getRGBA(x, y));
		}
	}

	int clear = 0;

	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (copy->getRGBA(x, y) == clear)
			{
				int black = 0;

				//check right and down
				if (x + 1 < bufferedImage->getWidth() && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGBA(x + 1, y) != clear && copy->getRGBA(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check right and up
				if (x + 1 < bufferedImage->getWidth() && y - 1 >= 0)
				{
					if (copy->getRGBA(x + 1, y) != clear && copy->getRGBA(x, y - 1) != clear)
					{
						black = 1;
					}
				}


				//check left and down
				if (x - 1 >= 0 && y + 1 < bufferedImage->getHeight())
				{
					if (copy->getRGBA(x - 1, y) != clear && copy->getRGBA(x, y + 1) != clear)
					{
						black = 1;
					}
				}

				//check left and up
				if (x - 1 >= 0 && y - 1 >= 0)
				{
					if (copy->getRGBA(x - 1, y) != clear && copy->getRGBA(x, y - 1) != clear)
					{
						black = 1;
					}
				}

				if (black == 1)
				{
					bufferedImage->setRGB(x, y, OKColor::getRGBA(0, 0, 0, 127));
				}
			}
		}
	}
}

void Map::setHQ2XAlphaFromOriginal(sp<BufferedImage> hq2xBufferedImage, sp<BufferedImage> bufferedImage)
{ //===============================================================================================
	//now go through original image again. take each transparent pixel and set the hq2x one with it at 2x
	for (int y = 0; y < bufferedImage->getHeight(); y++)
	{
		for (int x = 0; x < bufferedImage->getWidth(); x++)
		{
			if (bufferedImage->getRGBA(x, y) == 0)
			{
				for (int xx = 0; xx < 2; xx++)
				{
					for (int yy = 0; yy < 2; yy++)
					{
						hq2xBufferedImage->setRGB((x * 2) + xx, ((y * 2) + yy), 0);
					}
				}
			}
		}
	}
}

void Map::addEntitiesAndCharactersFromCurrentStateToActiveEntityList()
{ //=========================================================================================================================


	for (int n = 0; n < (int)currentState->entityList.size(); n++)
	{
		sp<Entity> ms = currentState->entityList.at(n);
		activeEntityList.push_back(ms);
	}

	for (int n = 0; n < (int)currentState->characterList.size(); n++)
	{
		sp<Character> ms = currentState->characterList.at(n);
		activeEntityList.push_back(ms);
	}

	if (getPlayer() != nullptr && getClientGameEngine()->playerExistsInMap)
	{
		activeEntityList.push_back(getPlayer());
	}
}

void Map::clearActiveEntityList()
{ //=========================================================================================================================

	//have to release unique textures on random entities
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		sp<Entity> e = activeEntityList.at(i);
		if ((dynamic_cast<RandomCharacter*>(e.get()) != NULL))
		{
			sp<RandomCharacter> r = static_cast<sp<RandomCharacter>>(e);
			if (r->uniqueTexture != nullptr)
			{
				r->uniqueTexture->release();
				delete r->uniqueTexture;
				r->uniqueTexture = nullptr;
			}
		}
	}

	activeEntityList.clear();
	//if(getPlayer()!=null)entityList.push_back(getPlayer());
	//entityList.push_back(getCameraman());
}

bool Map::isAnyoneOverlappingXY(float x, float y)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		sp<Entity> e = activeEntityList.at(i);

		if (x > e->getLeft() && x < e->getRight() && y > e->getTop() && y < e->getBottom())
		{
			return true;
		}
	}

	return false;
}

bool Map::isAnyoneOverlappingXYXY(float x, float y, float x2, float y2)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		sp<Entity> e = activeEntityList.at(i);

		if (x < e->getRight() && x2 > e->getLeft() && y < e->getBottom() && y2 > e->getTop())
		{
			return true;
		}
	}

	return false;
}

bool Map::isAnyRandomCharacterTryingToGoToXY(float x, float y)
{ //=========================================================================================================================
	for (int i = 0; i < activeEntityList.size(); i++)
	{
		//find any characters
		sp<Entity> e = activeEntityList.at(i);

		if ((dynamic_cast<RandomCharacter*>(e.get()) != NULL))
		{
			sp<RandomCharacter> c = ms<RandomCharacter>(e.get());

			if (x == c->targetX && y == c->targetY)
			{
				return true;
			}
		}
	}

	return false;
}

int* Map::findOpenSpaceInArea(sp<Area> a, int w, int h)
{ //=========================================================================================================================

	vector<int*> coords;// = new vector<int>();

	for (int x = 1; x < a->getWidth() / 8; x++)
	{
		for (int y = 1; y < a->getHeight() / 8; y++)
		{
			int* xy = new int[2];
			xy[0] = x;
			xy[1] = y;
			coords.push_back(xy);
		}
	}

	while (coords.size() > 0)
	{
		int i = Math::randLessThan(coords.size());
		int* xy = coords.at(i);
		int x = xy[0];
		int y = xy[1];

		if (isAnyoneOverlappingXYXY((float)a->getX() + (x * 8 - w / 2), (float)a->getY() + (y * 8 - h / 2), (float)a->getX() + (x * 8 + w / 2), (float)a->getY() + (y * 8 + h / 2)) == false && isAnyRandomCharacterTryingToGoToXY(a->getX() + a->getWidth() / 2, a->getY() + a->getHeight() / 2) == false)
		{
			//TODO: could also check all the other random characters targetX and targetY to make sure nobody is TRYING to go here


			int* finalcoords = new int[2];
			finalcoords[0] = (int)(a->getX() + x * 8);
			finalcoords[1] = (int)(a->getY() + y * 8);

			return finalcoords;
		}
		else
		{
			coords.erase(coords.begin()+i);
		}
	}
	return nullptr;
}

bool Map::isAnyCharacterTouchingArea(sp<Area> a)
{ //=========================================================================================================================

	//go through all entities, if somebody is standing here, don't go there.

	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			sp<Entity> e = activeEntityList.at(i);

			if (
				(
					(
						(
							(dynamic_cast<Character*>(e.get()) != NULL)
							||
							(dynamic_cast<RandomCharacter*>(e.get()) != NULL)
						)
					)
					||
					(dynamic_cast<Player*>(e.get()) != NULL)
				)
				&&
				a->isEntityHitBoxTouchingMyBoundary(e)
			)
			//&&
			//m.getNonWalkable==true
			{
				return true;
			}
		}
	}

	return false;
}

bool Map::isAnyEntityTouchingArea(sp<Area> a)
{ //=========================================================================================================================

	//go through all entities, if somebody is standing here, don't go there.

	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			sp<Entity> e = activeEntityList.at(i);

			if (a->isEntityHitBoxTouchingMyBoundary(e))
			{
				return true;
			}
		}
	}

	return false;
}

sp<vector<sp<Entity>>> Map::getAllEntitiesTouchingArea(sp<Area> a)
{ //=========================================================================================================================

	sp<vector<sp<Entity>>> entitiesInArea;// = ms<ArrayList><sp<Entity>>();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		sp<Entity> e = activeEntityList.at(i);

		if (a->isEntityHitBoxTouchingMyBoundary(e))
		{
			entitiesInArea->push_back(e);
		}
	}

	return entitiesInArea;
}

sp<vector<sp<Entity>>> Map::getAllEntitiesPlayerIsTouching()
{ //=========================================================================================================================

	sp<vector<sp<Entity>>> entitiesTouching;// = ms<ArrayList><sp<Entity>>();


	for (int i = 0; i < activeEntityList.size(); i++)
	{
		sp<Entity> e = activeEntityList.at(i);

		if (getPlayer()->isEntityHitBoxTouchingMyHitBox(e))
		{
			entitiesTouching->push_back(e);
		}
	}

	return entitiesTouching;
}

bool Map::isAnyoneTryingToGoToArea(sp<Area> a)
{ //=========================================================================================================================
	if (a != nullptr) //DEBUG HERE
	{
		for (int i = 0; i < activeEntityList.size(); i++)
		{
			if (activeEntityList.at(i)->currentAreaTYPEIDTarget == a->getName())
			{
				return true;
			}
		}
	}
	return false;
}

bool Map::isAnyEntityUsingSpriteAsset(sp<Sprite> s)
{ //=========================================================================================================================

	for (int i = 0; i < activeEntityList.size(); i++)
	{
		if (activeEntityList.at(i)->sprite == s)
		{
			return true;
		}
	}


	return false;
}

sp<vector<sp<Entity>>> Map::getAllEntitiesUsingSpriteAsset(sp<Sprite> s)
{ //=========================================================================================================================

	sp<vector<sp<Entity>>> entitiesUsingSprite;// = ms<vector><sp<Entity>>();

	for (int i = 0; i < activeEntityList.size(); i++)
	{
		sp<Entity> e = activeEntityList.at(i);

		if (e->sprite == s)
		{
			entitiesUsingSprite->push_back(e);
		}
	}


	return entitiesUsingSprite;
}

sp<Entity> Map::createEntity(const string& spriteName, sp<Sprite> spriteAsset, float mapX, float mapY)
{ //=========================================================================================================================


	sp<EntityData> entityData = ms<EntityData>(-1, spriteName, spriteAsset->getName(), (int)(mapX / 2), (int)(mapY / 2));

	sp<Entity> e = ms<Entity>(getEngine(), entityData, shared_from_this());

	getCurrentMap()->currentState->entityList.push_back(e);
	getCurrentMap()->currentState->entityByNameHashtable.put(e->getName(),e);

	return e;
}

sp<Entity> Map::createEntityFeetAtXY(const string& spriteName, sp<Sprite> sprite, float mapX, float mapY)
{ //=========================================================================================================================

	// use hitbox center instead of arbitrary offset
	sp<SpriteAnimationSequence> a = sprite->getFirstAnimation();
	int hitBoxYCenter = (a->hitBoxFromTopPixels1X) + (((sprite->getImageHeight() - (a->hitBoxFromTopPixels1X)) - (a->hitBoxFromBottomPixels1X)) / 2);

	return createEntity(spriteName, sprite, mapX - (sprite->getImageWidth() / 2), mapY - (hitBoxYCenter));
}

sp<Entity> Map::createEntityIfWithinRangeElseDelete_MUST_USE_RETURNVAL(sp<Entity> e, const string& spriteName, sp<Sprite> sprite, float mapX, float mapY, int amt)
{ //=========================================================================================================================

	if (isXYWithinScreenByAmt(mapX + sprite->getImageWidth() / 2, mapY + sprite->getImageHeight() / 2, amt) == true)
	{
		if (e == nullptr)
		{
			return createEntity(spriteName, sprite, mapX, mapY);
		}
		else
		{
			return e;
		}
	}
	else
	{
		if (e != nullptr)
		{
			e->deleteFromMapEntityListAndReleaseTexture();
			//delete e;
			e = nullptr;
		}
		return nullptr;
	}
}

sp<Entity> Map::createEntityAtArea(const string& spriteName, sp<Sprite> spriteAsset, sp<Area> a)
{ //=========================================================================================================================
	float x = a->middleX();
	float y = a->middleY();

	return createEntityFeetAtXY(spriteName, spriteAsset, x, y);
}

sp<MapData> Map::getData()
{
	return data;
}

int Map::getID()
{
	return data->getID();
}


string& Map::getName()
{
	return data->getName();
}


string& Map::getMapNote()
{
	return data->getMapNote();
}

int Map::getWidthTiles1X()
{
	return data->getWidthTiles1X();
}

int Map::getHeightTiles1X()
{
	return data->getHeightTiles1X();
}

int Map::getWidthPixelsHQ()
{
	return data->getWidthPixelsHQ();
}

int Map::getHeightPixelsHQ()
{
	return data->getHeightPixelsHQ();
}

int Map::getMaxRandoms()
{
	return data->getMaxRandoms();
}

bool Map::getIsOutside()
{
	return data->getIsOutside();
}


string Map::getTYPEIDString()
{
	return data->getTYPEIDString();
}


string& Map::getGroundLayerMD5()
{
	return getData()->getGroundLayerMD5();
}


string& Map::getGroundObjectsMD5()
{
	return getData()->getGroundObjectsMD5();
}


string& Map::getGroundShadowMD5()
{
	return getData()->getGroundShadowMD5();
}


string& Map::getObjectsMD5()
{
	return getData()->getObjectsMD5();
}


string& Map::getObjects2MD5()
{
	return getData()->getObjects2MD5();
}


string& Map::getObjectShadowMD5()
{
	return getData()->getObjectShadowMD5();
}


string& Map::getAboveMD5()
{
	return getData()->getAboveMD5();
}


string& Map::getAbove2MD5()
{
	return getData()->getAbove2MD5();
}


string& Map::getSpriteShadowMD5()
{
	return getData()->getSpriteShadowMD5();
}


string& Map::getGroundShaderMD5()
{
	return getData()->getGroundShaderMD5();
}


string& Map::getCameraBoundsMD5()
{
	return getData()->getCameraBoundsMD5();
}


string& Map::getHitBoundsMD5()
{
	return getData()->getHitBoundsMD5();
}


string& Map::getLightMaskMD5()
{
	return getData()->getLightMaskMD5();
}


string& Map::getPaletteMD5()
{
	return getData()->getPaletteMD5();
}


string& Map::getTilesMD5()
{
	return getData()->getTilesMD5();
}

void Map::setGroundLayerMD5(const string& s)
{
	getData()->setGroundLayerMD5(s);
}

void Map::setGroundObjectsMD5(const string& s)
{
	getData()->setGroundObjectsMD5(s);
}

void Map::setGroundShadowMD5(const string& s)
{
	getData()->setGroundShadowMD5(s);
}

void Map::setObjectsMD5(const string& s)
{
	getData()->setObjectsMD5(s);
}

void Map::setObjects2MD5(const string& s)
{
	getData()->setObjects2MD5(s);
}

void Map::setObjectShadowMD5(const string& s)
{
	getData()->setObjectShadowMD5(s);
}

void Map::setAboveMD5(const string& s)
{
	getData()->setAboveMD5(s);
}

void Map::setAbove2MD5(const string& s)
{
	getData()->setAbove2MD5(s);
}

void Map::setSpriteShadowMD5(const string& s)
{
	getData()->setSpriteShadowMD5(s);
}

void Map::setGroundShaderMD5(const string& s)
{
	getData()->setGroundShaderMD5(s);
}

void Map::setCameraBoundsMD5(const string& s)
{
	getData()->setCameraBoundsMD5(s);
}

void Map::setHitBoundsMD5(const string& s)
{
	getData()->setHitBoundsMD5(s);
}

void Map::setLightMaskMD5(const string& s)
{
	getData()->setLightMaskMD5(s);
}

void Map::setPaletteMD5(const string& s)
{
	getData()->setPaletteMD5(s);
}

void Map::setTilesMD5(const string& s)
{
	getData()->setTilesMD5(s);
}

