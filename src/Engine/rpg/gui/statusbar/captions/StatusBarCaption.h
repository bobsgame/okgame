//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;

#include "../../../../map/Light.h"

class StatusBarCaption : public EnginePart
{
public:

	static Logger log;

	shared_ptr<Caption> caption = nullptr;
	shared_ptr<Light> light = nullptr;

	shared_ptr<BobColor> defaultFGColor = BobColor::white;
	shared_ptr<BobColor> defaultAAColor = BobColor::darkerGray;
	shared_ptr<BobColor> defaultBGColor = BobColor::clear;

	shared_ptr<BobColor> currentFGColor = BobColor::white;
	shared_ptr<BobColor> currentAAColor = BobColor::darkerGray;
	shared_ptr<BobColor> currentBGColor = BobColor::clear;

	bool enabled = true;

	StatusBarCaption();
	StatusBarCaption(shared_ptr<BGClientEngine> g);

	void setEnabled(bool b);

	virtual void init();

	virtual void update();

	virtual void render(int layer);

	void updateCaption(const string& s);

	virtual void setColors(shared_ptr<BobColor> fg, shared_ptr<BobColor> aa, shared_ptr<BobColor> bg);

	void setDefaultColor();
};

