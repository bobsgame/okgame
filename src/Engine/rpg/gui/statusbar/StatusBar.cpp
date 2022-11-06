
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StatusBar::log = Logger("StatusBar");


shared_ptr<BobTexture> StatusBar::blackBackgroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::blackForegroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::whiteBackgroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::whiteForegroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::backgroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::foregroundTexture = nullptr;
shared_ptr<BobTexture> StatusBar::glowTexture = nullptr;
shared_ptr<BobTexture> StatusBar::dividerTexture = nullptr;
int StatusBar::sizeY = 26;
float StatusBar::glossAlpha = 1.0f;
bool StatusBar::useLightTheme = false;

StatusBar::StatusBar(shared_ptr<BGClientEngine> g)
{ //=========================================================================================================================

	this->e = g;

	clockCaption = make_shared<ClockCaption>(g);
	dayCaption = make_shared<DayCaption>(g);
	moneyCaption = make_shared<MoneyCaption>(g);
	ndButton = make_shared<NDButton>(g);
	gameStoreButton = make_shared<GameStoreButton>(g);
	stuffButton = make_shared<StuffButton>(g);

	notificationManager = make_shared<NotificationManager>(g);


	blackBackgroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/blackbarbackground.png");
	blackForegroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/blackbarforeground.png");

	whiteBackgroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/whitebarbackground.png");
	whiteForegroundTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/whitebarforeground.png");

	backgroundTexture = blackBackgroundTexture;
	foregroundTexture = blackForegroundTexture;


	glowTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/greenDot.png");
	dividerTexture = GLUtils::getTextureFromPNGExePath("data/statusbar/dividerLine.png");
}

void StatusBar::init()
{ //=========================================================================================================================

	clockCaption->init();
	dayCaption->init();
	moneyCaption->init();
	ndButton->init();
	gameStoreButton->init();
	stuffButton->init();

	notificationManager->init();
}

void StatusBar::update()
{ //=========================================================================================================================
	clockCaption->update();
	dayCaption->update();
	moneyCaption->update();

	ndButton->update();
	gameStoreButton->update();
	stuffButton->update();

	notificationManager->update();
}

void StatusBar::setLightTheme()
{ //=========================================================================================================================

	if (useLightTheme == false)
	{
		useLightTheme = true;
		backgroundTexture = whiteBackgroundTexture;
		foregroundTexture = whiteForegroundTexture;


		clockCaption->setColors(make_shared<BobColor>(200, 0, 0), BobColor::lightRed, nullptr);
		dayCaption->setColors(BobColor::black, BobColor::lighterGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void StatusBar::setDarkTheme()
{ //=========================================================================================================================
	if (useLightTheme == true)
	{
		useLightTheme = false;
		backgroundTexture = blackBackgroundTexture;
		foregroundTexture = blackForegroundTexture;


		clockCaption->setColors(BobColor::red, BobColor::darkerRed, nullptr);
		dayCaption->setColors(BobColor::white, BobColor::darkerGray, nullptr);
		moneyCaption->setColors(BobColor::green, BobColor::darkerGreen, nullptr);
	}
}

void StatusBar::setEnabled(bool b)
{ //=========================================================================================================================
	enabled = b;
}

void StatusBar::render()
{ //=========================================================================================================================


	if (enabled == false)
	{
		return;
	}


	render(0);

	clockCaption->render(0); //getText, lights
	dayCaption->render(0);
	moneyCaption->render(0);


	ndButton->render(0); //button graphics
	gameStoreButton->render(0);
	stuffButton->render(0);

	notificationManager->render(0); //notification string

	render(1); //status bar gloss


	clockCaption->render(1); //nothing
	dayCaption->render(1); //nothing
	moneyCaption->render(1); //divider


	ndButton->render(1); //dividers
	gameStoreButton->render(1);
	stuffButton->render(1);


	notificationManager->render(1); //nothing yet
}

void StatusBar::render(int layer)
{ //=========================================================================================================================

	if (enabled == false)
	{
		return;
	}

	shared_ptr<BobTexture> texture = nullptr;
	if (layer == 0)
	{
		texture = backgroundTexture;
	}
	if (layer == 1)
	{
		texture = foregroundTexture;
	}

	float alpha = 1.0f;
	if (layer == 1)
	{
		alpha = glossAlpha;
	}


	GLUtils::drawTexture(texture, 0, (float)GLUtils::getViewportWidth(), -6, (float)sizeY + 6, alpha, GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING);
}

