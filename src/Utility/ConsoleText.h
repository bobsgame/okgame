//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;

#include "src/Utility/Color.h"


class Caption;



class ConsoleText
{
public:
	static Logger log;

	shared_ptr<Caption> caption = nullptr;

	bool alwaysOnBottom = false;

	string text = "";

	int x = -1;
	int y = -1;

	int ticks = -1;

	shared_ptr<OKColor> color = nullptr;

	static shared_ptr<OKColor> defaultColor;

	bool isDebug = false;

	ConsoleText();
	ConsoleText(const string& s, shared_ptr<OKColor> c, int x, int y, int ticks, bool isDebug);
	float getWidth();
	float getHeight();
};

