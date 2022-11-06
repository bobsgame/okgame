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


	shared_ptr<StuffMenu> stuffMenu = nullptr;
	//GUI* stuffMenuGUI = nullptr;

	shared_ptr<GameStore> gameStore = nullptr;
	//GUI* gameStoreGUI = nullptr;

	shared_ptr<PlayerEditMenu> playerEditMenu = nullptr;
	//GUI* playerEditGUI = nullptr;

	ArrayList<shared_ptr<GameChallengeNotificationPanel>> gameChallenges;// = make_shared<ArrayList><shared_ptr<GameChallengeNotificationPanel>>();
	//ArrayList<GUI> gameChallengesGUIs;

	shared_ptr<KeyboardMenuPanel> keyboardScreen = nullptr;
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


	GUIManager(shared_ptr<BGClientEngine> g);


	void init();


	void update();


	void render();


	//The following method was originally marked 'synchronized':
	shared_ptr<GameChallengeNotificationPanel> makeGameChallengeNotification(shared_ptr<FriendCharacter> friend_in, const string& gameName);


	void removeGameNotification(shared_ptr<GameChallengeNotificationPanel> g);


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

