#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger EnginePart::log = Logger("EnginePart");

//shared_ptr<BGClientEngine> EnginePart::clientGameEngine = nullptr;
//shared_ptr<ControlsManager> EnginePart::controlsManager = nullptr;

EnginePart::EnginePart()
{ //=========================================================================================================================
}

EnginePart::EnginePart(shared_ptr<Engine> g)
{ //=========================================================================================================================
	this->e = g;

	//if(g==null)log->error("e is null");
}

//
//void EnginePart::setControlsManager(shared_ptr<ControlsManager> controlsManager)
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

shared_ptr<Engine> EnginePart::getEngine()
{
	if(e==nullptr)return Main::gameEngine;
	return e;
}

shared_ptr<Cameraman> EnginePart::getCameraman()
{
	return getEngine()->cameraman;
}

shared_ptr<MapManager> EnginePart::getMapManager()
{
	return getEngine()->mapManager;
}

shared_ptr<SpriteManager> EnginePart::getSpriteManager()
{
	return getEngine()->spriteManager;
}

shared_ptr<ActionManager> EnginePart::getActionManager()
{
	return getEngine()->actionManager;
}

shared_ptr<TextManager> EnginePart::getTextManager()
{
	return getEngine()->textManager;
}

shared_ptr<AudioManager> EnginePart::getAudioManager()
{
	return getEngine()->audioManager;
}

shared_ptr<CaptionManager> EnginePart::getCaptionManager()
{
	return getEngine()->captionManager;
}

shared_ptr<EventManager> EnginePart::getEventManager()
{
	return getEngine()->eventManager;
}

shared_ptr<CinematicsManager> EnginePart::getCinematicsManager()
{
	return getEngine()->cinematicsManager;
}

shared_ptr<Map> EnginePart::getCurrentMap()
{
	shared_ptr<Map> m = getEngine()->mapManager->currentMap;
//	if (m == nullptr)
//	{
//		m = make_shared<Map>(e, make_shared<MapData>(-1, "none", 0, 0));
//	}
	return m;
}




//void EnginePart::setClientGameEngine(shared_ptr<BGClientEngine> gameEngine)
//{
//	EnginePart::clientGameEngine = gameEngine;
//}

shared_ptr<BGClientEngine> EnginePart::getClientGameEngine()
{
	return Main::gameEngine;
}

shared_ptr<ControlsManager> EnginePart::getControlsManager()
{
	return getEngine()->getControlsManager();
}


shared_ptr<Clock> EnginePart::getClock()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->clock;
}

shared_ptr<GUIManager> EnginePart::getGUIManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->guiManager;
}

shared_ptr<StuffMenu> EnginePart::getStuffMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->stuffMenu;
}

shared_ptr<GameStore> EnginePart::getGameStore()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->gameStore;
}

shared_ptr<PlayerEditMenu> EnginePart::getPlayerEditMenu()
{
	if (getGUIManager() == nullptr)return nullptr;
	return getGUIManager()->playerEditMenu;
}

shared_ptr<Player> EnginePart::getPlayer()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->player;
}

ND* EnginePart::getND()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->nD;
}

shared_ptr<Wallet> EnginePart::getWallet()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->wallet;
}

shared_ptr<FriendManager> EnginePart::getFriendManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->friendManager;
}

shared_ptr<StatusBar> EnginePart::getStatusBar()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getClientGameEngine()->statusBar;
}

shared_ptr<NotificationManager> EnginePart::getNotificationManager()
{
	if (getClientGameEngine() == nullptr)return nullptr;
	return getStatusBar()->notificationManager;
}

shared_ptr<TCPServerConnection> EnginePart::getServerConnection()
{
	return OKNet::tcpServerConnection;
}

GameSave EnginePart::getGameSave()
{
	return getServerConnection()->getGameSave_S();
}

//=========================================================================================================================
bool EnginePart::udpPeerMessageReceived(shared_ptr<UDPPeerConnection> c, string e)
{//=========================================================================================================================

	string s = e;

	if (s.find(":") == string::npos)return false;

	string command = s.substr(s.find(":") + 1);
	s = s.substr(s.find(":") + 1);

	return false;
}