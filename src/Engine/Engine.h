//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"

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

class Engine// : public State
{
//private:
	//typedef State super;
public:
	

	static Logger log;

	AudioManager* audioManager = nullptr;
	Cameraman* cameraman = nullptr;
	SpriteManager* spriteManager = nullptr;
	ActionManager* actionManager = nullptr;
	MapManager* mapManager = nullptr;
	CinematicsManager* cinematicsManager = nullptr;
	CaptionManager* captionManager = nullptr;
	TextManager* textManager = nullptr;
	EventManager* eventManager = nullptr;


	static ArrayList<UDPPeerConnection*> onlineFriends;

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
	ControlsManager* controlsManager = nullptr;
	ControlsManager* chatControlsManager = nullptr;
	ControlsManager* activeControlsManager = nullptr;
	bool chatFocused = false;
	bool textStarted = false;

	ConsoleText* chatConsoleText = nullptr;
public:
	ControlsManager* getControlsManager();
	ControlsManager* getActiveControlsManager();

	//static void setClientGameEngine(BGClientEngine* gameEngine);
	static BGClientEngine* getClientGameEngine();

	virtual void updateControls();
	virtual void resetPressedButtons();
	virtual void setButtonStates();


	static TCPServerConnection* getServerConnection();

	static long long getUserID_S();
	static string getUserName_S();
	static GameSave getGameSave_S();
	static void setGameSave_S(GameSave &g);

	int getWidth();

	int getHeight();

	virtual bool udpPeerMessageReceived(UDPPeerConnection *c, string s);
	virtual bool serverMessageReceived(string cs);



	//static BGClientEngine* clientGameEngine;
	//ArrayDeque<Cameraman*> *cameramanStack = new ArrayDeque<Cameraman*>();

public:

	bool hitLayerEnabled = true;
	bool underLayerEnabled = true;
	bool overLayerEnabled = true;
	bool entityLayerEnabled = true;
	bool lightsLayerEnabled = true;
	bool debugLayerEnabled = false;

	//DebugText cameraSpeedText = DebugConsole.add("cameraSpeedText");
	ConsoleText* zoomText = nullptr;// Console::debug("zoomText");

	ConsoleText* mapCamText = nullptr;// = Console::debug("mapCamText");
	ConsoleText* mapScreenText = nullptr;// = Console::debug("mapScreenText");

	ConsoleText* mapSizeText = nullptr;// = Console::debug("mapSizeText");
	ConsoleText* resolutionText = nullptr;// = Console::debug("resolutionText");

	ConsoleText* textText = nullptr;// = Console::debug("textText");
	ConsoleText* textOptionText = nullptr;// = Console::debug("textOptionText");

	Engine();
	virtual ~Engine();
	virtual void init();


	virtual void updateDebugText();
	void* getGameObjectByTYPEIDName(const string& typeIDName);

	Cameraman* getCameraman();
	MapManager* getMapManager();
	SpriteManager* getSpriteManager();
	ActionManager* getActionManager();
	TextManager* getTextManager();
	AudioManager* getAudioManager();
	CaptionManager* getCaptionManager();
	EventManager* getEventManager();

	CinematicsManager* getCinematicsManager();
	Map* getCurrentMap();

public:
	//static void setClientGameEngine(BGClientEngine* clientGameEngine);
	//void setControlsManager(ControlsManager* controlsManager);
	//static BGClientEngine* getClientGameEngine();

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
	void sendServerObjectRequest(ServerObject* serverObject);

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

