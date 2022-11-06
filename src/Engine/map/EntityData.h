//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;



class EntityData : public AssetData
{
private:
	typedef AssetData super;

private:
	
	string spriteName = "";
	float spawnXPixels1X = 0;
	float spawnYPixels1X = 0;
	int initialFrame = 0;
	bool pushable = false;
	bool nonWalkable = false;
	float toAlpha = 1.0f;
	float scale = 1.0f;
	bool disableShadow = false;

	bool aboveTopLayer = false; //dont use this in client, client only uses layer, this is only for the editor to easily set a sprite to above layer.
	//eventually it will be replaced when i move to objectData save/load in editor.
	//TODO: phase this out for just "set layer" above/below

	int layer = 0; //ground
	RenderOrder renderOrder = RenderOrder::GROUND;
	bool aboveWhenEqual = false; //if two entities are on the same layer and the bottom lines up, render this one after
	bool alwaysOnBottom = false; //render first on whatever layer it is on
	bool alwaysOnTop = false; //render last on whatever layer it is on
	bool animateThroughFrames = false; //cannot have BOTH this and animateThroughCurrentAnimation set.
	int ticksBetweenFrames = 100;
	bool randomUpToTicksBetweenFrames = false; //added in editor
	bool randomFrames = false; //initial frame will be randomized too. applies to both animateThroughAllFrames and animateThroughCurrentAnimation
	int ticksBetweenAnimation = 0; //will be random up to this if checked random up to ticks between animation loop
	bool randomTimeBetweenAnimation = false;

public:
	int walkSpeed = 1; //DONE: phase this out for a getTicksPerPixelMoved edit box // THIS VARIABLE IS OBSOLETE, keeping it for backwards compatibility.
private:
	
	float ticksPerPixelMoved = 10;
	//int eventID = -1;
	bool onlyHereDuringEvent = false; //TODO: what does this do
	//int mapID = -1;
	//int stateID = -1;

	//TODO: implement in editor:
	bool animateThroughCurrentAnimation = false; //TODO: implement
	
	bool loopAnimation = true; //TODO: implement
	float voicePitch = 0; //TODO: implement
	bool animationDisabled = false; //TODO see where this is used.
	bool hitLayerDisabled = false;
	bool ignoreHitPlayer = false;
	bool ignoreHitEntities = false;
	bool dontUsePathfinding = false;

	//public boolean ignore_fx_layer=false;
	
	bool pullPlayer = false;
	bool pushPlayer = false;
	ArrayList<string> behaviorList;// = make_shared<ArrayList><string>();
	ArrayList<string> connectionTYPEIDList;// = make_shared<ArrayList><string>();
	string comment = "";
	bool isNPC = false; //only used for export from tools for now to determine whether to spawn a character or an entity. determined from the SPRITE.getIsNPC, which is where it should be.

	shared_ptr<EventData> eventData = nullptr;

public:
	EntityData();

	EntityData(int id, const string& name, const string& spriteAssetName = "", int spawnXPixels1X = 0, int spawnYPixels1X = 0, int initialFrame = 0, bool pushable = false, bool nonWalkable = false, int alphaByte = 255, float scale = 1, int ticksPerPixelMoved = 12, bool aboveTopLayer = false, bool aboveWhenEqual = false, bool alwaysOnBottom = false, bool animateThroughFrames = false, bool randomTimeBetweenAnimation = false, int ticksBetweenFrames = 0, int ticksBetweenAnimation = false, bool onlyHereDuringEvent = false, bool randomFrames = false, bool disableShadow = false, shared_ptr<EventData> eventData = nullptr, const string& comment = "");
	void initEntityData(int id, const string& name, const string& spriteAssetName = "", int spawnXPixels1X = 0, int spawnYPixels1X = 0, int initialFrame = 0, bool pushable = false, bool nonWalkable = false, int alphaByte = 255, float scale = 1, int ticksPerPixelMoved = 12, bool aboveTopLayer = false, bool aboveWhenEqual = false, bool alwaysOnBottom = false, bool animateThroughFrames = false, bool randomTimeBetweenAnimation = false, int ticksBetweenFrames = 0, int ticksBetweenAnimation = false, bool onlyHereDuringEvent = false, bool randomFrames = false, bool disableShadow = false, shared_ptr<EventData> eventData = nullptr, const string& comment = "");

	//	
	//	public void addConnection(String s)
	//	{
	//		getConnectionTYPEIDList.add(s);
	//	}

	//	
	//	public void addBehavior(String s)
	//	{
	//		getBehaviorList.add(s);
	//	}

	virtual string& initFromString(string& t) override;
	//static shared_ptr<EntityData> fromBase64ZippedJSON(const string& b64);
	//static shared_ptr<EntityData> fromJSON(const string& json);

	virtual string getTYPEIDString();

	float getSpawnXPixels1X();
	float getSpawnYPixels1X();
	float getSpawnXPixelsHQ();
	float getSpawnYPixelsHQ();

	string& getSpriteName();
	string& getComment();
	int getInitialFrame();
	bool getPushable();
	bool getNonWalkable();
	float getToAlpha();
	float getScale();
	bool getDisableShadow();
	int getLayer();
	RenderOrder getRenderOrder();
	bool getAboveWhenEqual();
	bool getAboveTopLayer();
	bool getAlwaysOnBottom();
	bool getAlwaysOnTop();
	bool getIsNPC();
	bool getAnimatingThroughAllFrames();
	bool getAnimatingThroughCurrentAnimation();
	bool getLoopAnimation();
	bool getRandomFrames();
	bool getRandomUpToTicksBetweenAnimationLoop();
	int getTicksBetweenFrames();
	bool getRandomUpToTicksBetweenFrames();
	int getTicksBetweenAnimationLoop();

	float getTicksPerPixelMoved();
	bool getOnlyHereDuringEvent();
	float getVoicePitch();
	bool getMovementAnimationDisabled();
	bool getHitLayerDisabled();
	bool getIgnoreHitPlayer();
	bool getIgnoreHitEntities();
	bool getDontUsePathfinding();
	bool getPullPlayer();
	bool getPushPlayer();
	shared_ptr<EventData> getEventData();
	//int getMapID();
	//int getStateID();
	ArrayList<string>* getConnectionTYPEIDList();
	ArrayList<string>* getBehaviorList();

	//set

	void setSpriteName(const string& s);
	void setInitialFrame(int s);
	void setPushable(bool s);
	void setNonWalkable(bool s);
	void setToAlpha(float s);
	void setScale(float s);
	void setDisableShadow(bool s);
	void setRenderOrder(RenderOrder s);
	void setAboveTopLayer(bool s);
	void setAboveWhenEqual(bool s);
	void setAlwaysOnBottom(bool s);
	void setAlwaysOnTop(bool s);
	void setIsNPC(bool s);
	void setOnlyHereDuringEvent(bool s);
	void setVoicePitch(float s);
	void setAnimationDisabled(bool s);
	void setHitLayerDisabled(bool s);
	void setIgnoreHitPlayer(bool s);
	void setIgnoreHitEntities(bool s);
	void setDontUsePathfinding(bool s);

	void setRandomFrames(bool s);
	void setRandomUpToTicksBetweenAnimationLoop(bool s);
	void setTicksBetweenFrames(int s);
	void setRandomUpToTicksBetweenFrames(bool s);
	void setTicksBetweenAnimationLoop(int s);

	void setTicksPerPixelMoved(float s);
	void setSpawnXPixels1X(float s);
	void setSpawnYPixels1X(float s);
	//void setMapID(int s);
	//void setStateID(int s);
	//void setEventID(int s);
	void setComment(const string& s);

	void setAnimateThroughAllFrames(bool s);
	void setAnimateThroughCurrentAnimation(bool s);
	void setLoopAnimation(bool s);
};

