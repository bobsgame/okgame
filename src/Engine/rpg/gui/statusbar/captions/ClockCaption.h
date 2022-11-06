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

	ClockCaption(shared_ptr<BGClientEngine> g);

	virtual void init() override;

	virtual void update() override;

	void setDarkTheme();

	void setLightTheme();

	shared_ptr<BobColor> pausedFGColor = BobColor::darkGray;
	shared_ptr<BobColor> pausedAAColor = BobColor::gray;
	shared_ptr<BobColor> pausedBGColor = BobColor::lightGray;

	shared_ptr<BobColor> fastFGColor = BobColor::darkerBlue;
	shared_ptr<BobColor> fastAAColor = BobColor::darkBlue;
	shared_ptr<BobColor> fastBGColor = BobColor::blue;

	shared_ptr<BobColor> unknownFGColor = BobColor::white;
	shared_ptr<BobColor> unknownAAColor = BobColor::lightGray;
	shared_ptr<BobColor> unknownBGColor = BobColor::black;

	void setPausedColor();

	void setUnknownColor();

	void setFastColor();

	void setColors(shared_ptr<BobColor> fg, shared_ptr<BobColor> aa, shared_ptr<BobColor> bg) override;
};

