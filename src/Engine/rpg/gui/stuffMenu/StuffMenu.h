//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
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


	shared_ptr<FriendsPanel> friendsPanel = nullptr;
	shared_ptr<DebugInfoPanel> debugInfoPanel = nullptr;
	shared_ptr<StatusPanel> statusPanel = nullptr;
	shared_ptr<MessagesPanel> messagesPanel = nullptr;
	shared_ptr<ItemsPanel> itemsPanel = nullptr;
	shared_ptr<LogsPanel> logsPanel = nullptr;
	shared_ptr<ControlsPanel> controlsPanel = nullptr;
	shared_ptr<SettingsPanel> settingsPanel = nullptr;


	//ArrayList<shared_ptr<ToggleButton>> stuffMenuTabs;


	float subPanelScreenWidthPercent = 0.80f;
	float subPanelScreenHeightPercent = 0.86f;


	StuffMenu();


	virtual void setActivated(bool b) override;


	void setAllInvisible();


	void openSubMenu();// shared_ptr<SubPanel> subPanel);


	void init();


	virtual void update() override;


	virtual void render() override;


protected:
	virtual void layout() override;
};

