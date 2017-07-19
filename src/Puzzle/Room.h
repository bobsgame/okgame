//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include <string>
#include "bobtypes.h"
#include <src/Engine/network/UDPPeerConnection.h>
#include "GameSequence.h"
#include "BobsGame.h"







//=========================================================================================================================
class Room
{//=========================================================================================================================
public:

	

	
	

	string uuid = "";
	string gameSequenceOrTypeName = "";
	string gameSequenceUUID = "";
	string gameTypeUUID = "";
	string difficultyName = "Beginner";

	//this is only used for sending stats to the server and for saving and loading game configurations
	//on load config this should set randomizeSequence in currentRoom->currentSequence
	//because either multiplayer allows multiple sequences in which case each player can determine this
	//or it sends the serialized gameSequence with randomizeSequence set
	bool singleplayer_RandomizeSequence = true;


	bool endlessMode = false;



	
	int multiplayer_NumPlayers = 0;
	long long multiplayer_HostUserID = 0;
	int multiplayer_MaxPlayers = 0;
	bool multiplayer_PrivateRoom = false;
	bool multiplayer_TournamentRoom = false;
	bool multiplayer_AllowDifferentDifficulties = true;
	bool multiplayer_AllowDifferentGameSequences = true;
	bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	bool multiplayer_DisableVSGarbage = false;

	//don't export
	GameSequence *gameSequence = nullptr;
	UDPPeerConnection *hostPeer = nullptr;

	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================
		ar & BOOST_SERIALIZATION_NVP(uuid);
		ar & BOOST_SERIALIZATION_NVP(gameSequenceOrTypeName);
		ar & BOOST_SERIALIZATION_NVP(gameSequenceUUID);
		ar & BOOST_SERIALIZATION_NVP(gameTypeUUID);
		ar & BOOST_SERIALIZATION_NVP(difficultyName);
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
			difficulty = difficultyName;

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

		s += ",`" + gameSequence->name + "`";

		if (gameSequence->gameTypes.size() == 1)
		{
			s += ",GameType," + gameSequence->gameTypes.get(0)->uuid;
		}
		else
		{
			s += ",GameSequence," + gameSequence->uuid;
		}

		s +=

			"," + to_string(multiplayer_NumPlayers) +
			"," + to_string(multiplayer_MaxPlayers) +
			"," + to_string((int)multiplayer_PrivateRoom) +
			"," + to_string((int)multiplayer_TournamentRoom) +
			"," + difficultyName +
			"," + to_string((int)endlessMode) +
			"," + to_string((int)multiplayer_AllowDifferentDifficulties) +
			"," + to_string((int)multiplayer_AllowDifferentGameSequences) +
			"," + to_string((int)multiplayer_GameEndsWhenOnePlayerRemains) +
			"," + to_string((int)multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel) +
			"," + to_string((int)multiplayer_DisableVSGarbage) +
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
	static Room* decodeRoomData(string s, bool decodeGameSequenceXML)
	{//=========================================================================================================================

		string hostUserIDString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string roomUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		s = s.substr(s.find("`") + 1);
		string gameSequenceOrTypeName = s.substr(0, s.find("`"));
		s = s.substr(s.find("`") + 1);
		s = s.substr(s.find(",") + 1);
		string isGameSequenceOrType = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string gameSequenceOrTypeUUID = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string playersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string maxPlayersString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string privateRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);
		string tournamentRoomString = s.substr(0, s.find(","));
		s = s.substr(s.find(",") + 1);		

		string difficultyNameString = s.substr(0, s.find(","));
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

		string multiplayer_SelectedGameSequenceString = "";
		if (decodeGameSequenceXML)
		{
			s = s.substr(s.find(":") + 1);
			multiplayer_SelectedGameSequenceString = s.substr(0, s.find(":"));
			if (multiplayer_SelectedGameSequenceString.length() < 10)multiplayer_SelectedGameSequenceString = "";
		}

		Room *newRoom = new Room();



		int hostUserID = -1;
		try
		{
			hostUserID = stoi(hostUserIDString);
		}
		catch (exception)
		{
			BobsGame::log.error("hostUserID could not be parsed");
			return nullptr;
		}
		newRoom->multiplayer_HostUserID = hostUserID;

		newRoom->uuid = roomUUID;

		newRoom->gameSequenceOrTypeName = gameSequenceOrTypeName;

		if (isGameSequenceOrType == "GameType")
		{
			//newRoom->isSingleGameType = true;
			newRoom->gameTypeUUID = gameSequenceOrTypeUUID;
		}
		else
		{
			//newRoom->isGameSequence = true;
			newRoom->gameSequenceUUID = gameSequenceOrTypeUUID;
		}

		int numPlayers = -1;
		try
		{
			numPlayers = stoi(playersString);
		}
		catch (exception)
		{
			BobsGame::log.error("numPlayers could not be parsed");
			return nullptr;
		}
		newRoom->multiplayer_NumPlayers = numPlayers;

		try
		{
			newRoom->multiplayer_MaxPlayers = stoi(maxPlayersString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse maxPlayers");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_PrivateRoom = 0 != stoi(privateRoomString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse privateRoom");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_TournamentRoom = 0 != stoi(tournamentRoomString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse tournamentRoom");
			return nullptr;
		}


		newRoom->difficultyName = difficultyNameString;

		try
		{
			newRoom->endlessMode = 0 != stoi(endlessModeString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse endlessMode");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_AllowDifferentDifficulties = 0 != stoi(multiplayer_AllowDifferentDifficultiesString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_AllowDifferentDifficulties");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_AllowDifferentGameSequences = 0 != stoi(multiplayer_AllowDifferentGameSequencesString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_AllowDifferentGameSequences");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_GameEndsWhenOnePlayerRemains = 0 != stoi(multiplayer_GameEndsWhenAllOpponentsLoseString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_GameEndsWhenAllOpponentsLose");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = 0 != stoi(multiplayer_GameEndsWhenSomeoneCompletesCreditsLevelString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel");
			return nullptr;
		}

		try
		{
			newRoom->multiplayer_DisableVSGarbage = 0 != stoi(multiplayer_DisableVSGarbageString);
		}
		catch (exception)
		{
			BobsGame::log.error("Could not parse multiplayer_DisableVSGarbage");
			return nullptr;
		}

		if (decodeGameSequenceXML)
		{
			if (multiplayer_SelectedGameSequenceString.length() > 0)
			{
				NetworkGameSequence *gs = NetworkGameSequence::fromBase64GZippedXML(multiplayer_SelectedGameSequenceString);

				if (gs == nullptr)
				{
					BobsGame::log.error("Could not parse received GameSequence");
					return nullptr;
				}

				BobsGame::saveUnknownGameSequencesAndTypesToXML(gs);

				newRoom->gameSequence = gs;
				if (gs->gameTypes.size() == 1)
				{
					//newRoom->isSingleGameType = true;
					newRoom->gameTypeUUID = gs->gameTypes.get(0)->uuid;
				}
				else
				{
					//newRoom->isGameSequence = true;
					newRoom->gameSequenceUUID = gs->uuid;
				}
			}
			else
			{
				newRoom->gameSequence = nullptr;
			}
		}

		return newRoom;
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
//	static Room* deserializeRoomData(string &s, bool decodeGameSequenceXML)
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
//			BobsGame::log.error("Could not unserialize Room");
//		}
//
//		Room *newRoom = new Room();
//		*newRoom = rs;
//
//
//		if (decodeGameSequenceXML)
//		{
//			if (gameSequenceZip.length() > 0)
//			{
//				NetworkGameSequence *gs = NetworkGameSequence::fromBase64GZippedXML(gameSequenceZip);
//
//				if (gs == nullptr)
//				{
//					BobsGame::log.error("Could not parse received GameSequence");
//					return nullptr;
//				}
//
//				BobsGame::saveUnknownGameSequencesAndTypesToXML(gs);
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