
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StatusBar::log = Logger("StatusBar");


sp<OKTexture> StatusBar::blackBackgroundTexture = nullptr;
sp<OKTexture> StatusBar::blackForegroundTexture = nullptr;
sp<OKTexture> StatusBar::whiteBackgroundTexture = nullptr;
sp<OKTexture> StatusBar::whiteForegroundTexture = nullptr;
sp<OKTexture> StatusBar::backgroundTexture = nullptr;
sp<OKTexture> StatusBar::foregroundTexture = nullptr;
sp<OKTexture> StatusBar::glowTexture = nullptr;
sp<OKTexture> StatusBar::dividerTexture = nullptr;
int StatusBar::sizeY = 26;
float StatusBar::glossAlpha = 1.0f;
bool StatusBar::useLightTheme = false;

StatusBar::StatusBar(sp<BGClientEngine> g)
{ //=========================================================================================================================

	this->e = g;

	clockCaption = ms<ClockCaption>(g);
	dayCaption = ms<DayCaption>(g);
	moneyCaption = ms<MoneyCaption>(g);
	ndButton = ms<NDButton>(g);
	gameStoreButton = ms<GameStoreButton>(g);
	stuffButton = ms<StuffButton>(g);

	notificationManager = ms<NotificationManager>(g);


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


		clockCaption->setColors(ms<OKColor>(200, 0, 0), OKColor::lightRed, nullptr);
		dayCaption->setColors(OKColor::black, OKColor::lighterGray, nullptr);
		moneyCaption->setColors(OKColor::green, OKColor::darkerGreen, nullptr);
	}
}

void StatusBar::setDarkTheme()
{ //=========================================================================================================================
	if (useLightTheme == true)
	{
		useLightTheme = false;
		backgroundTexture = blackBackgroundTexture;
		foregroundTexture = blackForegroundTexture;


		clockCaption->setColors(OKColor::red, OKColor::darkerRed, nullptr);
		dayCaption->setColors(OKColor::white, OKColor::darkerGray, nullptr);
		moneyCaption->setColors(OKColor::green, OKColor::darkerGreen, nullptr);
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

	sp<OKTexture> texture = nullptr;
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

