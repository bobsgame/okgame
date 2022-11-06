//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;



#include "../../Engine/entity/Entity.h"

class Map;
class Entity;
class Engine;
class Area;


class Cameraman : public Entity
{
public:

	static Logger log;


	shared_ptr<Entity> targetEntity = nullptr;

	int lastXTarget = -1;
	int lastYTarget = -1;

	bool ignoreCameraFXBoundaries = false;

	int camstop_tile = 4;
	int tileSize = 16;


	static shared_ptr<ConsoleText> currentSpeedXText;
	static shared_ptr<ConsoleText> currentSpeedYText;


	static shared_ptr<ConsoleText> targetSpeedXText;
	static shared_ptr<ConsoleText> targetSpeedYText;


	int ticksSinceSnapToPlayer = 0;
	int ticksSinceZoomOut = 0;

	float snapSpeedX = 0;
	float snapSpeedY = 0;


	//public float easingDistance = 0;
	//public int easingTicks = 0;
	//public int easingDuration = 2000;
	//public float easingStartX = getX();
	//public float easingStartY = getY();

	int runningZoomTicks = 0;
	int walkingZoomTicks = 0;
	int standingTicks = 0;
	int zoomBackInTicks = 0;

	float walkingTempZoom = 0;
	float runningTempZoom = 0;
	float standingTempZoom = 0;


	int ticksToZoomBackInFromRunningOrWalking = 1000;
	int ticksToWaitBeforeZoomingBackIn = 200;

	int ticksToWaitBeforeZoomingOut = 1000;
	int ticksToZoomOutWhileRunningOrWalking = 1000;

	int ticksToWaitBeforeCenteringOnPlayer = 1000;
	int ticksToCenterOnPlayer = 2000;

	float runningZoom = 1.0f;
	float walkingZoom = 1.5f;

	//TODO: if running outside, zoom out to 1.0f
	//TODO: if walking outside, zoom out to 1.5


	bool autoZoomByPlayerMovementEnabled = true;
	bool zoomManuallyEnabled = true;


	float screenShakeX = 0.0f;
	float screenShakeY = 0.0f;
	int screenShakeTicksPerShake = 0;
	int screenShakeTicksPerShakeXCounter = 0;
	int screenShakeTicksPerShakeYCounter = 0;

	long long shakeScreenStartTime = 0;
	bool shakeScreenLeftRightToggle = false;
	bool shakeScreenUpDownToggle = false;

	int shakeScreenTicksCounter = 0;
	int shakeScreenTicksDuration = 0;
	int screenShakeMaxX = 0;
	int screenShakeMaxY = 0;

	Cameraman(shared_ptr<Engine> g);


	void initCurrentAnimationFromSprite();


	//shared_ptr<Map> getMap();


	shared_ptr<Map> getCurrentMap();


	void render(float alpha);


	float getX();

	float getY();


	void setShakeScreen(int ticksDuration, int maxX, int maxY, int ticksPerShake);


	void updateScreenShake();


	void update();


	static float ZOOMINCREMENT;

	static float MINZOOM; //1.0f;

	static float MAXZOOM;


	float ZOOMto = 2.0f; //0.25f;//2.0f;

	float quickZOOMto = 0.0f; //0.25f;//2.0f;
	float runZOOMto = ZOOMto; //0.25f;//2.0f;


	int ZOOMlock = 0;

private:
	float zoom = 2.0f; //0.25f;//2.0f;


public:
	float speedMultiplier = 0; //TODO

	float popZOOMto = 0.0f;


	float getZoom();
	void setZoomTO(float ZOOMto);


	void setZoomToFitArea(shared_ptr<Area> a);


	void updateZoom();


	void zoomOut();

	void zoomIn();

	void resetZoom();

	void quickZoomOut();

	void quickZoomIn();

	void resetQuickZoom();


	int getXTarget();


	int getYTarget();


	int getMaxCameraBoundaryWidth();


	int getMaxCameraBoundaryHeight();


	int getMapWidthBasedOnCameraBoundsFromEdge();

	int getMapHeightBasedOnCameraBoundsFromEdge();


	void setXYToTarget();


	void setTarget(shared_ptr<Entity> t);


	void setTarget(float mapXPixelsHQ, float mapYPixelsHQ);


	void setTarget(shared_ptr<Area> area);


	void setDummyTarget();


	void setAutoZoomByPlayerMovement(bool b);


	void setPlayerCanZoomManuallyWithKeyboard(bool b);
};

