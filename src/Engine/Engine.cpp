#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

shared_ptr<Logger> Engine::log = make_shared<Logger>("Engine");

//shared_ptr<BGClientEngine> Engine::clientGameEngine = nullptr;

//bool Engine::callNanoTimeForEachCall = false;

int Engine::totalFrames = 0;

//long long Engine::ticksPassedThisUpdate = 0;
int Engine::framesThisSecond = 0;

long long Engine::totalTicks = 0;
long long Engine::ticksThisSecond = 0;
int Engine::framesSkipped = 0;

ArrayList< shared_ptr<UDPPeerConnection>> Engine::onlineFriends;


//=========================================================================================================================
Engine::Engine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log->debug("Engine()");
#endif

}

//=========================================================================================================================
Engine::~Engine()
{ //=========================================================================================================================
#ifdef _DEBUG
	log->debug("~Engine()");
#endif
	//delete audioManager;
	//delete spriteManager;
	//delete mapManager;
	//delete cinematicsManager;
	//delete captionManager;
	//delete textManager;
	//delete eventManager;
	//delete cameraman;
	//delete actionManager;
	//delete controlsManager;
}

//=========================================================================================================================
void Engine::init()
{//=========================================================================================================================

	//super::init();

//#ifdef _DEBUG
//	log->debug("Engine::init()");
//#endif



	audioManager = make_shared<AudioManager>(this);//(shared_from_this()); ???
	spriteManager = make_shared < SpriteManager>(this);
	mapManager = make_shared < MapManager>(this);
	cinematicsManager = make_shared < CinematicsManager>(this);
	captionManager = make_shared < CaptionManager>(this);
	textManager = make_shared < TextManager>(this);
	eventManager = make_shared < EventManager>(this);
	cameraman = make_shared < Cameraman>(this);
	actionManager = make_shared < ActionManager>(this);

	controlsManager = make_shared<ControlsManager>(this);
	chatControlsManager = make_shared<ControlsManager>(this);

	activeControlsManager = controlsManager;

	textManager->init();
	cinematicsManager->init();

	GLUtils::e();

	Main::bobNet->addEngineToForwardMessagesTo(shared_from_this());


}
//=========================================================================================================================
void Engine::cleanup()
{//=========================================================================================================================
	

}

//=========================================================================================================================
void Engine::update()
{ //=========================================================================================================================

	onlineFriends.clear();
	for (int i = 0; i < (int)OKNet::udpConnections.size(); i++)
	{
		shared_ptr<UDPPeerConnection> f = OKNet::udpConnections.get(i);
		if (f->getConnectedToPeer_S() == true && 
			f->getGotFriendData_S() == true && 
			f->peerStatus == OKNet::status_AVAILABLE)
		{
			if (onlineFriends.contains(f) == false)
				onlineFriends.add(f);
		}
	}


	audioManager->update();

	textManager->update();

	captionManager->update();

	spriteManager->update();

	cameraman->update();

	mapManager->update(); //map adjusts itself based on cameraman xy so it must update after entities do

	

	actionManager->update();
	eventManager->update();
	cinematicsManager->update();


	updateDebugText();

	updateChatConsole();

}

//=========================================================================================================================
void Engine::updateChatConsole()
{//=========================================================================================================================
	
	if (chatFocused)
	{
		bool stop = false;
		if (chatControlsManager->key_ESC_Pressed())
		{
			stop = true;
		}
		else
		if (chatControlsManager->key_RETURN_Pressed())
		{
			stop = true;

			if (chatControlsManager->text != "")
			{
				getServerConnection()->sendChatMessage(chatControlsManager->text);
			}
		}
		else
		{
			if (!textStarted) { SDL_StartTextInput(); chatControlsManager->text = ""; textStarted = true; }

			if (chatConsoleText == nullptr) { chatConsoleText = Main::rightConsole->add("Say: ",OKColor::magenta); chatConsoleText->alwaysOnBottom = true; }

			chatConsoleText->text = "Say: "+chatControlsManager->text;
		}

		if(stop || chatEnabled==false)
		{
			chatControlsManager->unsetHeldButtons();
			chatFocused = false;
			activeControlsManager = controlsManager;
			
			if (textStarted) { SDL_StopTextInput(); textStarted = false; }

			chatControlsManager->text = "";
			if (chatConsoleText != nullptr)
			{
				chatConsoleText->text = "";
				chatConsoleText->ticks = 0;
				chatConsoleText = nullptr;
			}
		}

	}
	else
	{
		if (chatEnabled == true)
		{
			if (getControlsManager()->key_T_Pressed())
			{
				controlsManager->unsetHeldButtons();
				chatFocused = true;
				activeControlsManager = chatControlsManager;
			}
		}

	}

}


//=========================================================================================================================
void Engine::render()
{ //=========================================================================================================================

	//super::render();

	getMapManager()->render(); //does entities as well, multi-layered rendering here.

	getSpriteManager()->renderScreenSprites(RenderOrder::ABOVE);

	getCaptionManager()->render(RenderOrder::ABOVE);

	getSpriteManager()->renderScreenSprites(RenderOrder::ABOVE_TOP);

	getCaptionManager()->render(RenderOrder::ABOVE_TOP);

	//if(!Keyboard.isKeyDown(Keyboard.KEY_LBRACKET))GLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	getCinematicsManager()->render(RenderOrder::ABOVE_TOP);
	//if(!Keyboard.isKeyDown(Keyboard.KEY_RBRACKET))GLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	getTextManager()->render();

	getMapManager()->renderEntities(RenderOrder::OVER_TEXT);

	getSpriteManager()->renderScreenSprites(RenderOrder::OVER_TEXT); //screensprites

	getCaptionManager()->render(RenderOrder::OVER_TEXT);

	getMapManager()->renderDebug();

	getSpriteManager()->renderScreenSprites(RenderOrder::OVER_GUI);

	getCaptionManager()->render(RenderOrder::OVER_GUI);


}

void Engine::updateDebugText()
{ //=========================================================================================================================


	if (zoomText == nullptr)zoomText = Main::console->debug("zoomText");
	if (mapCamText == nullptr)mapCamText = Main::console->debug("mapCamText");
	if (mapScreenText == nullptr)mapScreenText = Main::console->debug("mapScreenText");
	if (mapSizeText == nullptr)mapSizeText = Main::console->debug("mapSizeText");
	if (resolutionText == nullptr)resolutionText = Main::console->debug("resolutionText");
	if (textText == nullptr)textText = Main::console->debug("textText");
	if (textOptionText == nullptr)textOptionText = Main::console->debug("textOptionText");


	//playerSpeedText.getText = "Player speed: " + player.pixelsToMoveThisFrame;
	//cameraSpeedText.getText = "Camera speed: " + cameraman.pixelsToMoveThisFrame;

	zoomText->text = "Zoom level: " + to_string(cameraman->getZoom()) + " ZoomTO: " + to_string(cameraman->ZOOMto);

	mapCamText->text = "Map cam xy: " + to_string(getCurrentMap()->mapCamX()) + "," + to_string(getCurrentMap()->mapCamY());
	mapScreenText->text = "Map screen xy: " + to_string(getCurrentMap()->screenX()) + "," + to_string(getCurrentMap()->screenY());

	mapSizeText->text = "Map: " + string(getCurrentMap()->getName()) + " | Size : " + to_string(getCurrentMap()->getWidthPixelsHQ()) + " x " + to_string(getCurrentMap()->getHeightPixelsHQ()) + " PixelsHQ | " + to_string(getCurrentMap()->getWidthTiles1X()) + " x " + to_string(getCurrentMap()->getHeightTiles1X()) + " Tiles 1X ";

	resolutionText->text = "Viewport res: " + to_string(getWidth()) + " x " + to_string(getHeight()) + " (" + to_string((int)(getWidth()) / 2 / cameraman->getZoom()) + " x " + to_string((int)(getHeight()) / 2 / cameraman->getZoom()) + ")";

	textText->text = "Text: " + textManager->currentText;
	textOptionText->text = "Text option: " + textManager->optionBuffer;


}

void* Engine::getGameObjectByTYPEIDName(const string& typeIDName)
{ //=========================================================================================================================


	//typeIDName always looks like TYPE.id
	//MUSIC.1
	//DIALOGUE.0f
	//STATE.4
	//AREA.15

	//areas, entities, and lights are map-specific and are created when the map loads, and destroyed when the map changes.
	//they always have the same ID when they are created, but they may not exist if the map is not loaded.

	//this function is intended to be called when event parameters are parsed,
	//upon loading new events inside of objects (inside of maps), because objects are referenced by id name inside event strings send from the server,
	//based on the exported IDs from the tools, which indexes everything uniquely.
	//therefore all of the objects that a script references will exist inside the map the event is being called from.
	//these references will break every time the map is loaded and unloaded and the objects are destroyed, so an event must re-parse all the parameters each time the map is loaded.

	int id = -1;
	
	try
	{
		id = stoi(typeIDName.substr(typeIDName.find(".") + 1));
	}
	catch (exception)
	{
		log->error("Could not parse id in typeIDName");
	}
	


	//global objects
	if (OKString::startsWith(typeIDName, "MAP."))
	{
		return getMapManager()->getMapByIDBlockUntilLoaded(id).get();
	}
	if (OKString::startsWith(typeIDName, "SPRITE."))
	{
		return getSpriteManager()->getSpriteAssetByIDOrRequestFromServerIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "DIALOGUE."))
	{
		return getEventManager()->getDialogueByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "CUTSCENEEVENT."))
	{
		return getEventManager()->getEventByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "EVENT."))
	{
		return getEventManager()->getEventByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "FLAG."))
	{
		return getEventManager()->getFlagByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "SKILL."))
	{
		return getEventManager()->getSkillByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "GAMESTRING."))
	{
		return getEventManager()->getGameStringByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "MUSIC."))
	{
		return getAudioManager()->getSoundByIDCreateIfNotExist(id).get();
	}
	if (OKString::startsWith(typeIDName, "SOUND."))
	{
		return getAudioManager()->getSoundByIDCreateIfNotExist(id).get();
	}


	//map objects (will only exist within the current map)
	if (OKString::startsWith(typeIDName, "STATE."))
	{
		return getMapManager()->getMapStateByID(id).get();
	}
	if (OKString::startsWith(typeIDName, "ENTITY."))
	{
		return getMapManager()->getEntityByID(id).get();
	}
	if (OKString::startsWith(typeIDName, "AREA."))
	{
		return getMapManager()->getAreaByID(id).get();
	}
	if (OKString::startsWith(typeIDName, "LIGHT."))
	{
		return getMapManager()->getLightByID(id).get();
	}
	if (OKString::startsWith(typeIDName, "DOOR."))
	{
		return getMapManager()->getDoorByID(id).get();
	}


	return nullptr;
}

shared_ptr<Cameraman> Engine::getCameraman()
{
	return cameraman;
}

shared_ptr<MapManager> Engine::getMapManager()
{
	return mapManager;
}

shared_ptr<SpriteManager> Engine::getSpriteManager()
{
	return spriteManager;
}

shared_ptr<ActionManager> Engine::getActionManager()
{
	return actionManager;
}

shared_ptr<TextManager> Engine::getTextManager()
{
	return textManager;
}

shared_ptr<AudioManager> Engine::getAudioManager()
{
	return audioManager;
}

shared_ptr<CaptionManager> Engine::getCaptionManager()
{
	return captionManager;
}

shared_ptr<EventManager> Engine::getEventManager()
{
	return eventManager;
}

shared_ptr<CinematicsManager> Engine::getCinematicsManager()
{
	return cinematicsManager;
}

shared_ptr<Map> Engine::getCurrentMap()
{
	shared_ptr<Map> m = mapManager->currentMap;
	if (m == nullptr)
	{
		m = make_shared<Map>(this, make_shared<MapData>(-1, "none", 0, 0));
	}
	return m;
}


//void Engine::setClientGameEngine(shared_ptr<BGClientEngine> clientGameEngine)
//{
//	Engine::clientGameEngine = clientGameEngine;
//	EnginePart::setClientGameEngine(clientGameEngine);
//}


//void Engine::setControlsManager(shared_ptr<ControlsManager> controlsManager)
//{
//	controlsManager = controlsManager;
//	
//}

//shared_ptr<BGClientEngine> Engine::getClientGameEngine()
//{
//	return clientGameEngine;
//}


//=========================================================================================================================
void Engine::updateTimers()
{//=========================================================================================================================
	framesThisSecond++;
	totalFrames++;

	totalTicks += realWorldTicksPassed();
	ticksThisSecond += realWorldTicksPassed();

	if (ticksThisSecond >= 1000)
	{
		ticksThisSecond = 0;

		//log->info("" + to_string(rendersThisSecond));
		framesThisSecond = 0;
	}

	//if(ticksPassedThisUpdate>17)ticksPassedThisUpdate=17; //TODO: this is frameskip off, basically. game will slow down instead
	if (realWorldTicksPassed() > 16 * 2)
	{
		framesSkipped++; //= ticksPassedThisUpdate/16;
	}
}


void Engine::setEngineSpeed(double f)
{ //=========================================================================================================================
	engineSpeed = f;
}

int Engine::engineTicksPassed()
{ //=========================================================================================================================

  //	if (callNanoTimeForEachCall == true)
  //	{
  //
  //
  //		long long currentHighResTime = System::currentHighResTimer();
  //
  //		int ticksPassed = (long long)((double)(currentHighResTime - lastRenderHighResTime) / System::cpuFreq);
  //
  //		return static_cast<long long>(ticksPassed * engineSpeed);
  //	}
  //	else
	{
		return (int)(System::ticksPassedThisUpdate * engineSpeed);
	}

	//DONE: can multiply this to speed up game, divide it to slow game down!
}

int Engine::realWorldTicksPassed()
{ //=========================================================================================================================

  //	if (callNanoTimeForEachCall == true)
  //	{
  //		currentHighResTime = System::currentHighResTimer();
  //
  //		int ticksPassed = (long long)((double)(currentHighResTime - lastRenderHighResTime) / System::cpuFreq);
  //
  //		return static_cast<long long>(ticksPassed);
  //	}
  //	else
	{
		return (int)(System::ticksPassedThisUpdate);
	}

	//DONE: can multiply this to speed up game, divide it to slow game down!
}

void Engine::updateControls()
{
	resetPressedButtons();
	setButtonStates();
}

void Engine::resetPressedButtons()
{
	getActiveControlsManager()->resetPressedButtons();
}

void Engine::setButtonStates()
{
	getActiveControlsManager()->setButtonStates();
}

shared_ptr<ControlsManager> Engine::getControlsManager()
{
	return controlsManager;
}

shared_ptr<ControlsManager> Engine::getActiveControlsManager()
{
	return activeControlsManager;
}

shared_ptr<BGClientEngine> Engine::getClientGameEngine()
{
	return Main::gameEngine;
}

shared_ptr<TCPServerConnection> Engine::getServerConnection()
{
	return Main::bobNet->tcpServerConnection;
}

long long Engine::getUserID_S()
{
	return getGameSave_S().userID;
}

string Engine::getUserName_S()
{
	return getGameSave_S().userName;
}

GameSave Engine::getGameSave_S()
{
	return getServerConnection()->getGameSave_S();
}

void Engine::setGameSave_S(GameSave& g)
{
	getServerConnection()->setGameSave_S(g);
}

int Engine::getWidth()
{
	return GLUtils::getViewportWidth();
}

int Engine::getHeight()
{
	return GLUtils::getViewportHeight();
}

bool Engine::udpPeerMessageReceived(shared_ptr<UDPPeerConnection> c, string s)
{
	return false;
}

//bool Engine::serverMessageReceived(string cs)
//{
//	//override this!
//	return false;
//}



float Engine::getWidthRelativeToZoom()
{
	return getWidth() / getCameraman()->getZoom();
}

float Engine::getHeightRelativeToZoom()
{
	return getHeight() / getCameraman()->getZoom();
}



bool Engine::serverMessageReceived(string e)// shared_ptr<ChannelHandlerContext> ctx, shared_ptr<MessageEvent> e)
{ //===============================================================================================


  //Print out the line received from the server.
  //
  //   try
  //   {
  //      Thread::currentThread().setName("ClientTCP_OKGameClientHandler");
  //   }
  //   catch (SecurityException ex)
  //   {
  //      ex->printStackTrace();
  //   }



	string s = e;


//	if (super::serverMessageReceived(e))
//	{
//		return true;
//	}
//	else
	if (OKString::startsWith(s, OKNet::Sprite_Response))
	{
		incomingSpriteData(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Map_Response))
	{
		incomingMapData(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Dialogue_Response))
	{
		incomingDialogue(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Flag_Response))
	{
		incomingFlag(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Skill_Response))
	{
		incomingSkill(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Event_Response))
	{
		incomingEvent(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::GameString_Response))
	{
		incomingGameString(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Music_Response))
	{
		incomingMusic(s);
		return true;
	}
	else
	if (OKString::startsWith(s, OKNet::Sound_Response))
	{
		incomingSound(s);
		return true;
	}
	return false;


}




void Engine::sendSpriteDataRequestByName(string spriteAssetName)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Sprite_Request_By_Name + spriteAssetName + OKNet::endline);
}

void Engine::sendSpriteDataRequestByID(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Sprite_Request_By_ID + to_string(id) + OKNet::endline);
}

void Engine::incomingSpriteData(string s)
{ //=========================================================================================================================

  //Sprite:id-getSpriteName:spriteData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<SpriteData> data = make_shared<SpriteData>(); data->initFromString(s);


	if (data == nullptr)
	{
		log->error("Sprite could not be decompressed.");
	}
	else
	{
		shared_ptr<Sprite> sprite = nullptr;
		if(getSpriteManager()->spriteByNameHashMap.containsKey(data->getName()))
		sprite = getSpriteManager()->spriteByNameHashMap.get(data->getName());

		if (sprite == nullptr)
		{
			sprite = make_shared<Sprite>(this);
		}

		sprite->initializeWithSpriteData(data);

		getSpriteManager()->spriteByNameHashMap.put(sprite->getName(), sprite);
		getSpriteManager()->spriteByIDHashMap.put(sprite->getID(), sprite);
	}
}

void Engine::sendMapDataRequestByName(string mapName)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Map_Request_By_Name + mapName + OKNet::endline);
}

void Engine::sendMapDataRequestByID(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Map_Request_By_ID + to_string(id) + OKNet::endline);
}

void Engine::incomingMapData(string s)
{ //=========================================================================================================================

  //Map:id-name:Base64->GZip->GSON/JSON->MapData[Lights,Entities,Events,States,Areas,Doors,Characters]
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<MapData> data = make_shared<MapData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Map could not be decompressed.");
	}
	else
	{
		if (getMapManager()->mapByNameHashMap.containsKey(data->getName()) == false)
		{
			shared_ptr<Map> m = make_shared<Map>(this, data);
			getMapManager()->mapList.add(m);
			getMapManager()->mapByNameHashMap.put(data->getName(), m);
			getMapManager()->mapByIDHashMap.put(data->getID(), m);
		}
	}
}

void Engine::sendServerObjectRequest(shared_ptr<ServerObject> serverObject)
{ //====================================================
     if(dynamic_cast<Dialogue*>(serverObject.get()) != nullptr)
     {
        sendDialogueRequest((static_cast<Dialogue*>(serverObject.get()))->getID());
     }
     if (dynamic_cast<Flag*>(serverObject.get()) != nullptr)
     {
        sendFlagRequest((static_cast<Flag*>(serverObject.get()))->getID());
     }
     if (dynamic_cast<GameString*>(serverObject.get()) != nullptr)
     {
        sendGameStringRequest((static_cast<GameString*>(serverObject.get()))->getID());
     }
     if (dynamic_cast<Skill*>(serverObject.get()) != nullptr)
     {
        sendSkillRequest((static_cast<Skill*>(serverObject.get()))->getID());
     }
     if (dynamic_cast<Event*>(serverObject.get()) != nullptr)
     {
        sendEventRequest((static_cast<Event*>(serverObject.get()))->getID());
     }
     if (dynamic_cast<AudioFile*>(serverObject.get()) != nullptr)
     {
        sendSoundRequest((static_cast<AudioFile*>(serverObject.get()))->getID());
     }

}

void Engine::sendDialogueRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Dialogue_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingDialogue(string s)
{ //=========================================================================================================================

	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

								   //Dialogue:id-name:base64Blob

	shared_ptr<DialogueData> data = make_shared<DialogueData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Dialogue could not be decompressed.");
	}
	else
	{
		shared_ptr<Dialogue> d = getEventManager()->getDialogueByIDCreateIfNotExist(data->getID());
		d->setData_S(data);
	}
}


void Engine::sendEventRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Event_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingEvent(string s)
{ //=========================================================================================================================

  //Event:id-name:eventData
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::


	shared_ptr<EventData> data = make_shared<EventData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Event could not be decompressed.");
	}
	else
	{
		//shared_ptr<Event> d = 
			getEventManager()->getEventByIDCreateIfNotExist(data->getID());
		//if (d == nullptr)d = make_shared<Event>(this, data, "cutscene");
	}
}

void Engine::sendGameStringRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::GameString_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingGameString(string s)
{ //=========================================================================================================================


  //GameString:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<GameStringData> data = make_shared<GameStringData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("GameString could not be decompressed.");
	}
	else
	{
		shared_ptr<GameString> gameString = getEventManager()->getGameStringByIDCreateIfNotExist(data->getID());
		gameString->setData_S(data);
	}
}

void Engine::sendFlagRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Flag_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingFlag(string s)
{ //=========================================================================================================================


  //Flag:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<FlagData> data = make_shared<FlagData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Flag could not be decompressed.");
	}
	else
	{
		shared_ptr<Flag> flag = getEventManager()->getFlagByIDCreateIfNotExist(data->getID());
		flag->setData_S(data);
	}
}

void Engine::sendSkillRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Skill_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingSkill(string s)
{ //=========================================================================================================================


  //Skill:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<SkillData> data = make_shared<SkillData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Skill could not be decompressed.");
	}
	else
	{
		shared_ptr<Skill> skill = getEventManager()->getSkillByIDCreateIfNotExist(data->getID());
		skill->setData_S(data);
	}
}

void Engine::sendMusicRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Music_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingMusic(string s)
{ //=========================================================================================================================

  //Music:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<AudioData> data = make_shared<AudioData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Music could not be decompressed.");
	}
	else
	{
		shared_ptr<AudioFile> music = AudioManager::getAudioFileByIDCreateIfNotExist(data->getID());
		music->setData_S(data);
	}
}

void Engine::sendSoundRequest(int id)
{ //=========================================================================================================================
	getServerConnection()->connectAndAuthorizeAndQueueWriteToChannel_S(OKNet::Sound_Request + to_string(id) + OKNet::endline);
}

void Engine::incomingSound(string s)
{ //=========================================================================================================================


  //Sound:id:data
	s = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1); //intentional ::

	shared_ptr<AudioData> data = make_shared<AudioData>(); data->initFromString(s);

	if (data == nullptr)
	{
		log->error("Sound could not be decompressed.");
	}
	else
	{
		shared_ptr<AudioFile> sound = AudioManager::getAudioFileByIDCreateIfNotExist(data->getID());
		sound->setData_S(data);
	}
}

