//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "src/Engine/EnginePart.h"


class Logger;

class GameDataLoader : public EnginePart
{
public:
	static Logger log;

	//static shared_ptr<GameDataLoader> gameDataLoader;

	bool debug = false;


	GameDataLoader(shared_ptr<Engine> g);


	void loadGameData();
};

