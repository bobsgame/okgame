//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;

#include "src/Utility/OKColor.h"


class Caption;



class ConsoleText
{
public:
	static Logger log;

	sp<Caption> caption = nullptr;

	bool alwaysOnBottom = false;

	string text = "";

	int x = -1;
	int y = -1;

	int ticks = -1;

	sp<OKColor> color = nullptr;

	static sp<OKColor> defaultColor;

	bool isDebug = false;

	ConsoleText();
	ConsoleText(const string& s, sp<OKColor> c, int x, int y, int ticks, bool isDebug);
	float getWidth();
	float getHeight();
};

