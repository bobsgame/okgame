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


	ArrayList<shared_ptr<Engine>> states;

	//shared_ptr<Engine> currentState = nullptr;


	StateManager();


	shared_ptr<Engine> getCurrentState();


	void pushState(shared_ptr<Engine> s);
	void popState();


	void update();

	void render();


};

