
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger OKGameStadium::log = Logger("OKGameStadium");

//=========================================================================================================================
OKGameStadium::OKGameStadium()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("OKGameStadium()");
#endif
	
}
//=========================================================================================================================
OKGameStadium::~OKGameStadium()
{ //=========================================================================================================================
#ifdef _DEBUG
	log.info("~OKGameStadium()");
#endif

}
//=========================================================================================================================
void OKGameStadium::init()
{ //=========================================================================================================================

	super::init();


#ifdef _DEBUG
	log.info("OKGameStadium::init()");
#endif

	name = "ok game";
}

OKGameStadium::OKGameStadium(sp<StadiumScreen> stadiumScreen, sp<Area> area)
{ //=========================================================================================================================

#ifdef _DEBUG
	log.info("OKGameStadium(sp<StadiumScreen> stadiumScreen, sp<Area> area)");
#endif

	//StadiumGameEngine(stadiumScreen, area);
	this->stadiumScreen = stadiumScreen;
	this->area = area;
	stadiumScreen->setGame(shared_from_this(), area);



}


void OKGameStadium::shakeSmall()
{ //=========================================================================================================================
	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.1f;
	getClientGameEngine()->getCameraman()->setShakeScreen(300, 2, 2, 30);
	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
}

void OKGameStadium::shakeHard()
{ //=========================================================================================================================
	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.5f;
	getClientGameEngine()->getCameraman()->setShakeScreen(1000, 5, 5, 30);
	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
}








void OKGameStadium::titleMenuUpdate()
{ //=========================================================================================================================

	if (titleMenu == nullptr)
	{
		titleMenu = ms<OKMenu>(this,"");
		titleMenu->add("TOURNAMENT MODE");
	}


	if (getControlsManager()->miniGame_CONFIRM_Pressed())
	{
		titleMenuShowing = false;


		if (titleMenu != nullptr)
		{
			//delete titleMenu;
			titleMenu = nullptr;
		}
	}
}



void OKGameStadium::tryToCloseGame()
{ //=========================================================================================================================
	//TODO: upload score to leaderboard
}



