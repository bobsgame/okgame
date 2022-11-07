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


	shared_ptr<StateManager> stadiumGameStateManager = nullptr;


	shared_ptr<Area> area = nullptr;


	StadiumScreen(shared_ptr<Engine> g);


	void update();


	void setGame(shared_ptr<MiniGameEngine> game, shared_ptr<Area> area);


	shared_ptr<MiniGameEngine> getGame();


	void render();
};

