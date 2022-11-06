//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class LoggedOutState : public Engine
{
public:

	static Logger log;

	LoggedOutState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};

