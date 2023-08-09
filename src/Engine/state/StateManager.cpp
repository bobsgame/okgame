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

sp<Engine> StateManager::getCurrentState()
{ //=========================================================================================================================

	if(states->size()>0)
	return states->at(0);
	else return nullptr;
}

//void StateManager::setState(sp<Engine> s)
//{ //=========================================================================================================================
//	currentState = s;
//}

void StateManager::pushState(sp<Engine> s)
{ //=========================================================================================================================
	//states->insert(0, s);
	states->insert(states->begin(), s);
}

void StateManager::popState()
{ //=========================================================================================================================
	if(states->size()>0)
	states->erase(states->begin()+0);
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

