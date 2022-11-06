//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
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

	shared_ptr<OKColor> pausedFGColor = OKColor::darkGray;
	shared_ptr<OKColor> pausedAAColor = OKColor::gray;
	shared_ptr<OKColor> pausedBGColor = OKColor::lightGray;

	shared_ptr<OKColor> fastFGColor = OKColor::darkerBlue;
	shared_ptr<OKColor> fastAAColor = OKColor::darkBlue;
	shared_ptr<OKColor> fastBGColor = OKColor::blue;

	shared_ptr<OKColor> unknownFGColor = OKColor::white;
	shared_ptr<OKColor> unknownAAColor = OKColor::lightGray;
	shared_ptr<OKColor> unknownBGColor = OKColor::black;

	void setPausedColor();

	void setUnknownColor();

	void setFastColor();

	void setColors(shared_ptr<OKColor> fg, shared_ptr<OKColor> aa, shared_ptr<OKColor> bg) override;
};

