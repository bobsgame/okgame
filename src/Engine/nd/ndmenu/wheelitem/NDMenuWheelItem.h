//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class NDMenuWheelItem : public EnginePart
{
public:

	static Logger log;


	static sp<OKTexture> wheelItemBackgroundTexture;
	static sp<OKTexture> wheelItemGlossyOverlayTexture;

	static int firstCartY; //((getViewportHeight()/2)-(wheelItemHeight/2));

	static int wheelItemHeight; //40;//37;//48;//cart_SURFACE->h; //size of cart image
	static int wheelItemLabelOffsetX; //where the label "container" starts inside the cart png
	static int wheelItemLabelOffsetY; //13;//where the label "container" starts inside the cart png


	float x = 0;
	float y = 0;

	//public Texture labelTexture = null;
	//public Texture labelGlowTexture = null;

	int slot = 0;
	string name = "";

	sp<NDGameEngine> game = nullptr;

	sp<OKColor> color = OKColor::black;


	sp<Caption> caption = nullptr;


	NDMenuWheelItem(sp<Engine> g, sp<NDGameEngine> game, const string& name, sp<OKColor> color);


	float top();

	float middleY();

	float bottom();

	void render(bool isSelected);
};

