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

Engine* StateManager::getState()
{ //=========================================================================================================================
	return currentState;
}

void StateManager::setState(Engine* s)
{ //=========================================================================================================================
	currentState = s;
}

void StateManager::update()
{
	Engine::updateTimers();
	currentState->update();
}

void StateManager::render()
{
	currentState->render();
}

