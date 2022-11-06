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

//shared_ptr<EventData> EventData::fromBase64ZippedJSON(const string& b64)
//{ //===============================================================================================
//
//
//	string json = FileUtils::unzipBase64StringToString(b64);
//
//	//Gson gson = make_shared<Gson>();
//	//EventData data = gson.fromJson(json,EventData.class);
//
//	return fromJSON(json);
//}
//
//shared_ptr<EventData> EventData::fromJSON(const string& json)
//{ //===============================================================================================
//
//	//shared_ptr<Gson> gson = make_shared<Gson>();
//	shared_ptr<EventData> data = nullptr;//gson->fromJson(json, EventData::typeid);
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
			shared_ptr<DialogueData> data = make_shared<DialogueData>();
			t = data->initFromString(t);
			dialogueDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("flagDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			shared_ptr<FlagData> data = make_shared<FlagData>();
			t = data->initFromString(t);
			flagDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("skillDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			shared_ptr<SkillData> data = make_shared<SkillData>();
			t = data->initFromString(t);
			skillDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("gameStringDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			shared_ptr<GameStringData> data = make_shared<GameStringData>();
			t = data->initFromString(t);
			gameStringDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("musicDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			shared_ptr<AudioData> data = make_shared<AudioData>();
			t = data->initFromString(t);
			musicDataList->add(data);
		}
		t = t.substr(t.find("}") + 1);
		t = t.substr(t.find(",") + 1);

		t = t.substr(t.find("soundDataList:{") + 1);
		t = t.substr(t.find("{") + 1);
		while (String::startsWith(t,"}") == false)
		{
			shared_ptr<AudioData> data = make_shared<AudioData>();
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

EventScriptTree::EventScriptTree(shared_ptr<EventData> outerInstance) : outerInstance(outerInstance)
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

ArrayList<shared_ptr<EventScriptCommand>>* EventData::commandList = make_shared<ArrayList><shared_ptr<EventScriptCommand>>();
ArrayList<shared_ptr<EventScriptQualifier>>* EventData::qualifierList = make_shared<ArrayList><shared_ptr<EventScriptQualifier>>();

const shared_ptr<EventScriptQualifier> EventData::isPlayerTouchingThisArea = make_shared<EventScriptQualifier>("isPlayerTouchingThisArea", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerWalkingIntoThisDoor = make_shared<EventScriptQualifier>("isPlayerWalkingIntoThisDoor", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerTouchingThisEntity = make_shared<EventScriptQualifier>("isPlayerTouchingThisEntity", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerTouchingAnyEntityUsingThisSprite = make_shared<EventScriptQualifier>("isPlayerTouchingAnyEntityUsingThisSprite", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerWalkingIntoDoor_DOOR = make_shared<EventScriptQualifier>("isPlayerWalkingIntoDoor_DOOR", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerWalkingIntoWarp_WARP = make_shared<EventScriptQualifier>("isPlayerWalkingIntoWarp_WARP", "");
const shared_ptr<EventScriptQualifier> EventData::isActionButtonHeld = make_shared<EventScriptQualifier>("isActionButtonHeld", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerAutoPilotOn = make_shared<EventScriptQualifier>("isPlayerAutoPilotOn", "");
const shared_ptr<EventScriptQualifier> EventData::isFlagSet_FLAG = make_shared<EventScriptQualifier>("isFlagSet_FLAG", "");
const shared_ptr<EventScriptQualifier> EventData::hasSkillAtLeast_SKILL_FLOAT1 = make_shared<EventScriptQualifier>("hasSkillAtLeast_SKILL_FLOAT1", "");
const shared_ptr<EventScriptQualifier> EventData::isCurrentState_STATE = make_shared<EventScriptQualifier>("isCurrentState_STATE", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerStandingInArea_AREA = make_shared<EventScriptQualifier>("isPlayerStandingInArea_AREA", "");
const shared_ptr<EventScriptQualifier> EventData::isEntityStandingInArea_ENTITY_AREA = make_shared<EventScriptQualifier>("isEntityStandingInArea_ENTITY_AREA", "");
const shared_ptr<EventScriptQualifier> EventData::hourPastOrEqualTo_INT23 = make_shared<EventScriptQualifier>("hourPastOrEqualTo_INT23", "");
const shared_ptr<EventScriptQualifier> EventData::hourLessThan_INT23 = make_shared<EventScriptQualifier>("hourLessThan_INT23", "");
const shared_ptr<EventScriptQualifier> EventData::minutePastOrEqualTo_INT59 = make_shared<EventScriptQualifier>("minutePastOrEqualTo_INT59", "");
const shared_ptr<EventScriptQualifier> EventData::minuteLessThan_INT59 = make_shared<EventScriptQualifier>("minuteLessThan_INT59", "");
const shared_ptr<EventScriptQualifier> EventData::hasMoneyAtLeastAmount_FLOAT = make_shared<EventScriptQualifier>("hasMoneyAtLeastAmount_FLOAT", "");
const shared_ptr<EventScriptQualifier> EventData::hasMoneyLessThanAmount_FLOAT = make_shared<EventScriptQualifier>("hasMoneyLessThanAmount_FLOAT", "");
const shared_ptr<EventScriptQualifier> EventData::hasItem_ITEM = make_shared<EventScriptQualifier>("hasItem_ITEM", "");
const shared_ptr<EventScriptQualifier> EventData::hasGame_GAME = make_shared<EventScriptQualifier>("hasGame_GAME", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerMale = make_shared<EventScriptQualifier>("isPlayerMale", "");
const shared_ptr<EventScriptQualifier> EventData::isPlayerFemale = make_shared<EventScriptQualifier>("isPlayerFemale", "");
const shared_ptr<EventScriptQualifier> EventData::isAnyEntityUsingSprite_SPRITE = make_shared<EventScriptQualifier>("isAnyEntityUsingSprite_SPRITE", "");
const shared_ptr<EventScriptQualifier> EventData::isAnyEntityUsingSpriteAtArea_SPRITE_AREA = make_shared<EventScriptQualifier>("isAnyEntityUsingSpriteAtArea_SPRITE_AREA", "");
const shared_ptr<EventScriptQualifier> EventData::isEntitySpawned_ENTITY = make_shared<EventScriptQualifier>("isEntitySpawned_ENTITY", "");
const shared_ptr<EventScriptQualifier> EventData::isEntityAtArea_ENTITY_AREA = make_shared<EventScriptQualifier>("isEntityAtArea_ENTITY_AREA", "");
const shared_ptr<EventScriptQualifier> EventData::isAreaEmpty_AREA = make_shared<EventScriptQualifier>("isAreaEmpty_AREA", "");
const shared_ptr<EventScriptQualifier> EventData::hasFinishedDialogue_DIALOGUE = make_shared<EventScriptQualifier>("hasFinishedDialogue_DIALOGUE", "");
const shared_ptr<EventScriptQualifier> EventData::isTextBoxOpen = make_shared<EventScriptQualifier>("isTextBoxOpen", "");
const shared_ptr<EventScriptQualifier> EventData::isTextAnswerBoxOpen = make_shared<EventScriptQualifier>("isTextAnswerBoxOpen", "");
const shared_ptr<EventScriptQualifier> EventData::isTextAnswerSelected_INT4 = make_shared<EventScriptQualifier>("isTextAnswerSelected_INT4", "");
const shared_ptr<EventScriptQualifier> EventData::isTextAnswerSelected_STRING = make_shared<EventScriptQualifier>("isTextAnswerSelected_STRING", "");
const shared_ptr<EventScriptQualifier> EventData::randomEqualsOneOutOfLessThan_INT = make_shared<EventScriptQualifier>("randomEqualsOneOutOfLessThan_INT", "");
const shared_ptr<EventScriptQualifier> EventData::randomEqualsOneOutOfIncluding_INT = make_shared<EventScriptQualifier>("randomEqualsOneOutOfIncluding_INT", "");
const shared_ptr<EventScriptQualifier> EventData::isAnyMusicPlaying = make_shared<EventScriptQualifier>("isAnyMusicPlaying", "");
const shared_ptr<EventScriptQualifier> EventData::isMusicPlaying_MUSIC = make_shared<EventScriptQualifier>("isMusicPlaying_MUSIC", "");
const shared_ptr<EventScriptQualifier> EventData::isRaining = make_shared<EventScriptQualifier>("isRaining", "");
const shared_ptr<EventScriptQualifier> EventData::isWindy = make_shared<EventScriptQualifier>("isWindy", "");
const shared_ptr<EventScriptQualifier> EventData::isSnowing = make_shared<EventScriptQualifier>("isSnowing", "");
const shared_ptr<EventScriptQualifier> EventData::isFoggy = make_shared<EventScriptQualifier>("isFoggy", "");
const shared_ptr<EventScriptQualifier> EventData::isMapOutside = make_shared<EventScriptQualifier>("isMapOutside", "");
const shared_ptr<EventScriptQualifier> EventData::hasTalkedToThisToday = make_shared<EventScriptQualifier>("hasTalkedToThisToday", "");
const shared_ptr<EventScriptQualifier> EventData::hasBeenMinutesSinceFlagSet_FLAG_INT = make_shared<EventScriptQualifier>("hasBeenMinutesSinceFlagSet_FLAG_INT", "");
const shared_ptr<EventScriptQualifier> EventData::hasBeenHoursSinceFlagSet_FLAG_INT23 = make_shared<EventScriptQualifier>("hasBeenHoursSinceFlagSet_FLAG_INT23", "");
const shared_ptr<EventScriptQualifier> EventData::hasBeenDaysSinceFlagSet_FLAG_INT = make_shared<EventScriptQualifier>("hasBeenDaysSinceFlagSet_FLAG_INT", "");
const shared_ptr<EventScriptQualifier> EventData::isThisActivated = make_shared<EventScriptQualifier>("isThisActivated", "");
const shared_ptr<EventScriptQualifier> EventData::haveSecondsPassedSinceActivated_INT = make_shared<EventScriptQualifier>("haveSecondsPassedSinceActivated_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveMinutesPassedSinceActivated_INT = make_shared<EventScriptQualifier>("haveMinutesPassedSinceActivated_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveHoursPassedSinceActivated_INT = make_shared<EventScriptQualifier>("haveHoursPassedSinceActivated_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveDaysPassedSinceActivated_INT = make_shared<EventScriptQualifier>("haveDaysPassedSinceActivated_INT", "");
const shared_ptr<EventScriptQualifier> EventData::hasActivatedThisEver = make_shared<EventScriptQualifier>("hasActivatedThisEver", "");
const shared_ptr<EventScriptQualifier> EventData::hasActivatedThisSinceEnterRoom = make_shared<EventScriptQualifier>("hasActivatedThisSinceEnterRoom", "");
const shared_ptr<EventScriptQualifier> EventData::hasBeenHereEver = make_shared<EventScriptQualifier>("hasBeenHereEver", "");
const shared_ptr<EventScriptQualifier> EventData::hasBeenHereSinceEnterRoom = make_shared<EventScriptQualifier>("hasBeenHereSinceEnterRoom", "");
const shared_ptr<EventScriptQualifier> EventData::haveSecondsPassedSinceBeenHere_INT = make_shared<EventScriptQualifier>("haveSecondsPassedSinceBeenHere_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveMinutesPassedSinceBeenHere_INT = make_shared<EventScriptQualifier>("haveMinutesPassedSinceBeenHere_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveHoursPassedSinceBeenHere_INT = make_shared<EventScriptQualifier>("haveHoursPassedSinceBeenHere_INT", "");
const shared_ptr<EventScriptQualifier> EventData::haveDaysPassedSinceBeenHere_INT = make_shared<EventScriptQualifier>("haveDaysPassedSinceBeenHere_INT", "");
const shared_ptr<EventScriptQualifier> EventData::isLightOn_LIGHT = make_shared<EventScriptQualifier>("isLightOn_LIGHT", "");
const shared_ptr<EventScriptCommand> EventData::alwaysBlockWhileNotStandingHere = make_shared<EventScriptCommand>("alwaysBlockWhileNotStandingHere", "");
const shared_ptr<EventScriptCommand> EventData::e00 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::blockUntilActionButtonPressed = make_shared<EventScriptCommand>("blockUntilActionButtonPressed", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilActionCaptionButtonPressed_STRING = make_shared<EventScriptCommand>("blockUntilActionCaptionButtonPressed_STRING", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilCancelButtonPressed = make_shared<EventScriptCommand>("blockUntilCancelButtonPressed", "");
const shared_ptr<EventScriptCommand> EventData::blockForTicks_INT = make_shared<EventScriptCommand>("blockForTicks_INT", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilClockHour_INT23 = make_shared<EventScriptCommand>("blockUntilClockHour_INT23", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilClockMinute_INT59 = make_shared<EventScriptCommand>("blockUntilClockMinute_INT59", "");
const shared_ptr<EventScriptCommand> EventData::e000 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::loadMapState_STATE = make_shared<EventScriptCommand>("loadMapState_STATE", "");
const shared_ptr<EventScriptCommand> EventData::runEvent_EVENT = make_shared<EventScriptCommand>("runEvent_EVENT", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilEventDone_EVENT = make_shared<EventScriptCommand>("blockUntilEventDone_EVENT", "");
const shared_ptr<EventScriptCommand> EventData::clearThisEvent = make_shared<EventScriptCommand>("clearThisEvent", "");
const shared_ptr<EventScriptCommand> EventData::clearEvent_EVENT = make_shared<EventScriptCommand>("clearEvent_EVENT", "");
const shared_ptr<EventScriptCommand> EventData::e001 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setThisActivated_BOOL = make_shared<EventScriptCommand>("setThisActivated_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::toggleThisActivated = make_shared<EventScriptCommand>("toggleThisActivated", "");
const shared_ptr<EventScriptCommand> EventData::e002 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setLastBeenHereTime = make_shared<EventScriptCommand>("setLastBeenHereTime", "");
const shared_ptr<EventScriptCommand> EventData::resetLastBeenHereTime = make_shared<EventScriptCommand>("resetLastBeenHereTime", "");
const shared_ptr<EventScriptCommand> EventData::e003 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setFlag_FLAG_BOOL = make_shared<EventScriptCommand>("setFlag_FLAG_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setFlagTrue_FLAG = make_shared<EventScriptCommand>("setFlagTrue_FLAG", "");
const shared_ptr<EventScriptCommand> EventData::setFlagFalse_FLAG = make_shared<EventScriptCommand>("setFlagFalse_FLAG", "");
const shared_ptr<EventScriptCommand> EventData::e004 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::giveSkillPoints_SKILL_INT = make_shared<EventScriptCommand>("giveSkillPoints_SKILL_INT", "");
const shared_ptr<EventScriptCommand> EventData::removeSkillPoints_SKILL_INT = make_shared<EventScriptCommand>("removeSkillPoints_SKILL_INT", "");
const shared_ptr<EventScriptCommand> EventData::setSkillPoints_SKILL_INT = make_shared<EventScriptCommand>("setSkillPoints_SKILL_INT", "");
const shared_ptr<EventScriptCommand> EventData::e005 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::enterThisDoor = make_shared<EventScriptCommand>("enterThisDoor", "");
const shared_ptr<EventScriptCommand> EventData::enterThisWarp = make_shared<EventScriptCommand>("enterThisWarp", "");
const shared_ptr<EventScriptCommand> EventData::enterDoor_DOOR = make_shared<EventScriptCommand>("enterDoor_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::enterWarp_WARP = make_shared<EventScriptCommand>("enterWarp_WARP", "");
const shared_ptr<EventScriptCommand> EventData::changeMap_MAP_AREA = make_shared<EventScriptCommand>("changeMap_MAP_AREA", "");
const shared_ptr<EventScriptCommand> EventData::changeMap_MAP_DOOR = make_shared<EventScriptCommand>("changeMap_MAP_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::changeMap_MAP_WARP = make_shared<EventScriptCommand>("changeMap_MAP_WARP", "");
const shared_ptr<EventScriptCommand> EventData::changeMap_MAP_INT_INT = make_shared<EventScriptCommand>("changeMap_MAP_INT_INT", "");
const shared_ptr<EventScriptCommand> EventData::e006 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::doDialogue_DIALOGUE = make_shared<EventScriptCommand>("doDialogue_DIALOGUE", "");
const shared_ptr<EventScriptCommand> EventData::doDialogueWithCaption_DIALOGUE = make_shared<EventScriptCommand>("doDialogueWithCaption_DIALOGUE", "");
const shared_ptr<EventScriptCommand> EventData::doDialogueIfNew_DIALOGUE = make_shared<EventScriptCommand>("doDialogueIfNew_DIALOGUE", "");
const shared_ptr<EventScriptCommand> EventData::e007 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setSpriteBox0_ENTITY = make_shared<EventScriptCommand>("setSpriteBox0_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::setSpriteBox1_ENTITY = make_shared<EventScriptCommand>("setSpriteBox1_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::setSpriteBox0_SPRITE = make_shared<EventScriptCommand>("setSpriteBox0_SPRITE", "");
const shared_ptr<EventScriptCommand> EventData::setSpriteBox1_SPRITE = make_shared<EventScriptCommand>("setSpriteBox1_SPRITE", "");
const shared_ptr<EventScriptCommand> EventData::e008 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::blockUntilTextBoxClosed = make_shared<EventScriptCommand>("blockUntilTextBoxClosed", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilTextAnswerBoxClosed = make_shared<EventScriptCommand>("blockUntilTextAnswerBoxClosed", "");
const shared_ptr<EventScriptCommand> EventData::e009 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::doCinematicTextNoBorder_DIALOGUE_INTy = make_shared<EventScriptCommand>("doCinematicTextNoBorder_DIALOGUE_INTy", "");
const shared_ptr<EventScriptCommand> EventData::e025 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setDoorOpenAnimation_DOOR_BOOLopenClose = make_shared<EventScriptCommand>("setDoorOpenAnimation_DOOR_BOOLopenClose", "");
const shared_ptr<EventScriptCommand> EventData::setDoorActionIcon_DOOR_BOOLonOff = make_shared<EventScriptCommand>("setDoorActionIcon_DOOR_BOOLonOff", "");
const shared_ptr<EventScriptCommand> EventData::setDoorDestination_DOOR_DOORdestination = make_shared<EventScriptCommand>("setDoorDestination_DOOR_DOORdestination", "");
const shared_ptr<EventScriptCommand> EventData::setAreaActionIcon_AREA_BOOLonOff = make_shared<EventScriptCommand>("setAreaActionIcon_AREA_BOOLonOff", "");
const shared_ptr<EventScriptCommand> EventData::setWarpDestination_WARP_WARPdestination = make_shared<EventScriptCommand>("setWarpDestination_WARP_WARPdestination", "");
const shared_ptr<EventScriptCommand> EventData::e010 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::e012 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setCameraNoTarget = make_shared<EventScriptCommand>("setCameraNoTarget", "");
const shared_ptr<EventScriptCommand> EventData::setCameraTargetToArea_AREA = make_shared<EventScriptCommand>("setCameraTargetToArea_AREA", "");
const shared_ptr<EventScriptCommand> EventData::setCameraTargetToEntity_ENTITY = make_shared<EventScriptCommand>("setCameraTargetToEntity_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::setCameraIgnoreBounds_BOOL = make_shared<EventScriptCommand>("setCameraIgnoreBounds_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setCameraTargetToPlayer = make_shared<EventScriptCommand>("setCameraTargetToPlayer", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilCameraReaches_AREA = make_shared<EventScriptCommand>("blockUntilCameraReaches_AREA", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilCameraReaches_ENTITY = make_shared<EventScriptCommand>("blockUntilCameraReaches_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilCameraReachesPlayer = make_shared<EventScriptCommand>("blockUntilCameraReachesPlayer", "");
const shared_ptr<EventScriptCommand> EventData::pushCameraState = make_shared<EventScriptCommand>("pushCameraState", "");
const shared_ptr<EventScriptCommand> EventData::popCameraState = make_shared<EventScriptCommand>("popCameraState", "");
const shared_ptr<EventScriptCommand> EventData::setKeyboardCameraZoom_BOOL = make_shared<EventScriptCommand>("setKeyboardCameraZoom_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::enableKeyboardCameraZoom = make_shared<EventScriptCommand>("enableKeyboardCameraZoom", "");
const shared_ptr<EventScriptCommand> EventData::disableKeyboardCameraZoom = make_shared<EventScriptCommand>("disableKeyboardCameraZoom", "");
const shared_ptr<EventScriptCommand> EventData::setCameraAutoZoomByPlayerMovement_BOOL = make_shared<EventScriptCommand>("setCameraAutoZoomByPlayerMovement_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::enableCameraAutoZoomByPlayerMovement = make_shared<EventScriptCommand>("enableCameraAutoZoomByPlayerMovement", "");
const shared_ptr<EventScriptCommand> EventData::disableCameraAutoZoomByPlayerMovement = make_shared<EventScriptCommand>("disableCameraAutoZoomByPlayerMovement", "");
const shared_ptr<EventScriptCommand> EventData::setCameraZoom_FLOAT = make_shared<EventScriptCommand>("setCameraZoom_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::setCameraSpeed_FLOAT = make_shared<EventScriptCommand>("setCameraSpeed_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerToTempPlayerWithSprite_SPRITE = make_shared<EventScriptCommand>("setPlayerToTempPlayerWithSprite_SPRITE", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerToNormalPlayer = make_shared<EventScriptCommand>("setPlayerToNormalPlayer", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerExists_BOOL = make_shared<EventScriptCommand>("setPlayerExists_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerControlsEnabled_BOOL = make_shared<EventScriptCommand>("setPlayerControlsEnabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::enablePlayerControls = make_shared<EventScriptCommand>("enablePlayerControls", "");
const shared_ptr<EventScriptCommand> EventData::disablePlayerControls = make_shared<EventScriptCommand>("disablePlayerControls", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerAutoPilot_BOOL = make_shared<EventScriptCommand>("setPlayerAutoPilot_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerShowNameCaption_BOOL = make_shared<EventScriptCommand>("setPlayerShowNameCaption_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setPlayerShowAccountTypeCaption_BOOL = make_shared<EventScriptCommand>("setPlayerShowAccountTypeCaption_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::playerSetBehaviorQueueOnOff_BOOL = make_shared<EventScriptCommand>("playerSetBehaviorQueueOnOff_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::playerSetToArea_AREA = make_shared<EventScriptCommand>("playerSetToArea_AREA", "");
const shared_ptr<EventScriptCommand> EventData::playerSetToDoor_DOOR = make_shared<EventScriptCommand>("playerSetToDoor_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::playerSetToTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("playerSetToTileXY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToArea_AREA = make_shared<EventScriptCommand>("playerWalkToArea_AREA", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToDoor_DOOR = make_shared<EventScriptCommand>("playerWalkToDoor_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToEntity_ENTITY = make_shared<EventScriptCommand>("playerWalkToEntity_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("playerWalkToTileXY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::playerBlockUntilReachesArea_AREA = make_shared<EventScriptCommand>("playerBlockUntilReachesArea_AREA", "");
const shared_ptr<EventScriptCommand> EventData::playerBlockUntilReachesDoor_DOOR = make_shared<EventScriptCommand>("playerBlockUntilReachesDoor_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::playerBlockUntilReachesEntity_ENTITY = make_shared<EventScriptCommand>("playerBlockUntilReachesEntity_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("playerBlockUntilReachesTileXY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToAreaAndBlockUntilThere_AREA = make_shared<EventScriptCommand>("playerWalkToAreaAndBlockUntilThere_AREA", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToEntityAndBlockUntilThere_ENTITY = make_shared<EventScriptCommand>("playerWalkToEntityAndBlockUntilThere_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToDoorAndBlockUntilThere_DOOR = make_shared<EventScriptCommand>("playerWalkToDoorAndBlockUntilThere_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("playerWalkToTileXYAndBlockUntilThere_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::playerStandAndShuffle = make_shared<EventScriptCommand>("playerStandAndShuffle", "");
const shared_ptr<EventScriptCommand> EventData::playerStandAndShuffleAndFaceEntity_ENTITY = make_shared<EventScriptCommand>("playerStandAndShuffleAndFaceEntity_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame = make_shared<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame", "");
const shared_ptr<EventScriptCommand> EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame = make_shared<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame", "");
const shared_ptr<EventScriptCommand> EventData::playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerDoAnimationByNameOnce_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("playerDoAnimationByNameLoop_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::playerStopAnimating = make_shared<EventScriptCommand>("playerStopAnimating", "");
const shared_ptr<EventScriptCommand> EventData::playerSetGlobalAnimationDisabled_BOOL = make_shared<EventScriptCommand>("playerSetGlobalAnimationDisabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::playerSetMovementSpeed_INTticksPerPixel = make_shared<EventScriptCommand>("playerSetMovementSpeed_INTticksPerPixel", "");
const shared_ptr<EventScriptCommand> EventData::playerSetFaceMovementDirection_STRINGdirection = make_shared<EventScriptCommand>("playerSetFaceMovementDirection_STRINGdirection", "");
const shared_ptr<EventScriptCommand> EventData::playerSetToAlpha_FLOAT = make_shared<EventScriptCommand>("playerSetToAlpha_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::e024 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::entitySetBehaviorQueueOnOff_ENTITY_BOOL = make_shared<EventScriptCommand>("entitySetBehaviorQueueOnOff_ENTITY_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::entitySetToArea_ENTITY_AREA = make_shared<EventScriptCommand>("entitySetToArea_ENTITY_AREA", "");
const shared_ptr<EventScriptCommand> EventData::entitySetToDoor_ENTITY_DOOR = make_shared<EventScriptCommand>("entitySetToDoor_ENTITY_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("entitySetToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToArea_ENTITY_AREA = make_shared<EventScriptCommand>("entityWalkToArea_ENTITY_AREA", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToDoor_ENTITY_DOOR = make_shared<EventScriptCommand>("entityWalkToDoor_ENTITY_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToEntity_ENTITY_ENTITY = make_shared<EventScriptCommand>("entityWalkToEntity_ENTITY_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("entityWalkToTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("entityMoveToArea_ENTITY_AREA_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const shared_ptr<EventScriptCommand> EventData::entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("entityMoveToDoor_ENTITY_DOOR_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const shared_ptr<EventScriptCommand> EventData::entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("entityMoveToEntity_ENTITY_ENTITY_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const shared_ptr<EventScriptCommand> EventData::entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal = make_shared<EventScriptCommand>("entityMoveToTileXY_ENTITY_INTxTile1X_INTyTile1X_BOOLwalkOrSlide_BOOLcheckHit_BOOLavoidOthers_BOOLpushOthers_BOOLpathfind_BOOLanimate_BOOLmoveDiagonal", "");
const shared_ptr<EventScriptCommand> EventData::entityBlockUntilReachesArea_ENTITY_AREA = make_shared<EventScriptCommand>("entityBlockUntilReachesArea_ENTITY_AREA", "");
const shared_ptr<EventScriptCommand> EventData::entityBlockUntilReachesDoor_ENTITY_DOOR = make_shared<EventScriptCommand>("entityBlockUntilReachesDoor_ENTITY_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::entityBlockUntilReachesEntity_ENTITY_ENTITY = make_shared<EventScriptCommand>("entityBlockUntilReachesEntity_ENTITY_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("entityBlockUntilReachesTileXY_ENTITY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToAreaAndBlockUntilThere_ENTITY_AREA = make_shared<EventScriptCommand>("entityWalkToAreaAndBlockUntilThere_ENTITY_AREA", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY = make_shared<EventScriptCommand>("entityWalkToEntityAndBlockUntilThere_ENTITY_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR = make_shared<EventScriptCommand>("entityWalkToDoorAndBlockUntilThere_ENTITY_DOOR", "");
const shared_ptr<EventScriptCommand> EventData::entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X = make_shared<EventScriptCommand>("entityWalkToTileXYAndBlockUntilThere_ENTITY_INTxTile1X_INTyTile1X", "");
const shared_ptr<EventScriptCommand> EventData::entityStandAndShuffle_ENTITY = make_shared<EventScriptCommand>("entityStandAndShuffle_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityStandAndShuffleAndFacePlayer_ENTITY = make_shared<EventScriptCommand>("entityStandAndShuffleAndFacePlayer_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY = make_shared<EventScriptCommand>("entityStandAndShuffleAndFaceEntity_ENTITY_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityAnimateOnceThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityAnimateLoopThroughCurrentAnimationFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityAnimateOnceThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityAnimateLoopThroughAllFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entitySetAnimateRandomFrames_ENTITY_INTticksPerFrame_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName = make_shared<EventScriptCommand>("entitySetAnimationByNameFirstFrame_ENTITY_STRINGanimationName", "");
const shared_ptr<EventScriptCommand> EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame = make_shared<EventScriptCommand>("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const shared_ptr<EventScriptCommand> EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame = make_shared<EventScriptCommand>("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame", "");
const shared_ptr<EventScriptCommand> EventData::entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityDoAnimationByNameOnce_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks = make_shared<EventScriptCommand>("entityDoAnimationByNameLoop_ENTITY_STRINGanimationName_INTticksPerFrame_BOOLrandomUpToTicks_INTticksBetweenLoops_BOOLrandomUpToTicks", "");
const shared_ptr<EventScriptCommand> EventData::entityStopAnimating_ENTITY = make_shared<EventScriptCommand>("entityStopAnimating_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entitySetGlobalAnimationDisabled_ENTITY_BOOL = make_shared<EventScriptCommand>("entitySetGlobalAnimationDisabled_ENTITY_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::entitySetMovementSpeed_ENTITY_INTticksPerPixel = make_shared<EventScriptCommand>("entitySetMovementSpeed_ENTITY_INTticksPerPixel", "");
const shared_ptr<EventScriptCommand> EventData::entitySetFaceMovementDirection_ENTITY_STRINGdirection = make_shared<EventScriptCommand>("entitySetFaceMovementDirection_ENTITY_STRINGdirection", "");
const shared_ptr<EventScriptCommand> EventData::entitySetNonWalkable_ENTITY_BOOL = make_shared<EventScriptCommand>("entitySetNonWalkable_ENTITY_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::entitySetPushable_ENTITY_BOOL = make_shared<EventScriptCommand>("entitySetPushable_ENTITY_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::entitySetToAlpha_ENTITY_FLOAT = make_shared<EventScriptCommand>("entitySetToAlpha_ENTITY_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::entityFadeOutDelete_ENTITY = make_shared<EventScriptCommand>("entityFadeOutDelete_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::entityDeleteInstantly_ENTITY = make_shared<EventScriptCommand>("entityDeleteInstantly_ENTITY", "");
const shared_ptr<EventScriptCommand> EventData::e016 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA = make_shared<EventScriptCommand>("spawnSpriteAsEntity_SPRITE_STRINGentityIdent_AREA", "");
const shared_ptr<EventScriptCommand> EventData::spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA = make_shared<EventScriptCommand>("spawnSpriteAsEntityFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const shared_ptr<EventScriptCommand> EventData::spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA = make_shared<EventScriptCommand>("spawnSpriteAsNPC_SPRITE_STRINGentityIdent_AREA", "");
const shared_ptr<EventScriptCommand> EventData::spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA = make_shared<EventScriptCommand>("spawnSpriteAsNPCFadeIn_SPRITE_STRINGentityIdent_AREA", "");
const shared_ptr<EventScriptCommand> EventData::e017 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = make_shared<EventScriptCommand>("createScreenSpriteUnderTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const shared_ptr<EventScriptCommand> EventData::createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy = make_shared<EventScriptCommand>("createScreenSpriteOverTextAtPercentOfScreen_SPRITE_FLOATx_FLOATy", "");
const shared_ptr<EventScriptCommand> EventData::createScreenSpriteUnderText_SPRITE_INTx_INTy = make_shared<EventScriptCommand>("createScreenSpriteUnderText_SPRITE_INTx_INTy", "");
const shared_ptr<EventScriptCommand> EventData::createScreenSpriteOverText_SPRITE_INTx_INTy = make_shared<EventScriptCommand>("createScreenSpriteOverText_SPRITE_INTx_INTy", "");
const shared_ptr<EventScriptCommand> EventData::e026 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::giveItem_ITEM = make_shared<EventScriptCommand>("giveItem_ITEM", "");
const shared_ptr<EventScriptCommand> EventData::takeItem_ITEM = make_shared<EventScriptCommand>("takeItem_ITEM", "");
const shared_ptr<EventScriptCommand> EventData::giveGame_GAME = make_shared<EventScriptCommand>("giveGame_GAME", "");
const shared_ptr<EventScriptCommand> EventData::takeMoney_FLOAT = make_shared<EventScriptCommand>("takeMoney_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::giveMoney_FLOAT = make_shared<EventScriptCommand>("giveMoney_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::e027 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::playSound_SOUND = make_shared<EventScriptCommand>("playSound_SOUND", "");
const shared_ptr<EventScriptCommand> EventData::playSound_SOUND_FLOATvol = make_shared<EventScriptCommand>("playSound_SOUND_FLOATvol", "");
const shared_ptr<EventScriptCommand> EventData::playSound_SOUND_FLOATvol_FLOATpitch_INTtimes = make_shared<EventScriptCommand>("playSound_SOUND_FLOATvol_FLOATpitch_INTtimes", "");
const shared_ptr<EventScriptCommand> EventData::playMusicOnce_MUSIC = make_shared<EventScriptCommand>("playMusicOnce_MUSIC", "");
const shared_ptr<EventScriptCommand> EventData::playMusicLoop_MUSIC = make_shared<EventScriptCommand>("playMusicLoop_MUSIC", "");
const shared_ptr<EventScriptCommand> EventData::playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop = make_shared<EventScriptCommand>("playMusic_MUSIC_FLOATvol_FLOATpitch_BOOLloop", "");
const shared_ptr<EventScriptCommand> EventData::stopAllMusic = make_shared<EventScriptCommand>("stopAllMusic", "");
const shared_ptr<EventScriptCommand> EventData::stopMusic_MUSIC = make_shared<EventScriptCommand>("stopMusic_MUSIC", "");
const shared_ptr<EventScriptCommand> EventData::fadeOutMusic_MUSIC_INT = make_shared<EventScriptCommand>("fadeOutMusic_MUSIC_INT", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC = make_shared<EventScriptCommand>("blockUntilLoopingMusicDoneWithLoopAndReplaceWith_MUSIC_MUSIC", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilMusicDone_MUSIC = make_shared<EventScriptCommand>("blockUntilMusicDone_MUSIC", "");
const shared_ptr<EventScriptCommand> EventData::fadeOutAllMusic_INT = make_shared<EventScriptCommand>("fadeOutAllMusic_INT", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilAllMusicDone = make_shared<EventScriptCommand>("blockUntilAllMusicDone", "");
const shared_ptr<EventScriptCommand> EventData::e028 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake = make_shared<EventScriptCommand>("shakeScreen_INTticks_INTxpixels_INTypixels_INTticksPerShake", "");
const shared_ptr<EventScriptCommand> EventData::fadeToBlack_INTticks = make_shared<EventScriptCommand>("fadeToBlack_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::fadeFromBlack_INTticks = make_shared<EventScriptCommand>("fadeFromBlack_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::fadeToWhite_INTticks = make_shared<EventScriptCommand>("fadeToWhite_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::fadeFromWhite_INTticks = make_shared<EventScriptCommand>("fadeFromWhite_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::e029 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha = make_shared<EventScriptCommand>("fadeColorFromCurrentAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const shared_ptr<EventScriptCommand> EventData::fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha = make_shared<EventScriptCommand>("fadeColorFromAlphaToAlpha_INTticks_INTr_INTg_INTb_FLOATfromAlpha_FLOATtoAlpha", "");
const shared_ptr<EventScriptCommand> EventData::fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha = make_shared<EventScriptCommand>("fadeColorFromTransparentToAlphaBackToTransparent_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const shared_ptr<EventScriptCommand> EventData::setInstantOverlay_INTr_INTg_INTb_FLOATa = make_shared<EventScriptCommand>("setInstantOverlay_INTr_INTg_INTb_FLOATa", "");
const shared_ptr<EventScriptCommand> EventData::clearOverlay = make_shared<EventScriptCommand>("clearOverlay", "");
const shared_ptr<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha = make_shared<EventScriptCommand>("fadeColorFromCurrentAlphaToAlphaUnderLights_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const shared_ptr<EventScriptCommand> EventData::setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa = make_shared<EventScriptCommand>("setInstantOverlayUnderLights_INTr_INTg_INTb_FLOATa", "");
const shared_ptr<EventScriptCommand> EventData::clearOverlayUnderLights = make_shared<EventScriptCommand>("clearOverlayUnderLights", "");
const shared_ptr<EventScriptCommand> EventData::fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha = make_shared<EventScriptCommand>("fadeColorFromCurrentAlphaToAlphaGroundLayer_INTticks_INTr_INTg_INTb_FLOATtoAlpha", "");
const shared_ptr<EventScriptCommand> EventData::setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa = make_shared<EventScriptCommand>("setInstantOverlayGroundLayer_INTr_INTg_INTb_FLOATa", "");
const shared_ptr<EventScriptCommand> EventData::clearOverlayGroundLayer = make_shared<EventScriptCommand>("clearOverlayGroundLayer", "");
const shared_ptr<EventScriptCommand> EventData::e030 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setLetterbox_BOOL = make_shared<EventScriptCommand>("setLetterbox_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks = make_shared<EventScriptCommand>("setLetterbox_BOOL_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks_INTsize = make_shared<EventScriptCommand>("setLetterbox_BOOL_INTticks_INTsize", "");
const shared_ptr<EventScriptCommand> EventData::setLetterbox_BOOL_INTticks_FLOATsize = make_shared<EventScriptCommand>("setLetterbox_BOOL_INTticks_FLOATsize", "");
const shared_ptr<EventScriptCommand> EventData::setBlur_BOOL = make_shared<EventScriptCommand>("setBlur_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setMosaic_BOOL = make_shared<EventScriptCommand>("setMosaic_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setHBlankWave_BOOL = make_shared<EventScriptCommand>("setHBlankWave_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setRotate_BOOL = make_shared<EventScriptCommand>("setRotate_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setBlackAndWhite_BOOL = make_shared<EventScriptCommand>("setBlackAndWhite_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setInvertedColors_BOOL = make_shared<EventScriptCommand>("setInvertedColors_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::set8BitMode_BOOL = make_shared<EventScriptCommand>("set8BitMode_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::e031 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setEngineSpeed_FLOAT = make_shared<EventScriptCommand>("setEngineSpeed_FLOAT", "");
const shared_ptr<EventScriptCommand> EventData::e032 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::toggleLightOnOff_LIGHT = make_shared<EventScriptCommand>("toggleLightOnOff_LIGHT", "");
const shared_ptr<EventScriptCommand> EventData::setLightOnOff_LIGHT_BOOL = make_shared<EventScriptCommand>("setLightOnOff_LIGHT_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setLightFlicker_LIGHT_BOOL = make_shared<EventScriptCommand>("setLightFlicker_LIGHT_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::toggleAllLightsOnOff = make_shared<EventScriptCommand>("toggleAllLightsOnOff", "");
const shared_ptr<EventScriptCommand> EventData::setAllLightsOnOff_BOOL = make_shared<EventScriptCommand>("setAllLightsOnOff_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::e033 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setRandomSpawn_BOOL = make_shared<EventScriptCommand>("setRandomSpawn_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::deleteRandoms = make_shared<EventScriptCommand>("deleteRandoms", "");
const shared_ptr<EventScriptCommand> EventData::e034 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = make_shared<EventScriptCommand>("makeCaption_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const shared_ptr<EventScriptCommand> EventData::makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb = make_shared<EventScriptCommand>("makeCaptionOverPlayer_STRING_INTsec_INTr_INTg_INTb", "");
const shared_ptr<EventScriptCommand> EventData::makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb = make_shared<EventScriptCommand>("makeCaptionOverEntity_ENTITY_STRING_INTsec_INTr_INTg_INTb", "");
const shared_ptr<EventScriptCommand> EventData::makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb = make_shared<EventScriptCommand>("makeNotification_STRING_INTsec_INTx_INTy_INTr_INTg_INTb", "");
const shared_ptr<EventScriptCommand> EventData::setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks = make_shared<EventScriptCommand>("setShowConsoleMessage_GAMESTRING_INTr_INTg_INT_b_INTticks", "");
const shared_ptr<EventScriptCommand> EventData::e035 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setShowClockCaption_BOOL = make_shared<EventScriptCommand>("setShowClockCaption_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowDayCaption_BOOL = make_shared<EventScriptCommand>("setShowDayCaption_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowMoneyCaption_BOOL = make_shared<EventScriptCommand>("setShowMoneyCaption_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowAllStatusBarCaptions_BOOL = make_shared<EventScriptCommand>("setShowAllStatusBarCaptions_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowStatusBar_BOOL = make_shared<EventScriptCommand>("setShowStatusBar_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowNDButton_BOOL = make_shared<EventScriptCommand>("setShowNDButton_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowGameStoreButton_BOOL = make_shared<EventScriptCommand>("setShowGameStoreButton_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowStuffButton_BOOL = make_shared<EventScriptCommand>("setShowStuffButton_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setShowAllButtons_BOOL = make_shared<EventScriptCommand>("setShowAllButtons_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setNDEnabled_BOOL = make_shared<EventScriptCommand>("setNDEnabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setGameStoreMenuEnabled_BOOL = make_shared<EventScriptCommand>("setGameStoreMenuEnabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setStuffMenuEnabled_BOOL = make_shared<EventScriptCommand>("setStuffMenuEnabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setAllMenusAndNDEnabled_BOOL = make_shared<EventScriptCommand>("setAllMenusAndNDEnabled_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::e046 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setClockUnknown = make_shared<EventScriptCommand>("setClockUnknown", "");
const shared_ptr<EventScriptCommand> EventData::setClockNormal = make_shared<EventScriptCommand>("setClockNormal", "");
const shared_ptr<EventScriptCommand> EventData::setTimePaused_BOOL = make_shared<EventScriptCommand>("setTimePaused_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::setTimeFastForward = make_shared<EventScriptCommand>("setTimeFastForward", "");
const shared_ptr<EventScriptCommand> EventData::setTimeNormalSpeed = make_shared<EventScriptCommand>("setTimeNormalSpeed", "");
const shared_ptr<EventScriptCommand> EventData::e037 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::setNDOpen_BOOL = make_shared<EventScriptCommand>("setNDOpen_BOOL", "");
const shared_ptr<EventScriptCommand> EventData::startGame = make_shared<EventScriptCommand>("startGame", "");
const shared_ptr<EventScriptCommand> EventData::startBobsGameOnStadiumScreen_AREA = make_shared<EventScriptCommand>("startBobsGameOnStadiumScreen_AREA", "");
const shared_ptr<EventScriptCommand> EventData::blockUntilBobsGameDead = make_shared<EventScriptCommand>("blockUntilBobsGameDead", "");
const shared_ptr<EventScriptCommand> EventData::showLoginScreen = make_shared<EventScriptCommand>("showLoginScreen", "");
const shared_ptr<EventScriptCommand> EventData::e038 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::closeAllMenusAndND = make_shared<EventScriptCommand>("closeAllMenusAndND", "");
const shared_ptr<EventScriptCommand> EventData::e039 = make_shared<EventScriptCommand>();
const shared_ptr<EventScriptCommand> EventData::openStuffMenu = make_shared<EventScriptCommand>("openStuffMenu", "");
const shared_ptr<EventScriptCommand> EventData::openItemsMenu = make_shared<EventScriptCommand>("openItemsMenu", "");
const shared_ptr<EventScriptCommand> EventData::openLogMenu = make_shared<EventScriptCommand>("openLogMenu", "");
const shared_ptr<EventScriptCommand> EventData::openStatusMenu = make_shared<EventScriptCommand>("openStatusMenu", "");
const shared_ptr<EventScriptCommand> EventData::openFriendsMenu = make_shared<EventScriptCommand>("openFriendsMenu", "");
const shared_ptr<EventScriptCommand> EventData::openSettingsMenu = make_shared<EventScriptCommand>("openSettingsMenu", "");
const shared_ptr<EventScriptCommand> EventData::openGameStoreMenu = make_shared<EventScriptCommand>("openGameStoreMenu", "");

