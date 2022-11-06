//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class ServersHaveShutDownState : public Engine
{
public:

	static Logger log;


	ServersHaveShutDownState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

