//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "../network/OKNet.h"


class FriendManager : public EnginePart
{
public:

	static Logger log;



	//ArrayList because threads will access it
	vector<sp<FriendCharacter>> friendCharacters;// = ms<ArrayList><sp<FriendCharacter>>();



	FriendManager(sp<BGClientEngine> g);


	void init();


	void cleanup();


	//this should keep a list of all the friends online
	//each friend is a unique UDP client connection with a unique designated UDP port.
	//go through the list and update those.


	void update();




	//The following method was originally marked 'synchronized':
	//void addNewOnlineFriendIfNotExist(int userID, int peerType);
};

