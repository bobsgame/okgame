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


	vector<sp<Engine>> states;

	//sp<Engine> currentState = nullptr;


	StateManager();


	sp<Engine> getCurrentState();


	void pushState(sp<Engine> s);
	void popState();


	void update();

	void render();


};

