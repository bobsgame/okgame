//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



#include "MenuPanel.h"

class GameChallengeNotificationPanel : public MenuPanel
{
public:
	static Logger log;

	//sp<DialogLayout> notificationPanel = nullptr;

	//sp<Button> yesButton = nullptr;
	//sp<Button> noButton = nullptr;

	sp<FriendCharacter> friendCharacter = nullptr;
	string gameName = "";

	long long notificationCreatedTime = 0;

	//sp<Label> timeLeftLabel = nullptr;

	GameChallengeNotificationPanel(sp<FriendCharacter> friend_in, const string& gameName);

	virtual void update() override;

	virtual void onScrolledUp() override;

	virtual void scrollUp() override;

	virtual void scrollDown() override;

protected:
	virtual void layout() override;

public:
	void setButtonsVisible(bool b);

	void doNo();

	void doYes();

	virtual void renderBefore() override;

	virtual void render() override;
};

