//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;






class LogoState : public Engine
{
public:

	static Logger log;


	//GUI* loginScreenGUI = nullptr;
	//LoginScreen* loginScreen = nullptr;


	int frame = 0;
	int ticks = 0;

	int count = 0;

	BobTexture* logo = nullptr;
	BobTexture* gradient = nullptr;

	long long totalTicksPassed = 0;
	long long ticksToShow = 2000;

	LogoState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};



