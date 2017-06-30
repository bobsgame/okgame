//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "StatusBarCaption.h"


class ClockCaption : public StatusBarCaption
{
public:

	static Logger log;


	ClockCaption(BGClientEngine* g);


	virtual void init() override;


	virtual void update() override;


	void setDarkTheme();

	void setLightTheme();


	BobColor* pausedFGColor = BobColor::darkGray;
	BobColor* pausedAAColor = BobColor::gray;
	BobColor* pausedBGColor = BobColor::lightGray;

	BobColor* fastFGColor = BobColor::darkerBlue;
	BobColor* fastAAColor = BobColor::darkBlue;
	BobColor* fastBGColor = BobColor::blue;

	BobColor* unknownFGColor = BobColor::white;
	BobColor* unknownAAColor = BobColor::lightGray;
	BobColor* unknownBGColor = BobColor::black;


	void setPausedColor();


	void setUnknownColor();


	void setFastColor();


	void setColors(BobColor* fg, BobColor* aa, BobColor* bg);
};

