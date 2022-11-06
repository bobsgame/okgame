//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class DayCaption : public StatusBarCaption
{
public:

	static Logger log;


	DayCaption(shared_ptr<BGClientEngine> g);


	virtual void init() override;


	virtual void update() override;


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


	void setFastSpeedColor();
};

