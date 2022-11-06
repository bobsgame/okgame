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
	//   insideLayout = make_shared<DialogLayout>();
	//   insideLayout->setTheme(GUIManager::emptyDialogLayoutTheme);
	//   insideLayout->setCanAcceptKeyboardFocus(false);
	//
	//
	//   //----------------------
	//   //setup scrollpane
	//   //----------------------
	//
	//   scrollPane = make_shared<ScrollPane>(insideLayout);
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
//shared_ptr<BGClientEngine> SubPanel::getClientEngine()
//{
//	return Main::gameEngine;
//}
//
//shared_ptr<EventManager> SubPanel::getEventManager()
//{
//	return getClientEngine()->eventManager;
//}
//
//shared_ptr<Clock> SubPanel::getClock()
//{
//	return getClientEngine()->clock;
//}
//
//shared_ptr<GUIManager> SubPanel::getGUIManager()
//{
//	return getClientEngine()->guiManager;
//}
//
//shared_ptr<StuffMenu> SubPanel::getStuffMenu()
//{
//	return getGUIManager()->stuffMenu;
//}
//
//shared_ptr<GameStore> SubPanel::getGameStore()
//{
//	return getGUIManager()->gameStore;
//}
//
//shared_ptr<PlayerEditMenu> SubPanel::getPlayerEditMenu()
//{
//	return getGUIManager()->playerEditMenu;
//}
//
//shared_ptr<Player> SubPanel::getPlayer()
//{
//	return getClientEngine()->player;
//}
//
//ND* SubPanel::getND()
//{
//	return getClientEngine()->nD;
//}
//
//shared_ptr<Wallet> SubPanel::getWallet()
//{
//	return getClientEngine()->wallet;
//}
//
//shared_ptr<FriendManager> SubPanel::getFriendManager()
//{
//	return getClientEngine()->friendManager;
//}
//
//shared_ptr<StatusBar> SubPanel::getStatusBar()
//{
//	return getClientEngine()->statusBar;
//}
//
//shared_ptr<NotificationManager> SubPanel::getNotificationManager()
//{
//	return getStatusBar()->notificationManager;
//}
//
//shared_ptr<TCPServerConnection> SubPanel::getServerConnection()
//{
//	return OKNet::tcpServerConnection;
//}
//
//shared_ptr<GameSave> SubPanel::getGameSave()
//{
//	return getServerConnection()->getGameSave_S();
//}
//
