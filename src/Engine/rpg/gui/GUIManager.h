//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;





#include "../../state/KeyboardMenuPanel.h"


class GUIManager : public EnginePart
{
public:

	static Logger log;


	sp<StuffMenu> stuffMenu = nullptr;
	//GUI* stuffMenuGUI = nullptr;

	sp<GameStore> gameStore = nullptr;
	//GUI* gameStoreGUI = nullptr;

	sp<PlayerEditMenu> playerEditMenu = nullptr;
	//GUI* playerEditGUI = nullptr;

	sp<vector<sp<GameChallengeNotificationPanel>>>gameChallenges;// = ms<vector><sp<GameChallengeNotificationPanel>>();
	//sp<vector<GUI>>gameChallengesGUIs;

	sp<KeyboardMenuPanel> keyboardScreen = nullptr;
	//GUI* keyboardScreenGUI = nullptr;


	//this panel (with plate)
	static string lightThemeString;
	static string darkThemeString;


	//child panel (with plate)
	static string subMenuPanelDialogLayoutTheme;

	//scrollpane here

	//panel inside scrollpane
	static string emptyDialogLayoutTheme;

	static string buttonTheme;
	static string checkboxTheme;
	static string scrollPaneTheme;

	bool lightTheme = false;


	GUIManager(sp<BGClientEngine> g);


	void init();


	void update();


	void render();


	//The following method was originally marked 'synchronized':
	sp<GameChallengeNotificationPanel> makeGameChallengeNotification(sp<FriendCharacter> friend_in, const string& gameName);


	void removeGameNotification(sp<GameChallengeNotificationPanel> g);


	void cleanup();


	void setDarkTheme();


	void setLightTheme();


	void openND();


	void closeND();


	void openGameStore();


	void openSettingsMenu();


	void openFriendsMenu();


	void openStatusMenu();


	void openLogMenu();


	void openItemsMenu();


	void openStuffMenu();


	void enableAllMenusAndND();


	void disableAllMenusAndND();


	void closeAllMenusAndND();
};

