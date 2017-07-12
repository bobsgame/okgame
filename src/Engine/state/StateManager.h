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


	Engine* currentState = nullptr;


	StateManager();


	Engine* getState();


	void setState(Engine* s);


	void update();

	void render();


};

