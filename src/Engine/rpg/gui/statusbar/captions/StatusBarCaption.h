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


	Caption* caption = nullptr;
	Light* light = nullptr;


	BobColor* defaultFGColor = BobColor::white;
	BobColor* defaultAAColor = BobColor::darkerGray;
	BobColor* defaultBGColor = BobColor::clear;


	BobColor* currentFGColor = BobColor::white;
	BobColor* currentAAColor = BobColor::darkerGray;
	BobColor* currentBGColor = BobColor::clear;


	bool enabled = true;


	StatusBarCaption();
	StatusBarCaption(BGClientEngine* g);


	void setEnabled(bool b);


	virtual void init();


	virtual void update();


	virtual void render(int layer);


	void updateCaption(const string& s);


	virtual void setColors(BobColor* fg, BobColor* aa, BobColor* bg);


	void setDefaultColor();
};

