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


	State* currentState = nullptr;


	StateManager();


	State* getState();


	void setState(State* s);


	void update();

	void render();


};

