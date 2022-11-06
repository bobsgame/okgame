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

	//shared_ptr<DialogLayout> notificationPanel = nullptr;

	//shared_ptr<Button> yesButton = nullptr;
	//shared_ptr<Button> noButton = nullptr;

	shared_ptr<FriendCharacter> friendCharacter = nullptr;
	string gameName = "";

	long long notificationCreatedTime = 0;

	//shared_ptr<Label> timeLeftLabel = nullptr;

	GameChallengeNotificationPanel(shared_ptr<FriendCharacter> friend_in, const string& gameName);

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

