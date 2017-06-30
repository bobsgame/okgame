//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class ClockCaption;
class DayCaption;
class MoneyCaption;
class NDButton;
class GameStoreButton;
class StuffButton;


class StatusBar : public EnginePart
{
public:

	static Logger log;


	static BobTexture* blackBackgroundTexture;
	static BobTexture* blackForegroundTexture;

	static BobTexture* whiteBackgroundTexture;
	static BobTexture* whiteForegroundTexture;

	static BobTexture* backgroundTexture;
	static BobTexture* foregroundTexture;


	static BobTexture* glowTexture;
	static BobTexture* dividerTexture;


	static int sizeY;

	static float glossAlpha;

	static bool useLightTheme;

	ClockCaption* clockCaption = nullptr;
	DayCaption* dayCaption = nullptr;
	MoneyCaption* moneyCaption = nullptr;
	NDButton* ndButton = nullptr;
	GameStoreButton* gameStoreButton = nullptr;
	StuffButton* stuffButton = nullptr;

	NotificationManager* notificationManager = nullptr;


	bool enabled = true;


	StatusBar(BGClientEngine* g);


	void init();


	void update();


	void setLightTheme();

	void setDarkTheme();


	void setEnabled(bool b);


	void render();


	void render(int layer);
};

