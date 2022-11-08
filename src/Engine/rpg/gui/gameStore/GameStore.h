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


	vector<shared_ptr<GameItem>> games;// = make_shared<ArrayList><shared_ptr<GameItem>>();
	//public GameListPanel gameStorePanel;


	GameStore();


	virtual void setActivated(bool b) override;


	virtual void render() override;
};

