//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"

#include <src/Utility/Logger.h>
#include "src/Puzzle/Room.h"

//===============================================================================================
//game stats logs stats for every single game that every user plays
class BobsGameGameStats
{//===============================================================================================

public:
	Logger log = Logger("BobsGameGameStats");

	string userName = "";
	long long userID = 0;

	string isGameTypeOrSequence = "";

	string gameTypeName = "";
	string gameTypeUUID = "";
	string gameSequenceName = "";
	string gameSequenceUUID = "";
	string difficultyName = "";

	string gameTypeEndedOnName = "";
	string gameTypeEndedOnUUID = "";
	

	int won = 0;
	int died = 0;
	int lost = 0;
	int complete = 0;
	int isLocalMultiplayer = 0;
	int isNetworkMultiplayer = 0;
	int numPlayers = 1;

	int level = 0;
	long long timeLasted = 0;
	long long timeStarted = 0;
	long long timeEnded = 0;
	int blocksMade = 0;
	int piecesMade = 0;
	int blocksCleared = 0;
	int piecesPlaced = 0;
	int combosMade = 0;
	int biggestCombo = 0;

	string allFrameStatesZipped = "";
	string playerIDsCSV = "";//id:`userName`:lost,id:`userName`:won,:

	string statsUUID = "";

	Room* room = nullptr;

	//game type or sequence,
	//sequence options
	//sequence uuid or gametype uuid
	//time started, time finished, time lasted
	//blocks made, pieces made, blocks cleared
	//was multiplayer,
	//number of players
	//multiplayer options,
	//whether won / lost
	//send replay packet as well

	//===============================================================================================
	BobsGameGameStats()
	{//===============================================================================================
		boost::uuids::random_generator generator;
		statsUUID = to_string(generator());
	}

	//===============================================================================================
	string encode()
	{//===============================================================================================
		string s = "";

		s += "`" + userName + "`" + ","
			+ to_string(userID) + ","
			+ isGameTypeOrSequence + ","
			+ "`" + gameTypeName + "`" + ","
			+ gameTypeUUID + ","
			+ "`" + gameSequenceName + "`" + ","
			+ gameSequenceUUID + ","
			+ difficultyName + ","

			+"`" + gameTypeEndedOnName + "`" + ","
			+ gameTypeEndedOnUUID + ","
			
			+ to_string(won) + ","
			+ to_string(died) + ","
			+ to_string(lost) + ","
			+ to_string(complete) + ","
			+ to_string(isLocalMultiplayer) + ","
			+ to_string(isNetworkMultiplayer) + ","
			+ to_string(numPlayers) + ","
			+ to_string(level) + ","
			+ to_string(timeLasted) + ","
			+ to_string(timeStarted) + ","
			+ to_string(timeEnded) + ","
			+ to_string(blocksMade) + ","
			+ to_string(piecesMade) + ","
			+ to_string(blocksCleared) + ","
			+ to_string(piecesPlaced) + ","
			+ to_string(combosMade) + ","
			+ to_string(biggestCombo) + ","


			+allFrameStatesZipped + ","
			+ statsUUID + ","
			+ playerIDsCSV + ":"
			+ room->encodeRoomData(false) + ":";

		return s;
	}



};