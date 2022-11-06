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


	RamioOKa(shared_ptr<Engine> g);


	bool dead = false;


	bool checkHitLayerBlocksAndOtherOKas(int dir);


	virtual void update() override;


	bool checkStomp(shared_ptr<RamioGuy> guy);


	bool checkRunningInto(shared_ptr<RamioGuy> guy);
};

