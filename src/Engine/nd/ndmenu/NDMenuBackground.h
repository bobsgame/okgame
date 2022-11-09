//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;





#include "../../state/GlowTileBackgroundMenuPanel.h"


class NDMenuBackground : public GlowTileBackgroundMenuPanel
{
public:

	static Logger log;


	NDMenuBackground(sp<Engine> g);


	virtual void init() override;
};

