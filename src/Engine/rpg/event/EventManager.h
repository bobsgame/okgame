//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;


class GameString;
class Flag;
class Skill;
class Item;

class EventManager : public EnginePart
{
public:

	static Logger log;

	//ArrayList<shared_ptr<Event>> cutsceneEventList;//project events and unattached events
	ArrayList<shared_ptr<Event>> eventList;//all events get put here for global lookup
	ArrayList<shared_ptr<Dialogue>> dialogueList;
	ArrayList<shared_ptr<GameString>> gameStringList;
	ArrayList<shared_ptr<Flag>> flagList;
	ArrayList<shared_ptr<Skill>> skillList;
	ArrayList<shared_ptr<Item>> itemList;

	ArrayList<shared_ptr<Event>> runningEventQueue;

	EventManager(shared_ptr<Engine> g);


	void update();

	void addToEventQueueIfNotThere(shared_ptr<Event> event);

	bool isEventInQueue(shared_ptr<Event> event);

	void unloadCurrentMapEvents();

	shared_ptr<Item> getItemByID(int id);

	shared_ptr<Dialogue> getDialogueByIDCreateIfNotExist(int id);

	//shared_ptr<Event> getCutsceneEventByID(int id);
	shared_ptr<Event> getEventByIDCreateIfNotExist(int id);

	shared_ptr<Skill> getSkillByIDCreateIfNotExist(int id);

	shared_ptr<GameString> getGameStringByIDCreateIfNotExist(int id);

	shared_ptr<Flag> getFlagByIDCreateIfNotExist(int id);
};

