//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;



#include "src/Engine/network/ServerObject.h"


class GameStringData;

class GameString : public ServerObject, public std::enable_shared_from_this<GameString>
{
private:
	sp<GameStringData> data = nullptr;


public:

	static Logger log;
	GameString(sp<Engine> g, int id);


	GameString(sp<Engine> g, sp<GameStringData> data);


	//The following method was originally marked 'synchronized':
	void setData_S(sp<GameStringData> data);


	sp<GameStringData> getData();

	int getID();
	string& getName();
	string& text();

	string getTYPEIDString();

	void id(int id);
	void setName(const string& name);
	void text(const string& text);
};

