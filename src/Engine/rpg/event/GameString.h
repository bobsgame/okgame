//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;



#include "src/Engine/network/ServerObject.h"


class GameStringData;

class GameString : public ServerObject
{
private:
	shared_ptr<GameStringData> data = nullptr;


public:

	static Logger log;
	GameString(shared_ptr<Engine> g, int id);


	GameString(shared_ptr<Engine> g, shared_ptr<GameStringData> data);


	//The following method was originally marked 'synchronized':
	void setData_S(shared_ptr<GameStringData> data);


	shared_ptr<GameStringData> getData();

	int getID();
	string& getName();
	string& text();

	string getTYPEIDString();

	void id(int id);
	void setName(const string& name);
	void text(const string& text);
};

