//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once

#include "bobtypes.h"

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

//	static shared_ptr<BGClientEngine> getClientEngine();
//	static shared_ptr<EventManager> getEventManager();
//	static shared_ptr<Clock> getClock();
//	static shared_ptr<GUIManager> getGUIManager();
//	static shared_ptr<StuffMenu> getStuffMenu();
//	static shared_ptr<GameStore> getGameStore();
//	static shared_ptr<PlayerEditMenu> getPlayerEditMenu();
//	static shared_ptr<Player> getPlayer();
//	static ND* getND();
//	static shared_ptr<Wallet> getWallet();
//	static shared_ptr<FriendManager> getFriendManager();
//	static shared_ptr<StatusBar> getStatusBar();
//	static shared_ptr<NotificationManager> getNotificationManager();
//	static shared_ptr<GameSave> getGameSave();
//	static shared_ptr<TCPServerConnection> getServerConnection();

};

