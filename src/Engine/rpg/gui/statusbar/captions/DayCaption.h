//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class DayCaption : public StatusBarCaption
{
public:

	static Logger log;


	DayCaption(sp<BGClientEngine> g);


	virtual void init() override;


	virtual void update() override;


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


	void setFastSpeedColor();
};

