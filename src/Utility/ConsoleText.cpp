
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger ConsoleText::log = Logger("ConsoleText");


shared_ptr<BobColor> ConsoleText::defaultColor = nullptr;
ConsoleText::ConsoleText()
{
	
}

ConsoleText::ConsoleText(const string& s, shared_ptr<BobColor> c, int x, int y, int ticks, bool isDebug)
{ //=========================================================================================================================


	if (defaultColor == nullptr)defaultColor = BobColor::white;

	if (c == nullptr)c = defaultColor;
	
	this->text = s;
	if (c != nullptr)
	{
		this->color = c;
	}
	this->x = x;
	this->y = y;
	this->ticks = ticks;
	this->isDebug = isDebug;
}

float ConsoleText::getWidth()
{
	if (caption != nullptr)
	return caption->getWidth();
	return 0;
}
float ConsoleText::getHeight()
{
	if(caption!=nullptr)
	return caption->getHeight();
	return 0;
}