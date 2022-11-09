//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class PingBackground : public EnginePart
{
public:

	static Logger log;


	PingBackground(sp<Engine> g);


	bool tvRolling = false;
	int scrollingBackgroundX = 0;
	bool backgroundShakeDirectionToggle = false;
	bool tvScanlinesColorPulseToggle = false;

	bool backgroundInit = false;
	sp<OKTexture> backgroundTexture = nullptr;
	int screenX = 0;
	int screenY = 0;


	long long pulseTicks = 0;
	long long rollTicks = 0;


	void init();


	void update();


	void render();
};

