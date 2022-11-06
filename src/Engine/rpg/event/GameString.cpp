#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger GameString::log = Logger("GameString");


GameString::GameString(shared_ptr<Engine> g, int id)
{ //=========================================================================================================================
	this->e = g;

	this->data = make_shared<GameStringData>(id, "", "");

	for (int i = 0; i < (int)getEventManager()->gameStringList.size(); i++)
	{
		if (getEventManager()->gameStringList.get(i)->getID() == data->getID())
		{
			log.error("GameString already exists:" + data->getName());
			return;
		}
	}
	getEventManager()->gameStringList.add(this);
}

GameString::GameString(shared_ptr<Engine> g, shared_ptr<GameStringData> data)
{ //=========================================================================================================================
	this->e = g;

	this->data = data;
	setInitialized_S(true);

	for (int i = 0; i < (int)getEventManager()->gameStringList.size(); i++)
	{
		if (getEventManager()->gameStringList.get(i)->getID() == data->getID())
		{
			log.error("GameString already exists:" + data->getName());
			return;
		}
	}
	getEventManager()->gameStringList.add(this);
}

//The following method was originally marked 'synchronized':
void GameString::setData_S(shared_ptr<GameStringData> data)
{ //=========================================================================================================================
	this->data = data;
	setInitialized_S(true);
}

shared_ptr<GameStringData> GameString::getData()
{
	return data;
}

int GameString::getID()
{
	return getData()->getID();
}


string& GameString::getName()
{
	return getData()->getName();
}


string& GameString::text()
{
	return getData()->getText();
}


string GameString::getTYPEIDString()
{
	return getData()->getTYPEIDString();
}

void GameString::id(int id)
{
	getData()->setID(id);
}

void GameString::setName(const string& name)
{
	getData()->setName(name);
}

void GameString::text(const string& text)
{
	getData()->setText(text);
}

