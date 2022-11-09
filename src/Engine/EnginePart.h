//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class UDPPeerConnection;
class TCPServerConnection;
class Logger;



class ControlsManager;
class Cameraman;
class Engine;
class MapManager;
class SpriteManager;
class ActionManager;
class AudioManager;
class TextManager;
class EventManager;
class CinematicsManager;
class Map;
class BGClientEngine;
class Player;
class Wallet;
class GameSave;
class CaptionManager;
class Clock;
class BGClientTCP;
class GUIManager;
class StuffMenu;
class GameStore;
class PlayerEditMenu;
class ND;
class FriendManager;
class StatusBar;
class NotificationManager;

class EnginePart// : public std::enable_shared_from_this<EnginePart>
{
public:
	virtual ~EnginePart()
	{
	}

	static Logger log;

protected:
	sp<Engine> e = nullptr;

private:
	//static sp<BGClientEngine> clientGameEngine;
	//sp<ControlsManager> controlsManager = nullptr;

	
	bool isActivated = false;
	long long lastTimeHere = -1;
	long long timeActivated = -1;

public:
	EnginePart();
	EnginePart(sp<Engine> e);

	//void setControlsManager(sp<ControlsManager> controlsManager);

	virtual void toggleActivated();
	virtual void setActivated(bool b);
	virtual bool getIsActivated();
	bool getWasEverActivated();
	int getSecondsSinceActivated();
	bool getWasEverHere();
	void resetLastTimeHere();
	void setLastTimeHere();
	long long getLastTimeHere();
	int getSecondsSinceLastHere();
	int getMinutesSinceLastHere();

	sp<Engine> getEngine();
	sp<Cameraman> getCameraman();
	sp<MapManager> getMapManager();
	sp<SpriteManager> getSpriteManager();
	sp<ActionManager> getActionManager();
	sp<TextManager> getTextManager();
	sp<AudioManager> getAudioManager();
	virtual sp<CaptionManager> getCaptionManager();
	sp<EventManager> getEventManager();
	sp<CinematicsManager> getCinematicsManager();

	virtual sp<Map> getCurrentMap();

	sp<ControlsManager> getControlsManager();

	//static void setClientGameEngine(sp<BGClientEngine> gameEngine);

	static sp<BGClientEngine> getClientGameEngine();

	static sp<TCPServerConnection> getServerConnection();

	static sp<Clock> getClock();
	static sp<GUIManager> getGUIManager();
	static sp<StuffMenu> getStuffMenu();
	static sp<GameStore> getGameStore();
	static sp<PlayerEditMenu> getPlayerEditMenu();
	static sp<Player> getPlayer();
	static ND* getND();
	static sp<Wallet> getWallet();
	static sp<FriendManager> getFriendManager();
	static sp<StatusBar> getStatusBar();
	static sp<NotificationManager> getNotificationManager();
	//The following method was originally marked 'synchronized':
	static GameSave getGameSave();

	virtual bool udpPeerMessageReceived(sp<UDPPeerConnection> c, string e);
	//
	//	public String getIDString()
	//	{
	//
	//		return null;
	//	}
	//
	//
	//
	//	public String getShortTypeName()
	//	{
	//
	//		return null;
	//	}
};

