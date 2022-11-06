//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "GameStringData.h"
#include "DialogueData.h"
#include "FlagData.h"
#include "SkillData.h"
#include "src/Utility/AssetData.h"
#include "src/Utility/audio/AudioData.h"

class Logger;




//TODO make comment structure for these


class EventScriptCommand
{
protected:
	string command;
	string comment; //for editor

	//ArrayList<EventParameter> eventParameters

public:
	string toString();
	//public EventCommand toEventCommandWithParameters(){return null;}

	EventScriptCommand();

	EventScriptCommand(const string& command, const string& comment);


	string getCommand() const;

	string getCommandWithArguments();

	string getComment(); //TODO: handle comments in editor event editor
};


class EventScriptQualifier : public EventScriptCommand
{
public:
	EventScriptQualifier(const string& command, const string& comment);
};





class EventData : public AssetData
{
private:
	typedef AssetData super;


	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------
	//
	//
	//
	//	WARNING! EDITING THESE NAMES WILL BREAK JSON DECODING
	//
	//
	//
	//
	//---------------------------------------------------------
	//---------------------------------------------------------
	//---------------------------------------------------------


public:


private:
	
	int type = 0;
	
	string comment = "";
	
	string text = "";

public:

	//these are used for the client to preload dialogues, flags, music, etc without doing a server lookup.  USED FOR EXPORT ONLY IN TOOLS. not stored in data structure.
	ArrayList<shared_ptr<DialogueData>>* dialogueDataList = make_shared<ArrayList><shared_ptr<DialogueData>>();
	ArrayList<shared_ptr<FlagData>>* flagDataList = make_shared<ArrayList><shared_ptr<FlagData>>();
	ArrayList<shared_ptr<SkillData>>* skillDataList = make_shared<ArrayList><shared_ptr<SkillData>>();
	ArrayList<shared_ptr<GameStringData>>* gameStringDataList = make_shared<ArrayList><shared_ptr<GameStringData>>();
	ArrayList<shared_ptr<AudioData>>* musicDataList = make_shared<ArrayList><shared_ptr<AudioData>>();
	ArrayList<shared_ptr<AudioData>>* soundDataList = make_shared<ArrayList><shared_ptr<AudioData>>();





public:

	static Logger log;


	EventData();


	EventData(int id, const string& name, int type, const string& comment, const string& text);

	virtual string& initFromString(string& t) override;

	//static shared_ptr<EventData> fromBase64ZippedJSON(const string& b64);


	//static shared_ptr<EventData> fromJSON(const string& json);


	string getTYPEIDString();


	int getType();
	string& getComment();
	string& getText();

	void setType(int s);
	void setComment(const string& s);
	void setText(const string& s);


	static int TYPE_PROJECT_INITIAL_LOADER; //project cutscene loader, one per project
	static int TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED; //project cutscene loader, one per project

	static int TYPE_MAP_RUN_ONCE_BEFORE_LOAD; //maps will use this for setting the map State, it is run exactly once upon map load, before any objects are created.
	static int TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING; //all object will use this (door, area, entity, sprite)
	static int TYPE_MAP_DONT_RUN_UNTIL_CALLED; //maps can set this type, which is populated in the EventEditor Events tab. it is an event that any of the objects on this map can call.
	static int TYPE_MAP_RUN_ONCE_AFTER_LOAD; //maps can set this type, it is used for cutscenes


public:
	static ArrayList<shared_ptr<EventScriptCommand>>* commandList;
	static ArrayList<shared_ptr<EventScriptQualifier>>* qualifierList;


	const static shared_ptr<EventScriptQualifier> isPlayerTouchingThisArea;
	const static shared_ptr<EventScriptQualifier> isPlayerWalkingIntoThisDoor;
	const static shared_ptr<EventScriptQualifier> isPlayerTouchingThisEntity;
	const static shared_ptr<EventScriptQualifier> isPlayerTouchingAnyEntityUsingThisSprite;
	const static shared_ptr<EventScriptQualifier> isPlayerWalkingIntoDoor_DOOR;
	const static shared_ptr<EventScriptQualifier> isPlayerWalkingIntoWarp_WARP;
	const static shared_ptr<EventScriptQualifier> isActionButtonHeld;
	const static shared_ptr<EventScriptQualifier> isPlayerAutoPilotOn;
	const static shared_ptr<EventScriptQualifier> isFlagSet_FLAG;
	const static shared_ptr<EventScriptQualifier> hasSkillAtLeast_SKILL_FLOAT1;
	const static shared_ptr<EventScriptQualifier> isCurrentState_STATE;
	const static shared_ptr<EventScriptQualifier> isPlayerStandingInArea_AREA;
	const static shared_ptr<EventScriptQualifier> isEntityStandingInArea_ENTITY_AREA;
	const static shared_ptr<EventScriptQualifier> hourPastOrEqualTo_INT23;
	const static shared_ptr<EventScriptQualifier> hourLessThan_INT23;
	const static shared_ptr<EventScriptQualifier> minutePastOrEqualTo_INT59;
	const static shared_ptr<EventScriptQualifier> minuteLessThan_INT59;
	const static shared_ptr<EventScriptQualifier> hasMoneyAtLeastAmount_FLOAT;
	const static shared_ptr<EventScriptQualifier> hasMoneyLessThanAmount_FLOAT;
	const static shared_ptr<EventScriptQualifier> hasItem_ITEM;
	const static shared_ptr<EventScriptQualifier> hasGame_GAME;
	const static shared_ptr<EventScriptQualifier> isPlayerMale;
	const static shared_ptr<EventScriptQualifier> isPlayerFemale;
	const static shared_ptr<EventScriptQualifier> isAnyEntityUsingSprite_SPRITE;
	const static shared_ptr<EventScriptQualifier> isAnyEntityUsingSpriteAtArea_SPRITE_AREA;
	const static shared_ptr<EventScriptQualifier> isEntitySpawned_ENTITY;
	const static shared_ptr<EventScriptQualifier> isEntityAtArea_ENTITY_AREA;
	const static shared_ptr<EventScriptQualifier> isAreaEmpty_AREA;
	const static shared_ptr<EventScriptQualifier> hasFinishedDialogue_DIALOGUE;
	const static shared_ptr<EventScriptQualifier> isTextBoxOpen;
	const static shared_ptr<EventScriptQualifier> isTextAnswerBoxOpen;
	const static shared_ptr<EventScriptQualifier> isTextAnswerSelected_INT4;
	const static shared_ptr<EventScriptQualifier> isTextAnswerSelected_STRING;
	const static shared_ptr<EventScriptQualifier> randomEqualsOneOutOfLessThan_INT;
	const static shared_ptr<EventScriptQualifier> randomEqualsOneOutOfIncluding_INT;
	const static shared_ptr<EventScriptQualifier> isAnyMusicPlaying;
	const static shared_ptr<EventScriptQualifier> isMusicPlaying_MUSIC;
	const static shared_ptr<EventScriptQualifier> isRaining;
	const static shared_ptr<EventScriptQualifier> isWindy;
	const static shared_ptr<EventScriptQualifier> isSnowing;
	const static shared_ptr<EventScriptQualifier> isFoggy;
	//	public static final EventScriptQualifier isPlayerHolding = make_shared<EventScriptQualifier>("isPlayerHolding_ITEM","");
	//	public static final EventScriptQualifier isPlayerWearing = make_shared<EventScriptQualifier>("isPlayerWearing_ITEM","");
	const static shared_ptr<EventScriptQualifier> isMapOutside;
	const static shared_ptr<EventScriptQualifier> hasTalkedToThisToday;
	const static shared_ptr<EventScriptQualifier> hasBeenMinutesSinceFlagSet_FLAG_INT;
	const static shared_ptr<EventScriptQualifier> hasBeenHoursSinceFlagSet_FLAG_INT23;
	const static shared_ptr<EventScriptQualifier> hasBeenDaysSinceFlagSet_FLAG_INT;
	const static shared_ptr<EventScriptQualifier> isThisActivated;
	const static shared_ptr<EventScriptQualifier> haveSecondsPassedSinceActivated_INT;
	const static shared_ptr<EventScriptQualifier> haveMinutesPassedSinceActivated_INT;
	const static shared_ptr<EventScriptQualifier> haveHoursPassedSinceActivated_INT;
	const static shared_ptr<EventScriptQualifier> haveDaysPassedSinceActivated_INT;
	const static shared_ptr<EventScriptQualifier> hasActivatedThisEver;
	const static shared_ptr<EventScriptQualifier> hasActivatedThisSinceEnterRoom;
	const static shared_ptr<EventScriptQualifier> hasBeenHereEver;
	const static shared_ptr<EventScriptQualifier> hasBeenHereSinceEnterRoom;
	const static shared_ptr<EventScriptQualifier> haveSecondsPassedSinceBeenHere_INT;
	const static shared_ptr<EventScriptQualifier> haveMinutesPassedSinceBeenHere_INT;
	const static shared_ptr<EventScriptQualifier> haveHoursPassedSinceBeenHere_INT;
	const static shared_ptr<EventScriptQualifier> haveDaysPassedSinceBeenHere_INT;
	const static shared_ptr<EventScriptQualifier> isLightOn_LIGHT;


	//commands
	const static shared_ptr<EventScriptCommand> alwaysBlockWhileNotStandingHere;
	//doesn't delete from the stack, checks every time, continues stack underneath normally.
	//this is an alternative to having an option for deleting the stack when not standing in area
	//instead of deleting the stack
	//this could cause state problems like NPC AI getting stuck off, etc.


	const static shared_ptr<EventScriptCommand> e00;
	const static shared_ptr<EventScriptCommand> blockUntilActionButtonPressed; //BLOCK//doesn't delete from the stack until valid, doesn't proceed until it is.
	const static shared_ptr<EventScriptCommand> blockUntilActionCaptionButtonPressed_STRING; //BLOCK//this will stay in the queue checking if we are standing here, use ACTION_area
	const static shared_ptr<EventScriptCommand> blockUntilCancelButtonPressed; //BLOCK
	const static shared_ptr<EventScriptCommand> blockForTicks_INT; //BLOCK
	const static shared_ptr<EventScriptCommand> blockUntilClockHour_INT23; //BLOCK
	const static shared_ptr<EventScriptCommand> blockUntilClockMinute_INT59; //BLOCK
	const static shared_ptr<EventScriptCommand> e000;
	const static shared_ptr<EventScriptCommand> loadMapState_STATE;
	const static shared_ptr<EventScriptCommand> runEvent_EVENT;
	const static shared_ptr<EventScriptCommand> blockUntilEventDone_EVENT;
	const static shared_ptr<EventScriptCommand> clearThisEvent;
	const static shared_ptr<EventScriptCommand> clearEvent_EVENT;
	const static shared_ptr<EventScriptCommand> e001;
	const static shared_ptr<EventScriptCommand> setThisActivated_BOOL;
	const static shared_ptr<EventScriptCommand> toggleThisActivated;
	const static shared_ptr<EventScriptCommand> e002;
	const static shared_ptr<EventScriptCommand> setLastBeenHereTime;
	const static shared_ptr<EventScriptCommand> resetLastBeenHereTime;
	const static shared_ptr<EventScriptCommand> e003;
	const static shared_ptr<EventScriptCommand> setFlag_FLAG_BOOL;
	const static shared_ptr<EventScriptCommand> setFlagTrue_FLAG;
	const static shared_ptr<EventScriptCommand> setFlagFalse_FLAG;
	const static shared_ptr<EventScriptCommand> e004;
	const static shared_ptr<EventScriptCommand> giveSkillPoints_SKILL_INT;
	const static shared_ptr<EventScriptCommand> removeSkillPoints_SKILL_INT;
	const static shared_ptr<EventScriptCommand> setSkillPoints_SKILL_INT;
	const static shared_ptr<EventScriptCommand> e005;

	const static shared_ptr<EventScriptCommand> enterThisDoor;
	const static shared_ptr<EventScriptCommand> enterThisWarp;
	const static shared_ptr<EventScriptCommand> enterDoor_DOOR;
	const static shared_ptr<EventScriptCommand> enterWarp_WARP;
	const static shared_ptr<EventScriptCommand> changeMap_MAP_AREA;
	const static shared_ptr<EventScriptCommand> changeMap_MAP_DOOR;
	const static shared_ptr<EventScriptCommand> changeMap_MAP_WARP;
	const static shared_ptr<EventScriptCommand> changeMap_MAP_INT_INT;
	const static shared_ptr<EventScriptCommand> e006;
	const static shared_ptr<EventScriptCommand> doDialogue_DIALOGUE;
	const static shared_ptr<EventScriptCommand> doDialogueWithCaption_DIALOGUE;
	const static shared_ptr<EventScriptCommand> doDialogueIfNew_DIALOGUE;
	const static shared_ptr<EventScriptCommand> e007;
	const static shared_ptr<EventScriptCommand> setSpriteBox0_ENTITY;
	const static shared_ptr<EventScriptCommand> setSpriteBox1_ENTITY;
	const static shared_ptr<EventScriptCommand> setSpriteBox0_SPRITE;
	const static shared_ptr<EventScriptCommand> setSpriteBox1_SPRITE;
	const static shared_ptr<EventScriptCommand> e008;
	const static shared_ptr<EventScriptCommand> blockUntilTextBoxClosed;
	const static shared_ptr<EventScriptCommand> blockUntilTextAnswerBoxClosed;
	const static shared_ptr<EventScriptCommand> e009;
	const static shared_ptr<EventScriptCommand> doCinematicTextNoBorder_DIALOGUE_INTy;

	const static shared_ptr<EventScriptCommand> e025;
	const static shared_ptr<EventScriptCommand> setDoorOpenAnimation_DOOR_BOOLopenClose;
	const static shared_ptr<EventScriptCommand> setDoorActionIcon_DOOR_BOOLonOff;
	const static shared_ptr<EventScriptCommand> setDoorDestination_DOOR_DOORdestination;
	const static shared_ptr<EventScriptCommand> setAreaActionIcon_AREA_BOOLonOff;
	const static shared_ptr<EventScriptCommand> setWarpDestination_WARP_WARPdestination;


	//public static final EventScriptCommand playVideo_VIDEO = make_shared<EventScriptCommand>("playVideo_VIDEO","");
	const static shared_ptr<EventScriptCommand> e010;


	const static shared_ptr<EventScriptCommand> e012;
	const static shared_ptr<EventScriptCommand> setCameraNoTarget;
	const static shared_ptr<EventScriptCommand> setCameraTargetToArea_AREA;
	const static shared_ptr<EventScriptCommand> setCameraTargetToEntity_ENTITY;
	const static shared_ptr<EventScriptCommand> setCameraIgnoreBounds_BOOL;
	const static shared_ptr<EventScriptCommand> setCameraTargetToPlayer;
	const static shared_ptr<EventScriptCommand> blockUntilCameraReaches_AREA;
	const static shared_ptr<EventScriptCommand> blockUntilCameraReaches_ENTITY;
	const static shared_ptr<EventScriptCommand> blockUntilCameraReachesPlayer;
	const static shared_ptr<EventScriptCommand> pushCameraState;
	const static shared_ptr<EventScriptCommand> popCameraState;
	const static shared_ptr<EventScriptCommand> setKeyboardCameraZoom_BOOL;
	const static shared_ptr<EventScriptCommand> enableKeyboardCameraZoom;
	const static shared_ptr<EventScriptCommand> disableKeyboardCameraZoom;
	const static shared_ptr<EventScriptCommand> setCameraAutoZoomByPlayerMovement_BOOL;
	const static shared_ptr<EventScriptCommand> enableCameraAutoZoomByPlayerMovement;
	const static shared_ptr<EventScriptCommand> disableCameraAutoZoomByPlayerMovement;
	const static shared_ptr<EventScriptCommand> setCameraZoom_FLOAT;
	const static shared_ptr<EventScriptCommand> setCameraSpeed_FLOAT;


	const static shared_ptr<EventScriptCommand> setPlayerToTempPlayerWithSprite_SPRITE;
	const static shared_ptr<EventScriptCommand> setPlayerToNormalPlayer;
	const static shared_ptr<EventScriptCommand> setPlayerExists_BOOL;
	const static shared_ptr<EventScriptCommand> setPlayerControlsEnabled_BOOL;
	const static shared_ptr<EventScriptCommand> enablePlayerControls;
	const static shared_ptr<EventScriptCommand> disablePlayerControls;
	const static shared_ptr<EventScriptCommand> setPlayerAutoPilot_BOOL;
	const static shared_ptr<EventScriptCommand> setPlayerShowNameCaption_BOOL;
	const static shared_ptr<EventScriptCommand> setPlayerShowAccountTypeCaption_BOOL;

	const static shared_ptr<EventScriptCommand> playerSetBehaviorQueueOnOff_BOOL;
	const static shared_ptr<EventScriptCommand> playerSetToArea_AREA;
	const static shared_ptr<EventScriptCommand> playerSetToDoor_DOOR;
	const static shared_ptr<EventScriptCommand> playerSetToTileXY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> playerWalkToArea_AREA;
	const static shared_ptr<EventScriptCommand> playerWalkToDoor_DOOR;
	const static shared_ptr<EventScriptCommand> playerWalkToEntity_ENTITY;
	const static shared_ptr<EventScriptCommand> playerWalkToTileXY_INTxTile1X_INTyTile1X;
	//	public static final EventScriptCommand playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	const static shared_ptr<EventScriptCommand> playerBlockUntilReachesArea_AREA;
	const static shared_ptr<EventScriptCommand> playerBlockUntilReachesDoor_DOOR;
	const static shared_ptr<EventScriptCommand> playerBlockUntilReachesEntity_ENTITY;
	const static shared_ptr<EventScriptCommand> playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> playerWalkToAreaAndBlockUntilThere_AREA;
	const static shared_ptr<EventScriptCommand> playerWalkToEntityAndBlockUntilThere_ENTITY;
	const static shared_ptr<EventScriptCommand> playerWalkToDoorAndBlockUntilThere_DOOR;
	const static shared_ptr<EventScriptCommand> playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> playerStandAndShuffle;
	//	public static final EventScriptCommand playerStandAndShuffleAndFacePlayer = make_shared<EventScriptCommand>("playerStandAndShuffleAndFacePlayer","");
	const static shared_ptr<EventScriptCommand> playerStandAndShuffleAndFaceEntity_ENTITY;
	//	public static final EventScriptCommand playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName = make_shared<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName","");
	//	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName = make_shared<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName","");
	const static shared_ptr<EventScriptCommand> playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame;
	const static shared_ptr<EventScriptCommand> playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame;
	const static shared_ptr<EventScriptCommand> playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> playerStopAnimating;
	const static shared_ptr<EventScriptCommand> playerSetGlobalAnimationDisabled_BOOL;
	const static shared_ptr<EventScriptCommand> playerSetMovementSpeed_INTticksPerPixel;
	const static shared_ptr<EventScriptCommand> playerSetFaceMovementDirection_STRINGdirection;
	//	public static final EventScriptCommand playerSetNonWalkable_BOOL = make_shared<EventScriptCommand>("playerSetNonWalkable_BOOL","");
	//	public static final EventScriptCommand playerSetPushable_BOOL = make_shared<EventScriptCommand>("playerSetPushable_BOOL","");
	const static shared_ptr<EventScriptCommand> playerSetToAlpha_FLOAT;
	//public static final EventScriptCommand playerFadeOutDelete = make_shared<EventScriptCommand>("playerFadeOutDelete","");
	//public static final EventScriptCommand playerDeleteInstantly = make_shared<EventScriptCommand>("playerDeleteInstantly","");


	//	public static final EventScriptCommand thisEntitySetBehaviorQueueOnOff_BOOL = make_shared<EventScriptCommand>("thisEntitySetBehaviorQueueOnOff_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToArea_AREA = make_shared<EventScriptCommand>("thisEntitySetToArea_AREA","");
	//	public static final EventScriptCommand thisEntitySetToDoor_DOOR = make_shared<EventScriptCommand>("thisEntitySetToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntitySetToTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("thisEntitySetToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityWalkToArea_AREA = make_shared<EventScriptCommand>("thisEntityWalkToArea_AREA","");
	//	public static final EventScriptCommand thisEntityWalkToDoor_DOOR = make_shared<EventScriptCommand>("thisEntityWalkToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityWalkToEntity_ENTITY = make_shared<EventScriptCommand>("thisEntityWalkToEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityWalkToTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("thisEntityWalkToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesArea_AREA = make_shared<EventScriptCommand>("thisEntityBlockUntilReachesArea_AREA","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesDoor_DOOR = make_shared<EventScriptCommand>("thisEntityBlockUntilReachesDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesEntity_ENTITY = make_shared<EventScriptCommand>("thisEntityBlockUntilReachesEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityStandAndShuffle = make_shared<EventScriptCommand>("thisEntityStandAndShuffle","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFacePlayer = make_shared<EventScriptCommand>("thisEntityStandAndShuffleAndFacePlayer","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFaceEntity_ENTITY = make_shared<EventScriptCommand>("thisEntityStandAndShuffleAndFaceEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityStopAnimating = make_shared<EventScriptCommand>("thisEntityStopAnimating","");
	//	public static final EventScriptCommand thisEntitySetGlobalAnimationDisabled_BOOL = make_shared<EventScriptCommand>("thisEntitySetGlobalAnimationDisabled_BOOL","");
	//	public static final EventScriptCommand thisEntitySetMovementSpeed_INTticksPerPixel = make_shared<EventScriptCommand>("thisEntitySetMovementSpeed_INTticksPerPixel","");
	//	public static final EventScriptCommand thisEntitySetFaceMovementDirection_STRINGdirection = make_shared<EventScriptCommand>("thisEntitySetFaceMovementDirection_STRINGdirection","");
	//	public static final EventScriptCommand thisEntitySetNonWalkable_BOOL = make_shared<EventScriptCommand>("thisEntitySetNonWalkable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetPushable_BOOL = make_shared<EventScriptCommand>("thisEntitySetPushable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToAlpha_FLOAT = make_shared<EventScriptCommand>("thisEntitySetToAlpha_FLOAT","");
	//	public static final EventScriptCommand thisEntityFadeOutDelete = make_shared<EventScriptCommand>("thisEntityFadeOutDelete","");
	//	public static final EventScriptCommand thisEntityDeleteInstantly = make_shared<EventScriptCommand>("thisEntityDeleteInstantly","");


	const static shared_ptr<EventScriptCommand> e024;
	const static shared_ptr<EventScriptCommand> entitySetBehaviorQueueOnOff_ENTITY_BOOL;
	const static shared_ptr<EventScriptCommand> entitySetToArea_ENTITY_AREA;
	const static shared_ptr<EventScriptCommand> entitySetToDoor_ENTITY_DOOR;
	const static shared_ptr<EventScriptCommand> entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> entityWalkToArea_ENTITY_AREA;
	const static shared_ptr<EventScriptCommand> entityWalkToDoor_ENTITY_DOOR;
	const static shared_ptr<EventScriptCommand> entityWalkToEntity_ENTITY_ENTITY;
	const static shared_ptr<EventScriptCommand> entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static shared_ptr<EventScriptCommand> entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static shared_ptr<EventScriptCommand> entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static shared_ptr<EventScriptCommand> entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static shared_ptr<EventScriptCommand> entityBlockUntilReachesArea_ENTITY_AREA;
	const static shared_ptr<EventScriptCommand> entityBlockUntilReachesDoor_ENTITY_DOOR;
	const static shared_ptr<EventScriptCommand> entityBlockUntilReachesEntity_ENTITY_ENTITY;
	const static shared_ptr<EventScriptCommand> entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> entityWalkToAreaAndBlockUntilThere_ENTITY_AREA;
	const static shared_ptr<EventScriptCommand> entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY;
	const static shared_ptr<EventScriptCommand> entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR;
	const static shared_ptr<EventScriptCommand> entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X;
	const static shared_ptr<EventScriptCommand> entityStandAndShuffle_ENTITY;
	const static shared_ptr<EventScriptCommand> entityStandAndShuffleAndFacePlayer_ENTITY;
	const static shared_ptr<EventScriptCommand> entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY;
	const static shared_ptr<EventScriptCommand> entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName;
	const static shared_ptr<EventScriptCommand> entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static shared_ptr<EventScriptCommand> entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static shared_ptr<EventScriptCommand> entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static shared_ptr<EventScriptCommand> entityStopAnimating_ENTITY;
	const static shared_ptr<EventScriptCommand> entitySetGlobalAnimationDisabled_ENTITY_BOOL;
	const static shared_ptr<EventScriptCommand> entitySetMovementSpeed_ENTITY_INTticksPerPixel;
	const static shared_ptr<EventScriptCommand> entitySetFaceMovementDirection_ENTITY_STRINGdirection;
	const static shared_ptr<EventScriptCommand> entitySetNonWalkable_ENTITY_BOOL;
	const static shared_ptr<EventScriptCommand> entitySetPushable_ENTITY_BOOL;
	const static shared_ptr<EventScriptCommand> entitySetToAlpha_ENTITY_FLOAT;
	const static shared_ptr<EventScriptCommand> entityFadeOutDelete_ENTITY;
	const static shared_ptr<EventScriptCommand> entityDeleteInstantly_ENTITY;

	const static shared_ptr<EventScriptCommand> e016;
	const static shared_ptr<EventScriptCommand> spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA;
	const static shared_ptr<EventScriptCommand> spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static shared_ptr<EventScriptCommand> spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA;
	const static shared_ptr<EventScriptCommand> spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static shared_ptr<EventScriptCommand> e017;
	const static shared_ptr<EventScriptCommand> createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static shared_ptr<EventScriptCommand> createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static shared_ptr<EventScriptCommand> createScreenSpriteUnderText_SPRITE_INTx_INTy;
	const static shared_ptr<EventScriptCommand> createScreenSpriteOverText_SPRITE_INTx_INTy;


	const static shared_ptr<EventScriptCommand> e026;
	const static shared_ptr<EventScriptCommand> giveItem_ITEM;
	const static shared_ptr<EventScriptCommand> takeItem_ITEM;
	const static shared_ptr<EventScriptCommand> giveGame_GAME;
	const static shared_ptr<EventScriptCommand> takeMoney_FLOAT;
	const static shared_ptr<EventScriptCommand> giveMoney_FLOAT;

	const static shared_ptr<EventScriptCommand> e027;
	const static shared_ptr<EventScriptCommand> playSound_SOUND;
	const static shared_ptr<EventScriptCommand> playSound_SOUND_FLOATvol;
	const static shared_ptr<EventScriptCommand> playSound_SOUND_FLOATvol_FLOATpitch_INTtimes;
	const static shared_ptr<EventScriptCommand> playMusicOnce_MUSIC;
	const static shared_ptr<EventScriptCommand> playMusicLoop_MUSIC;
	const static shared_ptr<EventScriptCommand> playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop;
	const static shared_ptr<EventScriptCommand> stopAllMusic;
	const static shared_ptr<EventScriptCommand> stopMusic_MUSIC;
	const static shared_ptr<EventScriptCommand> fadeOutMusic_MUSIC_INT;
	const static shared_ptr<EventScriptCommand> blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC;
	const static shared_ptr<EventScriptCommand> blockUntilMusicDone_MUSIC;
	const static shared_ptr<EventScriptCommand> fadeOutAllMusic_INT;
	const static shared_ptr<EventScriptCommand> blockUntilAllMusicDone;

	const static shared_ptr<EventScriptCommand> e028;
	const static shared_ptr<EventScriptCommand> shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake;
	const static shared_ptr<EventScriptCommand> fadeToBlack_INTticks;
	const static shared_ptr<EventScriptCommand> fadeFromBlack_INTticks;
	const static shared_ptr<EventScriptCommand> fadeToWhite_INTticks;
	const static shared_ptr<EventScriptCommand> fadeFromWhite_INTticks;
	const static shared_ptr<EventScriptCommand> e029;
	const static shared_ptr<EventScriptCommand> fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static shared_ptr<EventScriptCommand> fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha;
	const static shared_ptr<EventScriptCommand> fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static shared_ptr<EventScriptCommand> setInstantOverlay_INTr_INTg_INTb_FLOATa;
	const static shared_ptr<EventScriptCommand> clearOverlay;

	const static shared_ptr<EventScriptCommand> fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static shared_ptr<EventScriptCommand> setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa;
	const static shared_ptr<EventScriptCommand> clearOverlayUnderLights;

	const static shared_ptr<EventScriptCommand> fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static shared_ptr<EventScriptCommand> setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa;
	const static shared_ptr<EventScriptCommand> clearOverlayGroundLayer;

	const static shared_ptr<EventScriptCommand> e030;
	const static shared_ptr<EventScriptCommand> setLetterbox_BOOL;
	const static shared_ptr<EventScriptCommand> setLetterbox_BOOL_INTticks;
	const static shared_ptr<EventScriptCommand> setLetterbox_BOOL_INTticks_INTsize;
	const static shared_ptr<EventScriptCommand> setLetterbox_BOOL_INTticks_FLOATsize;
	const static shared_ptr<EventScriptCommand> setBlur_BOOL;
	const static shared_ptr<EventScriptCommand> setMosaic_BOOL;
	const static shared_ptr<EventScriptCommand> setHBlankWave_BOOL;
	const static shared_ptr<EventScriptCommand> setRotate_BOOL;
	const static shared_ptr<EventScriptCommand> setBlackAndWhite_BOOL;
	const static shared_ptr<EventScriptCommand> setInvertedColors_BOOL;
	const static shared_ptr<EventScriptCommand> set8BitMode_BOOL;
	const static shared_ptr<EventScriptCommand> e031;
	const static shared_ptr<EventScriptCommand> setEngineSpeed_FLOAT;
	const static shared_ptr<EventScriptCommand> e032;
	const static shared_ptr<EventScriptCommand> toggleLightOnOff_LIGHT;
	const static shared_ptr<EventScriptCommand> setLightOnOff_LIGHT_BOOL;
	const static shared_ptr<EventScriptCommand> setLightFlicker_LIGHT_BOOL;
	const static shared_ptr<EventScriptCommand> toggleAllLightsOnOff;
	const static shared_ptr<EventScriptCommand> setAllLightsOnOff_BOOL;
	const static shared_ptr<EventScriptCommand> e033;
	const static shared_ptr<EventScriptCommand> setRandomSpawn_BOOL;
	const static shared_ptr<EventScriptCommand> deleteRandoms;
	const static shared_ptr<EventScriptCommand> e034;
	const static shared_ptr<EventScriptCommand> makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static shared_ptr<EventScriptCommand> makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb;
	const static shared_ptr<EventScriptCommand> makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb;
	const static shared_ptr<EventScriptCommand> makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static shared_ptr<EventScriptCommand> setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks;


	const static shared_ptr<EventScriptCommand> e035;
	const static shared_ptr<EventScriptCommand> setShowClockCaption_BOOL;
	const static shared_ptr<EventScriptCommand> setShowDayCaption_BOOL;
	const static shared_ptr<EventScriptCommand> setShowMoneyCaption_BOOL;
	const static shared_ptr<EventScriptCommand> setShowAllStatusBarCaptions_BOOL;
	const static shared_ptr<EventScriptCommand> setShowStatusBar_BOOL;

	const static shared_ptr<EventScriptCommand> setShowNDButton_BOOL;
	const static shared_ptr<EventScriptCommand> setShowGameStoreButton_BOOL;
	const static shared_ptr<EventScriptCommand> setShowStuffButton_BOOL;
	const static shared_ptr<EventScriptCommand> setShowAllButtons_BOOL;

	const static shared_ptr<EventScriptCommand> setNDEnabled_BOOL;
	const static shared_ptr<EventScriptCommand> setGameStoreMenuEnabled_BOOL;
	const static shared_ptr<EventScriptCommand> setStuffMenuEnabled_BOOL;
	const static shared_ptr<EventScriptCommand> setAllMenusAndNDEnabled_BOOL;


	const static shared_ptr<EventScriptCommand> e046;
	const static shared_ptr<EventScriptCommand> setClockUnknown;
	const static shared_ptr<EventScriptCommand> setClockNormal;
	const static shared_ptr<EventScriptCommand> setTimePaused_BOOL;
	const static shared_ptr<EventScriptCommand> setTimeFastForward;
	const static shared_ptr<EventScriptCommand> setTimeNormalSpeed;
	const static shared_ptr<EventScriptCommand> e037;


	const static shared_ptr<EventScriptCommand> setNDOpen_BOOL;
	const static shared_ptr<EventScriptCommand> startGame;
	const static shared_ptr<EventScriptCommand> startBobsGameOnStadiumScreen_AREA;
	const static shared_ptr<EventScriptCommand> blockUntilBobsGameDead;
	const static shared_ptr<EventScriptCommand> showLoginScreen;
	//public const static final EventScriptCommand closeND = make_shared<EventScriptCommand>("closeND","");

	const static shared_ptr<EventScriptCommand> e038;
	const static shared_ptr<EventScriptCommand> closeAllMenusAndND;

	//public const static final EventScriptCommand enableAllMenus = make_shared<EventScriptCommand>("enableAllMenus","");
	const static shared_ptr<EventScriptCommand> e039;
	const static shared_ptr<EventScriptCommand> openStuffMenu;
	const static shared_ptr<EventScriptCommand> openItemsMenu;
	const static shared_ptr<EventScriptCommand> openLogMenu;
	const static shared_ptr<EventScriptCommand> openStatusMenu;
	const static shared_ptr<EventScriptCommand> openFriendsMenu;
	const static shared_ptr<EventScriptCommand> openSettingsMenu;
	const static shared_ptr<EventScriptCommand> openGameStoreMenu;

	//	static final EventScriptCommand e040 = make_shared<EventScriptCommand>();
	//	public static final EventScriptCommand pushGameState = make_shared<EventScriptCommand>("pushGameState","");
	//	public static final EventScriptCommand popGameState = make_shared<EventScriptCommand>("popGameState","");
	//	static final EventScriptCommand e041 = make_shared<EventScriptCommand>();
	//	public static final EventScriptCommand showTitleScreen = make_shared<EventScriptCommand>("showTitleScreen","");
	//	public static final EventScriptCommand showCinemaEvent = make_shared<EventScriptCommand>("showCinemaEvent","");
	//	public static final EventScriptCommand runGlobalEvent = make_shared<EventScriptCommand>("runGlobalEvent","");
	//	static final EventScriptCommand e042 = make_shared<EventScriptCommand>();
};

class EventScriptTree
{
private:
	shared_ptr<EventData> outerInstance = nullptr;

public:
	EventScriptTree(shared_ptr<EventData> outerInstance);


	//public String toEventText();

	//TODO: should unify all the event parsing stuff into a class here instead of having basically the same thing in both client and editor.
};