//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "StadiumScreen.h"

class StadiumScreen;

class BobsGameStadium : public BobsGame
{
private:
	typedef BobsGame super;
public:
	static Logger log;

	shared_ptr<StadiumScreen> stadiumScreen = nullptr;
	shared_ptr<Area> area = nullptr;


	BobsGameStadium();
	~BobsGameStadium();
	void init() override;
	BobsGameStadium(shared_ptr<StadiumScreen> stadiumScreen, shared_ptr<Area> area);


	virtual void shakeSmall() override;
	virtual void shakeHard() override;

	virtual void titleMenuUpdate() override;

	virtual void tryToCloseGame() override;

	

};

