//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;



class EasingTest : public EnginePart
{
public:
	static sp<Caption> linearTweenCaption;

	static sp<Caption> easeInQuadCaption;
	static sp<Caption> easeInCubicCaption;
	static sp<Caption> easeInQuartCaption;
	static sp<Caption> easeInQuintCaption;
	static sp<Caption> easeInExpoCaption;
	static sp<Caption> easeInCircCaption;
	static sp<Caption> easeInSineCaption;

	static sp<Caption> easeOutQuadCaption;
	static sp<Caption> easeOutCubicCaption;
	static sp<Caption> easeOutQuartCaption;
	static sp<Caption> easeOutQuintCaption;
	static sp<Caption> easeOutExpoCaption;
	static sp<Caption> easeOutCircCaption;
	static sp<Caption> easeOutSineCaption;

	static sp<Caption> easeInOutQuadCaption;
	static sp<Caption> easeInOutCubicCaption;
	static sp<Caption> easeInOutQuartCaption;
	static sp<Caption> easeInOutQuintCaption;
	static sp<Caption> easeInOutExpoCaption;
	static sp<Caption> easeInOutCircCaption;
	static sp<Caption> easeInOutSineCaption;


	EasingTest(sp<Engine> g);


	static float ticksCount;
	static float duration;
	static float beginningValue;
	static float changeInValue;

	void update();
};

