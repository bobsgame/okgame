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
#include "src/Utility/audio/MusicData.h"
#include "src/Utility/audio/SoundData.h"


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
	ArrayList<DialogueData*>* dialogueDataList = new ArrayList<DialogueData*>();
	ArrayList<FlagData*>* flagDataList = new ArrayList<FlagData*>();
	ArrayList<SkillData*>* skillDataList = new ArrayList<SkillData*>();
	ArrayList<GameStringData*>* gameStringDataList = new ArrayList<GameStringData*>();
	ArrayList<MusicData*>* musicDataList = new ArrayList<MusicData*>();
	ArrayList<SoundData*>* soundDataList = new ArrayList<SoundData*>();





public:

	static Logger log;


	EventData();


	EventData(int id, const string& name, int type, const string& comment, const string& text);

	virtual string& initFromString(string& t) override;

	//static EventData* fromBase64ZippedJSON(const string& b64);


	//static EventData* fromJSON(const string& json);


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
	static ArrayList<EventScriptCommand*>* commandList;
	static ArrayList<EventScriptQualifier*>* qualifierList;


	const static EventScriptQualifier* isPlayerTouchingThisArea;
	const static EventScriptQualifier* isPlayerWalkingIntoThisDoor;
	const static EventScriptQualifier* isPlayerTouchingThisEntity;
	const static EventScriptQualifier* isPlayerTouchingAnyEntityUsingThisSprite;
	const static EventScriptQualifier* isPlayerWalkingIntoDoor_DOOR;
	const static EventScriptQualifier* isPlayerWalkingIntoWarp_WARP;
	const static EventScriptQualifier* isActionButtonHeld;
	const static EventScriptQualifier* isPlayerAutoPilotOn;
	const static EventScriptQualifier* isFlagSet_FLAG;
	const static EventScriptQualifier* hasSkillAtLeast_SKILL_FLOAT1;
	const static EventScriptQualifier* isCurrentState_STATE;
	const static EventScriptQualifier* isPlayerStandingInArea_AREA;
	const static EventScriptQualifier* isEntityStandingInArea_ENTITY_AREA;
	const static EventScriptQualifier* hourPastOrEqualTo_INT23;
	const static EventScriptQualifier* hourLessThan_INT23;
	const static EventScriptQualifier* minutePastOrEqualTo_INT59;
	const static EventScriptQualifier* minuteLessThan_INT59;
	const static EventScriptQualifier* hasMoneyAtLeastAmount_FLOAT;
	const static EventScriptQualifier* hasMoneyLessThanAmount_FLOAT;
	const static EventScriptQualifier* hasItem_ITEM;
	const static EventScriptQualifier* hasGame_GAME;
	const static EventScriptQualifier* isPlayerMale;
	const static EventScriptQualifier* isPlayerFemale;
	const static EventScriptQualifier* isAnyEntityUsingSprite_SPRITE;
	const static EventScriptQualifier* isAnyEntityUsingSpriteAtArea_SPRITE_AREA;
	const static EventScriptQualifier* isEntitySpawned_ENTITY;
	const static EventScriptQualifier* isEntityAtArea_ENTITY_AREA;
	const static EventScriptQualifier* isAreaEmpty_AREA;
	const static EventScriptQualifier* hasFinishedDialogue_DIALOGUE;
	const static EventScriptQualifier* isTextBoxOpen;
	const static EventScriptQualifier* isTextAnswerBoxOpen;
	const static EventScriptQualifier* isTextAnswerSelected_INT4;
	const static EventScriptQualifier* isTextAnswerSelected_STRING;
	const static EventScriptQualifier* randomEqualsOneOutOfLessThan_INT;
	const static EventScriptQualifier* randomEqualsOneOutOfIncluding_INT;
	const static EventScriptQualifier* isAnyMusicPlaying;
	const static EventScriptQualifier* isMusicPlaying_MUSIC;
	const static EventScriptQualifier* isRaining;
	const static EventScriptQualifier* isWindy;
	const static EventScriptQualifier* isSnowing;
	const static EventScriptQualifier* isFoggy;
	//	public static final EventScriptQualifier isPlayerHolding = new EventScriptQualifier("isPlayerHolding_ITEM","");
	//	public static final EventScriptQualifier isPlayerWearing = new EventScriptQualifier("isPlayerWearing_ITEM","");
	const static EventScriptQualifier* isMapOutside;
	const static EventScriptQualifier* hasTalkedToThisToday;
	const static EventScriptQualifier* hasBeenMinutesSinceFlagSet_FLAG_INT;
	const static EventScriptQualifier* hasBeenHoursSinceFlagSet_FLAG_INT23;
	const static EventScriptQualifier* hasBeenDaysSinceFlagSet_FLAG_INT;
	const static EventScriptQualifier* isThisActivated;
	const static EventScriptQualifier* haveSecondsPassedSinceActivated_INT;
	const static EventScriptQualifier* haveMinutesPassedSinceActivated_INT;
	const static EventScriptQualifier* haveHoursPassedSinceActivated_INT;
	const static EventScriptQualifier* haveDaysPassedSinceActivated_INT;
	const static EventScriptQualifier* hasActivatedThisEver;
	const static EventScriptQualifier* hasActivatedThisSinceEnterRoom;
	const static EventScriptQualifier* hasBeenHereEver;
	const static EventScriptQualifier* hasBeenHereSinceEnterRoom;
	const static EventScriptQualifier* haveSecondsPassedSinceBeenHere_INT;
	const static EventScriptQualifier* haveMinutesPassedSinceBeenHere_INT;
	const static EventScriptQualifier* haveHoursPassedSinceBeenHere_INT;
	const static EventScriptQualifier* haveDaysPassedSinceBeenHere_INT;
	const static EventScriptQualifier* isLightOn_LIGHT;


	//commands
	const static EventScriptCommand* alwaysBlockWhileNotStandingHere;
	//doesn't delete from the stack, checks every time, continues stack underneath normally.
	//this is an alternative to having an option for deleting the stack when not standing in area
	//instead of deleting the stack
	//this could cause state problems like NPC AI getting stuck off, etc.


	const static EventScriptCommand* e00;
	const static EventScriptCommand* blockUntilActionButtonPressed; //BLOCK//doesn't delete from the stack until valid, doesn't proceed until it is.
	const static EventScriptCommand* blockUntilActionCaptionButtonPressed_STRING; //BLOCK//this will stay in the queue checking if we are standing here, use ACTION_area
	const static EventScriptCommand* blockUntilCancelButtonPressed; //BLOCK
	const static EventScriptCommand* blockForTicks_INT; //BLOCK
	const static EventScriptCommand* blockUntilClockHour_INT23; //BLOCK
	const static EventScriptCommand* blockUntilClockMinute_INT59; //BLOCK
	const static EventScriptCommand* e000;
	const static EventScriptCommand* loadMapState_STATE;
	const static EventScriptCommand* runEvent_EVENT;
	const static EventScriptCommand* blockUntilEventDone_EVENT;
	const static EventScriptCommand* clearThisEvent;
	const static EventScriptCommand* clearEvent_EVENT;
	const static EventScriptCommand* e001;
	const static EventScriptCommand* setThisActivated_BOOL;
	const static EventScriptCommand* toggleThisActivated;
	const static EventScriptCommand* e002;
	const static EventScriptCommand* setLastBeenHereTime;
	const static EventScriptCommand* resetLastBeenHereTime;
	const static EventScriptCommand* e003;
	const static EventScriptCommand* setFlag_FLAG_BOOL;
	const static EventScriptCommand* setFlagTrue_FLAG;
	const static EventScriptCommand* setFlagFalse_FLAG;
	const static EventScriptCommand* e004;
	const static EventScriptCommand* giveSkillPoints_SKILL_INT;
	const static EventScriptCommand* removeSkillPoints_SKILL_INT;
	const static EventScriptCommand* setSkillPoints_SKILL_INT;
	const static EventScriptCommand* e005;

	const static EventScriptCommand* enterThisDoor;
	const static EventScriptCommand* enterThisWarp;
	const static EventScriptCommand* enterDoor_DOOR;
	const static EventScriptCommand* enterWarp_WARP;
	const static EventScriptCommand* changeMap_MAP_AREA;
	const static EventScriptCommand* changeMap_MAP_DOOR;
	const static EventScriptCommand* changeMap_MAP_WARP;
	const static EventScriptCommand* changeMap_MAP_INT_INT;
	const static EventScriptCommand* e006;
	const static EventScriptCommand* doDialogue_DIALOGUE;
	const static EventScriptCommand* doDialogueWithCaption_DIALOGUE;
	const static EventScriptCommand* doDialogueIfNew_DIALOGUE;
	const static EventScriptCommand* e007;
	const static EventScriptCommand* setSpriteBox0_ENTITY;
	const static EventScriptCommand* setSpriteBox1_ENTITY;
	const static EventScriptCommand* setSpriteBox0_SPRITE;
	const static EventScriptCommand* setSpriteBox1_SPRITE;
	const static EventScriptCommand* e008;
	const static EventScriptCommand* blockUntilTextBoxClosed;
	const static EventScriptCommand* blockUntilTextAnswerBoxClosed;
	const static EventScriptCommand* e009;
	const static EventScriptCommand* doCinematicTextNoBorder_DIALOGUE_INTy;

	const static EventScriptCommand* e025;
	const static EventScriptCommand* setDoorOpenAnimation_DOOR_BOOLopenClose;
	const static EventScriptCommand* setDoorActionIcon_DOOR_BOOLonOff;
	const static EventScriptCommand* setDoorDestination_DOOR_DOORdestination;
	const static EventScriptCommand* setAreaActionIcon_AREA_BOOLonOff;
	const static EventScriptCommand* setWarpDestination_WARP_WARPdestination;


	//public static final EventScriptCommand playVideo_VIDEO = new EventScriptCommand("playVideo_VIDEO","");
	const static EventScriptCommand* e010;


	const static EventScriptCommand* e012;
	const static EventScriptCommand* setCameraNoTarget;
	const static EventScriptCommand* setCameraTargetToArea_AREA;
	const static EventScriptCommand* setCameraTargetToEntity_ENTITY;
	const static EventScriptCommand* setCameraIgnoreBounds_BOOL;
	const static EventScriptCommand* setCameraTargetToPlayer;
	const static EventScriptCommand* blockUntilCameraReaches_AREA;
	const static EventScriptCommand* blockUntilCameraReaches_ENTITY;
	const static EventScriptCommand* blockUntilCameraReachesPlayer;
	const static EventScriptCommand* pushCameraState;
	const static EventScriptCommand* popCameraState;
	const static EventScriptCommand* setKeyboardCameraZoom_BOOL;
	const static EventScriptCommand* enableKeyboardCameraZoom;
	const static EventScriptCommand* disableKeyboardCameraZoom;
	const static EventScriptCommand* setCameraAutoZoomByPlayerMovement_BOOL;
	const static EventScriptCommand* enableCameraAutoZoomByPlayerMovement;
	const static EventScriptCommand* disableCameraAutoZoomByPlayerMovement;
	const static EventScriptCommand* setCameraZoom_FLOAT;
	const static EventScriptCommand* setCameraSpeed_FLOAT;


	const static EventScriptCommand* setPlayerToTempPlayerWithSprite_SPRITE;
	const static EventScriptCommand* setPlayerToNormalPlayer;
	const static EventScriptCommand* setPlayerExists_BOOL;
	const static EventScriptCommand* setPlayerControlsEnabled_BOOL;
	const static EventScriptCommand* enablePlayerControls;
	const static EventScriptCommand* disablePlayerControls;
	const static EventScriptCommand* setPlayerAutoPilot_BOOL;
	const static EventScriptCommand* setPlayerShowNameCaption_BOOL;
	const static EventScriptCommand* setPlayerShowAccountTypeCaption_BOOL;

	const static EventScriptCommand* playerSetBehaviorQueueOnOff_BOOL;
	const static EventScriptCommand* playerSetToArea_AREA;
	const static EventScriptCommand* playerSetToDoor_DOOR;
	const static EventScriptCommand* playerSetToTileXY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* playerWalkToArea_AREA;
	const static EventScriptCommand* playerWalkToDoor_DOOR;
	const static EventScriptCommand* playerWalkToEntity_ENTITY;
	const static EventScriptCommand* playerWalkToTileXY_INTxTile1X_INTyTile1X;
	//	public static final EventScriptCommand playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	const static EventScriptCommand* playerBlockUntilReachesArea_AREA;
	const static EventScriptCommand* playerBlockUntilReachesDoor_DOOR;
	const static EventScriptCommand* playerBlockUntilReachesEntity_ENTITY;
	const static EventScriptCommand* playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* playerWalkToAreaAndBlockUntilThere_AREA;
	const static EventScriptCommand* playerWalkToEntityAndBlockUntilThere_ENTITY;
	const static EventScriptCommand* playerWalkToDoorAndBlockUntilThere_DOOR;
	const static EventScriptCommand* playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* playerStandAndShuffle;
	//	public static final EventScriptCommand playerStandAndShuffleAndFacePlayer = new EventScriptCommand("playerStandAndShuffleAndFacePlayer","");
	const static EventScriptCommand* playerStandAndShuffleAndFaceEntity_ENTITY;
	//	public static final EventScriptCommand playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName","");
	//	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName","");
	const static EventScriptCommand* playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame;
	const static EventScriptCommand* playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame;
	const static EventScriptCommand* playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static EventScriptCommand* playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static EventScriptCommand* playerStopAnimating;
	const static EventScriptCommand* playerSetGlobalAnimationDisabled_BOOL;
	const static EventScriptCommand* playerSetMovementSpeed_INTticksPerPixel;
	const static EventScriptCommand* playerSetFaceMovementDirection_STRINGdirection;
	//	public static final EventScriptCommand playerSetNonWalkable_BOOL = new EventScriptCommand("playerSetNonWalkable_BOOL","");
	//	public static final EventScriptCommand playerSetPushable_BOOL = new EventScriptCommand("playerSetPushable_BOOL","");
	const static EventScriptCommand* playerSetToAlpha_FLOAT;
	//public static final EventScriptCommand playerFadeOutDelete = new EventScriptCommand("playerFadeOutDelete","");
	//public static final EventScriptCommand playerDeleteInstantly = new EventScriptCommand("playerDeleteInstantly","");


	//	public static final EventScriptCommand thisEntitySetBehaviorQueueOnOff_BOOL = new EventScriptCommand("thisEntitySetBehaviorQueueOnOff_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToArea_AREA = new EventScriptCommand("thisEntitySetToArea_AREA","");
	//	public static final EventScriptCommand thisEntitySetToDoor_DOOR = new EventScriptCommand("thisEntitySetToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntitySetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntitySetToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityWalkToArea_AREA = new EventScriptCommand("thisEntityWalkToArea_AREA","");
	//	public static final EventScriptCommand thisEntityWalkToDoor_DOOR = new EventScriptCommand("thisEntityWalkToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityWalkToEntity_ENTITY = new EventScriptCommand("thisEntityWalkToEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityWalkToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesArea_AREA = new EventScriptCommand("thisEntityBlockUntilReachesArea_AREA","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesDoor_DOOR = new EventScriptCommand("thisEntityBlockUntilReachesDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesEntity_ENTITY = new EventScriptCommand("thisEntityBlockUntilReachesEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityStandAndShuffle = new EventScriptCommand("thisEntityStandAndShuffle","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFacePlayer = new EventScriptCommand("thisEntityStandAndShuffleAndFacePlayer","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("thisEntityStandAndShuffleAndFaceEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityStopAnimating = new EventScriptCommand("thisEntityStopAnimating","");
	//	public static final EventScriptCommand thisEntitySetGlobalAnimationDisabled_BOOL = new EventScriptCommand("thisEntitySetGlobalAnimationDisabled_BOOL","");
	//	public static final EventScriptCommand thisEntitySetMovementSpeed_INTticksPerPixel = new EventScriptCommand("thisEntitySetMovementSpeed_INTticksPerPixel","");
	//	public static final EventScriptCommand thisEntitySetFaceMovementDirection_STRINGdirection = new EventScriptCommand("thisEntitySetFaceMovementDirection_STRINGdirection","");
	//	public static final EventScriptCommand thisEntitySetNonWalkable_BOOL = new EventScriptCommand("thisEntitySetNonWalkable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetPushable_BOOL = new EventScriptCommand("thisEntitySetPushable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToAlpha_FLOAT = new EventScriptCommand("thisEntitySetToAlpha_FLOAT","");
	//	public static final EventScriptCommand thisEntityFadeOutDelete = new EventScriptCommand("thisEntityFadeOutDelete","");
	//	public static final EventScriptCommand thisEntityDeleteInstantly = new EventScriptCommand("thisEntityDeleteInstantly","");


	const static EventScriptCommand* e024;
	const static EventScriptCommand* entitySetBehaviorQueueOnOff_ENTITY_BOOL;
	const static EventScriptCommand* entitySetToArea_ENTITY_AREA;
	const static EventScriptCommand* entitySetToDoor_ENTITY_DOOR;
	const static EventScriptCommand* entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* entityWalkToArea_ENTITY_AREA;
	const static EventScriptCommand* entityWalkToDoor_ENTITY_DOOR;
	const static EventScriptCommand* entityWalkToEntity_ENTITY_ENTITY;
	const static EventScriptCommand* entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static EventScriptCommand* entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static EventScriptCommand* entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static EventScriptCommand* entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static EventScriptCommand* entityBlockUntilReachesArea_ENTITY_AREA;
	const static EventScriptCommand* entityBlockUntilReachesDoor_ENTITY_DOOR;
	const static EventScriptCommand* entityBlockUntilReachesEntity_ENTITY_ENTITY;
	const static EventScriptCommand* entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* entityWalkToAreaAndBlockUntilThere_ENTITY_AREA;
	const static EventScriptCommand* entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY;
	const static EventScriptCommand* entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR;
	const static EventScriptCommand* entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X;
	const static EventScriptCommand* entityStandAndShuffle_ENTITY;
	const static EventScriptCommand* entityStandAndShuffleAndFacePlayer_ENTITY;
	const static EventScriptCommand* entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY;
	const static EventScriptCommand* entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static EventScriptCommand* entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static EventScriptCommand* entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static EventScriptCommand* entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static EventScriptCommand* entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static EventScriptCommand* entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName;
	const static EventScriptCommand* entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static EventScriptCommand* entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static EventScriptCommand* entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static EventScriptCommand* entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static EventScriptCommand* entityStopAnimating_ENTITY;
	const static EventScriptCommand* entitySetGlobalAnimationDisabled_ENTITY_BOOL;
	const static EventScriptCommand* entitySetMovementSpeed_ENTITY_INTticksPerPixel;
	const static EventScriptCommand* entitySetFaceMovementDirection_ENTITY_STRINGdirection;
	const static EventScriptCommand* entitySetNonWalkable_ENTITY_BOOL;
	const static EventScriptCommand* entitySetPushable_ENTITY_BOOL;
	const static EventScriptCommand* entitySetToAlpha_ENTITY_FLOAT;
	const static EventScriptCommand* entityFadeOutDelete_ENTITY;
	const static EventScriptCommand* entityDeleteInstantly_ENTITY;

	const static EventScriptCommand* e016;
	const static EventScriptCommand* spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA;
	const static EventScriptCommand* spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static EventScriptCommand* spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA;
	const static EventScriptCommand* spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static EventScriptCommand* e017;
	const static EventScriptCommand* createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static EventScriptCommand* createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static EventScriptCommand* createScreenSpriteUnderText_SPRITE_INTx_INTy;
	const static EventScriptCommand* createScreenSpriteOverText_SPRITE_INTx_INTy;


	const static EventScriptCommand* e026;
	const static EventScriptCommand* giveItem_ITEM;
	const static EventScriptCommand* takeItem_ITEM;
	const static EventScriptCommand* giveGame_GAME;
	const static EventScriptCommand* takeMoney_FLOAT;
	const static EventScriptCommand* giveMoney_FLOAT;

	const static EventScriptCommand* e027;
	const static EventScriptCommand* playSound_SOUND;
	const static EventScriptCommand* playSound_SOUND_FLOATvol;
	const static EventScriptCommand* playSound_SOUND_FLOATvol_FLOATpitch_INTtimes;
	const static EventScriptCommand* playMusicOnce_MUSIC;
	const static EventScriptCommand* playMusicLoop_MUSIC;
	const static EventScriptCommand* playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop;
	const static EventScriptCommand* stopAllMusic;
	const static EventScriptCommand* stopMusic_MUSIC;
	const static EventScriptCommand* fadeOutMusic_MUSIC_INT;
	const static EventScriptCommand* blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC;
	const static EventScriptCommand* blockUntilMusicDone_MUSIC;
	const static EventScriptCommand* fadeOutAllMusic_INT;
	const static EventScriptCommand* blockUntilAllMusicDone;

	const static EventScriptCommand* e028;
	const static EventScriptCommand* shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake;
	const static EventScriptCommand* fadeToBlack_INTticks;
	const static EventScriptCommand* fadeFromBlack_INTticks;
	const static EventScriptCommand* fadeToWhite_INTticks;
	const static EventScriptCommand* fadeFromWhite_INTticks;
	const static EventScriptCommand* e029;
	const static EventScriptCommand* fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static EventScriptCommand* fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha;
	const static EventScriptCommand* fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static EventScriptCommand* setInstantOverlay_INTr_INTg_INTb_FLOATa;
	const static EventScriptCommand* clearOverlay;

	const static EventScriptCommand* fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static EventScriptCommand* setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa;
	const static EventScriptCommand* clearOverlayUnderLights;

	const static EventScriptCommand* fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static EventScriptCommand* setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa;
	const static EventScriptCommand* clearOverlayGroundLayer;

	const static EventScriptCommand* e030;
	const static EventScriptCommand* setLetterbox_BOOL;
	const static EventScriptCommand* setLetterbox_BOOL_INTticks;
	const static EventScriptCommand* setLetterbox_BOOL_INTticks_INTsize;
	const static EventScriptCommand* setLetterbox_BOOL_INTticks_FLOATsize;
	const static EventScriptCommand* setBlur_BOOL;
	const static EventScriptCommand* setMosaic_BOOL;
	const static EventScriptCommand* setHBlankWave_BOOL;
	const static EventScriptCommand* setRotate_BOOL;
	const static EventScriptCommand* setBlackAndWhite_BOOL;
	const static EventScriptCommand* setInvertedColors_BOOL;
	const static EventScriptCommand* set8BitMode_BOOL;
	const static EventScriptCommand* e031;
	const static EventScriptCommand* setEngineSpeed_FLOAT;
	const static EventScriptCommand* e032;
	const static EventScriptCommand* toggleLightOnOff_LIGHT;
	const static EventScriptCommand* setLightOnOff_LIGHT_BOOL;
	const static EventScriptCommand* setLightFlicker_LIGHT_BOOL;
	const static EventScriptCommand* toggleAllLightsOnOff;
	const static EventScriptCommand* setAllLightsOnOff_BOOL;
	const static EventScriptCommand* e033;
	const static EventScriptCommand* setRandomSpawn_BOOL;
	const static EventScriptCommand* deleteRandoms;
	const static EventScriptCommand* e034;
	const static EventScriptCommand* makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static EventScriptCommand* makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb;
	const static EventScriptCommand* makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb;
	const static EventScriptCommand* makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static EventScriptCommand* setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks;


	const static EventScriptCommand* e035;
	const static EventScriptCommand* setShowClockCaption_BOOL;
	const static EventScriptCommand* setShowDayCaption_BOOL;
	const static EventScriptCommand* setShowMoneyCaption_BOOL;
	const static EventScriptCommand* setShowAllStatusBarCaptions_BOOL;
	const static EventScriptCommand* setShowStatusBar_BOOL;

	const static EventScriptCommand* setShowNDButton_BOOL;
	const static EventScriptCommand* setShowGameStoreButton_BOOL;
	const static EventScriptCommand* setShowStuffButton_BOOL;
	const static EventScriptCommand* setShowAllButtons_BOOL;

	const static EventScriptCommand* setNDEnabled_BOOL;
	const static EventScriptCommand* setGameStoreMenuEnabled_BOOL;
	const static EventScriptCommand* setStuffMenuEnabled_BOOL;
	const static EventScriptCommand* setAllMenusAndNDEnabled_BOOL;


	const static EventScriptCommand* e046;
	const static EventScriptCommand* setClockUnknown;
	const static EventScriptCommand* setClockNormal;
	const static EventScriptCommand* setTimePaused_BOOL;
	const static EventScriptCommand* setTimeFastForward;
	const static EventScriptCommand* setTimeNormalSpeed;
	const static EventScriptCommand* e037;


	const static EventScriptCommand* setNDOpen_BOOL;
	const static EventScriptCommand* startGame;
	const static EventScriptCommand* startBobsGameOnStadiumScreen_AREA;
	const static EventScriptCommand* blockUntilBobsGameDead;
	const static EventScriptCommand* showLoginScreen;
	//public const static final EventScriptCommand closeND = new EventScriptCommand("closeND","");

	const static EventScriptCommand* e038;
	const static EventScriptCommand* closeAllMenusAndND;

	//public const static final EventScriptCommand enableAllMenus = new EventScriptCommand("enableAllMenus","");
	const static EventScriptCommand* e039;
	const static EventScriptCommand* openStuffMenu;
	const static EventScriptCommand* openItemsMenu;
	const static EventScriptCommand* openLogMenu;
	const static EventScriptCommand* openStatusMenu;
	const static EventScriptCommand* openFriendsMenu;
	const static EventScriptCommand* openSettingsMenu;
	const static EventScriptCommand* openGameStoreMenu;

	//	static final EventScriptCommand e040 = new EventScriptCommand();
	//	public static final EventScriptCommand pushGameState = new EventScriptCommand("pushGameState","");
	//	public static final EventScriptCommand popGameState = new EventScriptCommand("popGameState","");
	//	static final EventScriptCommand e041 = new EventScriptCommand();
	//	public static final EventScriptCommand showTitleScreen = new EventScriptCommand("showTitleScreen","");
	//	public static final EventScriptCommand showCinemaEvent = new EventScriptCommand("showCinemaEvent","");
	//	public static final EventScriptCommand runGlobalEvent = new EventScriptCommand("runGlobalEvent","");
	//	static final EventScriptCommand e042 = new EventScriptCommand();
};

class EventScriptTree
{
private:
	EventData* outerInstance = nullptr;

public:
	EventScriptTree(EventData* outerInstance);


	//public String toEventText();

	//TODO: should unify all the event parsing stuff into a class here instead of having basically the same thing in both client and editor.
};