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

	ClockCaption(sp<BGClientEngine> g);

	virtual void init() override;

	virtual void update() override;

	void setDarkTheme();

	void setLightTheme();

	sp<OKColor> pausedFGColor = OKColor::darkGray;
	sp<OKColor> pausedAAColor = OKColor::gray;
	sp<OKColor> pausedBGColor = OKColor::lightGray;

	sp<OKColor> fastFGColor = OKColor::darkerBlue;
	sp<OKColor> fastAAColor = OKColor::darkBlue;
	sp<OKColor> fastBGColor = OKColor::blue;

	sp<OKColor> unknownFGColor = OKColor::white;
	sp<OKColor> unknownAAColor = OKColor::lightGray;
	sp<OKColor> unknownBGColor = OKColor::black;

	void setPausedColor();

	void setUnknownColor();

	void setFastColor();

	void setColors(sp<OKColor> fg, sp<OKColor> aa, sp<OKColor> bg) override;
};

