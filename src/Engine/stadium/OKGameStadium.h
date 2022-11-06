//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "StadiumScreen.h"

class StadiumScreen;

class OKGameStadium : public OKGame
{
private:
	typedef OKGame super;
public:
	static Logger log;

	shared_ptr<StadiumScreen> stadiumScreen = nullptr;
	shared_ptr<Area> area = nullptr;


	OKGameStadium();
	~OKGameStadium();
	void init() override;
	OKGameStadium(shared_ptr<StadiumScreen> stadiumScreen, shared_ptr<Area> area);


	virtual void shakeSmall() override;
	virtual void shakeHard() override;

	virtual void titleMenuUpdate() override;

	virtual void tryToCloseGame() override;

	

};

