//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;



class Logger;
class Engine;
class EnginePart;

//TODO: improve speed function for this
//TODO: maybe automatically shut off letterbox if leave room

//TODO: need getters and setters


class Letterbox : public EnginePart
{
	//letterbox

public:
	static Logger log;


private:
	float alpha = 1.0f;


	int sizeY = 0;

	float currentYOffset = 0;

	bool on = false;


	sp<OKColor> color = OKColor::black;

	int ticksSlideDuration = 0;

	long long startTime = System::currentHighResTimer();


	/// <summary>
	/// letterbox takes in size, alpha, and speed.
	/// it will scroll from 0 to size on top and bottom.
	/// speed must be low. 0.1f * ticks(16) * 60fps = 96 pixels per second.
	/// </summary>
public:
	Letterbox(sp<Engine> g);


	void init();


	void setAlpha();

	void setColor();


	void setLayer();


	void setOn(int ticksSlideDuration, float percentY);


	void setOn(int ticksSlideDuration, int sizeY);


	void setOff(int ticksSlideDuration);


	void update();


	void render();
};

