//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class RamioGuy;

class RamioBoba : public Entity
{
public:

	static Logger log;


	RamioBoba(shared_ptr<Engine> g);


	bool dead = false;


	bool checkHitLayerBlocksAndOtherBobas(int dir);


	virtual void update() override;


	bool checkStomp(shared_ptr<RamioGuy> guy);


	bool checkRunningInto(shared_ptr<RamioGuy> guy);
};

