//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;






class LogoState : public Engine
{
public:

	static Logger log;


	//GUI* loginScreenGUI = nullptr;
	//sp<LoginScreen> loginScreen = nullptr;


	int frame = 0;
	int ticks = 0;

	int count = 0;

	sp<OKTexture> logo = nullptr;
	sp<OKTexture> gradient = nullptr;

	long long totalTicksPassed = 0;
	long long ticksToShow = 2000;

	LogoState();


	virtual void update() override;


	virtual void render() override;


	virtual void cleanup() override;
};



