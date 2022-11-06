//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




#include "../MiniGameEngine.h"
#include "GameDataLoader.h"

class ND;

class OKTexture;
class Caption;

class NDGameEngine : public MiniGameEngine
{
private:
	typedef MiniGameEngine super;
public:
	static Logger log;

protected:
	ND* nD = nullptr;


public:
	
	NDGameEngine();
	~NDGameEngine();
	NDGameEngine(ND* nD);
	void init() override;

	void tryToCloseGame() override;

};

