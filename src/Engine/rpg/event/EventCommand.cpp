#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger EventCommand::log = Logger("EventCommand");


int EventCommand::TYPE_COMMAND = 0;
int EventCommand::TYPE_QUALIFIER_TRUE = 1;
int EventCommand::TYPE_QUALIFIER_FALSE = 2;

EventCommand::EventCommand(shared_ptr<Engine> g, const string& command, ArrayList<shared_ptr<EventParameter>>* parameterList, int type)
{ //===============================================================================================

	this->e = g;

	this->type = type;

	if(parameterList!=nullptr)this->parameterList = parameterList;

	this->commandString = command;
}

int EventCommand::getNumParams()
{ //===============================================================================================
	if (parameterList->isEmpty())
	{
		return 0;
	}
	else
	{
		return parameterList->size();
	}
}

shared_ptr<EventCommand> EventCommand::parseEventCommandFromCommandString(shared_ptr<Engine> g, shared_ptr<Event> event, string commandString)
{ //===============================================================================================


	//possible commandString getting passed in:

	//doThing
	//doThing()
	//doThing(thing)
	//doThing(thing|thing)
	//ifDoThing == TRUE
	//ifDoThing() == TRUE
	//ifDoThing(thing) == TRUE
	//ifDoThing(thing|thing) == TRUE

	int type = -1;

	shared_ptr<EventCommand> e = nullptr;


	if (commandString.find(" == TRUE") != string::npos)
	{
		type = TYPE_QUALIFIER_TRUE;
		commandString = commandString.substr(0, commandString.find(" == TRUE"));
	}
	else
	{
		if (commandString.find(" == FALSE") != string::npos)
		{
			type = TYPE_QUALIFIER_FALSE;
			commandString = commandString.substr(0, commandString.find(" == FALSE"));
		}
		else
		{
			type = TYPE_COMMAND;
		}
	}

	//now we're left with one of these:
	//doThing
	//doThing()
	//doThing(thing)
	//doThing(thing|thing)


	if (commandString.find("(") != string::npos)
	{
		ArrayList<shared_ptr<EventParameter>>* newParameterList = make_shared<ArrayList><shared_ptr<EventParameter>>();

		string command = commandString.substr(0, commandString.find("("));

		commandString = commandString.substr(commandString.find("(") + 1);

		//commandString now looks like "thing)" or "thing|thing)" or ")"

		while (String::startsWith(commandString, ")") == false)
		{
			if (commandString.find("|") != -1) //commandString looks like thing|thing)
			{
				string parameterString = commandString.substr(0, commandString.find("|"));
				commandString = commandString.substr(commandString.find("|") + 1); //split off parameter and |
				//commandString now looks like "thing)" or "thing|thing)"

				//all parameters looks like THING.ID
				newParameterList->add(make_shared<EventParameter>(g, parameterString));
			}
			else //commandString looks like thing)
			{
				string parameterString = commandString.substr(0, commandString.find(")"));
				commandString = commandString.substr(commandString.find(")")); //split off parameter
				//commandString now looks like ")"

				//all parameters looks like THING.ID
				newParameterList->add(make_shared<EventParameter>(g, parameterString));
			}
		}


		e = make_shared<EventCommand>(g, command, newParameterList, type);
	}
	else
	{
		//it's just doThing

		e = make_shared<EventCommand>(g, commandString, nullptr, type);
	}


	return e;
}

shared_ptr<EventCommand> EventCommand::getParent()
{ //=========================================================================================================================
	return parent;
}

void EventCommand::addChild(shared_ptr<EventCommand> e)
{ //=========================================================================================================================

	children->add(e);
	e->parent = this;
}

shared_ptr<EventCommand> EventCommand::getNextChild()
{ //=========================================================================================================================

	//ROOT
	//ifPlayerInArea TRUE
	//doThing
	//doNextThing
	//ifPlayerInArea FALSE

	//if we are [ROOT], we return [ifPlayerInArea TRUE]
	//if we are [ifPlayerInArea], we return [doThing]
	//if we are [doThing], we return [doNextThing]
	//if we are [doNextThing], we return [ifPlayerInArea FALSE]

	if (currentChildIndex < children->size())
	{
		shared_ptr<EventCommand> e = children->get(currentChildIndex);
		currentChildIndex++;

		return e;
	}
	else
	{
		currentChildIndex = 0;
		if (getParent() != nullptr)
		{
			return getParent()->getNextChild();
		}

		return nullptr;
	}
}

