//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "NDMenuBackground.h"
#include "NDMenuWheel.h"

class NDMenu : public NDGameEngine
{
private:
	typedef NDGameEngine super;
public:
	static Logger log;

	NDMenu();
	~NDMenu();
	NDMenu(ND* nD);
	void init() override;

	bool runSelectedGame = false;
	int quit = 0;


	sp<NDMenuWheel> wheel = ms<NDMenuWheel>(this);
	sp<NDMenuBackground> background = ms<NDMenuBackground>(this);


	sp<OKColor> WHITE = ms<OKColor>(255, 255, 255);
	sp<OKColor> BLACK = ms<OKColor>(0, 0, 0);
	sp<OKColor> RED = ms<OKColor>(255, 0, 0);
	sp<OKColor> GREEN = ms<OKColor>(0, 255, 0);
	sp<OKColor> BLUE = ms<OKColor>(0, 0, 255);
	sp<OKColor> MAGENTA = ms<OKColor>(255, 0, 255);
	sp<OKColor> YELLOW = ms<OKColor>(0, 127, 127);


	static bool actionButtonPressed;
	long long buttonHeldTicks = 0;

	bool downButtonPressed = false;
	bool rightButtonPressed = false;
	bool upButtonPressed = false;
	bool leftButtonPressed = false;

	int ticksSinceDownPressed = 0;
	int ticksSinceRightPressed = 0;
	int ticksSinceUpPressed = 0;
	int ticksSinceLeftPressed = 0;

	long long ticks_since_down_repeat = 0;
	long long ticks_since_right_repeat = 0;
	long long ticks_since_up_repeat = 0;
	long long ticks_since_left_repeat = 0;

	long long currentTicks = 0;
	long long lastTicks = 0;

	static int actionFadeCountSwitch;

	int showMovie = 0;
	int movieSelected = 1;
	static bool directionButtonPressed;
	bool directionButtonUnpressed = false;


	static int actionFadeCounter;

	int fadeDirection = 0;
	long long fadeOutTicks = 0;


	void addGame(sp<NDGameEngine> game, const string& name, sp<OKColor> color);
	virtual void update() override;
	virtual void cleanup() override;
	virtual void render() override;
	void handleInput();
	void updateVideo();
	void renderVideo();
	void fillScreenBlack(float a);
	void fillScreenWhite(float a);
	void drawScreenOverlayFade();
};

