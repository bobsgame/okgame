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


	shared_ptr<Caption> RAMIO_timercaption = nullptr;

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


	ArrayList<shared_ptr<RamioOKa>> bobas;// = make_shared<ArrayList><shared_ptr<RamioOKa>>();
	ArrayList<shared_ptr<RamioBrickBlock>> brickBlocks;/// = make_shared<ArrayList><shared_ptr<RamioBrickBlock>>();
	ArrayList<shared_ptr<RamioMoneyBlock>> moneyBlocks;// = make_shared<ArrayList><shared_ptr<RamioMoneyBlock>>();


	shared_ptr<RamioGuy> guy = nullptr;


	void updateScore();


	bool checkHit(int dir);


	void initGame();


	void doWinSequence();


	void doDeathSequence();


	shared_ptr<ConsoleText> ramioText = Main::console->add("ramioText", OKColor::green);

	virtual void update() override;


	virtual void render() override;
};

