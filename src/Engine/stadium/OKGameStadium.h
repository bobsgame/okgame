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

	sp<StadiumScreen> stadiumScreen = nullptr;
	sp<Area> area = nullptr;


	OKGameStadium();
	~OKGameStadium();
	void init() override;
	OKGameStadium(sp<StadiumScreen> stadiumScreen, sp<Area> area);


	virtual void shakeSmall() override;
	virtual void shakeHard() override;

	virtual void titleMenuUpdate() override;

	virtual void tryToCloseGame() override;

	

};

