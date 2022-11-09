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

//sp<EventData> EventData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = ms<Gson>();
//	//EventData data = gson.fromJson(json,EventData.class);
//
//	return fromJSON(json);
//}
//
//sp<EventData> EventData::fromJSON(const string& json)
//{ //===============================================================================================
//
//	//sp<Gson> gson = ms<Gson>();
//	sp<EventData> data = nullptr;//gson->fromJson(json, EventData::typeid);
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
	if (OKString::startsWith(t,"dialogueDataList"))
	{
		t = t.substr(t.find("dialogueDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<DialogueData> data = ms<DialogueData>();
			t = data->initFromString(t);
			dialogueDataList.push_back(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("flagDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<FlagData> data = ms<FlagData>();
			t = data->initFromString(t);
			flagDataList.push_back(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("skillDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<SkillData> data = ms<SkillData>();
			t = data->initFromString(t);
			skillDataList.push_back(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("gameStringDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<GameStringData> data = ms<GameStringData>();
			t = data->initFromString(t);
			gameStringDataList.push_back(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("musicDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<AudioData> data = ms<AudioData>();
			t = data->initFromString(t);
			musicDataList.push_back(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("soundDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (OKString::startsWith(t,"}") == false)
		{
			sp<AudioData> data = ms<AudioData>();
			t = data->initFromString(t);
			soundDataList.push_back(data);
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

EventScriptTree::EventScriptTree(sp<EventData> outerInstance) : outerInstance(outerInstance)
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

	EventData::commandList.push_back(shared_from_this());
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

	EventData::qualifierList.push_back(shared_from_this());
}

vector<sp<EventScriptCommand>> EventData::commandList;// = ms<ArrayList><sp<EventScriptCommand>>();
vector<sp<EventScriptQualifier>> EventData::qualifierList;// = ms<ArrayList><sp<EventScriptQualifier>>();

const sp<EventScriptQualifier> EventData::isPlayerTouchingThisArea = ms<EventScriptQualifier>("isPlayerTouchingThisArea", "");
const sp<EventScriptQualifier> EventData::isPlayerWalkingIntoThisDoor = ms<EventScriptQualifier>("isPlayerWalkingIntoThisDoor", "");
const sp<EventScriptQualifier> EventData::isPlayerTouchingThisEntity = ms<EventScriptQualifier>("isPlayerTouchingThisEntity", "");
const sp<EventScriptQualifier> EventData::isPlayerTouchingAnyEntityUsingThisSprite = ms<EventScriptQualifier>("isPlayerTouchingAnyEntityUsingThisSprite", "");
const sp<EventScriptQualifier> EventData::isPlayerWalkingIntoDoor_DOOR = ms<EventScriptQualifier>("isPlayerWalkingIntoDoor_DOOR", "");
const sp<EventScriptQualifier> EventData::isPlayerWalkingIntoWarp_WARP = ms<EventScriptQualifier>("isPlayerWalkingIntoWarp_WARP", "");
const sp<EventScriptQualifier> EventData::isActionButtonHeld = ms<EventScriptQualifier>("isActionButtonHeld", "");
const sp<EventScriptQualifier> EventData::isPlayerAutoPilotOn = ms<EventScriptQualifier>("isPlayerAutoPilotOn", "");
const sp<EventScriptQualifier> EventData::isFlagSet_FLAG = ms<EventScriptQualifier>("isFlagSet_FLAG", "");
const sp<EventScriptQualifier> EventData::hasSkillAtLeast_SKILL_FLOAT1 = ms<EventScriptQualifier>("hasSkillAtLeast_SKILL_FLOAT1", "");
const sp<EventScriptQualifier> EventData::isCurrentState_STATE = ms<EventScriptQualifier>("isCurrentState_STATE", "");
const sp<EventScriptQualifier> EventData::isPlayerStandingInArea_AREA = ms<EventScriptQualifier>("isPlayerStandingInArea_AREA", "");
const sp<EventScriptQualifier> EventData::isEntityStandingInArea_ENTITY_AREA = ms<EventScriptQualifier>("isEntityStandingInArea_ENTITY_AREA", "");
const sp<EventScriptQualifier> EventData::hourPastOrEqualTo_INT23 = ms<EventScriptQualifier>("hourPastOrEqualTo_INT23", "");
const sp<EventScriptQualifier> EventData::hourLessThan_INT23 = ms<EventScriptQualifier>("hourLessThan_INT23", "");
const sp<EventScriptQualifier> EventData::minutePastOrEqualTo_INT59 = ms<EventScriptQualifier>("minutePastOrEqualTo_INT59", "");
const sp<EventScriptQualifier> EventData::minuteLessThan_INT59 = ms<EventScriptQualifier>("minuteLessThan_INT59", "");
const sp<EventScriptQualifier> EventData::hasMoneyAtLeastAmount_FLOAT = ms<EventScriptQualifier>("hasMoneyAtLeastAmount_FLOAT", "");
const sp<EventScriptQualifier> EventData::hasMoneyLessThanAmount_FLOAT = ms<EventScriptQualifier>("hasMoneyLessThanAmount_FLOAT", "");
const sp<EventScriptQualifier> EventData::hasItem_ITEM = ms<EventScriptQualifier>("hasItem_ITEM", "");
const sp<EventScriptQualifier> EventData::hasGame_GAME = ms<EventScriptQualifier>("hasGame_GAME", "");
const sp<EventScriptQualifier> EventData::isPlayerMale = ms<EventScriptQualifier>("isPlayerMale", "");
const sp<EventScriptQualifier> EventData::isPlayerFemale = ms<EventScriptQualifier>("isPlayerFemale", "");
const sp<EventScriptQualifier> EventData::isAnyEntityUsingSprite_SPRITE = ms<EventScriptQualifier>("isAnyEntityUsingSprite_SPRITE", "");
const sp<EventScriptQualifier> EventData::isAnyEntityUsingSpriteAtArea_SPRITE_AREA = ms<EventScriptQualifier>("isAnyEntityUsingSpriteAtArea_SPRITE_AREA", "");
const sp<EventScriptQualifier> EventData::isEntitySpawned_ENTITY = ms<EventScriptQualifier>("isEntitySpawned_ENTITY", "");
const sp<EventScriptQualifier> EventData::isEntityAtArea_ENTITY_AREA = ms<EventScriptQualifier>("isEntityAtArea_ENTITY_AREA", "");
const sp<EventScriptQualifier> EventData::isAreaEmpty_AREA = ms<EventScriptQualifier>("isAreaEmpty_AREA", "");
const sp<EventScriptQualifier> EventData::hasFinishedDialogue_DIALOGUE = ms<EventScriptQualifier>("hasFinishedDialogue_DIALOGUE", "");
const sp<EventScriptQualifier> EventData::isTextBoxOpen = ms<EventScriptQualifier>("isTextBoxOpen", "");
const sp<EventScriptQualifier> EventData::isTextAnswerBoxOpen = ms<EventScriptQualifier>("isTextAnswerBoxOpen", "");
const sp<EventScriptQualifier> EventData::isTextAnswerSelected_INT4 = ms<EventScriptQualifier>("isTextAnswerSelected_INT4", "");
const sp<EventScriptQualifier> EventData::isTextAnswerSelected_STRING = ms<EventScriptQualifier>("isTextAnswerSelected_STRING", "");
const sp<EventScriptQualifier> EventData::randomEqualsOneOutOfLessThan_INT = ms<EventScriptQualifier>("randomEqualsOneOutOfLessThan_INT", "");
const sp<EventScriptQualifier> EventData::randomEqualsOneOutOfIncluding_INT = ms<EventScriptQualifier>("randomEqualsOneOutOfIncluding_INT", "");
const sp<EventScriptQualifier> EventData::isAnyMusicPlaying = ms<EventScriptQualifier>("isAnyMusicPlaying", "");
const sp<EventScriptQualifier> EventData::isMusicPlaying_MUSIC = ms<EventScriptQualifier>("isMusicPlaying_MUSIC", "");
const sp<EventScriptQualifier> EventData::isRaining = ms<EventScriptQualifier>("isRaining", "");
const sp<EventScriptQualifier> EventData::isWindy = ms<EventScriptQualifier>("isWindy", "");
const sp<EventScriptQualifier> EventData::isSnowing = ms<EventScriptQualifier>("isSnowing", "");
const sp<EventScriptQualifier> EventData::isFoggy = ms<EventScriptQualifier>("isFoggy", "");
const sp<EventScriptQualifier> EventData::isMapOutside = ms<EventScriptQualifier>("isMapOutside", "");
const sp<EventScriptQualifier> EventData::hasTalkedToThisToday = ms<EventScriptQualifier>("hasTalkedToThisToday", "");
const sp<EventScriptQualifier> EventData::hasBeenMinutesSinceFlagSet_FLAG_INT = ms<EventScriptQualifier>("hasBeenMinutesSinceFlagSet_FLAG_INT", "");
const sp<EventScriptQualifier> EventData::hasBeenHoursSinceFlagSet_FLAG_INT23 = ms<EventScriptQualifier>("hasBeenHoursSinceFlagSet_FLAG_INT23", "");
const sp<EventScriptQualifier> EventData::hasBeenDaysSinceFlagSet_FLAG_INT = ms<EventScriptQualifier>("hasBeenDaysSinceFlagSet_FLAG_INT", "");
const sp<EventScriptQualifier> EventData::isThisActivated = ms<EventScriptQualifier>("isThisActivated", "");
const sp<EventScriptQualifier> EventData::haveSecondsPassedSinceActivated_INT = ms<EventScriptQualifier>("haveSecondsPassedSinceActivated_INT", "");
const sp<EventScriptQualifier> EventData::haveMinutesPassedSinceActivated_INT = ms<EventScriptQualifier>("haveMinutesPassedSinceActivated_INT", "");
const sp<EventScriptQualifier> EventData::haveHoursPassedSinceActivated_INT = ms<EventScriptQualifier>("haveHoursPassedSinceActivated_INT", "");
const sp<EventScriptQualifier> EventData::haveDaysPassedSinceActivated_INT = ms<EventScriptQualifier>("haveDaysPassedSinceActivated_INT", "");
const sp<EventScriptQualifier> EventData::hasActivatedThisEver = ms<EventScriptQualifier>("hasActivatedThisEver", "");
const sp<EventScriptQualifier> EventData::hasActivatedThisSinceEnterRoom = ms<EventScriptQualifier>("hasActivatedThisSinceEnterRoom", "");
const sp<EventScriptQualifier> EventData::hasBeenHereEver = ms<EventScriptQualifier>("hasBeenHereEver", "");
const sp<EventScriptQualifier> EventData::hasBeenHereSinceEnterRoom = ms<EventScriptQualifier>("hasBeenHereSinceEnterRoom", "");
const sp<EventScriptQualifier> EventData::haveSecondsPassedSinceBeenHere_INT = ms<EventScriptQualifier>("haveSecondsPassedSinceBeenHere_INT", "");
const sp<EventScriptQualifier> EventData::haveMinutesPassedSinceBeenHere_INT = ms<EventScriptQualifier>("haveMinutesPassedSinceBeenHere_INT", "");
const sp<EventScriptQualifier> EventData::haveHoursPassedSinceBeenHere_INT = ms<EventScriptQualifier>("haveHoursPassedSinceBeenHere_INT", "");
const sp<EventScriptQualifier> EventData::haveDaysPassedSinceBeenHere_INT = ms<EventScriptQualifier>("haveDaysPassedSinceBeenHere_INT", "");
const sp<EventScriptQualifier> EventData::isLightOn_LIGHT = ms<EventScriptQualifier>("isLightOn_LIGHT", "");
const sp<EventScriptCommand> EventData::alwaysBlockWhileNotStandingHere = ms<EventScriptCommand>("alwaysBlockWhileNotStandingHere", "");
const sp<EventScriptCommand> EventData::e00 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::blockUntilActionButtonPressed = ms<EventScriptCommand>("blockUntilActionButtonPressed", "");
const sp<EventScriptCommand> EventData::blockUntilActionCaptionButtonPressed_STRING = ms<EventScriptCommand>("blockUntilActionCaptionButtonPressed_STRING", "");
const sp<EventScriptCommand> EventData::blockUntilCancelButtonPressed = ms<EventScriptCommand>("blockUntilCancelButtonPressed", "");
const sp<EventScriptCommand> EventData::blockForTicks_INT = ms<EventScriptCommand>("blockForTicks_INT", "");
const sp<EventScriptCommand> EventData::blockUntilClockHour_INT23 = ms<EventScriptCommand>("blockUntilClockHour_INT23", "");
const sp<EventScriptCommand> EventData::blockUntilClockMinute_INT59 = ms<EventScriptCommand>("blockUntilClockMinute_INT59", "");
const sp<EventScriptCommand> EventData::e000 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::loadMapState_STATE = ms<EventScriptCommand>("loadMapState_STATE", "");
const sp<EventScriptCommand> EventData::runEvent_EVENT = ms<EventScriptCommand>("runEvent_EVENT", "");
const sp<EventScriptCommand> EventData::blockUntilEventDone_EVENT = ms<EventScriptCommand>("blockUntilEventDone_EVENT", "");
const sp<EventScriptCommand> EventData::clearThisEvent = ms<EventScriptCommand>("clearThisEvent", "");
const sp<EventScriptCommand> EventData::clearEvent_EVENT = ms<EventScriptCommand>("clearEvent_EVENT", "");
const sp<EventScriptCommand> EventData::e001 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setThisActivated_BOOL = ms<EventScriptCommand>("setThisActivated_BOOL", "");
const sp<EventScriptCommand> EventData::toggleThisActivated = ms<EventScriptCommand>("toggleThisActivated", "");
const sp<EventScriptCommand> EventData::e002 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setLastBeenHereTime = ms<EventScriptCommand>("setLastBeenHereTime", "");
const sp<EventScriptCommand> EventData::resetLastBeenHereTime = ms<EventScriptCommand>("resetLastBeenHereTime", "");
const sp<EventScriptCommand> EventData::e003 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setFlag_FLAG_BOOL = ms<EventScriptCommand>("setFlag_FLAG_BOOL", "");
const sp<EventScriptCommand> EventData::setFlagTrue_FLAG = ms<EventScriptCommand>("setFlagTrue_FLAG", "");
const sp<EventScriptCommand> EventData::setFlagFalse_FLAG = ms<EventScriptCommand>("setFlagFalse_FLAG", "");
const sp<EventScriptCommand> EventData::e004 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::giveSkillPoints_SKILL_INT = ms<EventScriptCommand>("giveSkillPoints_SKILL_INT", "");
const sp<EventScriptCommand> EventData::removeSkillPoints_SKILL_INT = ms<EventScriptCommand>("removeSkillPoints_SKILL_INT", "");
const sp<EventScriptCommand> EventData::setSkillPoints_SKILL_INT = ms<EventScriptCommand>("setSkillPoints_SKILL_INT", "");
const sp<EventScriptCommand> EventData::e005 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::enterThisDoor = ms<EventScriptCommand>("enterThisDoor", "");
const sp<EventScriptCommand> EventData::enterThisWarp = ms<EventScriptCommand>("enterThisWarp", "");
const sp<EventScriptCommand> EventData::enterDoor_DOOR = ms<EventScriptCommand>("enterDoor_DOOR", "");
const sp<EventScriptCommand> EventData::enterWarp_WARP = ms<EventScriptCommand>("enterWarp_WARP", "");
const sp<EventScriptCommand> EventData::changeMap_MAP_AREA = ms<EventScriptCommand>("changeMap_MAP_AREA", "");
const sp<EventScriptCommand> EventData::changeMap_MAP_DOOR = ms<EventScriptCommand>("changeMap_MAP_DOOR", "");
const sp<EventScriptCommand> EventData::changeMap_MAP_WARP = ms<EventScriptCommand>("changeMap_MAP_WARP", "");
const sp<EventScriptCommand> EventData::changeMap_MAP_INT_INT = ms<EventScriptCommand>("changeMap_MAP_INT_INT", "");
const sp<EventScriptCommand> EventData::e006 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::doDialogue_DIALOGUE = ms<EventScriptCommand>("doDialogue_DIALOGUE", "");
const sp<EventScriptCommand> EventData::doDialogueWithCaption_DIALOGUE = ms<EventScriptCommand>("doDialogueWithCaption_DIALOGUE", "");
const sp<EventScriptCommand> EventData::doDialogueIfNew_DIALOGUE = ms<EventScriptCommand>("doDialogueIfNew_DIALOGUE", "");
const sp<EventScriptCommand> EventData::e007 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setSpriteBox0_ENTITY = ms<EventScriptCommand>("setSpriteBox0_ENTITY", "");
const sp<EventScriptCommand> EventData::setSpriteBox1_ENTITY = ms<EventScriptCommand>("setSpriteBox1_ENTITY", "");
const sp<EventScriptCommand> EventData::setSpriteBox0_SPRITE = ms<EventScriptCommand>("setSpriteBox0_SPRITE", "");
const sp<EventScriptCommand> EventData::setSpriteBox1_SPRITE = ms<EventScriptCommand>("setSpriteBox1_SPRITE", "");
const sp<EventScriptCommand> EventData::e008 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::blockUntilTextBoxClosed = ms<EventScriptCommand>("blockUntilTextBoxClosed", "");
const sp<EventScriptCommand> EventData::blockUntilTextAnswerBoxClosed = ms<EventScriptCommand>("blockUntilTextAnswerBoxClosed", "");
const sp<EventScriptCommand> EventData::e009 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::doCinematicTextNoBorder_DIALOGUE_INTy = ms<EventScriptCommand>("doCinematicTextNoBorder_DIALOGUE_INTy", "");
const sp<EventScriptCommand> EventData::e025 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setDoorOpenAnimation_DOOR_BOOLopenClose = ms<EventScriptCommand>("setDoorOpenAnimation_DOOR_BOOLopenClose", "");
const sp<EventScriptCommand> EventData::setDoorActionIcon_DOOR_BOOLonOff = ms<EventScriptCommand>("setDoorActionIcon_DOOR_BOOLonOff", "");
const sp<EventScriptCommand> EventData::setDoorDestination_DOOR_DOORdestination = ms<EventScriptCommand>("setDoorDestination_DOOR_DOORdestination", "");
const sp<EventScriptCommand> EventData::setAreaActionIcon_AREA_BOOLonOff = ms<EventScriptCommand>("setAreaActionIcon_AREA_BOOLonOff", "");
const sp<EventScriptCommand> EventData::setWarpDestination_WARP_WARPdestination = ms<EventScriptCommand>("setWarpDestination_WARP_WARPdestination", "");
const sp<EventScriptCommand> EventData::e010 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::e012 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setCameraNoTarget = ms<EventScriptCommand>("setCameraNoTarget", "");
const sp<EventScriptCommand> EventData::setCameraTargetToArea_AREA = ms<EventScriptCommand>("setCameraTargetToArea_AREA", "");
const sp<EventScriptCommand> EventData::setCameraTargetToEntity_ENTITY = ms<EventScriptCommand>("setCameraTargetToEntity_ENTITY", "");
const sp<EventScriptCommand> EventData::setCameraIgnoreBounds_BOOL = ms<EventScriptCommand>("setCameraIgnoreBounds_BOOL", "");
const sp<EventScriptCommand> EventData::setCameraTargetToPlayer = ms<EventScriptCommand>("setCameraTargetToPlayer", "");
const sp<EventScriptCommand> EventData::blockUntilCameraReaches_AREA = ms<EventScriptCommand>("blockUntilCameraReaches_AREA", "");
const sp<EventScriptCommand> EventData::blockUntilCameraReaches_ENTITY = ms<EventScriptCommand>("blockUntilCameraReaches_ENTITY", "");
const sp<EventScriptCommand> EventData::blockUntilCameraReachesPlayer = ms<EventScriptCommand>("blockUntilCameraReachesPlayer", "");
const sp<EventScriptCommand> EventData::pushCameraState = ms<EventScriptCommand>("pushCameraState", "");
const sp<EventScriptCommand> EventData::popCameraState = ms<EventScriptCommand>("popCameraState", "");
const sp<EventScriptCommand> EventData::setKeyboardCameraZoom_BOOL = ms<EventScriptCommand>("setKeyboardCameraZoom_BOOL", "");
const sp<EventScriptCommand> EventData::enableKeyboardCameraZoom = ms<EventScriptCommand>("enableKeyboardCameraZoom", "");
const sp<EventScriptCommand> EventData::disableKeyboardCameraZoom = ms<EventScriptCommand>("disableKeyboardCameraZoom", "");
const sp<EventScriptCommand> EventData::setCameraAutoZoomByPlayerMovement_BOOL = ms<EventScriptCommand>("setCameraAutoZoomByPlayerMovement_BOOL", "");
const sp<EventScriptCommand> EventData::enableCameraAutoZoomByPlayerMovement = ms<EventScriptCommand>("enableCameraAutoZoomByPlayerMovement", "");
const sp<EventScriptCommand> EventData::disableCameraAutoZoomByPlayerMovement = ms<EventScriptCommand>("disableCameraAutoZoomByPlayerMovement", "");
const sp<EventScriptCommand> EventData::setCameraZoom_FLOAT = ms<EventScriptCommand>("setCameraZoom_FLOAT", "");
const sp<EventScriptCommand> EventData::setCameraSpeed_FLOAT = ms<EventScriptCommand>("setCameraSpeed_FLOAT", "");
const sp<EventScriptCommand> EventData::setPlayerToTempPlayerWithSprite_SPRITE = ms<EventScriptCommand>("setPlayerToTempPlayerWithSprite_SPRITE", "");
const sp<EventScriptCommand> EventData::setPlayerToNormalPlayer = ms<EventScriptCommand>("setPlayerToNormalPlayer", "");
const sp<EventScriptCommand> EventData::setPlayerExists_BOOL = ms<EventScriptCommand>("setPlayerExists_BOOL", "");
const sp<EventScriptCommand> EventData::setPlayerControlsEnabled_BOOL = ms<EventScriptCommand>("setPlayerControlsEnabled_BOOL", "");
const sp<EventScriptCommand> EventData::enablePlayerControls = ms<EventScriptCommand>("enablePlayerControls", "");
const sp<EventScriptCommand> EventData::disablePlayerControls = ms<EventScriptCommand>("disablePlayerControls", "");
const sp<EventScriptCommand> EventData::setPlayerAutoPilot_BOOL = ms<EventScriptCommand>("setPlayerAutoPilot_BOOL", "");
const sp<EventScriptCommand> EventData::setPlayerShowNameCaption_BOOL = ms<EventScriptCommand>("setPlayerShowNameCaption_BOOL", "");
const sp<EventScriptCommand> EventData::setPlayerShowAccountTypeCaption_BOOL = ms<EventScriptCommand>("setPlayerShowAccountTypeCaption_BOOL", "");
const sp<EventScriptCommand> EventData::playerSetBehaviorQueueOnOff_BOOL = ms<EventScriptCommand>("playerSetBehaviorQueueOnOff_BOOL", "");
const sp<EventScriptCommand> EventData::playerSetToArea_AREA = ms<EventScriptCommand>("playerSetToArea_AREA", "");
const sp<EventScriptCommand> EventData::playerSetToDoor_DOOR = ms<EventScriptCommand>("playerSetToDoor_DOOR", "");
const sp<EventScriptCommand> EventData::playerSetToTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("playerSetToTileXY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::playerWalkToArea_AREA = ms<EventScriptCommand>("playerWalkToArea_AREA", "");
const sp<EventScriptCommand> EventData::playerWalkToDoor_DOOR = ms<EventScriptCommand>("playerWalkToDoor_DOOR", "");
const sp<EventScriptCommand> EventData::playerWalkToEntity_ENTITY = ms<EventScriptCommand>("playerWalkToEntity_ENTITY", "");
const sp<EventScriptCommand> EventData::playerWalkToTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("playerWalkToTileXY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::playerBlockUntilReachesArea_AREA = ms<EventScriptCommand>("playerBlockUntilReachesArea_AREA", "");
const sp<EventScriptCommand> EventData::playerBlockUntilReachesDoor_DOOR = ms<EventScriptCommand>("playerBlockUntilReachesDoor_DOOR", "");
const sp<EventScriptCommand> EventData::playerBlockUntilReachesEntity_ENTITY = ms<EventScriptCommand>("playerBlockUntilReachesEntity_ENTITY", "");
const sp<EventScriptCommand> EventData::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::playerWalkToAreaAndBlockUntilThere_AREA = ms<EventScriptCommand>("playerWalkToAreaAndBlockUntilThere_AREA", "");
const sp<EventScriptCommand> EventData::playerWalkToEntityAndBlockUntilThere_ENTITY = ms<EventScriptCommand>("playerWalkToEntityAndBlockUntilThere_ENTITY", "");
const sp<EventScriptCommand> EventData::playerWalkToDoorAndBlockUntilThere_DOOR = ms<EventScriptCommand>("playerWalkToDoorAndBlockUntilThere_DOOR", "");
const sp<EventScriptCommand> EventData::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::playerStandAndShuffle = ms<EventScriptCommand>("playerStandAndShuffle", "");
const sp<EventScriptCommand> EventData::playerStandAndShuffleAndFaceEntity_ENTITY = ms<EventScriptCommand>("playerStandAndShuffleAndFaceEntity_ENTITY", "");
const sp<EventScriptCommand> EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame = ms<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame", "");
const sp<EventScriptCommand> EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame = ms<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame", "");
const sp<EventScriptCommand> EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::playerStopAnimating = ms<EventScriptCommand>("playerStopAnimating", "");
const sp<EventScriptCommand> EventData::playerSetGlobalAnimationDisabled_BOOL = ms<EventScriptCommand>("playerSetGlobalAnimationDisabled_BOOL", "");
const sp<EventScriptCommand> EventData::playerSetMovementSpeed_INTticksPerPixel = ms<EventScriptCommand>("playerSetMovementSpeed_INTticksPerPixel", "");
const sp<EventScriptCommand> EventData::playerSetFaceMovementDirection_STRINGdirection = ms<EventScriptCommand>("playerSetFaceMovementDirection_STRINGdirection", "");
const sp<EventScriptCommand> EventData::playerSetToAlpha_FLOAT = ms<EventScriptCommand>("playerSetToAlpha_FLOAT", "");
const sp<EventScriptCommand> EventData::e024 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::entitySetBehaviorQueueOnOff_ENTITY_BOOL = ms<EventScriptCommand>("entitySetBehaviorQueueOnOff_ENTITY_BOOL", "");
const sp<EventScriptCommand> EventData::entitySetToArea_ENTITY_AREA = ms<EventScriptCommand>("entitySetToArea_ENTITY_AREA", "");
const sp<EventScriptCommand> EventData::entitySetToDoor_ENTITY_DOOR = ms<EventScriptCommand>("entitySetToDoor_ENTITY_DOOR", "");
const sp<EventScriptCommand> EventData::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::entityWalkToArea_ENTITY_AREA = ms<EventScriptCommand>("entityWalkToArea_ENTITY_AREA", "");
const sp<EventScriptCommand> EventData::entityWalkToDoor_ENTITY_DOOR = ms<EventScriptCommand>("entityWalkToDoor_ENTITY_DOOR", "");
const sp<EventScriptCommand> EventData::entityWalkToEntity_ENTITY_ENTITY = ms<EventScriptCommand>("entityWalkToEntity_ENTITY_ENTITY", "");
const sp<EventScriptCommand> EventData::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const sp<EventScriptCommand> EventData::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const sp<EventScriptCommand> EventData::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const sp<EventScriptCommand> EventData::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = ms<EventScriptCommand>("entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const sp<EventScriptCommand> EventData::entityBlockUntilReachesArea_ENTITY_AREA = ms<EventScriptCommand>("entityBlockUntilReachesArea_ENTITY_AREA", "");
const sp<EventScriptCommand> EventData::entityBlockUntilReachesDoor_ENTITY_DOOR = ms<EventScriptCommand>("entityBlockUntilReachesDoor_ENTITY_DOOR", "");
const sp<EventScriptCommand> EventData::entityBlockUntilReachesEntity_ENTITY_ENTITY = ms<EventScriptCommand>("entityBlockUntilReachesEntity_ENTITY_ENTITY", "");
const sp<EventScriptCommand> EventData::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA = ms<EventScriptCommand>("entityWalkToAreaAndBlockUntilThere_ENTITY_AREA", "");
const sp<EventScriptCommand> EventData::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY = ms<EventScriptCommand>("entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY", "");
const sp<EventScriptCommand> EventData::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR = ms<EventScriptCommand>("entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR", "");
const sp<EventScriptCommand> EventData::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X = ms<EventScriptCommand>("entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X", "");
const sp<EventScriptCommand> EventData::entityStandAndShuffle_ENTITY = ms<EventScriptCommand>("entityStandAndShuffle_ENTITY", "");
const sp<EventScriptCommand> EventData::entityStandAndShuffleAndFacePlayer_ENTITY = ms<EventScriptCommand>("entityStandAndShuffleAndFacePlayer_ENTITY", "");
const sp<EventScriptCommand> EventData::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY = ms<EventScriptCommand>("entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY", "");
const sp<EventScriptCommand> EventData::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName = ms<EventScriptCommand>("entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName", "");
const sp<EventScriptCommand> EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame = ms<EventScriptCommand>("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const sp<EventScriptCommand> EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame = ms<EventScriptCommand>("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const sp<EventScriptCommand> EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = ms<EventScriptCommand>("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const sp<EventScriptCommand> EventData::entityStopAnimating_ENTITY = ms<EventScriptCommand>("entityStopAnimating_ENTITY", "");
const sp<EventScriptCommand> EventData::entitySetGlobalAnimationDisabled_ENTITY_BOOL = ms<EventScriptCommand>("entitySetGlobalAnimationDisabled_ENTITY_BOOL", "");
const sp<EventScriptCommand> EventData::entitySetMovementSpeed_ENTITY_INTticksPerPixel = ms<EventScriptCommand>("entitySetMovementSpeed_ENTITY_INTticksPerPixel", "");
const sp<EventScriptCommand> EventData::entitySetFaceMovementDirection_ENTITY_STRINGdirection = ms<EventScriptCommand>("entitySetFaceMovementDirection_ENTITY_STRINGdirection", "");
const sp<EventScriptCommand> EventData::entitySetNonWalkable_ENTITY_BOOL = ms<EventScriptCommand>("entitySetNonWalkable_ENTITY_BOOL", "");
const sp<EventScriptCommand> EventData::entitySetPushable_ENTITY_BOOL = ms<EventScriptCommand>("entitySetPushable_ENTITY_BOOL", "");
const sp<EventScriptCommand> EventData::entitySetToAlpha_ENTITY_FLOAT = ms<EventScriptCommand>("entitySetToAlpha_ENTITY_FLOAT", "");
const sp<EventScriptCommand> EventData::entityFadeOutDelete_ENTITY = ms<EventScriptCommand>("entityFadeOutDelete_ENTITY", "");
const sp<EventScriptCommand> EventData::entityDeleteInstantly_ENTITY = ms<EventScriptCommand>("entityDeleteInstantly_ENTITY", "");
const sp<EventScriptCommand> EventData::e016 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA = ms<EventScriptCommand>("spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA", "");
const sp<EventScriptCommand> EventData::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA = ms<EventScriptCommand>("spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const sp<EventScriptCommand> EventData::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA = ms<EventScriptCommand>("spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA", "");
const sp<EventScriptCommand> EventData::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA = ms<EventScriptCommand>("spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const sp<EventScriptCommand> EventData::e017 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = ms<EventScriptCommand>("createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const sp<EventScriptCommand> EventData::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = ms<EventScriptCommand>("createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const sp<EventScriptCommand> EventData::createScreenSpriteUnderText_SPRITE_INTx_INTy = ms<EventScriptCommand>("createScreenSpriteUnderText_SPRITE_INTx_INTy", "");
const sp<EventScriptCommand> EventData::createScreenSpriteOverText_SPRITE_INTx_INTy = ms<EventScriptCommand>("createScreenSpriteOverText_SPRITE_INTx_INTy", "");
const sp<EventScriptCommand> EventData::e026 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::giveItem_ITEM = ms<EventScriptCommand>("giveItem_ITEM", "");
const sp<EventScriptCommand> EventData::takeItem_ITEM = ms<EventScriptCommand>("takeItem_ITEM", "");
const sp<EventScriptCommand> EventData::giveGame_GAME = ms<EventScriptCommand>("giveGame_GAME", "");
const sp<EventScriptCommand> EventData::takeMoney_FLOAT = ms<EventScriptCommand>("takeMoney_FLOAT", "");
const sp<EventScriptCommand> EventData::giveMoney_FLOAT = ms<EventScriptCommand>("giveMoney_FLOAT", "");
const sp<EventScriptCommand> EventData::e027 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::playSound_SOUND = ms<EventScriptCommand>("playSound_SOUND", "");
const sp<EventScriptCommand> EventData::playSound_SOUND_FLOATvol = ms<EventScriptCommand>("playSound_SOUND_FLOATvol", "");
const sp<EventScriptCommand> EventData::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes = ms<EventScriptCommand>("playSound_SOUND_FLOATvol_FLOATpitch_INTtimes", "");
const sp<EventScriptCommand> EventData::playMusicOnce_MUSIC = ms<EventScriptCommand>("playMusicOnce_MUSIC", "");
const sp<EventScriptCommand> EventData::playMusicLoop_MUSIC = ms<EventScriptCommand>("playMusicLoop_MUSIC", "");
const sp<EventScriptCommand> EventData::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop = ms<EventScriptCommand>("playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop", "");
const sp<EventScriptCommand> EventData::stopAllMusic = ms<EventScriptCommand>("stopAllMusic", "");
const sp<EventScriptCommand> EventData::stopMusic_MUSIC = ms<EventScriptCommand>("stopMusic_MUSIC", "");
const sp<EventScriptCommand> EventData::fadeOutMusic_MUSIC_INT = ms<EventScriptCommand>("fadeOutMusic_MUSIC_INT", "");
const sp<EventScriptCommand> EventData::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC = ms<EventScriptCommand>("blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC", "");
const sp<EventScriptCommand> EventData::blockUntilMusicDone_MUSIC = ms<EventScriptCommand>("blockUntilMusicDone_MUSIC", "");
const sp<EventScriptCommand> EventData::fadeOutAllMusic_INT = ms<EventScriptCommand>("fadeOutAllMusic_INT", "");
const sp<EventScriptCommand> EventData::blockUntilAllMusicDone = ms<EventScriptCommand>("blockUntilAllMusicDone", "");
const sp<EventScriptCommand> EventData::e028 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake = ms<EventScriptCommand>("shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake", "");
const sp<EventScriptCommand> EventData::fadeToBlack_INTticks = ms<EventScriptCommand>("fadeToBlack_INTticks", "");
const sp<EventScriptCommand> EventData::fadeFromBlack_INTticks = ms<EventScriptCommand>("fadeFromBlack_INTticks", "");
const sp<EventScriptCommand> EventData::fadeToWhite_INTticks = ms<EventScriptCommand>("fadeToWhite_INTticks", "");
const sp<EventScriptCommand> EventData::fadeFromWhite_INTticks = ms<EventScriptCommand>("fadeFromWhite_INTticks", "");
const sp<EventScriptCommand> EventData::e029 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha = ms<EventScriptCommand>("fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const sp<EventScriptCommand> EventData::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha = ms<EventScriptCommand>("fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha", "");
const sp<EventScriptCommand> EventData::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha = ms<EventScriptCommand>("fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const sp<EventScriptCommand> EventData::setInstantOverlay_INTr_INTg_INTb_FLOATa = ms<EventScriptCommand>("setInstantOverlay_INTr_INTg_INTb_FLOATa", "");
const sp<EventScriptCommand> EventData::clearOverlay = ms<EventScriptCommand>("clearOverlay", "");
const sp<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha = ms<EventScriptCommand>("fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const sp<EventScriptCommand> EventData::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa = ms<EventScriptCommand>("setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa", "");
const sp<EventScriptCommand> EventData::clearOverlayUnderLights = ms<EventScriptCommand>("clearOverlayUnderLights", "");
const sp<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha = ms<EventScriptCommand>("fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const sp<EventScriptCommand> EventData::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa = ms<EventScriptCommand>("setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa", "");
const sp<EventScriptCommand> EventData::clearOverlayGroundLayer = ms<EventScriptCommand>("clearOverlayGroundLayer", "");
const sp<EventScriptCommand> EventData::e030 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setLetterbox_BOOL = ms<EventScriptCommand>("setLetterbox_BOOL", "");
const sp<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks = ms<EventScriptCommand>("setLetterbox_BOOL_INTticks", "");
const sp<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks_INTsize = ms<EventScriptCommand>("setLetterbox_BOOL_INTticks_INTsize", "");
const sp<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks_FLOATsize = ms<EventScriptCommand>("setLetterbox_BOOL_INTticks_FLOATsize", "");
const sp<EventScriptCommand> EventData::setBlur_BOOL = ms<EventScriptCommand>("setBlur_BOOL", "");
const sp<EventScriptCommand> EventData::setMosaic_BOOL = ms<EventScriptCommand>("setMosaic_BOOL", "");
const sp<EventScriptCommand> EventData::setHBlankWave_BOOL = ms<EventScriptCommand>("setHBlankWave_BOOL", "");
const sp<EventScriptCommand> EventData::setRotate_BOOL = ms<EventScriptCommand>("setRotate_BOOL", "");
const sp<EventScriptCommand> EventData::setBlackAndWhite_BOOL = ms<EventScriptCommand>("setBlackAndWhite_BOOL", "");
const sp<EventScriptCommand> EventData::setInvertedColors_BOOL = ms<EventScriptCommand>("setInvertedColors_BOOL", "");
const sp<EventScriptCommand> EventData::set8BitMode_BOOL = ms<EventScriptCommand>("set8BitMode_BOOL", "");
const sp<EventScriptCommand> EventData::e031 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setEngineSpeed_FLOAT = ms<EventScriptCommand>("setEngineSpeed_FLOAT", "");
const sp<EventScriptCommand> EventData::e032 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::toggleLightOnOff_LIGHT = ms<EventScriptCommand>("toggleLightOnOff_LIGHT", "");
const sp<EventScriptCommand> EventData::setLightOnOff_LIGHT_BOOL = ms<EventScriptCommand>("setLightOnOff_LIGHT_BOOL", "");
const sp<EventScriptCommand> EventData::setLightFlicker_LIGHT_BOOL = ms<EventScriptCommand>("setLightFlicker_LIGHT_BOOL", "");
const sp<EventScriptCommand> EventData::toggleAllLightsOnOff = ms<EventScriptCommand>("toggleAllLightsOnOff", "");
const sp<EventScriptCommand> EventData::setAllLightsOnOff_BOOL = ms<EventScriptCommand>("setAllLightsOnOff_BOOL", "");
const sp<EventScriptCommand> EventData::e033 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setRandomSpawn_BOOL = ms<EventScriptCommand>("setRandomSpawn_BOOL", "");
const sp<EventScriptCommand> EventData::deleteRandoms = ms<EventScriptCommand>("deleteRandoms", "");
const sp<EventScriptCommand> EventData::e034 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = ms<EventScriptCommand>("makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const sp<EventScriptCommand> EventData::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb = ms<EventScriptCommand>("makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb", "");
const sp<EventScriptCommand> EventData::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb = ms<EventScriptCommand>("makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb", "");
const sp<EventScriptCommand> EventData::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = ms<EventScriptCommand>("makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const sp<EventScriptCommand> EventData::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks = ms<EventScriptCommand>("setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks", "");
const sp<EventScriptCommand> EventData::e035 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setShowClockCaption_BOOL = ms<EventScriptCommand>("setShowClockCaption_BOOL", "");
const sp<EventScriptCommand> EventData::setShowDayCaption_BOOL = ms<EventScriptCommand>("setShowDayCaption_BOOL", "");
const sp<EventScriptCommand> EventData::setShowMoneyCaption_BOOL = ms<EventScriptCommand>("setShowMoneyCaption_BOOL", "");
const sp<EventScriptCommand> EventData::setShowAllStatusBarCaptions_BOOL = ms<EventScriptCommand>("setShowAllStatusBarCaptions_BOOL", "");
const sp<EventScriptCommand> EventData::setShowStatusBar_BOOL = ms<EventScriptCommand>("setShowStatusBar_BOOL", "");
const sp<EventScriptCommand> EventData::setShowNDButton_BOOL = ms<EventScriptCommand>("setShowNDButton_BOOL", "");
const sp<EventScriptCommand> EventData::setShowGameStoreButton_BOOL = ms<EventScriptCommand>("setShowGameStoreButton_BOOL", "");
const sp<EventScriptCommand> EventData::setShowStuffButton_BOOL = ms<EventScriptCommand>("setShowStuffButton_BOOL", "");
const sp<EventScriptCommand> EventData::setShowAllButtons_BOOL = ms<EventScriptCommand>("setShowAllButtons_BOOL", "");
const sp<EventScriptCommand> EventData::setNDEnabled_BOOL = ms<EventScriptCommand>("setNDEnabled_BOOL", "");
const sp<EventScriptCommand> EventData::setGameStoreMenuEnabled_BOOL = ms<EventScriptCommand>("setGameStoreMenuEnabled_BOOL", "");
const sp<EventScriptCommand> EventData::setStuffMenuEnabled_BOOL = ms<EventScriptCommand>("setStuffMenuEnabled_BOOL", "");
const sp<EventScriptCommand> EventData::setAllMenusAndNDEnabled_BOOL = ms<EventScriptCommand>("setAllMenusAndNDEnabled_BOOL", "");
const sp<EventScriptCommand> EventData::e046 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setClockUnknown = ms<EventScriptCommand>("setClockUnknown", "");
const sp<EventScriptCommand> EventData::setClockNormal = ms<EventScriptCommand>("setClockNormal", "");
const sp<EventScriptCommand> EventData::setTimePaused_BOOL = ms<EventScriptCommand>("setTimePaused_BOOL", "");
const sp<EventScriptCommand> EventData::setTimeFastForward = ms<EventScriptCommand>("setTimeFastForward", "");
const sp<EventScriptCommand> EventData::setTimeNormalSpeed = ms<EventScriptCommand>("setTimeNormalSpeed", "");
const sp<EventScriptCommand> EventData::e037 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::setNDOpen_BOOL = ms<EventScriptCommand>("setNDOpen_BOOL", "");
const sp<EventScriptCommand> EventData::startGame = ms<EventScriptCommand>("startGame", "");
const sp<EventScriptCommand> EventData::startOKGameOnStadiumScreen_AREA = ms<EventScriptCommand>("startOKGameOnStadiumScreen_AREA", "");
const sp<EventScriptCommand> EventData::blockUntilOKGameDead = ms<EventScriptCommand>("blockUntilOKGameDead", "");
const sp<EventScriptCommand> EventData::showLoginScreen = ms<EventScriptCommand>("showLoginScreen", "");
const sp<EventScriptCommand> EventData::e038 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::closeAllMenusAndND = ms<EventScriptCommand>("closeAllMenusAndND", "");
const sp<EventScriptCommand> EventData::e039 = ms<EventScriptCommand>();
const sp<EventScriptCommand> EventData::openStuffMenu = ms<EventScriptCommand>("openStuffMenu", "");
const sp<EventScriptCommand> EventData::openItemsMenu = ms<EventScriptCommand>("openItemsMenu", "");
const sp<EventScriptCommand> EventData::openLogMenu = ms<EventScriptCommand>("openLogMenu", "");
const sp<EventScriptCommand> EventData::openStatusMenu = ms<EventScriptCommand>("openStatusMenu", "");
const sp<EventScriptCommand> EventData::openFriendsMenu = ms<EventScriptCommand>("openFriendsMenu", "");
const sp<EventScriptCommand> EventData::openSettingsMenu = ms<EventScriptCommand>("openSettingsMenu", "");
const sp<EventScriptCommand> EventData::openGameStoreMenu = ms<EventScriptCommand>("openGameStoreMenu", "");

