//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


class Logger;
class Engine;
class EnginePart;
class Letterbox;
class ScreenOverlay;
enum class RenderOrder;


class CinematicsManager : public EnginePart
{
public:

	static Logger log;


	shared_ptr<Letterbox> letterbox = nullptr;
	shared_ptr<ScreenOverlay> screenOverlayOverLights = nullptr;
	shared_ptr<ScreenOverlay> screenOverlayUnderLights = nullptr;
	shared_ptr<ScreenOverlay> screenOverlayGroundLayer = nullptr;


	//TODO: probably want to organize these effects in a linked list or something

	//need a way to make new effects at any time, or maybe could just have a lot of presets?


	//color overlays (screenfade with max opacity)

	//flashes (screenfade with fast speed)


	//screen shake: need to access cameraman, that's it

	//slow motion: need to modulate Game().ticksPassed() per frame, probably


	//lighting
	//shadows on edges of screen
	//do fps hdr light modulation when go indoor/outdoors

	//hdr, color saturation controls, etc

	//eyes closing and opening (+ blur, nice effect)

	//tv blip like android phone

	//mosaic, rotate, etc

	//darkness layer and torch

	//flicker

	//screen wipes


	//ntsc distortion
	//scanlines
	//crosshatch and glow simulate crt pixels

	//use nnedi3/eedi3 scaling?

	//motion blur

	//timeline, show places lived on map, show desk pictures, do metroid like getText intro, show version of game


	//blur: render to small framebuffer, render back to screen with bilinear filter
	//OR: pixel shader
	//how to do this per-layer?
	//should never blur the getText engine probably, unless it's a dizzyness thing

	//lighting effects (grayscale, sepia, filters,etc)
	//will need pixel shader or framebuffer object for these
	//research using pixel shaders, maybe that even needs framebuffer


	//rewind and fast forward


	CinematicsManager(shared_ptr<Engine> g);

	void init();


	void update();


	void render(RenderOrder renderOrder);


	void setLetterbox(bool on, int slideDurationTicks, int size);

	void setLetterbox(bool on, int slideDurationTicks, float sizePercent);


	void fadeToWhite(int ticks);

	void fadeFromWhite(int ticks);


	void fadeToBlack(int ticks);

	void fadeFromBlack(int ticks);


	//	
	//	public void fadeColorFromCurrentAlphaToOpaque(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doTransition(make_shared<Color>(ri,gi,bi),-1,1.0f,ticks);
	//	}
	//	
	//	public void fadeColorFromOpaqueToTransparent(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doTransition(make_shared<Color>(ri,gi,bi),1.0f,0.0f,ticks);
	//	}


	void fadeColorFromCurrentAlphaToAlpha(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha);

	void fadeColorFromAlphaToAlpha(int ticks, u8 ri, u8 gi, u8 bi, float fromAlpha, float toAlpha);

	//	
	//	public void fadeFromTransparentToBlackOpaqueAndBackToTransparent(int ticks)
	//	{
	//		screenOverlay.doToAndFromTransition(Color.black,ticks, 1.0f);
	//	}
	//
	//	
	//	public void fadeFromTransparentToWhiteOpaqueAndBackToTransparent(int ticks)
	//	{
	//		screenOverlay.doToAndFromTransition(Color.white,ticks,1.0f);
	//	}

	//	
	//	public void fadeColorFromTransparentToOpaqueAndBack(int ticks, int ri, int gi, int bi)
	//	{
	//		screenOverlay.doToAndFromTransition(make_shared<Color>(ri,gi,bi),ticks,1.0f);
	//	}

	void fadeColorFromTransparentToAlphaBackToTransparent(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha);
	//	
	//	public void fadeColorFromCurrentAlphaToAlphaBackToCurrentAlpha(int ticks, int ri, int gi, int bi, float getToAlpha)
	//	{
	//		screenOverlay.doToAndFromTransition(make_shared<Color>(ri,gi,bi),ticks, getToAlpha);
	//	}

	void setInstantOverlayColor(u8 ri, u8 gi, u8 bi, float af);


	void clearOverlay();

	//TODO eventually redo overlay system to make disposable events that i can combine, i.e. flash red while fading to black, etc.


	void fadeColorFromCurrentAlphaToAlphaUnderLights(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha);


	void setInstantOverlayColorUnderLights(u8 ri, u8 gi, u8 bi, float af);


	void clearOverlayUnderLights();


	void fadeColorFromCurrentAlphaToAlphaGroundLayer(int ticks, u8 ri, u8 gi, u8 bi, float toAlpha);


	void setInstantOverlayColorGroundLayer(u8 ri, u8 gi, u8 bi, float af);


	void clearOverlayGroundLayer();


	void set8BitMode(bool b);


	void setInvertedColors(bool b);


	void setBlackAndWhite(bool b);


	void setRotate(bool b);


	void setHBlankWave(bool b);


	void setMosaic(bool b);


	void setBlur(bool b);


	void openEyes(int ticksDuration);

	void closeEyes(int ticksDuration);


	void shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(int ticksDuration, int maxX, int maxY, int ticksPerShake);


	void shakeScreenForTicksDurationConstantRateEasingBetweenShakes(bool onOff, int maxX, int maxY, int ticksPerShake);


	void shakeScreenOnOffConstantRateEasingBetweenShakesMustTurnOff(bool onOff, int maxX, int maxY, int ticksPerShake);


	void setGameSpeed(float multiplier);
};

