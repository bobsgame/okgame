//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class StateManager
{
public:

	static Logger log;


	ArrayList<Engine*> states;

	//shared_ptr<Engine> currentState = nullptr;


	StateManager();


	Engine* getCurrentState();


	void pushState(Engine* s);
	void popState();


	void update();

	void render();


};

