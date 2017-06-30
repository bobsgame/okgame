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


	RamioBoba(Engine* g);


	bool dead = false;


	bool checkHitLayerBlocksAndOtherBobas(int dir);


	virtual void update() override;


	bool checkStomp(RamioGuy* guy);


	bool checkRunningInto(RamioGuy* guy);
};

