//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;

#include "../../../../map/Light.h"

class StatusBarCaption : public EnginePart
{
public:

	static Logger log;

	sp<Caption> caption = nullptr;
	sp<Light> light = nullptr;

	sp<OKColor> defaultFGColor = OKColor::white;
	sp<OKColor> defaultAAColor = OKColor::darkerGray;
	sp<OKColor> defaultBGColor = OKColor::clear;

	sp<OKColor> currentFGColor = OKColor::white;
	sp<OKColor> currentAAColor = OKColor::darkerGray;
	sp<OKColor> currentBGColor = OKColor::clear;

	bool enabled = true;

	StatusBarCaption();
	StatusBarCaption(sp<BGClientEngine> g);

	void setEnabled(bool b);

	virtual void init();

	virtual void update();

	virtual void render(int layer);

	void updateCaption(const string& s);

	virtual void setColors(sp<OKColor> fg, sp<OKColor> aa, sp<OKColor> bg);

	void setDefaultColor();
};

