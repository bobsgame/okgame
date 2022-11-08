#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger Flag::log = Logger("Flag");


Flag::Flag(shared_ptr<Engine> g, int id)
{ //=========================================================================================================================
	this->e = g;

	this->data = make_shared<FlagData>(id, "");

	for (int i = 0; i < (int)getEventManager()->flagList.size(); i++)
	{
		if (getEventManager()->flagList.at(i)->getID() == data->getID())
		{
			log.error("Flag already exists:" + data->getName());
			return;
		}
	}
	getEventManager()->flagList.push_back(shared_from_this());

	//we don't particularly need to know what the actual flag name is... ID is fine.
	//so, don't really care about getting the flag name from the server.
	//it's a good idea for debugging.
}

Flag::Flag(shared_ptr<Engine> g, shared_ptr<FlagData> data)
{ //=========================================================================================================================
	this->e = g;

	this->data = data;
	setInitialized_S(true);

	for (int i = 0; i < (int)getEventManager()->flagList.size(); i++)
	{
		if (getEventManager()->flagList.at(i)->getID() == data->getID())
		{
			log.error("Flag already exists:" + data->getName());
			return;
		}
	}
	getEventManager()->flagList.push_back(shared_from_this());
}

//The following method was originally marked 'synchronized':
void Flag::setData_S(shared_ptr<FlagData> data)
{ //=========================================================================================================================
	this->data = data;
	setInitialized_S(true);
}

shared_ptr<FlagData> Flag::getData()
{
	return data;
}

int Flag::getID()
{
	return getData()->getID();
}


string& Flag::getName()
{
	return getData()->getName();
}


string Flag::getTYPEIDString()
{
	return getData()->getTYPEIDString();
}

void Flag::setID(int id)
{
	getData()->setID(id);
}

void Flag::setName(const string& name)
{
	getData()->setName(name);
}

//The following method was originally marked 'synchronized':
void Flag::setValue_S(bool b)
{ //=========================================================================================================================

	//send a request to the server

	timeSet = System::currentHighResTimer();
	value = b;

	if (b == true)
	{
		getServerConnection()->addQueuedGameSaveUpdateRequest_S("flagsSet:`" + to_string(getID()) + ":true:" + to_string(timeSet) + "`");
	}
	if (b == false)
	{
		getServerConnection()->addQueuedGameSaveUpdateRequest_S("flagsSet:`" + to_string(getID()) + ":false:" + to_string(timeSet) + "`");
	}
}

//The following method was originally marked 'synchronized':
void Flag::initValueFromGameSave_S(bool b, long long timeSet)
{ //=========================================================================================================================

	this->value = b;
	this->timeSet = timeSet;
}

//The following method was originally marked 'synchronized':
bool Flag::getValue_S()
{ //=========================================================================================================================
	return value;
}

long long Flag::getTimeSet()
{ //=========================================================================================================================
	return timeSet;
}

