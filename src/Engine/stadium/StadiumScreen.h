//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class MiniGameEngine;

class StadiumScreen : public EnginePart
{
public:

	static Logger log;


	//static const int getViewportWidth() = 640 * 2;
	//static const int getViewportHeight() = 480 * 2;
	//static const int FBO_SCALE = 1;


	sp<StateManager> stadiumGameStateManager = nullptr;


	sp<Area> area = nullptr;


	StadiumScreen(sp<Engine> g);


	void update();


	void setGame(sp<MiniGameEngine> game, sp<Area> area);


	sp<MiniGameEngine> getGame();


	void render();
};

