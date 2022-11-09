//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class RamioGuy;

class RamioOKa : public Entity
{
public:

	static Logger log;


	RamioOKa(sp<Engine> g);


	bool dead = false;


	bool checkHitLayerBlocksAndOtherOKas(int dir);


	virtual void update() override;


	bool checkStomp(sp<RamioGuy> guy);


	bool checkRunningInto(sp<RamioGuy> guy);
};

