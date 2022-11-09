//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class ControlsPanel : public SubPanel
{
public:

	static Logger log;


	//ArrayList<sp<Label>> buttonValueLabel;


	ControlsPanel();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		sp<ControlsPanel> outerInstance = nullptr;

	public:
		WidgetAnonymousInnerClassHelper(sp<ControlsPanel> outerInstance);

		void layout();
	};


public:
	void setButton(int index, int value);
};

