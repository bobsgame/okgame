#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger EventManager::log = Logger("EventManager");

EventManager::EventManager(shared_ptr<Engine> g)
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
		shared_ptr<Event> s = runningEventQueue.at(i);
		s->run();
	}
}

void EventManager::addToEventQueueIfNotThere(shared_ptr<Event> event)
{ //=========================================================================================================================

	if (event->getWasAddedToQueue() == false)
	{
		runningEventQueue.push_back(event);
		event->setAddedToQueue();
	}

	//if it isn't in the event queue, add a fresh stack to the event queue.

	//if it is in the event queue, run the next instruction.
}

bool EventManager::isEventInQueue(shared_ptr<Event> event)
{ //=========================================================================================================================

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		shared_ptr<Event> s = runningEventQueue.at(i);

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
		shared_ptr<Event> s = getCurrentMap()->mapEventList.at(i);// getEventManager()->getEventByID(getCurrentMap()->mapEventIDList.at(i));
		if(s!=nullptr)s->reset();
	}

	for (int i = 0; i < runningEventQueue.size(); i++)
	{
		shared_ptr<Event> s = runningEventQueue.at(i);

		if (s->type() != EventData::TYPE_PROJECT_INITIAL_LOADER && s->type() != EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED)
		{
			s->reset();
			runningEventQueue.removeAt(i);
			i = -1;
		}
	}
}

shared_ptr<Item> EventManager::getItemByID(int id)
{ //=========================================================================================================================
	for (int i = 0; i < itemList.size(); i++)
	{
		shared_ptr<Item> s = itemList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	string e = "Item not found! getItemByID():" + to_string(id);
	Main::console->error(e);
	log->error(e);

	return nullptr;
}

shared_ptr<Dialogue> EventManager::getDialogueByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < dialogueList.size(); i++)
	{
		shared_ptr<Dialogue> d = dialogueList.at(i);
		if (d->getID() == id)
		{
			return d;
		}
	}
	return make_shared<Dialogue>(getEngine(), id);
}

//shared_ptr<Event> EventManager::getCutsceneEventByID(int id)
//{ //=========================================================================================================================
//	//go through list
//	//if event doesn't exist, make new one
//	for (int i = 0; i < cutsceneEventList.size(); i++)
//	{
//		shared_ptr<Event> d = cutsceneEventList.at(i);
//		if (d->getID() == id)
//		{
//			return d;
//		}
//	}
//
//	return nullptr;
//}

shared_ptr<Event> EventManager::getEventByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	//go through list
	//if event doesn't exist, make new one
	for (int i = 0; i < eventList.size(); i++)
	{
		shared_ptr<Event> d = eventList.at(i);
		if (d->getID() == id)
		{
			return d;
		}
	}

	//first of all this should never happen because events are embedded in objects now
	//but i think the object should request the event from the server instead of making an empty event
	//or at least the object should create the event itself so it can be associated with the correct object
	//log->error("Could not find event with ID " + to_string(id));
	shared_ptr<Event> d = make_shared<Event>(getEngine(), make_shared<EventData>(id, "", 0, "", ""), "");
	d->setInitialized_S(false);

	return d;
}

shared_ptr<Skill> EventManager::getSkillByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < skillList.size(); i++)
	{
		shared_ptr<Skill> s = skillList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	//All skills defined in editor should be loaded from /res/SkillData at load, so it should always exist.

	string e = "Skill not found! getSkillByID():" + to_string(id);
	Main::console->error(e);
	log->error(e);

	return make_shared<Skill>(getEngine(), id);
}

shared_ptr<GameString> EventManager::getGameStringByIDCreateIfNotExist(int id)
{ //=========================================================================================================================

	for (int i = 0; i < gameStringList.size(); i++)
	{
		shared_ptr<GameString> s = gameStringList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return make_shared<GameString>(getEngine(), id);
}

shared_ptr<Flag> EventManager::getFlagByIDCreateIfNotExist(int id)
{ //=========================================================================================================================
	for (int i = 0; i < flagList.size(); i++)
	{
		shared_ptr<Flag> s = flagList.at(i);
		if (s->getID() == id)
		{
			return s;
		}
	}

	return make_shared<Flag>(getEngine(), id);
}

