#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger EnginePart::log = Logger("EnginePart");

//sp<BGClientEngine> EnginePart::clientGameEngine = nullptr;
//sp<ControlsManager> EnginePart::controlsManager = nullptr;

EnginePart::EnginePart()
{ //=========================================================================================================================
}

EnginePart::EnginePart(sp<Engine> g)
{ //=========================================================================================================================
	this->e = g;

	//if(g==null)log->error("e is null");
}

//
//void EnginePart::setControlsManager(sp<ControlsManager> controlsManager)
//{
//	EnginePart::controlsManager = controlsManager;
//}

void EnginePart::toggleActivated()
{
	isActivated = !isActivated;
	timeActivated = System::currentHighResTimer();

	//TODO: send flag update with this game object TYPEID

	//TODO: maybe instead of flag i should allow any kind of value: int, float, bool, string

	//so, GAMEVALUE
}

void EnginePart::setActivated(bool b)
{
	isActivated = b;
	timeActivated = System::currentHighResTimer();

	//TODO: send flag update with this game object TYPEID
}

bool EnginePart::getIsActivated()
{
	return isActivated;
}

bool EnginePart::getWasEverActivated()
{
	if (timeActivated == -1)
	{
		return false;
	}
	return true;
}

int EnginePart::getSecondsSinceActivated()
{
	if (timeActivated == -1)
	{
		return 0;
	}

	long long startTime = timeActivated;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)(ticksPassed / 1000);
}

bool EnginePart::getWasEverHere()
{
	if (lastTimeHere == -1)
	{
		return false;
	}
	return true;
}

void EnginePart::resetLastTimeHere()
{
	lastTimeHere = -1;
}

void EnginePart::setLastTimeHere()
{
	lastTimeHere = System::currentHighResTimer();

	//TODO: send flag update with this game object TYPEID
}

long long EnginePart::getLastTimeHere()
{
	return lastTimeHere;
}

int EnginePart::getSecondsSinceLastHere()
{
	if (lastTimeHere == -1)
	{
		return -1;
	}

	long long startTime = lastTimeHere;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)(ticksPassed / 1000);
}

int EnginePart::getMinutesSinceLastHere()
{
	if (lastTimeHere == -1)
	{
		return -1;
	}

	long long startTime = lastTimeHere;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

	return (int)((ticksPassed / 1000) / 60);
}

sp<Engine> EnginePart::getEngine()
{
	if(e==nullptr)return Main::gameEngine;
	return e;
}

sp<Cameraman> EnginePart::getCameraman()
{
	return getEngine()->cameraman;
}

sp<MapManager> EnginePart::getMapManager()
{
	return getEngine()->mapManager;
}

sp<SpriteManager> EnginePart::getSpriteManager()
{
	return getEngine()->spriteManager;
}

sp<ActionManager> EnginePart::getActionManager()
{
	return getEngine()->actionManager;
}

sp<TextManager> EnginePart::getTextManager()
{
	return getEngine()->textManager;
}

sp<AudioManager> EnginePart::getAudioManager()
{
	return getEngine()->audioManager;
}

sp<CaptionManager> EnginePart::getCaptionManager()
{
	return getEngine()->captionManager;
}

sp<EventManager> EnginePart::getEventManager()
{
	return getEngine()->eventManager;
}

sp<CinematicsManager> EnginePart::getCinematicsManager()
{
	return getEngine()->cinematicsManager;
}

sp<Map> EnginePart::getCurrentMap()
{
	sp<Map> m = getEngine()->mapManager->currentMap;
//	if (m == nullptr)
//	{
//		m = ms<Map>(e, ms<MapData>(-1, "none", 0, 0));
//	}
	return m;
}




//void EnginePart::setClientGameEngine(sp<BGClientEngine> gameEngine)
//{
//	EnginePart::clientGameEngine = gameEngine;
//}

sp<BGClientEngine> EnginePart::getClientGameEngine()
{
	return Main::gameEngine;
}

sp<ControlsManager> EnginePart::getControlsManager()
{
	return getEngine()->getControlsManager();
}


sp<Clock> EnginePart::getClock()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->clock;
}

sp<GUIManager> EnginePart::getGUIManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->guiManager;
}

sp<StuffMenu> EnginePart::getStuffMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->stuffMenu;
}

sp<GameStore> EnginePart::getGameStore()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->gameStore;
}

sp<PlayerEditMenu> EnginePart::getPlayerEditMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->playerEditMenu;
}

sp<Player> EnginePart::getPlayer()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->player;
}

ND* EnginePart::getND()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->nD;
}

sp<Wallet> EnginePart::getWallet()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->wallet;
}

sp<FriendManager> EnginePart::getFriendManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->friendManager;
}

sp<StatusBar> EnginePart::getStatusBar()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->statusBar;
}

sp<NotificationManager> EnginePart::getNotificationManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getStatusBar()->notificationManager;
}

sp<TCPServerConnection> EnginePart::getServerConnection()
{
	return OKNet::tcpServerConnection;
}

GameSave EnginePart::getGameSave()
{
	return getServerConnection()->getGameSave_S();
}

//=========================================================================================================================
bool EnginePart::udpPeerMessageReceived(sp<UDPPeerConnection> c, string e)
{//=========================================================================================================================

	string s = e;

	if (s.find(":") == string::npos)return false;

	string command = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1);

	return false;
}