//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class StateManager
{
public:

	static Logger log;


	ArrayList<Engine*> states;

	//Engine* currentState = nullptr;


	StateManager();


	Engine* getCurrentState();


	void pushState(Engine* s);
	void popState();


	void update();

	void render();


};

