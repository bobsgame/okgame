#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RamioOKa::log = Logger("RamioOKa");


RamioOKa::RamioOKa(sp<Engine> g)
{ //=========================================================================================================================
	this->e = g;
}

bool RamioOKa::checkHitLayerBlocksAndOtherOKas(int dir)
{
	return false;
}

void RamioOKa::update()
{ //=========================================================================================================================


	if (dead == false)
	{
		//check down
		if (checkHitLayerBlocksAndOtherOKas(DOWN) == false)
		{
			incY();
		}


		if (movementDirection == LEFT)
		{
			//check getHit
			if (checkHitLayerBlocksAndOtherOKas(LEFT) == false)
			{
				//move left
				decX();
			}
			else
			{
				movementDirection = RIGHT;
			}
		}

		if (movementDirection == RIGHT)
		{
			//heck getHit
			if (checkHitLayerBlocksAndOtherOKas(RIGHT) == false)
			{
				//move right
				incX();
			}
			else
			{
				movementDirection = LEFT;
			}
		}
	}


	if (dead == true)
	{
		//set animation to "dead"
		if (getCurrentAnimationName() == "dead" == false)
		{
			setCurrentAnimationByName("dead");
			setAnimateOnceThroughCurrentAnimation();


			//TODO: make setCurrentAnimation
		}
	}
}

bool RamioOKa::checkStomp(sp<RamioGuy> guy)
{
	// int r=rand()%5;
	// if(r==0)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Squish!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
	// if(r==1)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Take that!",FONT_NORMAL_ID,WHITE,BLACK,1,1);
	// if(r==2)CAPTION_make_caption(&yuu_ramio_caption, 1,CAPTION_CENTERED_OVER_SPRITE,PLAYER_npc->screen_y-10,3,"Poor guy.",FONT_NORMAL_ID,WHITE,BLACK,1,1);

	dead = true;
	// play sound
	getAudioManager()->playSound("ramiosplat", 64, 44100, 0);
	// bounce
	RamioGuy::jumping = true;


	return false;
}

bool RamioOKa::checkRunningInto(sp<RamioGuy> guy)
{
	// TODO
	return false;
}

