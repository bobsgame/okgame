//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



class EasingTest : public EnginePart
{
public:
	static shared_ptr<Caption> linearTweenCaption;

	static shared_ptr<Caption> easeInQuadCaption;
	static shared_ptr<Caption> easeInCubicCaption;
	static shared_ptr<Caption> easeInQuartCaption;
	static shared_ptr<Caption> easeInQuintCaption;
	static shared_ptr<Caption> easeInExpoCaption;
	static shared_ptr<Caption> easeInCircCaption;
	static shared_ptr<Caption> easeInSineCaption;

	static shared_ptr<Caption> easeOutQuadCaption;
	static shared_ptr<Caption> easeOutCubicCaption;
	static shared_ptr<Caption> easeOutQuartCaption;
	static shared_ptr<Caption> easeOutQuintCaption;
	static shared_ptr<Caption> easeOutExpoCaption;
	static shared_ptr<Caption> easeOutCircCaption;
	static shared_ptr<Caption> easeOutSineCaption;

	static shared_ptr<Caption> easeInOutQuadCaption;
	static shared_ptr<Caption> easeInOutCubicCaption;
	static shared_ptr<Caption> easeInOutQuartCaption;
	static shared_ptr<Caption> easeInOutQuintCaption;
	static shared_ptr<Caption> easeInOutExpoCaption;
	static shared_ptr<Caption> easeInOutCircCaption;
	static shared_ptr<Caption> easeInOutSineCaption;


	EasingTest(shared_ptr<Engine> g);


	static float ticksCount;
	static float duration;
	static float beginningValue;
	static float changeInValue;

	void update();
};

