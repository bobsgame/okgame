//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include <string>
#include "oktypes.h"
#include <src/Engine/network/UDPPeerConnection.h>
#include "GameSequence.h"




enum class SendGarbageToRule
{
	
	SEND_GARBAGE_TO_ALL_PLAYERS,
	SEND_GARBAGE_TO_ALL_PLAYERS_50_PERCENT_CHANCE,
	SEND_GARBAGE_TO_RANDOM_PLAYER,
	SEND_GARBAGE_TO_EACH_PLAYER_IN_ROTATION,
	SEND_GARBAGE_TO_PLAYER_WITH_LEAST_BLOCKS,
	LAST,//last marker of enum to do loop

};



//=========================================================================================================================
class Room
{//=========================================================================================================================
public:

	

	
	

	string uuid = "";

	//this is only used for sending rooms to other clients and when sending stats to the server
	//it is the host's game type, but is ignored if allow different gametypes is true
	string room_IsGameSequenceOrType = "";
	string room_GameTypeName = "";
	string room_GameSequenceName = "";
	string room_GameTypeUUID = "";
	string room_GameSequenceUUID = "";

	//this is used if allow different difficulties is false, otherwise it is the host's selected difficulty
	string room_DifficultyName = "Beginner";

	//this is only used for sending stats to the server and for saving and loading game configurations
	//on load config this should set randomizeSequence in currentRoom->currentSequence
	//because either multiplayer allows multiple sequences in which case each player can determine this
	//or it sends the serialized gameSequence with randomizeSequence set
	bool singleplayer_RandomizeSequence = true;


	int multiplayer_NumPlayers = 0;
	long long multiplayer_HostUserID = 0;

	//these are set in the multiplayer setup screen
	int multiplayer_MaxPlayers = 0;
	bool multiplayer_PrivateRoom = false;
	bool multiplayer_TournamentRoom = false;
	bool multiplayer_AllowDifferentDifficulties = true;
	bool multiplayer_AllowDifferentGameSequences = true;



	//these are set in the roomOptions screen for both single and multiplayer
	bool	endlessMode = false;
	bool	multiplayer_GameEndsWhenOnePlayerRemains = true;
	bool	multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	bool	multiplayer_DisableVSGarbage = false;

	float	gameSpeedStart = 0.01f;
	float	gameSpeedChangeRate = 0.02f;
	float	gameSpeedMaximum = 1.0f;//can be 0.1 to 10.0 although that won't make sense
	float	levelUpMultiplier = 1.0f;//can be negative
	float	levelUpCompoundMultiplier = 1.0f;//can be negative

	bool	multiplayer_AllowNewPlayersDuringGame = false;//TODO:
	bool	multiplayer_UseTeams = false;//TODO:

	float	multiplayer_GarbageMultiplier = 1.0f;
	int		multiplayer_GarbageLimit = 0;
	bool	multiplayer_GarbageScaleByDifficulty = true;//scale garbage by difficulty, beginner->insane 2x, insane->beginner 0.5x, etc.
	int		multiplayer_SendGarbageTo = (int)SendGarbageToRule::SEND_GARBAGE_TO_ALL_PLAYERS;

	int		floorSpinLimit = -1;
	int		totalYLockDelayLimit = -1;
	float	lockDelayDecreaseRate = 0;
	int		lockDelayMinimum = 0;

	int		stackWaitLimit = -1;
	int		spawnDelayLimit = -1;
	float	spawnDelayDecreaseRate = 0;
	int		spawnDelayMinimum = 0;
	int		dropDelayMinimum = 0;

	//=========================================================================================================================
	void setDefaults()
	{//=========================================================================================================================


		Room r;

		this->multiplayer_GameEndsWhenOnePlayerRemains = r.multiplayer_GameEndsWhenOnePlayerRemains;
		this->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = r.multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel;
		this->multiplayer_DisableVSGarbage = r.multiplayer_DisableVSGarbage;


		this->gameSpeedStart = r.gameSpeedStart;
		this->gameSpeedChangeRate = r.gameSpeedChangeRate;
		this->gameSpeedMaximum = r.gameSpeedMaximum;
		this->levelUpMultiplier = r.levelUpMultiplier;
		this->levelUpCompoundMultiplier = r.levelUpCompoundMultiplier;
		this->multiplayer_AllowNewPlayersDuringGame = r.multiplayer_AllowNewPlayersDuringGame;
		this->multiplayer_UseTeams = r.multiplayer_UseTeams;
		this->multiplayer_GarbageMultiplier = r.multiplayer_GarbageMultiplier;
		this->multiplayer_GarbageLimit = r.multiplayer_GarbageLimit;
		this->multiplayer_GarbageScaleByDifficulty = r.multiplayer_GarbageScaleByDifficulty;
		this->multiplayer_SendGarbageTo = r.multiplayer_SendGarbageTo;
		this->floorSpinLimit = r.floorSpinLimit;
		this->totalYLockDelayLimit = r.totalYLockDelayLimit;
		this->lockDelayDecreaseRate = r.lockDelayDecreaseRate;
		this->lockDelayMinimum = r.lockDelayMinimum;
		this->stackWaitLimit = r.stackWaitLimit;
		this->spawnDelayLimit = r.spawnDelayLimit;
		this->spawnDelayDecreaseRate = r.spawnDelayDecreaseRate;
		this->spawnDelayMinimum = r.spawnDelayMinimum;
		this->dropDelayMinimum = r.dropDelayMinimum;
	}

	//=========================================================================================================================
	bool isDefaultSettings()
	{//=========================================================================================================================

		Room r;

		if(this->gameSpeedStart != r.gameSpeedStart)return false;
		if(this->gameSpeedChangeRate != r.gameSpeedChangeRate)return false;
		if(this->gameSpeedMaximum != r.gameSpeedMaximum)return false;
		if(this->levelUpMultiplier != r.levelUpMultiplier)return false;
		if(this->levelUpCompoundMultiplier != r.levelUpCompoundMultiplier)return false;
		if(this->multiplayer_AllowNewPlayersDuringGame != r.multiplayer_AllowNewPlayersDuringGame)return false;
		if(this->multiplayer_UseTeams != r.multiplayer_UseTeams)return false;
		if(this->multiplayer_GarbageMultiplier != r.multiplayer_GarbageMultiplier)return false;
		if(this->multiplayer_GarbageLimit != r.multiplayer_GarbageLimit)return false;
		if(this->multiplayer_GarbageScaleByDifficulty != r.multiplayer_GarbageScaleByDifficulty)return false;
		if(this->multiplayer_SendGarbageTo != r.multiplayer_SendGarbageTo)return false;
		if(this->floorSpinLimit != r.floorSpinLimit)return false;
		if(this->totalYLockDelayLimit != r.totalYLockDelayLimit)return false;
		if(this->lockDelayDecreaseRate != r.lockDelayDecreaseRate)return false;
		if(this->lockDelayMinimum != r.lockDelayMinimum)return false;
		if(this->stackWaitLimit != r.stackWaitLimit)return false;
		if(this->spawnDelayLimit != r.spawnDelayLimit)return false;
		if(this->spawnDelayDecreaseRate != r.spawnDelayDecreaseRate)return false;
		if(this->spawnDelayMinimum != r.spawnDelayMinimum)return false;
		if(this->dropDelayMinimum != r.dropDelayMinimum)return false;

		return true;
	}


	//don't export
	shared_ptr<GameSequence>gameSequence = nullptr;
	shared_ptr<UDPPeerConnection>hostPeer = nullptr;

	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================
		ar & BOOST_SERIALIZATION_NVP(uuid);
		ar & BOOST_SERIALIZATION_NVP(room_IsGameSequenceOrType);
		ar & BOOST_SERIALIZATION_NVP(room_GameTypeName);
		ar & BOOST_SERIALIZATION_NVP(room_GameTypeUUID);
		ar & BOOST_SERIALIZATION_NVP(room_GameSequenceName);
		ar & BOOST_SERIALIZATION_NVP(room_GameSequenceUUID);
		ar & BOOST_SERIALIZATION_NVP(room_DifficultyName);
		ar & BOOST_SERIALIZATION_NVP(singleplayer_RandomizeSequence);
		ar & BOOST_SERIALIZATION_NVP(endlessMode);



		
		ar & BOOST_SERIALIZATION_NVP(multiplayer_NumPlayers);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_HostUserID);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_MaxPlayers);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_PrivateRoom);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_TournamentRoom);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_AllowDifferentDifficulties);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_AllowDifferentGameSequences);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_GameEndsWhenOnePlayerRemains);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_DisableVSGarbage);



		ar & BOOST_SERIALIZATION_NVP(gameSpeedStart);
		ar & BOOST_SERIALIZATION_NVP(gameSpeedChangeRate);
		ar & BOOST_SERIALIZATION_NVP(gameSpeedMaximum);
		ar & BOOST_SERIALIZATION_NVP(levelUpMultiplier);
		ar & BOOST_SERIALIZATION_NVP(levelUpCompoundMultiplier);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_AllowNewPlayersDuringGame);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_UseTeams);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_GarbageMultiplier);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_GarbageLimit);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_GarbageScaleByDifficulty);
		ar & BOOST_SERIALIZATION_NVP(multiplayer_SendGarbageTo);
		ar & BOOST_SERIALIZATION_NVP(floorSpinLimit);
		ar & BOOST_SERIALIZATION_NVP(totalYLockDelayLimit);
		ar & BOOST_SERIALIZATION_NVP(lockDelayDecreaseRate);
		ar & BOOST_SERIALIZATION_NVP(lockDelayMinimum);
		ar & BOOST_SERIALIZATION_NVP(stackWaitLimit);

		ar & BOOST_SERIALIZATION_NVP(spawnDelayLimit);
		ar & BOOST_SERIALIZATION_NVP(spawnDelayDecreaseRate);
		ar & BOOST_SERIALIZATION_NVP(spawnDelayMinimum);

		ar & BOOST_SERIALIZATION_NVP(dropDelayMinimum);

	}



	//=========================================================================================================================
	Room()
	{//=========================================================================================================================
		boost::uuids::random_generator generator;
		uuid = to_string(generator());
	}
	//=========================================================================================================================
	string getRoomDescription()
	{//=========================================================================================================================
		string visibility = "Public";
		if (multiplayer_PrivateRoom)visibility = "Private";

		string scoreMode = "Free Play";
		if (multiplayer_TournamentRoom)scoreMode = "Tournament";

		string game = "Any Game";

		if (multiplayer_AllowDifferentGameSequences == false && gameSequence != nullptr)
			game = gameSequence->name;

		string difficulty = "Any Difficulty";
		if (multiplayer_AllowDifferentDifficulties == false)
			difficulty = room_DifficultyName;

		string garbage = "";
		if (multiplayer_DisableVSGarbage)
			garbage = "No Garbage";

		string endWhenLose = "Ends When All Lost";
		if (multiplayer_GameEndsWhenOnePlayerRemains)endWhenLose = "End On 1 Player Left";

		string endOnCredits = "Free Play To Completion";
		if (endlessMode)endOnCredits = "Endless Mode";
		else
		if (multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel)endOnCredits = "End On First Completion";

		string roomDescription = game;
		if (visibility != "")roomDescription += " | " + visibility;
		if (scoreMode != "")roomDescription += " | " + scoreMode;
		if (difficulty != "")roomDescription += " | " + difficulty;
		//if (garbage != "")roomDescription += " | " + garbage;
		//if (endWhenLose != "")roomDescription += " | " + endWhenLose;
		//if (endOnCredits != "")roomDescription += " | " + endOnCredits;

		string playersString = to_string(multiplayer_NumPlayers);
		if (multiplayer_MaxPlayers > 1)playersString += "/" + to_string(multiplayer_MaxPlayers) + " players";
		else playersString += " players";

		roomDescription += " | " + playersString;
		return roomDescription;
	}



	//=========================================================================================================================
	string encodeRoomData(bool includeXMLGameSequence)
	{//=========================================================================================================================

	 //hostUserID,roomUUID,`gameSequenceOrTypeName`,isGameSequenceOrType,gameSequenceOrTypeUUID,usersInRoom,maxUsers,private,tournament,multiplayerOptions,
		string s =
			to_string(multiplayer_HostUserID) +
			"," + uuid;




		if (gameSequence->gameTypes.size() == 1)
		{
			room_IsGameSequenceOrType = "GameType";
			room_GameTypeName = gameSequence->gameTypes.get(0)->name;
			room_GameTypeUUID = gameSequence->gameTypes.get(0)->uuid;
		}
		else
		{
			room_IsGameSequenceOrType = "GameSequence";
			room_GameSequenceName = gameSequence->name;
			room_GameSequenceUUID = gameSequence->uuid;
		}

		s += "," + room_IsGameSequenceOrType;
		s += ",`" + room_GameTypeName + "`";
		s += "," + room_GameTypeUUID;
		s += ",`" + room_GameSequenceName + "`";
		s += "," + room_GameSequenceUUID;
		s += "," + room_DifficultyName;

		s +=

			"," + to_string(multiplayer_NumPlayers) +
			"," + to_string(multiplayer_MaxPlayers) +
			"," + to_string((int)multiplayer_PrivateRoom) +
			"," + to_string((int)multiplayer_TournamentRoom) +
			"," + to_string((int)endlessMode) +
			"," + to_string((int)multiplayer_AllowDifferentDifficulties) +
			"," + to_string((int)multiplayer_AllowDifferentGameSequences) +
			"," + to_string((int)multiplayer_GameEndsWhenOnePlayerRemains) +
			"," + to_string((int)multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel) +
			"," + to_string((int)multiplayer_DisableVSGarbage) +


			"," + to_string(gameSpeedStart) +
			"," + to_string(gameSpeedChangeRate) +
			"," + to_string(gameSpeedMaximum) +
			"," + to_string(levelUpMultiplier) +
			"," + to_string(levelUpCompoundMultiplier) +
			"," + to_string((int)multiplayer_AllowNewPlayersDuringGame) +
			"," + to_string((int)multiplayer_UseTeams) +
			"," + to_string(multiplayer_GarbageMultiplier) +
			"," + to_string(multiplayer_GarbageLimit) +
			"," + to_string((int)multiplayer_GarbageScaleByDifficulty) +
			"," + to_string(multiplayer_SendGarbageTo) +
			"," + to_string(floorSpinLimit) +
			"," + to_string(totalYLockDelayLimit) +
			"," + to_string(lockDelayDecreaseRate) +
			"," + to_string(lockDelayMinimum) +
			"," + to_string(stackWaitLimit) +

			"," + to_string(spawnDelayLimit) +
			"," + to_string(spawnDelayDecreaseRate) +
			"," + to_string(spawnDelayMinimum) +
			"," + to_string(dropDelayMinimum) +
			",";

		if (includeXMLGameSequence)
		{
			if (gameSequence != nullptr)
			{
				NetworkGameSequence ngs = NetworkGameSequence(*(gameSequence));
				s += ":" + ngs.toBase64GZippedXML();
			}
		}
		return s;
	}


	//=========================================================================================================================
	static shared_ptr<Room> decodeRoomData(string s, bool decodeGameSequenceXML)
	{//=========================================================================================================================
		shared_ptr<Room>newRoom = make_shared<Room>();
		newRoom->decode(s, decodeGameSequenceXML);
		return newRoom;
	}

	//=========================================================================================================================
	void decode(string s, bool decodeGameSequenceXML)
	{//=========================================================================================================================



		string hostUserIDString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string roomUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		int hostUserID = -1;
		try
		{
			hostUserID = stoi(hostUserIDString);
		}
		catch (exception)
		{
			OKGame::log.error("hostUserID could not be parsed");
			
		}
		multiplayer_HostUserID = hostUserID;

		uuid = roomUUID;

		


		room_IsGameSequenceOrType = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		s = s.substr(s.find("`") + 1);
		room_GameTypeName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);

		room_GameTypeUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		s = s.substr(s.find("`") + 1);
		room_GameSequenceName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);

		room_GameSequenceUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		room_DifficultyName = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);



		string playersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string maxPlayersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string privateRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string tournamentRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);		



		string endlessModeString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		string multiplayer_AllowDifferentDifficultiesString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowDifferentGameSequencesString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenAllOpponentsLoseString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_DisableVSGarbageString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);


		string gameSpeedStartString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string gameSpeedIncreaseRateString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string gameSpeedMaximumString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string levelUpMultiplierString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string levelUpCompoundMultiplierString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_AllowNewPlayersDuringGameString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_UseTeamsString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GarbageMultiplierString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GarbageLimitString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_GarbageScaleByDifficultyString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_SendGarbageToString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_FloorSpinLimitString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_LockDelayLimitString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_LockDelayDecreaseMultiplierString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_LockDelayMinimumString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_StackWaitLimitString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);


		string multiplayer_SpawnDelayLimitString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_SpawnDelayDecreaseRateString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string multiplayer_SpawnDelayMinimumString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);

		string multiplayer_DropDelayMinimumString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);



		string multiplayer_ZippedGameSequenceString = "";
		if (decodeGameSequenceXML)
		{
			s = s.substr(s.find(":") + 1);
			multiplayer_ZippedGameSequenceString = s.substr(0, s.find(":"));
			if (multiplayer_ZippedGameSequenceString.length() < 10)multiplayer_ZippedGameSequenceString = "";
		}

		






		int numPlayers = -1;
		try
		{
			numPlayers = stoi(playersString);
		}
		catch (exception)
		{
			OKGame::log.error("numPlayers could not be parsed");
			
		}
		multiplayer_NumPlayers = numPlayers;

		try
		{
			multiplayer_MaxPlayers = stoi(maxPlayersString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse maxPlayers");
			
		}

		try
		{
			multiplayer_PrivateRoom = 0 != stoi(privateRoomString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse privateRoom");
			
		}

		try
		{
			multiplayer_TournamentRoom = 0 != stoi(tournamentRoomString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse tournamentRoom");
			
		}



		try
		{
			endlessMode = 0 != stoi(endlessModeString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse endlessMode");
			
		}

		try
		{
			multiplayer_AllowDifferentDifficulties = 0 != stoi(multiplayer_AllowDifferentDifficultiesString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse multiplayer_AllowDifferentDifficulties");
			
		}

		try
		{
			multiplayer_AllowDifferentGameSequences = 0 != stoi(multiplayer_AllowDifferentGameSequencesString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse multiplayer_AllowDifferentGameSequences");
			
		}

		try
		{
			multiplayer_GameEndsWhenOnePlayerRemains = 0 != stoi(multiplayer_GameEndsWhenAllOpponentsLoseString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse multiplayer_GameEndsWhenAllOpponentsLose");
			
		}

		try
		{
			multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = 0 != stoi(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel");
			
		}

		try
		{
			multiplayer_DisableVSGarbage = 0 != stoi(multiplayer_DisableVSGarbageString);
		}
		catch (exception)
		{
			OKGame::log.error("Could not parse multiplayer_DisableVSGarbage");
			
		}




		try
		{

			gameSpeedStart							 = stof(gameSpeedStartString);
			gameSpeedChangeRate					 = stof(gameSpeedIncreaseRateString);
			gameSpeedMaximum						 = stof(gameSpeedMaximumString);
			levelUpMultiplier						 = stof(levelUpMultiplierString);
			levelUpCompoundMultiplier				 = stof(levelUpCompoundMultiplierString);
			multiplayer_AllowNewPlayersDuringGame	 = 0 != stoi(multiplayer_AllowNewPlayersDuringGameString);
			multiplayer_UseTeams					 = 0 != stoi(multiplayer_UseTeamsString);
			multiplayer_GarbageMultiplier			 = stof(multiplayer_GarbageMultiplierString);
			multiplayer_GarbageLimit				 = stoi(multiplayer_GarbageLimitString);
			multiplayer_GarbageScaleByDifficulty	 = 0 != stoi(multiplayer_GarbageScaleByDifficultyString);
			multiplayer_SendGarbageTo				 = stoi(multiplayer_SendGarbageToString);
			floorSpinLimit				 = stoi(multiplayer_FloorSpinLimitString);
			totalYLockDelayLimit		 = stoi(multiplayer_LockDelayLimitString);
			lockDelayDecreaseRate		 = stof(multiplayer_LockDelayDecreaseMultiplierString);
			lockDelayMinimum			 = stoi(multiplayer_LockDelayMinimumString);
			stackWaitLimit				 = stoi(multiplayer_StackWaitLimitString);

			spawnDelayLimit			 = stoi(multiplayer_SpawnDelayLimitString);
			spawnDelayDecreaseRate		 = stof(multiplayer_SpawnDelayDecreaseRateString);
			spawnDelayMinimum			 = stoi(multiplayer_SpawnDelayMinimumString);
			dropDelayMinimum			 = stoi(multiplayer_DropDelayMinimumString);



		}
		catch (exception)
		{
			OKGame::log.error("Could not parse room options");
			
		}


		if (decodeGameSequenceXML)
		{
			if (multiplayer_ZippedGameSequenceString.length() > 0)
			{
				shared_ptr<NetworkGameSequence>gs = NetworkGameSequence::fromBase64GZippedXML(multiplayer_ZippedGameSequenceString);

				if (gs == nullptr)
				{
					OKGame::log.error("Could not parse received GameSequence");
				}

				OKGame::saveUnknownGameSequencesAndTypesToXML(gs);

				gameSequence = gs;
				if (gs->gameTypes.size() == 1)
				{
					room_IsGameSequenceOrType = "GameType";
					room_GameTypeName = gs->gameTypes.get(0)->name;
					room_GameTypeUUID = gs->gameTypes.get(0)->uuid;
				}
				else
				{
					room_IsGameSequenceOrType = "GameSequence";
					room_GameSequenceName = gs->name;
					room_GameSequenceUUID = gs->uuid;
				}
			}
			else
			{
				gameSequence = nullptr;
			}
		}

	}

//
//	//=========================================================================================================================
//	string serializeRoomData(bool includeXMLGameSequence)
//	{//=========================================================================================================================
//
//	 //hostUserID,roomUUID,`gameSequenceOrTypeName`,isGameSequenceOrType,gameSequenceOrTypeUUID,usersInRoom,maxUsers,private,tournament,multiplayerOptions,
//		
//
//		std::stringstream ss;
//		boost::archive::xml_oarchive oarchive(ss);
//
//		Room r;
//		r = *this;
//		oarchive << BOOST_SERIALIZATION_NVP(r);
//
//
//		string s = FileUtils::lz4StringToBase64String(ss.str());
//
//		if (includeXMLGameSequence)
//		{
//			if (gameSequence != nullptr)
//			{
//				NetworkGameSequence ngs = NetworkGameSequence(*(gameSequence));
//				s += ":" + ngs.toBase64GZippedXML();
//			}
//		}
//		return s;
//	}
//
//	//=========================================================================================================================
//	static shared_ptr<Room> deserializeRoomData(string &s, bool decodeGameSequenceXML)
//	{//=========================================================================================================================
//
//		string roomLZ4 = "";
//		string gameSequenceZip = "";
//		
//		if (s.find(":") != string::npos)
//		{
//			roomLZ4 = s.substr(0,s.find(":"));
//			gameSequenceZip = s.substr(s.find(":")+1);
//		}
//		else
//		{
//			roomLZ4 = s;
//		}
//
//
//		string roomString = FileUtils::unlz4Base64StringToString(roomLZ4);
//
//		stringstream ss;
//		ss << roomString;
//
//		boost::archive::xml_iarchive ia(ss);
//		Room rs;
//		try
//		{
//			ia >> BOOST_SERIALIZATION_NVP(rs);
//		}
//		catch (exception)
//		{
//			rs = Room();
//			OKGame::log.error("Could not unserialize Room");
//		}
//
//		shared_ptr<Room>newRoom = make_shared<Room>();
//		*newRoom = rs;
//
//
//		if (decodeGameSequenceXML)
//		{
//			if (gameSequenceZip.length() > 0)
//			{
//				shared_ptr<NetworkGameSequence>gs = NetworkGameSequence::fromBase64GZippedXML(gameSequenceZip);
//
//				if (gs == nullptr)
//				{
//					OKGame::log.error("Could not parse received GameSequence");
//					return nullptr;
//				}
//
//				OKGame::saveUnknownGameSequencesAndTypesToXML(gs);
//
//				newRoom->gameSequence = gs;
//				if (gs->gameTypes.size() == 1)
//				{
//					//newRoom->isSingleGameType = true;
//					newRoom->gameTypeUUID = gs->gameTypes.get(0)->uuid;
//				}
//				else
//				{
//					//newRoom->isGameSequence = true;
//					newRoom->gameSequenceUUID = gs->uuid;
//				}
//			}
//			else
//			{
//				newRoom->gameSequence = nullptr;
//			}
//		}
//
//		return newRoom;
//	}



};
BOOST_CLASS_VERSION(Room, 1)
BOOST_CLASS_TRACKING(Room, boost::serialization::track_never)