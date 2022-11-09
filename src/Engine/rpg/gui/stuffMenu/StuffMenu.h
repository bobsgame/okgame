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


	sp<FriendsPanel> friendsPanel = nullptr;
	sp<DebugInfoPanel> debugInfoPanel = nullptr;
	sp<StatusPanel> statusPanel = nullptr;
	sp<MessagesPanel> messagesPanel = nullptr;
	sp<ItemsPanel> itemsPanel = nullptr;
	sp<LogsPanel> logsPanel = nullptr;
	sp<ControlsPanel> controlsPanel = nullptr;
	sp<SettingsPanel> settingsPanel = nullptr;


	//ArrayList<sp<ToggleButton>> stuffMenuTabs;


	float subPanelScreenWidthPercent = 0.80f;
	float subPanelScreenHeightPercent = 0.86f;


	StuffMenu();


	virtual void setActivated(bool b) override;


	void setAllInvisible();


	void openSubMenu();// sp<SubPanel> subPanel);


	void init();


	virtual void update() override;


	virtual void render() override;


protected:
	virtual void layout() override;
};

