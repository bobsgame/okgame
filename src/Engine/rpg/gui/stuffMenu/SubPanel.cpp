#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger SubPanel::log = Logger("SubPanel");

SubPanel::SubPanel()
{ //=========================================================================================================================

	//   thisDialogLayout = this;
	//
	//
	//   setTheme(GUIManager::subMenuPanelDialogLayoutTheme);
	//
	//   //----------------------
	//   //setup layout inside scrollpane
	//   //----------------------
	//   insideLayout = ms<DialogLayout>();
	//   insideLayout->setTheme(GUIManager::emptyDialogLayoutTheme);
	//   insideLayout->setCanAcceptKeyboardFocus(false);
	//
	//
	//   //----------------------
	//   //setup scrollpane
	//   //----------------------
	//
	//   scrollPane = ms<ScrollPane>(insideLayout);
	//   scrollPane->setTheme(GUIManager::scrollPaneTheme);
	//   scrollPane->setCanAcceptKeyboardFocus(false);
	//   scrollPane->setExpandContentSize(true);
	//
	//
	//   //----------------------
	//   //setup this dialoglayout
	//   //----------------------
	//
	//   add(scrollPane);
	//   setVisible(false);
	//
	//   setCanAcceptKeyboardFocus(false);
	//   setHorizontalGroup(createParallelGroup(scrollPane));
	//
	//   setVerticalGroup(createSequentialGroup(scrollPane));
}

void SubPanel::init()
{ //=========================================================================================================================
	//put anything in here that you want to happen after the subpanel is created and constructed
}

void SubPanel::setVisible(bool b)
{ //=========================================================================================================================
	//DialogLayout::setVisible(b);

	//put anything in here that you want to happen when we switch to the subpanel
}

void SubPanel::layout()
{ //=========================================================================================================================

	//   scrollPane->setMinSize((int)(StuffMenu()->insideScrollPaneLayout->getInnerWidth() * StuffMenu()->subPanelScreenWidthPercent), (int)(StuffMenu()->insideScrollPaneLayout->getInnerHeight() * StuffMenu()->subPanelScreenHeightPercent));
	//   scrollPane->setSize((int)(StuffMenu()->insideScrollPaneLayout->getInnerWidth() * StuffMenu()->subPanelScreenWidthPercent), (int)(StuffMenu()->insideScrollPaneLayout->getInnerHeight() * StuffMenu()->subPanelScreenHeightPercent));
	//   //scrollPane.adjustSize();
	//
	//   scrollPane->updateScrollbarSizes();
	//
	//   DialogLayout::layout();

}

void SubPanel::update()
{ //=========================================================================================================================

	//put anything in here that you want to change every frame
}

void SubPanel::render()
{ //=========================================================================================================================
}
//
//sp<BGClientEngine> SubPanel::getClientEngine()
//{
//	return Main::gameEngine;
//}
//
//sp<EventManager> SubPanel::getEventManager()
//{
//	return getClientEngine()->eventManager;
//}
//
//sp<Clock> SubPanel::getClock()
//{
//	return getClientEngine()->clock;
//}
//
//sp<GUIManager> SubPanel::getGUIManager()
//{
//	return getClientEngine()->guiManager;
//}
//
//sp<StuffMenu> SubPanel::getStuffMenu()
//{
//	return getGUIManager()->stuffMenu;
//}
//
//sp<GameStore> SubPanel::getGameStore()
//{
//	return getGUIManager()->gameStore;
//}
//
//sp<PlayerEditMenu> SubPanel::getPlayerEditMenu()
//{
//	return getGUIManager()->playerEditMenu;
//}
//
//sp<Player> SubPanel::getPlayer()
//{
//	return getClientEngine()->player;
//}
//
//ND* SubPanel::getND()
//{
//	return getClientEngine()->nD;
//}
//
//sp<Wallet> SubPanel::getWallet()
//{
//	return getClientEngine()->wallet;
//}
//
//sp<FriendManager> SubPanel::getFriendManager()
//{
//	return getClientEngine()->friendManager;
//}
//
//sp<StatusBar> SubPanel::getStatusBar()
//{
//	return getClientEngine()->statusBar;
//}
//
//sp<NotificationManager> SubPanel::getNotificationManager()
//{
//	return getStatusBar()->notificationManager;
//}
//
//sp<TCPServerConnection> SubPanel::getServerConnection()
//{
//	return OKNet::tcpServerConnection;
//}
//
//sp<GameSave> SubPanel::getGameSave()
//{
//	return getServerConnection()->getGameSave_S();
//}
//
