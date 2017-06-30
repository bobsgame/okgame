//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class ControlsPanel : public SubPanel
{
public:

	static Logger log;


	//ArrayList<Label*> buttonValueLabel;


	ControlsPanel();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		ControlsPanel* outerInstance = nullptr;

	public:
		WidgetAnonymousInnerClassHelper(ControlsPanel* outerInstance);

		void layout();
	};


public:
	void setButton(int index, int value);
};

