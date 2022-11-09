#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger EventManager::log = Logger("EventManager");

EventManager::EventManager(sp<Engine> g)
{ //=========================================================================================================================

	this->e = g;
}


void EventManager::update()
{ //=========================================================================================================================

	for(int i=0;i<eventList.size();i++)eventList.at(i)->update();//only update running events, otherwise we update events that we might not have access to yet.

	for (int i = 0; i < itemList.size(); i++)
	{
		itemList.at(i)->update();
	}

	for (int i = 0; i < gameStringList.size(); i++)
	{
		gameStringList.at(i)->update();
	}

	for (int i = 0; i < dialogueList.size(); i++)
	{
		dialogueList.at(i)->update();
	}

	for (int i = 0; i < flagList.size(); i++)
	{
		flagList.at(i)->update();
	}

	for (int i = 0; i < skillList.size(); i++)
	{
		skillList.at(i)->update();
	}

//	for (int i = 0; i < cutsceneEventList.size(); i++)
//	{
//		cutsceneEventList.at(i)->update();
//	}

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		sp<Event> s = runningEventQueue.at(i);
		s->run();
	}
}

void EventManager::addToEventQueueIfNotThere(sp<Event> event)
{ //=========================================================================================================================

	if (event->getWasAddedToQueue() == false)
	{
		runningEventQueue.push_back(event);
		event->setAddedToQueue();
	}

	//if it isn't in the event queue, add a fresh stack to the event queue.

	//if it is in the event queue, run the next instruction.
}

bool EventManager::isEventInQueue(sp<Event> event)
{ //=========================================================================================================================

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		sp<Event> s = runningEventQueue.at(i);

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
		sp<Event> s = getCurrentMap()->mapEventList.at(i);// getEventManager()->getEventByID(getCurrentMap()->mapEventIDList.at(i));
		if(s!=nullptr)s->reset();
	}

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		sp<Event> s = runningEventQueue.at(i);

		if (s->type() != EventData::TYPE_PROJECT_INITIAL_LOADER && s->type() != EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
		{
			s->reset();
			runningEventQueue.erase(runningEventQueue.begin()+i);
			i = -1;
		}
	}
}

sp<Item> EventManager::getItemByID(int id)
{ //=========================================================================================================================
	for (int i = 0; i < itemList.size(); i++)
	{
		sp<Item> s = itemList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	string e = "Item not found! getItemByID():" + to_string(id);
	Main::console->error(e);
	log.error(e);

	return nullptr;
}

sp<Dialogue> EventManager::getDialogueByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < dialogueList.size(); i++)
	{
		sp<Dialogue> d = dialogueList.at(i);
		if (d->getID() == id)
		{
			return d;
		}
	}
	return ms<Dialogue>(getEngine(), id);
}

//sp<Event> EventManager::getCutsceneEventByID(int id)
//{ //=========================================================================================================================
//	//go through list
//	//if event doesn't exist, make new one
//	for (int i = 0; i < cutsceneEventList.size(); i++)
//	{
//		sp<Event> d = cutsceneEventList.at(i);
//		if (d->getID() == id)
//		{
//			return d;
//		}
//	}
//
//	return nullptr;
//}

sp<Event> EventManager::getEventByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	//go through list
	//if event doesn't exist, make new one
	for (int i = 0; i < eventList.size(); i++)
	{
		sp<Event> d = eventList.at(i);
		if (d->getID() == id)
		{
			return d;
		}
	}

	//first of all this should never happen because events are embedded in objects now
	//but i think the object should request the event from the server instead of making an empty event
	//or at least the object should create the event itself so it can be associated with the correct object
	//log->error("Could not find event with ID " + to_string(id));
	sp<Event> d = ms<Event>(getEngine(), ms<EventData>(id, "", 0, "", ""), "");
	d->setInitialized_S(false);

	return d;
}

sp<Skill> EventManager::getSkillByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < skillList.size(); i++)
	{
		sp<Skill> s = skillList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	//All skills defined in editor should be loaded from /res/SkillData at load, so it should always exist.

	string e = "Skill not found! getSkillByID():" + to_string(id);
	Main::console->error(e);
	log.error(e);

	return ms<Skill>(getEngine(), id);
}

sp<GameString> EventManager::getGameStringByIDCreateIfNotExist(int id)
{ //=========================================================================================================================

	for (int i = 0; i < gameStringList.size(); i++)
	{
		sp<GameString> s = gameStringList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return ms<GameString>(getEngine(), id);
}

sp<Flag> EventManager::getFlagByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < flagList.size(); i++)
	{
		sp<Flag> s = flagList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return ms<Flag>(getEngine(), id);
}

