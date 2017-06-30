//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MiniGameEngine;

class StadiumScreen : public EnginePart
{
public:

	static Logger log;


	//static const int getViewportWidth() = 640 * 2;
	//static const int getViewportHeight() = 480 * 2;
	//static const int FBO_SCALE = 1;


	StateManager* stadiumGameStateManager = nullptr;


	Area* area = nullptr;


	StadiumScreen(Engine* g);


	void update();


	void setGame(MiniGameEngine* game, Area* area);


	MiniGameEngine* getGame();


	void render();
};

