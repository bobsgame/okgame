#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger FriendCharacter::log = Logger("FriendCharacter");



FriendCharacter::FriendCharacter(shared_ptr<BGClientEngine> g)
{ //===============================================================================================


	//Character(g, make_shared<EntityData>(-1, "Camera", "Camera", 0, 0, 0, false, true, 255, 1.25f, 8, false, false, false, false, false, 0, 0, false, false, false, -1, ""));
	shared_ptr<EntityData> data = make_shared<EntityData>(-1, "Camera", "Camera", 0, 0, 0, false, true, 255, 1.25f, 8, false, false, false, false, false, 0, 0, false, false, false, nullptr, "");
	this->e = g;
	initEntity(data);
	initCharacter();

	setScale(1.25f);
	rotationAnimationSpeedTicks = 100; //80;


	if (getEventData() != nullptr)this->event = make_shared<Event>(g, getEventData(), this);
}

FriendCharacter::FriendCharacter(shared_ptr<BGClientEngine> g, int friendUserID, int friendType)
{ //===============================================================================================


	//this(g); //does NOT add to entityList
	shared_ptr<EntityData> data = make_shared<EntityData>(-1, "Camera", "Camera", 0, 0, 0, false, true, 255, 1.25f, 8, false, false, false, false, false, 0, 0, false, false, false, nullptr, "");
	this->e = g;
	initEntity(data);
	initCharacter();
	setScale(1.25f);
	rotationAnimationSpeedTicks = 100; //80;


	friendManager = g->friendManager;

//	this->userID = userID;
//	this->peerType = peerType;
//
//
//	connection = make_shared<FriendUDPConnection>(g, friendManager->getNextUDPPort(), this);


	if (getEventData() != nullptr)this->event = make_shared<Event>(g, getEventData(), this);
}

FriendCharacter::FriendCharacter(shared_ptr<BGClientEngine> g, int friendUserID, int friendType, int myUDPPort, int theirUDPPort)
{ //===============================================================================================


	//FOR DEBUG
	//FOR DEBUG
	//FOR DEBUG

	//this(g); //does NOT add to entityList
	shared_ptr<EntityData> data = make_shared<EntityData>(-1, "Camera", "Camera", 0, 0, 0, false, true, 255, 1.25f, 8, false, false, false, false, false, 0, 0, false, false, false, nullptr, "");
	this->e = g;
	initEntity(data);
	initCharacter();
	setScale(1.25f);
	rotationAnimationSpeedTicks = 100; //80;


	friendManager = g->friendManager;

//	this->userID = userID;
//	this->peerType = peerType;
//
//	connection = make_shared<FriendUDPConnection>(g, myUDPPort, this);
//	connection->setPeerIPAddress_S("127.0.0.1", theirUDPPort);

	if (getEventData() != nullptr)this->event = make_shared<Event>(g, getEventData(), this);
}

void FriendCharacter::setGameToForwardPacketsTo(shared_ptr<MiniGameEngine> game)
{ //===============================================================================================

	this->game = game;
}

bool FriendCharacter::udpPeerMessageReceived(shared_ptr<UDPPeerConnection>c, string e)// shared_ptr<ChannelHandlerContext> ctx, shared_ptr<MessageEvent> e)
{ //===============================================================================================

	//string s = e;// static_cast<string>(e->getMessage());

	if (OKString::startsWith(e, OKNet::Friend_LocationStatus_Update))
	{
		incomingFriendLocationStatusUpdate(e);
		return true;
	}

	if (OKString::startsWith(e, OKNet::Game_Challenge_Request))
	{
		incomingGameChallengeRequest(e);
		return true;
	}

	if (game != nullptr)
	{
		if (game->udpPeerMessageReceived(c, e))return true;
	}

	return false;
}

void FriendCharacter::update()
{ //===============================================================================================


	Character::update(); //Character.update() -> Entity.update()


	long long currentTime = System::currentHighResTimer();


	//see if we have a udp connection to them established
	//if (connection->established())
	{



		//generate avatar from charAppearance
		if (uniqueTexture == nullptr)
		{
			if (connection->getGotFriendData_S() == true)
			{
				string characterName = connection->getFriendData_S().characterName;
				string characterAppearance = connection->getFriendData_S().characterAppearance;
				int accountType = connection->getFriendData_S().accountRank;


				setAppearanceFromCharacterAppearanceString(characterAppearance);

				setCharacterNameAndCaption(getClientGameEngine()->getNameColor(accountType), characterName, getClientGameEngine()->getAccountRankColor(accountType), getClientGameEngine()->getAccountRankString(accountType));
			}
		}


		//send room,x,y
		//xy data, messages, minigame reqs, etc.
		long long startTime = lastSentLocationTime;
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
		if (ticksPassed > 100)
		{
			lastSentLocationTime = currentTime;

			sendFriendLocationStatusUpdate();
		}
	}

	//TODO: need function to get screen pixels based on camera zoom
	if (abs(getRoundedMiddleX() - targetX) > getEngine()->getWidth())
	{
		setX(targetX - getMiddleOffsetX());
	}
	if (abs(getRoundedMiddleY() - targetY) > getEngine()->getWidth())
	{
		setY(targetY - getMiddleOffsetY());
	}

	walkToXYNoCheckHit(targetX, targetY);

	checkIfMoved();

	doCharacterAnimation();
}


//The following method was originally marked 'synchronized':
void FriendCharacter::setMapName_S(const string& mapName)
{ //===============================================================================================
	this->mapName = mapName;
}

//The following method was originally marked 'synchronized':
void FriendCharacter::setX_S(float x)
{ //===============================================================================================
	this->setX(x);
}

//The following method was originally marked 'synchronized':
void FriendCharacter::setY_S(float y)
{ //===============================================================================================
	this->setY(y);
}
void FriendCharacter::sendFriendLocationStatusUpdate()
{ //===============================================================================================

	connection->writeReliable_S(
		OKNet::Friend_LocationStatus_Update +
		string(getMap()->getName()) + "," +
		to_string(getPlayer()->getRoundedMiddleX()) + "," +
		to_string(getPlayer()->getRoundedMiddleY()) + "," +
		to_string(OKNet::myStatus) + OKNet::endline);
}

void FriendCharacter::incomingFriendLocationStatusUpdate(string e)//shared_ptr<MessageEvent> e)
{ //===============================================================================================

	//FriendLocationUpdate:mapName,x,y,status
	
	string s = e;// ->getMessage()->toString();
	s = s.substr(s.find(":") + 1);

	string mapName = s.substr(0, s.find(","));
	s = s.substr(s.find(",") + 1);

	float mapX = -1;
	try
	{
		mapX = stof(s.substr(0, s.find(",")));
	}
	catch (exception ex)//NumberFormatException ex)
	{
		return;
	}
	s = s.substr(s.find(",") + 1);

	float mapY = -1;
	try
	{
		mapY = stof(s.substr(0, s.find(",")));
	}
	catch (exception ex)//NumberFormatException ex)
	{
		return;
	}
	s = s.substr(s.find(",") + 1);

	int status = -1;
	try
	{
		status = stoi(s);
	}
	catch (exception ex)//NumberFormatException ex)
	{
		return;
	}


	targetX = mapX;
	targetY = mapY;

	setMapName_S(mapName);
	connection->peerStatus = status;
}



//The following method was originally marked 'synchronized':
void FriendCharacter::setOutgoingGameChallengeResponse(int i)
{ //===============================================================================================

	timeOutgoingGameChallengeResponseSet = System::currentHighResTimer();

	outgoingGameChallengeResponse = i;

	if (i == NDGameEngine::gameChallengeResponse_ACCEPT)
	{
		sendGameChallengeResponse(true);
	}
	else
	{
		if (i == NDGameEngine::gameChallengeResponse_DECLINE)
		{
			sendGameChallengeResponse(false);
		}
	}
}

//The following method was originally marked 'synchronized':
int FriendCharacter::getOutgoingGameChallengeResponse()
{ //===============================================================================================


	//store last challenge time for this user
	//if challenge less than 10 seconds ago, just send last decision.


	long long startTime = timeOutgoingGameChallengeResponseSet;
	long long currentTime = System::currentHighResTimer();
	int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime));
	if (ticksPassed > 10000)
	{
		outgoingGameChallengeResponse = NDGameEngine::gameChallengeResponse_NONE;
	}

	return outgoingGameChallengeResponse;
}

void FriendCharacter::sendGameChallengeResponse(bool b)
{ //===============================================================================================

	if (b == true)
	{
		connection->writeReliable_S(OKNet::Game_Challenge_Response + "Accept" + OKNet::endline);
	}
	else
	{
		connection->writeReliable_S(OKNet::Game_Challenge_Response + "Decline" + OKNet::endline);
	}
}

void FriendCharacter::incomingGameChallengeRequest(string e)//shared_ptr<MessageEvent> e)
{ //===============================================================================================


	
	string s = e;// ->getMessage()->toString();
	s = s.substr(s.find(":") + 1);
	string gameName = s;


	//if player is already in game, they should not show up in the minigame challenge list, should broadcast current status constantly.
	//however, if they got populated before the broadcast was received, automatically deny the request

	if (OKNet::myStatus != OKNet::status_AVAILABLE)
	{
		sendGameChallengeResponse(false);
		return;
	}

	if (getOutgoingGameChallengeResponse() == NDGameEngine::gameChallengeResponse_NONE)
	{
		//if notification is already open, don't open a new one, wait for the old one to time out.
		if (this->gameChallengeNotification != nullptr)
		{
			return;
		}

		//&&this.gameChallengeNotification.getIsActivated()==true)return; //this doesn't work because we destroy the GUI on unload.


		//open dialog window with friendname, game name
		this->gameChallengeNotification = getGUIManager()->makeGameChallengeNotification(this, gameName);
	}
	else
	{
		//resend last response
		if (getOutgoingGameChallengeResponse() == NDGameEngine::gameChallengeResponse_ACCEPT)
		{
			sendGameChallengeResponse(true);
		}
		else
		{
			if (getOutgoingGameChallengeResponse() == NDGameEngine::gameChallengeResponse_DECLINE)
			{
				sendGameChallengeResponse(false);
			}
		}
	}
}

void FriendCharacter::cleanup()
{
	

}
