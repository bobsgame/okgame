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


	//ArrayList<shared_ptr<Label>> buttonValueLabel;


	ControlsPanel();

private:
	class WidgetAnonymousInnerClassHelper// : public Widget
	{
	private:
		shared_ptr<ControlsPanel> outerInstance = nullptr;

	public:
		WidgetAnonymousInnerClassHelper(shared_ptr<ControlsPanel> outerInstance);

		void layout();
	};


public:
	void setButton(int index, int value);
};

