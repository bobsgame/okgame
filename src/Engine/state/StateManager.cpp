#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger StateManager::log = Logger("StateManager");


StateManager::StateManager()
{ //=========================================================================================================================
}

Engine* StateManager::getCurrentState()
{ //=========================================================================================================================

	if(states.size()>0)
	return states.get(0);
	else return nullptr;
}

//void StateManager::setState(Engine* s)
//{ //=========================================================================================================================
//	currentState = s;
//}

void StateManager::pushState(Engine* s)
{ //=========================================================================================================================
	states.insert(0, s);
}

void StateManager::popState()
{ //=========================================================================================================================
	if(states.size()>0)
	states.removeAt(0);
}

void StateManager::update()
{
	Engine::updateTimers();
	getCurrentState()->update();
}

void StateManager::render()
{
	getCurrentState()->render();
}

