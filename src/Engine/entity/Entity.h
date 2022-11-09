//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
#include "../../Utility/OKBool.h"
#include "Sprite.h"
#include "../rpg/event/EventData.h"
class Logger;

class SpriteAnimationSequence;
class EnginePart;
class Engine;
class EntityData;
class MapData;
class Map;
class Area;

class Entity : public EnginePart
{
public:

	static Logger log;

	sp<Map> map = nullptr;

	sp<Event> event = nullptr;

	const static int DOWN;
	const static int UP;
	const static int LEFT;
	const static int RIGHT;
	const static int UPLEFT;
	const static int DOWNRIGHT;
	const static int DOWNLEFT;
	const static int UPRIGHT;

	int SPEED_ACCEL_INCREMENT_AMOUNT = 1;

	//these are ticks per pixel moved
	int ticksPerPixel_CAR = 2;
	int ticksPerPixel_FASTEST = 3;
	int ticksPerPixel_FASTER = 4;
	int ticksPerPixel_FAST = 5;
	int ticksPerPixel_NORMAL = 10;
	int ticksPerPixel_SLOW = 15;
	int ticksPerPixel_SLOWER = 20;
	int ticksPerPixel_SLOWEST = 30;

	int ticksPerPixel_CAMERA_CONVERSATION = 4;
	int ticksPerPixel_CAMERA_STOPPED = 30;// ticksPerPixel_SLOWEST;

	int YUU_WALKING_SPEED_KEYBOARD = 24;
	int YUU_RUNNING_SPEED_KEYBOARD = 3;// ticksPerPixel_FASTEST;
	int YUU_STANDING_SPEED_KEYBOARD = 20;// ticksPerPixel_SLOWER;

	int YUU_WALKING_SPEED_JOYSTICK = 28;
	int YUU_RUNNING_SPEED_JOYSTICK = 3;// ticksPerPixel_FASTEST;
	int YUU_STANDING_SPEED_JOYSTICK = 20;// ticksPerPixel_SLOWER;

	bool disableMovementAnimationForAllEntities = false;
	bool isPlayerBeingDraggedThisFrame = false;
	int numberOfEntitiesPullingPlayerThisFrame = 0;
	bool isWalkingIntoPlayerThisFrame = false;
	bool isWalkingIntoWallThisFrame = false;

	sp<Sprite> sprite = nullptr;

protected:
	sp<EntityData> data = nullptr;

public:
	float mapX = 0;
	float mapY = 0;

	float standJitterX = 0; //used when characters are standing to give them a little extra movement
	float standJitterY = 0;

	float alpha = 1.0f;

	bool draw = false;

private:
	long long animationTicksCounter = 0; // was vbl_animation_timer
	int frameIndexInTexture = 0; //based on current sequence (getAnimDirection()) and currentAnimationFrameInSequence, this is what will be rendered
	sp<SpriteAnimationSequence> currentAnimation = nullptr;

	int ticksBetweenAnimationLoopThisLoop = 0; //for storing random value between loops

public:
	int movementDirection = 0; //was walk_dir

	float* shadowClipPerPixel = nullptr;
	bool clipShadow = false;
	float shadowSize = 0.65f;
	//public float getShadowStart = 0.75f;
	float shadowAlpha = 0.60f;

	long long ticksSinceLastMovement = 0;
public:
	float pixelsToMoveThisFrame = 0;

	bool behaviorEnabled = true;

	vector<string> eventBehaviorList;// = ms<ArrayList><string>(); //TODO: do something with this!
	vector<string> eventTargetTYPEIDList;// = ms<ArrayList><string>(); //TODO: do something with this!

	string currentAreaTYPEIDTarget = "";

private:
	bool deleteWhenAlphaZero = false;

public:
	Entity();
	Entity(sp<Engine> g, sp<Map> m);

	Entity(sp<Engine> g, sp<EntityData> entityData, sp<Map> m);

	void initEntity(sp<EntityData> entityData);

	virtual void initCurrentAnimationFromSprite();

	virtual void update();

	void updateTimers();

	//	
	//	public void addDialogue(String dialogueIDString)
	//	{
	//
	//		int dialogueID = Integer.parseInt(dialogueIDString);
	//
	//		if(dialogueID!=-1)
	//		{
	//
	//			Dialogue d = g.getDialogueByID(dialogueID);
	//
	//			if(d!=null)dialogueList.add(d);
	//			else
	//			dialogueList.add(ms<Dialogue>(dialogueID));
	//
	//		}
	//	}

	virtual void renderDebugBoxes();

	virtual void renderDebugInfo();

	string getCurrentAreaTargetName();

	//	
	//	public void render()
	//	{
	//		render(alpha);
	//		//overrode this so i can send in arbitrary alpha, really only used for fading sprites out with the last map.
	//	}

	virtual void render(float mapAlpha);

	virtual void render(float alpha, sp<OKTexture> texture, sp<OKTexture> shadowTexture);

	virtual sp<Map> getCurrentMap();

	sp<Map> getMap();

	virtual bool shouldDraw();

	bool isWithinScreenBounds();

	//
	//	
	//	public boolean check_collide_fx(int dir)
	//	{
	//
	//		boolean return_this=true;
	//
	//
	//
	//		if(dir==UP)
	//		{
	//			if(
	//				getMap()->get_fx_layer_xy(getLeft()+1,getTop())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX()-1,getTop())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX(),getTop())==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getTop())==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==DOWN)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getLeft()+1,getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX()-1,getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getMiddleX(),getBottom())==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getBottom())==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==LEFT)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getLeft(),getBottom()-1)==0
	//				&&getMap()->get_fx_layer_xy(getLeft(),getBottom()-4)==0
	//			)return_this=false;
	//		}
	//		else
	//		if(dir==RIGHT)
	//		{
	//			if(
	//					getMap()->get_fx_layer_xy(getRight()-1,getBottom()-1)==0
	//				&&getMap()->get_fx_layer_xy(getRight()-1,getBottom()-4)==0
	//			)return_this=false;
	//		}
	//
	//		if(ignore_fx_layer==true)return false;
	//
	//		return return_this;
	//	}

	virtual bool checkHitBoxAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir);

	bool checkMiddlePixelAgainstHitLayerAndNonWalkableEntitiesInDirection(int dir);

	/// 
	/// <summary>
	/// this is used for PATHFINDING so it ignores doors (so sprites can go through doors) and walkable sprites!!
	/// 
	/// </summary>
	bool checkPathBlockedXY(float x, float y);

	bool checkXYAgainstNonWalkableEntities(float x, float y);

	bool checkXYAgainstHitLayerAndNonWalkableEntities(float x, float y);

	bool checkHitBoxAndMovePixelInDirection(int dir); //returns 0 if getHit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )

	bool checkMiddlePixelHitAndMovePixelInDirection(int dir); //returns 0 if getHit wall   ( DOES HIT DETECTION/WALL DETECTION,HIT WITH SPRITE DETECTION )

	void movePixelInDirection(int dir);

	bool ifCanMoveAPixelThisFrameSubtractAndReturnTrue();

	bool canCreateAtXY(float x, float y);

	void setFeetAtMapXY(float mapXPixels2X, float mapYPixels2X);

	int getFrame();

	void setFrame(int f);

protected:
	void resetAnimationTimer();

public:
	bool haveTicksPassedSinceLastAnimated_ResetIfTrue(int ticks);

	sp<SpriteAnimationSequence> getCurrentAnimation();

	void setCurrentAnimation(sp<SpriteAnimationSequence> a);

	void setCurrentAnimationByName(const string& name);

	void setCurrentAnimationByDirection(int dir);

	int getSpriteLastFrame();

	sp<SpriteAnimationSequence> getAnimationBySpriteFrame(int frame);

	void setCurrentAnimationBySpriteFrame(int frame);

	int getCurrentAnimationNumberOfFrames();

	int getCurrentAnimationStartFrame();

	int getCurrentAnimationLastFrame();

	string getCurrentAnimationName();

	int getCurrentFrameOffsetInCurrentAnimation();

	void setFrameOffsetInCurrentAnimation(int frameOffset);

	void setFrameInAllFrames(int frame);

	void selectRandomFrame(int from, int toIncluding);

	void selectRandomFrameInAllFrames();

	void selectRandomFrameInCurrentAnimation();

	void incrementAnimationFrame(int from, int toIncluding); //increments the frame in the current walking direction

	void incrementAnimationFrameInAllFrames(); //increments the frame in the current walking direction

	void incrementAnimationFrameInCurrentAnimation(); //increments the frame in the current walking direction

	void stopAnimation();

	void setAnimateLoopThroughCurrentAnimation();

	void setAnimateLoopThroughAllFrames();

	void setFrameToAllFramesZero();

	void setFrameToCurrentAnimationStart();

	void setAnimateOnceThroughCurrentAnimation();

	void setAnimateOnceThroughAllFrames();

	void doAnimation();

	void setAlphaImmediately(float a);

	void fadeOutAndDelete();

	virtual void deleteFromMapEntityListAndReleaseTexture();

	void addEventBehavior(const string& s);

	//	
	//	public void addBehavior(String s)
	//	{
	//		getBehaviorList().add(s);
	//	}
	//
	//
	//	
	//	public void addConnectionTYPEID(String s)
	//	{
	//		getConnectionTYPEIDList().add(s);
	//	}

	/// <summary>
	/// This gets called repeatedly in events, until it returns a non-null value, at which point the event continues and does not ask again.
	/// This function will continue asking the server for the value, returning null until the server has set the response value.
	/// Upon finding a non-null response value set by the networking thread by a server response, we reset it to null and return that value, ensuring that it is always a fresh copy from the server.
	/// </summary>
	sp<OKBool> checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn();

	void tellServerTalkedToToday();

	float getDistanceFromEntity(sp<Entity> e);

	sp<Entity> findNearestEntity();

	sp<Entity> findNearestEntityInDirection(int dir);

	bool isWalkingIntoEntity(sp<Entity> entity);

	bool isWalkingIntoArea(sp<Area> area);

	bool isEntityHitBoxTouchingMyHitBox(sp<Entity> e);

	bool isNearestEntityHitBoxTouchingMyHitBox();

	bool isAreaCenterTouchingMyHitBox(sp<Area> a);

	bool isAreaBoundaryTouchingMyHitBox(sp<Area> a);

	bool isXYTouchingMyHitBox(float x, float y);

	bool isXYXYTouchingMyHitBox(float left, float top, float right, float bottom);

	bool isAreaBoundaryTouchingMyMiddleXY(sp<Area> a);

	bool isEntityMiddleXYTouchingMyMiddleXY(sp<Entity> e);

	bool isAreaCenterTouchingMyMiddleXY(sp<Area> a);

	bool isXYTouchingMyMiddleXY(float x, float y);

	bool isXYXYTouchingMyMiddleXY(float left, float top, float right, float bottom);

	bool isEntityHitBoxTouchingMyHitBoxByAmount(sp<Entity> e, int amt);

	bool isNearestEntityHitBoxTouchingMyHitBoxByAmount(int amt);

	bool isAreaCenterTouchingMyHitBoxByAmount(sp<Area> a, int amt);

	bool isAreaBoundaryTouchingMyHitBoxByAmount(sp<Area> a, int amt);

	bool isXYTouchingMyHitBoxByAmount(float x, float y, int amt);

	bool isXYXYTouchingMyHitBoxByAmount(float left, float top, float right, float bottom, int amt);

	bool isAreaBoundaryTouchingMyMiddleXYByAmount(sp<Area> a, int amt);

	bool isEntityMiddleXYTouchingMyMiddleXYByAmount(sp<Entity> e, int amt);

	bool isAreaCenterTouchingMyMiddleXYByAmount(sp<Area> a, int amt);

	bool isXYTouchingMyMiddleXYByAmount(float x, float y, int amt);

	bool isXYXYTouchingMyMiddleXYByAmount(float left, float top, float right, float bottom, int amt);

	bool isTouchingPlayerInDirection(int dir);

	bool isHitBoxTouchingEntityInDirectionByAmount(sp<Entity> e, int direction, int amt);

	bool isHitBoxTouchingXYInDirectionByAmount(float x, float y, int direction, int amt);

	bool isHitBoxTouchingXYXYInDirectionByAmount(float left, float top, float right, float bottom, int direction, int amt);

	virtual float getTop();

	virtual float getLeft();

	virtual float getRight();

	virtual float getBottom();

	float getMiddleX();

	float getMiddleY();

	float getRoundedMiddleX();

	float getRoundedMiddleY();

	float getMiddleOffsetX();

	float getMiddleOffsetY();

private:
	float getScreenX();

	float getScreenY();

public:
	virtual float getScreenLeft();

	virtual float getScreenTop();

	float getScreenMiddleHitboxY();

	/// <summary>
	/// This is the offset from x to the hitbox </summary>
	virtual float getHitBoxFromLeft();

	/// <summary>
	/// This is the offset from x + width to the hitbox, it is a positive number but subtracted: x + width - hitbox </summary>
	virtual float getHitBoxFromRight();

	/// <summary>
	/// This is the offset from y to the hitbox, this is larger for people as it offsets down to the feet </summary>
	virtual float getHitBoxFromTop();

	/// <summary>
	/// This is the offset from y + height to the hitbox, it is a positive number but subtracted: y + height - hitbox </summary>
	virtual float getHitBoxFromBottom();

	float getShadowStart();

	virtual float getX();
	virtual float getY();

	virtual void setX(float x);

	virtual void setY(float y);

	void incX();
	void incY();
	void decX();
	void decY();

	virtual float getWidth();

	virtual float getHeight();

	virtual sp<EntityData> getData();

	string& getName();
	string& getComment();
	int getID();
	//int getMapID();
	string& getSpriteName();

	bool getIsNPC();
	bool getPushable();
	bool getNonWalkable();
	float getToAlpha();
	float getScale();
	bool getDisableShadow();
	bool getAboveWhenEqual();
	bool getAlwaysOnTop();
	bool getAlwaysOnBottom();
	RenderOrder getRenderOrder();
	bool getAboveTopLayer();
	int getInitialFrame();
	bool getAnimatingThroughAllFrames();
	bool getRandomFrames();
	bool getRandomUpToTicksBetweenFrames();
	bool getRandomUpToTicksBetweenAnimationLoop();
	int getTicksBetweenFrames();
	int getTicksBetweenAnimationLoop();

	float getTicksPerPixelMoved();

	sp<EventData> getEventData();
	bool getOnlyHereDuringEvent();
	float getVoicePitch();
	bool getMovementAnimationDisabled();
	bool getIgnoreHitLayer();
	bool getIgnoreHitPlayer();
	bool getPullPlayer();
	bool getPushPlayer();

	bool getAnimatingThroughCurrentAnimation();
	bool getLoopAnimation();

	sp<vector<string>> getConnectionTYPEIDList();
	sp<vector<string>> getBehaviorList();

	string getTYPEIDString();

	//set
	void setID(int s);
	void setName(const string& s);
	void setComment(const string& s);

	void setSpawnXPixelsHQ(float s);
	void setSpawnYPixelsHQ(float s);
	void setIsNPC(bool s);
	void setPushable(bool s);
	void setNonWalkable(bool s);
	void setToAlpha(float alpha);
	void setScale(float s);
	void setDisableShadow(bool s);
	void setInitialFrame(int f);
	void setRandomFrames(bool s);
	void setRandomUpToTicksBetweenFrames(bool s);
	void setRandomUpToTicksBetweenAnimationLoop(bool s);
	void setTicksBetweenFrames(int s);
	void setTicksBetweenAnimationLoop(int s);

	void setTicksPerPixelMoved(float s);
	void setRenderOrder(RenderOrder s);
	void setAboveTopLayer(bool s);
	void setAboveWhenEqual(bool s);
	void setAlwaysOnBottom(bool s);
	void setAlwaysOnTop(bool s);
	void setOnlyHereDuringEvent(bool s);
	void setVoicePitch(float s);
	void setAnimationDisabled(bool s);
	void setHitLayerDisabled(bool s);
	void setIgnoreHitPlayer(bool s);
	//void setEventID(int s);

	void setAnimateThroughAllFrames(bool s);
	void setAnimateThroughCurrentAnimation(bool s);
	void setLoopAnimation(bool s);
};

