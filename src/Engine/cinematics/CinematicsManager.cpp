#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger CinematicsManager::log = Logger("CinematicsManager");


CinematicsManager::CinematicsManager(sp<Engine> g)
{ //=========================================================================================================================

	this->e = g;

	screenOverlayOverLights = ms<ScreenOverlay>(g);
	screenOverlayUnderLights = ms<ScreenOverlay>(g);
	screenOverlayGroundLayer = ms<ScreenOverlay>(g);

	letterbox = ms<Letterbox>(g);
}

void CinematicsManager::init()
{ //=========================================================================================================================

	//log->debug("Init CinematicsManager");

	screenOverlayOverLights->init();
	screenOverlayUnderLights->init();
	screenOverlayGroundLayer->init();


	letterbox->init();
}

void CinematicsManager::update()
{ //=========================================================================================================================
	letterbox->update();

	screenOverlayOverLights->update();
	screenOverlayUnderLights->update();
	screenOverlayGroundLayer->update();
}

void CinematicsManager::render(RenderOrder renderOrder)
{ //=========================================================================================================================
	if (renderOrder == RenderOrder::GROUND)
	{
		screenOverlayGroundLayer->render();
	}

	if (renderOrder == RenderOrder::ABOVE)
	{
		screenOverlayUnderLights->render();
	}

	if (renderOrder == RenderOrder::ABOVE_TOP)
	{
		letterbox->render();
		screenOverlayOverLights->render();
	}
}

void CinematicsManager::setLetterbox(bool on, int slideDurationTicks, int size)
{ //=========================================================================================================================
	if (on == true)
	{
		letterbox->setOn(slideDurationTicks, size);
	}
	else
	{
		letterbox->setOff(slideDurationTicks);
	}
}

void CinematicsManager::setLetterbox(bool on, int slideDurationTicks, float sizePercent)
{ //=========================================================================================================================
	if (on == true)
	{
		letterbox->setOn(slideDurationTicks, sizePercent);
	}
	else
	{
		letterbox->setOff(slideDurationTicks);
	}
}

void CinematicsManager::fadeToWhite(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(OKColor::white, 0.0f, 1.0f, ticks);
}

void CinematicsManager::fadeFromWhite(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(OKColor::white, 1.0f, 0.0f, ticks);
}

void CinematicsManager::fadeToBlack(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(OKColor::black, 0.0f, 1.0f, ticks);
}

void CinematicsManager::fadeFromBlack(int ticks)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(OKColor::black, 1.0f, 0.0f, ticks);
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlpha(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(ms<OKColor>(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::fadeColorFromAlphaToAlpha(int ticks, u8 ri, u8 gi, u8 bi, float fromAlpha, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doTransition(ms<OKColor>(ri, gi, bi), fromAlpha, toAlpha, ticks);
}

void CinematicsManager::fadeColorFromTransparentToAlphaBackToTransparent(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayOverLights->doToAndFromTransition(ms<OKColor>(ri, gi, bi), ticks, toAlpha);
}

void CinematicsManager::setInstantOverlayColor(u8 ri, u8 gi, u8 bi, float a)
{ //=========================================================================================================================
	screenOverlayOverLights->setInstantOverlay(ms<OKColor>(ri, gi, bi), a);
}

void CinematicsManager::clearOverlay()
{ //=========================================================================================================================
	screenOverlayOverLights->clearOverlays();
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlphaUnderLights(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayUnderLights->doTransition(ms<OKColor>(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::setInstantOverlayColorUnderLights(u8 ri, u8 gi, u8 bi, float af)
{ //=========================================================================================================================
	screenOverlayUnderLights->setInstantOverlay(ms<OKColor>(ri, gi, bi), af);
}

void CinematicsManager::clearOverlayUnderLights()
{ //=========================================================================================================================
	screenOverlayUnderLights->clearOverlays();
}

void CinematicsManager::fadeColorFromCurrentAlphaToAlphaGroundLayer(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha)
{ //=========================================================================================================================
	screenOverlayGroundLayer->doTransition(ms<OKColor>(ri, gi, bi), -1, toAlpha, ticks);
}

void CinematicsManager::setInstantOverlayColorGroundLayer(u8 ri, u8 gi, u8 bi, float af)
{ //=========================================================================================================================
	screenOverlayGroundLayer->setInstantOverlay(ms<OKColor>(ri, gi, bi), af);
}

void CinematicsManager::clearOverlayGroundLayer()
{ //=========================================================================================================================
	screenOverlayGroundLayer->clearOverlays();
}

void CinematicsManager::set8BitMode(bool b)
{ //=========================================================================================================================
	getMapManager()->effects8Bit = b;
}

void CinematicsManager::setInvertedColors(bool b)
{ //=========================================================================================================================
	getMapManager()->effectsInverted = b;
}

void CinematicsManager::setBlackAndWhite(bool b)
{ //=========================================================================================================================
	getMapManager()->effectsBlackAndWhite = b;
}

void CinematicsManager::setRotate(bool b)
{ //=========================================================================================================================

	//rotate in a "swing" fashion, back and forth
	//getMapManager()->swingBackAndForth(ticksDuration, maxDegrees, ticksBetweenSwing);

	//rotate in a spiral
	//getMapManager()->rotateInSpiral(ticksDuration, maxDegrees, ticksBetweenSwing);
}

void CinematicsManager::setHBlankWave(bool b)
{ //=========================================================================================================================
	//do this with an FBO
}

void CinematicsManager::setMosaic(bool b)
{ //=========================================================================================================================

	//getMapManager()->mosaicEffect(ticksDuration, maxMosaicSize);

	//TODO: make event for this
}

void CinematicsManager::setBlur(bool b)
{ //=========================================================================================================================

	//getMapManager()->blurEffect(ticksDuration,maxBlurStrength);

	//TODO: make event for this

	//blur on/off
	//blur DURATION
}

void CinematicsManager::openEyes(int ticksDuration)
{ //=========================================================================================================================
	//blur and letterbox

	//TODO: make event for this
}

void CinematicsManager::closeEyes(int ticksDuration)
{ //=========================================================================================================================
	//blur and letterbox

	//TODO: make event for this
}

void CinematicsManager::shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(int ticksDuration, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	getCameraman()->setShakeScreen(ticksDuration, maxX, maxY, ticksPerShake);
}

void CinematicsManager::shakeScreenForTicksDurationConstantRateEasingBetweenShakes(bool onOff, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	//getCameraman()->setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

	//TODO: make event for this
}

void CinematicsManager::shakeScreenOnOffConstantRateEasingBetweenShakesMustTurnOff(bool onOff, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================
	//getCameraman()->setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

	//TODO: make event for this
}

void CinematicsManager::setGameSpeed(float multiplier)
{ //=========================================================================================================================

	//TODO: make event for this
}

