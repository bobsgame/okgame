#include "stdafx.h"

#include "src/Utility/audio/AudioManager.h"

#include "stdlib.h"

#include "Room.h"


//=========================================================================================================================
void OKGame::setupMenus()
{//=========================================================================================================================

	super::setupMenus();

	numTitleMenuTextureFrames = 11;// 22;//;//91; //139;//with quotes

}

bool OKGame::updateMenus()
{ //=========================================================================================================================

	//titleMenuShowing = false;
	//customGameEditorMenuShowing = true;
	//gameSequenceEditorMenuShowing = true;
	//globalSettingsMenuShowing = true;
	//gameSetupMenuShowing = true;

	bool updatedMenu = false;

	if (super::updateMenus() == true)updatedMenu = true;


	if (gettingGamesFromServerMenuShowing)
	{
		gettingGamesFromServerMenuUpdate();
		return true;
	}

	if (startScreenMenuShowing)
	{
		startScreenMenuUpdate();
		return true;
	}

	if (controllerMenuShowing)
	{
		controllerMenuUpdate();
		return true;
	}

	if (localMultiplayerPlayerJoinMenuShowing)
	{
		localMultiplayerPlayerJoinMenuUpdate();
		return true;
	}

	if (loginMenuShowing)
	{
		loginMenuUpdate();
		return true;
	}

	if (createAccountMenuShowing)
	{
		createAccountMenuUpdate();
		return true;
	}

	if (networkMultiplayerLobbyMenuShowing)
	{
		networkMultiplayerLobbyMenuUpdate();
		return true;
	}

	if (networkMultiplayerPlayerJoinMenuShowing)
	{
		networkMultiplayerPlayerJoinMenuUpdate();
		return true;
	}

	if (customGameEditorMenuShowing)
	{
		customGameEditorMenuUpdate();
		return true;
	}

	if (gameSequenceEditorMenuShowing)
	{
		gameSequenceEditorMenuUpdate();
		return true;
	}

	if (gameTestMenuShowing)
	{
		gameTestMenuUpdate();
		return true;
	}

	if (globalSettingsMenuShowing)
	{
		globalSettingsMenuUpdate();
		return true;
	}

	if (gameSetupMenuShowing)
	{
		gameSetupMenuUpdate();
		return true;
	}

	if (statsMenuShowing)
	{
		statsMenuUpdate();
		return true;
	}

//	if (selectGameSequenceOrSingleGameTypeMenuShowing)
//	{
//		selectGameSequenceOrSingleGameTypeMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (selectGameSequenceMenuShowing)
//	{
//		selectGameSequenceMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (selectSingleGameTypeMenuShowing)
//	{
//		selectSingleGameTypeMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (difficultyMenuShowing)
//	{
//		difficultyMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (gameSequenceOptionsMenuShowing)
//	{
//		gameSequenceOptionsMenuUpdate();
//		updatedMenu = true;
//	}
//
//	if (gameObjectiveMenuShowing)
//	{
//		gameObjectiveMenuUpdate();
//		updatedMenu = true;
//	}

	if (multiplayerOptionsMenuShowing)
	{
		multiplayerOptionsMenuUpdate();
		return true;
	}

//	if (gameSetupMenuShowing)
//	{
//		gameSetupMenuUpdate();
//		updatedMenu = true;
//	}

	if(updatedMenu == false)unloadTitleMenuTextures();
	return updatedMenu;
}

bool OKGame::renderMenus()
{//=========================================================================================================================

	bool renderedMenu = false;

	if (super::renderMenus() == true)renderedMenu = true;


	if (gettingGamesFromServerMenuShowing)
	{
		gettingGamesFromServerMenuRender();
		return true;
	}

	if (startScreenMenuShowing)
	{
		startScreenMenuRender();
		return true;
	}

	if (controllerMenuShowing)
	{
		controllerMenuRender();
		return true;
	}

	if (localMultiplayerPlayerJoinMenuShowing)
	{
		localMultiplayerPlayerJoinMenuRender();
		return true;
	}

	if (loginMenuShowing)
	{
		loginMenuRender();
		return true;
	}

	if (createAccountMenuShowing)
	{
		createAccountMenuRender();
		return true;
	}

	if (networkMultiplayerLobbyMenuShowing)
	{
		networkMultiplayerLobbyMenuRender();
		return true;
	}

	if (networkMultiplayerPlayerJoinMenuShowing)
	{
		networkMultiplayerPlayerJoinMenuRender();
		return true;
	}

	if (customGameEditorMenuShowing)
	{
		customGameEditorMenuRender();
		return true;
	}

	if (gameSequenceEditorMenuShowing)
	{
		gameSequenceEditorMenuRender();
		return true;
	}

	if (gameTestMenuShowing)
	{
		gameTestMenuRender();
		return true;
	}

	if (globalSettingsMenuShowing)
	{
		globalSettingsMenuRender();
		return true;
	}

	if (gameSetupMenuShowing)
	{
		gameSetupMenuRender();
		return true;
	}

	if (statsMenuShowing)
	{
		statsMenuRender();
		return true;
	}

//	if (selectGameSequenceOrSingleGameTypeMenuShowing)
//	{
//		selectGameSequenceOrSingleGameTypeMenuRender();
//		renderedMenu = true;
//	}
//
//	if (selectGameSequenceMenuShowing)
//	{
//		selectGameSequenceMenuRender();
//		renderedMenu = true;
//	}
//
//	if (selectSingleGameTypeMenuShowing)
//	{
//		selectSingleGameTypeMenuRender();
//		renderedMenu = true;
//	}
//
//	if (difficultyMenuShowing)
//	{
//		difficultyMenuRender();
//		renderedMenu = true;
//	}
//
//	if (gameSequenceOptionsMenuShowing)
//	{
//		gameSequenceOptionsMenuRender();
//		renderedMenu = true;
//	}
//
//	if (gameObjectiveMenuShowing)
//	{
//		gameObjectiveMenuRender();
//		renderedMenu = true;
//	}

	if (multiplayerOptionsMenuShowing)
	{
		multiplayerOptionsMenuRender();
		return true;
	}
//	if (gameSetupMenuShowing)
//	{
//		gameSetupMenuRender();
//		renderedMenu = true;
//	}
	return renderedMenu;

}

//=========================================================================================================================
void OKGame::updateTitleScreenLogo()
{//=========================================================================================================================

	titleMenuFrameTicks += super::engineTicksPassed();
	if (titleMenuFrameTicks > 20)
	{
		titleMenuFrameTicks = 0;
		if (currentTitleMenuTextureFrameIncrementDecrementToggle)
		{
			currentTitleMenuTextureFrame++;
			if (currentTitleMenuTextureFrame >= numTitleMenuTextureFrames)
			{
				currentTitleMenuTextureFrame = numTitleMenuTextureFrames-1;
				currentTitleMenuTextureFrameIncrementDecrementToggle = !currentTitleMenuTextureFrameIncrementDecrementToggle;
			}
		}
		else
		{
			currentTitleMenuTextureFrame--;
			if (currentTitleMenuTextureFrame < 0)
			{
				currentTitleMenuTextureFrame = 0;
				currentTitleMenuTextureFrameIncrementDecrementToggle = !currentTitleMenuTextureFrameIncrementDecrementToggle;
			}
		}

		updateTitleMenuLogoTexture();
	}
}

//=========================================================================================================================
void OKGame::updateTitleMenuLogoTexture()
{//=========================================================================================================================

//	if(titleScreenTexture!= nullptr)
//	{
//		titleScreenTexture->release();
//		titleScreenTexture= nullptr;
//	}

//	string numString = ""+to_string(currentTitleScreenTextureFrame);
//	int len = numString.length();
//	for(int n=0;n<2-len;n++)numString = "0"+numString;//pad to 2 zeros

	//titleScreenTexture = GLUtils::getTextureFromPNG("data/guiBackground/logo/"+numString+".png");

	//if(titleMenuTextures==nullptr)titleMenuTextures = ms<vector><sp<OKTexture>>();// [numTileScreenTextureFrames];
	if(titleMenuTextures->size()==0)
	{
		for (int i = 0; i<numTitleMenuTextureFrames; i++)
		{
			string numString = "" + to_string(i);
			int len = (int)numString.length();
			for (int n = 0; n<2 - len; n++)numString = "0" + numString;//pad to 2 zeros

			titleMenuTextures->push_back(GLUtils::getTextureFromPNGExePath("data/guiBackground/logo/" + numString + ".png"));
		}
	}
}

//=========================================================================================================================
void OKGame::titleMenuUpdate()
{//=========================================================================================================================

	if (titleMenu == nullptr)
	{
		titleMenu = ms<OKMenu>(this, "");
		titleMenu->spacing = 1.2f;

		titleMenu->addInfo("Connecting to server...","Login");
		titleMenu->add("Play Offline");
		titleMenu->add("Exit Game");

		titleMenu->cursorPosition = titleMenuCursorPosition;
	}

	bool leaveMenu = false;

	if (getServerConnection()->getConnectedToServer_S())
	{
		if(FileUtils::readSessionTokenFromCache()!="")
		{
			titleMenu->getMenuItemByID("Login")->setText("Logging in...");
			titleMenu->getMenuItemByID("Login")->info = true;
		}
		else
		{
			if (titleMenu->getMenuItemByID("Login")->info)
			{
				titleMenu->getMenuItemByID("Login")->setText("Login Or Create Account");
				titleMenu->getMenuItemByID("Login")->info = false;
				titleMenu->getMenuItemByID("Login")->setColor(OKMenu::menuColor);
				titleMenu->setSelectedID("Login");
			}
		}

		if (getServerConnection()->getAuthorizedOnServer_S())
		{
			leaveMenu = true;
			startScreenMenuShowing = true;
		}
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		titleMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		titleMenu->down();
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (confirm || clicked)
	{

		if (titleMenu->isSelectedID("Login", clicked, mx, my))
		{
			if (titleMenu->getMenuItemByID("Login")->info == false)
			{
				loginMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (titleMenu->isSelectedID("Play Offline", clicked, mx, my))
		{
			startScreenMenuShowing = true;
			leaveMenu = true;
		}

		if (titleMenu->isSelectedID("Exit Game", clicked, mx, my))
		{
			Main::quit = true;
		}
	}

	if (leaveMenu)
	{
		titleMenuShowing = false;

		if (titleMenu != nullptr)
		{
			titleMenuCursorPosition = titleMenu->cursorPosition;
			//delete titleMenu;
			titleMenu = nullptr;
		}
	}
}

void OKGame::titleMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture>t = nullptr;

	if (
		//titleMenuTextures != nullptr && 
		titleMenuTextures->size()>0)t = titleMenuTextures->at(currentTitleMenuTextureFrame);

	if (titleMenuTexture != nullptr)t = titleMenuTexture;

	if (titleMenu == nullptr)return;

	if (t != nullptr)
	{
		titleMenu->setGraphic(t, getWidth() / 3*2, getHeight() / 10);
		titleMenu->render();
	}

}

void OKGame::startScreenMenuUpdate()
{ //=========================================================================================================================

	updateTitleScreenLogo();

	if (startScreenMenu == nullptr)
	{
		startScreenMenu = ms<OKMenu>(this, "");
		startScreenMenu->spacing = 1.2f;
		startScreenMenu->setFontSize(32);

		//pressEnterCaption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, y-60, -1, "Press Enter to begin", oswald_24, infoColor, clearColor, RenderOrder::OVER_GUI);
		//pressEnterCaption->flashing = true;
		//pressEnterCaption->flashingTicksPerFlash = 3000;

		startScreenMenu->add("Single Player");
		startScreenMenu->add("Local Multiplayer");
		startScreenMenu->add("Online Multiplayer","", OKMenu::disabledMenuColor);
		startScreenMenu->add("Stats And Leaderboards","Stats", OKMenu::disabledMenuColor);
		startScreenMenu->add("Vote On New Games", "", OKMenu::disabledMenuColor);
		startScreenMenu->add("Custom Game Editor");
		startScreenMenu->add("Game Sequence Creator");
		startScreenMenu->add("Global Settings");
		startScreenMenu->add("Controller Test");
		//startScreenMenu->add("Report Bug");
		//startScreenMenu->add("Support On Patreon", "Donate");
		startScreenMenu->add("Exit Game");

		startScreenMenu->cursorPosition = startScreenMenuCursorPosition;

		localMultiplayer = false;
		networkMultiplayer = false;
	}

	if (infoMenu == nullptr)
	{
		infoMenu = ms<OKMenu>(this, "");
		infoMenu->center = false;
		infoMenu->setFontSize(10);
		infoMenu->outline = false;
		infoMenu->addInfo("Build " + Main::version + " " + __TIMESTAMP__);// +" - Support this game: ", "Build Number");
		infoMenu->addInfo("This game is actively developed by one person for free and will have bugs. I rely on your feedback!");
		infoMenu->addInfo("Please report problems, crashes, and suggestions to bugs@bobsgame.com or ", "Open Forum");
//		infoMenu->addInfo("There are no built in games, they are downloaded. If no games show in the menu the server might be overloaded, wait a bit or restart a few times.");
//		infoMenu->addInfo("Currently working on: Better leaderboards, Android/iOS ports.");
	}


//	if (patreonMenu == nullptr)
//	{
//		patreonMenu = ms<OKMenu>(this, "");
//		patreonMenu->center = false;
//		patreonMenu->font = 10;
//		patreonMenu->outline = false;
//		patreonMenu->addInfo("https://patreon.com/bobsgame", "Patreon", OKColor::lightBlue);
//	}


	if (forumMenu == nullptr)
	{
		forumMenu = ms<OKMenu>(this, "");
		forumMenu->center = false;
		forumMenu->setFontSize(10);
		forumMenu->outline = false;
		forumMenu->addInfo("https://bobsgame.com/forum", "Open Forum",OKColor::lightBlue);
	}

	if(getServerConnection()->getConnectedToServer_S())
	{
		startScreenMenu->getMenuItemByID("Online Multiplayer")->setColor(OKMenu::menuColor);
		startScreenMenu->getMenuItemByID("Online Multiplayer")->info = false;

		startScreenMenu->getMenuItemByID("Stats")->setColor(OKMenu::menuColor);
		startScreenMenu->getMenuItemByID("Stats")->info = false;

		startScreenMenu->getMenuItemByID("Vote On New Games")->setColor(OKMenu::menuColor);
		startScreenMenu->getMenuItemByID("Vote On New Games")->info = false;

	}
	else
	{
		startScreenMenu->getMenuItemByID("Online Multiplayer")->info = true;
		startScreenMenu->getMenuItemByID("Vote On New Games")->info = true;
	}


	if (activityStream->size()>0)
	{
							
		if (activityMenu == nullptr)
		{
			activityMenu = ms<OKMenu>(this, "", "Activity Stream");
			activityMenu->spacing = 1.2f;
			activityMenu->setFontSize(14);
			activityMenu->center = false;

			for (int i = 0; i < activityStream->size() && i < 20; i++)
			{
				activityMenu->addInfo(activityStream->at(i));
			}
		}
	}

		
	




	if (getControlsManager()->miniGame_UP_Pressed())
	{
		startScreenMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		startScreenMenu->down();
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		bool leaveMenu = false;

		if (startScreenMenu->isSelectedID("Single Player", clicked, mx, my))
		{
			localMultiplayer = false;
			networkMultiplayer = false;
			gameSetupMenuShowing = true;
			leaveMenu = true;
		}
		if (startScreenMenu->isSelectedID("Local Multiplayer", clicked, mx, my))
		{
			localMultiplayer = true;
			networkMultiplayer = false;
			multiplayerOptionsMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Online Multiplayer", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				localMultiplayer = false;
				networkMultiplayer = true;
				loginMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Stats", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				statsMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Vote On New Games", clicked, mx, my))
		{
			if (getServerConnection()->getConnectedToServer_S())
			{
				gameTestMenuShowing = true;
				leaveMenu = true;
			}
		}

		if (startScreenMenu->isSelectedID("Custom Game Editor", clicked, mx, my))
		{
			customGameEditorMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Game Sequence Creator", clicked, mx, my))
		{
			gameSequenceEditorMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Global Settings", clicked, mx, my))
		{
			globalSettingsMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Controller Test", clicked, mx, my))
		{
			controllerMenuShowing = true;
			leaveMenu = true;
		}

		if (startScreenMenu->isSelectedID("Exit Game", clicked, mx, my))
		{
			Main::quit = true;
		}

		if (confirm == false && clicked == true)
		{
//			if (patreonMenu!=nullptr && patreonMenu->isSelectedID("Patreon", clicked, mx, my))
//			{
//				Main::openURL("https://www.patreon.com/bobsgame");
//			}
//
			if (forumMenu!=nullptr && forumMenu->isSelectedID("Open Forum", clicked, mx, my))
			{
				Main::openURL("https://www.bobsgame.com/forum");
			}
		}

		if (leaveMenu)
		{
			startScreenMenuShowing = false;

			if(startScreenMenu!=nullptr)
			{
				startScreenMenuCursorPosition = startScreenMenu->cursorPosition;
				//delete startScreenMenu;
				startScreenMenu = nullptr;
			}
			if (infoMenu != nullptr)
			{
				//delete infoMenu;
				infoMenu = nullptr;
			}
			if (patreonMenu != nullptr)
			{
				//delete patreonMenu;
				patreonMenu = nullptr;
			}
			if (forumMenu != nullptr)
			{
				//delete forumMenu;
				forumMenu = nullptr;
			}
			if (activityMenu != nullptr)
			{
				//delete activityMenu;
				activityMenu = nullptr;				
			}
		}
	}
}

void OKGame::startScreenMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255,255,255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture>t = nullptr;

	if (
		//titleMenuTextures != nullptr && 
		titleMenuTextures->size()>0)t = titleMenuTextures->at(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;

	if (startScreenMenu == nullptr)return;

	if (t != nullptr)
	{
		startScreenMenu->setGraphic(t, getWidth()/3*2, getHeight() / 10, getHeight()/3);

		if (activityMenu != nullptr)
		{
			int bottomOfGraphic = 0;
			int rightX = 0;
			startScreenMenu->render(0, 0 ,getHeight(),true,&bottomOfGraphic,nullptr, false,nullptr,&rightX);
			activityMenu->render(getHeight()-(activityMenu->lastHeight+30), rightX + 100 ,getHeight(),false);
		}
		else
		{
			startScreenMenu->render();
		}
	}

	infoMenu->render(0, 6);// getHeight() - (infoMenu->getAmountOfMenuItems() * 20), 10);

//	if(patreonMenu!=nullptr)
//	{
//		sp<Caption>c = infoMenu->getMenuItemByID("Build Number")->caption;
//		int x = c->screenX + c->getWidth();
//		int y = c->screenY;
//		patreonMenu->render(y, x);
//	}
//
	if(forumMenu!=nullptr)
	{
		sp<Caption>c = infoMenu->getMenuItemByID("Open Forum")->caption;
		int x = x = c->screenX + c->getWidth();
		int y = y = c->screenY;
		forumMenu->render(y, x);
	}
}


void OKGame::gettingGamesFromServerMenuUpdate()
{ //=========================================================================================================================

	updateTitleScreenLogo();

	if (gettingGamesFromServerMenu == nullptr)
	{
		gettingGamesFromServerMenu = ms<OKMenu>(this, "");
		gettingGamesFromServerMenu->spacing = 1.2f;
		gettingGamesFromServerMenu->setFontSize(24);
		gettingGamesFromServerMenu->addInfo("Downloading games from server...","Downloading");
	}

	long long currentTime = System::currentHighResTimer();
	long long startTime = gettingGamesFromServerDotsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 300)
	{
		gettingGamesFromServerDotsTime = currentTime;
		gettingGamesFromServerCount++;
		gettingGamesFromServerMenu->getMenuItemByID("Downloading")->setText("Downloading games from server" + cycleDots(gettingGamesFromServerCount));
	}


}

void OKGame::gettingGamesFromServerMenuRender()
{ //=========================================================================================================================

	GLUtils::drawFilledRect(255,255,255, 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture>t = nullptr;

	if (
		//titleMenuTextures != nullptr && 
		titleMenuTextures->size()>0)t = titleMenuTextures->at(currentTitleMenuTextureFrame);
	if (titleMenuTexture != nullptr)t = titleMenuTexture;

	if (gettingGamesFromServerMenu == nullptr)return;

	if (t != nullptr)
	{
		gettingGamesFromServerMenu->setGraphic(t, getWidth()/3*2, getHeight() / 10);
		gettingGamesFromServerMenu->render();
	}

}

void OKGame::decreaseVolume()
{//=========================================================================================================================
	if (Main::globalSettings->musicVolume > 0)Main::globalSettings->musicVolume -= 1;
	if (Main::globalSettings->musicVolume < 0)Main::globalSettings->musicVolume = 0;
	music->setVolume(((float)Main::globalSettings->musicVolume / 100.0f));
}

void OKGame::increaseVolume()
{//=========================================================================================================================
	if (Main::globalSettings->musicVolume < 100)Main::globalSettings->musicVolume += 1;
	if (Main::globalSettings->musicVolume > 100)Main::globalSettings->musicVolume = 100;
	music->setVolume(((float)Main::globalSettings->musicVolume / 100.0f));
}

//=========================================================================================================================
void OKGame::pauseMenuUpdate()
{//=========================================================================================================================

	if(pauseMenu == nullptr)
	{
		pauseMenu = ms<OKMenu>(this,"Paused");

		pauseMenu->add("Back To Game", "Back To Game");
		settingsMenuInit(pauseMenu, false);
		playerControllerSettingsMenuInit(pauseMenu, getPlayer1());
		pauseMenu->add("Quit Game And Return To Title Screen","Quit Game And Return To Title Screen");

		pauseMenu->cursorPosition = pauseMenuCursorPosition;
	}


	if(getControlsManager()->miniGame_UP_Pressed())
	{
		pauseMenu->up();
	}

	if(getControlsManager()->miniGame_DOWN_Pressed())
	{
		pauseMenu->down();
	}



	if (getControlsManager()->MINIGAME_LEFT_HELD)
	{
		settingsMenuLeft(pauseMenu);
	}
	if (getControlsManager()->MINIGAME_RIGHT_HELD)
	{
		settingsMenuRight(pauseMenu);
	}
	if (getControlsManager()->miniGame_LEFT_Pressed())
	{
		settingsMenuToggle(pauseMenu);
		playerControllerSettingsMenuToggle(pauseMenu,getPlayer1());
	}
	if (getControlsManager()->miniGame_RIGHT_Pressed())
	{
		settingsMenuToggle(pauseMenu);
		playerControllerSettingsMenuToggle(pauseMenu, getPlayer1());
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		settingsMenuToggle(pauseMenu);
		playerControllerSettingsMenuToggle(pauseMenu, getPlayer1());

		if (pauseMenu->isSelectedID("Defaults", clicked, mx, my))
		{
			settingsMenuSetDefaults(pauseMenu, false);
		}

		if(pauseMenu->isSelectedID("Back To Game", clicked, mx, my))
		{
			leaveMenu = true;
		}

		if (pauseMenu->isSelectedID("Quit Game And Return To Title Screen", clicked, mx, my))
		{
			leaveMenu = true;
			startScreenMenuShowing = true;
			initPlayer();
		}

	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if(leaveMenu)
	{
		pauseMenuShowing = false;

		if (pauseMenu != nullptr)
		{
			pauseMenuCursorPosition = pauseMenu->cursorPosition;
			//delete pauseMenu;
			pauseMenu = nullptr;
		}
	}
}

//=========================================================================================================================
void OKGame::pauseMenuRender()
{//=========================================================================================================================

//	if (pauseMenu != nullptr)
//	{
//		if(
//			pauseMenu->isSelectedID("Brightness") == false &&
//			pauseMenu->isSelectedID("Contrast") == false &&
//			pauseMenu->isSelectedID("Saturation") == false
//		)
//		{
//			GLUtils::drawFilledRect(255, 255, 255, 0, (float)getWidth(), 0, (float)getHeight(), 0.7f);
//		}
//	}

	sp<OKTexture> t = keyboardTexture;

	if (pauseMenu == nullptr)return;

	if (t != nullptr)
	{
		pauseMenu->setGraphic(t, getWidth() / 8 * 5, getHeight() / 8);
	}

	pauseMenu->render(0, getWidth()/4, getHeight(), true, nullptr, nullptr, true);
}


//=========================================================================================================================
void OKGame::controllerMenuUpdate()
{//=========================================================================================================================

	if (controllerMenu == nullptr)
	{

		//Game controllers are automatically detected.
		//Test your buttons here, press Esc to stop.
		//If your controller was not detected, you can create a new mapping for it.
		//This will be saved to disk and loaded automatically.

		//Test controls
		//Testing... Press Esc to stop.
		//Create custom mapping

		controllerMenu = ms<OKMenu>(this, "Controller Test");
		controllerMenu->addInfo("Game controllers should be automatically detected.");
#ifdef _WINDOWS_
		controllerMenu->addInfo("If your controller does not work, try downloading x360ce.");
		controllerMenu->addInfo("You can also try the controller map tool in /data/ControllerMapTool");
#endif
		controllerMenu->addInfo("If it still does not work, please report to bugs@bobsgame.com");
		controllerMenu->addInfo(" ");
#ifdef _WINDOWS_
		controllerMenu->add("Use XInput (better controller support but 4 player max)", "XInput");
		controllerMenu->addInfo("");
#endif
		controllerMenu->add("Use Analog Sticks: ","Use Analog Sticks");
		controllerMenu->add("Test detected button mapping");
		controllerMenu->add("Return to Title Screen");
		controllerMenu->addInfo(" ", "Testing Caption");
		controllerMenu->addInfo(" ", "Button Press Caption");

		controllerMenu->cursorPosition = controllerMenuCursorPosition;
	}

#ifdef _WINDOWS_
	if(Main::globalSettings->useXInput)controllerMenu->getMenuItemByID("XInput")->setText("Use XInput (better controller support but 4 player max)");
	else controllerMenu->getMenuItemByID("XInput")->setText("Use DirectInput (worse controller support but no player limit)");
#endif

	if (Main::globalSettings->useAnalogSticks)controllerMenu->getMenuItemByID("Use Analog Sticks")->setText("Use Analog Sticks: Yes");
	else controllerMenu->getMenuItemByID("Use Analog Sticks")->setText("Use Analog Sticks: No");

	if(controllerMenuTestingButtons)
	{
		controllerMenu->getMenuItemByID("Testing Caption")->setColor(OKColor::lightGreen);
		controllerMenu->getMenuItemByID("Testing Caption")->setText("Testing buttons... Press Esc key or hold Start and Select on controller to stop");

		sp<OKMenu::MenuItem> m = controllerMenu->getMenuItemByID("Button Press Caption");

		for (int i = 0; i < getControlsManager()->gameControllers->size(); i++)
		{
			sp<GameController>g = getControlsManager()->gameControllers->at(i);

			m->setColor(OKColor::lightRed);

			if (g->up_Pressed())m->setText("Controller "+to_string(i)+" Up Pressed");
			if (g->down_Pressed())m->setText("Controller " + to_string(i) + " Down Pressed");
			if (g->left_Pressed())m->setText("Controller " + to_string(i) + " Left Pressed");
			if (g->right_Pressed())m->setText("Controller " + to_string(i) + " Right Pressed");
			if (g->b_Pressed())m->setText("Controller " + to_string(i) + " B Pressed");
			if (g->a_Pressed())m->setText("Controller " + to_string(i) + " A Pressed");
			if (g->x_Pressed())m->setText("Controller " + to_string(i) + " X Pressed");
			if (g->y_Pressed())m->setText("Controller " + to_string(i) + " Y Pressed");
			if (g->start_Pressed())m->setText("Controller " + to_string(i) + " Start Pressed");
			if (g->select_Pressed())m->setText("Controller " + to_string(i) + " Select Pressed");
			if (g->l_Pressed())m->setText("Controller " + to_string(i) + " L Pressed");
			if (g->r_Pressed())m->setText("Controller " + to_string(i) + " R Pressed");
		}

		if (getControlsManager()->key_ESC_Pressed() || (getControlsManager()->MINIGAME_START_HELD && getControlsManager()->MINIGAME_SELECT_HELD))
		{
			controllerMenuTestingButtons = false;
			controllerMenu->getMenuItemByID("Testing Caption")->setText(" ");
			controllerMenu->getMenuItemByID("Button Press Caption")->setText(" ");
		}

	}
	else
	{

		if (getControlsManager()->miniGame_UP_Pressed())
		{
			controllerMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			controllerMenu->down();
		}

		bool leaveMenu = false;

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
		int mx = getControlsManager()->getMouseX();
		int my = getControlsManager()->getMouseY();

		if (confirm || clicked)
		{

			if (controllerMenu->isSelectedID("Use Analog Sticks", clicked, mx, my))
			{
				Main::globalSettings->useAnalogSticks = !Main::globalSettings->useAnalogSticks;
			}

			if (controllerMenu->isSelectedID("XInput", clicked, mx, my))
			{
				Main::globalSettings->useXInput = !Main::globalSettings->useXInput;
				controllerMenu->getMenuItemByID("Button Press Caption")->setText("Must Restart To Apply Changes!");
			}

			if (controllerMenu->isSelectedID("Test detected button mapping", clicked, mx, my))
			{
				//testing
				controllerMenuTestingButtons = true;
			}
			if (controllerMenu->isSelectedID("Return to Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;
				leaveMenu = true;
			}
		}

		if(getControlsManager()->miniGame_CANCEL_Pressed())
		{
			startScreenMenuShowing = true;
			leaveMenu = true;
		}

		if(leaveMenu)
		{
			controllerMenuShowing = false;

			if (controllerMenu != nullptr)
			{
				controllerMenuCursorPosition = controllerMenu->cursorPosition;
				//delete controllerMenu;
				controllerMenu = nullptr;
			}
		}
	}
}

//=========================================================================================================================
void OKGame::controllerMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = controllerTexture;

	if (controllerMenu == nullptr)return;

	if (t != nullptr)
	{
		controllerMenu->setGraphic(t, getWidth() / 3 * 1, getHeight() / 8);
	}

	controllerMenu->render();
}



//=========================================================================================================================
void OKGame::playerSettingsMenuInit(sp<OKMenu> m, sp<PuzzlePlayer>p)
{//=========================================================================================================================

	m->add("Player Hue Shift: " + to_string((int)(p->hue * 100)) + "%", "Player Hue Shift");
}
//=========================================================================================================================
void OKGame::playerSettingsMenuLeft(sp<OKMenu> m, sp<PuzzlePlayer>p)
{//=========================================================================================================================

	if (m->isSelectedID("Player Hue Shift"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (p->hue > 0)p->hue -= 0.01f;
			if (p->hue < 0)p->hue = 0;
			m->getMenuItemByID("Player Hue Shift")->setText("Player Hue Shift: " + to_string((int)(p->hue * 100)) + "%");
		}
	}

}

//=========================================================================================================================
void OKGame::playerSettingsMenuRight(sp<OKMenu> m, sp<PuzzlePlayer>p)
{//=========================================================================================================================

	if (m->isSelectedID("Player Hue Shift"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (p->hue < 1)p->hue += 0.01f;
			if (p->hue > 1)p->hue = 1;
			m->getMenuItemByID("Player Hue Shift")->setText("Player Hue Shift: " + to_string((int)(p->hue * 100)) + "%");
		}
	}

}
//=========================================================================================================================
void OKGame::playerControllerSettingsMenuInit(sp<OKMenu> m, sp<PuzzlePlayer>p)
{//=========================================================================================================================

	m->add("Slam With Up: " + string(p->slamWithUp ? "On" : "Off"), "Slam With Up");
	m->add("Slam Lock: " + string(p->slamLock ? "On" : "Off"), "Slam Lock");
	m->add("Single Down Lock: " + string(p->singleDownLock ? "On" : "Off"), "Single Down Lock");
	m->add("Double Down Lock: " + string(p->doubleDownLock ? "On" : "Off"), "Double Down Lock");

}

//=========================================================================================================================
void OKGame::playerControllerSettingsMenuToggle(sp<OKMenu> m, sp<PuzzlePlayer>p)
{//=========================================================================================================================

	if (m->isSelectedID("Slam With Up"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			p->slamWithUp = !p->slamWithUp;
			m->getMenuItemByID("Slam With Up")->setText("Slam With Up: " + string(p->slamWithUp ? "On" : "Off"));
		}
	}

	if (m->isSelectedID("Slam Lock"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			p->slamLock = !p->slamLock;
			m->getMenuItemByID("Slam Lock")->setText("Slam Lock: " + string(p->slamLock ? "On" : "Off"));
		}
	}

	if (m->isSelectedID("Single Down Lock"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			p->singleDownLock = !p->singleDownLock;
			m->getMenuItemByID("Single Down Lock")->setText("Single Down Lock: " + string(p->singleDownLock ? "On" : "Off"));
		}
	}

	if (m->isSelectedID("Double Down Lock"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			p->doubleDownLock = !p->doubleDownLock;
			m->getMenuItemByID("Double Down Lock")->setText("Double Down Lock: " + string(p->doubleDownLock ? "On" : "Off"));
		}
	}



}

//=========================================================================================================================
void OKGame::playerPauseMiniMenuUpdate(sp<PuzzlePlayer>p)
{//=========================================================================================================================

	if (p != nullptr)
	{
		if (p->menu == nullptr)
		{
			p->menu = ms<OKMenu>(this, "");

			p->menu->add("Back To Game", "Back To Game", OKColor::white);
			settingsMenuInit(p->menu, false);

			playerSettingsMenuInit(p->menu, p);


			playerControllerSettingsMenuInit(p->menu, p);

			p->menu->addInfo(" ");
			p->menu->add("Forfeit", "Forfeit", OKColor::white);
		}

		if (p->upPressed())
		{
			p->menu->up();
		}

		if (p->downPressed())
		{
			p->menu->down();
		}

		if (p->LEFT_HELD)
		{
			settingsMenuLeft(p->menu);
			playerSettingsMenuLeft(p->menu,p);
		}
		if (p->RIGHT_HELD)
		{
			settingsMenuRight(p->menu);
			playerSettingsMenuRight(p->menu, p);
		}

		if (p->leftPressed())
		{
			settingsMenuToggle(p->menu);
			playerControllerSettingsMenuToggle(p->menu, p);
		}
		if (p->rightPressed())
		{
			settingsMenuToggle(p->menu);
			playerControllerSettingsMenuToggle(p->menu, p);
		}

		bool leaveMenu = false;
		//bool deletePlayer = false;

		if (p->confirmPressed())
		{

			settingsMenuToggle(p->menu);
			playerControllerSettingsMenuToggle(p->menu, p);


			if (p->menu->isSelectedID("Defaults"))
			{
				settingsMenuSetDefaults(p->menu, false);

				p->hue = 1.0f;
				p->menu->getMenuItemByID("Player Hue Shift")->setText("Player Hue Shift: " + to_string((int)(p->hue * 100)) + "%");


			}

			if (p->menu->isSelectedID("Back To Game"))
			{
				leaveMenu = true;
			}

			if (p->menu->isSelectedID("Forfeit"))
			{
				//if (isMultiplayer())
				{
					if (isNetworkGame())
					{
						tellAllPeersOneOfMyPlayersForfeitsGame(p);
					}

					p->gameLogic->died = true;
					//players->remove(p);
					//deletePlayer = true;

					bool allLocalPlayersDead = true;
					for (int i = 0; i < players->size(); i++)
					{
						sp<PuzzlePlayer>o = players->at(i);
						if (o->isNetworkPlayer() == false && o->gameLogic->died==false)allLocalPlayersDead = false;
					}

					if (allLocalPlayersDead)
					{
						if (isNetworkGame())
						{

							if (hosting)
							{
								//send to all friends disconnected
								tellAllPeersIAmNotHosting();
							}

							tellAllJoinedPeersIHaveLeftTheGame();

							OKNet::myStatus = OKNet::status_AVAILABLE;
							joinedPeers->clear();
							networkMultiplayerLobbyMenuShowing = true;
						}
						else
						{
							localMultiplayerPlayerJoinMenuShowing = true;
						}


						initPlayer();
					}
					leaveMenu = true;
				}
			}
		}

		if (p->cancelPressed())
		{
			leaveMenu = true;
		}

		if (leaveMenu)
		{
			if (p->menu != nullptr)
			{
				//delete p->menu;
				p->menu = nullptr;
			}
			p->gameLogic->pauseMiniMenuShowing = false;

//			if(deletePlayer)
//			{
//				delete p;
//				return false;
//			}
//			return true;
		}
	}
	//return true;
}

//=========================================================================================================================
void OKGame::playerPauseMiniMenuRender(sp<PuzzlePlayer>p, float x0, float x1, float y0, float y1)
{//=========================================================================================================================

	//GLUtils::drawFilledRect(255,255,255, x0,x1,y0,y1, 0.7f);

	if (p->menu != nullptr)
	{
		p->menu->render((int)(y0+((y1-y0)/2)), (int)(x0 + ((x1 - x0) / 2)),getHeight(),true,nullptr,nullptr,true);
	}
}

//=========================================================================================================================
void OKGame::loginMenuUpdate()
{//=========================================================================================================================

	//log in
	//save login
	//create account

	int y = (int)(getHeight() / 4 * 3);

	if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, y, -1, " ", 16, true, OKMenu::statusColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
	if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, y, -1, " ", 16, true, OKMenu::errorColor, OKMenu::clearColor, RenderOrder::OVER_GUI);

	if (loginMenu == nullptr)
	{
		loginMenu = ms<OKMenu>(this, "Login");
		//loginMenu->center = false;
		loginMenu->add("Username or Email: " + userNameOrEmailText,"Username or Email", OKMenu::statusColor);
		loginMenu->add("Password: " + passwordStarsText, "Password", OKMenu::statusColor);
		loginMenu->add("Stay logged in: Yes", "Stay logged in");
		loginMenu->add("Log in");
		loginMenu->addInfo(" ");
		loginMenu->add("Create new account");
		loginMenu->add("Forgot password");
		loginMenu->addInfo(" ");
		loginMenu->add("Return to title screen");

		loginMenu->cursorPosition = loginMenuCursorPosition;

		chatEnabled = false;
	}

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (mx != lastMX || my != lastMY)
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		lastMX = mx;
		lastMY = my;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		loginMenu->up();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed())
	{
		loginMenu->down();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

	if (confirm || clicked || (getControlsManager()->miniGame_LEFT_Pressed() || getControlsManager()->miniGame_RIGHT_Pressed()))
	{
		if (loginMenu->isSelectedID("Stay logged in", clicked, mx, my))
		{
			stayLoggedIn = !stayLoggedIn;

			if (stayLoggedIn)loginMenu->getMenuItemByID("Stay logged in")->setText("Stay logged in: Yes");
			else loginMenu->getMenuItemByID("Stay logged in")->setText("Stay logged in: No");

		}
	}

	if (loginMenu->isSelectedID("Username or Email"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = userNameOrEmailText; textStarted = true;}
		userNameOrEmailText = getControlsManager()->text;
		loginMenu->getMenuItemByID("Username or Email")->setText("Username or Email: " + userNameOrEmailText);
	}
	else
	if (loginMenu->isSelectedID("Password"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = passwordText; textStarted = true; }
		passwordText = getControlsManager()->text;
		passwordStarsText = "";
		for (int i = 0; i < (int)passwordText.length(); i++)passwordStarsText += "*";
		loginMenu->getMenuItemByID("Password")->setText("Password: " + passwordStarsText);
	}
	else
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	bool leaveMenu = false;

	if (confirm || clicked)
	{

		if (loginMenu->isSelectedID("Log in", clicked, mx, my) || loginMenu->isSelectedID("Password", clicked, mx, my))
		{

			getServerConnection()->doLogin(statusLabel, errorLabel, userNameOrEmailText, passwordText, stayLoggedIn);

			passwordText = "";
			
		}

		if (loginMenu->isSelectedID("Create new account", clicked, mx, my))
		{
			leaveMenu = true;
			createAccountMenuShowing = true;
		}

		if (loginMenu->isSelectedID("Forgot password", clicked, mx, my))
		{
			getServerConnection()->doForgotPassword(statusLabel,errorLabel,userNameOrEmailText);
		}

		if (loginMenu->isSelectedID("Return to title screen", clicked, mx, my))
		{
			//back to title screen
			leaveMenu = true;
			titleMenuShowing = true;
		}

	}

	if (getServerConnection()->getAuthorizedOnServer_S())
	{
		leaveMenu = true;
		if (networkMultiplayer)networkMultiplayerLobbyMenuShowing = true;
		else startScreenMenuShowing = true;
	}

	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		startScreenMenuShowing = true;
	}

	if (leaveMenu)
	{

		chatEnabled = true;

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		getControlsManager()->text = "";

		loginMenuShowing = false;

		if (loginMenu != nullptr)
		{
			loginMenuCursorPosition = loginMenu->cursorPosition;
			//delete loginMenu;
			loginMenu = nullptr;
		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}

}


//=========================================================================================================================
void OKGame::loginMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = onlineTexture;

	if (loginMenu == nullptr)return;

	if (t != nullptr)
	{
		loginMenu->setGraphic(t, getWidth() / 8 * 4, 100);
	}

	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		errorLabel->screenY = (float)(getHeight() / 4 * 3);
		statusLabel->screenY = (float)((getHeight() / 4 * 3) + 24);
	}

	loginMenu->render();
}

//=========================================================================================================================
void OKGame::createAccountMenuUpdate()
{//=========================================================================================================================

	if (createAccountMenu == nullptr)
	{
		int y = (int)(getHeight() / 4 * 3);

		if (statusLabel == nullptr)statusLabel = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, y, -1, " ", 16, true, OKMenu::statusColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
		if (errorLabel == nullptr)errorLabel = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, y, -1, " ", 16, true, OKMenu::errorColor, OKMenu::clearColor, RenderOrder::OVER_GUI);

		if (userNameOrEmailText.length()>0)
		{
			if (userNameOrEmailText.find("@") != string::npos)
				emailText = userNameOrEmailText;
			else
				userNameText = userNameOrEmailText;
		}

		createAccountMenu = ms<OKMenu>(this, "Create Account");
		//createAccountMenu->center = false;
		createAccountMenu->add("Username: " + userNameText, "Username");
		createAccountMenu->add("Email: " + emailText, "Email");
		createAccountMenu->add("Password: " + passwordStarsText, "Password");
		//createAccountMenu->add("Confirm password: " + confirmPasswordStarsText, "Confirm");
		createAccountMenu->add("Create account");
		createAccountMenu->addInfo(" ");
		createAccountMenu->add("Return to login screen");

		chatEnabled = false;
	}

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if(mx!=lastMX || my !=lastMY)
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		lastMX = mx;
		lastMY = my;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		createAccountMenu->up();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed())
	{
		createAccountMenu->down();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (createAccountMenu->isSelectedID("Username"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = userNameText; textStarted = true; }
		userNameText = getControlsManager()->text;
		createAccountMenu->getMenuItemByID("Username")->setText("Username: " + userNameText);
	}
	else
	if (createAccountMenu->isSelectedID("Email"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = emailText; textStarted = true; }
		emailText = getControlsManager()->text;
		createAccountMenu->getMenuItemByID("Email")->setText("Email: " + emailText);
	}
	else
	if (createAccountMenu->isSelectedID("Password"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = passwordText; textStarted = true; }
		passwordText = getControlsManager()->text;
		passwordStarsText = "";
		for (int i = 0; i < (int)passwordText.length(); i++)passwordStarsText += "*";
		createAccountMenu->getMenuItemByID("Password")->setText("Password: " + passwordStarsText);
	}
	else
	if (createAccountMenu->isSelectedID("Confirm"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = confirmPasswordText; textStarted = true; }
		confirmPasswordText = getControlsManager()->text;
		confirmPasswordStarsText = "";
		for (int i = 0; i < (int)confirmPasswordText.length(); i++)confirmPasswordStarsText += "*";
		createAccountMenu->getMenuItemByID("Confirm")->setText("Confirm password: " + confirmPasswordStarsText);
	}
	else
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	if (confirm || clicked)
	{
		if (createAccountMenu->isSelectedID("Create account", clicked, mx, my))
		{
			if(getServerConnection()->doCreateAccount(statusLabel,errorLabel,userNameText,emailText,passwordText,confirmPasswordText)==true)
			{
				
				Main::delay(2000);

				if(getServerConnection()->doLogin(statusLabel, errorLabel, userNameText, passwordText, true)==true)
				{
					startScreenMenuShowing = true;
					passwordText = "";
				}
				else
				{
					loginMenuShowing = true;
					passwordText = "";
				}
				leaveMenu = true;

			}
		}

		if (createAccountMenu->isSelectedID("Return to login screen", clicked, mx, my))
		{
			//back to title screen
			leaveMenu = true;
			loginMenuShowing = true;
		}
	}

	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		loginMenuShowing = true;
	}

	if (leaveMenu)
	{

		chatEnabled = true;

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		getControlsManager()->text = "";

		createAccountMenuShowing = false;

		if(createAccountMenu != nullptr)
		{
			//delete createAccountMenu;
			createAccountMenu = nullptr;
		}

		if (statusLabel != nullptr)
		{
			statusLabel->setToBeDeletedImmediately();
			statusLabel = nullptr;
		}

		if (errorLabel != nullptr)
		{
			errorLabel->setToBeDeletedImmediately();
			errorLabel = nullptr;
		}
	}

}


//=========================================================================================================================
void OKGame::createAccountMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = onlineTexture;

	if (createAccountMenu == nullptr)return;

	if (t != nullptr)
	{
		createAccountMenu->setGraphic(t, getWidth() / 8 * 4, 20);
	}

	if (statusLabel != nullptr && errorLabel != nullptr)
	{
		errorLabel->screenY = (float)(getHeight() / 4 * 3);
		statusLabel->screenY = (float)((getHeight() / 4 * 3) + 24);
	}

	createAccountMenu->render();

}

//=========================================================================================================================
void OKGame::settingsMenuInit(sp<OKMenu> m, bool isSettingsMenu)
{//=========================================================================================================================
	m->add("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%", "Music Volume");
	m->add("Brightness: " + to_string((int)(Main::globalSettings->brightness * 100)) + "%", "Brightness");
	m->add("Contrast: " + to_string((int)(Main::globalSettings->contrast * 100)) + "%", "Contrast");
	m->add("Saturation: " + to_string((int)(Main::globalSettings->saturation * 100)) + "%", "Saturation");

	m->add("Global Hue Shift: " + to_string((int)(Main::globalSettings->hue * 100)) + "%", "Global Hue Shift");
	if (isSettingsMenu)m->add("Level Up Screen Flash: " + to_string((int)(Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha * 100 * 2)) + "%", "Screen Flash");
	if (isSettingsMenu)m->add("Show Detailed Game Stats: " + string(Main::globalSettings->bobsGame_showDetailedGameInfoCaptions ? "On" : "Off"), "Game Stats");
	if (isSettingsMenu)m->add("Show High Score Bar In Single Player: " + string(Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer ? "On" : "Off"), "Score Bars");
	if (isSettingsMenu)m->add("Remove Profanity In Usernames: " + string(Main::globalSettings->censorBadWords ? "On" : "Off"), "Censor");
	if (isSettingsMenu)m->add("Hide Chat: " + string(Main::globalSettings->hideChat ? "On" : "Off"), "Hide Chat");
	if (isSettingsMenu)m->add("Hide Notifications: " + string(Main::globalSettings->hideNotifications ? "On" : "Off"), "Hide Notifications");

	m->add("Defaults");
}


//=========================================================================================================================
void OKGame::settingsMenuSetDefaults(sp<OKMenu> m, bool isSettingsMenu)
{//=========================================================================================================================

	GlobalSettings gs;
	Main::globalSettings->musicVolume = gs.musicVolume;
	Main::globalSettings->hue = gs.hue;
	Main::globalSettings->saturation = gs.saturation;
	Main::globalSettings->brightness = gs.brightness;
	Main::globalSettings->contrast = gs.contrast;
	Main::globalSettings->gamma = gs.gamma;
	if (isSettingsMenu)Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha = gs.bobsGame_screenFlashOnLevelUpAlpha;
	if (isSettingsMenu)Main::globalSettings->bobsGame_showDetailedGameInfoCaptions = gs.bobsGame_showDetailedGameInfoCaptions;
	if (isSettingsMenu)Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer = gs.bobsGame_showScoreBarsInSinglePlayer;
	if (isSettingsMenu)Main::globalSettings->censorBadWords = gs.censorBadWords;
	if (isSettingsMenu)Main::globalSettings->hideChat = gs.hideChat;
	if (isSettingsMenu)Main::globalSettings->hideNotifications = gs.hideNotifications;

	music->setVolume(((float)Main::globalSettings->musicVolume / 100.0f));
	m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
	m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(Main::globalSettings->brightness * 100)) + "%");
	m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(Main::globalSettings->contrast * 100)) + "%");
	m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(Main::globalSettings->saturation * 100)) + "%");
	m->getMenuItemByID("Global Hue Shift")->setText("Global Hue Shift: " + to_string((int)(Main::globalSettings->hue * 100)) + "%");
	if (isSettingsMenu)m->getMenuItemByID("Screen Flash")->setText("Level Up Screen Flash: " + to_string((int)(Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha * 100 * 2)) + "%");
	if (isSettingsMenu)m->getMenuItemByID("Game Stats")->setText("Show Detailed Game Stats: " + string(Main::globalSettings->bobsGame_showDetailedGameInfoCaptions ? "On" : "Off"));
	if (isSettingsMenu)m->getMenuItemByID("Score Bars")->setText("Show High Score Bar In Single Player: " + string(Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer ? "On" : "Off"));
	if (isSettingsMenu)m->getMenuItemByID("Censor")->setText("Remove Profanity In Usernames: " + string(Main::globalSettings->censorBadWords ? "On" : "Off"));
	if (isSettingsMenu)m->getMenuItemByID("Hide Chat")->setText("Hide Chat: " + string(Main::globalSettings->hideChat ? "On" : "Off"));
	if (isSettingsMenu)m->getMenuItemByID("Hide Notifications")->setText("Hide Notifications: " + string(Main::globalSettings->hideNotifications ? "On" : "Off"));

}


//=========================================================================================================================
void OKGame::settingsMenuToggle(sp<OKMenu> m)
{//=========================================================================================================================

	if (m->isSelectedID("Game Stats"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			Main::globalSettings->bobsGame_showDetailedGameInfoCaptions = !Main::globalSettings->bobsGame_showDetailedGameInfoCaptions;

			getPlayer1Game()->deleteInfoCaptions();

			m->getMenuItemByID("Game Stats")->setText("Show Detailed Game Stats: " + string(Main::globalSettings->bobsGame_showDetailedGameInfoCaptions ? "On" : "Off"));
		}
	}

	if (m->isSelectedID("Score Bars"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer = !Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer;

			getPlayer1Game()->deleteScoreBarCaptions();

			m->getMenuItemByID("Score Bars")->setText("Show Detailed Game Stats: " + string(Main::globalSettings->bobsGame_showScoreBarsInSinglePlayer ? "On" : "Off"));
		}
	}

	if (m->isSelectedID("Censor"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			Main::globalSettings->censorBadWords = !Main::globalSettings->censorBadWords;

			m->getMenuItemByID("Censor")->setText("Remove Profanity In Usernames: " + string(Main::globalSettings->censorBadWords ? "On" : "Off"));
		}
	}
	if (m->isSelectedID("Hide Chat"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			Main::globalSettings->hideChat = !Main::globalSettings->hideChat;

			Main::rightConsole->pruneChats(0);

			m->getMenuItemByID("Hide Chat")->setText("Hide Chat: " + string(Main::globalSettings->hideChat ? "On" : "Off"));
		}
	}
	if (m->isSelectedID("Hide Notifications"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			Main::globalSettings->hideNotifications = !Main::globalSettings->hideNotifications;

			m->getMenuItemByID("Hide Notifications")->setText("Hide Notifications: " + string(Main::globalSettings->hideNotifications ? "On" : "Off"));
		}
	}

}



//=========================================================================================================================
void OKGame::settingsMenuLeft(sp<OKMenu> m)
{//=========================================================================================================================
	if (m->isSelectedID("Music Volume"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			decreaseVolume();
			m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
		}
	}

	if (m->isSelectedID("Brightness"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->brightness > 0)Main::globalSettings->brightness -= 0.01f;
			if (Main::globalSettings->brightness < 0)Main::globalSettings->brightness = 0;
			m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(Main::globalSettings->brightness * 100)) + "%");
		}
	}

	if (m->isSelectedID("Contrast"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->contrast > 0)Main::globalSettings->contrast -= 0.01f;
			if (Main::globalSettings->contrast < 0)Main::globalSettings->contrast = 0;
			m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(Main::globalSettings->contrast * 100)) + "%");
		}
	}

	if (m->isSelectedID("Saturation"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->saturation > 0)Main::globalSettings->saturation -= 0.01f;
			if (Main::globalSettings->saturation < 0)Main::globalSettings->saturation = 0;
			m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(Main::globalSettings->saturation * 100)) + "%");
		}
	}

	if (m->isSelectedID("Global Hue Shift"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->hue > 0)Main::globalSettings->hue -= 0.01f;
			if (Main::globalSettings->hue < 0)Main::globalSettings->hue = 0;
			m->getMenuItemByID("Global Hue Shift")->setText("Global Hue Shift: " + to_string((int)(Main::globalSettings->hue * 100)) + "%");
		}
	}

	if (m->isSelectedID("Screen Flash"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha > 0)Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha -= 0.01f;
			if (Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha < 0)Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha = 0;
			m->getMenuItemByID("Screen Flash")->setText("Level Up Screen Flash: " + to_string((int)(Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha * 100 * 2)) + "%");
		}
	}


}

//=========================================================================================================================
void OKGame::settingsMenuRight(sp<OKMenu> m)
{//=========================================================================================================================
	if (m->isSelectedID("Music Volume"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			increaseVolume();
			m->getMenuItemByID("Music Volume")->setText("Music Volume: " + to_string((int)(music->getVolume() * 100)) + "%");
		}
	}
	if (m->isSelectedID("Brightness"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->brightness < 2)Main::globalSettings->brightness += 0.01f;
			if (Main::globalSettings->brightness > 2)Main::globalSettings->brightness = 2;
			m->getMenuItemByID("Brightness")->setText("Brightness: " + to_string((int)(Main::globalSettings->brightness * 100)) + "%");
		}
	}

	if (m->isSelectedID("Contrast"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->contrast < 2)Main::globalSettings->contrast += 0.01f;
			if (Main::globalSettings->contrast > 2)Main::globalSettings->contrast = 2;
			m->getMenuItemByID("Contrast")->setText("Contrast: " + to_string((int)(Main::globalSettings->contrast * 100)) + "%");
		}
	}

	if (m->isSelectedID("Saturation"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->saturation < 2)Main::globalSettings->saturation += 0.01f;
			if (Main::globalSettings->saturation > 2)Main::globalSettings->saturation = 2;
			m->getMenuItemByID("Saturation")->setText("Saturation: " + to_string((int)(Main::globalSettings->saturation * 100)) + "%");
		}
	}

	if (m->isSelectedID("Global Hue Shift"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->hue < 1)Main::globalSettings->hue += 0.01f;
			if (Main::globalSettings->hue > 1)Main::globalSettings->hue = 1;
			m->getMenuItemByID("Global Hue Shift")->setText("Global Hue Shift: " + to_string((int)(Main::globalSettings->hue * 100)) + "%");
		}
	}

	if (m->isSelectedID("Screen Flash"))
	{
		long long startTime = timeLastChangedSetting;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

		if (ticksPassed > 15)
		{
			timeLastChangedSetting = currentTime;
			if (Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha < 0.5f)Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha += 0.01f;
			if (Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha > 0.5f)Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha = 0.5f;
			m->getMenuItemByID("Screen Flash")->setText("Level Up Screen Flash: " + to_string((int)(Main::globalSettings->bobsGame_screenFlashOnLevelUpAlpha * 100 * 2)) + "%");
		}
	}


}

//=========================================================================================================================
void OKGame::globalSettingsMenuUpdate()
{//=========================================================================================================================

	if (globalSettingsMenu == nullptr)
	{
		globalSettingsMenu = ms<OKMenu>(this, "Global Settings");

		settingsMenuInit(globalSettingsMenu, true);
		globalSettingsMenu->add("Back To Title Screen", "Back To Title Screen");

		globalSettingsMenu->cursorPosition = globalSettingsMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		globalSettingsMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		globalSettingsMenu->down();
	}

	if (getControlsManager()->MINIGAME_LEFT_HELD)
	{
		settingsMenuLeft(globalSettingsMenu);
	}
	if (getControlsManager()->MINIGAME_RIGHT_HELD)
	{
		settingsMenuRight(globalSettingsMenu);
	}
	if (getControlsManager()->miniGame_LEFT_Pressed())
	{
		settingsMenuToggle(globalSettingsMenu);
	}
	if (getControlsManager()->miniGame_RIGHT_Pressed())
	{
		settingsMenuToggle(globalSettingsMenu);
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		settingsMenuToggle(globalSettingsMenu);

		if (globalSettingsMenu->isSelectedID("Defaults", clicked, mx, my))
		{
			settingsMenuSetDefaults(globalSettingsMenu, true);
		}
		if (globalSettingsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
		{
			leaveMenu = true;
		}

	}

	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		globalSettingsMenuShowing = false;
		startScreenMenuShowing = true;

		if (globalSettingsMenu != nullptr)
		{
			globalSettingsMenuCursorPosition = globalSettingsMenu->cursorPosition;
			//delete globalSettingsMenu;
			globalSettingsMenu = nullptr;
		}

	}
}

//=========================================================================================================================
void OKGame::globalSettingsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = gearsTexture;

	if (globalSettingsMenu == nullptr)return;

	if (t != nullptr)
	{
		globalSettingsMenu->setGraphic(t, getWidth() / 3, getHeight() / 8);
	}

	globalSettingsMenu->render();
}

//=========================================================================================================================
void OKGame::resetAllStatsMenuVars()
{//=========================================================================================================================
	statsMenu_totalTimePlayed = false;
	statsMenu_totalBlocksCleared = false;
	statsMenu_planeswalkerPoints = false;
	statsMenu_eloScore = false;
	statsMenu_timeLasted = false;
	statsMenu_blocksCleared = false;
}
//=========================================================================================================================
void OKGame::whichStatsMiniMenuUpdate()
{//=========================================================================================================================

	//populate leaderBoardMiniMenu
	if (whichStatsMiniMenu == nullptr)
	{
		whichStatsMiniMenu = ms<OKMenu>(this, "");
		whichStatsMiniMenu->center = false;
		whichStatsMiniMenu->setFontSize(12);

		whichStatsMiniMenu->add("Top Players By Total Time Played", "totalTimePlayed");
		whichStatsMiniMenu->add("Top Players By Total Blocks Cleared", "totalBlocksCleared");
		whichStatsMiniMenu->add("Top Players By Planeswalker Points", "planeswalkerPoints");
		whichStatsMiniMenu->add("Top Players By Elo Score", "eloScore");
		whichStatsMiniMenu->add("Top Games By Time Lasted", "timeLasted");
		whichStatsMiniMenu->add("Top Games By Blocks Cleared", "blocksCleared");
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		whichStatsMiniMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		whichStatsMiniMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (whichStatsMiniMenu->isSelectedID("totalTimePlayed"))
		{
			resetAllStatsMenuVars();
			statsMenu_totalTimePlayed = true;
		}
		if (whichStatsMiniMenu->isSelectedID("totalBlocksCleared"))
		{
			resetAllStatsMenuVars();
			statsMenu_totalBlocksCleared = true;
		}
		if (whichStatsMiniMenu->isSelectedID("planeswalkerPoints"))
		{
			resetAllStatsMenuVars();
			statsMenu_planeswalkerPoints = true;
		}
		if (whichStatsMiniMenu->isSelectedID("eloScore"))
		{
			resetAllStatsMenuVars();
			statsMenu_eloScore = true;
		}
		if (whichStatsMiniMenu->isSelectedID("timeLasted"))
		{
			resetAllStatsMenuVars();
			statsMenu_timeLasted = true;
		}
		if (whichStatsMiniMenu->isSelectedID("blocksCleared"))
		{
			resetAllStatsMenuVars();
			statsMenu_blocksCleared = true;
		}

		leaveMenu = true;
	}

	//	if (getControlsManager()->miniGame_CANCEL_Pressed())
	//	{
	//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
	//		leaveMenu = true;
	//	}

	if (leaveMenu)
	{
		whichStatsMiniMenuShowing = false;

		if (whichStatsMiniMenu != nullptr)
		{
			//delete whichStatsMiniMenu;
			whichStatsMiniMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}


//=========================================================================================================================
void OKGame::statsMenuUpdate()
{//=========================================================================================================================

	if (statsMenu == nullptr)
	{
		statsMenu = ms<OKMenu>(this, "Stats And Leaderboards");
		statsMenu->center = false;

		statsMenu->add("Leaderboard Type: ", "Stats Type");
		statsMenu->add("Game: All Games", "Game");
		statsMenu->add("Difficulty: All Difficulties", "Difficulty");
		statsMenu->add("Objective: Play To Credits", "Objective");
		statsMenu->addInfo(" ");
		statsMenu->add("Back To Title Screen", "Back To Title Screen");

		statsMenu_difficultyName = "OVERALL";
		statsMenu_gameSequenceOrTypeUUID = "OVERALL";
		statsMenu_gameSequenceOrTypeName = "OVERALL";

		statsMenu->cursorPosition = statsMenuCursorPosition;
	}

	if (statsMenu_difficultyName == "OVERALL") whichDifficultyToShow = 0;
	if (statsMenu_difficultyName == "Beginner")whichDifficultyToShow = 1;
	if (statsMenu_difficultyName == "Easy")	   whichDifficultyToShow = 2;
	if (statsMenu_difficultyName == "Normal")  whichDifficultyToShow = 3;
	if (statsMenu_difficultyName == "Hard")	   whichDifficultyToShow = 4;
	if (statsMenu_difficultyName == "Insane")  whichDifficultyToShow = 5;



	if(statsMenu_totalTimePlayed)		statsMenu->getMenuItemByID("Stats Type")->setText("Leaderboard Type: Top Players By Total Time Played");
	if(statsMenu_totalBlocksCleared)	statsMenu->getMenuItemByID("Stats Type")->setText("Leaderboard Type: Top Players By Total Blocks Cleared");
	if(statsMenu_planeswalkerPoints)	statsMenu->getMenuItemByID("Stats Type")->setText("Leaderboard Type: Top Players By Planeswalker Points");
	if(statsMenu_eloScore)				statsMenu->getMenuItemByID("Stats Type")->setText("Leaderboard Type: Top Players By Elo Score");
	if(statsMenu_timeLasted)			statsMenu->getMenuItemByID("Stats Type")->setText("High Scores Type: Top Games By Time Lasted");
	if(statsMenu_blocksCleared)			statsMenu->getMenuItemByID("Stats Type")->setText("High Scores Type: Top Games By Blocks Cleared");

	statsMenu->getMenuItemByID("Difficulty")->setText("Difficulty: " + statsMenu_difficultyName);

	statsMenu->getMenuItemByID("Game")->setText("Game: " + statsMenu_gameSequenceOrTypeName);

	statsMenu->getMenuItemByID("Objective")->setText("Objective: " + statsMenu_objectiveName);



	bool leaveMenu = false;

	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	bool clicked = false;
	bool confirm = false;

	if (whichStatsMiniMenuShowing)
	{
		whichStatsMiniMenuUpdate();
	}
	else
	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
		if (selectGameSequenceMenuShowing)
		{
			selectGameSequenceMenuUpdate();
		}
		else
			if (selectSingleGameTypeMenuShowing)
			{
				selectSingleGameTypeMenuUpdate();
			}
			else
				if (gameSequenceOptionsMenuShowing)
				{
					gameSequenceOptionsMenuUpdate();
				}
				else
						if (difficultyMenuShowing)
						{
							difficultyMenuUpdate();
						}
						else
						{
							if (getControlsManager()->miniGame_UP_Pressed())
							{
								statsMenu->up();
							}

							if (getControlsManager()->miniGame_DOWN_Pressed())
							{
								statsMenu->down();
							}

							confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
							clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();


							if (clicked == true && confirm == false)
							{

								if (leaderBoardMenu->isSelectedID("Stats Type", clicked, mx, my))
								{
									updateStatsMenu = true;

									if (statsMenu_totalTimePlayed)
									{
										statsMenu_totalTimePlayed = false;
										statsMenu_totalBlocksCleared = true;
									}
									else
										if (statsMenu_totalBlocksCleared)
										{
											statsMenu_totalBlocksCleared = false;
											statsMenu_planeswalkerPoints = true;
										}
										else
											if (statsMenu_planeswalkerPoints)
											{
												statsMenu_planeswalkerPoints = false;
												statsMenu_eloScore = true;
											}
											else
												if (statsMenu_eloScore)
												{
													statsMenu_eloScore = false;
													statsMenu_timeLasted = true;
												}
												else
													if (statsMenu_timeLasted)
													{
														statsMenu_timeLasted = false;
														statsMenu_blocksCleared = true;
													}
													else
														if (statsMenu_blocksCleared)
														{
															statsMenu_blocksCleared = false;
															statsMenu_totalTimePlayed = true;
														}
								}
								else
								if (yourStatsMenu->isSelectedID("Difficulty", clicked, mx, my) || leaderBoardMenu->isSelectedID("Difficulty", clicked, mx, my))
								{
									whichDifficultyToShow++;
									if (whichDifficultyToShow > 5)whichDifficultyToShow = 0;
									if (whichDifficultyToShow == 0)statsMenu_difficultyName = "OVERALL";
									if (whichDifficultyToShow == 1)statsMenu_difficultyName = "Beginner";
									if (whichDifficultyToShow == 2)statsMenu_difficultyName = "Easy";
									if (whichDifficultyToShow == 3)statsMenu_difficultyName = "Normal";
									if (whichDifficultyToShow == 4)statsMenu_difficultyName = "Hard";
									if (whichDifficultyToShow == 5)statsMenu_difficultyName = "Insane";
									updateStatsMenu = true;
								}

				

							}

							if (confirm || clicked)
							{
								if (statsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
								{
									leaveMenu = true;
								}
								if (statsMenu->isSelectedID("Stats Type", clicked, mx, my))
								{
									whichStatsMiniMenuShowing = true;
								}

								if (statsMenu->isSelectedID("Game", clicked, mx, my))
								{
									selectGameSequenceOrSingleGameTypeMenuShowing = true;
								}

								if (statsMenu->isSelectedID("Difficulty", clicked, mx, my))
								{
									difficultyMenuShowing = true;
								}

								if (statsMenu->isSelectedID("Objective", clicked, mx, my) || yourStatsMenu->isSelectedID("Objective", clicked, mx, my) || leaderBoardMenu->isSelectedID("Objective", clicked, mx, my))
								{
									if (statsMenu_objectiveName == "Endless Mode")statsMenu_objectiveName = "Play To Credits";
									else statsMenu_objectiveName = "Endless Mode";
									updateStatsMenu = true;
								}

							}
						}

	if (yourStatsMenu == nullptr)
	{
		yourStatsMenu = ms<OKMenu>(this, "", "Your Stats");
		yourStatsMenu->center = false;
		yourStatsMenu->setFontSize(14);
		yourStatsMenu->outline = false;
		yourStatsMenu->defaultMenuColor = OKColor::darkGray;

		updateStatsMenu = true;

		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, "OVERALL", "OVERALL", statsMenu_objectiveName);

	}

	if (leaderBoardMenu == nullptr)
	{
		leaderBoardMenu = ms<OKMenu>(this, "", "High Scores");
		leaderBoardMenu->center = false;
		leaderBoardMenu->setFontSize(14);
		leaderBoardMenu->outline = false;
		leaderBoardMenu->defaultMenuColor = OKColor::darkGray;

		string title = populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, "OVERALL", "OVERALL", statsMenu_objectiveName,
			statsMenu_totalTimePlayed, statsMenu_totalBlocksCleared, statsMenu_planeswalkerPoints, statsMenu_eloScore, statsMenu_timeLasted, statsMenu_blocksCleared);

		leaderBoardMenu->subtitleCaption->setText(title);
	}

	long long currentTime = System::currentHighResTimer();
	long long startTime = updateStatsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (updateStatsMenu || ticksPassed > 200)
	{
		updateStatsMenu = false;
		updateStatsTime = currentTime;

		yourStatsMenu->clear();
		leaderBoardMenu->clear();


		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName);

		string title = populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName,
				statsMenu_totalTimePlayed, statsMenu_totalBlocksCleared, statsMenu_planeswalkerPoints, statsMenu_eloScore, statsMenu_timeLasted, statsMenu_blocksCleared);

		leaderBoardMenu->subtitleCaption->setText(title);

		yourStatsMenu->setAllCaptionsToFullAlpha();
		leaderBoardMenu->setAllCaptionsToFullAlpha();
	}




	if (getControlsManager()->miniGame_CANCEL_Pressed())
	{
		leaveMenu = true;
	}

	if (leaveMenu)
	{
		statsMenuShowing = false;
		startScreenMenuShowing = true;

		if (statsMenu != nullptr)
		{
			statsMenuCursorPosition = statsMenu->cursorPosition;
			//delete statsMenu;
			statsMenu = nullptr;
		}
		if (yourStatsMenu != nullptr)
		{
			//delete yourStatsMenu;
			yourStatsMenu = nullptr;
		}
		if (leaderBoardMenu != nullptr)
		{
			//delete leaderBoardMenu;
			leaderBoardMenu = nullptr;
		}

	}
}

//=========================================================================================================================
void OKGame::statsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = chartTexture;

	if (statsMenu == nullptr)return;

	if (t != nullptr)
	{
		statsMenu->setGraphic(t, getWidth() / 4, getHeight() / 10);
	}


	int startHeight = 0;
	int bottomHeight = 0;
	int leftX = 0;
	int rightX = 0;
	statsMenu->render(0, (getWidth() - (statsMenu->lastWidth + 50 + yourStatsMenu->lastWidth + 50 + leaderBoardMenu->lastWidth)) / 2, getHeight(), true, &startHeight, &bottomHeight, false, &leftX, &rightX);
	yourStatsMenu->render(startHeight, rightX + 50, getHeight(), false, nullptr, nullptr, false, nullptr, &rightX);
	leaderBoardMenu->render(startHeight, rightX + 50, getHeight(), false, nullptr, nullptr, false);

	if (whichStatsMiniMenuShowing && whichStatsMiniMenu != nullptr)
	{
		sp<Caption>c = statsMenu->getCaptionByID("Stats Type");
		whichStatsMiniMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = statsMenu->getCaptionByID("Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		sp<Caption>c = statsMenu->getCaptionByID("Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = statsMenu->getCaptionByID("Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (difficultyMenuShowing && difficultyMenu != nullptr)
	{
		sp<Caption>c = statsMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

}


//
//void selectedGameSequence(sp<OKGame>b, string name)
//{
//	//get game sequence by name
//	//set current game sequence
//}
//
//void selectedGameType(sp<OKGame>b, string name)
//{
//	//select game type by name
//	//create new game sequence with only that one game type
//	//set current game sequence
//}
//
//void selectedDifficulty(sp<OKGame>b, string name)
//{
//	//set current difficulty type
//}
//
//void selectedObjective(sp<OKGame>b, string& name)
//{
//	if(name=="End At Credits Level")
//	{
//
//	}
//
//	if(name == "Endless")
//	{
//
//	}
//}
//

//enum class StartWithOption
//{
//	FIRST_GAME,
//	RANDOM,
//};
//
//enum class PlayOrderOption
//{
//	RANDOM_BAG,
//	TOTALLY_RANDOM,
//	IN_ORDER,
//};

//enum class GameObjective
//{
//	PLAY_TO_CREDITS_LEVEL,
//	ENDLESS,
//	LAST,
//};




//=========================================================================================================================
void OKGame::saveRoomConfigMenuUpdate()
{//=========================================================================================================================


	if (saveRoomConfigMenu == nullptr)
	{
		chatEnabled = false;

		saveRoomConfigMenu = ms<OKMenu>(this, "");
		saveRoomConfigMenu->center = false;
		//saveRoomConfigMenu->outline = false;

		saveRoomConfigNameText = "" + currentRoom->gameSequence->name + " " + currentRoom->room_DifficultyName + " ";


		saveRoomConfigMenu->add("Name: " + saveRoomConfigNameText,"Name", OKMenu::statusColor);
		saveRoomConfigMenu->add("Save");
		saveRoomConfigMenu->add("Cancel");




		saveRoomConfigMenu->cursorPosition = saveRoomConfigMenuCursorPosition;
	}


	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();

	if (mx != lastMX || my != lastMY)
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		lastMX = mx;
		lastMY = my;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		saveRoomConfigMenu->up();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	if (getControlsManager()->miniGame_DOWN_Pressed() || getControlsManager()->key_TAB_Pressed())
	{
		saveRoomConfigMenu->down();

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}


	if (saveRoomConfigMenu->isSelectedID("Name"))
	{
		if (!textStarted) { SDL_StartTextInput(); getControlsManager()->text = saveRoomConfigNameText; textStarted = true; }
		saveRoomConfigNameText = getControlsManager()->text;
		saveRoomConfigMenu->getMenuItemByID("Name")->setText("Name: " + saveRoomConfigNameText);
	}
	else
	{
		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
	}

	bool leaveMenu = false;
	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

	if (confirm || clicked)
	{

		if (saveRoomConfigMenu->isSelectedID("Save", clicked, mx, my))
		{
			if (name.length() > 0)
			{

				time_t t = time(0); // get time now
				struct tm * now = localtime(&t);
				string year = to_string(now->tm_year + 1900);
				string month = to_string((now->tm_mon + 1));
				string day = to_string(now->tm_mday);
				string hour = to_string(now->tm_hour);
				string minute = to_string(now->tm_min);
				string second = to_string(now->tm_sec);

				string name = saveRoomConfigNameText + " " + year + "-" + month + "-" + day + "-" + hour + "-" + minute + "-" + second + ".roomConfig";

				name = FileUtils::removeIllegalFilenameChars(name);

				leaveMenu = true;

				OKGame::saveRoomConfigToFile(currentRoom, name);
			}
		}

		if (saveRoomConfigMenu->isSelectedID("Cancel", clicked, mx, my))
		{
			leaveMenu = true;
		}
	}

	if (leaveMenu)
	{
		chatEnabled = true;

		if (textStarted) { SDL_StopTextInput(); textStarted = false; }
		saveRoomConfigMenuShowing = false;
		if (saveRoomConfigMenu != nullptr)
		{
			saveRoomConfigMenuCursorPosition = saveRoomConfigMenu->cursorPosition;
			//delete saveRoomConfigMenu;
			saveRoomConfigMenu = nullptr;
		}
	}
}


//=========================================================================================================================
void OKGame::loadRoomConfigMenuUpdate()
{//=========================================================================================================================

	if (loadRoomConfigMenu == nullptr)
	{
		loadRoomConfigMenu = ms<OKMenu>(this, "");
		loadRoomConfigMenu->center = false;
		//loadRoomConfigMenu->outline = false;



		sp<vector<string>> roomConfigNames = OKGame::getRoomConfigsList();

		for (int i = 0; i < roomConfigNames->size(); i++)
		{
			loadRoomConfigMenu->add(roomConfigNames->at(i));
		}

		loadRoomConfigMenu->add("Cancel");

		loadRoomConfigMenu->cursorPosition = loadRoomConfigMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		loadRoomConfigMenu->up();
	}
	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		loadRoomConfigMenu->down();
	}
	bool leaveMenu = false;
	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{


		if (loadRoomConfigMenu->isSelectedID("Cancel", clicked, mx, my))
		{
			leaveMenu = true;
		}
		else
		{

			sp<vector<string>>ids = loadRoomConfigMenu->getArrayListOfMenuItemIDs();

			for (int i = 0; i < ids->size(); i++)
			{
				if (loadRoomConfigMenu->isSelectedID(ids->at(i), clicked, mx, my))
				{
					sp<Room>r = OKGame::loadRoomConfig(ids->at(i));

					if (r != nullptr)currentRoom = r;
					leaveMenu = true;
				}
			}
		}



	}

	if (leaveMenu)
	{
		loadRoomConfigMenuShowing = false;
		if (loadRoomConfigMenu != nullptr)
		{
			loadRoomConfigMenuCursorPosition = loadRoomConfigMenu->cursorPosition;
			//delete loadRoomConfigMenu;
			loadRoomConfigMenu = nullptr;
		}
	}
}


//=========================================================================================================================
void OKGame::gameObjectiveMenuUpdate()
{//=========================================================================================================================

	const string PLAY_TO_CREDITS_LEVEL = "Play To Credits";
	const string ENDLESS = "Endless Mode";
	if (gameObjectiveMenu == nullptr)
	{
		gameObjectiveMenu = ms<OKMenu>(this, "");
		//gameObjectiveMenu->outline = false;

		gameObjectiveMenu->add(PLAY_TO_CREDITS_LEVEL);
		gameObjectiveMenu->add(ENDLESS);
		gameObjectiveMenu->cursorPosition = gameObjectiveMenuCursorPosition;
	}
	if (getControlsManager()->miniGame_UP_Pressed())
	{
		gameObjectiveMenu->up();
	}
	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		gameObjectiveMenu->down();
	}
	bool leaveMenu = false;
	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (gameObjectiveMenu->isSelectedID(PLAY_TO_CREDITS_LEVEL, clicked, mx, my))
		{
			//selectedObjectiveIndex = (int)GameObjective::PLAY_TO_CREDITS_LEVEL;
			if (currentRoom != nullptr)currentRoom->endlessMode = false;
		}

		if (gameObjectiveMenu->isSelectedID(ENDLESS, clicked, mx, my))
		{
			//selectedObjectiveIndex = (int)GameObjective::ENDLESS;
			if (currentRoom != nullptr)currentRoom->endlessMode = true;
		}

		leaveMenu = true;
	}

	if (leaveMenu)
	{
		gameObjectiveMenuShowing = false;
		if (gameObjectiveMenu != nullptr)
		{
			gameObjectiveMenuCursorPosition = gameObjectiveMenu->cursorPosition;
			//delete gameObjectiveMenu;
			gameObjectiveMenu = nullptr;
		}
		updateStatsMenu = true;
	}
}
//=========================================================================================================================
void OKGame::sendGarbageToMenuUpdate()
{//=========================================================================================================================

	const string SEND_GARBAGE_TO_ALL_PLAYERS="All Other Players";
	const string SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE="All Other Players 50% Chance";
	const string SEND_GARBAGE_TO_RANDOM_PLAYER="One Random Player";
	const string SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION="Rotate Between Other Players";
	const string SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS="Player With Least Blocks";

	if (sendGarbageToMenu == nullptr)
	{
		sendGarbageToMenu = ms<OKMenu>(this, "");
		//sendGarbageToMenu->outline = false;


		sendGarbageToMenu->add(SEND_GARBAGE_TO_ALL_PLAYERS);
		sendGarbageToMenu->add(SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE);
		if (networkMultiplayer == false)
		{
			sendGarbageToMenu->add(SEND_GARBAGE_TO_RANDOM_PLAYER);
			sendGarbageToMenu->add(SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION);
			sendGarbageToMenu->add(SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS);
		}

		sendGarbageToMenu->cursorPosition = sendGarbageToMenuCursorPosition;
	}
	if (getControlsManager()->miniGame_UP_Pressed())
	{
		sendGarbageToMenu->up();
	}
	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		sendGarbageToMenu->down();
	}
	bool leaveMenu = false;
	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		if (sendGarbageToMenu->isSelectedID(SEND_GARBAGE_TO_ALL_PLAYERS, clicked, mx, my))currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS;
		if (sendGarbageToMenu->isSelectedID(SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE, clicked, mx, my))currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE;
		if (sendGarbageToMenu->isSelectedID(SEND_GARBAGE_TO_RANDOM_PLAYER, clicked, mx, my))currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_RANDOM_PLAYER;
		if (sendGarbageToMenu->isSelectedID(SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION, clicked, mx, my))currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION;
		if (sendGarbageToMenu->isSelectedID(SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS, clicked, mx, my))currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS;

		leaveMenu = true;
	}

	if (leaveMenu)
	{
		sendGarbageToMenuShowing = false;
		if (sendGarbageToMenu != nullptr)
		{
			sendGarbageToMenuCursorPosition = sendGarbageToMenu->cursorPosition;
			//delete sendGarbageToMenu;
			sendGarbageToMenu = nullptr;
		}
	}
}

float myMin(float a, float b)
{
    if(a<b)return a;
    return b;
}
float myMax(float a, float b)
{
    if(a>b)return a;
    return b;
}
//=========================================================================================================================
void OKGame::leftRightMenuAdjustFloat(float& variable, float min, float max, float minIncrement, float maxIncrement)
{//=========================================================================================================================

	bool leftHeld = getControlsManager()->MINIGAME_LEFT_HELD;
	bool rightHeld = getControlsManager()->MINIGAME_RIGHT_HELD;

	long long currentTime = System::currentHighResTimer();

	if (leftHeld || rightHeld)
	{
		int ticksSinceStart = (int)(System::getTicksBetweenTimes(timeStartedChangedSetting, currentTime));
		float increment = minIncrement + (myMin((myMax(ticksSinceStart - 200, 0) / 1000.0f), 1.0f) * (float)(maxIncrement - minIncrement));

		long long startTime = timeLastChangedSetting;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 30)
		{
			timeLastChangedSetting = currentTime;

			if (leftHeld)
			{
				if (variable > min)variable -= increment;
				if (variable < min)variable = min;
			}

			if (rightHeld)
			{
				if (variable < max)variable += increment;
				if (variable > max)variable = max;
			}
		}
	}
	else
	{
		timeStartedChangedSetting = currentTime;
	}
}


//=========================================================================================================================
void OKGame::leftRightMenuAdjustInt(int& variable, int min, int max, int minIncrement, int maxIncrement)
{//=========================================================================================================================

	bool leftHeld = getControlsManager()->MINIGAME_LEFT_HELD;
	bool rightHeld = getControlsManager()->MINIGAME_RIGHT_HELD;

	long long currentTime = System::currentHighResTimer();

	if (leftHeld || rightHeld)
	{
		int ticksSinceStart = (int)(System::getTicksBetweenTimes(timeStartedChangedSetting, currentTime));
		int increment = minIncrement + (myMin((int)(myMax(ticksSinceStart - 200, 0) / 1000.0f), 1.0f) * (float)(maxIncrement - minIncrement));
		

		long long startTime = timeLastChangedSetting;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 30)
		{
			timeLastChangedSetting = currentTime;

			if (leftHeld)
			{
				if (variable > min)variable -= increment;
				if (variable < min)variable = min;
			}

			if (rightHeld)
			{
				if (variable < max)variable += increment;
				if (variable > max)variable = max;
			}
		}
	}
	else
	{
		timeStartedChangedSetting = currentTime;
	}
}


//=========================================================================================================================
void OKGame::roomOptionsMenuUpdate()
{//=========================================================================================================================

	//const string OBJECTIVE = "Objective";


	if (roomOptionsMenu == nullptr)
	{
		if (descriptionCaption != nullptr) 
		{ 
			//delete descriptionCaption; 
			descriptionCaption = nullptr; 
		}
		descriptionCaption = ms<Caption>(this, Caption::Position::CENTERED_X, 0, 0, -1, "", 18, false, OKColor::darkGray, OKColor::clear);
		roomOptionsMenu = ms<OKMenu>(this, "");
		roomOptionsMenu->center = false;
		roomOptionsMenu->setFontSize(24);
		//roomOptionsMenu->outline = false;
		//roomOptionsMenu->defaultMenuColor = OKColor::gray;


		roomOptionsMenu->add("Game Speed Start: ", "Game Speed Start");
		roomOptionsMenu->add("Game Speed Increase Rate: ", "Game Speed Change Rate");
		roomOptionsMenu->add("Game Speed Maximum: ", "Game Speed Maximum");
		roomOptionsMenu->addInfo(" ");
		roomOptionsMenu->add("Score Needed To Level Up Multiplier: ", "Levelup Multiplier");
		roomOptionsMenu->add("Score Needed To Level Up Compound Multiplier: ", "Levelup Compound Multiplier");
		roomOptionsMenu->addInfo(" ");
		roomOptionsMenu->add("Floor Movement Limit: ", "Floor Movement Limit");
		roomOptionsMenu->add("Total Lock Delay Limit: ", "Total Lock Delay Limit");
		roomOptionsMenu->add("Lock Delay Decrease Rate: ", "Lock Delay Decrease Rate");
		roomOptionsMenu->add("Lock Delay Minimum: ", "Lock Delay Minimum");
		roomOptionsMenu->addInfo(" ");
		roomOptionsMenu->add("Stack Wait Limit: ", "Stack Wait Limit");
		roomOptionsMenu->add("Spawn Delay Limit: ", "Spawn Delay Limit");
		roomOptionsMenu->add("Spawn Delay Decrease Rate: ", "Spawn Delay Decrease Rate");
		roomOptionsMenu->add("Spawn Delay Minimum: ", "Spawn Delay Minimum");
		roomOptionsMenu->add("Drop Delay Minimum: ", "Drop Delay Minimum");

		if (localMultiplayer || networkMultiplayer)
		{
			roomOptionsMenu->addInfo(" ");
			roomOptionsMenu->addInfo("Multiplayer Options:");


			//roomOptionsMenu->add("Allow New Players To Join During Game: ", "Allow Join");
			//roomOptionsMenu->add("Use Teams: ", "Use Teams");
			roomOptionsMenu->add("End Rule: Game Ends When One Player Remains", "End Rule");
			roomOptionsMenu->add("Finish Rule: End On First Completion", "Finish Rule");
			roomOptionsMenu->addInfo(" ");
			roomOptionsMenu->add("VS Garbage: ", "Garbage Rule");
			roomOptionsMenu->add("Garbage Multiplier: ", "Garbage Multiplier");
			roomOptionsMenu->add("Garbage Limit: ", "Garbage Limit");
			roomOptionsMenu->add("Scale Garbage By Difficulty: ", "Garbage Scale");
			roomOptionsMenu->add("Send Garbage To: ", "Garbage Scale");



			//TODO: infinite spin max time ?
			//lock delay limit, floor kick limit, 128 turns, step delay
			//allow teams(your team sends garbage to other team only), team victory, colored border, maybe caption
			//add select team to player setup minimenu

		}

		roomOptionsMenu->addInfo(" ");
		roomOptionsMenu->add("Set Defaults", "Defaults");
		roomOptionsMenu->addInfo(" ");
		roomOptionsMenu->add("Apply Options And Close", "Apply");

		roomOptionsMenu->cursorPosition = roomOptionsMenuCursorPosition;
	}


	roomOptionsMenu->getMenuItemByID("Game Speed Start")->setText("Game Speed Start: " + to_string((int)(currentRoom->gameSpeedStart * 100)) + "%");
	roomOptionsMenu->getMenuItemByID("Game Speed Change Rate")->setText("Game Speed Change Rate: " + to_string((int)(currentRoom->gameSpeedChangeRate * 100)) + "%");
	roomOptionsMenu->getMenuItemByID("Game Speed Maximum")->setText("Game Speed Maximum: " + to_string((int)(currentRoom->gameSpeedMaximum * 100)) + "%");
	roomOptionsMenu->getMenuItemByID("Levelup Multiplier")->setText("Score Needed To Level Up Multiplier: " + to_string((int)(currentRoom->levelUpMultiplier * 100)) + "%");
	roomOptionsMenu->getMenuItemByID("Levelup Compound Multiplier")->setText("Score To Level Up Compound Multiplier: " + to_string((int)(currentRoom->levelUpCompoundMultiplier * 100)) + "%");
	roomOptionsMenu->getMenuItemByID("Floor Movement Limit")->setText("Floor Movement Limit: " + string((currentRoom->floorSpinLimit > -1) ? to_string(currentRoom->floorSpinLimit) : "No Limit"));
	roomOptionsMenu->getMenuItemByID("Total Lock Delay Limit")->setText("Total Lock Delay Limit: " + string((currentRoom->totalYLockDelayLimit > -1) ? to_string(currentRoom->totalYLockDelayLimit) + "ms" : "No Limit"));
	roomOptionsMenu->getMenuItemByID("Lock Delay Decrease Rate")->setText("Lock Delay Decrease Rate: " + string((currentRoom->lockDelayDecreaseRate > 0) ? to_string((int)(currentRoom->lockDelayDecreaseRate * 100)) + "%" : "None"));
	roomOptionsMenu->getMenuItemByID("Lock Delay Minimum")->setText("Lock Delay Minimum: " + string((currentRoom->lockDelayMinimum > 0) ? to_string(currentRoom->lockDelayMinimum) + "ms" : "None"));
	roomOptionsMenu->getMenuItemByID("Stack Wait Limit")->setText("Stack Wait Limit: " + string((currentRoom->stackWaitLimit > -1) ? to_string(currentRoom->stackWaitLimit) + "ms" : "No Limit"));
	roomOptionsMenu->getMenuItemByID("Spawn Delay Limit")->setText("Spawn Delay Limit: " + string((currentRoom->spawnDelayLimit > -1) ? to_string(currentRoom->spawnDelayLimit) + "ms" : "No Limit"));
	roomOptionsMenu->getMenuItemByID("Spawn Delay Decrease Rate")->setText("Spawn Delay Decrease Rate: " + string((currentRoom->spawnDelayDecreaseRate > 0) ? to_string((int)(currentRoom->spawnDelayDecreaseRate * 100)) + "%" : "None"));
	roomOptionsMenu->getMenuItemByID("Spawn Delay Minimum")->setText("Spawn Delay Minimum: " + string((currentRoom->spawnDelayMinimum > 0) ? to_string(currentRoom->spawnDelayMinimum) + "ms" : "None"));
	roomOptionsMenu->getMenuItemByID("Drop Delay Minimum")->setText("Drop Delay Minimum: " + string((currentRoom->dropDelayMinimum > 0) ? to_string(currentRoom->dropDelayMinimum) + "ms" : "None"));


	if (localMultiplayer || networkMultiplayer)
	{

		//roomOptionsMenu->getMenuItemByID("Allow Join")->setText("Allow New Players To Join During Game: " + string(currentRoom->multiplayer_AllowNewPlayersDuringGame ? "On" : "Off"));
		//roomOptionsMenu->getMenuItemByID("Use Teams")->setText("Use Teams: " + string(currentRoom->multiplayer_UseTeams ? "On" : "Off"));

		if (currentRoom->multiplayer_GameEndsWhenOnePlayerRemains)
			roomOptionsMenu->getMenuItemByID("End Rule")->setText("End Rule: Game Ends When One Player Remains");
		else roomOptionsMenu->getMenuItemByID("End Rule")->setText("End Rule: Continue Until All Players Lose");

		if (currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)
			roomOptionsMenu->getMenuItemByID("Finish Rule")->setText("Finish Rule: End On First Completion");
		else roomOptionsMenu->getMenuItemByID("Finish Rule")->setText("Finish Rule: Free Play To Completion");

		if (currentRoom->endlessMode)
		{
			roomOptionsMenu->getMenuItemByID("Finish Rule")->setText("Finish Rule: Endless Mode");
			roomOptionsMenu->getMenuItemByID("Finish Rule")->info = true;
		}
		else
		{
			roomOptionsMenu->getMenuItemByID("Finish Rule")->info = false;
		}

		roomOptionsMenu->getMenuItemByID("Garbage Rule")->setText("VS Garbage: " + string((currentRoom->multiplayer_DisableVSGarbage) ? "Off" : "On"));
		roomOptionsMenu->getMenuItemByID("Garbage Multiplier")->setText("Garbage Multiplier: " + to_string((int)(currentRoom->multiplayer_GarbageMultiplier > 100)) + "%");
		roomOptionsMenu->getMenuItemByID("Garbage Limit")->setText("Garbage Limit: " + string((currentRoom->multiplayer_GarbageLimit > 0) ? to_string(currentRoom->multiplayer_GarbageLimit) : "No Limit"));
		roomOptionsMenu->getMenuItemByID("Garbage Scale")->setText("Scale Garbage By Difficulty: " + string(currentRoom->multiplayer_GarbageScaleByDifficulty ? "On" : "Off"));

		if (currentRoom->multiplayer_SendGarbageTo == (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS)roomOptionsMenu->getMenuItemByID("Send Garbage To")->setText("Send Garbage To: All Other Players");
		if (currentRoom->multiplayer_SendGarbageTo == (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE)roomOptionsMenu->getMenuItemByID("Send Garbage To")->setText("Send Garbage To: All Other Players 50% Chance");
		if (currentRoom->multiplayer_SendGarbageTo == (int)SendGarbageToRule::SEND_GARBAGE_TO_RANDOM_PLAYER)roomOptionsMenu->getMenuItemByID("Send Garbage To")->setText("Send Garbage To: One Random Player");
		if (currentRoom->multiplayer_SendGarbageTo == (int)SendGarbageToRule::SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION)roomOptionsMenu->getMenuItemByID("Send Garbage To")->setText("Send Garbage To: Rotate Between Other Players");
		if (currentRoom->multiplayer_SendGarbageTo == (int)SendGarbageToRule::SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS)roomOptionsMenu->getMenuItemByID("Send Garbage To")->setText("Send Garbage To: Player With Least Blocks");

	}




	if (sendGarbageToMenuShowing)
	{
		sendGarbageToMenuUpdate();
	}
	else
	{

		if (getControlsManager()->miniGame_UP_Pressed())
		{
			roomOptionsMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			roomOptionsMenu->down();
		}




		if (roomOptionsMenu->isSelectedID("Game Speed Start"))
		{
			leftRightMenuAdjustFloat(currentRoom->gameSpeedStart, 0.01f, 1.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Game Speed Change Rate"))
		{
			leftRightMenuAdjustFloat(currentRoom->gameSpeedChangeRate, -1.0f, 1.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Game Speed Maximum"))
		{
			leftRightMenuAdjustFloat(currentRoom->gameSpeedMaximum, 0.01f, 5.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Levelup Multiplier"))
		{
			leftRightMenuAdjustFloat(currentRoom->levelUpMultiplier, 0.01f, 10.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Levelup Compound Multiplier"))
		{
			leftRightMenuAdjustFloat(currentRoom->levelUpCompoundMultiplier, -1.0f, 1.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Garbage Multiplier"))
		{
			leftRightMenuAdjustFloat(currentRoom->multiplayer_GarbageMultiplier, 0.01f, 2.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Garbage Limit"))
		{
			leftRightMenuAdjustInt(currentRoom->multiplayer_GarbageLimit, 0, 50, 1, 2);
		}

		if (roomOptionsMenu->isSelectedID("Floor Movement Limit"))
		{
			leftRightMenuAdjustInt(currentRoom->floorSpinLimit, -1, 128, 1, 3);
		}

		if (roomOptionsMenu->isSelectedID("Total Lock Delay Limit"))
		{
			leftRightMenuAdjustInt(currentRoom->totalYLockDelayLimit, -1, 10000, 1, 300);
		}

		if (roomOptionsMenu->isSelectedID("Lock Delay Decrease Rate"))
		{
			leftRightMenuAdjustFloat(currentRoom->lockDelayDecreaseRate, 0.0f, 1.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Lock Delay Minimum"))
		{
			leftRightMenuAdjustInt(currentRoom->lockDelayMinimum, 0, 10000, 1, 300);
		}

		if (roomOptionsMenu->isSelectedID("Stack Wait Limit"))
		{
			leftRightMenuAdjustInt(currentRoom->stackWaitLimit, -1, 10000, 1, 300);
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Limit"))
		{
			leftRightMenuAdjustInt(currentRoom->spawnDelayLimit, -1, 10000, 1, 300);
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Decrease Rate"))
		{
			leftRightMenuAdjustFloat(currentRoom->spawnDelayDecreaseRate, 0.0f, 1.0f, 0.01f, 0.03f);
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Minimum"))
		{
			leftRightMenuAdjustInt(currentRoom->spawnDelayMinimum, 0, 10000, 1, 300);
		}

		if (roomOptionsMenu->isSelectedID("Drop Delay Minimum"))
		{
			leftRightMenuAdjustInt(currentRoom->dropDelayMinimum, 0, 10000, 1, 300);
		}
		


		if (roomOptionsMenu->isSelectedID("Game Speed Start"))
		{
			descriptionCaption->setText("Percent speed at which the game begins. Default is 0%.");
		}

		if (roomOptionsMenu->isSelectedID("Game Speed Change Rate"))
		{
			descriptionCaption->setText("Percent speed the game changes each level. Default is 2%. Can be negative.");
		}

		if (roomOptionsMenu->isSelectedID("Game Speed Maximum"))
		{
			descriptionCaption->setText("Additional multiplier applied to the maximum game speed (defined in the selected difficulty). Default is 100%.");
		}

		if (roomOptionsMenu->isSelectedID("Levelup Multiplier"))
		{
			descriptionCaption->setText("Multiplier applied globally to score needed (pieces cleared, lines made, etc) to level up. Default is 100%.");
		}

		if (roomOptionsMenu->isSelectedID("Levelup Compound Multiplier"))
		{
			descriptionCaption->setText("Multiplier applied every level to score needed to level up, making each level longer/shorter than the last. Default is 0%. Can be negative");
		}

		if (roomOptionsMenu->isSelectedID("Garbage Multiplier"))
		{
			descriptionCaption->setText("Multiplier for sent garbage. Default is 100%.");
		}

		if (roomOptionsMenu->isSelectedID("Garbage Limit"))
		{
			descriptionCaption->setText("Hard limit on garbage queued. Default is no limit.");
		}

		if (roomOptionsMenu->isSelectedID("Floor Movement Limit"))
		{
			descriptionCaption->setText("How many times a piece can be spun in place or moved on the same Y position before locking. Set to 0 to always lock instantly. Default is no limit (infinite spin).");
		}

		if (roomOptionsMenu->isSelectedID("Total Lock Delay Limit"))
		{
			descriptionCaption->setText("Maximum total milliseconds a piece can stay in the same Y position before locking. Set to 0 to always lock instantly. Default is no limit.");
		}

		if (roomOptionsMenu->isSelectedID("Lock Delay Decrease Rate"))
		{
			descriptionCaption->setText("Percent the lock delay will decrease each level. Default is 0 (Lock delay does not decrease).");
		}

		if (roomOptionsMenu->isSelectedID("Lock Delay Minimum"))
		{
			descriptionCaption->setText("Minimum milliseconds before a piece locks. Resets every movement or rotation. Set to 0 to always lock instantly. Default is 500.");
		}

		if (roomOptionsMenu->isSelectedID("Stack Wait Limit"))
		{
			descriptionCaption->setText("Maximum milliseconds that the stack can be waiting to scroll after a combo. Set to 0 to always scroll. Default is no limit.");
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Limit"))
		{
			descriptionCaption->setText("Maximum milliseconds that a piece will wait at the top before moving down. Set to 0 to always spawn instantly. Default is no limit.");
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Decrease Rate"))
		{
			descriptionCaption->setText("Percent the initial spawn delay will decrease each level. Making combos can increase it up to the limit. Default is 0 (Spawn delay does not decrease).");
		}

		if (roomOptionsMenu->isSelectedID("Spawn Delay Minimum"))
		{
			descriptionCaption->setText("Minimum milliseconds for a spawned piece to move down. Does nothing if spawn rate does not decrease. Default is 500.");
		}

		if (roomOptionsMenu->isSelectedID("Drop Delay Minimum"))
		{
			descriptionCaption->setText("Minimum milliseconds for a piece to move down a row. Overrides minimum set in difficulty. Default is 500.");
		}

		if (roomOptionsMenu->isSelectedID("End Rule"))
		{
			descriptionCaption->setText("");
		}

		if (roomOptionsMenu->isSelectedID("Finish Rule"))
		{
			descriptionCaption->setText("");
		}

		if (roomOptionsMenu->isSelectedID("Garbage Rule"))
		{
			descriptionCaption->setText("");
		}

		if (roomOptionsMenu->isSelectedID("Allow Join"))
		{
			descriptionCaption->setText("Allow new players to join while the match is going, for more casual ongoing games.");
		}

		if (roomOptionsMenu->isSelectedID("Use Teams"))
		{
			descriptionCaption->setText("Players can select a team color, and their garbage will only be sent to the other teams. The winning player's team wins.");
		}

		if (roomOptionsMenu->isSelectedID("Garbage Scale"))
		{
			descriptionCaption->setText("This will scale the amount of garbage sent based on the difference in difficulty. Insane will send 0.25x to Beginner, but receive 4x.");
		}

		if (roomOptionsMenu->isSelectedID("Send Garbage To"))
		{
			descriptionCaption->setText("");
		}

		if (roomOptionsMenu->isSelectedID("Defaults"))
		{
			descriptionCaption->setText("Set all options to default.");
		}

		if (roomOptionsMenu->isSelectedID("Apply"))
		{
			descriptionCaption->setText("Apply settings and return to game setup screen.");
		}


		bool left = getControlsManager()->miniGame_LEFT_Pressed();
		bool right = getControlsManager()->miniGame_RIGHT_Pressed();

		bool leaveMenu = false;

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
		int mx = getControlsManager()->getMouseX();
		int my = getControlsManager()->getMouseY();
		if (confirm || clicked || left || right)
		{




			if (roomOptionsMenu->isSelectedID("End Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_GameEndsWhenOnePlayerRemains = !currentRoom->multiplayer_GameEndsWhenOnePlayerRemains;
			}

			if (roomOptionsMenu->isSelectedID("Finish Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = !currentRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel;
			}

			if (roomOptionsMenu->isSelectedID("Garbage Rule", clicked, mx, my))
			{
				currentRoom->multiplayer_DisableVSGarbage = !currentRoom->multiplayer_DisableVSGarbage;
			}

			if (roomOptionsMenu->isSelectedID("Allow Join", clicked, mx, my))
			{
				currentRoom->multiplayer_AllowNewPlayersDuringGame = !currentRoom->multiplayer_AllowNewPlayersDuringGame;
			}

			if (roomOptionsMenu->isSelectedID("Use Teams", clicked, mx, my))
			{
				currentRoom->multiplayer_UseTeams = !currentRoom->multiplayer_UseTeams;
			}

			if (roomOptionsMenu->isSelectedID("Garbage Scale", clicked, mx, my))
			{
				currentRoom->multiplayer_GarbageScaleByDifficulty = !currentRoom->multiplayer_GarbageScaleByDifficulty;
			}

			if (roomOptionsMenu->isSelectedID("Send Garbage To", clicked, mx, my))
			{
				if (confirm || clicked)sendGarbageToMenuShowing = true;
				else
				{

					if(networkMultiplayer)
					{
						if (left)
						{
							currentRoom->multiplayer_SendGarbageTo--;
							if (currentRoom->multiplayer_SendGarbageTo < 0)currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE;
						}
						if (right)
						{
							currentRoom->multiplayer_SendGarbageTo++;
							if (currentRoom->multiplayer_SendGarbageTo > (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE)currentRoom->multiplayer_SendGarbageTo = 0;
						}

					}
					else
					{
						if (left)
						{
							currentRoom->multiplayer_SendGarbageTo--;
							if (currentRoom->multiplayer_SendGarbageTo < 0)currentRoom->multiplayer_SendGarbageTo = (int)SendGarbageToRule::LAST - 1;
						}
						if (right)
						{
							currentRoom->multiplayer_SendGarbageTo++;
							if (currentRoom->multiplayer_SendGarbageTo >= (int)SendGarbageToRule::LAST)currentRoom->multiplayer_SendGarbageTo = 0;
						}
					}

				}
			}
		}

		if (confirm || clicked)
		{
			if (roomOptionsMenu->isSelectedID("Defaults", clicked, mx, my))
			{
				currentRoom->setDefaults();
			}

			if (roomOptionsMenu->isSelectedID("Apply", clicked, mx, my))
			{
				leaveMenu = true;
			}
		}

		if (leaveMenu)
		{
			roomOptionsMenuShowing = false;

			if (descriptionCaption != nullptr) 
			{ 
				//delete descriptionCaption; 
				descriptionCaption = nullptr; 
			}

			if (roomOptionsMenu != nullptr)
			{
				roomOptionsMenuCursorPosition = roomOptionsMenu->cursorPosition;
				//delete roomOptionsMenu;
				roomOptionsMenu = nullptr;
			}
		}
	}

}



//=========================================================================================================================
void OKGame::gameSetupMenuUpdate()
{//=========================================================================================================================

	if (gameSetupMenu == nullptr)
	{

		errorLabel = ms<Caption>(this, Caption::Position::CENTERED_X, 0, 0, -1, "", 16, false, OKColor::red, OKColor::clear);

		gameSetupMenu = ms<OKMenu>(this, "Setup Game Options");
		gameSetupMenu->center = false;

		gameSetupMenu->add("Start Game", "Start Game", OKColor::green);
		gameSetupMenu->addInfo(" ", " ");
		gameSetupMenu->add("Select Game Sequence Or Single Game Type...", "Select Game");
		gameSetupMenu->add("Difficulty: Beginner", "Difficulty");
		gameSetupMenu->add("Objective: ", "Objective");

		gameSetupMenu->add("More Options...", "Options");
		gameSetupMenu->addInfo(" ", " ");
		gameSetupMenu->add("Save Config...", "Save");
		gameSetupMenu->add("Load Config...", "Load");
		gameSetupMenu->addInfo(" ", " ");
		gameSetupMenu->add("Back To Title Screen", "Back To Title Screen");

		gameSetupMenu->cursorPosition = gameSetupMenuCursorPosition;

	}


	if(currentRoom->isDefaultSettings()==false)
	{
		errorLabel->setText("Settings are not default, score will not count towards leaderboard ranking.");
	}
	else
	{
		errorLabel->setText("");
	}


	{
		sp<GameSequence>selectedGameSequence = nullptr;
		if (localMultiplayer || networkMultiplayer)
		{
			selectedGameSequence = currentRoom->gameSequence;
		}
		else
		{
			selectedGameSequence = getPlayer1Game()->currentGameSequence;
		}

		if (selectedGameSequence == nullptr)
		{
			selectedGameSequence = getGameSequenceByName("bob's game");
			if (selectedGameSequence == nullptr)
			{
				selectedGameSequence = ms<GameSequence>();
				selectedGameSequence->gameTypes->push_back(ms<GameType>());
			}
			currentRoom->gameSequence = selectedGameSequence;
			getPlayer1Game()->currentGameSequence = selectedGameSequence;
		}

		{
			sp<OKMenu::MenuItem> c = gameSetupMenu->getMenuItemByID("Select Game");
			if (c != nullptr)
			{
				if (selectedGameSequence->gameTypes->size() > 1)
				{
					c->setText("Game Sequence: " + selectedGameSequence->name);
					statsMenu_gameSequenceOrTypeUUID = selectedGameSequence->uuid;
				}
				if (selectedGameSequence->gameTypes->size() == 1)
				{
					c->setText("Game Type: " + selectedGameSequence->name);
					statsMenu_gameSequenceOrTypeUUID = selectedGameSequence->gameTypes->at(0)->uuid;
				}
			}
		}

		gameSetupMenu->getMenuItemByID("Start Game")->setColor(OKMenu::menuColor);
		gameSetupMenu->getMenuItemByID("Start Game")->info = false;

	}


	{
		string selectedDifficultyName = "";
		if (localMultiplayer || networkMultiplayer)
		{
			if (currentRoom == nullptr)currentRoom = ms<Room>();

			if (currentRoom->room_DifficultyName != "")
			{
				selectedDifficultyName = currentRoom->room_DifficultyName;
			}
		}
		else
		{
			if (getPlayer1Game()->currentGameSequence != nullptr)
				selectedDifficultyName = getPlayer1Game()->currentGameSequence->currentDifficultyName;
		}

		if (selectedDifficultyName != "")
		{

			GameType gt;
			for (int i = 0; i < gt.difficultyTypes->size(); i++)
			{
				string difficultyName = gt.difficultyTypes->at(i)->name;
				if (selectedDifficultyName == difficultyName)selectedDifficultyIndex = i;
			}


			if (currentRoom == nullptr)currentRoom = ms<Room>();
			if (currentRoom->room_DifficultyName != "")
			{
				currentRoom->room_DifficultyName = selectedDifficultyName;
			}

			if (getPlayer1Game()->currentGameSequence != nullptr)
				getPlayer1Game()->currentGameSequence->currentDifficultyName = selectedDifficultyName;

			statsMenu_difficultyName = selectedDifficultyName;

			gameSetupMenu->getMenuItemByID("Difficulty")->setText("Difficulty: " + selectedDifficultyName);
		}
	}


	{
		string objectiveString = "";

		if (currentRoom->endlessMode)
		{
			objectiveString = "Endless Mode";
			statsMenu_objectiveName = "Endless Mode";
		}
		else
		{
			objectiveString = "Play To Credits";
			statsMenu_objectiveName = "Play To Credits";
		}
		gameSetupMenu->getMenuItemByID("Objective")->setText("Objective: " + objectiveString);
	}


	if (currentRoom->endlessMode)
	{
		statsMenu_totalTimePlayed = false;
		statsMenu_totalBlocksCleared = false;
		statsMenu_planeswalkerPoints = false;
		statsMenu_eloScore = false;
		statsMenu_timeLasted = false;
		statsMenu_blocksCleared = true;
	}
	else
	{
		statsMenu_totalTimePlayed = false;
		statsMenu_totalBlocksCleared = false;
		statsMenu_planeswalkerPoints = false;
		statsMenu_eloScore = false;
		statsMenu_timeLasted = true;
		statsMenu_blocksCleared = false;
	}

	if (yourStatsMenu == nullptr)
	{
		yourStatsMenu = ms<OKMenu>(this, "", "Your Stats");
		yourStatsMenu->center = false;
		yourStatsMenu->setFontSize(14);
		yourStatsMenu->outline = false;
		yourStatsMenu->defaultMenuColor = OKColor::darkGray;

		updateStatsMenu = true;

		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName);

	}

	if (leaderBoardMenu == nullptr)
	{
		leaderBoardMenu = ms<OKMenu>(this, "", "High Scores");
		leaderBoardMenu->center = false;
		leaderBoardMenu->setFontSize(14);
		leaderBoardMenu->outline = false;
		leaderBoardMenu->defaultMenuColor = OKColor::darkGray;

		string title = populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName,
			statsMenu_totalTimePlayed, statsMenu_totalBlocksCleared, statsMenu_planeswalkerPoints, statsMenu_eloScore, statsMenu_timeLasted, statsMenu_blocksCleared);

		leaderBoardMenu->subtitleCaption->setText(title);
	}


	long long currentTime = System::currentHighResTimer();
	long long startTime = updateStatsTime;
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (updateStatsMenu || ticksPassed > 200)
	{
		updateStatsMenu = false;
		updateStatsTime = currentTime;

		yourStatsMenu->clear();
		leaderBoardMenu->clear();

		populateUserStatsForSpecificGameAndDifficultyMenu(yourStatsMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName);

		string title = populateLeaderBoardOrHighScoreBoardMenu(leaderBoardMenu, statsMenu_gameSequenceOrTypeUUID, statsMenu_difficultyName, statsMenu_objectiveName,
			statsMenu_totalTimePlayed, statsMenu_totalBlocksCleared, statsMenu_planeswalkerPoints, statsMenu_eloScore, statsMenu_timeLasted, statsMenu_blocksCleared);

		leaderBoardMenu->subtitleCaption->setText(title);

		yourStatsMenu->setAllCaptionsToFullAlpha();
		leaderBoardMenu->setAllCaptionsToFullAlpha();
	}



	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();



	if (loadRoomConfigMenuShowing)
	{
		loadRoomConfigMenuUpdate();
	}
	else
	if (saveRoomConfigMenuShowing)
	{
		saveRoomConfigMenuUpdate();
	}
	else
	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
	if (selectGameSequenceMenuShowing)
	{
		selectGameSequenceMenuUpdate();
	}
	else
	if (selectSingleGameTypeMenuShowing)
	{
		selectSingleGameTypeMenuUpdate();
	}
	else
	if (gameSequenceOptionsMenuShowing)
	{
		gameSequenceOptionsMenuUpdate();
	}
	else
	if (difficultyMenuShowing)
	{
		difficultyMenuUpdate();
	}
	else
	if (gameObjectiveMenuShowing)
	{
		gameObjectiveMenuUpdate();
	}
	else
	if (roomOptionsMenuShowing)
	{
		roomOptionsMenuUpdate();
	}
	else
	{
		if (getControlsManager()->miniGame_UP_Pressed())
		{
			gameSetupMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			gameSetupMenu->down();
		}

		bool left = getControlsManager()->miniGame_LEFT_Pressed();
		bool right = getControlsManager()->miniGame_RIGHT_Pressed();

		if (left || right)
		{
			if (gameSetupMenu->isSelectedID("Difficulty"))
			{
				updateStatsMenu = true;

				GameType gt;
				if (left)
				{
					selectedDifficultyIndex--;
					if (selectedDifficultyIndex < 0)selectedDifficultyIndex = (int)gt.difficultyTypes->size() - 1;
				}
				if (right)
				{
					selectedDifficultyIndex++;
					if (selectedDifficultyIndex >= gt.difficultyTypes->size())selectedDifficultyIndex = 0;
				}

				sp<DifficultyType>d = gt.difficultyTypes->at(selectedDifficultyIndex);
				string difficultyName = d->name;
				currentRoom->room_DifficultyName = difficultyName;
				if (getPlayer1Game()->currentGameSequence != nullptr)
					getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;

			}

		}

		bool leaveMenu = false;


		bool confirm = false;

		//assign controller to p1 if start or b pressed
		for (int i = 0; i < getControlsManager()->gameControllers->size(); i++)
		{
			sp<GameController>g = getControlsManager()->gameControllers->at(i);
			if (g->b_Pressed())
			{
				confirm = true;
				getPlayer1()->gameController = g;
				getPlayer1()->rotateCWPressed();//cancel this
			}
			if (g->start_Pressed())
			{
				confirm = true;
				getPlayer1()->gameController = g;
				getPlayer1()->pausePressed();//cancel this so it doesn't pause immediately
			}
		}

		//check enter and space
		if (getControlsManager()->miniGame_CONFIRM_Pressed())confirm = true;//, clicked, mx, my


		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();

		if(confirm || clicked || left || right)
		{
			if (gameSetupMenu->isSelectedID("Objective", clicked, mx, my))
			{

				updateStatsMenu = true;

				if (confirm || clicked) gameObjectiveMenuShowing = true;
				else
				{
					currentRoom->endlessMode = !currentRoom->endlessMode;
					//if (left)
					//{
					//	selectedObjectiveIndex--;
					//	if (selectedObjectiveIndex < 0)selectedObjectiveIndex = (int)GameObjective::LAST - 1;
					//}
					//if (right)
					//{
					//	selectedObjectiveIndex++;
					//	if (selectedObjectiveIndex >= (int)GameObjective::LAST)selectedObjectiveIndex = 0;
					//}
					//if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
					//{
					//	if (currentRoom != nullptr)currentRoom->endlessMode = false;
					//}
					//if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
					//{
					//	if (currentRoom != nullptr)currentRoom->endlessMode = true;
					//}
				}
			}
		}

		if (confirm || clicked)
		{

			if (gameSetupMenu->isSelectedID("Select Game", clicked, mx, my))
			{
				selectGameSequenceOrSingleGameTypeMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Difficulty", clicked, mx, my))
			{
				difficultyMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Options", clicked, mx, my))
			{
				roomOptionsMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Save", clicked, mx, my))
			{
				saveRoomConfigMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Load", clicked, mx, my))
			{
				loadRoomConfigMenuShowing = true;
			}

			if (gameSetupMenu->isSelectedID("Start Game", clicked, mx, my))
			{

				if(getPlayer1Game()->currentGameSequence == nullptr)getPlayer1Game()->currentGameSequence = currentRoom->gameSequence;

				GameType gt;
				sp<DifficultyType>d = gt.difficultyTypes->at(selectedDifficultyIndex);
				string difficultyName = d->name;
				currentRoom->room_DifficultyName = difficultyName;
				if (getPlayer1Game()->currentGameSequence != nullptr)
					getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;



				sentStats = false;

				//if game type selected, else gray out
				leaveMenu = true;
			}

			if (gameSetupMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;

				leaveMenu = true;
			}
		}


//		if (confirm || clicked)
//		{
//
//			if (
//				leaderBoardMenu->isSelectedID(leaderBoardMenu->getSelectedMenuItem()->id, clicked, mx, my)
//				)
//			{
//
//				updateStatsMenu = true;
//
//				if (statsMenu_totalTimePlayed)
//				{
//					statsMenu_totalTimePlayed = false; 
//					statsMenu_totalBlocksCleared = true;
//				}
//				else
//				if (statsMenu_totalBlocksCleared)
//				{
//					statsMenu_totalBlocksCleared = false;
//					statsMenu_planeswalkerPoints = true;
//				}
//				else
//				if (statsMenu_planeswalkerPoints)
//				{
//					statsMenu_planeswalkerPoints = false;
//					statsMenu_eloScore = true;
//				}
//				else
//				if (statsMenu_eloScore)
//				{
//					statsMenu_eloScore = false;
//					statsMenu_timeLasted = true;
//				}
//				else
//				if (statsMenu_timeLasted)
//				{
//					statsMenu_timeLasted = false;
//					statsMenu_blocksCleared = true;
//				}
//				else
//				if (statsMenu_blocksCleared)
//				{
//					statsMenu_blocksCleared = false;
//					statsMenu_totalTimePlayed = true;
//				}
//
//			}
//		}

		if (getControlsManager()->miniGame_CANCEL_Pressed())
		{

			startScreenMenuShowing = true;

			leaveMenu = true;
		}

		if (leaveMenu)
		{
			gameSetupMenuShowing = false;

			if(errorLabel!=nullptr)
			{
				//delete errorLabel;
				errorLabel = nullptr;
			}

			if (gameSetupMenu != nullptr)
			{
				gameSetupMenuCursorPosition = gameSetupMenu->cursorPosition;
				//delete gameSetupMenu;
				gameSetupMenu = nullptr;
			}

			if (yourStatsMenu != nullptr)
			{
				//delete yourStatsMenu;
				yourStatsMenu = nullptr;
			}

			if (leaderBoardMenu != nullptr)
			{
				//delete leaderBoardMenu;
				leaderBoardMenu = nullptr;
			}
		}
	}
}

//=========================================================================================================================
void OKGame::gameSetupMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = keyboardTexture;

	if (gameSetupMenu == nullptr)return;

	if (t != nullptr)
	{
		gameSetupMenu->setGraphic(t, getWidth() / 8 * 6, getHeight() / 10, getHeight() / 3);
	}

	{

		int startHeight = 0;
		
		int leftX = 0;
		int rightX = 0;


		int bottomOfCaptions = 0;
		gameSetupMenu->render(0, (getWidth()-(gameSetupMenu->lastWidth + 50 + yourStatsMenu->lastWidth + 50 + leaderBoardMenu->lastWidth)) / 2 , getHeight(), true, &startHeight,&bottomOfCaptions, false, &leftX, &rightX);
		if (errorLabel != nullptr)
		{
			errorLabel->screenY = getHeight() - 50; //bottomOfCaptions + 24;
			errorLabel->update();
			errorLabel->render();
		}

		yourStatsMenu->render(startHeight, rightX + 50, getHeight(), false, nullptr, nullptr, false, nullptr, &rightX);
		leaderBoardMenu->render(startHeight, rightX + 50, getHeight(), false, nullptr, nullptr, false);

	}

	if(selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Select Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Select Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Select Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (gameSequenceOptionsMenuShowing && gameSequenceOptionsMenu != nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Select Game");
		gameSequenceOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (difficultyMenuShowing && difficultyMenu!=nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (saveRoomConfigMenuShowing && saveRoomConfigMenu!=nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Save");
		saveRoomConfigMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (loadRoomConfigMenuShowing && loadRoomConfigMenu!=nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Load");
		loadRoomConfigMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (gameObjectiveMenuShowing && gameObjectiveMenu != nullptr)
	{
		sp<Caption>c = gameSetupMenu->getCaptionByID("Objective");
		gameObjectiveMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (roomOptionsMenuShowing && roomOptionsMenu != nullptr)
	{
		int bottomOfCaptions = 0;

		{
			//sp<Caption>c = gameSetupMenu->getCaptionByID("Options");
			//roomOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, &bottomOfCaptions, true);
			roomOptionsMenu->render(getHeight()/6, 0, getHeight(), true, nullptr, &bottomOfCaptions, true);
		}

		if (descriptionCaption != nullptr)
		{
			descriptionCaption->screenY = getHeight() - 30;// bottomOfCaptions + 24;
			descriptionCaption->update();
			descriptionCaption->render();
		}

		if (sendGarbageToMenuShowing && sendGarbageToMenu != nullptr)
		{
			sp<Caption>c = roomOptionsMenu->getCaptionByID("Send Garbage To");
			sendGarbageToMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
		}
	}
}

//=========================================================================================================================
void OKGame::selectGameSequenceOrSingleGameTypeMenuUpdate()
{//=========================================================================================================================


	//TODO: store default difficulty in GlobalSettings

	if (selectGameSequenceOrSingleGameTypeMenu == nullptr)
	{
		selectGameSequenceOrSingleGameTypeMenu = ms<OKMenu>(this, "");

		if(localMultiplayer || networkMultiplayer)
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Allow Different Game Sequences Or Types");
		}

		if (statsMenuShowing)
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Any Game Type Or Sequence", "Allow Different Game Sequences Or Types");
			selectGameSequenceOrSingleGameTypeMenu->add("Select Game Sequence", "Play Game Sequence");
			selectGameSequenceOrSingleGameTypeMenu->add("Select Single Game Type", "Play Single Game Type");
		}
		else
		{
			selectGameSequenceOrSingleGameTypeMenu->add("Play Game Sequence", "Play Game Sequence");
			selectGameSequenceOrSingleGameTypeMenu->add("Play Single Game Type", "Play Single Game Type");
		}

		selectGameSequenceOrSingleGameTypeMenu->cursorPosition = selectGameSequenceOrSingleGameTypeMenuCursorPosition;
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceOrSingleGameTypeMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Allow Different Game Sequences Or Types", clicked, mx, my))
		{
			if (localMultiplayer || networkMultiplayer)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = true;
			}

			if(statsMenuShowing)
			{
				statsMenu_gameSequenceOrTypeUUID = "OVERALL";
				statsMenu_gameSequenceOrTypeName = "OVERALL";
			}
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Play Game Sequence", clicked, mx, my))
		{
			if (statsMenuShowing == false)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = false;
			}
			selectGameSequenceMenuShowing = true;
		}

		if (selectGameSequenceOrSingleGameTypeMenu->isSelectedID("Play Single Game Type", clicked, mx, my))
		{
			if (statsMenuShowing == false)
			{
				currentRoom->multiplayer_AllowDifferentGameSequences = false;
			}
			selectSingleGameTypeMenuShowing = true;
		}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		if(localMultiplayer || networkMultiplayer)
//		{
//			multiplayerOptionsMenuShowing = true;
//		}
//		else
//		{
//			titleMenuShowing = true;
//		}
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectGameSequenceOrSingleGameTypeMenuShowing = false;

		if (selectGameSequenceOrSingleGameTypeMenu != nullptr)
		{
			selectGameSequenceOrSingleGameTypeMenuCursorPosition = selectGameSequenceOrSingleGameTypeMenu->cursorPosition;
			//delete selectGameSequenceOrSingleGameTypeMenu;
			selectGameSequenceOrSingleGameTypeMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}

//=========================================================================================================================
void OKGame::selectGameSequenceOrSingleGameTypeMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = keyboardTexture;

	if (selectGameSequenceOrSingleGameTypeMenu == nullptr)return;

	if (t != nullptr)
	{
		selectGameSequenceOrSingleGameTypeMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	selectGameSequenceOrSingleGameTypeMenu->render(getHeight()/2);
}


//=========================================================================================================================
void OKGame::selectGameSequenceMenuUpdate()
{//=========================================================================================================================

	if (selectGameSequenceMenu == nullptr)
	{
		selectGameSequenceMenu = ms<OKMenu>(this, "");
		selectGameSequenceMenu->center = false;
		selectGameSequenceMenu->outline = false;

		populateGameSequencesMenu(selectGameSequenceMenu);

		selectGameSequenceMenu->cursorPosition = selectGameSequenceMenuCursorPosition;
	}

	if (getControlsManager()->miniGame_UP_Pressed())
	{
		selectGameSequenceMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		selectGameSequenceMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{
		for (int i = 0; i<loadedGameSequences->size(); i++)
		{
			sp<GameSequence>g = loadedGameSequences->at(i);
			if (selectGameSequenceMenu->isSelectedID(g->uuid, clicked, mx, my))
			{
				if(statsMenuShowing)
				{
					statsMenu_gameSequenceOrTypeUUID = g->uuid;
					statsMenu_gameSequenceOrTypeName = g->name;
				}
				else
				{
					currentRoom->gameSequence = g;
					getPlayer1Game()->currentGameSequence = g;

					gameSequenceOptionsMenuShowing = true;
				}
			}
		}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectGameSequenceMenuShowing = false;

		if (selectGameSequenceMenu != nullptr)
		{
			selectGameSequenceMenuCursorPosition = selectGameSequenceMenu->cursorPosition;
			//delete selectGameSequenceMenu;
			selectGameSequenceMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}

//=========================================================================================================================
void OKGame::selectGameSequenceMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = keyboardTexture;

	if (selectGameSequenceMenu == nullptr)return;

	if (t != nullptr)
	{
		selectGameSequenceMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	selectGameSequenceMenu->render(getHeight()/2);
}


//=========================================================================================================================
void OKGame::gameSequenceOptionsMenuUpdate()
{//=========================================================================================================================

	const string RANDOMIZE_SEQUENCE = "Randomize Sequence";
	const string PLAY_THROUGH_SEQUENCE_IN_ORDER = "Play Through Sequence In Order";

	if (gameSequenceOptionsMenu == nullptr)
	{
		gameSequenceOptionsMenu = ms<OKMenu>(this,"");

		gameSequenceOptionsMenu->add(RANDOMIZE_SEQUENCE);
		gameSequenceOptionsMenu->add(PLAY_THROUGH_SEQUENCE_IN_ORDER);

		gameSequenceOptionsMenu->cursorPosition = gameSequenceOptionsMenuCursorPosition;
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		gameSequenceOptionsMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		gameSequenceOptionsMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (gameSequenceOptionsMenu->isSelectedID(RANDOMIZE_SEQUENCE, clicked, mx, my))
		{
			if (currentRoom->gameSequence != nullptr)currentRoom->gameSequence->randomizeSequence = true;
			if (currentRoom != nullptr)currentRoom->singleplayer_RandomizeSequence = true;
		}

		if (gameSequenceOptionsMenu->isSelectedID(PLAY_THROUGH_SEQUENCE_IN_ORDER, clicked, mx, my))
		{
			if (currentRoom->gameSequence != nullptr)currentRoom->gameSequence->randomizeSequence = false;
			if (currentRoom != nullptr)currentRoom->singleplayer_RandomizeSequence = false;
		}

		//gameObjectiveMenuShowing = true;

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		gameSequenceOptionsMenuShowing = false;

		if (gameSequenceOptionsMenu != nullptr)
		{
			gameSequenceOptionsMenuCursorPosition = gameSequenceOptionsMenu->cursorPosition;
			//delete gameSequenceOptionsMenu;
			gameSequenceOptionsMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}

//=========================================================================================================================
void OKGame::gameSequenceOptionsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = keyboardTexture;

	if (gameSequenceOptionsMenu == nullptr)return;

	if (t != nullptr)
	{
		gameSequenceOptionsMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 10);
	}

	gameSequenceOptionsMenu->render();
}


//=========================================================================================================================
/// <summary>
/// Calculates the Wilson Score based on the total votes and upvotes
/// </summary>
/// <param name="up">Number of upvotes</param>
/// <param name="total">Total number of votes</param>
/// <param name="confidence">Confidence used in calculation, default 1.644853 (95%)</param>
double OKGame::wilsonScore(double up, double total, double confidence)
{//=========================================================================================================================
	/** Based on http://www.evanmiller.org/how-not-to-sort-by-average-rating.html **/
	if (total <= 0 || total < up)
		return 0;

	double phat = up / total;
	double z2 = confidence * confidence;

	return (phat + z2 / (2 * total) - confidence * sqrt((phat * (1 - phat) + z2 / (4 * total)) / total)) / (1 + z2 / total);
}

//=========================================================================================================================
sp<vector<sp<pair<sp<GameType>,sp<pair<string,sp<OKColor>>>>>>> OKGame::getSortedGameTypes()
{//=========================================================================================================================

	sp<vector<sp<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>>>> gamesStringColor;

//	for (int i = 0; i<loadedGameTypes->size(); i++)
//	{
//		sp<GameType>g = loadedGameTypes->at(i);
//		if (g->builtInType)
//		{
//			string name = g->name;
//			sp<OKColor>color = OKColor::darkGreen;
//			pair<string, sp<OKColor>> stringColorPair = pair<string, sp<OKColor>>(name,color);
//			pair<sp<GameType>, pair<string, sp<OKColor>>> gameTypeStringColorPairPair = pair<sp<GameType>, pair<string, sp<OKColor>>>(g, stringColorPair);
//			gamesStringColor.add(gameTypeStringColorPairPair);
//		}
//	}
	for (int i = 0; i<loadedGameTypes->size(); i++)
	{
		sp<GameType>g = loadedGameTypes->at(i);
		if (g->downloaded == false)//g->builtInType == false &&
		{
			string name = g->creatorUserName + " - " + g->name;
			sp<OKColor>color = OKColor::purple;
			sp<pair<string, sp<OKColor>>> stringColorPair = ms<pair<string, sp<OKColor>>>(pair<string, sp<OKColor>>(name, color));
			sp<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>> gameTypeStringColorPairPair = ms<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>>(pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>(g, stringColorPair));
			gamesStringColor->push_back(gameTypeStringColorPairPair);
		}
	}

	sp<vector<sp<GameType>>>downloadedGames;
	for (int i = 0; i<loadedGameTypes->size(); i++)
	{
		sp<GameType>g = loadedGameTypes->at(i);
		if (g->downloaded == true)//g->builtInType == false &&
		{
			downloadedGames->push_back(g);
		}
	}

	multimap<double, sp<GameType>> games;
	for (int i = 0; i < downloadedGames->size(); i++)
	{
		sp<GameType>g = downloadedGames->at(i);

		double up = (double)(g->upVotes);
		double total = (double)(g->upVotes + g->downVotes);
		double score = wilsonScore(up, total);

		games.insert(std::pair<double, sp<GameType>>(score, g));
	}

	long long currentSecondsSinceEpoch = (long long)time(nullptr);

	multimap<double, sp<GameType>>::iterator pos;
	for (pos = games.begin(); pos != games.end(); ++pos)
	{
		sp<GameType>g = pos->second;

		long long secondsSinceEpoch = g->dateCreated / 1000;
		long long secondsExisted = currentSecondsSinceEpoch - secondsSinceEpoch;
		int daysExisted = (int)(secondsExisted / 60 / 60 / 24);

		string name = g->creatorUserName + " - " + g->name + " | Score: " + to_string(g->upVotes - g->downVotes) + " Age: " + to_string(daysExisted) + " days";

		sp<OKColor>color = OKColor::darkGray;
		sp<pair<string, sp<OKColor>>> stringColorPair = ms<pair<string, sp<OKColor>>>(pair<string, sp<OKColor>>(name, color));
		sp<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>> gameTypeStringColorPairPair = ms<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>>(pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>(g, stringColorPair));
		gamesStringColor->push_back(gameTypeStringColorPairPair);
	}

	return gamesStringColor;

}

//=========================================================================================================================
sp<vector<sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>>>> OKGame::getSortedGameSequences()
{//=========================================================================================================================

	sp<vector<sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>>>> gamesStringColor;

//	for (int i = 0; i<loadedGameSequences->size(); i++)
//	{
//		sp<GameSequence>g = loadedGameSequences->at(i);
//		if (g->builtInType)
//		{
//			string name = g->name;
//			sp<OKColor>color = OKColor::darkGreen;
//			pair<string, sp<OKColor>> stringColorPair = pair<string, sp<OKColor>>(name, color);
//			pair<sp<GameSequence>, pair<string, sp<OKColor>>> gameSequenceStringColorPairPair = pair<sp<GameSequence>, pair<string, sp<OKColor>>>(g, stringColorPair);
//			gamesStringColor.add(gameSequenceStringColorPairPair);
//		}
//	}
	for (int i = 0; i<loadedGameSequences->size(); i++)
	{
		sp<GameSequence>g = loadedGameSequences->at(i);
		if (g->downloaded == false)//g->builtInType == false &&
		{
			string name = g->creatorUserName + " - " + g->name;
			sp<OKColor>color = OKColor::purple;
			sp<pair<string, sp<OKColor>>> stringColorPair = ms<pair<string, sp<OKColor>>>(pair<string, sp<OKColor>>(name, color));
			sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>> gameSequenceStringColorPairPair = ms<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>>(pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>(g, stringColorPair));
			gamesStringColor->push_back(gameSequenceStringColorPairPair);
		}
	}

	sp<vector<sp<GameSequence>>> downloadedGames;
	for (int i = 0; i<loadedGameSequences->size(); i++)
	{
		sp<GameSequence>g = loadedGameSequences->at(i);
		if (g->downloaded == true)//g->builtInType == false &&
		{
			downloadedGames->push_back(g);
		}
	}

	multimap<double, sp<GameSequence>> games;
	for (int i = 0; i < downloadedGames->size(); i++)
	{
		sp<GameSequence>g = downloadedGames->at(i);

		double up = (double)(g->upVotes);
		double total = (double)(g->upVotes + g->downVotes);
		double score = wilsonScore(up, total);

		games.insert(std::pair<double, sp<GameSequence>>(score, g));
	}

	long long currentSecondsSinceEpoch = (long long)time(nullptr);

	multimap<double, sp<GameSequence>>::iterator pos;
	for (pos = games.begin(); pos != games.end(); ++pos)
	{
		sp<GameSequence>g = pos->second;

		long long secondsSinceEpoch = g->dateCreated / 1000;
		long long secondsExisted = currentSecondsSinceEpoch - secondsSinceEpoch;
		int daysExisted = (int)(secondsExisted / 60 / 60 / 24);

		string name = g->creatorUserName + " - " + g->name + " | Score: " + to_string(g->upVotes - g->downVotes) + " Age: " + to_string(daysExisted) + " days";

		sp<OKColor>color = OKColor::darkGray;
		sp<pair<string, sp<OKColor>>> stringColorPair = ms<pair<string, sp<OKColor>>>(pair<string, sp<OKColor>>(name, color));
		sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>> gameSequenceStringColorPairPair = ms<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>>(pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>(g, stringColorPair));
		gamesStringColor->push_back(gameSequenceStringColorPairPair);
	}

	return gamesStringColor;

}
//=========================================================================================================================
void OKGame::populateGameTypesMenu(sp<OKMenu>menu)
{//=========================================================================================================================


	//need to sort and color
	//make built in games green maybe
	//make usermade by me under those, make blue
	//make downloaded ones have user info, sorted by some voodoo metric of upvotes / timeexisted
	//use smaller font
	//username - game name - upvotes/downvotes

	sp<vector<sp<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>>>> gamesStringColor = getSortedGameTypes();
	for (int i = 0; i < gamesStringColor->size(); i++)
	{
		sp<pair<sp<GameType>, sp<pair<string, sp<OKColor>>>>> gameTypeStringColorPairPair = gamesStringColor->at(i);
		sp<GameType>g = gameTypeStringColorPairPair->first;
		sp<pair<string, sp<OKColor>>> stringColorPair = gameTypeStringColorPairPair->second;
		string name = stringColorPair->first;
		sp<OKColor>color = stringColorPair->second;

		sp<OKMenu::MenuItem> m = menu->add(name, g->uuid);
		m->setColor(color);

	}
	//TODO:maybe show preview of game running really fast ???
}

//=========================================================================================================================
void OKGame::populateGameSequencesMenu(sp<OKMenu>menu)
{//=========================================================================================================================

	sp<vector<sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>>>> gamesStringColor = getSortedGameSequences();
	for (int i = 0; i < gamesStringColor->size(); i++)
	{
		sp<pair<sp<GameSequence>, sp<pair<string, sp<OKColor>>>>> gameSequenceStringColorPairPair = gamesStringColor->at(i);
		sp<GameSequence>g = gameSequenceStringColorPairPair->first;
		sp<pair<string, sp<OKColor>>> stringColorPair = gameSequenceStringColorPairPair->second;
		string name = stringColorPair->first;
		sp<OKColor>color = stringColorPair->second;

		sp<OKMenu::MenuItem> m = menu->add(name, g->uuid);
		m->setColor(color);

	}
}








//=========================================================================================================================

string getNiceTime(long long ms)
{//=========================================================================================================================
	int sec = ms / 1000;
	int min = sec / 60;
	int hrs = min / 60;
	sec = sec % 60;
	min = min % 60;

	string niceTime = "";

	if (hrs>0)
	{
		if (hrs > 0 && hrs < 10)niceTime += "0" + to_string(hrs) + ":";
		if (hrs >= 10)niceTime += "" + to_string(hrs) + ":";

		if (min >= 0 && min < 10)niceTime += "0" + to_string(min) + ":";
		if (min >= 10)niceTime += "" + to_string(min) + ":";

		if (sec >= 0 && sec < 10)niceTime += "0" + to_string(sec) + "";
		if (sec >= 10)niceTime += "" + to_string(sec) + "";
	}
	else
	{

		if (min >= 0 && min < 10)niceTime += "0" + to_string(min) + ":";
		if (min >= 10)niceTime += "" + to_string(min) + ":";

		if (sec >= 0 && sec < 10)niceTime += "0" + to_string(sec) + "";
		if (sec >= 10)niceTime += "" + to_string(sec) + "";

	}

//	if (hrs > 0 && hrs < 10)niceTime += "0"+to_string(hrs) + "h ";
//	if (hrs > 0 && hrs >= 10)niceTime += to_string(hrs) + "h ";
//
//	if (min > 0 && min < 10)niceTime += "0" + to_string(min) + "m ";
//	if (min > 0 && min >= 10)niceTime += to_string(min) + "m ";
//
//	if (sec > 0 && sec < 10)niceTime += "0" + to_string(sec) + "s";
//	if (sec > 0 && sec >= 10)niceTime += to_string(sec) + "s";
	return niceTime;
}


#include <time.h>

//=========================================================================================================================

string getDateFromEpochTime(long long ms)
{//=========================================================================================================================
	std::time_t seconds = ms / 1000;
	tm * time = localtime(&seconds);
	string s = std::asctime(time);
	std::string::size_type i = s.find("\n");
	if (i != std::string::npos)
		s.erase(i, s.length());
	return s;
}

//=========================================================================================================================
//gameTypeOrSequenceString or difficulty string can be "OVERALL"
sp<OKGameUserStatsForSpecificGameAndDifficulty> OKGame::getUserStatsForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString)
{//=========================================================================================================================
	sp<OKGameUserStatsForSpecificGameAndDifficulty>stats = nullptr;
	for (int i = 0; i < userStatsPerGameAndDifficulty->size(); i++)
	{
		sp<OKGameUserStatsForSpecificGameAndDifficulty>s = userStatsPerGameAndDifficulty->at(i);
		if (s->gameTypeUUID == gameTypeOrSequenceUUID || s->gameSequenceUUID == gameTypeOrSequenceUUID || s->isGameTypeOrSequence == gameTypeOrSequenceUUID)
		{
			if (s->difficultyName == difficultyString)
			{
				if (s->objectiveString == objectiveString)
				{
					stats = s;
					break;
				}
			}
		}
	}
	return stats;

}


//=========================================================================================================================
//gameTypeOrSequenceString or difficulty string can be "OVERALL"
void OKGame::populateUserStatsForSpecificGameAndDifficultyMenu(sp<OKMenu>menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString)
{//=========================================================================================================================


	sp<OKGameUserStatsForSpecificGameAndDifficulty>stats = getUserStatsForGame(gameTypeOrSequenceUUID, difficultyString, objectiveString);

	bool deleteStats = false;
	if (stats == nullptr)
	{
		stats = ms<OKGameUserStatsForSpecificGameAndDifficulty>();
		deleteStats = true;
	}

	string gameName = "";
	if (gameTypeOrSequenceUUID == "OVERALL")
	{
		gameName = "Game: OVERALL";
	}
	else
	{
		sp<GameType> gt = getGameTypeByUUID(gameTypeOrSequenceUUID);
		sp<GameSequence>gs = getGameSequenceByUUID(gameTypeOrSequenceUUID);
		if (gt != nullptr)gameName = "Game Type: " + gt->name;
		if (gs != nullptr)gameName = "Game Sequence: " + gs->name;
	}

	string difficultyName = "";
	if (difficultyString == "OVERALL")
	{
		difficultyName = "Difficulty: OVERALL";
	}
	else
	{
		difficultyName = "Difficulty: " + difficultyString;
	}

	if (getServerConnection()->getConnectedToServer_S())
	{
		if (getServerConnection()->getAuthorizedOnServer_S())
		{

			//menu->add("Your Stats");
			menu->add(gameName);
			menu->add(difficultyName);
			menu->add("Objective: " + objectiveString);
			menu->addInfo(" ");

			if (objectiveString == "Play To Credits")
			{
				menu->add("Fastest Cleared Time: " + getNiceTime(stats->fastestClearedLength));
				menu->add("Most Blocks Cleared: " + to_string(stats->mostBlocksCleared));
			}
			else
			{
				menu->add("Most Blocks Cleared: " + to_string(stats->mostBlocksCleared));
				menu->add("Longest Game Length: " + getNiceTime(stats->longestGameLength));
			}

			menu->add("Average Game Length: " + getNiceTime(stats->averageGameLength));

			menu->add("Biggest Combo: " + to_string(stats->biggestCombo));

			menu->add("Planeswalker Score: " + to_string(stats->planesWalkerPoints));
			menu->add("Elo Score: " + to_string(stats->eloScore));

			menu->add("Total Games Played: " + to_string(stats->totalGamesPlayed));
			menu->add("Single Player Games Played: " + to_string(stats->singlePlayerGamesPlayed));
			menu->add("Single Player Games Completed: " + to_string(stats->singlePlayerGamesCompleted));
			menu->add("Single Player Games Failed: " + to_string(stats->singlePlayerGamesLost));
			menu->add("Local Multiplayer Games Played: " + to_string(stats->localMultiplayerGamesPlayed));
			menu->add("Tournament Games Played: " + to_string(stats->tournamentGamesPlayed));
			menu->add("Tournament Games Won: " + to_string(stats->tournamentGamesWon));
			menu->add("Tournament Games Lost: " + to_string(stats->tournamentGamesLost));

			menu->add("Total Time Played: " + getNiceTime(stats->totalTimePlayed));
			menu->add("First Time Played: " + getDateFromEpochTime(stats->firstTimePlayed));
			menu->add("Last Time Played: " + getDateFromEpochTime(stats->lastTimePlayed));
			
			menu->add("Total Blocks Made: " + to_string(stats->totalBlocksMade));
			menu->add("Total Blocks Cleared: " + to_string(stats->totalBlocksCleared));
			menu->add("Total Pieces Made: " + to_string(stats->totalPiecesMade));
			menu->add("Total Pieces Placed: " + to_string(stats->totalPiecesPlaced));
			menu->add("Total Combos Made: " + to_string(stats->totalCombosMade));
			


			if (deleteStats)
			{
				//delete stats;
				stats = nullptr;
			}
		}
		else
		{
			menu->add(gameName);
			menu->add(difficultyName);
			menu->add("Objective: " + objectiveString);
			menu->addInfo(" ");
			menu->add("Create an account to track your stats!");
		}
	}
}

/*

static sp<vector<sp<OKGameUserStatsForSpecificGameAndDifficulty>>>userStatsPerGameAndDifficulty;
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByTotalTimePlayed;
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByTotalBlocksCleared;
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByPlaneswalkerPoints;
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topPlayersByEloScore;

//TODO: could do highest level reached
//TODO: could do biggest combo
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topGamesByTimeLasted;
static sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>topGamesByBlocksCleared;
*/


//=========================================================================================================================
sp<OKGameLeaderBoardAndHighScoreBoard> OKGame::getLeaderboardOrHighScoreBoardForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
	bool totalTimePlayed,
	bool totalBlocksCleared,
	bool planeswalkerPoints,
	bool eloScore,
	bool timeLasted,
	bool blocksCleared)
{//=========================================================================================================================

	sp<OKGameLeaderBoardAndHighScoreBoard>stats = nullptr;

	sp<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topPlayersByTotalTimePlayed);

	if (totalTimePlayed)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topPlayersByTotalTimePlayed);
	if (totalBlocksCleared)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topPlayersByTotalBlocksCleared);
	if (planeswalkerPoints)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topPlayersByPlaneswalkerPoints);
	if (eloScore)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topPlayersByEloScore);
	if (timeLasted)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topGamesByTimeLasted);
	if (blocksCleared)board = ms<vector<sp<OKGameLeaderBoardAndHighScoreBoard>>>(topGamesByBlocksCleared);

	for (int i = 0; i<board->size(); i++)
	{
		sp<OKGameLeaderBoardAndHighScoreBoard>s = board->at(i);
		if (s->gameTypeUUID == gameTypeOrSequenceUUID || s->gameSequenceUUID == gameTypeOrSequenceUUID || s->isGameTypeOrSequence == gameTypeOrSequenceUUID)
		{
			if (s->difficultyName == difficultyString)
			{
				if (s->objectiveString == objectiveString)
				{
					stats = s;
					break;
				}
			}
		}
	}

	return stats;
}

//=========================================================================================================================
string OKGame::populateLeaderBoardOrHighScoreBoardMenu(sp<OKMenu>menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
	bool totalTimePlayed,
	bool totalBlocksCleared,
	bool planeswalkerPoints,
	bool eloScore,
	bool timeLasted,
	bool blocksCleared
)
{//=========================================================================================================================

	sp<OKGameLeaderBoardAndHighScoreBoard>stats = getLeaderboardOrHighScoreBoardForGame(gameTypeOrSequenceUUID, difficultyString, objectiveString,
		totalTimePlayed,
		totalBlocksCleared,
		planeswalkerPoints,
		eloScore,
		timeLasted,
		blocksCleared);


	bool deleteStats = false;
	if (stats == nullptr)
	{
		stats = ms<OKGameLeaderBoardAndHighScoreBoard>();
		deleteStats = true;
	}

	string gameName = "";
	if (gameTypeOrSequenceUUID == "OVERALL")
	{
		gameName = "Game: OVERALL";
	}
	else
	{
		sp<GameType> gt = getGameTypeByUUID(gameTypeOrSequenceUUID);
		sp<GameSequence>gs = getGameSequenceByUUID(gameTypeOrSequenceUUID);
		if (gt != nullptr)gameName = "Game Type: "+gt->name;
		if (gs != nullptr)gameName = "Game Sequence: "+gs->name;
	}

	string difficultyName = "";
	if (difficultyString == "OVERALL")
	{
		difficultyName = "Difficulty: OVERALL";
	}
	else
	{
		difficultyName = "Difficulty: "+difficultyString;
	}

	/*

		class OKGameLeaderBoardAndHighScoreBoardEntry
	{
	public:
		string userName = "";
		long userID = -1;

		//elo score should handle most of this
		int totalGamesPlayed = 0;
		int singlePlayerGamesPlayed = 0;
		int tournamentGamesPlayed = 0;
		int localMultiplayerGamesPlayed = 0;
		int tournamentGamesWon = 0;
		int tournamentGamesLost = 0;
		int singlePlayerGamesCompleted = 0;
		int singlePlayerGamesLost = 0;
		int singlePlayerHighestLevelReached = 0;
		long totalTimePlayed = 0;
		long longestGameLength = 0;
		long firstTimePlayed = 0;
		long lastTimePlayed = 0;
		long timeRecordSet = 0;
		double eloScore = 0;
		long planesWalkerPoints = 0;
		long totalBlocksCleared = 0;
		int biggestCombo = 0;
		int mostBlocksClearedInOneGame = 0;
		string statsUUID = "";
	};

	sp<vector<sp<OKGameLeaderBoardAndHighScoreBoardEntry>>>entries;
	*/

	string titleName = "";


	//menu->add(titleName);
	menu->add(gameName);
	menu->add(difficultyName);
	menu->add("Objective: "+objectiveString);
	menu->addInfo(" ");

	for (int i = 0; i < stats->entries->size(); i++)
	{

		sp<OKGameLeaderBoardAndHighScoreBoard::OKGameLeaderBoardAndHighScoreBoardEntry> e = stats->entries->at(i);

		if (e->userName == "") { continue; }

		string s = to_string(i)+") " + e->userName + " | ";

		if (totalTimePlayed)
		{
			menu->add(s+"Total Time Played: " + getNiceTime(e->totalTimePlayed));
			titleName = "Top Players: Total Time Played";
		}
		if (totalBlocksCleared)
		{
			menu->add(s + "Total Blocks Cleared: " + to_string(e->totalBlocksCleared));
			titleName = "Top Players: Total Blocks Cleared";
		}

		if (planeswalkerPoints)
		{
			menu->add(s + "Planeswalker Score: " + to_string(e->planesWalkerPoints));
			titleName = "Top Players: Planeswalker Points";
		}

		if (eloScore)
		{
			menu->add(s + "Elo Score: " + to_string(e->eloScore));
			titleName = "Top Players: Elo Score";
		}

		if (timeLasted)
		{
			if (objectiveString == "Play To Credits")
			{
				menu->add(s + "Fastest Cleared Time: " + getNiceTime(e->fastestClearedLength));
				titleName = "Top Games: Fastest Cleared Time";
			}
			else
			{
				menu->add(s + "Longest Time Lasted: " + getNiceTime(e->longestGameLength));
				titleName = "Top Games: Longest Time Lasted";
			}
		}

		if (blocksCleared)
		{
			menu->add(s + "Most Blocks Cleared: " + to_string(e->mostBlocksClearedInOneGame));
			titleName = "Top Games: Most Blocks Cleared";
		}

//		menu->add("Total Games Played: " + to_string(e->totalGamesPlayed));
//		menu->add("Single Player Games Played: " + to_string(e->singlePlayerGamesPlayed));
//		menu->add("Single Player Games Completed: " + to_string(e->singlePlayerGamesCompleted));
//		menu->add("Single Player Games Failed: " + to_string(e->singlePlayerGamesLost));
//		menu->add("Local Multiplayer Games Played: " + to_string(e->localMultiplayerGamesPlayed));
//		menu->add("Tournament Games Played: " + to_string(e->tournamentGamesPlayed));
//		menu->add("Tournament Games Won: " + to_string(e->tournamentGamesWon));
//		menu->add("Tournament Games Lost: " + to_string(e->tournamentGamesLost));
//		menu->add("First Time Played: " + getDateFromEpochTime(e->firstTimePlayed));
//		menu->add("Time Record Set: " + getDateFromEpochTime(e->timeRecordSet));
//		menu->add("Biggest Combo: " + to_string(e->biggestCombo));


		menu->addInfo(" ");
	}

	if (deleteStats)
	{
		//delete stats;
		stats = nullptr;
	}

	return titleName;

}


//=========================================================================================================================
void OKGame::selectSingleGameTypeMenuUpdate()
{//=========================================================================================================================

	if (selectSingleGameTypeMenu == nullptr)
	{
		selectSingleGameTypeMenu = ms<OKMenu>(this, "");
		selectSingleGameTypeMenu->center = false;
		selectSingleGameTypeMenu->setFontSize(14);
		selectSingleGameTypeMenu->outline = false;

		populateGameTypesMenu(selectSingleGameTypeMenu);


		selectSingleGameTypeMenu->cursorPosition = selectSingleGameTypeMenuCursorPosition;
	}

	//make key repeat work
	if (getControlsManager()->MINIGAME_UP_HELD)
	{
		long long currentTime = System::currentHighResTimer();

		if(upRepeatedStarted==false)
		{
			selectSingleGameTypeMenu->up();
			upRepeatedStarted = true;
			upLastTime = currentTime;
		}
		else
		{

			long long startTime = upLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (upRepeating == false)
			{
				if (ticksPassed > 300)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
					upRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					upLastTime = currentTime;
					selectSingleGameTypeMenu->up();
				}
			}
		}
	}
	else
	{
		upRepeating = false;
		upRepeatedStarted = false;
	}

	if (getControlsManager()->MINIGAME_DOWN_HELD)
	{
		long long currentTime = System::currentHighResTimer();

		if (downRepeatedStarted == false)
		{
			selectSingleGameTypeMenu->down();
			downRepeatedStarted = true;
			downLastTime = currentTime;
		}
		else
		{
			long long startTime = downLastTime;
			int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

			if (downRepeating == false)
			{
				if (ticksPassed > 300)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
					downRepeating = true;
				}
			}
			else
			{
				if (ticksPassed > 30)
				{
					downLastTime = currentTime;
					selectSingleGameTypeMenu->down();
				}
			}
		}
	}
	else
	{
		downRepeating = false;
		downRepeatedStarted = false;
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		for (int i = 0; i<loadedGameTypes->size(); i++)
		{
			sp<GameType>g = loadedGameTypes->at(i);
			if (selectSingleGameTypeMenu->isSelectedID(g->uuid, clicked, mx, my))
			{

				if(statsMenuShowing)
				{
					statsMenu_gameSequenceOrTypeUUID = g->uuid;
					statsMenu_gameSequenceOrTypeName = g->name;
				}
				else
				{

					currentRoom->gameSequence = ms<GameSequence>();
					currentRoom->gameSequence->gameTypes->push_back(g);
					currentRoom->gameSequence->name = g->name;

					getPlayer1Game()->currentGameSequence = currentRoom->gameSequence;
				}
			}
		}

		//gameObjectiveMenuShowing = true;


		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		selectSingleGameTypeMenuShowing = false;

		if (selectSingleGameTypeMenu != nullptr)
		{
			selectSingleGameTypeMenuCursorPosition = selectSingleGameTypeMenu->cursorPosition;
			//delete selectSingleGameTypeMenu;
			selectSingleGameTypeMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}






//=========================================================================================================================
void OKGame::difficultyMenuUpdate()
{//=========================================================================================================================

	GameType gt;

	if (difficultyMenu == nullptr)
	{
		difficultyMenu = ms<OKMenu>(this, "");
		difficultyMenu->center = false;

		if (localMultiplayer || networkMultiplayer)
		{
			difficultyMenu->add("Allow Different Difficulties");
		}

		if(statsMenuShowing)
		{
			difficultyMenu->add("All Difficulties", "Allow Different Difficulties");
		}

		for (int i = 0; i<gt.difficultyTypes->size(); i++)
		{
			difficultyMenu->add(gt.difficultyTypes->at(i)->name);
		}

		difficultyMenu->cursorPosition = difficultyMenuCursorPosition;
	}


	if (getControlsManager()->miniGame_UP_Pressed())
	{
		difficultyMenu->up();
	}

	if (getControlsManager()->miniGame_DOWN_Pressed())
	{
		difficultyMenu->down();
	}

	bool leaveMenu = false;

	bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
	bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
	int mx = getControlsManager()->getMouseX();
	int my = getControlsManager()->getMouseY();
	if (confirm || clicked)
	{

		if (difficultyMenu->isSelectedID("Allow Different Difficulties", clicked, mx, my))
		{
			if (localMultiplayer || networkMultiplayer)
			{
				currentRoom->multiplayer_AllowDifferentDifficulties = true;
			}

			if(statsMenuShowing)
			{
				statsMenu_difficultyName = "OVERALL";
			}
		}

		for (int i = 0; i<gt.difficultyTypes->size(); i++)
		{

			string difficultyName = gt.difficultyTypes->at(i)->name;
			if (difficultyMenu->isSelectedID(difficultyName, clicked, mx, my))
			{

				if (statsMenuShowing == false)
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = false;
					currentRoom->room_DifficultyName = difficultyName;

					if (getPlayer1Game()->currentGameSequence != nullptr)
						getPlayer1Game()->currentGameSequence->currentDifficultyName = currentRoom->room_DifficultyName;
				}
				else
				{
					statsMenu_difficultyName = difficultyName;
				}

			}
		}

//		if (localMultiplayer)
//		{
//			localMultiplayerPlayerJoinMenuShowing = true;
//		}
//		else
//			if (networkMultiplayer)
//			{
//				networkMultiplayerPlayerJoinMenuShowing = true;
//			}
//			else
//			{
//				//start single player game
//			}

		leaveMenu = true;
	}

//	if (getControlsManager()->miniGame_CANCEL_Pressed())
//	{
//		if (localMultiplayer || networkMultiplayer)
//		{
//			multiplayerOptionsMenuShowing = true;
//		}
//		else
//		{
//			selectGameSequenceOrSingleGameTypeMenuShowing = true;
//		}
//		leaveMenu = true;
//	}

	if (leaveMenu)
	{
		difficultyMenuShowing = false;

		if (difficultyMenu != nullptr)
		{
			difficultyMenuCursorPosition = difficultyMenu->cursorPosition;
			//delete difficultyMenu;
			difficultyMenu = nullptr;
		}
		updateStatsMenu = true;
	}

}


//=========================================================================================================================
void OKGame::multiplayerOptionsMenuUpdate()
{//=========================================================================================================================

	//const string ALLOW_DIFFERENT_GAME_SEQUENCES_OR_TYPES = "Game Sequence: Allow Different Game Sequences Or Types";
	//const string ALLOW_DIFFERENT_DIFFICULTIES = "Difficulty: Allow Different Difficulties";
	//const string GAME_ENDS_WHEN_ALL_OPPONENTS_LOSE = "Game Ends When All Opponents Lose";
	//const string GAME_ENDS_WHEN_SOMEONE_COMPLETES_CREDITS_LEVEL = "Game Ends When Someone Completes Credits Level";
	//const string DISABLE_VS_GARBAGE = "Disable Sending VS Garbage";
	//const string CONTINUE = "Continue";

	if (multiplayerOptionsMenu == nullptr)
	{

		if(networkMultiplayer)
		{
			multiplayerOptionsMenu = ms<OKMenu>(this, "Set Network Multiplayer Room Options");
			//multiplayerOptionsMenu->center = false;
		}
		else
		{
			multiplayerOptionsMenu = ms<OKMenu>(this, "Set Local Multiplayer Options");
			//multiplayerOptionsMenu->center = false;
		}

		multiplayerOptionsMenu->add("Continue");
		multiplayerOptionsMenu->addInfo(" ", " ");

		if (networkMultiplayer)
		{
			multiplayerOptionsMenu->add("Visibility: Public", "Public Or Private");
			multiplayerOptionsMenu->add("Score Mode: Free Play", "Free Play Or Tournament");
			multiplayerOptionsMenu->add("Max Players: Unlimited", "Max Players");
			multiplayerOptionsMenu->addInfo(" ", " ");
		}

		multiplayerOptionsMenu->add("Game Sequence: Allow Different Game Sequences Or Types", "Select Game");
		multiplayerOptionsMenu->add("Difficulty: Allow Different Difficulties", "Difficulty");
		multiplayerOptionsMenu->add("Objective: ", "Objective");
		multiplayerOptionsMenu->add("More Options...", "Options");
		multiplayerOptionsMenu->addInfo(" "," ");

		multiplayerOptionsMenu->add("Save Config...", "Save");
		multiplayerOptionsMenu->add("Load Config...", "Load");
		multiplayerOptionsMenu->addInfo(" ", " ");
		if(networkMultiplayer)multiplayerOptionsMenu->add("Back To Network Multiplayer Lobby");
		else multiplayerOptionsMenu->add("Back To Title Screen");


		multiplayerOptionsMenu->cursorPosition = multiplayerOptionsMenuCursorPosition;
	}

	if(currentRoom==nullptr)
	{
		currentRoom = ms<Room>();
	}

	if(currentRoom->gameSequence == nullptr)
	{
		currentRoom->gameSequence = ms<GameSequence>();
		currentRoom->gameSequence->gameTypes->push_back(ms<GameType>());
	}

	if(currentRoom->multiplayer_AllowDifferentGameSequences)
	{
		multiplayerOptionsMenu->getMenuItemByID("Select Game")->setText("Game Sequence: Allow Different Game Sequences Or Types");
	}
	else
	if (currentRoom->gameSequence != nullptr)
	{
		{
			sp<OKMenu::MenuItem> c = multiplayerOptionsMenu->getMenuItemByID("Select Game");
			if (c != nullptr)
			{
				if (currentRoom->gameSequence->gameTypes->size() > 1)c->setText("Game Sequence: " + currentRoom->gameSequence->name);
				if (currentRoom->gameSequence->gameTypes->size() == 1)c->setText("Game Type: " + currentRoom->gameSequence->name);
			}
		}
	}

	if (currentRoom->multiplayer_AllowDifferentDifficulties)
	{
		multiplayerOptionsMenu->getMenuItemByID("Difficulty")->setText("Difficulty: Allow Different Difficulties");
	}
	else
	if (currentRoom->room_DifficultyName != "")
	{

		GameType gt;
		for (int i = 0; i < gt.difficultyTypes->size(); i++)
		{
			string difficultyName = gt.difficultyTypes->at(i)->name;
			if (currentRoom->room_DifficultyName == difficultyName)selectedDifficultyIndex = i + 1;
		}

		sp<DifficultyType>d = gt.difficultyTypes->at(selectedDifficultyIndex - 1);
		string difficultyName = d->name;
		currentRoom->room_DifficultyName = difficultyName;
		if (getPlayer1Game()->currentGameSequence != nullptr)
			getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;

		multiplayerOptionsMenu->getMenuItemByID("Difficulty")->setText("Difficulty: " + difficultyName);
	}

	{
		string objectiveString = "";

		if (currentRoom->endlessMode)
		{
			objectiveString = "Play As Long As You Can (Endless Mode)";
		}
		else
		{
			objectiveString = "Play To Credits Level";
		}
		multiplayerOptionsMenu->getMenuItemByID("Objective")->setText("Objective: " + objectiveString);
	}

	if (networkMultiplayer)
	{
		if (currentRoom->multiplayer_PrivateRoom)multiplayerOptionsMenu->getMenuItemByID("Public Or Private")->setText("Visibility: Private (Friends Only)");
		else multiplayerOptionsMenu->getMenuItemByID("Public Or Private")->setText("Visibility: Public");

		if (currentRoom->multiplayer_TournamentRoom)multiplayerOptionsMenu->getMenuItemByID("Free Play Or Tournament")->setText("Score Mode: Tournament (Counts Towards Ranking)");
		else multiplayerOptionsMenu->getMenuItemByID("Free Play Or Tournament")->setText("Score Mode: Free Play");

		if (currentRoom->multiplayer_MaxPlayers < 2)multiplayerOptionsMenu->getMenuItemByID("Max Players")->setText("Max Players: Unlimited");
		else multiplayerOptionsMenu->getMenuItemByID("Max Players")->setText("Max Players: " + to_string(currentRoom->multiplayer_MaxPlayers));
	}




	if (selectGameSequenceOrSingleGameTypeMenuShowing)
	{
		selectGameSequenceOrSingleGameTypeMenuUpdate();
	}
	else
	if (selectGameSequenceMenuShowing)
	{
		selectGameSequenceMenuUpdate();
	}
	else
	if (selectSingleGameTypeMenuShowing)
	{
		selectSingleGameTypeMenuUpdate();
	}
	else
	if (gameSequenceOptionsMenuShowing)
	{
		gameSequenceOptionsMenuUpdate();
	}
	else
	if (difficultyMenuShowing)
	{
		difficultyMenuUpdate();
	}
	else
	if (gameObjectiveMenuShowing)
	{
		gameObjectiveMenuUpdate();
	}
	else
	if (roomOptionsMenuShowing)
	{
		roomOptionsMenuUpdate();
	}
	else
	{

		if (getControlsManager()->miniGame_UP_Pressed())
		{
			multiplayerOptionsMenu->up();
		}

		if (getControlsManager()->miniGame_DOWN_Pressed())
		{
			multiplayerOptionsMenu->down();
		}

		bool leaveMenu = false;

		bool left = getControlsManager()->miniGame_LEFT_Pressed();
		bool right = getControlsManager()->miniGame_RIGHT_Pressed();

		if(left || right)
		{

			if (multiplayerOptionsMenu->isSelectedID("Difficulty"))
			{
				GameType gt;
				if (left)
				{
					selectedDifficultyIndex--;
					if (selectedDifficultyIndex < 0)selectedDifficultyIndex = (int)gt.difficultyTypes->size();//-1
				}
				if (right)
				{
					selectedDifficultyIndex++;
					if (selectedDifficultyIndex > gt.difficultyTypes->size())selectedDifficultyIndex = 0;
				}

				if (selectedDifficultyIndex > 0)
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = false;
					sp<DifficultyType>d = gt.difficultyTypes->at(selectedDifficultyIndex - 1);
					string difficultyName = d->name;
					currentRoom->room_DifficultyName = difficultyName;
					if (getPlayer1Game()->currentGameSequence != nullptr)
						getPlayer1Game()->currentGameSequence->currentDifficultyName = difficultyName;
				}
				else
				{
					currentRoom->multiplayer_AllowDifferentDifficulties = true;
				}
			}



		}

		bool confirm = getControlsManager()->miniGame_CONFIRM_Pressed();//, clicked, mx, my
		bool clicked = getControlsManager()->mouse_LEFTBUTTON_Pressed();
		int mx = getControlsManager()->getMouseX();
		int my = getControlsManager()->getMouseY();
		if (confirm || left || right || clicked)
		{



			if (multiplayerOptionsMenu->isSelectedID("Public Or Private", clicked, mx, my))
			{
				currentRoom->multiplayer_PrivateRoom = !currentRoom->multiplayer_PrivateRoom;
			}

			if (multiplayerOptionsMenu->isSelectedID("Free Play Or Tournament", clicked, mx, my))
			{
				currentRoom->multiplayer_TournamentRoom = !currentRoom->multiplayer_TournamentRoom;
			}

			if ((confirm || clicked) && multiplayerOptionsMenu->isSelectedID("Max Players", clicked, mx, my))
			{
				currentRoom->multiplayer_MaxPlayers = 0;
			}

			if (multiplayerOptionsMenu->isSelectedID("Objective", clicked, mx, my))
			{
				if (confirm || clicked) gameObjectiveMenuShowing = true;
				else
				{
					currentRoom->endlessMode = !currentRoom->endlessMode;
					//if (left)
					//{
					//	selectedObjectiveIndex--;
					//	if (selectedObjectiveIndex < 0)selectedObjectiveIndex = (int)GameObjective::LAST - 1;
					//}
					//if (right)
					//{
					//	selectedObjectiveIndex++;
					//	if (selectedObjectiveIndex >= (int)GameObjective::LAST)selectedObjectiveIndex = 0;
					//}
					//if (selectedObjectiveIndex == (int)GameObjective::PLAY_TO_CREDITS_LEVEL)
					//{
					//	if (currentRoom != nullptr)currentRoom->endlessMode = false;
					//}
					//if (selectedObjectiveIndex == (int)GameObjective::ENDLESS)
					//{
					//	if (currentRoom != nullptr)currentRoom->endlessMode = true;
					//}
				}
			}

		}



		if(left)
		{
			if (multiplayerOptionsMenu->isSelectedID("Max Players"))
			{
				long long startTime = timeLastChangedSetting;
				long long currentTime = System::currentHighResTimer();
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

				if (ticksPassed > 15)
				{
					timeLastChangedSetting = currentTime;
					if (currentRoom->multiplayer_MaxPlayers > 0) currentRoom->multiplayer_MaxPlayers--;
					if (currentRoom->multiplayer_MaxPlayers < 2)currentRoom->multiplayer_MaxPlayers = 0;
				}
			}
		}

		if(right)
		{
			if (multiplayerOptionsMenu->isSelectedID("Max Players"))
			{
				long long startTime = timeLastChangedSetting;
				long long currentTime = System::currentHighResTimer();
				int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

				if (ticksPassed > 15)
				{
					timeLastChangedSetting = currentTime;
					currentRoom->multiplayer_MaxPlayers++;
					if (currentRoom->multiplayer_MaxPlayers < 2)currentRoom->multiplayer_MaxPlayers = 2;
					
				}
			}
		}

		if (confirm || clicked)
		{

			if (multiplayerOptionsMenu->isSelectedID("Select Game", clicked, mx, my))
			{
				selectGameSequenceOrSingleGameTypeMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Difficulty", clicked, mx, my))
			{
				difficultyMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Options", clicked, mx, my))
			{
				roomOptionsMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Save", clicked, mx, my))
			{
				saveRoomConfigMenuShowing = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Load", clicked, mx, my))
			{
				loadRoomConfigMenuShowing = true;
			}


			if (multiplayerOptionsMenu->isSelectedID("Continue", clicked, mx, my))
			{

				if (localMultiplayer)
				{
					localMultiplayerPlayerJoinMenuShowing = true;
				}
				else
					if (networkMultiplayer)
					{
						networkMultiplayerPlayerJoinMenuShowing = true;
					}

				leaveMenu = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Back To Title Screen", clicked, mx, my))
			{
				startScreenMenuShowing = true;

				leaveMenu = true;
			}

			if (multiplayerOptionsMenu->isSelectedID("Back To Network Multiplayer Lobby", clicked, mx, my))
			{
				networkMultiplayerLobbyMenuShowing = true;

				leaveMenu = true;
			}
		}

		if (getControlsManager()->miniGame_CANCEL_Pressed())
		{
			if(networkMultiplayer)networkMultiplayerLobbyMenuShowing = true;
			else startScreenMenuShowing = true;

			leaveMenu = true;
		}

		if (leaveMenu)
		{
			multiplayerOptionsMenuShowing = false;

			if (multiplayerOptionsMenu != nullptr)
			{
				multiplayerOptionsMenuCursorPosition = multiplayerOptionsMenu->cursorPosition;
				//delete multiplayerOptionsMenu;
				multiplayerOptionsMenu = nullptr;
			}
		}
	}

}

//=========================================================================================================================
void OKGame::multiplayerOptionsMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> t = onlineTexture;

	if (multiplayerOptionsMenu == nullptr)return;

	if (t != nullptr)
	{
		multiplayerOptionsMenu->setGraphic(t, getWidth() / 3 * 2, getHeight() / 8);
	}

	multiplayerOptionsMenu->render(getHeight() / 2, getWidth() / 2 - 50);

	if (selectGameSequenceOrSingleGameTypeMenuShowing && selectGameSequenceOrSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectGameSequenceOrSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectGameSequenceMenuShowing && selectGameSequenceMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectGameSequenceMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (selectSingleGameTypeMenuShowing && selectSingleGameTypeMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		selectSingleGameTypeMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (gameSequenceOptionsMenuShowing && gameSequenceOptionsMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Select Game");
		gameSequenceOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (difficultyMenuShowing && difficultyMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Difficulty");
		difficultyMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (gameObjectiveMenuShowing && gameObjectiveMenu != nullptr)
	{
		sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Objective");
		gameObjectiveMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
	}

	if (roomOptionsMenuShowing && roomOptionsMenu != nullptr)
	{
		int bottomOfCaptions = 0;

		{
			//sp<Caption>c = multiplayerOptionsMenu->getCaptionByID("Options");
			//roomOptionsMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, &bottomOfCaptions, true);
			roomOptionsMenu->render(getHeight() / 6, 0, getHeight(), true, nullptr, &bottomOfCaptions, true);
		}

		if (descriptionCaption != nullptr)
		{
			descriptionCaption->screenY = getHeight() - 30;// bottomOfCaptions + 24;
			descriptionCaption->update();
			descriptionCaption->render();
		}

		if (sendGarbageToMenuShowing && sendGarbageToMenu != nullptr)
		{
			sp<Caption>c = roomOptionsMenu->getCaptionByID("Send Garbage To");
			sendGarbageToMenu->render(c->screenY + c->getHeight() + 8, c->screenX + c->getWidth() / 2, getHeight(), true, nullptr, nullptr, true);
		}
	}

}




//=========================================================================================================================
void OKGame::localMultiplayerPlayerJoinMenuUpdate()
{//=========================================================================================================================

	if (localMultiplayerPlayerJoinMenu == nullptr)
	{
		localMultiplayerPlayerJoinMenu = ms<OKMenu>(this, "Local Multiplayer Host/Join Menu");
		localMultiplayerPlayerJoinMenu->addInfo("Press the Space key or A on your controller to join");
		localMultiplayerPlayerJoinMenu->addInfo("Press Esc or Select on your controller to return to Title Screen");

		players->clear();
//		while (players->size()>0)
//		{
//			sp<PuzzlePlayer>p = players->at(players->size() - 1);
//			players->erase(->begin()+players->size() - 1);
//			delete p;
//		}
	}

	bool leaveMenu = false;

	//select player, show icon for gamepad or keyboard
	//show mini difficulty menu
	//if press a, ready
	//if both ready, game start

	bool ready = true;
	for (int i = 0; i<players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);
		if (p->confirmed == false)
		{
			ready = false;


			if (p->setGameSequence == false)
			{
				if (currentRoom->multiplayer_AllowDifferentGameSequences)
				{
					playerGameSequenceMiniMenuUpdate(p);
				}
				else
				{
					p->gameLogic->currentGameSequence = currentRoom->gameSequence;
					p->setGameSequence = true;
				}
			}
			else
			if (p->setDifficulty == false)
			{
				if (currentRoom->multiplayer_AllowDifferentDifficulties)
				{
					playerDifficultyMiniMenuUpdate(p);
				}
				else
				{
					p->gameLogic->currentGameSequence->currentDifficultyName = currentRoom->room_DifficultyName;
					p->setDifficulty = true;
				}
			}
			else
			if(p->confirmed==false)
			{
				p->confirmed = true;

				p->gameCaption = getCaptionManager()->newManagedCaption(Caption::Position::NONE, 0, 0, -1, p->gameLogic->currentGameSequence->name, 12, true, OKMenu::menuColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
				p->difficultyCaption = getCaptionManager()->newManagedCaption(Caption::Position::NONE, 0, 0, -1, p->gameLogic->currentGameSequence->currentDifficultyName, 12, true, OKMenu::menuColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
			}

		}
	}

	if (players->size() > 1)
	{
		if (ready)
		{
			if (localMultiplayerPressStartCaption == nullptr)
			{
				localMultiplayerPressStartCaption = getCaptionManager()->newManagedCaption(Caption::Position::CENTERED_X, 0, (int)(getHeight() - 50), -1, "Press the Enter key or Start on your controller to start game", 16, true, OKMenu::menuColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
				localMultiplayerPressStartCaption->flashing = true;
				localMultiplayerPressStartCaption->flashingTicksPerFlash = 1000;
			}

			if (getControlsManager()->miniGame_START_Pressed())
			{
				//start the game!

				leaveMenu = true;
			}
		}
	}

	if (players->size() <= 1 || ready == false)
	{
		if (localMultiplayerPressStartCaption != nullptr)
		{
			localMultiplayerPressStartCaption->setToBeDeletedImmediately();
			localMultiplayerPressStartCaption = nullptr;
		}
	}

	//int maxPlayers = 4;
	if (getControlsManager()->key_SPACE_Pressed())
	{
		//if (players->size() < maxPlayers)
		{
			bool alreadyInUse = false;
			for (int i = 0; i < players->size(); i++)
			{
				sp<PuzzlePlayer> p = players->at(i);
				if (p->useKeyboard)alreadyInUse = true;
			}
			if (!alreadyInUse)
			{
				sp<PuzzlePlayer> p = ms<PuzzlePlayer>(ms<GameLogic>(this, -1));
				p->useKeyboard = true;
				players->push_back(p);
				p->nameCaption = getCaptionManager()->newManagedCaption(Caption::Position::NONE, 0, 0, -1, "Local (Keyboard)", 12, true, OKMenu::menuColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
			}
		}
	}
	if (getControlsManager()->key_LSHIFT_Pressed())
	{
		for (int i = 0; i < players->size(); i++)
		{
			sp<PuzzlePlayer> p = players->at(i);
			if (p->useKeyboard)
			{
				players->erase(players->begin()+i);
				//delete p;
				p = nullptr;
				i = 0;
			}
		}
	}

	for (int controllerNum = 0; controllerNum < getControlsManager()->gameControllers->size(); controllerNum++)
	{
		sp<GameController> g = getControlsManager()->gameControllers->at(controllerNum);

		if (g->a_Pressed())
		{
			//if (players->size() < maxPlayers)
			{
				bool alreadyInUse = false;
				for (int i = 0; i < players->size(); i++)
				{
					sp<PuzzlePlayer> p = players->at(i);
					if (p->gameController == g)alreadyInUse = true;
				}

				if (!alreadyInUse)
				{
					sp<PuzzlePlayer> p = ms<PuzzlePlayer>(ms<GameLogic>(this, -1));
					p->gameController = g;
					players->push_back(p);
					p->nameCaption = getCaptionManager()->newManagedCaption(Caption::Position::NONE, 0, 0, -1, "Local (Controller " + to_string(controllerNum) + ")", 12, true, OKMenu::menuColor, OKMenu::clearColor, RenderOrder::OVER_GUI);
				}
			}
		}

		if (g->b_Pressed())
		{
			for (int i = 0; i < players->size(); i++)
			{
				sp<PuzzlePlayer> p = players->at(i);
				if (p->gameController == g)
				{
					players->erase(players->begin()+i);
					//delete p;
					p = nullptr;
					i = 0;
				}
			}
		}
	}

	if (getControlsManager()->key_ESC_Pressed() || getControlsManager()->miniGame_SELECT_Pressed())
	{
		leaveMenu = true;
		startScreenMenuShowing = true;

		initPlayer();
	}

	if (leaveMenu)
	{
		localMultiplayerPlayerJoinMenuShowing = false;

		if (localMultiplayerPlayerJoinMenu != nullptr)
		{
			//delete localMultiplayerPlayerJoinMenu;
			localMultiplayerPlayerJoinMenu = nullptr;
		}

		if (localMultiplayerPressStartCaption != nullptr)
		{
			localMultiplayerPressStartCaption->setToBeDeletedImmediately();
			localMultiplayerPressStartCaption = nullptr;
		}
	}

}

//=========================================================================================================================
void OKGame::localMultiplayerPlayerJoinMenuRender()
{//=========================================================================================================================

	GLUtils::drawFilledRect(OKMenu::bgColor->ri(), OKMenu::bgColor->gi(), OKMenu::bgColor->bi(), 0, (float)getWidth(), 0, (float)getHeight(), 1.0f);

	sp<OKTexture> kt = keyboardIconTexture;
	sp<OKTexture> gt = controllerIconTexture;

	for (int i = 0; i < players->size(); i++)
	{
		sp<PuzzlePlayer>p = players->at(i);

		sp<OKTexture>t = nullptr;

		if (p->useKeyboard)t = kt;
		else
			if (p->gameController != nullptr)t = gt;

		float sx0 = 0;
		float sx1 = 0;
		float sy0 = 0;
		float sy1 = 0;

		if (t != nullptr)
		{
			int slot = (int)players->size();
			if (slot < 2)slot = 2;

			float tx0 = 0;
			float tx1 = (float)(t->getImageWidth()) / (float)(t->getTextureWidth());
			float ty0 = 0;
			float ty1 = (float)((float)(t->getImageHeight()) / (float)(t->getTextureHeight()));

			float ratio = (float)(getWidth() / slot / 6 * 2) / (float)(t->getImageWidth());

			sx0 = (float)((int)(getWidth() / slot*i + getWidth() / slot / 6 * 2));
			sx1 = sx0 + (int)((getWidth() / slot) / 6 * 2);
			sy0 = (float)((int)(getHeight() / 6 * 1));
			sy1 = sy0 + (float)((int)(t->getImageHeight() * ratio));

			GLUtils::drawTexture(t, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
		}

		float x = (float)((int)sx0);
		float y = (float)((int)sy1 + 6);
		if (p->confirmed == false)
		{
			playerDifficultyMiniMenuRender(p, x, y);
		}
		else
		{
			//draw greencheck mark or green box or something?
			GLUtils::drawFilledRect(0, 255, 0, sx0, sx1, sy0, sy1, 0.2f);

			if (p->gameCaption != nullptr)
			{
				p->gameCaption->screenX = sx0;
				p->gameCaption->screenY = sy1 + 4;
				//p->gameCaption->render();
			}
			if (p->difficultyCaption != nullptr)
			{
				p->difficultyCaption->screenX = sx0;
				p->difficultyCaption->screenY = sy1 + 4 + 16;
				//p->difficultyCaption->render();
			}
		}

		//need to render friend name and player number
		if (p->nameCaption != nullptr)
		{
			p->nameCaption->screenX = sx0;
			p->nameCaption->screenY = sy1 - 12;
			//p->nameCaption->render();
		}
	}

	if (localMultiplayerPlayerJoinMenu == nullptr)return;

	localMultiplayerPlayerJoinMenu->render(getHeight() / 4 * 3);

}


//=========================================================================================================================
void OKGame::playerDifficultyMiniMenuUpdate(sp<PuzzlePlayer>p)
{//=========================================================================================================================

	if (p != nullptr)
	{



		if (p->menu == nullptr)
		{
			p->menu = ms<OKMenu>(this, "");
			p->menu->center = false;
			p->menu->setFontSize(12);
			GameType g;

			for (int i = 0; i<g.difficultyTypes->size(); i++)
			{
				p->menu->add(g.difficultyTypes->at(i)->name);
			}
		}

		{
			bool up = false;
			bool down = false;
			bool a = false;
			if (p->useKeyboard)
			{
				if (getControlsManager()->key_UP_Pressed())up = true;
				if (getControlsManager()->key_DOWN_Pressed())down = true;
				if (getControlsManager()->key_SPACE_Pressed())a = true;
			}
			else
			{
				sp<GameController>g = p->gameController;
				if (g != nullptr)
				{
					if (g->up_Pressed())up = true;
					if (g->down_Pressed())down = true;
					if (g->a_Pressed())a = true;
				}
			}

			if (up)
			{
				p->menu->up();
			}

			if (down)
			{
				p->menu->down();
			}

			if (a)
			{
				sp<GameLogic>game = p->gameLogic;
				GameType g;

				for (int i = 0; i<g.difficultyTypes->size(); i++)
				{
					string difficultyName = g.difficultyTypes->at(i)->name;

					if (p->menu->isSelectedID(difficultyName))
					{
						game->currentGameSequence->currentDifficultyName = difficultyName;
						p->setDifficulty = true;
					}
				}

				if (p->menu != nullptr)
				{
					//delete p->menu;
					p->menu = nullptr;
				}


			}
		}
	}

}

//=========================================================================================================================
void OKGame::playerDifficultyMiniMenuRender(sp<PuzzlePlayer>p, float x, float y)
{//=========================================================================================================================

	if (p->menu != nullptr)
	{
		p->menu->render((int)y, (int)x);
	}
}

//=========================================================================================================================
void OKGame::playerGameSequenceMiniMenuUpdate(sp<PuzzlePlayer>p)
{//=========================================================================================================================

	const string PLAY_GAME_SEQUENCE = "Play Game Sequence";
	const string PLAY_SINGLE_GAME_TYPE = "Play Single Game Type";

	const string RANDOMIZE_SEQUENCE = "Randomize Sequence";
	const string PLAY_THROUGH_SEQUENCE_IN_ORDER = "Play Through Sequence In Order";

	if (p != nullptr)
	{
		if (p->menu == nullptr)
		{
			p->menu = ms<OKMenu>(this, "");
			p->menu->center = false;
			p->menu->setFontSize(14);
			p->menu->outline = false;

			if (p->selectGameSequenceOrSingleGameTypeMiniMenuShowing)
			{
				p->menu->add(PLAY_GAME_SEQUENCE);
				p->menu->add(PLAY_SINGLE_GAME_TYPE);
			}

			if(p->selectGameSequenceMiniMenuShowing)
			{
				populateGameSequencesMenu(p->menu);
			}

			if (p->gameSequenceOptionsMiniMenuShowing)
			{
				p->menu->add(RANDOMIZE_SEQUENCE);
				p->menu->add(PLAY_THROUGH_SEQUENCE_IN_ORDER);
			}

			if(p->selectSingleGameTypeMiniMenuShowing)
			{
				populateGameTypesMenu(p->menu);
			}
		}

		{
			bool up = false;
			bool down = false;
			bool a = false;
			if (p->useKeyboard)
			{
				if (getControlsManager()->KEY_UP_HELD)up = true;
				if (getControlsManager()->KEY_DOWN_HELD)down = true;
				if (getControlsManager()->key_SPACE_Pressed())a = true;
			}
			else
			{
				sp<GameController>g = p->gameController;
				if (g != nullptr)
				{
					if (g->UP_HELD)up = true;
					if (g->DOWN_HELD)down = true;
					if (g->a_Pressed())a = true;
				}
			}

			if (up)
			{
				long long currentTime = System::currentHighResTimer();

				if (p->upRepeatedStarted == false)
				{
					p->menu->up();
					p->upRepeatedStarted = true;
					p->upLastTime = currentTime;
				}
				else
				{

					long long startTime = p->upLastTime;
					int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

					if (p->upRepeating == false)
					{
						if (ticksPassed > 300)
						{
							p->upLastTime = currentTime;
							p->menu->up();
							p->upRepeating = true;
						}
					}
					else
					{
						if (ticksPassed > 30)
						{
							p->upLastTime = currentTime;
							p->menu->up();
						}
					}
				}
			}
			else
			{
				p->upRepeating = false;
				p->upRepeatedStarted = false;
			}

			if (down)
			{
				long long currentTime = System::currentHighResTimer();

				if (p->downRepeatedStarted == false)
				{
					p->menu->down();
					p->downRepeatedStarted = true;
					p->downLastTime = currentTime;
				}
				else
				{
					long long startTime = p->downLastTime;
					int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));

					if (p->downRepeating == false)
					{
						if (ticksPassed > 300)
						{
							p->downLastTime = currentTime;
							p->menu->down();
							p->downRepeating = true;
						}
					}
					else
					{
						if (ticksPassed > 30)
						{
							p->downLastTime = currentTime;
							p->menu->down();
						}
					}
				}
			}
			else
			{
				p->downRepeating = false;
				p->downRepeatedStarted = false;
			}

			if (a)
			{
				sp<GameLogic>game = p->gameLogic;

				if (p->selectGameSequenceOrSingleGameTypeMiniMenuShowing)
				{
					if (p->menu->isSelectedID(PLAY_GAME_SEQUENCE))
					{
						p->selectGameSequenceMiniMenuShowing = true;
					}
					if (p->menu->isSelectedID(PLAY_SINGLE_GAME_TYPE))
					{
						p->selectSingleGameTypeMiniMenuShowing = true;
					}

					p->selectGameSequenceOrSingleGameTypeMiniMenuShowing = false;
				}
				else
				if(p->selectGameSequenceMiniMenuShowing)
				{
					for (int i = 0; i<loadedGameSequences->size(); i++)
					{

						sp<GameSequence>gs = loadedGameSequences->at(i);
						if (p->menu->isSelectedID(gs->uuid))
						{
							game->currentGameSequence = gs;
							p->gameSequenceOptionsMiniMenuShowing = true;
						}
					}

					p->selectGameSequenceMiniMenuShowing = false;

				}
				else
				if(p->gameSequenceOptionsMiniMenuShowing)
				{
					if (p->menu->isSelectedID(RANDOMIZE_SEQUENCE))
					{
						game->currentGameSequence->randomizeSequence = true;
					}

					if (p->menu->isSelectedID(PLAY_THROUGH_SEQUENCE_IN_ORDER))
					{
						game->currentGameSequence->randomizeSequence = false;
					}

					p->setGameSequence = true;
					p->gameSequenceOptionsMiniMenuShowing = false;

				}
				else
				if(p->selectSingleGameTypeMiniMenuShowing)
				{

					for (int i = 0; i<loadedGameTypes->size(); i++)
					{
						sp<GameType>g = loadedGameTypes->at(i);
						if (p->menu->isSelectedID(g->uuid))
						{
							game->currentGameSequence = ms<GameSequence>();
							game->currentGameSequence->gameTypes->push_back(g);
							game->currentGameSequence->name = g->name;
						}
					}

					p->setGameSequence = true;
					p->selectSingleGameTypeMiniMenuShowing = false;

				}

				if (p->menu != nullptr)
				{
					//delete p->menu;
					p->menu = nullptr;
				}

			}
		}
	}

}

//=========================================================================================================================
void OKGame::playerGameSequenceMiniMenuRender(sp<PuzzlePlayer>p, float x, float y)
{//=========================================================================================================================

	if (p->menu != nullptr)
	{
		p->menu->render((int)y, (int)x);
	}
}

