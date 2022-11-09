//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class RamioMoneyBlock : public RamioBlock
{
public:

	static Logger log;


	RamioMoneyBlock(sp<Engine> g);


	bool open = false;
	bool contains = false;


	void getHit();
};

