//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"

class Logger;

//#include "./state/State.h"
#include "src/Utility/Console.h"
#include "src/Utility/ConsoleText.h"
//#include "src/Utility/ControlsManager.h"
//#include "src/Utility/audio/AudioManager.h"

class ControlsManager;
class AudioManager;
class BGClientEngine;
class Cameraman;
class SpriteManager;
class ActionManager;
class CinematicsManager;
class TextManager;
class EventManager;
class MapManager;
class Map;
class Wallet;
class Clock;
class GameSave;
class GUIManager;
class StuffMenu;
class GameStore;
class PlayerEditMenu;
class Player;
class ND;
class FriendManager;
class StatusBar;
class NotificationManager;
class ServerObject;
class Event;
class UDPPeerConnection;
class TCPServerConnection;

class Engine : public std::enable_shared_from_this<Engine>// : public State
{
//private:
	//typedef State super;
public:
	

	//static Logger log;
	static sp<Logger> log;

	//sp<AudioManager> audioManager = nullptr;
	//sp<Cameraman> cameraman = nullptr;
	//sp<SpriteManager> spriteManager = nullptr;
	//sp<ActionManager> actionManager = nullptr;
	//sp<MapManager> mapManager = nullptr;
	//sp<CinematicsManager> cinematicsManager = nullptr;
	//sp<CaptionManager> captionManager = nullptr;
	//sp<TextManager> textManager = nullptr;
	//sp<EventManager> eventManager = nullptr;

	sp<AudioManager> audioManager = nullptr;
	sp<Cameraman> cameraman = nullptr;
	sp<SpriteManager> spriteManager = nullptr;
	sp<ActionManager> actionManager = nullptr;
	sp<MapManager> mapManager = nullptr;
	sp<CinematicsManager> cinematicsManager = nullptr;
	sp<CaptionManager> captionManager = nullptr;
	sp<TextManager> textManager = nullptr;
	sp<EventManager> eventManager = nullptr;


	static vector<sp<UDPPeerConnection>> onlineFriends;

	double engineSpeed = 1.0;

private:
	static int totalFrames;

	//static long long ticksPassedThisUpdate;

	static int framesThisSecond;
	//static long long lastSecondTime;
	//private static long last100Ticks=lastRenderHighResTime;

	static long long totalTicks;
	static long long ticksThisSecond;
	static int framesSkipped;


public:
	static void updateTimers();
	void setEngineSpeed(double f);
	int engineTicksPassed();
	static int realWorldTicksPassed();

	virtual void update();
	virtual void render();
	virtual void cleanup();
	void updateChatConsole();

protected:

	static sp<ControlsManager> controlsManager;
	static sp<ControlsManager> chatControlsManager;
	static sp<ControlsManager> activeControlsManager;

	
	bool chatEnabled = true;
	bool chatFocused = false;
	bool textStarted = false;

	sp<ConsoleText> chatConsoleText = nullptr;
public:
	virtual sp <ControlsManager> getControlsManager();
	virtual sp <ControlsManager> getActiveControlsManager();

	//static void setClientGameEngine(std::sp<BGClientEngine> clientGameEngine);

	static void setControlsManager(sp<ControlsManager> controlsManager);


	virtual sp <BGClientEngine> getClientGameEngine();
	//static sp<BGClientEngine> clientGameEngine;

	virtual void updateControls();
	virtual void resetPressedButtons();
	virtual void setButtonStates();


	static sp <TCPServerConnection> getServerConnection();

	static long long getUserID_S();
	static string getUserName_S();
	static GameSave getGameSave_S();
	static void setGameSave_S(GameSave &g);

	int getWidth();

	int getHeight();

	virtual bool udpPeerMessageReceived(sp<UDPPeerConnection> c, string s);
	virtual bool serverMessageReceived(string cs);



	//static sp<BGClientEngine> clientGameEngine;
	//ArrayDeque<sp<Cameraman>> *cameramanStack = ms<ArrayDeque><sp<Cameraman>>();
	//std::sp<ArrayDeque<std::sp<Cameraman>>> cameramanStack = std::ms<ArrayDeque<std::sp<Cameraman>>>();

public:

	bool hitLayerEnabled = true;
	bool underLayerEnabled = true;
	bool overLayerEnabled = true;
	bool entityLayerEnabled = true;
	bool lightsLayerEnabled = true;
	bool debugLayerEnabled = false;

	//DebugText cameraSpeedText = DebugConsole.add("cameraSpeedText");
	sp<ConsoleText>  zoomText = nullptr;// Console::debug("zoomText");
	sp<ConsoleText>  mapCamText = nullptr;// = Console::debug("mapCamText");
	sp<ConsoleText>  mapScreenText = nullptr;// = Console::debug("mapScreenText");
	sp<ConsoleText>  mapSizeText = nullptr;// = Console::debug("mapSizeText");
	sp<ConsoleText>  resolutionText = nullptr;// = Console::debug("resolutionText");
	sp<ConsoleText>  textText = nullptr;// = Console::debug("textText");
	sp<ConsoleText>  textOptionText = nullptr;// = Console::debug("textOptionText");




	Engine();
	virtual ~Engine();
	virtual void init();


	virtual void updateDebugText();
	void* getGameObjectByTYPEIDName(const string& typeIDName);


	virtual sp<Cameraman> getCameraman();
	virtual sp<MapManager> getMapManager();
	virtual sp<SpriteManager> getSpriteManager();
	virtual sp<ActionManager> getActionManager();
	virtual sp<TextManager> getTextManager();
	virtual sp<AudioManager> getAudioManager();
	virtual sp<CaptionManager> getCaptionManager();
	virtual sp<EventManager> getEventManager();

	virtual sp<CinematicsManager> getCinematicsManager();
	virtual sp<Map> getCurrentMap();



public:


	float getWidthRelativeToZoom();
	float getHeightRelativeToZoom();






	//====================================================
	//SPRITE
	//====================================================
public:
	void sendSpriteDataRequestByName(string spriteAssetName);
	void sendSpriteDataRequestByID(int id);

private:
	void incomingSpriteData(string s);

	//====================================================
	//MAP
	//====================================================
public:
	void sendMapDataRequestByName(string mapName);
	void sendMapDataRequestByID(int id);

private:
	void incomingMapData(string s);

	//====================================================
public:
	void sendServerObjectRequest(std::sp<ServerObject> serverObject);

	//====================================================
	//DIALOGUE
	//====================================================
	void sendDialogueRequest(int id);

private:
	void incomingDialogue(string s);

	//====================================================
	//EVENT
	//====================================================

public:
	void sendEventRequest(int id);

private:
	void incomingEvent(string s);

	//====================================================
	//GAMESTRING
	//====================================================
public:
	void sendGameStringRequest(int id);

private:
	void incomingGameString(string s);

	//====================================================
	//FLAG
	//====================================================
public:
	void sendFlagRequest(int id);

private:
	void incomingFlag(string s);

	//====================================================
	//SKILL
	//====================================================
public:
	void sendSkillRequest(int id);

private:
	void incomingSkill(string s);
	//====================================================
	//MUSIC
	//====================================================
public:
	void sendMusicRequest(int id);

private:
	void incomingMusic(string s);

	//====================================================
	//SOUND
	//====================================================
public:
	void sendSoundRequest(int id);

private:
	void incomingSound(string s);
};

