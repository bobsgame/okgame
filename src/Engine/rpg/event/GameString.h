//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



#include "src/Engine/network/ServerObject.h"


class GameStringData;

class GameString : public ServerObject
{
private:
	GameStringData* data = nullptr;


public:

	static Logger log;
	GameString(Engine* g, int id);


	GameString(Engine* g, GameStringData* data);


	//The following method was originally marked 'synchronized':
	void setData_S(GameStringData* data);


	GameStringData* getData();

	int getID();
	string& getName();
	string& text();

	string getTYPEIDString();

	void id(int id);
	void setName(const string& name);
	void text(const string& text);
};

