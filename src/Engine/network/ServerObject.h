//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;

#include "../EnginePart.h"

class Logger;

class ServerObject : public EnginePart
{
public:

	static Logger log;
	ServerObject();
	ServerObject(Engine* g);

protected:
	bool _initialized = false;
	long long lastTimeRequestedFromServer = 0;

public:
	//The following method was originally marked 'synchronized':
	bool getInitialized_S();

public:
	//The following method was originally marked 'synchronized':
	void setInitialized_S(bool i);

private:
	virtual void sendServerRequest();

protected:
	bool loadedInfoDataFromServer = false; //non-threaded check
	long long lastCheckedInitializedTime = 0;

	bool getLoadedFromServerSendRequestIfFalse();

public:
	virtual void update();
};

