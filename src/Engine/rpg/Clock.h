//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class Clock : public EnginePart
{
public:
	static Logger log;

private:
	bool paused = false;
	bool unknown = false;
	bool fast = false;


public:
	int ticks = 0;
	int second = 0;
	int minute = 0;
	int hour = 0;
	int day = 0;


	Clock(sp<Engine> g);


	void update();


	void setTime(int day, int hour, int minute, int second);


	void updateCaptions();


	void setPaused(bool b);


	void setPausedOn();

	void setPausedOff();


	void setUnknown(bool b);

	void setUnknownOn();

	void setUnknownOff();


	void setFast(bool b);

	void setFastOn();

	void setFastOff();
};

