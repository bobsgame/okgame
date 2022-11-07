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

class EnginePart : public std::enable_shared_from_this<EnginePart>
{
public:
	virtual ~EnginePart()
	{
	}

	static Logger log;

protected:
	shared_ptr<Engine> e = nullptr;

private:
	//static shared_ptr<BGClientEngine> clientGameEngine;
	//shared_ptr<ControlsManager> controlsManager = nullptr;

	
	bool isActivated = false;
	long long lastTimeHere = -1;
	long long timeActivated = -1;

public:
	EnginePart();
	EnginePart(shared_ptr<Engine> e);

	//void setControlsManager(shared_ptr<ControlsManager> controlsManager);

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

	shared_ptr<Engine> getEngine();
	shared_ptr<Cameraman> getCameraman();
	shared_ptr<MapManager> getMapManager();
	shared_ptr<SpriteManager> getSpriteManager();
	shared_ptr<ActionManager> getActionManager();
	shared_ptr<TextManager> getTextManager();
	shared_ptr<AudioManager> getAudioManager();
	virtual shared_ptr<CaptionManager> getCaptionManager();
	shared_ptr<EventManager> getEventManager();
	shared_ptr<CinematicsManager> getCinematicsManager();

	virtual shared_ptr<Map> getCurrentMap();

	shared_ptr<ControlsManager> getControlsManager();

	//static void setClientGameEngine(shared_ptr<BGClientEngine> gameEngine);

	static shared_ptr<BGClientEngine> getClientGameEngine();

	static shared_ptr<TCPServerConnection> getServerConnection();

	static shared_ptr<Clock> getClock();
	static shared_ptr<GUIManager> getGUIManager();
	static shared_ptr<StuffMenu> getStuffMenu();
	static shared_ptr<GameStore> getGameStore();
	static shared_ptr<PlayerEditMenu> getPlayerEditMenu();
	static shared_ptr<Player> getPlayer();
	static ND* getND();
	static shared_ptr<Wallet> getWallet();
	static shared_ptr<FriendManager> getFriendManager();
	static shared_ptr<StatusBar> getStatusBar();
	static shared_ptr<NotificationManager> getNotificationManager();
	//The following method was originally marked 'synchronized':
	static GameSave getGameSave();

	virtual bool udpPeerMessageReceived(shared_ptr<UDPPeerConnection> c, string e);
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

