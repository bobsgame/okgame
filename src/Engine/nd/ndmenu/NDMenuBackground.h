//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;





#include "../../state/GlowTileBackgroundMenuPanel.h"


class NDMenuBackground : public GlowTileBackgroundMenuPanel
{
public:

	static Logger log;


	NDMenuBackground(Engine* g);


	virtual void init() override;
};

