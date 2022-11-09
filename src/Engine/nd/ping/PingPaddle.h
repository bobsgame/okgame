//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class PingPaddle : public EnginePart
{
public:

	static Logger log;


	static int h;
	static int w;

	//Texture texture;

	float x = 0;
	float y = 0;

	//float speed;

	bool selected = false;


	PingPaddle(sp<Engine> g);


	void update();


	void render();


	float left();

	float right();

	float top();

	float bottom();

	float middleX();

	float middleY();
};

