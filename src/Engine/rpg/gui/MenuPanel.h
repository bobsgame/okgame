//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class MenuPanel : public EnginePart
{
public:

	static Logger log;

	//shared_ptr<DialogLayout> mainPanelLayout = nullptr;
	//shared_ptr<ScrollPane> scrollPane = nullptr;
	//shared_ptr<DialogLayout> insideScrollPaneLayout = nullptr;

protected:
	
	bool isActivated = false;
	
	bool isScrollingDown = false;
	
	bool isScrolledUp = false;

public:
	int ticksSinceTurnedOn = 0;
	int ticksSinceTurnedOff = 0;

	float screenY = 0;

	float fadeInTime = 600.0f;
	float fadeOutTime = 1000.0f;

private:
	
	bool enabled = true;

public:

	MenuPanel();

	MenuPanel(shared_ptr<Engine>e);

	virtual void update();

	void setEnabled(bool b);

	bool getEnabled();

	virtual bool getIsActivated() override;

	bool getIsScrollingDown();

	bool getIsScrolledUp();

	virtual void setActivated(bool b) override;

	virtual void toggleActivated() override;

	virtual void onScrolledUp();

	virtual void scrollUp();

	virtual void scrollDown();

protected:
	virtual void layout();

public:
	virtual void renderBefore();

	virtual void render();

//
//	static shared_ptr<BGClientEngine> getClientGameEngine();
//
//
//
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
//
//	static shared_ptr<TCPServerConnection> getServerConnection();
//	static shared_ptr<GameSave> getGameSave();
};

