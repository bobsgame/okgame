
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger NDMenuBackground::log = Logger("NDMenuBackground");


NDMenuBackground::NDMenuBackground(sp<Engine> g)
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

	//glowTileFramesTexture = ms<vector><sp<Texture>>();
	for (int i = 0; i < tileFrames; i++)
	{
		glowTileFramesTexture->push_back(GLUtils::getTextureFromPNGExePath("data/guiBackground/nDmenu/" + to_string(i) + ".png"));
	}

	glowTiles->clear();

	for (int i = 0; i < numActiveTiles; i++)
	{
		glowTiles->push_back(ms<GlowTileBackgroundMenuPanel::GlowTile>(shared_from_this()));
	}

	glowTiles->at(0)->started = true;
}

