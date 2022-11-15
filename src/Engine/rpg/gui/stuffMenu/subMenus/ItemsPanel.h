//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class ItemsPanel : public SubPanel
{
public:

	static Logger log;


	//sp<vector<sp<DialogLayout>>>itemDialogLayout;

	//DialogLayout::Group* horizontalGroup = nullptr;
	//DialogLayout::Group* verticalGroup = nullptr;


	ItemsPanel();


	void updateItems();


	virtual void layout() override;


	virtual void setVisible(bool b) override;
};

