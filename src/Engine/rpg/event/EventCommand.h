//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class EventParameter;


class EventCommand : public EnginePart
{
public:

	static Logger log;


	string commandString = "";


	int type = -1;
	static int TYPE_COMMAND;
	static int TYPE_QUALIFIER_TRUE;
	static int TYPE_QUALIFIER_FALSE;


	ArrayList<shared_ptr<EventParameter>> parameterList;// = make_shared<ArrayList><shared_ptr<EventParameter>>();

	shared_ptr<EventCommand> parent = nullptr;


	ArrayList<shared_ptr<EventCommand>> children;// = make_shared<ArrayList><shared_ptr<EventCommand>>();


	EventCommand(shared_ptr<Engine> g, const string& command, ArrayList<shared_ptr<EventParameter>> &parameterList, int type);

	int getNumParams();


	static shared_ptr<EventCommand> parseEventCommandFromCommandString(shared_ptr<Engine> g, shared_ptr<Event> event, string commandString);


	shared_ptr<EventCommand> getParent();


	void addChild(shared_ptr<EventCommand> e);


	int currentChildIndex = 0;


	shared_ptr<EventCommand> getNextChild();
};

