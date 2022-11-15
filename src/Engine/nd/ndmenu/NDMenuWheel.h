//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;





#include "wheelitem/NDMenuWheelItem.h"


class NDMenuWheel : public EnginePart
{
public:

	static Logger log;


	NDMenuWheel(sp<Engine> g);


	static sp<vector<sp<NDMenuWheelItem>>>wheelItems;


	int selectedWheelItem = 0;
	int wheelSpinDirection = 0; //2;

	int wheelSoundQueue = 0;


	static int CLOCKWISE;
	static int COUNTERCLOCKWISE;


	sp<OKTexture> selectedItemColorSpinTexture[15];


	float cartSlideX = 0;

	int selectionBoxFrame = 0;
	long long selectionBoxTicks = 0;


	long long highlightTicks = 0;
	static float highlightColor;
	int highlightDir = 0;


	bool selectionColorSpinEnabled = true;


	bool wheelSpinning = false;


	void init();


	void addGame(sp<NDGameEngine> game, const string& name, sp<OKColor> color);


	void render();


	void renderGameTitleCentered();

	void renderGameTitleCenteredGlow();


	void spinWheel(int dir);


	void update();
};

