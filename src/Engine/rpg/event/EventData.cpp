#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger EventData::log = Logger("EventData");


class EventScriptCommand;
class EventScriptQualifier;


EventData::EventData()
{ //=========================================================================================================================
}

EventData::EventData(int id, const string& name, int type, const string& comment, const string& text)
{ //=========================================================================================================================

	//AssetData(id, name);
	this->id = id;
	this->name = name;

	this->type = type;
	this->comment = comment;
	this->text = text;
}

//EventData* EventData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = new Gson();
//	//EventData data = gson.fromJson(json,EventData.class);
//
//	return fromJSON(json);
//}
//
//EventData* EventData::fromJSON(const string& json)
//{ //===============================================================================================
//
//	//Gson* gson = new Gson();
//	EventData* data = nullptr;//gson->fromJson(json, EventData::typeid);
//
//
//	return data;
//}


//===============================================================================================

string& EventData::initFromString(string& t)
{//===============================================================================================

	t = super::initFromString(t);

	t = t.substr(t.find("type:`") + 1);
	t = t.substr(t.find("`") + 1);
	type = stoi(t.substr(0, t.find("`")));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("comment:`") + 1);
	t = t.substr(t.find("`") + 1);
	comment = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);

	t = t.substr(t.find("text:`") + 1);
	t = t.substr(t.find("`") + 1);
	text = t.substr(0, t.find("`"));
	t = t.substr(t.find("`,") + 2);


	//ONLY FOR USE ON CLIENT, IGNORE THIS
	if (String::startsWith(t,"dialogueDataList"))
	{
		t = t.substr(t.find("dialogueDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			DialogueData* data = new DialogueData();
			t = data->initFromString(t);
			dialogueDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("flagDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			FlagData* data = new FlagData();
			t = data->initFromString(t);
			flagDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("skillDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			SkillData* data = new SkillData();
			t = data->initFromString(t);
			skillDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("gameStringDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			GameStringData* data = new GameStringData();
			t = data->initFromString(t);
			gameStringDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("musicDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			MusicData* data = new MusicData();
			t = data->initFromString(t);
			musicDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("soundDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			SoundData* data = new SoundData();
			t = data->initFromString(t);
			soundDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);
	}

	return t;
}



string EventData::getTYPEIDString()
{ //===============================================================================================
	return "EVENT." + to_string(getID());
}

int EventData::getType()
{
	return type;
}


string& EventData::getComment()
{
	return comment;
}


string& EventData::getText()
{
	return text;
}

void EventData::setType(int s)
{
	this->type = s;
}

void EventData::setComment(const string& s)
{
	this->comment = s;
}

void EventData::setText(const string& s)
{
	this->text = s;
}

int EventData::TYPE_PROJECT_INITIAL_LOADER = -3;
int EventData::TYPE_PROJECT_CUTSCENE_DONT_RUN_UNTIL_CALLED = -2;
int EventData::TYPE_MAP_RUN_ONCE_BEFORE_LOAD = -1;
int EventData::TYPE_NORMAL_REPEAT_WHILE_MAP_RUNNING = 0;
int EventData::TYPE_MAP_DONT_RUN_UNTIL_CALLED = 1;
int EventData::TYPE_MAP_RUN_ONCE_AFTER_LOAD = 2;

EventScriptTree::EventScriptTree(EventData* outerInstance) : outerInstance(outerInstance)
{
}


string EventScriptCommand::toString()
{
	return getCommandWithArguments();
}

EventScriptCommand::EventScriptCommand()
{
	this->command = "---";
}

EventScriptCommand::EventScriptCommand(const string& command, const string& comment)
{
	this->command = command;
	this->comment = comment;

	EventData::commandList->add(this);
}


string EventScriptCommand::getCommand() const
{
	if (command.find("_") != string::npos)
	{
		return command.substr(0, command.find("_"));
	}
	return command;
}


string EventScriptCommand::getCommandWithArguments()
{
	return command;
}


string EventScriptCommand::getComment()
{
	return comment;
}

EventScriptQualifier::EventScriptQualifier(const string& command, const string& comment)
{
	this->command = command;
	this->comment = comment;

	EventData::qualifierList->add(this);
}

ArrayList<EventScriptCommand*>* EventData::commandList = new ArrayList<EventScriptCommand*>();
ArrayList<EventScriptQualifier*>* EventData::qualifierList = new ArrayList<EventScriptQualifier*>();

const EventScriptQualifier* EventData::isPlayerTouchingThisArea = new EventScriptQualifier("isPlayerTouchingThisArea", "");
const EventScriptQualifier* EventData::isPlayerWalkingIntoThisDoor = new EventScriptQualifier("isPlayerWalkingIntoThisDoor", "");
const EventScriptQualifier* EventData::isPlayerTouchingThisEntity = new EventScriptQualifier("isPlayerTouchingThisEntity", "");
const EventScriptQualifier* EventData::isPlayerTouchingAnyEntityUsingThisSprite = new EventScriptQualifier("isPlayerTouchingAnyEntityUsingThisSprite", "");
const EventScriptQualifier* EventData::isPlayerWalkingIntoDoor_DOOR = new EventScriptQualifier("isPlayerWalkingIntoDoor_DOOR", "");
const EventScriptQualifier* EventData::isPlayerWalkingIntoWarp_WARP = new EventScriptQualifier("isPlayerWalkingIntoWarp_WARP", "");
const EventScriptQualifier* EventData::isActionButtonHeld = new EventScriptQualifier("isActionButtonHeld", "");
const EventScriptQualifier* EventData::isPlayerAutoPilotOn = new EventScriptQualifier("isPlayerAutoPilotOn", "");
const EventScriptQualifier* EventData::isFlagSet_FLAG = new EventScriptQualifier("isFlagSet_FLAG", "");
const EventScriptQualifier* EventData::hasSkillAtLeast_SKILL_FLOAT1 = new EventScriptQualifier("hasSkillAtLeast_SKILL_FLOAT1", "");
const EventScriptQualifier* EventData::isCurrentState_STATE = new EventScriptQualifier("isCurrentState_STATE", "");
const EventScriptQualifier* EventData::isPlayerStandingInArea_AREA = new EventScriptQualifier("isPlayerStandingInArea_AREA", "");
const EventScriptQualifier* EventData::isEntityStandingInArea_ENTITY_AREA = new EventScriptQualifier("isEntityStandingInArea_ENTITY_AREA", "");
const EventScriptQualifier* EventData::hourPastOrEqualTo_INT23 = new EventScriptQualifier("hourPastOrEqualTo_INT23", "");
const EventScriptQualifier* EventData::hourLessThan_INT23 = new EventScriptQualifier("hourLessThan_INT23", "");
const EventScriptQualifier* EventData::minutePastOrEqualTo_INT59 = new EventScriptQualifier("minutePastOrEqualTo_INT59", "");
const EventScriptQualifier* EventData::minuteLessThan_INT59 = new EventScriptQualifier("minuteLessThan_INT59", "");
const EventScriptQualifier* EventData::hasMoneyAtLeastAmount_FLOAT = new EventScriptQualifier("hasMoneyAtLeastAmount_FLOAT", "");
const EventScriptQualifier* EventData::hasMoneyLessThanAmount_FLOAT = new EventScriptQualifier("hasMoneyLessThanAmount_FLOAT", "");
const EventScriptQualifier* EventData::hasItem_ITEM = new EventScriptQualifier("hasItem_ITEM", "");
const EventScriptQualifier* EventData::hasGame_GAME = new EventScriptQualifier("hasGame_GAME", "");
const EventScriptQualifier* EventData::isPlayerMale = new EventScriptQualifier("isPlayerMale", "");
const EventScriptQualifier* EventData::isPlayerFemale = new EventScriptQualifier("isPlayerFemale", "");
const EventScriptQualifier* EventData::isAnyEntityUsingSprite_SPRITE = new EventScriptQualifier("isAnyEntityUsingSprite_SPRITE", "");
const EventScriptQualifier* EventData::isAnyEntityUsingSpriteAtArea_SPRITE_AREA = new EventScriptQualifier("isAnyEntityUsingSpriteAtArea_SPRITE_AREA", "");
const EventScriptQualifier* EventData::isEntitySpawned_ENTITY = new EventScriptQualifier("isEntitySpawned_ENTITY", "");
const EventScriptQualifier* EventData::isEntityAtArea_ENTITY_AREA = new EventScriptQualifier("isEntityAtArea_ENTITY_AREA", "");
const EventScriptQualifier* EventData::isAreaEmpty_AREA = new EventScriptQualifier("isAreaEmpty_AREA", "");
const EventScriptQualifier* EventData::hasFinishedDialogue_DIALOGUE = new EventScriptQualifier("hasFinishedDialogue_DIALOGUE", "");
const EventScriptQualifier* EventData::isTextBoxOpen = new EventScriptQualifier("isTextBoxOpen", "");
const EventScriptQualifier* EventData::isTextAnswerBoxOpen = new EventScriptQualifier("isTextAnswerBoxOpen", "");
const EventScriptQualifier* EventData::isTextAnswerSelected_INT4 = new EventScriptQualifier("isTextAnswerSelected_INT4", "");
const EventScriptQualifier* EventData::isTextAnswerSelected_STRING = new EventScriptQualifier("isTextAnswerSelected_STRING", "");
const EventScriptQualifier* EventData::randomEqualsOneOutOfLessThan_INT = new EventScriptQualifier("randomEqualsOneOutOfLessThan_INT", "");
const EventScriptQualifier* EventData::randomEqualsOneOutOfIncluding_INT = new EventScriptQualifier("randomEqualsOneOutOfIncluding_INT", "");
const EventScriptQualifier* EventData::isAnyMusicPlaying = new EventScriptQualifier("isAnyMusicPlaying", "");
const EventScriptQualifier* EventData::isMusicPlaying_MUSIC = new EventScriptQualifier("isMusicPlaying_MUSIC", "");
const EventScriptQualifier* EventData::isRaining = new EventScriptQualifier("isRaining", "");
const EventScriptQualifier* EventData::isWindy = new EventScriptQualifier("isWindy", "");
const EventScriptQualifier* EventData::isSnowing = new EventScriptQualifier("isSnowing", "");
const EventScriptQualifier* EventData::isFoggy = new EventScriptQualifier("isFoggy", "");
const EventScriptQualifier* EventData::isMapOutside = new EventScriptQualifier("isMapOutside", "");
const EventScriptQualifier* EventData::hasTalkedToThisToday = new EventScriptQualifier("hasTalkedToThisToday", "");
const EventScriptQualifier* EventData::hasBeenMinutesSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenMinutesSinceFlagSet_FLAG_INT", "");
const EventScriptQualifier* EventData::hasBeenHoursSinceFlagSet_FLAG_INT23 = new EventScriptQualifier("hasBeenHoursSinceFlagSet_FLAG_INT23", "");
const EventScriptQualifier* EventData::hasBeenDaysSinceFlagSet_FLAG_INT = new EventScriptQualifier("hasBeenDaysSinceFlagSet_FLAG_INT", "");
const EventScriptQualifier* EventData::isThisActivated = new EventScriptQualifier("isThisActivated", "");
const EventScriptQualifier* EventData::haveSecondsPassedSinceActivated_INT = new EventScriptQualifier("haveSecondsPassedSinceActivated_INT", "");
const EventScriptQualifier* EventData::haveMinutesPassedSinceActivated_INT = new EventScriptQualifier("haveMinutesPassedSinceActivated_INT", "");
const EventScriptQualifier* EventData::haveHoursPassedSinceActivated_INT = new EventScriptQualifier("haveHoursPassedSinceActivated_INT", "");
const EventScriptQualifier* EventData::haveDaysPassedSinceActivated_INT = new EventScriptQualifier("haveDaysPassedSinceActivated_INT", "");
const EventScriptQualifier* EventData::hasActivatedThisEver = new EventScriptQualifier("hasActivatedThisEver", "");
const EventScriptQualifier* EventData::hasActivatedThisSinceEnterRoom = new EventScriptQualifier("hasActivatedThisSinceEnterRoom", "");
const EventScriptQualifier* EventData::hasBeenHereEver = new EventScriptQualifier("hasBeenHereEver", "");
const EventScriptQualifier* EventData::hasBeenHereSinceEnterRoom = new EventScriptQualifier("hasBeenHereSinceEnterRoom", "");
const EventScriptQualifier* EventData::haveSecondsPassedSinceBeenHere_INT = new EventScriptQualifier("haveSecondsPassedSinceBeenHere_INT", "");
const EventScriptQualifier* EventData::haveMinutesPassedSinceBeenHere_INT = new EventScriptQualifier("haveMinutesPassedSinceBeenHere_INT", "");
const EventScriptQualifier* EventData::haveHoursPassedSinceBeenHere_INT = new EventScriptQualifier("haveHoursPassedSinceBeenHere_INT", "");
const EventScriptQualifier* EventData::haveDaysPassedSinceBeenHere_INT = new EventScriptQualifier("haveDaysPassedSinceBeenHere_INT", "");
const EventScriptQualifier* EventData::isLightOn_LIGHT = new EventScriptQualifier("isLightOn_LIGHT", "");
const EventScriptCommand* EventData::alwaysBlockWhileNotStandingHere = new EventScriptCommand("alwaysBlockWhileNotStandingHere", "");
const EventScriptCommand* EventData::e00 = new EventScriptCommand();
const EventScriptCommand* EventData::blockUntilActionButtonPressed = new EventScriptCommand("blockUntilActionButtonPressed", "");
const EventScriptCommand* EventData::blockUntilActionCaptionButtonPressed_STRING = new EventScriptCommand("blockUntilActionCaptionButtonPressed_STRING", "");
const EventScriptCommand* EventData::blockUntilCancelButtonPressed = new EventScriptCommand("blockUntilCancelButtonPressed", "");
const EventScriptCommand* EventData::blockForTicks_INT = new EventScriptCommand("blockForTicks_INT", "");
const EventScriptCommand* EventData::blockUntilClockHour_INT23 = new EventScriptCommand("blockUntilClockHour_INT23", "");
const EventScriptCommand* EventData::blockUntilClockMinute_INT59 = new EventScriptCommand("blockUntilClockMinute_INT59", "");
const EventScriptCommand* EventData::e000 = new EventScriptCommand();
const EventScriptCommand* EventData::loadMapState_STATE = new EventScriptCommand("loadMapState_STATE", "");
const EventScriptCommand* EventData::runEvent_EVENT = new EventScriptCommand("runEvent_EVENT", "");
const EventScriptCommand* EventData::blockUntilEventDone_EVENT = new EventScriptCommand("blockUntilEventDone_EVENT", "");
const EventScriptCommand* EventData::clearThisEvent = new EventScriptCommand("clearThisEvent", "");
const EventScriptCommand* EventData::clearEvent_EVENT = new EventScriptCommand("clearEvent_EVENT", "");
const EventScriptCommand* EventData::e001 = new EventScriptCommand();
const EventScriptCommand* EventData::setThisActivated_BOOL = new EventScriptCommand("setThisActivated_BOOL", "");
const EventScriptCommand* EventData::toggleThisActivated = new EventScriptCommand("toggleThisActivated", "");
const EventScriptCommand* EventData::e002 = new EventScriptCommand();
const EventScriptCommand* EventData::setLastBeenHereTime = new EventScriptCommand("setLastBeenHereTime", "");
const EventScriptCommand* EventData::resetLastBeenHereTime = new EventScriptCommand("resetLastBeenHereTime", "");
const EventScriptCommand* EventData::e003 = new EventScriptCommand();
const EventScriptCommand* EventData::setFlag_FLAG_BOOL = new EventScriptCommand("setFlag_FLAG_BOOL", "");
const EventScriptCommand* EventData::setFlagTrue_FLAG = new EventScriptCommand("setFlagTrue_FLAG", "");
const EventScriptCommand* EventData::setFlagFalse_FLAG = new EventScriptCommand("setFlagFalse_FLAG", "");
const EventScriptCommand* EventData::e004 = new EventScriptCommand();
const EventScriptCommand* EventData::giveSkillPoints_SKILL_INT = new EventScriptCommand("giveSkillPoints_SKILL_INT", "");
const EventScriptCommand* EventData::removeSkillPoints_SKILL_INT = new EventScriptCommand("removeSkillPoints_SKILL_INT", "");
const EventScriptCommand* EventData::setSkillPoints_SKILL_INT = new EventScriptCommand("setSkillPoints_SKILL_INT", "");
const EventScriptCommand* EventData::e005 = new EventScriptCommand();
const EventScriptCommand* EventData::enterThisDoor = new EventScriptCommand("enterThisDoor", "");
const EventScriptCommand* EventData::enterThisWarp = new EventScriptCommand("enterThisWarp", "");
const EventScriptCommand* EventData::enterDoor_DOOR = new EventScriptCommand("enterDoor_DOOR", "");
const EventScriptCommand* EventData::enterWarp_WARP = new EventScriptCommand("enterWarp_WARP", "");
const EventScriptCommand* EventData::changeMap_MAP_AREA = new EventScriptCommand("changeMap_MAP_AREA", "");
const EventScriptCommand* EventData::changeMap_MAP_DOOR = new EventScriptCommand("changeMap_MAP_DOOR", "");
const EventScriptCommand* EventData::changeMap_MAP_WARP = new EventScriptCommand("changeMap_MAP_WARP", "");
const EventScriptCommand* EventData::changeMap_MAP_INT_INT = new EventScriptCommand("changeMap_MAP_INT_INT", "");
const EventScriptCommand* EventData::e006 = new EventScriptCommand();
const EventScriptCommand* EventData::doDialogue_DIALOGUE = new EventScriptCommand("doDialogue_DIALOGUE", "");
const EventScriptCommand* EventData::doDialogueWithCaption_DIALOGUE = new EventScriptCommand("doDialogueWithCaption_DIALOGUE", "");
const EventScriptCommand* EventData::doDialogueIfNew_DIALOGUE = new EventScriptCommand("doDialogueIfNew_DIALOGUE", "");
const EventScriptCommand* EventData::e007 = new EventScriptCommand();
const EventScriptCommand* EventData::setSpriteBox0_ENTITY = new EventScriptCommand("setSpriteBox0_ENTITY", "");
const EventScriptCommand* EventData::setSpriteBox1_ENTITY = new EventScriptCommand("setSpriteBox1_ENTITY", "");
const EventScriptCommand* EventData::setSpriteBox0_SPRITE = new EventScriptCommand("setSpriteBox0_SPRITE", "");
const EventScriptCommand* EventData::setSpriteBox1_SPRITE = new EventScriptCommand("setSpriteBox1_SPRITE", "");
const EventScriptCommand* EventData::e008 = new EventScriptCommand();
const EventScriptCommand* EventData::blockUntilTextBoxClosed = new EventScriptCommand("blockUntilTextBoxClosed", "");
const EventScriptCommand* EventData::blockUntilTextAnswerBoxClosed = new EventScriptCommand("blockUntilTextAnswerBoxClosed", "");
const EventScriptCommand* EventData::e009 = new EventScriptCommand();
const EventScriptCommand* EventData::doCinematicTextNoBorder_DIALOGUE_INTy = new EventScriptCommand("doCinematicTextNoBorder_DIALOGUE_INTy", "");
const EventScriptCommand* EventData::e025 = new EventScriptCommand();
const EventScriptCommand* EventData::setDoorOpenAnimation_DOOR_BOOLopenClose = new EventScriptCommand("setDoorOpenAnimation_DOOR_BOOLopenClose", "");
const EventScriptCommand* EventData::setDoorActionIcon_DOOR_BOOLonOff = new EventScriptCommand("setDoorActionIcon_DOOR_BOOLonOff", "");
const EventScriptCommand* EventData::setDoorDestination_DOOR_DOORdestination = new EventScriptCommand("setDoorDestination_DOOR_DOORdestination", "");
const EventScriptCommand* EventData::setAreaActionIcon_AREA_BOOLonOff = new EventScriptCommand("setAreaActionIcon_AREA_BOOLonOff", "");
const EventScriptCommand* EventData::setWarpDestination_WARP_WARPdestination = new EventScriptCommand("setWarpDestination_WARP_WARPdestination", "");
const EventScriptCommand* EventData::e010 = new EventScriptCommand();
const EventScriptCommand* EventData::e012 = new EventScriptCommand();
const EventScriptCommand* EventData::setCameraNoTarget = new EventScriptCommand("setCameraNoTarget", "");
const EventScriptCommand* EventData::setCameraTargetToArea_AREA = new EventScriptCommand("setCameraTargetToArea_AREA", "");
const EventScriptCommand* EventData::setCameraTargetToEntity_ENTITY = new EventScriptCommand("setCameraTargetToEntity_ENTITY", "");
const EventScriptCommand* EventData::setCameraIgnoreBounds_BOOL = new EventScriptCommand("setCameraIgnoreBounds_BOOL", "");
const EventScriptCommand* EventData::setCameraTargetToPlayer = new EventScriptCommand("setCameraTargetToPlayer", "");
const EventScriptCommand* EventData::blockUntilCameraReaches_AREA = new EventScriptCommand("blockUntilCameraReaches_AREA", "");
const EventScriptCommand* EventData::blockUntilCameraReaches_ENTITY = new EventScriptCommand("blockUntilCameraReaches_ENTITY", "");
const EventScriptCommand* EventData::blockUntilCameraReachesPlayer = new EventScriptCommand("blockUntilCameraReachesPlayer", "");
const EventScriptCommand* EventData::pushCameraState = new EventScriptCommand("pushCameraState", "");
const EventScriptCommand* EventData::popCameraState = new EventScriptCommand("popCameraState", "");
const EventScriptCommand* EventData::setKeyboardCameraZoom_BOOL = new EventScriptCommand("setKeyboardCameraZoom_BOOL", "");
const EventScriptCommand* EventData::enableKeyboardCameraZoom = new EventScriptCommand("enableKeyboardCameraZoom", "");
const EventScriptCommand* EventData::disableKeyboardCameraZoom = new EventScriptCommand("disableKeyboardCameraZoom", "");
const EventScriptCommand* EventData::setCameraAutoZoomByPlayerMovement_BOOL = new EventScriptCommand("setCameraAutoZoomByPlayerMovement_BOOL", "");
const EventScriptCommand* EventData::enableCameraAutoZoomByPlayerMovement = new EventScriptCommand("enableCameraAutoZoomByPlayerMovement", "");
const EventScriptCommand* EventData::disableCameraAutoZoomByPlayerMovement = new EventScriptCommand("disableCameraAutoZoomByPlayerMovement", "");
const EventScriptCommand* EventData::setCameraZoom_FLOAT = new EventScriptCommand("setCameraZoom_FLOAT", "");
const EventScriptCommand* EventData::setCameraSpeed_FLOAT = new EventScriptCommand("setCameraSpeed_FLOAT", "");
const EventScriptCommand* EventData::setPlayerToTempPlayerWithSprite_SPRITE = new EventScriptCommand("setPlayerToTempPlayerWithSprite_SPRITE", "");
const EventScriptCommand* EventData::setPlayerToNormalPlayer = new EventScriptCommand("setPlayerToNormalPlayer", "");
const EventScriptCommand* EventData::setPlayerExists_BOOL = new EventScriptCommand("setPlayerExists_BOOL", "");
const EventScriptCommand* EventData::setPlayerControlsEnabled_BOOL = new EventScriptCommand("setPlayerControlsEnabled_BOOL", "");
const EventScriptCommand* EventData::enablePlayerControls = new EventScriptCommand("enablePlayerControls", "");
const EventScriptCommand* EventData::disablePlayerControls = new EventScriptCommand("disablePlayerControls", "");
const EventScriptCommand* EventData::setPlayerAutoPilot_BOOL = new EventScriptCommand("setPlayerAutoPilot_BOOL", "");
const EventScriptCommand* EventData::setPlayerShowNameCaption_BOOL = new EventScriptCommand("setPlayerShowNameCaption_BOOL", "");
const EventScriptCommand* EventData::setPlayerShowAccountTypeCaption_BOOL = new EventScriptCommand("setPlayerShowAccountTypeCaption_BOOL", "");
const EventScriptCommand* EventData::playerSetBehaviorQueueOnOff_BOOL = new EventScriptCommand("playerSetBehaviorQueueOnOff_BOOL", "");
const EventScriptCommand* EventData::playerSetToArea_AREA = new EventScriptCommand("playerSetToArea_AREA", "");
const EventScriptCommand* EventData::playerSetToDoor_DOOR = new EventScriptCommand("playerSetToDoor_DOOR", "");
const EventScriptCommand* EventData::playerSetToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerSetToTileXY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::playerWalkToArea_AREA = new EventScriptCommand("playerWalkToArea_AREA", "");
const EventScriptCommand* EventData::playerWalkToDoor_DOOR = new EventScriptCommand("playerWalkToDoor_DOOR", "");
const EventScriptCommand* EventData::playerWalkToEntity_ENTITY = new EventScriptCommand("playerWalkToEntity_ENTITY", "");
const EventScriptCommand* EventData::playerWalkToTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::playerBlockUntilReachesArea_AREA = new EventScriptCommand("playerBlockUntilReachesArea_AREA", "");
const EventScriptCommand* EventData::playerBlockUntilReachesDoor_DOOR = new EventScriptCommand("playerBlockUntilReachesDoor_DOOR", "");
const EventScriptCommand* EventData::playerBlockUntilReachesEntity_ENTITY = new EventScriptCommand("playerBlockUntilReachesEntity_ENTITY", "");
const EventScriptCommand* EventData::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = new EventScriptCommand("playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::playerWalkToAreaAndBlockUntilThere_AREA = new EventScriptCommand("playerWalkToAreaAndBlockUntilThere_AREA", "");
const EventScriptCommand* EventData::playerWalkToEntityAndBlockUntilThere_ENTITY = new EventScriptCommand("playerWalkToEntityAndBlockUntilThere_ENTITY", "");
const EventScriptCommand* EventData::playerWalkToDoorAndBlockUntilThere_DOOR = new EventScriptCommand("playerWalkToDoorAndBlockUntilThere_DOOR", "");
const EventScriptCommand* EventData::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X = new EventScriptCommand("playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::playerStandAndShuffle = new EventScriptCommand("playerStandAndShuffle", "");
const EventScriptCommand* EventData::playerStandAndShuffleAndFaceEntity_ENTITY = new EventScriptCommand("playerStandAndShuffleAndFaceEntity_ENTITY", "");
const EventScriptCommand* EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame", "");
const EventScriptCommand* EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame", "");
const EventScriptCommand* EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::playerStopAnimating = new EventScriptCommand("playerStopAnimating", "");
const EventScriptCommand* EventData::playerSetGlobalAnimationDisabled_BOOL = new EventScriptCommand("playerSetGlobalAnimationDisabled_BOOL", "");
const EventScriptCommand* EventData::playerSetMovementSpeed_INTticksPerPixel = new EventScriptCommand("playerSetMovementSpeed_INTticksPerPixel", "");
const EventScriptCommand* EventData::playerSetFaceMovementDirection_STRINGdirection = new EventScriptCommand("playerSetFaceMovementDirection_STRINGdirection", "");
const EventScriptCommand* EventData::playerSetToAlpha_FLOAT = new EventScriptCommand("playerSetToAlpha_FLOAT", "");
const EventScriptCommand* EventData::e024 = new EventScriptCommand();
const EventScriptCommand* EventData::entitySetBehaviorQueueOnOff_ENTITY_BOOL = new EventScriptCommand("entitySetBehaviorQueueOnOff_ENTITY_BOOL", "");
const EventScriptCommand* EventData::entitySetToArea_ENTITY_AREA = new EventScriptCommand("entitySetToArea_ENTITY_AREA", "");
const EventScriptCommand* EventData::entitySetToDoor_ENTITY_DOOR = new EventScriptCommand("entitySetToDoor_ENTITY_DOOR", "");
const EventScriptCommand* EventData::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::entityWalkToArea_ENTITY_AREA = new EventScriptCommand("entityWalkToArea_ENTITY_AREA", "");
const EventScriptCommand* EventData::entityWalkToDoor_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoor_ENTITY_DOOR", "");
const EventScriptCommand* EventData::entityWalkToEntity_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntity_ENTITY_ENTITY", "");
const EventScriptCommand* EventData::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const EventScriptCommand* EventData::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const EventScriptCommand* EventData::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const EventScriptCommand* EventData::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = new EventScriptCommand("entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const EventScriptCommand* EventData::entityBlockUntilReachesArea_ENTITY_AREA = new EventScriptCommand("entityBlockUntilReachesArea_ENTITY_AREA", "");
const EventScriptCommand* EventData::entityBlockUntilReachesDoor_ENTITY_DOOR = new EventScriptCommand("entityBlockUntilReachesDoor_ENTITY_DOOR", "");
const EventScriptCommand* EventData::entityBlockUntilReachesEntity_ENTITY_ENTITY = new EventScriptCommand("entityBlockUntilReachesEntity_ENTITY_ENTITY", "");
const EventScriptCommand* EventData::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA = new EventScriptCommand("entityWalkToAreaAndBlockUntilThere_ENTITY_AREA", "");
const EventScriptCommand* EventData::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY = new EventScriptCommand("entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY", "");
const EventScriptCommand* EventData::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR = new EventScriptCommand("entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR", "");
const EventScriptCommand* EventData::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X = new EventScriptCommand("entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X", "");
const EventScriptCommand* EventData::entityStandAndShuffle_ENTITY = new EventScriptCommand("entityStandAndShuffle_ENTITY", "");
const EventScriptCommand* EventData::entityStandAndShuffleAndFacePlayer_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFacePlayer_ENTITY", "");
const EventScriptCommand* EventData::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY = new EventScriptCommand("entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY", "");
const EventScriptCommand* EventData::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName = new EventScriptCommand("entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName", "");
const EventScriptCommand* EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const EventScriptCommand* EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const EventScriptCommand* EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = new EventScriptCommand("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const EventScriptCommand* EventData::entityStopAnimating_ENTITY = new EventScriptCommand("entityStopAnimating_ENTITY", "");
const EventScriptCommand* EventData::entitySetGlobalAnimationDisabled_ENTITY_BOOL = new EventScriptCommand("entitySetGlobalAnimationDisabled_ENTITY_BOOL", "");
const EventScriptCommand* EventData::entitySetMovementSpeed_ENTITY_INTticksPerPixel = new EventScriptCommand("entitySetMovementSpeed_ENTITY_INTticksPerPixel", "");
const EventScriptCommand* EventData::entitySetFaceMovementDirection_ENTITY_STRINGdirection = new EventScriptCommand("entitySetFaceMovementDirection_ENTITY_STRINGdirection", "");
const EventScriptCommand* EventData::entitySetNonWalkable_ENTITY_BOOL = new EventScriptCommand("entitySetNonWalkable_ENTITY_BOOL", "");
const EventScriptCommand* EventData::entitySetPushable_ENTITY_BOOL = new EventScriptCommand("entitySetPushable_ENTITY_BOOL", "");
const EventScriptCommand* EventData::entitySetToAlpha_ENTITY_FLOAT = new EventScriptCommand("entitySetToAlpha_ENTITY_FLOAT", "");
const EventScriptCommand* EventData::entityFadeOutDelete_ENTITY = new EventScriptCommand("entityFadeOutDelete_ENTITY", "");
const EventScriptCommand* EventData::entityDeleteInstantly_ENTITY = new EventScriptCommand("entityDeleteInstantly_ENTITY", "");
const EventScriptCommand* EventData::e016 = new EventScriptCommand();
const EventScriptCommand* EventData::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA", "");
const EventScriptCommand* EventData::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const EventScriptCommand* EventData::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA", "");
const EventScriptCommand* EventData::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA = new EventScriptCommand("spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const EventScriptCommand* EventData::e017 = new EventScriptCommand();
const EventScriptCommand* EventData::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const EventScriptCommand* EventData::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = new EventScriptCommand("createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const EventScriptCommand* EventData::createScreenSpriteUnderText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteUnderText_SPRITE_INTx_INTy", "");
const EventScriptCommand* EventData::createScreenSpriteOverText_SPRITE_INTx_INTy = new EventScriptCommand("createScreenSpriteOverText_SPRITE_INTx_INTy", "");
const EventScriptCommand* EventData::e026 = new EventScriptCommand();
const EventScriptCommand* EventData::giveItem_ITEM = new EventScriptCommand("giveItem_ITEM", "");
const EventScriptCommand* EventData::takeItem_ITEM = new EventScriptCommand("takeItem_ITEM", "");
const EventScriptCommand* EventData::giveGame_GAME = new EventScriptCommand("giveGame_GAME", "");
const EventScriptCommand* EventData::takeMoney_FLOAT = new EventScriptCommand("takeMoney_FLOAT", "");
const EventScriptCommand* EventData::giveMoney_FLOAT = new EventScriptCommand("giveMoney_FLOAT", "");
const EventScriptCommand* EventData::e027 = new EventScriptCommand();
const EventScriptCommand* EventData::playSound_SOUND = new EventScriptCommand("playSound_SOUND", "");
const EventScriptCommand* EventData::playSound_SOUND_FLOATvol = new EventScriptCommand("playSound_SOUND_FLOATvol", "");
const EventScriptCommand* EventData::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes = new EventScriptCommand("playSound_SOUND_FLOATvol_FLOATpitch_INTtimes", "");
const EventScriptCommand* EventData::playMusicOnce_MUSIC = new EventScriptCommand("playMusicOnce_MUSIC", "");
const EventScriptCommand* EventData::playMusicLoop_MUSIC = new EventScriptCommand("playMusicLoop_MUSIC", "");
const EventScriptCommand* EventData::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop = new EventScriptCommand("playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop", "");
const EventScriptCommand* EventData::stopAllMusic = new EventScriptCommand("stopAllMusic", "");
const EventScriptCommand* EventData::stopMusic_MUSIC = new EventScriptCommand("stopMusic_MUSIC", "");
const EventScriptCommand* EventData::fadeOutMusic_MUSIC_INT = new EventScriptCommand("fadeOutMusic_MUSIC_INT", "");
const EventScriptCommand* EventData::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC = new EventScriptCommand("blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC", "");
const EventScriptCommand* EventData::blockUntilMusicDone_MUSIC = new EventScriptCommand("blockUntilMusicDone_MUSIC", "");
const EventScriptCommand* EventData::fadeOutAllMusic_INT = new EventScriptCommand("fadeOutAllMusic_INT", "");
const EventScriptCommand* EventData::blockUntilAllMusicDone = new EventScriptCommand("blockUntilAllMusicDone", "");
const EventScriptCommand* EventData::e028 = new EventScriptCommand();
const EventScriptCommand* EventData::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake = new EventScriptCommand("shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake", "");
const EventScriptCommand* EventData::fadeToBlack_INTticks = new EventScriptCommand("fadeToBlack_INTticks", "");
const EventScriptCommand* EventData::fadeFromBlack_INTticks = new EventScriptCommand("fadeFromBlack_INTticks", "");
const EventScriptCommand* EventData::fadeToWhite_INTticks = new EventScriptCommand("fadeToWhite_INTticks", "");
const EventScriptCommand* EventData::fadeFromWhite_INTticks = new EventScriptCommand("fadeFromWhite_INTticks", "");
const EventScriptCommand* EventData::e029 = new EventScriptCommand();
const EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const EventScriptCommand* EventData::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha = new EventScriptCommand("fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha", "");
const EventScriptCommand* EventData::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const EventScriptCommand* EventData::setInstantOverlay_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlay_INTr_INTg_INTb_FLOATa", "");
const EventScriptCommand* EventData::clearOverlay = new EventScriptCommand("clearOverlay", "");
const EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const EventScriptCommand* EventData::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa", "");
const EventScriptCommand* EventData::clearOverlayUnderLights = new EventScriptCommand("clearOverlayUnderLights", "");
const EventScriptCommand* EventData::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha = new EventScriptCommand("fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const EventScriptCommand* EventData::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa = new EventScriptCommand("setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa", "");
const EventScriptCommand* EventData::clearOverlayGroundLayer = new EventScriptCommand("clearOverlayGroundLayer", "");
const EventScriptCommand* EventData::e030 = new EventScriptCommand();
const EventScriptCommand* EventData::setLetterbox_BOOL = new EventScriptCommand("setLetterbox_BOOL", "");
const EventScriptCommand* EventData::setLetterbox_BOOL_INTticks = new EventScriptCommand("setLetterbox_BOOL_INTticks", "");
const EventScriptCommand* EventData::setLetterbox_BOOL_INTticks_INTsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_INTsize", "");
const EventScriptCommand* EventData::setLetterbox_BOOL_INTticks_FLOATsize = new EventScriptCommand("setLetterbox_BOOL_INTticks_FLOATsize", "");
const EventScriptCommand* EventData::setBlur_BOOL = new EventScriptCommand("setBlur_BOOL", "");
const EventScriptCommand* EventData::setMosaic_BOOL = new EventScriptCommand("setMosaic_BOOL", "");
const EventScriptCommand* EventData::setHBlankWave_BOOL = new EventScriptCommand("setHBlankWave_BOOL", "");
const EventScriptCommand* EventData::setRotate_BOOL = new EventScriptCommand("setRotate_BOOL", "");
const EventScriptCommand* EventData::setBlackAndWhite_BOOL = new EventScriptCommand("setBlackAndWhite_BOOL", "");
const EventScriptCommand* EventData::setInvertedColors_BOOL = new EventScriptCommand("setInvertedColors_BOOL", "");
const EventScriptCommand* EventData::set8BitMode_BOOL = new EventScriptCommand("set8BitMode_BOOL", "");
const EventScriptCommand* EventData::e031 = new EventScriptCommand();
const EventScriptCommand* EventData::setEngineSpeed_FLOAT = new EventScriptCommand("setEngineSpeed_FLOAT", "");
const EventScriptCommand* EventData::e032 = new EventScriptCommand();
const EventScriptCommand* EventData::toggleLightOnOff_LIGHT = new EventScriptCommand("toggleLightOnOff_LIGHT", "");
const EventScriptCommand* EventData::setLightOnOff_LIGHT_BOOL = new EventScriptCommand("setLightOnOff_LIGHT_BOOL", "");
const EventScriptCommand* EventData::setLightFlicker_LIGHT_BOOL = new EventScriptCommand("setLightFlicker_LIGHT_BOOL", "");
const EventScriptCommand* EventData::toggleAllLightsOnOff = new EventScriptCommand("toggleAllLightsOnOff", "");
const EventScriptCommand* EventData::setAllLightsOnOff_BOOL = new EventScriptCommand("setAllLightsOnOff_BOOL", "");
const EventScriptCommand* EventData::e033 = new EventScriptCommand();
const EventScriptCommand* EventData::setRandomSpawn_BOOL = new EventScriptCommand("setRandomSpawn_BOOL", "");
const EventScriptCommand* EventData::deleteRandoms = new EventScriptCommand("deleteRandoms", "");
const EventScriptCommand* EventData::e034 = new EventScriptCommand();
const EventScriptCommand* EventData::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const EventScriptCommand* EventData::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb", "");
const EventScriptCommand* EventData::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb = new EventScriptCommand("makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb", "");
const EventScriptCommand* EventData::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = new EventScriptCommand("makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const EventScriptCommand* EventData::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks = new EventScriptCommand("setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks", "");
const EventScriptCommand* EventData::e035 = new EventScriptCommand();
const EventScriptCommand* EventData::setShowClockCaption_BOOL = new EventScriptCommand("setShowClockCaption_BOOL", "");
const EventScriptCommand* EventData::setShowDayCaption_BOOL = new EventScriptCommand("setShowDayCaption_BOOL", "");
const EventScriptCommand* EventData::setShowMoneyCaption_BOOL = new EventScriptCommand("setShowMoneyCaption_BOOL", "");
const EventScriptCommand* EventData::setShowAllStatusBarCaptions_BOOL = new EventScriptCommand("setShowAllStatusBarCaptions_BOOL", "");
const EventScriptCommand* EventData::setShowStatusBar_BOOL = new EventScriptCommand("setShowStatusBar_BOOL", "");
const EventScriptCommand* EventData::setShowNDButton_BOOL = new EventScriptCommand("setShowNDButton_BOOL", "");
const EventScriptCommand* EventData::setShowGameStoreButton_BOOL = new EventScriptCommand("setShowGameStoreButton_BOOL", "");
const EventScriptCommand* EventData::setShowStuffButton_BOOL = new EventScriptCommand("setShowStuffButton_BOOL", "");
const EventScriptCommand* EventData::setShowAllButtons_BOOL = new EventScriptCommand("setShowAllButtons_BOOL", "");
const EventScriptCommand* EventData::setNDEnabled_BOOL = new EventScriptCommand("setNDEnabled_BOOL", "");
const EventScriptCommand* EventData::setGameStoreMenuEnabled_BOOL = new EventScriptCommand("setGameStoreMenuEnabled_BOOL", "");
const EventScriptCommand* EventData::setStuffMenuEnabled_BOOL = new EventScriptCommand("setStuffMenuEnabled_BOOL", "");
const EventScriptCommand* EventData::setAllMenusAndNDEnabled_BOOL = new EventScriptCommand("setAllMenusAndNDEnabled_BOOL", "");
const EventScriptCommand* EventData::e046 = new EventScriptCommand();
const EventScriptCommand* EventData::setClockUnknown = new EventScriptCommand("setClockUnknown", "");
const EventScriptCommand* EventData::setClockNormal = new EventScriptCommand("setClockNormal", "");
const EventScriptCommand* EventData::setTimePaused_BOOL = new EventScriptCommand("setTimePaused_BOOL", "");
const EventScriptCommand* EventData::setTimeFastForward = new EventScriptCommand("setTimeFastForward", "");
const EventScriptCommand* EventData::setTimeNormalSpeed = new EventScriptCommand("setTimeNormalSpeed", "");
const EventScriptCommand* EventData::e037 = new EventScriptCommand();
const EventScriptCommand* EventData::setNDOpen_BOOL = new EventScriptCommand("setNDOpen_BOOL", "");
const EventScriptCommand* EventData::startGame = new EventScriptCommand("startGame", "");
const EventScriptCommand* EventData::startBobsGameOnStadiumScreen_AREA = new EventScriptCommand("startBobsGameOnStadiumScreen_AREA", "");
const EventScriptCommand* EventData::blockUntilBobsGameDead = new EventScriptCommand("blockUntilBobsGameDead", "");
const EventScriptCommand* EventData::showLoginScreen = new EventScriptCommand("showLoginScreen", "");
const EventScriptCommand* EventData::e038 = new EventScriptCommand();
const EventScriptCommand* EventData::closeAllMenusAndND = new EventScriptCommand("closeAllMenusAndND", "");
const EventScriptCommand* EventData::e039 = new EventScriptCommand();
const EventScriptCommand* EventData::openStuffMenu = new EventScriptCommand("openStuffMenu", "");
const EventScriptCommand* EventData::openItemsMenu = new EventScriptCommand("openItemsMenu", "");
const EventScriptCommand* EventData::openLogMenu = new EventScriptCommand("openLogMenu", "");
const EventScriptCommand* EventData::openStatusMenu = new EventScriptCommand("openStatusMenu", "");
const EventScriptCommand* EventData::openFriendsMenu = new EventScriptCommand("openFriendsMenu", "");
const EventScriptCommand* EventData::openSettingsMenu = new EventScriptCommand("openSettingsMenu", "");
const EventScriptCommand* EventData::openGameStoreMenu = new EventScriptCommand("openGameStoreMenu", "");

