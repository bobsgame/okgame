//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
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


	static sp<OKTexture> blackBackgroundTexture;
	static sp<OKTexture> blackForegroundTexture;

	static sp<OKTexture> whiteBackgroundTexture;
	static sp<OKTexture> whiteForegroundTexture;

	static sp<OKTexture> backgroundTexture;
	static sp<OKTexture> foregroundTexture;


	static sp<OKTexture> glowTexture;
	static sp<OKTexture> dividerTexture;


	static int sizeY;

	static float glossAlpha;

	static bool useLightTheme;

	sp<ClockCaption> clockCaption = nullptr;
	sp<DayCaption> dayCaption = nullptr;
	sp<MoneyCaption> moneyCaption = nullptr;
	sp<NDButton> ndButton = nullptr;
	sp<GameStoreButton> gameStoreButton = nullptr;
	sp<StuffButton> stuffButton = nullptr;

	sp<NotificationManager> notificationManager = nullptr;


	bool enabled = true;


	StatusBar(sp<BGClientEngine> g);


	void init();


	void update();


	void setLightTheme();

	void setDarkTheme();


	void setEnabled(bool b);


	void render();


	void render(int layer);
};

