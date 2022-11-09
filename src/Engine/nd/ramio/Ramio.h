//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class Ramio : public NDGameEngine
{
public:

	static Logger log;


	Ramio(ND* nD);


	bool playing = true;
	bool won = false;

	static int timer;
	static int initialTimer;
	static int ticksToAddForMoneyBlock;


	sp<Caption> RAMIO_timercaption = nullptr;

	bool easymode = true;


	int highScore = 142;
	int score = 0;
	bool gotHighScore = false;


	int deadX = 0;
	int deadY = 0;
	bool dead = false;


	bool credits = false;
	bool creditScreenInit = false;
	bool initialized = false;


	long long ticks = 0;


	int winSequenceStep = 0;
	int dieSequenceStep = 0;


	vector<sp<RamioOKa>> bobas;// = ms<ArrayList><sp<RamioOKa>>();
	vector<sp<RamioBrickBlock>> brickBlocks;/// = ms<ArrayList><sp<RamioBrickBlock>>();
	vector<sp<RamioMoneyBlock>> moneyBlocks;// = ms<ArrayList><sp<RamioMoneyBlock>>();


	sp<RamioGuy> guy = nullptr;


	void updateScore();


	bool checkHit(int dir);


	void initGame();


	void doWinSequence();


	void doDeathSequence();


	sp<ConsoleText> ramioText = Main::console->add("ramioText", OKColor::green);

	virtual void update() override;


	virtual void render() override;
};

