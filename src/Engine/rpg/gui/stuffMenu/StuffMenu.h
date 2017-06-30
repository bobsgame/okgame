//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class FriendsPanel;
class DebugInfoPanel;
class StatusPanel;
class MessagesPanel;
class ItemsPanel;
class LogsPanel;
class ControlsPanel;
class SettingsPanel;


class StuffMenu : public MenuPanel
{
public:

	static Logger log;


	FriendsPanel* friendsPanel = nullptr;
	DebugInfoPanel* debugInfoPanel = nullptr;
	StatusPanel* statusPanel = nullptr;
	MessagesPanel* messagesPanel = nullptr;
	ItemsPanel* itemsPanel = nullptr;
	LogsPanel* logsPanel = nullptr;
	ControlsPanel* controlsPanel = nullptr;
	SettingsPanel* settingsPanel = nullptr;


	//ArrayList<ToggleButton*> stuffMenuTabs;


	float subPanelScreenWidthPercent = 0.80f;
	float subPanelScreenHeightPercent = 0.86f;


	StuffMenu();


	virtual void setActivated(bool b) override;


	void setAllInvisible();


	void openSubMenu();// SubPanel* subPanel);


	void init();


	virtual void update() override;


	virtual void render() override;


protected:
	virtual void layout() override;
};

