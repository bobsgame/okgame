//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class StuffButton : public StatusBarButton
{
public:

	static Logger log;


	StuffButton(shared_ptr<BGClientEngine> g);


	virtual void init() override;


	virtual void setOffsets() override;


	virtual void clicked() override;

	virtual bool isAssociatedMenuActive() override;
};

