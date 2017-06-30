//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "../../state/KeyboardScreen.h"


class GUIManager : public EnginePart
{
public:

	static Logger log;


	StuffMenu* stuffMenu = nullptr;
	//GUI* stuffMenuGUI = nullptr;

	GameStore* gameStore = nullptr;
	//GUI* gameStoreGUI = nullptr;

	PlayerEditMenu* playerEditMenu = nullptr;
	//GUI* playerEditGUI = nullptr;

	ArrayList<GameChallengeNotificationPanel*>* gameChallenges = new ArrayList<GameChallengeNotificationPanel*>();
	//ArrayList<GUI*> gameChallengesGUIs;

	KeyboardScreen* keyboardScreen = nullptr;
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


	GUIManager(BGClientEngine* g);


	void init();


	void update();


	void render();


	//The following method was originally marked 'synchronized':
	GameChallengeNotificationPanel* makeGameChallengeNotification(FriendCharacter* friend_in, const string& gameName);


	void removeGameNotification(GameChallengeNotificationPanel* g);


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

