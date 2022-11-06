//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class Wallet : public EnginePart
{
public:

	static Logger log;


	float money = 19.99f;

	float lastMoney = -1;


	Wallet(shared_ptr<BGClientEngine> g);


	void init();


	void update();
};

