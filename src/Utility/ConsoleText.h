//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;

#include "src/Utility/Color.h"


class Caption;



class ConsoleText
{
public:
	static Logger log;

	Caption* caption = nullptr;

	bool alwaysOnBottom = false;

	string text = "";

	int x = -1;
	int y = -1;

	int ticks = -1;

	BobColor* color = nullptr;

	static BobColor* defaultColor;

	bool isDebug = false;

	ConsoleText();
	ConsoleText(const string& s, BobColor* c, int x, int y, int ticks, bool isDebug);
	float getWidth();
	float getHeight();
};

