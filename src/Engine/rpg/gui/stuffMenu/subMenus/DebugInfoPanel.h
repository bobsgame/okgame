//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class DebugInfoPanel : public SubPanel
{
public:

	static Logger log;


	//static ArrayList<sp<Label>> label;

	//static DialogLayout::Group* horizontalGroup;
	//static DialogLayout::Group* verticalGroup;


	DebugInfoPanel();

	long long updateTicks = 0;


	virtual void update() override;
};

