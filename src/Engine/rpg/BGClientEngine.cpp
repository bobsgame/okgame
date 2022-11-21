#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once


#include "BGClientEngine.h"
#include "../../Utility/FileUtils.h"

Logger BGClientEngine::log = Logger("BGClientEngine");

bool BGClientEngine::debugMode = true;

BGClientEngine::BGClientEngine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("BGClientEngine()");
#endif
}

BGClientEngine::~BGClientEngine()
{ //=========================================================================================================================

#ifdef _DEBUG
	log.info("~BGClientEngine()");
#endif



}

void BGClientEngine::init()
{ //=========================================================================================================================


	super::init();


#ifdef _DEBUG
	log.info("BGClientEngine::init()");
#endif
	

	clock = ms<Clock>(this);

	player = ms<Player>(this);
	normalPlayer = player;

	guiManager = ms<GUIManager>(this);

	statusBar = ms<StatusBar>(this);
	wallet = ms<Wallet>(this);

	friendManager = ms<FriendManager>(this);

	nD = new ND();
	stadiumScreen = ms<StadiumScreen>(this);


	if (Main::previewClientInEditor == false)
	{
		loadPreCachedObjectData();
	}


	guiManager->init();

	statusBar->init();

	wallet->init();


	nD->init();

	sp<NDMenu> nDMenu = ms<NDMenu>(nD);
	nDMenu->init();
	

	sp<OKGame> bobsgame = ms<OKGame>(nD);
	bobsgame->init();
	

	sp<Ping> ping = ms<Ping>(nD);
	ping->init();
	

	sp<Ramio> ramio = ms<Ramio>(nD);
	ramio->init();
	


	nDMenu->addGame(ping, "Ping", OKColor::blue);
	nDMenu->addGame(ramio,"Ramio",OKColor::red);
	nDMenu->addGame(bobsgame,"\"bob's game\"",OKColor::green);

	nD->setGame(nDMenu);


	friendManager->init();

	//mapManager->changeMap("ALPHAOKApartment","atDesk");
	//mapManager->changeMap("ALPHAOKElevator","center");
	//mapManager->changeMap("TOWNYUUDownstairs",30,18);
	//mapManager.changeMap("TOWNVideoRentAdultRoom",10,10);
	//mapManager.changeMap("CITYTheCafe",10,10);
	//mapManager.changeMap("TOWNTacoBurger",53,110);
	//mapManager.changeMap("BLANK",16,16);
	//mapManager.changeMap("TOWNCoffeeShop",53,110);//start nowhere
	//mapManager.changeMap("CITYCityHallEntrance",53,110);
	//mapManager.changeMap("CITYStadiumBackstage",80,140);
	//mapManager.changeMap("TOWNPets4Less",53,110);
	//mapManager.changeMap("TOWNMovieTheatreMensBathroom",53,110);

	cameraman->setTarget(player);


	//can't remember why i did this, to fix gui stuff???
	cameraman->update(); //TODO: fix this so it only updates ONE TICK


	cameraman->setXYToTarget(); //TODO: fix this so it goes to xtarget (camstop tiles) instead of just npc target (player)


	//itemManager.ITEM_get_no_caption(ms<Item>("nD","The indie handheld Game() console. A juggernaut of disposable technology, devised as a vengeful scheme to destroy the traditional Game() industry. Invented by a secretive, notoriously stubborn developer whose first Game() was held back by corrupt, obsolete corporate policy. So cheap and ubiquitous that every kid has two or three- making it a modern societal requirement."));
	//itemManager.ITEM_get_no_caption(ms<Item>("Wallet","This holds your old receipts, slowly rubbing the ink off so the paper can be reused to write down phone numbers- if only you had a pen!"));
	//itemManager.ITEM_get_no_caption(ms<Item>("Keys","These relics of long-antiquated technology give an illusion of security. Easily lost, they weigh down your pants, scratch everything in your pockets, and are generally uncomfortable, noisy metal daggers. Don't ever leave home without them!"));
	//itemManager.ITEM_get_no_caption(ms<Item>("Smartphone","This infinitely helpful device keeps you constantly distracted and tracks your every move for a huge monthly fee. Sometimes you begin to wonder if it is making you more impulsive and helpless, and are fortunately comforted by its glow just as panic sets in. Scientists are pretty sure it doesn't cause brain cancer!"));


	//ms<EasingTest>();

	//cinematicsManager.toggleLetterbox(true);
	//textManager.getText("Yuu normal font <TINY>tiny font <SMALL><GREEN>small font <WHITE><HUGE>huge font <.><SMALL><NORMAL><NEXTLINE>next line <1>top getText box<0>bottom getText box");

	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_SCREEN,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_SCREEN",0,Color.white,Color.black,4,1.0f,0);
	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_OVER_SPRITE,0,-1,"CAPTION_CENTERED_OVER_SPRITE",0,Color.white,Color.black,4,1.0f,0);
	//captionManager.CAPTION_make_caption(Caption.CAPTION_CENTERED_X,0,Caption.CAPTION_DELETE_WHEN_MAIN_SPRITE_MOVES,"CAPTION_CENTERED_X",0,Color.white,Color.black,4,1.0f,0);


	//ms<Notification>("This is the notification area.");
	//ms<Notification>("This is the notification area. Important messages will show up here periodically to let you know about events or whatever.");
}





//The following method was originally marked 'synchronized':
void BGClientEngine::setGameInitializedFromSave_S(bool b)
{
	_isGameInitializedFromSave = b;
}

//The following method was originally marked 'synchronized':
bool BGClientEngine::getGameInitializedFromSave_S()
{
	return _isGameInitializedFromSave;
}


//The following method was originally marked 'synchronized':
void BGClientEngine::setProjectLoadEventID_S(int id)
{ //=========================================================================================================================
	_projectLoadEventID = id;
}

//The following method was originally marked 'synchronized':
int BGClientEngine::getProjectLoadEventID_S()
{ //=========================================================================================================================
	return _projectLoadEventID;
}

bool BGClientEngine::getFinishedLoadEvent()
{
	return finishedProjectLoadEvent;
}

void BGClientEngine::update()
{ //=========================================================================================================================

	
	//long long currentTime = System::currentHighResTimer();



	if (Main::introMode == true)
	{
		//getServerConnection()->setGameSave_S(ms<GameSave>());
		getServerConnection()->setInitialGameSaveReceived_S(true);
		setGameInitializedFromSave_S(true);

		guiManager->update();
	}
	else
	{
		if (getServerConnection()->getInitialGameSaveReceived_S() == false)
		{
			return;
		}


		if (isGameInitializedFromSave_nonThreaded == false)
		{
			if (getGameInitializedFromSave_S() == false)
			{
				isGameInitializedFromSave_nonThreaded = true;

				initializeGameFromSave_S();
				setPlayerAppearanceFromGameSave_S();
			}

			return;
		}




		guiManager->update();


		if (gameSaveCompleted_nonThreaded == false)
		{
			if (getGameSave_S().wasPlayerCreatedYet() == false)
			{
				if (guiManager->playerEditMenu->getIsActivated() == false)
				{
					guiManager->playerEditMenu->setActivated(true);
				}
			}
			else
			{
				gameSaveCompleted_nonThreaded = true;
			}

			return;
		}


//		if (isProjectLoadEventInitialized_nonThreaded == false)
//		{
//			long long startTime = lastSentProjectLoadEventRequestTime;
//			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
//			if (ticksPassed > 200)
//			{
//				lastSentProjectLoadEventRequestTime = currentTime;
//
//				if (getProjectLoadEventID_S() == -1)
//				{
//					sendProjectLoadEventRequest();
//				}
//				else
//				{
//					isProjectLoadEventInitialized_nonThreaded = true;
//
//					projectLoadEvent = getEventManager()->getEventByIDCreateIfNotExist(getProjectLoadEventID_S());
//					if(projectLoadEvent!=nullptr)getEventManager()->addToEventQueueIfNotThere(projectLoadEvent); //events update their own network data inside their run function
//				}
//			}
//
//			return;
//		}


		if (finishedProjectLoadEvent == false)
		{
			//wait for load event to finish
			//if (getEventManager()->isEventInQueue(projectLoadEvent) == false)
			{
				finishedProjectLoadEvent = true;

				GameSave g = getGameSave_S();


				bool updateGameSave = false;

				//if(g.startingRoom.equals("BLANK"))g.startingRoom = "GENERIC1UpstairsBedroom1";
				if (g.lastKnownRoom == "BLANK")
				{
					g.lastKnownRoom = "GENERIC1UpstairsBedroom1";
					g.lastKnownX = 17 * 8 * 2;
					g.lastKnownY = 12 * 8 * 2;
					getServerConnection()->setGameSave_S(g);
					updateGameSave = true;
				}

				getMapManager()->changeMap(g.lastKnownRoom, g.lastKnownX, g.lastKnownY, updateGameSave); // *** don't changemap in network thread! it blocks
			}
		}
	}


	handleGameEngineOptionKeys();


	super::update();


	clock->update();

	friendManager->update();


	//EasingTest.update();

	statusBar->update();

	wallet->update();

	nD->update();
	stadiumScreen->update();
}

void BGClientEngine::cleanup()
{ //=========================================================================================================================

	super::cleanup();

	guiManager->cleanup();

	friendManager->cleanup();
}

void BGClientEngine::render()
{ //=========================================================================================================================


	if (nD->getIsScrolledUp() == false)
	{
		super::render();
	}


	//GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

	nD->render();
	//stadiumScreen.render();

	//GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	statusBar->render();

	guiManager->render();

	//GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
}

bool BGClientEngine::areAnyMenusOpen()
{ //=========================================================================================================================


	if (getND()->getIsActivated() || getStuffMenu()->getIsActivated() || getPlayerEditMenu()->getIsActivated() || getGameStore()->getIsActivated())
	{
	    return true;
	}

	return false;
}

void BGClientEngine::handleGameEngineOptionKeys()
{ //=========================================================================================================================


	if (getControlsManager()->key_F1_Pressed() == true)
	{
		guiManager->keyboardScreen->toggleActivated();
	}


	if (getControlsManager()->bgClient_OPENND_Pressed() == true && nD->getIsActivated() == false)
	{
		nD->toggleActivated();
	}


	if (getControlsManager()->bgClient_OPENMENU_Pressed() == true)
	{
		guiManager->stuffMenu->toggleActivated();
	}


	if (areAnyMenusOpen())
	{
		return;
	}


	//-----------------------------
	// zoom controls
	//------------------------------

	if (getCameraman()->zoomManuallyEnabled)
	{
		if (getControlsManager()->bgClient_ZOOMOUT_Pressed() == true)
		{
			cameraman->zoomOut();
		}

		if (getControlsManager()->bgClient_ZOOMIN_Pressed() == true)
		{
			cameraman->zoomIn();
		}

		if (getControlsManager()->bgClient_ZOOMRESET_Pressed() == true)
		{
			cameraman->resetZoom();
		}

		if (getControlsManager()->BGCLIENT_QUICKZOOMOUT_HELD == true)
		{
			cameraman->quickZoomOut();
		}
		else
		{
			if (getControlsManager()->BGCLIENT_QUICKZOOMIN_HELD == true)
			{
				cameraman->quickZoomIn();
			}
			else
			{
				cameraman->resetQuickZoom();
			}
		}
	}


	if (debugMode == true)
	{
		if (getControlsManager()->key_H_Pressed() == true)
		{
			hitLayerEnabled = !hitLayerEnabled;
			Main::console->debug("Hit Layer Toggled: " + StringConverterHelper::toString(hitLayerEnabled), 1000);
		}

		if (getControlsManager()->key_TILDE_Pressed() == true)
		{
			underLayerEnabled = !underLayerEnabled;
			Main::console->debug("Under Layer Toggled: " + StringConverterHelper::toString(underLayerEnabled), 1000);
		}

		if (getControlsManager()->key_1_Pressed() == true)
		{
			entityLayerEnabled = !entityLayerEnabled;
			Main::console->debug("Entity Layer Toggled: " + StringConverterHelper::toString(entityLayerEnabled), 1000);
		}

		if (getControlsManager()->key_2_Pressed() == true)
		{
			overLayerEnabled = !overLayerEnabled;
			Main::console->debug("Over Layer Toggled: " + StringConverterHelper::toString(overLayerEnabled), 1000);
		}

		if (getControlsManager()->key_3_Pressed() == true)
		{
			lightsLayerEnabled = !lightsLayerEnabled;
			Main::console->debug("Lights Layer Toggled: " + StringConverterHelper::toString(lightsLayerEnabled), 1000);
		}

		if (getControlsManager()->key_4_Pressed() == true)
		{
			GLUtils::useShaders = !GLUtils::useShaders;
			Main::console->debug("Shader Toggled: " + to_string(GLUtils::useShaders), 1000);
		}

//		if (getControlsManager()->key_5_Pressed() == true)
//		{
//			GLUtils::useFBO = !GLUtils::useFBO;
//			Main::console->debug("FBO Toggled: " + StringConverterHelper::toString(GLUtils::useFBO), 1000);
//		}

		if (getControlsManager()->key_6_Pressed() == true)
		{
			debugLayerEnabled = !debugLayerEnabled;
			Main::console->debug("Debug Layer Toggled: " + StringConverterHelper::toString(debugLayerEnabled), 1000);
		}

		if (getControlsManager()->key_NUM2_Pressed() == true)
		{
			getMapManager()->contrast -= 0.1f;
			Main::console->debug("Contrast: " + to_string(getMapManager()->contrast), 1000);
		}

		if (getControlsManager()->key_NUM3_Pressed() == true)
		{
			getMapManager()->contrast += 0.1f;
			Main::console->debug("Contrast: " + to_string(getMapManager()->contrast), 1000);
		}

		if (getControlsManager()->key_NUM5_Pressed() == true)
		{
			getMapManager()->brightness -= 0.1f;
			Main::console->debug("Brightness: " + to_string(getMapManager()->brightness), 1000);
		}

		if (getControlsManager()->key_NUM6_Pressed() == true)
		{
			getMapManager()->brightness += 0.1f;
			Main::console->debug("Brightness: " + to_string(getMapManager()->brightness), 1000);
		}

		if (getControlsManager()->key_NUM8_Pressed() == true)
		{
			getMapManager()->saturation -= 0.1f;
			Main::console->debug("Saturation: " + to_string(getMapManager()->saturation), 1000);
		}

		if (getControlsManager()->key_NUM9_Pressed() == true)
		{
			getMapManager()->saturation += 0.1f;
			Main::console->debug("Saturation: " + to_string(getMapManager()->saturation), 1000);
		}

		if (getControlsManager()->key_NUM1_Pressed() == true)
		{
			getMapManager()->gamma -= 0.1f;
			Main::console->debug("Gamma: " + to_string(getMapManager()->gamma), 1000);
		}

		if (getControlsManager()->key_NUM4_Pressed() == true)
		{
			getMapManager()->gamma += 0.1f;
			Main::console->debug("Gamma: " + to_string(getMapManager()->gamma), 1000);
		}

		if (getControlsManager()->key_NUM0_Pressed() == true)
		{
			getMapManager()->saturation = 1.0f;
			getMapManager()->brightness = 1.0f;
			getMapManager()->contrast = 1.0f;
			getMapManager()->gamma = 1.0f;
			Main::console->debug("Saturation: " + to_string(getMapManager()->saturation) + " | Brightness: " + to_string(getMapManager()->brightness) + " | Contrast: " + to_string(getMapManager()->contrast) + " | Gamma: " + to_string(getMapManager()->gamma), 1000);
		}
	}
}

void BGClientEngine::updateDebugText()
{ //=========================================================================================================================
	Engine::updateDebugText();

	if (playerMapText == nullptr)playerMapText = Main::console->debug("playerMapText");
	if (playerScreenText == nullptr)playerScreenText = Main::console->debug("playerScreenText");

	playerMapText->text = "Player map xy: " + to_string(player->getX()) + "," + to_string(player->getY()) + " | Tiles: " + to_string(player->getX() / 8) + "," + to_string(player->getY() / 8);
	playerScreenText->text = "Player screen xy: " + to_string(player->getScreenLeft()) + "," + to_string(player->getScreenTop()) + " Player layer: " + to_string((int)player->getRenderOrder());
}

void BGClientEngine::loadPreCachedObjectData()
{ //===============================================================================================


	bool debug = true;


	sp<vector<string>> b64List = nullptr;


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSkillData");
	}
	catch (exception e)
	{
		log.error("Could not load PreloadSkillData");
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);
			if (s.length() > 0)
			{
				sp<SkillData> data = ms<SkillData>(); data->initFromString(s);

				//sp<Skill> skill =
                ms<Skill>(this, data);//adds itself to eventManager skill list in constructor
				//getEventManager()->skillList.add(skill);

				if (debug)
				{
					log.debug("Preload Skill id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadDialogueData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);
			if (s.length() > 0)
			{
				sp<DialogueData> data = ms<DialogueData>(); data->initFromString(s);
				//sp<Dialogue> m =
                ms<Dialogue>(this, data);
				//getEventManager()->dialogueList.add(m);
				if (debug)
				{
					log.debug("Preload Dialogue id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadFlagData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);
			if (s.length() > 0)
			{
				sp<FlagData> data = ms<FlagData>(); data->initFromString(s);
				//sp<Flag> m =
                ms<Flag>(this, data);
				//getEventManager()->flagList.add(m);
				if (debug)
				{
					log.debug("Preload Flag id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadGameStringData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);
			if (s.length() > 0)
			{
				sp<GameStringData> data = ms<GameStringData>(); data->initFromString(s);
				//sp<GameString> m =
                ms<GameString>(this, data);
				//getEventManager()->gameStringList.add(m);
				if (debug)
				{
					log.debug("Preload GameString id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadEventData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);
			if (s.length() > 0)
			{
				sp<EventData> data = ms<EventData>(); data->initFromString(s);
				//sp<Event> m =
                ms<Event>(this, data, "cutscene");
				//getEventManager()->eventList.add(m);
				if (debug)
				{
					log.debug("Preload Event id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSpriteData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);

			if (s.length() > 0)
			{
				sp<SpriteData> data = ms<SpriteData>(); data->initFromString(s);

				if (getSpriteManager()->spriteByIDHashMap->containsKey(data->getID()) == false)
				{
					sp<Sprite> sprite = ms<Sprite>(this);
					sprite->initializeWithSpriteData(data);

					getSpriteManager()->spriteByNameHashMap->put(data->getName(), sprite);
					getSpriteManager()->spriteByIDHashMap->put(data->getID(), sprite);
				}
				else
				{
					log.error("Sprite already exists:" + data->getName());
				}

				//System.out.println(spriteData.name);

				if (debug)
				{
					log.debug("Preload Sprite id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadSoundData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);

			if (s.length() > 0)
			{
				sp<AudioData> data = ms<AudioData>(); data->initFromString(s);

				sp<AudioFile> m = AudioManager::getAudioFileByName(data->getName());
				if (m == nullptr)
				{
					ms<AudioFile>(data);
				}
				else
				{
					m->setID(data->getID());
				}

				//just adding the md5 names for the sounds in sounds.zip to the soundList so they can be immediately accessed without server calls
				//getAudioManager()->soundList.add(m);

				//music will first ask the server

				//System.out.println(data.name);

				if (debug)
				{
					log.debug("Preload Sound id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}


	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadMusicData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);

			if (s.length() > 0)
			{
				sp<AudioData> data = ms<AudioData>(); data->initFromString(s);

				sp<AudioFile> m = AudioManager::getAudioFileByName(data->getName());
				if (m == nullptr)
				{
					ms<AudioFile>(data);
				}
				else
				{
					m->setID(data->getID());
				}

				//just adding the md5 names for PRELOADED music in music.zip to the musicList so they can be immediately accessed without server calls
				//getAudioManager()->musicList.add(m);

				if (debug)
				{
					log.debug("Preload Music id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}

	try
	{
		b64List = FileUtils::loadTextFileFromExePathIntoVectorOfStringsAndTrim("data/PreloadMapData");
	}
	catch (exception e)//IOException e)
	{
		//e->>printStackTrace();
	}
	if (b64List->size() > 0)
	{
		for (int i = 0; i < b64List->size(); i++)
		{
			string s = b64List->at(i);

			if (s.length() > 0)
			{
				sp<MapData> data = ms<MapData>(); data->initFromString(s);

				if (getMapManager()->mapByIDHashMap->containsKey(data->getID()) == false)
				{
					sp<Map> m = ms<Map>(this, data);

					getMapManager()->mapList->push_back(m);
					getMapManager()->mapByNameHashMap->put(data->getName(), m);
					getMapManager()->mapByIDHashMap->put(data->getID(), m);
				}
				else
				{
					log.error("Map already exists:" + data->getName());
				}

				if (debug)
				{
					log.debug("Preload Map id:" + to_string(data->getID()) + " name:" + data->getName());
				}
			}
		}
	}
}

//The following method was originally marked 'synchronized':
void BGClientEngine::initializeGameFromSave_S()
{ //=========================================================================================================================


	{
		//set flags, set dialogueDone values, stats values
		string itemsHeld = getGameSave_S().itemsHeld; //items are just comma separated values
		while (itemsHeld.find(",") != string::npos)
		{
			string dataString = itemsHeld.substr(0, itemsHeld.find(","));

			int itemID = -1;
			try
			{
				itemID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}


			itemsHeld = itemsHeld.substr(itemsHeld.find(",") + 1);


			sp<Item> f = getEventManager()->getItemByID(itemID);
			f->initHaveItemValue_S(value, timeSet);
		}
	}


	{
		string flagsSet = getGameSave_S().flagsSet; //flags are just comma separated values
		while (flagsSet.find(",") != string::npos)
		{
			//flag looks like id:true:timeSet,id:false:timeSet,
			string dataString = flagsSet.substr(0, flagsSet.find(","));

			int flagID = -1;
			try
			{
				flagID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}


			flagsSet = flagsSet.substr(flagsSet.find(",") + 1);

			sp<Flag> f = getEventManager()->getFlagByIDCreateIfNotExist(flagID);
			f->initValueFromGameSave_S(value, timeSet);
		}
	}


	{
		string dialoguesDone = getGameSave_S().dialoguesDone; //dialogues are just comma separated values
		while (dialoguesDone.find(",") != string::npos)
		{
			string dataString = dialoguesDone.substr(0, dialoguesDone.find(","));

			int dialogueID = -1;
			try
			{
				dialogueID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			bool value = StringConverterHelper::fromString<bool>(dataString.substr(0, dataString.find(":")));
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}

			dialoguesDone = dialoguesDone.substr(dialoguesDone.find(",") + 1);

			sp<Dialogue> d = getEventManager()->getDialogueByIDCreateIfNotExist(dialogueID);
			d->initDialogueDoneValueFromGameSave_S(value, timeSet);
		}
	}


	{
		string skillValues = getGameSave_S().skillValues; //skills look like skillID:float:time, so 199:-1.4:time,
		while (skillValues.find(",") != string::npos)
		{
			string dataString = skillValues.substr(0, skillValues.find(","));

			int skillID = -1;
			try
			{
				skillID = stoi(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			float value = -1;
			try
			{
				value = stof(dataString.substr(0, dataString.find(":")));
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}
			dataString = dataString.substr(dataString.find(":") + 1);
			long long timeSet = -1;
			try
			{
				timeSet = StringConverterHelper::fromString<long long>(dataString);
			}
			catch (exception e)//NumberFormatException ex)
			{
				//ex->printStackTrace();
				return;
			}

			skillValues = skillValues.substr(skillValues.find(",") + 1);

			sp<Skill> skill = getEventManager()->getSkillByIDCreateIfNotExist(skillID);
			skill->initValueFromGameSave_S(value, timeSet);
		}
	}

	//mapManager.changeMap("ALPHAOKApartment",18,15);//g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);
	//mapManager.changeMap(g.lastKnownRoom, g.lastKnownX/8, g.lastKnownY/8);


	setGameInitializedFromSave_S(true);
}

//The following method was originally marked 'synchronized':
void BGClientEngine::setPlayerAppearanceFromGameSave_S()
{ //=========================================================================================================================

	GameSave g = getGameSave_S();

	player->setAppearanceFromCharacterAppearanceString(g.characterAppearance);

	player->setCharacterNameAndCaption(getNameColor(g.accountRank), g.characterName, getAccountRankColor(g.accountRank), getAccountRankString(g.accountRank));
}

sp<OKColor> BGClientEngine::getNameColor(int accountType)
{ //=========================================================================================================================
	return getAccountRankColor(accountType);
}


string BGClientEngine::getAccountRankString(int accountRank)
{ //=========================================================================================================================
	string accountRankString = "Free";
	if (accountRank == 0)
	{
		accountRankString = "Free";
	}
	if (accountRank == 1)
	{
		accountRankString = "Premium";
	}
	if (accountRank == 2)
	{
		accountRankString = "nD Dev";
	}
	if (accountRank == 3)
	{
		accountRankString = "Mod";
	}
	if (accountRank == 4)
	{
		accountRankString = "Admin";
	}
	if (accountRank == 5)
	{
		accountRankString = "Champion";
	}
	if (accountRank == 6)
	{
		accountRankString = "Legend";
	}
	if (accountRank == 7)
	{
		accountRankString = "Saint";
	}
	if (accountRank == 8)
	{
		accountRankString = "Prophet";
	}
	if (accountRank == 9)
	{
		accountRankString = "Genius";
	}
	if (accountRank == 10)
	{
		accountRankString = "Uberman";
	}
	if (accountRank == 11)
	{
		accountRankString = "Angel";
	}
	if (accountRank == 12)
	{
		accountRankString = "Christ";
	}
	if (accountRank == 13)
	{
		accountRankString = "God";
	}
	if (accountRank == 14)
	{
		accountRankString = "\"bob\"";
	}

	return accountRankString;
}

sp<OKColor> BGClientEngine::getAccountRankColor(int accountRank)
{ //=========================================================================================================================
	sp<OKColor> accountRankColor = OKColor::white;
	if (accountRank == 0)
	{
		accountRankColor = OKColor::white; //"Free";
	}
	if (accountRank == 1)
	{
		accountRankColor = OKColor::purple; //"Premium";
	}
	if (accountRank == 2)
	{
		accountRankColor = OKColor::blue; //"nD Dev";
	}
	if (accountRank == 3)
	{
		accountRankColor = OKColor::red; //"Mod";
	}
	if (accountRank == 4)
	{
		accountRankColor = OKColor::red; //"Admin";
	}
	if (accountRank == 5)
	{
		accountRankColor = OKColor::red; //"Champion";
	}
	if (accountRank == 6)
	{
		accountRankColor = OKColor::red; //"Legend";
	}
	if (accountRank == 7)
	{
		accountRankColor = OKColor::red; //"Saint";
	}
	if (accountRank == 8)
	{
		accountRankColor = OKColor::red; //"Prophet";
	}
	if (accountRank == 9)
	{
		accountRankColor = OKColor::red; //"Genius";
	}
	if (accountRank == 10)
	{
		accountRankColor = OKColor::red; //"Uberman";
	}
	if (accountRank == 11)
	{
		accountRankColor = OKColor::red; //"Angel";
	}
	if (accountRank == 12)
	{
		accountRankColor = OKColor::red; //"Christ";
	}
	if (accountRank == 13)
	{
		accountRankColor = OKColor::red; //"God";
	}
	if (accountRank == 14)
	{
		accountRankColor = OKColor::green; //"\"bob\"";
	}

	return accountRankColor;
}



void BGClientEngine::setPlayerToTempPlayerWithSprite(sp<Sprite> s)
{ //=========================================================================================================================

	sp<Player> p = ms<Player>(this, s->getName());

	p->update();

	p->setX(player->getX());
	p->setY(player->getY());
	p->setSpawnXPixelsHQ(player->getX());
	p->setSpawnYPixelsHQ(player->getY());

	if (getCurrentMap() != nullptr)
	{
		for (int i = 0; i < getCurrentMap()->activeEntityList->size(); i++)
		{
			if (getCurrentMap()->activeEntityList->at(i).get() == player.get())
			{
				getCurrentMap()->activeEntityList->erase(getCurrentMap()->activeEntityList->begin()+i);
				getCurrentMap()->activeEntityList->push_back(p);
			}
		}
		//if (getCurrentMap()->activeEntityList.contains(player))
		//{
		//	getCurrentMap()->activeEntityList->remove(player);
		//	getCurrentMap()->activeEntityList->push_back(p);
		//}
	}

	if (getCameraman() != nullptr && getCameraman()->targetEntity == player)
	{
		getCameraman()->setTarget(p);
	}

	player = p;
}

void BGClientEngine::setPlayerToNormalPlayer()
{//=========================================================================================================================

	if (getCurrentMap() != nullptr)
	{

		for (int i = 0; i < getCurrentMap()->activeEntityList->size(); i++)
		{
			if (getCurrentMap()->activeEntityList->at(i).get() == player.get())
			{
				getCurrentMap()->activeEntityList->erase(getCurrentMap()->activeEntityList->begin() + i);
				getCurrentMap()->activeEntityList->push_back(normalPlayer);
			}
		}
		//if (getCurrentMap()->activeEntityList.contains(player))
		//{
		//	getCurrentMap()->activeEntityList->remove(player);
		//	getCurrentMap()->activeEntityList->push_back(normalPlayer);
		//}
	}

	if (getCameraman() != nullptr && getCameraman()->targetEntity == player)
	{
		getCameraman()->setTarget(normalPlayer);
	}

	player = normalPlayer;
}



sp<Clock> BGClientEngine::getClock()
{
	return clock;
}

sp<GUIManager> BGClientEngine::getGUIManager()
{
	return guiManager;
}

sp<StuffMenu> BGClientEngine::getStuffMenu()
{
	return getGUIManager()->stuffMenu;
}

sp<GameStore> BGClientEngine::getGameStore()
{
	return getGUIManager()->gameStore;
}

sp<PlayerEditMenu> BGClientEngine::getPlayerEditMenu()
{
	return getGUIManager()->playerEditMenu;
}

sp<Player> BGClientEngine::getPlayer()
{
	return player;
}

ND* BGClientEngine::getND()
{
	return nD;
}

sp<Wallet> BGClientEngine::getWallet()
{
	return wallet;
}

sp<FriendManager> BGClientEngine::getFriendManager()
{
	return friendManager;
}

sp<StatusBar> BGClientEngine::getStatusBar()
{
	return statusBar;
}

sp<NotificationManager> BGClientEngine::getNotificationManager()
{
	return getStatusBar()->notificationManager;
}





bool BGClientEngine::serverMessageReceived(string e)// sp<ChannelHandlerContext> ctx, sp<MessageEvent> e)
{ //===============================================================================================

	if(super::serverMessageReceived(e))
	{
		return true;
	}
	else
	if (OKString::startsWith(e, OKNet::Load_Event_Response))
	{
		incomingLoadEventResponse(e);
		return true;
	}
	return false;

}
void BGClientEngine::sendProjectLoadEventRequest()
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Load_Event_Request + OKNet::endline);
}

void BGClientEngine::incomingLoadEventResponse(string s)
{ //=========================================================================================================================

  //Event:id-name:eventData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::


	sp<EventData> data = ms<EventData>(); 
	data->initFromString(s);

	if (data == nullptr)
	{
		log.error("Load Event could not be decompressed.");
	}
	else
	{
		sp<Event> d = getEventManager()->getEventByIDCreateIfNotExist(data->getID());
		d->setData_S(data);

		setProjectLoadEventID_S(data->getID());

		if (data->getID() == -1)
		{
			log.error("Load eventID is -1");
		}
	}
}