//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class Wallet : public EnginePart
{
public:

	static Logger log;


	float money = 19.99f;

	float lastMoney = -1;


	Wallet(sp<BGClientEngine> g);


	void init();


	void update();
};

