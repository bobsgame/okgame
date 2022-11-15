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

	//sp<vector<sp<Event>>>cutsceneEventList;//project events and unattached events
	sp<vector<sp<Event>>>eventList;//all events get put here for global lookup
	sp<vector<sp<Dialogue>>>dialogueList;
	sp<vector<sp<GameString>>>gameStringList;
	sp<vector<sp<Flag>>>flagList;
	sp<vector<sp<Skill>>>skillList;
	sp<vector<sp<Item>>>itemList;
	sp<vector<sp<Event>>>runningEventQueue;

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

