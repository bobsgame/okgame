//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Engine/state/StateManager.h"
class Logger;




class ND : public MenuPanel
{
public:

	static Logger log;


	shared_ptr<BobTexture> texture = nullptr;

	float nDDrawAlpha = 1.0f;
	float nDZoom = 0.01f;


	float widthTextureAspectRatio = 0;
	float heightTextureAspectRatio = 0;
	float widthToHeightRatio = 0;


	float widthThisFrame = 0;
	float targetWidth = 0;


	


	shared_ptr<StateManager> nDGameStateManager = nullptr;


	shared_ptr<Light> light = nullptr;
	float lightAlpha = 1.0f;
	bool lightFadeInOutToggle = false;

	float lightFadeSpeedMult = 0.0005f;
	float lightMaxAlpha = 0.75f;
	float lightMinAlpha = 0.70f;


	shared_ptr<ConsoleText> ndZoomText = nullptr;// = Console::debug("ndZoomText");


	long long fadeOutMeshTicks = 0;
	int fadeOutMeshTicksSpeed = 2000;
	bool fadeMesh = true;
	float drawMeshAlpha = 0.5f;


	ND();


	void init();


	virtual void update() override;


	void setGame(shared_ptr<NDGameEngine> game);

	shared_ptr<NDGameEngine> getGame();


	virtual void toggleActivated() override;


	virtual void setActivated(bool b) override;


	virtual void onScrolledUp() override;


	virtual void scrollUp() override; //zoomIn()


	virtual void scrollDown() override; //zoomOut()





	virtual void render() override;


	virtual void layout() override;
};

