//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class RamioBrickBlock : public RamioBlock
{
public:

	static Logger log;


	RamioBrickBlock(sp<Engine> g);


	int open = 0;
	int contains = 0;


	void getHit();
};

