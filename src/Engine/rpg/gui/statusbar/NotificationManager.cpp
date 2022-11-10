
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NotificationManager::log = Logger("NotificationManager");


sp<OKTexture> NotificationManager::loadingBarTexture = nullptr;
sp<OKTexture> NotificationManager::loadingBarBackgroundTexture = nullptr;

NotificationManager::NotificationManager(sp<BGClientEngine> g)
{ //=========================================================================================================================


	this->e = g;

	loadingBarTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/loadingBar.png");
	loadingBarBackgroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/loadingBarBackground.png");


	//TODO: manage multiple notifications, cycle through them, keep them in a dropdown log

	//TODO: have status bar movable to bottom
}

void NotificationManager::init()
{ //=========================================================================================================================
}

void NotificationManager::update()
{ //=========================================================================================================================


	for (int i = 0; i < notificationList.size(); i++)
	{
		notificationList.at(i)->update();
	}
}

void NotificationManager::render(int layer)
{ //=========================================================================================================================
	for (int i = 0; i < notificationList.size(); i++)
	{
		notificationList.at(i)->render(layer);
	}
}

void NotificationManager::add(sp<Notification> n)
{ //=========================================================================================================================


	notificationList.push_back(n);
}

void NotificationManager::remove(sp<Notification> n)
{ //=========================================================================================================================

	notificationList.remove(n);
}

