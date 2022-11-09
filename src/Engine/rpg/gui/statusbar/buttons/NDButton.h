//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class NDButton : public StatusBarButton
{
public:

	static Logger log;

	NDButton(sp<BGClientEngine> g);

	virtual void init() override;

	virtual void setOffsets() override;

	virtual void clicked() override;

	virtual bool isAssociatedMenuActive() override;
};

