
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NDMenuBackground::log = Logger("NDMenuBackground");


NDMenuBackground::NDMenuBackground(Engine* g)
{ //=========================================================================================================================
	this->e = g;
	init();
}

void NDMenuBackground::init()
{ //=========================================================================================================================

	numActiveTiles = 6;
	scale = 0.75f;
	ticksPerFrame = 20;
	scrollSpeedTicksMultiplier = (1.0f / 64.0f);
	filter = GLUtils::FILTER_LINEAR;


	tileFrames = 65; //get from generator tool output


	cleanup();

	bgScrollTexture = GLUtils::getTextureFromPNGExePath("data/guiBackground/nDmenuBG.png");

	//glowTileFramesTexture = new ArrayList<Texture*>();
	for (int i = 0; i < tileFrames; i++)
	{
		glowTileFramesTexture->add(GLUtils::getTextureFromPNGExePath("data/guiBackground/nDmenu/" + to_string(i) + ".png"));
	}

	glowTiles->clear();

	for (int i = 0; i < numActiveTiles; i++)
	{
		glowTiles->add(new GlowTileBackgroundMenuPanel::GlowTile(this));
	}

	glowTiles->get(0)->started = true;
}

