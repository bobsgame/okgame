//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;

#include "src/Engine/Engine.h"

#include "src/Utility/Console.h"
#include "src/Utility/ConsoleText.h"

class Wallet;
class Clock;
class Player;
class GameSave;
class GUIManager;
class StatusBar;
class FriendManager;
class ND;
class Sprite;
class StadiumScreen;

class BGClientEngine : public Engine
{
	//DebugText playerSpeedText = DebugConsole.add("playerSpeedText");
private:
	typedef Engine super;

public:
	
	static Logger log;

	static bool debugMode;

	sp<ConsoleText> playerMapText = nullptr;// = Console::debug("playerMapText");
	sp<ConsoleText> playerScreenText = nullptr;// = Console::debug("playerScreenText");

	sp<GUIManager> guiManager = nullptr;
	sp<StatusBar> statusBar = nullptr;
	sp<Wallet> wallet = nullptr;

	sp<Clock> clock = nullptr;

	sp<Player> normalPlayer = nullptr;
	sp<Player> player = nullptr;

	sp<FriendManager> friendManager = nullptr;

	ND* nD = nullptr;
	sp<StadiumScreen> stadiumScreen = nullptr;

	bool controlsEnabled = true;
	bool playerExistsInMap = true;

	BGClientEngine();
	virtual ~BGClientEngine() override;
	virtual void init() override;

	virtual void update() override;

	virtual void cleanup() override;

	virtual void render() override;

	bool areAnyMenusOpen();

	void handleGameEngineOptionKeys();

	virtual void updateDebugText() override;

	void loadPreCachedObjectData();

	void initializeGameFromSave_S();
	void setPlayerAppearanceFromGameSave_S();

	sp<OKColor> getNameColor(int accountType);

	string getAccountRankString(int accountRank);
	sp<OKColor> getAccountRankColor(int accountRank);

	void setPlayerToTempPlayerWithSprite(sp<Sprite> s);
	void setPlayerToNormalPlayer();

	sp<Clock> getClock();
	sp<GUIManager> getGUIManager();
	sp<StuffMenu> getStuffMenu();
	sp<GameStore> getGameStore();
	sp<PlayerEditMenu> getPlayerEditMenu();
	sp<Player> getPlayer();
	ND* getND();
	sp<Wallet> getWallet();
	sp<FriendManager> getFriendManager();
	sp<StatusBar> getStatusBar();
	sp<NotificationManager> getNotificationManager();
	//The following method was originally marked 'synchronized':

	//====================================================
	//NETWORKING
	//====================================================

	bool gameSaveCompleted_nonThreaded = false;

	//sp<GameSave> getGameSave_S();

	private:
		bool isGameInitializedFromSave_nonThreaded = false;
		bool _isGameInitializedFromSave = false; //synchronized
public:
	//The following method was originally marked 'synchronized':
	void setGameInitializedFromSave_S(bool b);
	//The following method was originally marked 'synchronized':
	bool getGameInitializedFromSave_S();

	virtual bool serverMessageReceived(string e) override;

private:
	long long lastSentProjectLoadEventRequestTime = 0;
	bool isProjectLoadEventInitialized_nonThreaded = false;
	int _projectLoadEventID = -1;

public:
	//The following method was originally marked 'synchronized':
	void setProjectLoadEventID_S(int id);

	//The following method was originally marked 'synchronized':
	int getProjectLoadEventID_S();

	bool getFinishedLoadEvent();
	sp<Event> projectLoadEvent = nullptr;

	bool finishedProjectLoadEvent = false;

	public:
		void sendProjectLoadEventRequest();

private:
	void incomingLoadEventResponse(string s);

};

