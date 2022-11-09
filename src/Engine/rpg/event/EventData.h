//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
#include "GameStringData.h"
#include "DialogueData.h"
#include "FlagData.h"
#include "SkillData.h"
#include "src/Utility/AssetData.h"
#include "src/Utility/audio/AudioData.h"

class Logger;




//TODO make comment structure for these


class EventScriptCommand : public std::enable_shared_from_this<EventScriptCommand>
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


class EventScriptQualifier : public EventScriptCommand, public std::enable_shared_from_this<EventScriptQualifier>
{
public:
	EventScriptQualifier(const string& command, const string& comment);
};





class EventData : public AssetData, public std::enable_shared_from_this<EventData>
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
	vector<sp<DialogueData>> dialogueDataList;// = ms<ArrayList><sp<DialogueData>>();
	vector<sp<FlagData>> flagDataList;// = ms<ArrayList><sp<FlagData>>();
	vector<sp<SkillData>> skillDataList;// = ms<ArrayList><sp<SkillData>>();
	vector<sp<GameStringData>> gameStringDataList;// = ms<ArrayList><sp<GameStringData>>();
	vector<sp<AudioData>> musicDataList;// = ms<ArrayList><sp<AudioData>>();
	vector<sp<AudioData>> soundDataList;// = ms<ArrayList><sp<AudioData>>();





public:

	static Logger log;


	EventData();


	EventData(int id, const string& name, int type, const string& comment, const string& text);

	virtual string& initFromString(string& t) override;

	//static sp<EventData> fromBase64ZippedJSON(const string& b64);


	//static sp<EventData> fromJSON(const string& json);


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
	static vector<sp<EventScriptCommand>> commandList;
	static vector<sp<EventScriptQualifier>> qualifierList;


	const static sp<EventScriptQualifier> isPlayerTouchingThisArea;
	const static sp<EventScriptQualifier> isPlayerWalkingIntoThisDoor;
	const static sp<EventScriptQualifier> isPlayerTouchingThisEntity;
	const static sp<EventScriptQualifier> isPlayerTouchingAnyEntityUsingThisSprite;
	const static sp<EventScriptQualifier> isPlayerWalkingIntoDoor_DOOR;
	const static sp<EventScriptQualifier> isPlayerWalkingIntoWarp_WARP;
	const static sp<EventScriptQualifier> isActionButtonHeld;
	const static sp<EventScriptQualifier> isPlayerAutoPilotOn;
	const static sp<EventScriptQualifier> isFlagSet_FLAG;
	const static sp<EventScriptQualifier> hasSkillAtLeast_SKILL_FLOAT1;
	const static sp<EventScriptQualifier> isCurrentState_STATE;
	const static sp<EventScriptQualifier> isPlayerStandingInArea_AREA;
	const static sp<EventScriptQualifier> isEntityStandingInArea_ENTITY_AREA;
	const static sp<EventScriptQualifier> hourPastOrEqualTo_INT23;
	const static sp<EventScriptQualifier> hourLessThan_INT23;
	const static sp<EventScriptQualifier> minutePastOrEqualTo_INT59;
	const static sp<EventScriptQualifier> minuteLessThan_INT59;
	const static sp<EventScriptQualifier> hasMoneyAtLeastAmount_FLOAT;
	const static sp<EventScriptQualifier> hasMoneyLessThanAmount_FLOAT;
	const static sp<EventScriptQualifier> hasItem_ITEM;
	const static sp<EventScriptQualifier> hasGame_GAME;
	const static sp<EventScriptQualifier> isPlayerMale;
	const static sp<EventScriptQualifier> isPlayerFemale;
	const static sp<EventScriptQualifier> isAnyEntityUsingSprite_SPRITE;
	const static sp<EventScriptQualifier> isAnyEntityUsingSpriteAtArea_SPRITE_AREA;
	const static sp<EventScriptQualifier> isEntitySpawned_ENTITY;
	const static sp<EventScriptQualifier> isEntityAtArea_ENTITY_AREA;
	const static sp<EventScriptQualifier> isAreaEmpty_AREA;
	const static sp<EventScriptQualifier> hasFinishedDialogue_DIALOGUE;
	const static sp<EventScriptQualifier> isTextBoxOpen;
	const static sp<EventScriptQualifier> isTextAnswerBoxOpen;
	const static sp<EventScriptQualifier> isTextAnswerSelected_INT4;
	const static sp<EventScriptQualifier> isTextAnswerSelected_STRING;
	const static sp<EventScriptQualifier> randomEqualsOneOutOfLessThan_INT;
	const static sp<EventScriptQualifier> randomEqualsOneOutOfIncluding_INT;
	const static sp<EventScriptQualifier> isAnyMusicPlaying;
	const static sp<EventScriptQualifier> isMusicPlaying_MUSIC;
	const static sp<EventScriptQualifier> isRaining;
	const static sp<EventScriptQualifier> isWindy;
	const static sp<EventScriptQualifier> isSnowing;
	const static sp<EventScriptQualifier> isFoggy;
	//	public static final EventScriptQualifier isPlayerHolding = ms<EventScriptQualifier>("isPlayerHolding_ITEM","");
	//	public static final EventScriptQualifier isPlayerWearing = ms<EventScriptQualifier>("isPlayerWearing_ITEM","");
	const static sp<EventScriptQualifier> isMapOutside;
	const static sp<EventScriptQualifier> hasTalkedToThisToday;
	const static sp<EventScriptQualifier> hasBeenMinutesSinceFlagSet_FLAG_INT;
	const static sp<EventScriptQualifier> hasBeenHoursSinceFlagSet_FLAG_INT23;
	const static sp<EventScriptQualifier> hasBeenDaysSinceFlagSet_FLAG_INT;
	const static sp<EventScriptQualifier> isThisActivated;
	const static sp<EventScriptQualifier> haveSecondsPassedSinceActivated_INT;
	const static sp<EventScriptQualifier> haveMinutesPassedSinceActivated_INT;
	const static sp<EventScriptQualifier> haveHoursPassedSinceActivated_INT;
	const static sp<EventScriptQualifier> haveDaysPassedSinceActivated_INT;
	const static sp<EventScriptQualifier> hasActivatedThisEver;
	const static sp<EventScriptQualifier> hasActivatedThisSinceEnterRoom;
	const static sp<EventScriptQualifier> hasBeenHereEver;
	const static sp<EventScriptQualifier> hasBeenHereSinceEnterRoom;
	const static sp<EventScriptQualifier> haveSecondsPassedSinceBeenHere_INT;
	const static sp<EventScriptQualifier> haveMinutesPassedSinceBeenHere_INT;
	const static sp<EventScriptQualifier> haveHoursPassedSinceBeenHere_INT;
	const static sp<EventScriptQualifier> haveDaysPassedSinceBeenHere_INT;
	const static sp<EventScriptQualifier> isLightOn_LIGHT;


	//commands
	const static sp<EventScriptCommand> alwaysBlockWhileNotStandingHere;
	//doesn't delete from the stack, checks every time, continues stack underneath normally.
	//this is an alternative to having an option for deleting the stack when not standing in area
	//instead of deleting the stack
	//this could cause state problems like NPC AI getting stuck off, etc.


	const static sp<EventScriptCommand> e00;
	const static sp<EventScriptCommand> blockUntilActionButtonPressed; //BLOCK//doesn't delete from the stack until valid, doesn't proceed until it is.
	const static sp<EventScriptCommand> blockUntilActionCaptionButtonPressed_STRING; //BLOCK//this will stay in the queue checking if we are standing here, use ACTION_area
	const static sp<EventScriptCommand> blockUntilCancelButtonPressed; //BLOCK
	const static sp<EventScriptCommand> blockForTicks_INT; //BLOCK
	const static sp<EventScriptCommand> blockUntilClockHour_INT23; //BLOCK
	const static sp<EventScriptCommand> blockUntilClockMinute_INT59; //BLOCK
	const static sp<EventScriptCommand> e000;
	const static sp<EventScriptCommand> loadMapState_STATE;
	const static sp<EventScriptCommand> runEvent_EVENT;
	const static sp<EventScriptCommand> blockUntilEventDone_EVENT;
	const static sp<EventScriptCommand> clearThisEvent;
	const static sp<EventScriptCommand> clearEvent_EVENT;
	const static sp<EventScriptCommand> e001;
	const static sp<EventScriptCommand> setThisActivated_BOOL;
	const static sp<EventScriptCommand> toggleThisActivated;
	const static sp<EventScriptCommand> e002;
	const static sp<EventScriptCommand> setLastBeenHereTime;
	const static sp<EventScriptCommand> resetLastBeenHereTime;
	const static sp<EventScriptCommand> e003;
	const static sp<EventScriptCommand> setFlag_FLAG_BOOL;
	const static sp<EventScriptCommand> setFlagTrue_FLAG;
	const static sp<EventScriptCommand> setFlagFalse_FLAG;
	const static sp<EventScriptCommand> e004;
	const static sp<EventScriptCommand> giveSkillPoints_SKILL_INT;
	const static sp<EventScriptCommand> removeSkillPoints_SKILL_INT;
	const static sp<EventScriptCommand> setSkillPoints_SKILL_INT;
	const static sp<EventScriptCommand> e005;

	const static sp<EventScriptCommand> enterThisDoor;
	const static sp<EventScriptCommand> enterThisWarp;
	const static sp<EventScriptCommand> enterDoor_DOOR;
	const static sp<EventScriptCommand> enterWarp_WARP;
	const static sp<EventScriptCommand> changeMap_MAP_AREA;
	const static sp<EventScriptCommand> changeMap_MAP_DOOR;
	const static sp<EventScriptCommand> changeMap_MAP_WARP;
	const static sp<EventScriptCommand> changeMap_MAP_INT_INT;
	const static sp<EventScriptCommand> e006;
	const static sp<EventScriptCommand> doDialogue_DIALOGUE;
	const static sp<EventScriptCommand> doDialogueWithCaption_DIALOGUE;
	const static sp<EventScriptCommand> doDialogueIfNew_DIALOGUE;
	const static sp<EventScriptCommand> e007;
	const static sp<EventScriptCommand> setSpriteBox0_ENTITY;
	const static sp<EventScriptCommand> setSpriteBox1_ENTITY;
	const static sp<EventScriptCommand> setSpriteBox0_SPRITE;
	const static sp<EventScriptCommand> setSpriteBox1_SPRITE;
	const static sp<EventScriptCommand> e008;
	const static sp<EventScriptCommand> blockUntilTextBoxClosed;
	const static sp<EventScriptCommand> blockUntilTextAnswerBoxClosed;
	const static sp<EventScriptCommand> e009;
	const static sp<EventScriptCommand> doCinematicTextNoBorder_DIALOGUE_INTy;

	const static sp<EventScriptCommand> e025;
	const static sp<EventScriptCommand> setDoorOpenAnimation_DOOR_BOOLopenClose;
	const static sp<EventScriptCommand> setDoorActionIcon_DOOR_BOOLonOff;
	const static sp<EventScriptCommand> setDoorDestination_DOOR_DOORdestination;
	const static sp<EventScriptCommand> setAreaActionIcon_AREA_BOOLonOff;
	const static sp<EventScriptCommand> setWarpDestination_WARP_WARPdestination;


	//public static final EventScriptCommand playVideo_VIDEO = ms<EventScriptCommand>("playVideo_VIDEO","");
	const static sp<EventScriptCommand> e010;


	const static sp<EventScriptCommand> e012;
	const static sp<EventScriptCommand> setCameraNoTarget;
	const static sp<EventScriptCommand> setCameraTargetToArea_AREA;
	const static sp<EventScriptCommand> setCameraTargetToEntity_ENTITY;
	const static sp<EventScriptCommand> setCameraIgnoreBounds_BOOL;
	const static sp<EventScriptCommand> setCameraTargetToPlayer;
	const static sp<EventScriptCommand> blockUntilCameraReaches_AREA;
	const static sp<EventScriptCommand> blockUntilCameraReaches_ENTITY;
	const static sp<EventScriptCommand> blockUntilCameraReachesPlayer;
	const static sp<EventScriptCommand> pushCameraState;
	const static sp<EventScriptCommand> popCameraState;
	const static sp<EventScriptCommand> setKeyboardCameraZoom_BOOL;
	const static sp<EventScriptCommand> enableKeyboardCameraZoom;
	const static sp<EventScriptCommand> disableKeyboardCameraZoom;
	const static sp<EventScriptCommand> setCameraAutoZoomByPlayerMovement_BOOL;
	const static sp<EventScriptCommand> enableCameraAutoZoomByPlayerMovement;
	const static sp<EventScriptCommand> disableCameraAutoZoomByPlayerMovement;
	const static sp<EventScriptCommand> setCameraZoom_FLOAT;
	const static sp<EventScriptCommand> setCameraSpeed_FLOAT;


	const static sp<EventScriptCommand> setPlayerToTempPlayerWithSprite_SPRITE;
	const static sp<EventScriptCommand> setPlayerToNormalPlayer;
	const static sp<EventScriptCommand> setPlayerExists_BOOL;
	const static sp<EventScriptCommand> setPlayerControlsEnabled_BOOL;
	const static sp<EventScriptCommand> enablePlayerControls;
	const static sp<EventScriptCommand> disablePlayerControls;
	const static sp<EventScriptCommand> setPlayerAutoPilot_BOOL;
	const static sp<EventScriptCommand> setPlayerShowNameCaption_BOOL;
	const static sp<EventScriptCommand> setPlayerShowAccountTypeCaption_BOOL;

	const static sp<EventScriptCommand> playerSetBehaviorQueueOnOff_BOOL;
	const static sp<EventScriptCommand> playerSetToArea_AREA;
	const static sp<EventScriptCommand> playerSetToDoor_DOOR;
	const static sp<EventScriptCommand> playerSetToTileXY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> playerWalkToArea_AREA;
	const static sp<EventScriptCommand> playerWalkToDoor_DOOR;
	const static sp<EventScriptCommand> playerWalkToEntity_ENTITY;
	const static sp<EventScriptCommand> playerWalkToTileXY_INTxTile1X_INTyTile1X;
	//	public static final EventScriptCommand playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("playerMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("playerMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("playerMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("playerMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	const static sp<EventScriptCommand> playerBlockUntilReachesArea_AREA;
	const static sp<EventScriptCommand> playerBlockUntilReachesDoor_DOOR;
	const static sp<EventScriptCommand> playerBlockUntilReachesEntity_ENTITY;
	const static sp<EventScriptCommand> playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> playerWalkToAreaAndBlockUntilThere_AREA;
	const static sp<EventScriptCommand> playerWalkToEntityAndBlockUntilThere_ENTITY;
	const static sp<EventScriptCommand> playerWalkToDoorAndBlockUntilThere_DOOR;
	const static sp<EventScriptCommand> playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> playerStandAndShuffle;
	//	public static final EventScriptCommand playerStandAndShuffleAndFacePlayer = ms<EventScriptCommand>("playerStandAndShuffleAndFacePlayer","");
	const static sp<EventScriptCommand> playerStandAndShuffleAndFaceEntity_ENTITY;
	//	public static final EventScriptCommand playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerSetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand playerDoAnimationByNameOnce_STRINGanimationName = ms<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName","");
	//	public static final EventScriptCommand playerDoAnimationByNameLoop_STRINGanimationName = ms<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName","");
	const static sp<EventScriptCommand> playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame;
	const static sp<EventScriptCommand> playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame;
	const static sp<EventScriptCommand> playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> playerStopAnimating;
	const static sp<EventScriptCommand> playerSetGlobalAnimationDisabled_BOOL;
	const static sp<EventScriptCommand> playerSetMovementSpeed_INTticksPerPixel;
	const static sp<EventScriptCommand> playerSetFaceMovementDirection_STRINGdirection;
	//	public static final EventScriptCommand playerSetNonWalkable_BOOL = ms<EventScriptCommand>("playerSetNonWalkable_BOOL","");
	//	public static final EventScriptCommand playerSetPushable_BOOL = ms<EventScriptCommand>("playerSetPushable_BOOL","");
	const static sp<EventScriptCommand> playerSetToAlpha_FLOAT;
	//public static final EventScriptCommand playerFadeOutDelete = ms<EventScriptCommand>("playerFadeOutDelete","");
	//public static final EventScriptCommand playerDeleteInstantly = ms<EventScriptCommand>("playerDeleteInstantly","");


	//	public static final EventScriptCommand thisEntitySetBehaviorQueueOnOff_BOOL = ms<EventScriptCommand>("thisEntitySetBehaviorQueueOnOff_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToArea_AREA = ms<EventScriptCommand>("thisEntitySetToArea_AREA","");
	//	public static final EventScriptCommand thisEntitySetToDoor_DOOR = ms<EventScriptCommand>("thisEntitySetToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntitySetToTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("thisEntitySetToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityWalkToArea_AREA = ms<EventScriptCommand>("thisEntityWalkToArea_AREA","");
	//	public static final EventScriptCommand thisEntityWalkToDoor_DOOR = ms<EventScriptCommand>("thisEntityWalkToDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityWalkToEntity_ENTITY = ms<EventScriptCommand>("thisEntityWalkToEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityWalkToTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("thisEntityWalkToTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("thisEntityMoveToArea_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("thisEntityMoveToDoor_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("thisEntityMoveToEntity_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("thisEntityMoveToTileXY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesArea_AREA = ms<EventScriptCommand>("thisEntityBlockUntilReachesArea_AREA","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesDoor_DOOR = ms<EventScriptCommand>("thisEntityBlockUntilReachesDoor_DOOR","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesEntity_ENTITY = ms<EventScriptCommand>("thisEntityBlockUntilReachesEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("thisEntityBlockUntilReachesTileXY_INTxTile1X_INTyTile1X","");
	//	public static final EventScriptCommand thisEntityStandAndShuffle = ms<EventScriptCommand>("thisEntityStandAndShuffle","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFacePlayer = ms<EventScriptCommand>("thisEntityStandAndShuffleAndFacePlayer","");
	//	public static final EventScriptCommand thisEntityStandAndShuffleAndFaceEntity_ENTITY = ms<EventScriptCommand>("thisEntityStandAndShuffleAndFaceEntity_ENTITY","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityAnimateOnceThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityAnimateLoopThroughCurrentAnimationFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityAnimateOnceThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityAnimateLoopThroughAllFrames_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntitySetAnimateRandomFrames_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("thisEntityDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks","");
	//	public static final EventScriptCommand thisEntityStopAnimating = ms<EventScriptCommand>("thisEntityStopAnimating","");
	//	public static final EventScriptCommand thisEntitySetGlobalAnimationDisabled_BOOL = ms<EventScriptCommand>("thisEntitySetGlobalAnimationDisabled_BOOL","");
	//	public static final EventScriptCommand thisEntitySetMovementSpeed_INTticksPerPixel = ms<EventScriptCommand>("thisEntitySetMovementSpeed_INTticksPerPixel","");
	//	public static final EventScriptCommand thisEntitySetFaceMovementDirection_STRINGdirection = ms<EventScriptCommand>("thisEntitySetFaceMovementDirection_STRINGdirection","");
	//	public static final EventScriptCommand thisEntitySetNonWalkable_BOOL = ms<EventScriptCommand>("thisEntitySetNonWalkable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetPushable_BOOL = ms<EventScriptCommand>("thisEntitySetPushable_BOOL","");
	//	public static final EventScriptCommand thisEntitySetToAlpha_FLOAT = ms<EventScriptCommand>("thisEntitySetToAlpha_FLOAT","");
	//	public static final EventScriptCommand thisEntityFadeOutDelete = ms<EventScriptCommand>("thisEntityFadeOutDelete","");
	//	public static final EventScriptCommand thisEntityDeleteInstantly = ms<EventScriptCommand>("thisEntityDeleteInstantly","");


	const static sp<EventScriptCommand> e024;
	const static sp<EventScriptCommand> entitySetBehaviorQueueOnOff_ENTITY_BOOL;
	const static sp<EventScriptCommand> entitySetToArea_ENTITY_AREA;
	const static sp<EventScriptCommand> entitySetToDoor_ENTITY_DOOR;
	const static sp<EventScriptCommand> entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> entityWalkToArea_ENTITY_AREA;
	const static sp<EventScriptCommand> entityWalkToDoor_ENTITY_DOOR;
	const static sp<EventScriptCommand> entityWalkToEntity_ENTITY_ENTITY;
	const static sp<EventScriptCommand> entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static sp<EventScriptCommand> entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static sp<EventScriptCommand> entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static sp<EventScriptCommand> entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal;
	const static sp<EventScriptCommand> entityBlockUntilReachesArea_ENTITY_AREA;
	const static sp<EventScriptCommand> entityBlockUntilReachesDoor_ENTITY_DOOR;
	const static sp<EventScriptCommand> entityBlockUntilReachesEntity_ENTITY_ENTITY;
	const static sp<EventScriptCommand> entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> entityWalkToAreaAndBlockUntilThere_ENTITY_AREA;
	const static sp<EventScriptCommand> entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY;
	const static sp<EventScriptCommand> entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR;
	const static sp<EventScriptCommand> entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X;
	const static sp<EventScriptCommand> entityStandAndShuffle_ENTITY;
	const static sp<EventScriptCommand> entityStandAndShuffleAndFacePlayer_ENTITY;
	const static sp<EventScriptCommand> entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY;
	const static sp<EventScriptCommand> entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName;
	const static sp<EventScriptCommand> entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static sp<EventScriptCommand> entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame;
	const static sp<EventScriptCommand> entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks;
	const static sp<EventScriptCommand> entityStopAnimating_ENTITY;
	const static sp<EventScriptCommand> entitySetGlobalAnimationDisabled_ENTITY_BOOL;
	const static sp<EventScriptCommand> entitySetMovementSpeed_ENTITY_INTticksPerPixel;
	const static sp<EventScriptCommand> entitySetFaceMovementDirection_ENTITY_STRINGdirection;
	const static sp<EventScriptCommand> entitySetNonWalkable_ENTITY_BOOL;
	const static sp<EventScriptCommand> entitySetPushable_ENTITY_BOOL;
	const static sp<EventScriptCommand> entitySetToAlpha_ENTITY_FLOAT;
	const static sp<EventScriptCommand> entityFadeOutDelete_ENTITY;
	const static sp<EventScriptCommand> entityDeleteInstantly_ENTITY;

	const static sp<EventScriptCommand> e016;
	const static sp<EventScriptCommand> spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA;
	const static sp<EventScriptCommand> spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static sp<EventScriptCommand> spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA;
	const static sp<EventScriptCommand> spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA;
	const static sp<EventScriptCommand> e017;
	const static sp<EventScriptCommand> createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static sp<EventScriptCommand> createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy;
	const static sp<EventScriptCommand> createScreenSpriteUnderText_SPRITE_INTx_INTy;
	const static sp<EventScriptCommand> createScreenSpriteOverText_SPRITE_INTx_INTy;


	const static sp<EventScriptCommand> e026;
	const static sp<EventScriptCommand> giveItem_ITEM;
	const static sp<EventScriptCommand> takeItem_ITEM;
	const static sp<EventScriptCommand> giveGame_GAME;
	const static sp<EventScriptCommand> takeMoney_FLOAT;
	const static sp<EventScriptCommand> giveMoney_FLOAT;

	const static sp<EventScriptCommand> e027;
	const static sp<EventScriptCommand> playSound_SOUND;
	const static sp<EventScriptCommand> playSound_SOUND_FLOATvol;
	const static sp<EventScriptCommand> playSound_SOUND_FLOATvol_FLOATpitch_INTtimes;
	const static sp<EventScriptCommand> playMusicOnce_MUSIC;
	const static sp<EventScriptCommand> playMusicLoop_MUSIC;
	const static sp<EventScriptCommand> playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop;
	const static sp<EventScriptCommand> stopAllMusic;
	const static sp<EventScriptCommand> stopMusic_MUSIC;
	const static sp<EventScriptCommand> fadeOutMusic_MUSIC_INT;
	const static sp<EventScriptCommand> blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC;
	const static sp<EventScriptCommand> blockUntilMusicDone_MUSIC;
	const static sp<EventScriptCommand> fadeOutAllMusic_INT;
	const static sp<EventScriptCommand> blockUntilAllMusicDone;

	const static sp<EventScriptCommand> e028;
	const static sp<EventScriptCommand> shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake;
	const static sp<EventScriptCommand> fadeToBlack_INTticks;
	const static sp<EventScriptCommand> fadeFromBlack_INTticks;
	const static sp<EventScriptCommand> fadeToWhite_INTticks;
	const static sp<EventScriptCommand> fadeFromWhite_INTticks;
	const static sp<EventScriptCommand> e029;
	const static sp<EventScriptCommand> fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static sp<EventScriptCommand> fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha;
	const static sp<EventScriptCommand> fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static sp<EventScriptCommand> setInstantOverlay_INTr_INTg_INTb_FLOATa;
	const static sp<EventScriptCommand> clearOverlay;

	const static sp<EventScriptCommand> fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static sp<EventScriptCommand> setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa;
	const static sp<EventScriptCommand> clearOverlayUnderLights;

	const static sp<EventScriptCommand> fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha;
	const static sp<EventScriptCommand> setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa;
	const static sp<EventScriptCommand> clearOverlayGroundLayer;

	const static sp<EventScriptCommand> e030;
	const static sp<EventScriptCommand> setLetterbox_BOOL;
	const static sp<EventScriptCommand> setLetterbox_BOOL_INTticks;
	const static sp<EventScriptCommand> setLetterbox_BOOL_INTticks_INTsize;
	const static sp<EventScriptCommand> setLetterbox_BOOL_INTticks_FLOATsize;
	const static sp<EventScriptCommand> setBlur_BOOL;
	const static sp<EventScriptCommand> setMosaic_BOOL;
	const static sp<EventScriptCommand> setHBlankWave_BOOL;
	const static sp<EventScriptCommand> setRotate_BOOL;
	const static sp<EventScriptCommand> setBlackAndWhite_BOOL;
	const static sp<EventScriptCommand> setInvertedColors_BOOL;
	const static sp<EventScriptCommand> set8BitMode_BOOL;
	const static sp<EventScriptCommand> e031;
	const static sp<EventScriptCommand> setEngineSpeed_FLOAT;
	const static sp<EventScriptCommand> e032;
	const static sp<EventScriptCommand> toggleLightOnOff_LIGHT;
	const static sp<EventScriptCommand> setLightOnOff_LIGHT_BOOL;
	const static sp<EventScriptCommand> setLightFlicker_LIGHT_BOOL;
	const static sp<EventScriptCommand> toggleAllLightsOnOff;
	const static sp<EventScriptCommand> setAllLightsOnOff_BOOL;
	const static sp<EventScriptCommand> e033;
	const static sp<EventScriptCommand> setRandomSpawn_BOOL;
	const static sp<EventScriptCommand> deleteRandoms;
	const static sp<EventScriptCommand> e034;
	const static sp<EventScriptCommand> makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static sp<EventScriptCommand> makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb;
	const static sp<EventScriptCommand> makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb;
	const static sp<EventScriptCommand> makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb;
	const static sp<EventScriptCommand> setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks;


	const static sp<EventScriptCommand> e035;
	const static sp<EventScriptCommand> setShowClockCaption_BOOL;
	const static sp<EventScriptCommand> setShowDayCaption_BOOL;
	const static sp<EventScriptCommand> setShowMoneyCaption_BOOL;
	const static sp<EventScriptCommand> setShowAllStatusBarCaptions_BOOL;
	const static sp<EventScriptCommand> setShowStatusBar_BOOL;

	const static sp<EventScriptCommand> setShowNDButton_BOOL;
	const static sp<EventScriptCommand> setShowGameStoreButton_BOOL;
	const static sp<EventScriptCommand> setShowStuffButton_BOOL;
	const static sp<EventScriptCommand> setShowAllButtons_BOOL;

	const static sp<EventScriptCommand> setNDEnabled_BOOL;
	const static sp<EventScriptCommand> setGameStoreMenuEnabled_BOOL;
	const static sp<EventScriptCommand> setStuffMenuEnabled_BOOL;
	const static sp<EventScriptCommand> setAllMenusAndNDEnabled_BOOL;


	const static sp<EventScriptCommand> e046;
	const static sp<EventScriptCommand> setClockUnknown;
	const static sp<EventScriptCommand> setClockNormal;
	const static sp<EventScriptCommand> setTimePaused_BOOL;
	const static sp<EventScriptCommand> setTimeFastForward;
	const static sp<EventScriptCommand> setTimeNormalSpeed;
	const static sp<EventScriptCommand> e037;


	const static sp<EventScriptCommand> setNDOpen_BOOL;
	const static sp<EventScriptCommand> startGame;
	const static sp<EventScriptCommand> startOKGameOnStadiumScreen_AREA;
	const static sp<EventScriptCommand> blockUntilOKGameDead;
	const static sp<EventScriptCommand> showLoginScreen;
	//public const static final EventScriptCommand closeND = ms<EventScriptCommand>("closeND","");

	const static sp<EventScriptCommand> e038;
	const static sp<EventScriptCommand> closeAllMenusAndND;

	//public const static final EventScriptCommand enableAllMenus = ms<EventScriptCommand>("enableAllMenus","");
	const static sp<EventScriptCommand> e039;
	const static sp<EventScriptCommand> openStuffMenu;
	const static sp<EventScriptCommand> openItemsMenu;
	const static sp<EventScriptCommand> openLogMenu;
	const static sp<EventScriptCommand> openStatusMenu;
	const static sp<EventScriptCommand> openFriendsMenu;
	const static sp<EventScriptCommand> openSettingsMenu;
	const static sp<EventScriptCommand> openGameStoreMenu;

	//	static final EventScriptCommand e040 = ms<EventScriptCommand>();
	//	public static final EventScriptCommand pushGameState = ms<EventScriptCommand>("pushGameState","");
	//	public static final EventScriptCommand popGameState = ms<EventScriptCommand>("popGameState","");
	//	static final EventScriptCommand e041 = ms<EventScriptCommand>();
	//	public static final EventScriptCommand showTitleScreen = ms<EventScriptCommand>("showTitleScreen","");
	//	public static final EventScriptCommand showCinemaEvent = ms<EventScriptCommand>("showCinemaEvent","");
	//	public static final EventScriptCommand runGlobalEvent = ms<EventScriptCommand>("runGlobalEvent","");
	//	static final EventScriptCommand e042 = ms<EventScriptCommand>();
};

class EventScriptTree
{
private:
	sp<EventData> outerInstance = nullptr;

public:
	EventScriptTree(sp<EventData> outerInstance);


	//public String toEventText();

	//TODO: should unify all the event parsing stuff into a class here instead of having basically the same thing in both client and editor.
};