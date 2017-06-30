#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger EventManager::log = Logger("EventManager");

EventManager::EventManager(Engine* g)
{ //=========================================================================================================================

	this->e = g;
}


void EventManager::update()
{ //=========================================================================================================================

	for(int i=0;i<eventList.size();i++)eventList.get(i)->update();//only update running events, otherwise we update events that we might not have access to yet.

	for (int i = 0; i < itemList.size(); i++)
	{
		itemList.get(i)->update();
	}

	for (int i = 0; i < gameStringList.size(); i++)
	{
		gameStringList.get(i)->update();
	}

	for (int i = 0; i < dialogueList.size(); i++)
	{
		dialogueList.get(i)->update();
	}

	for (int i = 0; i < flagList.size(); i++)
	{
		flagList.get(i)->update();
	}

	for (int i = 0; i < skillList.size(); i++)
	{
		skillList.get(i)->update();
	}

//	for (int i = 0; i < cutsceneEventList.size(); i++)
//	{
//		cutsceneEventList.get(i)->update();
//	}

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		Event* s = runningEventQueue.get(i);
		s->run();
	}
}

void EventManager::addToEventQueueIfNotThere(Event* event)
{ //=========================================================================================================================

	if (event->getWasAddedToQueue() == false)
	{
		runningEventQueue.add(event);
		event->setAddedToQueue();
	}

	//if it isn't in the event queue, add a fresh stack to the event queue.

	//if it is in the event queue, run the next instruction.
}

bool EventManager::isEventInQueue(Event* event)
{ //=========================================================================================================================

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		Event* s = runningEventQueue.get(i);

		if (s == event)
		{
			return true;
		}
	}
	return false;
}

void EventManager::unloadCurrentMapEvents()
{ //=========================================================================================================================

	for (int i = 0; i < (int)getCurrentMap()->mapEventList.size(); i++)
	{
		Event* s = getCurrentMap()->mapEventList.get(i);// getEventManager()->getEventByID(getCurrentMap()->mapEventIDList.get(i));
		if(s!=nullptr)s->reset();
	}

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		Event* s = runningEventQueue.get(i);

		if (s->type() != EventData::TYPE_PROJECT_INITIAL_LOADER && s->type() != EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
		{
			s->reset();
			runningEventQueue.removeAt(i);
			i = -1;
		}
	}
}

Item* EventManager::getItemByID(int id)
{ //=========================================================================================================================
	for (int i = 0; i < itemList.size(); i++)
	{
		Item* s = itemList.get(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	string e = "Item not found! getItemByID():" + to_string(id);
	Console::error(e);
	log.error(e);

	return nullptr;
}

Dialogue* EventManager::getDialogueByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < dialogueList.size(); i++)
	{
		Dialogue* d = dialogueList.get(i);
		if (d->getID() == id)
		{
			return d;
		}
	}
	return new Dialogue(getEngine(), id);
}

//Event* EventManager::getCutsceneEventByID(int id)
//{ //=========================================================================================================================
//	//go through list
//	//if event doesn't exist, make new one
//	for (int i = 0; i < cutsceneEventList.size(); i++)
//	{
//		Event* d = cutsceneEventList.get(i);
//		if (d->getID() == id)
//		{
//			return d;
//		}
//	}
//
//	return nullptr;
//}

Event* EventManager::getEventByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	//go through list
	//if event doesn't exist, make new one
	for (int i = 0; i < eventList.size(); i++)
	{
		Event* d = eventList.get(i);
		if (d->getID() == id)
		{
			return d;
		}
	}

	//first of all this should never happen because events are embedded in objects now
	//but i think the object should request the event from the server instead of making an empty event
	//or at least the object should create the event itself so it can be associated with the correct object
	//log.error("Could not find event with ID " + to_string(id));
	Event* d = new Event(getEngine(), new EventData(id, "", 0, "", ""), "");
	d->setInitialized_S(false);

	return d;
}

Skill* EventManager::getSkillByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < skillList.size(); i++)
	{
		Skill* s = skillList.get(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	//All skills defined in editor should be loaded from /res/SkillData at load, so it should always exist.

	string e = "Skill not found! getSkillByID():" + to_string(id);
	Console::error(e);
	log.error(e);

	return new Skill(getEngine(), id);
}

GameString* EventManager::getGameStringByIDCreateIfNotExist(int id)
{ //=========================================================================================================================

	for (int i = 0; i < gameStringList.size(); i++)
	{
		GameString* s = gameStringList.get(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return new GameString(getEngine(), id);
}

Flag* EventManager::getFlagByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < flagList.size(); i++)
	{
		Flag* s = flagList.get(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return new Flag(getEngine(), id);
}

