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


	//ArrayList<Event*> cutsceneEventList;//project events and unattached events
	ArrayList<Event*> eventList;//all events get put here for global lookup
	ArrayList<Dialogue*> dialogueList;
	ArrayList<GameString*> gameStringList;
	ArrayList<Flag*> flagList;
	ArrayList<Skill*> skillList;
	ArrayList<Item*> itemList;


	ArrayList<Event*> runningEventQueue;


	EventManager(Engine* g);



	virtual void update();


	virtual void addToEventQueueIfNotThere(Event* event);


	virtual bool isEventInQueue(Event* event);


	virtual void unloadCurrentMapEvents();


	virtual Item* getItemByID(int id);


	virtual Dialogue* getDialogueByIDCreateIfNotExist(int id);


	//virtual Event* getCutsceneEventByID(int id);
	virtual Event* getEventByIDCreateIfNotExist(int id);


	virtual Skill* getSkillByIDCreateIfNotExist(int id);


	virtual GameString* getGameStringByIDCreateIfNotExist(int id);


	virtual Flag* getFlagByIDCreateIfNotExist(int id);
};

