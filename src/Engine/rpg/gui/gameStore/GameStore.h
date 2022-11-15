//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class GameStore : public MenuPanel
{
public:

	static Logger log;


	sp<vector<sp<GameItem>>>games;// = ms<vector><sp<GameItem>>();
	//public GameListPanel gameStorePanel;


	GameStore();


	virtual void setActivated(bool b) override;


	virtual void render() override;
};

