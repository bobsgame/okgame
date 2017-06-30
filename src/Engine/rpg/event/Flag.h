//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




#include "src/Engine/network/ServerObject.h"

class FlagData;

class Flag : public ServerObject
{
private:
	bool value = false;
	long long timeSet = -1;

	FlagData* data = nullptr;


public:


	static Logger log;
	Flag(Engine* g, int id);


	Flag(Engine* g, FlagData* data);


	//The following method was originally marked 'synchronized':
	void setData_S(FlagData* data);


	FlagData* getData();


	int getID();
	string& getName();
	string getTYPEIDString();


	void setID(int id);
	void setName(const string& name);


	//The following method was originally marked 'synchronized':
	void setValue_S(bool b); //sendServerValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	void initValueFromGameSave_S(bool b, long long timeSet); //sendServerValueUpdate(boolean b)


	//The following method was originally marked 'synchronized':
	bool getValue_S();


	long long getTimeSet();
};

