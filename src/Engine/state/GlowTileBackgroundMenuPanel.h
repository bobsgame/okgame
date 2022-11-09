//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class GlowTileBackgroundMenuPanel : public MenuPanel
{
public:

	static Logger log;


	sp<Engine> e = nullptr;


public:
	class GlowTile
	{
	private:
		sp<GlowTileBackgroundMenuPanel> outerInstance = nullptr;

	public:
		GlowTile(sp<GlowTileBackgroundMenuPanel> outerInstance);

		int tileX = 0;
		int tileY = 0;
		int frame = 0;
		long long ticks = 0; //=1000+Utils.randUpToIncluding(5000);
		bool started = false;
	};

public:
	vector<sp<GlowTile>> glowTiles;// = ms<ArrayList><sp<GlowTile>>();
	vector<sp<OKTexture>> glowTileFramesTexture;// = ms<ArrayList><sp<OKTexture>>();
	sp<OKTexture> bgScrollTexture = nullptr;
	float bgScrollX = 0;
	float bgScrollY = 0;
	long long ticksPassed = 0;


	int filter = GLUtils::FILTER_LINEAR;


	//must set these in init()
	int tileFrames = 0;
	int numActiveTiles = 0;
	float scale = 0;
	int ticksPerFrame = 0;
	float scrollSpeedTicksMultiplier = 0;


	GlowTileBackgroundMenuPanel();


	GlowTileBackgroundMenuPanel(sp<Engine> g);


	virtual void init();


	void cleanup();


	virtual void update() override;


	virtual void render() override;
};

