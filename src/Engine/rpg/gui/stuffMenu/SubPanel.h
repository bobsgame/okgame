//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once

#include "oktypes.h"

class Logger;

class SubPanel : public EnginePart
{
public:

	static Logger log;

	SubPanel();

	virtual void init();
	virtual void setVisible(bool b);
	virtual void layout();
	virtual void update();
	virtual void render();

//	static sp<BGClientEngine> getClientEngine();
//	static sp<EventManager> getEventManager();
//	static sp<Clock> getClock();
//	static sp<GUIManager> getGUIManager();
//	static sp<StuffMenu> getStuffMenu();
//	static sp<GameStore> getGameStore();
//	static sp<PlayerEditMenu> getPlayerEditMenu();
//	static sp<Player> getPlayer();
//	static ND* getND();
//	static sp<Wallet> getWallet();
//	static sp<FriendManager> getFriendManager();
//	static sp<StatusBar> getStatusBar();
//	static sp<NotificationManager> getNotificationManager();
//	static sp<GameSave> getGameSave();
//	static sp<TCPServerConnection> getServerConnection();

};

