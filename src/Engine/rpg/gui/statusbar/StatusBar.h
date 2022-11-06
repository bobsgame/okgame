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


	static shared_ptr<OKTexture> blackBackgroundTexture;
	static shared_ptr<OKTexture> blackForegroundTexture;

	static shared_ptr<OKTexture> whiteBackgroundTexture;
	static shared_ptr<OKTexture> whiteForegroundTexture;

	static shared_ptr<OKTexture> backgroundTexture;
	static shared_ptr<OKTexture> foregroundTexture;


	static shared_ptr<OKTexture> glowTexture;
	static shared_ptr<OKTexture> dividerTexture;


	static int sizeY;

	static float glossAlpha;

	static bool useLightTheme;

	shared_ptr<ClockCaption> clockCaption = nullptr;
	shared_ptr<DayCaption> dayCaption = nullptr;
	shared_ptr<MoneyCaption> moneyCaption = nullptr;
	shared_ptr<NDButton> ndButton = nullptr;
	shared_ptr<GameStoreButton> gameStoreButton = nullptr;
	shared_ptr<StuffButton> stuffButton = nullptr;

	shared_ptr<NotificationManager> notificationManager = nullptr;


	bool enabled = true;


	StatusBar(shared_ptr<BGClientEngine> g);


	void init();


	void update();


	void setLightTheme();

	void setDarkTheme();


	void setEnabled(bool b);


	void render();


	void render(int layer);
};

