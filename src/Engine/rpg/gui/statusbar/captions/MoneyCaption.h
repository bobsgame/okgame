//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class MoneyCaption : public StatusBarCaption
{
public:

	static Logger log;

	int dividerX = 0;

	MoneyCaption(sp<BGClientEngine> g);

	virtual void init() override;

	virtual void render(int layer) override;

	virtual void update() override;
};

