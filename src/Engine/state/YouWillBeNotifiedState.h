//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class YouWillBeNotifiedState : public Engine
{
public:

	static Logger log;

	YouWillBeNotifiedState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

