//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "../network/BobNet.h"


class FriendManager : public EnginePart
{
public:

	static Logger log;



	//ArrayList because threads will access it
	ArrayList<shared_ptr<FriendCharacter>>* friendCharacters = make_shared<ArrayList><shared_ptr<FriendCharacter>>();



	FriendManager(shared_ptr<BGClientEngine> g);


	void init();


	void cleanup();


	//this should keep a list of all the friends online
	//each friend is a unique UDP client connection with a unique designated UDP port.
	//go through the list and update those.


	void update();




	//The following method was originally marked 'synchronized':
	//void addNewOnlineFriendIfNotExist(int userID, int peerType);
};

