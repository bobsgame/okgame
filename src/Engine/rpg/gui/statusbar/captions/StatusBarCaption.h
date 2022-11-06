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

	shared_ptr<Caption> caption = nullptr;
	shared_ptr<Light> light = nullptr;

	shared_ptr<OKColor> defaultFGColor = OKColor::white;
	shared_ptr<OKColor> defaultAAColor = OKColor::darkerGray;
	shared_ptr<OKColor> defaultBGColor = OKColor::clear;

	shared_ptr<OKColor> currentFGColor = OKColor::white;
	shared_ptr<OKColor> currentAAColor = OKColor::darkerGray;
	shared_ptr<OKColor> currentBGColor = OKColor::clear;

	bool enabled = true;

	StatusBarCaption();
	StatusBarCaption(shared_ptr<BGClientEngine> g);

	void setEnabled(bool b);

	virtual void init();

	virtual void update();

	virtual void render(int layer);

	void updateCaption(const string& s);

	virtual void setColors(shared_ptr<OKColor> fg, shared_ptr<OKColor> aa, shared_ptr<OKColor> bg);

	void setDefaultColor();
};

