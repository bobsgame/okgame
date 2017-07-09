//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include <src/Engine/entity/Character.h>
#include <src/Engine/nd/NDGameEngine.h>
class Logger;


class FriendManager;
class UDPPeerConnection;
class MiniGameEngine;
class BGClientEngine;



class GameChallengeNotificationPanel;


class FriendCharacter : public Character
{
public:
	static Logger log;



	FriendManager* friendManager = nullptr;


	string mapName = "";

	UDPPeerConnection * connection = nullptr;


public:
	MiniGameEngine* game = nullptr;




	float targetX = 0;
	float targetY = 0;


	FriendCharacter(BGClientEngine* g);


	FriendCharacter(BGClientEngine* g, int friendUserID, int friendType);


	/// <summary>
	/// FOR DEBUG </summary>
	FriendCharacter(BGClientEngine* g, int friendUserID, int friendType, int myUDPPort, int theirUDPPort);


	void setGameToForwardPacketsTo(MiniGameEngine* game);


	bool udpPeerMessageReceived(UDPPeerConnection *c, string e) override;



	virtual void update() override;




	//TODO: no idea if synchronized functions that access non-synchronized variables works the way I want.

	void setMapName_S(const string& mapName);

	void setX_S(float x);
	void setY_S(float y);



	long long lastSentLocationTime = 0;

private:
	void sendFriendLocationStatusUpdate();


public:
	void incomingFriendLocationStatusUpdate(string e);


private:
	int outgoingGameChallengeResponse = NDGameEngine::gameChallengeResponse_NONE;
	long long timeOutgoingGameChallengeResponseSet = 0;
public:
	GameChallengeNotificationPanel* gameChallengeNotification = nullptr;

	void setOutgoingGameChallengeResponse(int i);
	int getOutgoingGameChallengeResponse();
	void sendGameChallengeResponse(bool b);
	void incomingGameChallengeRequest(string e);


	void cleanup();

};

