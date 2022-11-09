//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;


class GameString;
class Flag;
class Skill;
class Item;

class EventManager : public EnginePart
{
public:

	static Logger log;

	//vector<sp<Event>> cutsceneEventList;//project events and unattached events
	vector<sp<Event>> eventList;//all events get put here for global lookup
	vector<sp<Dialogue>> dialogueList;
	vector<sp<GameString>> gameStringList;
	vector<sp<Flag>> flagList;
	vector<sp<Skill>> skillList;
	vector<sp<Item>> itemList;
	vector<sp<Event>> runningEventQueue;

	EventManager(sp<Engine> g);


	void update();

	void addToEventQueueIfNotThere(sp<Event> event);

	bool isEventInQueue(sp<Event> event);

	void unloadCurrentMapEvents();

	sp<Item> getItemByID(int id);

	sp<Dialogue> getDialogueByIDCreateIfNotExist(int id);

	//sp<Event> getCutsceneEventByID(int id);
	sp<Event> getEventByIDCreateIfNotExist(int id);

	sp<Skill> getSkillByIDCreateIfNotExist(int id);

	sp<GameString> getGameStringByIDCreateIfNotExist(int id);

	sp<Flag> getFlagByIDCreateIfNotExist(int id);
};

