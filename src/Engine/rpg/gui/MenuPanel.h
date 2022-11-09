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

	//sp<DialogLayout> mainPanelLayout = nullptr;
	//sp<ScrollPane> scrollPane = nullptr;
	//sp<DialogLayout> insideScrollPaneLayout = nullptr;

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

	MenuPanel(sp<Engine>e);

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
//	static sp<BGClientEngine> getClientGameEngine();
//
//
//
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
//
//	static sp<TCPServerConnection> getServerConnection();
//	static sp<GameSave> getGameSave();
};

