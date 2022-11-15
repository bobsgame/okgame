//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class EventParameter;


class EventCommand : public EnginePart, public std::enable_shared_from_this<EventCommand>
{
public:

	static Logger log;


	string commandString = "";


	int type = -1;
	static int TYPE_COMMAND;
	static int TYPE_QUALIFIER_TRUE;
	static int TYPE_QUALIFIER_FALSE;


	sp<vector<sp<EventParameter>>>parameterList;// = ms<vector><sp<EventParameter>>();

	sp<EventCommand> parent = nullptr;


	sp<vector<sp<EventCommand>>>children;// = ms<vector><sp<EventCommand>>();


	EventCommand(sp<Engine> g, const string& command, sp<vector<sp<EventParameter>>>&parameterList, int type);

	int getNumParams();


	static sp<EventCommand> parseEventCommandFromCommandString(sp<Engine> g, sp<Event> event, string commandString);


	sp<EventCommand> getParent();


	void addChild(sp<EventCommand> e);


	int currentChildIndex = 0;


	sp<EventCommand> getNextChild();
};

