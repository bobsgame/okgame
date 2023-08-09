#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

const int OKNet::clientUDPPortStartRange = 6435;

const string OKNet::endline = ":END:\r\n";
const string OKNet::batch = ":BATCH:";
//const bool OKNet::debugMode = true;
const string OKNet::debugServerAddress = "localhost";
const string OKNet::releaseServerAddress = "server.bobsgame.com";
const int OKNet::serverTCPPort = 6065;
const string OKNet::debugSTUNServerAddress = "localhost";
const string OKNet::releaseSTUNServerAddress = "stun.bobsgame.com";
const int OKNet::STUNServerUDPPort = 6433;
const string OKNet::debugBigDataURL = "http://localhost/z/";
const string OKNet::releaseBigDataURL = "https://bobsgame.s3.amazonaws.com/z/";
const string OKNet::debugSmallDataURL = "http://localhost/assets/";
const string OKNet::releaseSmallDataURL = "http://bobsgame.com/assets/";
const string OKNet::debugINDEXServerAddress = "localhost";
const string OKNet::releaseINDEXServerAddress = "index.bobsgame.com";
const int OKNet::INDEXServerTCPPort = 606;
const string OKNet::Server_IP_Address_Request = "Server_IP_Address_Request:";
const string OKNet::Server_IP_Address_Response = "Server_IP_Address_Response:";
const string OKNet::Login_Request = "Login_Request:";
const string OKNet::Login_Response = "Login_Response:";
const string OKNet::Reconnect_Request = "Reconnect_Request:";
const string OKNet::Reconnect_Response = "Reconnect_Response:";
const string OKNet::Facebook_Login_Request = "Facebook_Login_Request:";
const string OKNet::Facebook_Login_Response = "Facebook_Login_Response:";
const string OKNet::Password_Recovery_Request = "Password_Recovery_Request:";
const string OKNet::Password_Recovery_Response = "Password_Recovery_Response:";
const string OKNet::Create_Account_Request = "Create_Account_Request:";
const string OKNet::Create_Account_Response = "Create_Account_Response:";
const string OKNet::Initial_GameSave_Request = "Initial_GameSave_Request:";
const string OKNet::Initial_GameSave_Response = "Initial_GameSave_Response:";
const string OKNet::Encrypted_GameSave_Update_Request = "Encrypted_GameSave_Update_Request:";
const string OKNet::Encrypted_GameSave_Update_Response = "Encrypted_GameSave_Update_Response:";
const string OKNet::Postal_Code_Update_Request = "Postal_Code_Update_Request:";
const string OKNet::Postal_Code_Update_Response = "Postal_Code_Update_Response:";
const string OKNet::Player_Coords = "Player_Coords:";
const string OKNet::Map_Request_By_Name = "Map_Request_By_Name:";
const string OKNet::Map_Request_By_ID = "Map_Request_By_ID:";
const string OKNet::Map_Response = "Map_Response:";
const string OKNet::Sprite_Request_By_Name = "Sprite_Request_By_Name:";
const string OKNet::Sprite_Request_By_ID = "Sprite_Request_By_ID:";
const string OKNet::Sprite_Response = "Sprite_Response:";
const string OKNet::Dialogue_Request = "Dialogue_Request:";
const string OKNet::Dialogue_Response = "Dialogue_Response:";
const string OKNet::Load_Event_Request = "Load_Event_Request:";
const string OKNet::Load_Event_Response = "Load_Event_Response:";
const string OKNet::Event_Request = "Event_Request:";
const string OKNet::Event_Response = "Event_Response:";
const string OKNet::GameString_Request = "GameString_Request:";
const string OKNet::GameString_Response = "GameString_Response:";
const string OKNet::Flag_Request = "Flag_Request:";
const string OKNet::Flag_Response = "Flag_Response:";
const string OKNet::Skill_Request = "Skill_Request:";
const string OKNet::Skill_Response = "Skill_Response:";
const string OKNet::Music_Request = "Music_Request:";
const string OKNet::Music_Response = "Music_Response:";
const string OKNet::Sound_Request = "Sound_Request:";
const string OKNet::Sound_Response = "Sound_Response:";
const string OKNet::Add_Friend_By_UserName_Request = "Add_Friend_By_UserName_Request:";
const string OKNet::Add_Friend_By_UserName_Response = "Add_Friend_By_UserName_Response:";
const string OKNet::Update_Facebook_Account_In_DB_Request = "Update_Facebook_Account_In_DB_Request:";
const string OKNet::Update_Facebook_Account_In_DB_Response = "Update_Facebook_Account_In_DB_Response:";
const string OKNet::Online_Friends_List_Request = "Online_Friends_List_Request:";
const string OKNet::Online_Friends_List_Response = "Online_Friends_List_Response:";
const string OKNet::Friend_Is_Online_Notification = "Friend_Is_Online_Notification:";
const string OKNet::Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else = "Tell_Client_Their_Session_Was_Logged_On_Somewhere_Else:";
const string OKNet::Tell_Client_Servers_Are_Shutting_Down = "Tell_Client_Servers_Are_Shutting_Down:";
const string OKNet::Tell_Client_Servers_Have_Shut_Down = "Tell_Client_Servers_Have_Shut_Down:";
const string OKNet::STUN_Request = "STUN_Request:";
const string OKNet::STUN_Response = "STUN_Response:";
const string OKNet::Friend_Connect_Request = "Friend_Connect_Request:";
const string OKNet::Friend_Connect_Response = "Friend_Connect_Response:";
const string OKNet::Friend_Data_Request = "Friend_Data_Request:";
const string OKNet::Friend_Data_Response = "Friend_Data_Response:";
const string OKNet::Friend_LocationStatus_Update = "Friend_Location_Update:";
const string OKNet::Game_Connect_Request = "Game_Connect_Request:";
const string OKNet::Game_Connect_Response = "Game_Connect_Response:";
const string OKNet::Game_Challenge_Request = "Game_Challenge_Request:";
const string OKNet::Game_Challenge_Response = "Game_Challenge_Response:";
const string OKNet::INDEX_Register_Server_With_INDEX_Request = "INDEX_Register_Server_With_INDEX_Request:";
const string OKNet::INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online = "INDEX_Tell_ServerID_To_Tell_UserID_That_UserIDs_Are_Online:";
const string OKNet::INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online = "INDEX_Tell_All_Servers_To_Tell_FacebookIDs_That_UserID_Is_Online:";
const string OKNet::INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers = "INDEX_UserID_Logged_On_This_Server_Log_Them_Off_Other_Servers:";
const string OKNet::Server_Register_Server_With_INDEX_Response = "Server_Registered_With_INDEX_Response:";
const string OKNet::Server_Tell_All_FacebookIDs_That_UserID_Is_Online = "Server_Tell_All_FacebookIDs_That_UserID_Is_Online:";
const string OKNet::Server_Tell_UserID_That_UserIDs_Are_Online = "Server_Tell_UserID_That_UserIDs_Are_Online:";
const string OKNet::Server_UserID_Logged_On_Other_Server_So_Log_Them_Off = "Server_UserID_Logged_On_Other_Server_So_Log_Them_Off:";
const string OKNet::Server_Tell_All_Users_Servers_Are_Shutting_Down = "Server_Tell_All_Users_Servers_Are_Shutting_Down:";
const string OKNet::Server_Tell_All_Users_Servers_Have_Shut_Down = "Server_Tell_All_Users_Servers_Have_Shut_Down:";
const string OKNet::OK_Game_GameTypesAndSequences_Download_Request = "OK_Game_GameTypesAndSequences_Download_Request:";
const string OKNet::OK_Game_GameTypesAndSequences_Download_Response = "OK_Game_GameTypesAndSequences_Download_Response:";
const string OKNet::OK_Game_GameTypesAndSequences_Upload_Request = "OK_Game_GameTypesAndSequences_Upload_Request:";
const string OKNet::OK_Game_GameTypesAndSequences_Upload_Response = "OK_Game_GameTypesAndSequences_Upload_Response:";

const string OKNet::OK_Game_GameTypesAndSequences_Vote_Request = "OK_Game_GameTypesAndSequences_Vote_Request:";
const string OKNet::OK_Game_GameTypesAndSequences_Vote_Response = "OK_Game_GameTypesAndSequences_Vote_Response:";


const string OKNet::OK_Game_RoomList_Request = "OK_Game_RoomList_Request:";
const string OKNet::OK_Game_RoomList_Response = "OK_Game_RoomList_Response:";
const string OKNet::OK_Game_TellRoomHostToAddMyUserID = "OK_Game_TellRoomHostToAddMyUserID:";
const string OKNet::OK_Game_NewRoomCreatedUpdate = "OK_Game_NewRoomCreatedUpdate:";

const string OKNet::OK_Game_HostingPublicRoomUpdate = "OK_Game_HostingPublicRoomUpdate:";
const string OKNet::OK_Game_HostingPublicRoomStarted = "OK_Game_HostingPublicRoomStarted:";
const string OKNet::OK_Game_HostingPublicRoomCanceled = "OK_Game_HostingPublicRoomCanceled:";
const string OKNet::OK_Game_HostingPublicRoomEnded = "OK_Game_HostingPublicRoomEnded:";

const string OKNet::OK_Game_GameStats = "OK_Game_GameStats:";
const string OKNet::OK_Game_GameStats_Response = "OK_Game_GameStats_Response:";

const string OKNet::OK_Game_ActivityStream_Request = "OK_Game_ActivityStream_Request:";
const string OKNet::OK_Game_ActivityStream_Response = "OK_Game_ActivityStream_Response:";
const string OKNet::OK_Game_ActivityStream_Update = "OK_Game_ActivityStream_Update:";


const string OKNet::OK_Game_GetHighScoresAndLeaderboardsRequest = "OK_Game_GetHighScoresAndLeaderboardsRequest:";
const string OKNet::OK_Game_UserStatsLeaderBoardsAndHighScoresBatched = "OK_Game_UserStatsLeaderBoardsAndHighScoresBatched:";
const string OKNet::OK_Game_UserStatsForSpecificGameAndDifficulty = "OK_Game_UserStatsForSpecificGameAndDifficulty:";
const string OKNet::OK_Game_LeaderBoardsByTotalTimePlayed = "OK_Game_LeaderBoardsByTotalTimePlayed:";
const string OKNet::OK_Game_LeaderBoardsByTotalBlocksCleared = "OK_Game_LeaderBoardsByTotalBlocksCleared:";
const string OKNet::OK_Game_LeaderBoardsByPlaneswalkerPoints = "OK_Game_LeaderBoardsByPlaneswalkerPoints:";
const string OKNet::OK_Game_LeaderBoardsByEloScore = "OK_Game_LeaderBoardsByEloScore:";
const string OKNet::OK_Game_HighScoreBoardsByTimeLasted = "OK_Game_HighScoreBoardsByTimeLasted:";
const string OKNet::OK_Game_HighScoreBoardsByBlocksCleared = "OK_Game_HighScoreBoardsByBlocksCleared:";




const string OKNet::Chat_Message = "Chat_Message:";
const string OKNet::Server_Stats_Request = "Server_Stats_Request:";
const string OKNet::Server_Stats_Response = "Server_Stats_Response:";

const string OKNet::Client_Location_Request = "Client_Location_Request:";
const string OKNet::Client_Location_Response = "Client_Location_Response:";






Logger OKNet::log = Logger("OKNet");
sp<Logger> OKNet::_threadLog = ms<Logger>("OKNet");

sp<vector<sp<UDPPeerConnection>>> OKNet::udpConnections;
sp<TCPServerConnection> OKNet::tcpServerConnection = ms<TCPServerConnection>();
int OKNet::myStatus = status_AVAILABLE;
sp<vector<sp<Engine>>> OKNet::engines;

bool OKNet::threadStarted = false;

OKNet::OKNet()
{

}

OKNet::~OKNet()
{
	if (threadStarted)
	{
		setStopThread_S(true);
		t.join();
	}

	for(int i=0;i<udpConnections->size();i++)
	{
		sp<UDPPeerConnection>c = udpConnections->at(i);
		//delete c;
		c = nullptr;
	}
	udpConnections->clear();

	tcpServerConnection->cleanup();
}

mutex OKNet::threadLog_Mutex;
thread OKNet::t;

UDPsocket OKNet::_socket = UDPsocket();
mutex OKNet::_socket_Mutex;

SDLNet_SocketSet OKNet::_socketSet = SDLNet_AllocSocketSet(1);
mutex OKNet::_socketSet_Mutex;

bool OKNet::_socketAddedToSet = false;
mutex OKNet::_socketAddedToSet_Mutex;

bool OKNet::_socketIsOpen = false;
mutex OKNet::_socketIsOpen_Mutex;

bool OKNet::_stopThread = false;
mutex OKNet::_stopThread_Mutex;

int OKNet::_stunChannel = -1;
mutex OKNet::_stunChannel_Mutex;

sp<IPaddress> OKNet::_stunServerIPAddress_S = nullptr;
int OKNet::_stunServerPort_S = -1;
mutex OKNet::_stunServerIPAddress_Mutex;

queue<string> OKNet::_stunMessageQueue;
mutex OKNet::_stunMessageQueue_Mutex;

//===============================================================================================
void OKNet::addEngineToForwardMessagesTo(sp<Engine> e)
{//===============================================================================================
	//if(engines->contains(e)==false)
	//engines->push_back(e);

	bool contains = false;
	for (int i = 0; i < engines->size(); i++)
	{
		if(engines->at(i).get() == e.get())
		{
			contains = true;
		}
	}
	if(contains==false)
	{
		engines->push_back(e);
	}



}
//===============================================================================================
void OKNet::update()
{//===============================================================================================

	if (threadStarted == false)
	{
		log.debug("Created STUN thread");
		t = thread(&OKNet::updateThreadLoop);
		threadStarted = true;
	}

	while (stunMessageQueueSize_S()>0)
	{
		string s = stunMessageQueueFront_S();
		stunMessageQueuePop_S();
		udpSTUNMessageReceived(s);
	}

	tcpServerConnection->update();

	for (int i = 0; i < udpConnections->size(); i++)
	{
		sp<UDPPeerConnection>p = udpConnections->at(i);
		p->update();
	}
}


//===============================================================================================
void OKNet::updateThreadLoop()
{//===============================================================================================

	//long long _queuedSaveGameUpdateDelayTime = 0;
	//long long _sendOnlineFriendListRequestTime = 0;
	//long long _sendOutgoingAuthorizedMessageQueueTime = 0;
	//bool _checkedSessionToken = false;

	while (getStopThread_S() == false)
	{
		this_thread::sleep_for(chrono::milliseconds(10));
		//SDL_Delay(10);

		_checkForIncomingSTUNTraffic();

	}
}

//===============================================================================================
bool OKNet::_ensureSocketIsOpen()
{//===============================================================================================
	if (getStunServerIPAddress_S() == nullptr)
	{
		setStunServerIPAddress_S(Main::STUNServerAddressString.c_str(), OKNet::STUNServerUDPPort);//this is server port, so it will always be original port number

		if (getStunServerIPAddress_S() == nullptr)return false;
	}

	if (getSocketIsOpen_S() == false)
	{
		if (getSocketAddedToSet_S())
		{
			if (SDLNet_UDP_DelSocket(getSocketSet_S(), getSocket_S()) < 0)
			{
				threadLogDebug_S("SDLNet_UDP_DelSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
				SDL_ClearError();
			}
			setSocketAddedToSet_S(false);
		}

		setSocket_S(SDLNet_UDP_Open(Main::STUNServerUDPPort));//this is client port, not server port, so it is +1 if the server is hosted locally
		log.debug("Opened socket to STUN server on port " + to_string(Main::STUNServerUDPPort));
		if (!getSocket_S())
		{
			//SDLNet_FreeSocketSet(set);
			threadLogError_S("SDLNet_UDP_Open stunServerAddress: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
			return false;
		}

		if (getSocketAddedToSet_S() == false)
		{
			if (SDLNet_UDP_AddSocket(getSocketSet_S(), getSocket_S()) < 0)
			{
				threadLogDebug_S("SDLNet_UDP_AddSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
				SDL_ClearError();
			}
			else
				setSocketAddedToSet_S(true);
		}

		setStunChannel_S(SDLNet_UDP_Bind(getSocket_S(), -1, getStunServerIPAddress_S().get()));

		setSocketIsOpen_S(true);
		return true;
	}
	return true;
}
//===============================================================================================
bool OKNet::_checkForIncomingSTUNTraffic()
{//===============================================================================================

	if (_ensureSocketIsOpen() == false)return false;

	int numReady = SDLNet_CheckSockets(getSocketSet_S(), 0);
	if (numReady < 0)
	{
		threadLogDebug_S("SDLNet_CheckSockets: " + string(SDLNet_GetError()) + string(SDL_GetError()));
		SDL_ClearError();
	}

	int numPacketsReceived = 0;

	if (numReady > 0)
	{

		int rd = SDLNet_SocketReady(getSocket_S());

		if (rd > 0)
		{
			sp<UDPpacket>packet = ms<UDPpacket>(SDLNet_AllocPacket(10000));
			numPacketsReceived = SDLNet_UDP_Recv(getSocket_S(), packet.get());

			if (numPacketsReceived > 0)
			{
				if (packet->address.host != getStunServerIPAddress_S()->host)
				{
					threadLogError_S("STUN address didn't match in incoming packet.");
				}

				string s = string((char*)packet->data, packet->len);

				SDLNet_FreePacket(packet.get());

				//return udpSTUNMessageReceived(s);
				stunMessageQueuePush_S(s);
				return true;

			}
			else if (numPacketsReceived < 0)
			{
				SDLNet_FreePacket(packet.get());
				//connection lost
				SDLNet_UDP_Close(getSocket_S());

				if (getSocketAddedToSet_S())
				{
					if (SDLNet_UDP_DelSocket(getSocketSet_S(), getSocket_S()) < 0)
					{
						threadLogDebug_S("SDLNet_UDP_DelSocket: " + string(SDLNet_GetError()) + string(SDL_GetError()));
						SDL_ClearError();
					}

					setSocketAddedToSet_S(false);
				}
				setSocketIsOpen_S(false);
				return false;
			}
			SDLNet_FreePacket(packet.get());
		}
		else
		if (rd < 0)
		{
			threadLogError_S("SDLNet_TCP_Recv Error: " + string(SDLNet_GetError()) + string(SDL_GetError()));
			SDL_ClearError();
			return false;
		}
	}
	return false;
}
//===============================================================================================
bool OKNet::udpSTUNMessageReceived(string e)
{//===============================================================================================

	if (OKString::startsWith(e, OKNet::STUN_Response))
	{

		//make sure it is from the correct IP

		//	if (e->getRemoteAddress()->toString()->equals(stunServerAddress->toString()) == false)
		//	{
		//		log.error("STUN IP address didn't match stunServerAddress");
		//		return;
		//	}

		string s = e;

		if (s.find(OKNet::endline) == string::npos)
		{
			log.error("Message doesn't end with endline");
			s = s + OKNet::endline;
		}

		//strip off endline
		s = s.substr(0, s.find(OKNet::endline));

#ifdef _DEBUG
		log.debug(s);
#endif
		string friendIPString = "";
		int friendPort = -1;

		//STUNResponse:userID,/127.0.0.1:stunport,peerPort,
		s = s.substr(s.find(":") + 1); //userID,/127.0.0.1:stunport,peerPort,
		int replyFriendUserID = -1;

		try
		{
			replyFriendUserID = stoi(s.substr(0, s.find(",")));
		}
		catch(exception)
		{
			log.error("Could not parse friend User ID in STUN reply");
			return false;
		}

		s = s.substr(s.find(",") + 1);//socketString looks like /127.0.0.1:stunport,peerPort,
		s = s.substr(s.find("/") + 1);//skip over /
		friendIPString = s.substr(0, s.find(":"));
		s = s.substr(s.find(",") + 1); //skip stunport

		string portString = s.substr(0,s.find(","));//peerPort
		try
		{
			friendPort = stoi(portString);
		}
		catch(exception)
		{
			log.error("Could not parse friend port in STUN reply");
			return false;
		}

		if (friendIPString.length() == 0)
		{
			return false;
		}
		if (friendPort == -1)
		{
			return false;
		}
		//log.debug("STUN reply:"+to_string(replyFriendUserID)+":" + friendIPString + ":" + to_string(friendPort));

		//find udpPeerConnection with that userID
		bool found = false;
		for(int i=0;i<udpConnections->size();i++)
		{
			sp<UDPPeerConnection>c = udpConnections->at(i);
			if(c->peerUserID==replyFriendUserID)
			{
				c->setPeerIPAddress_S(friendIPString, friendPort);
				found = true;
			}
		}
		if(!found)
		{
			log.error("Could not find peer with STUN reply userID");
		}
		
		
		return true;
	}
	return false;
}

//===============================================================================================
void OKNet::sendSTUNRequest(long long myUserID, long long friendUserID, int myPort)
{ //===============================================================================================

	if (_ensureSocketIsOpen() == false)return;

	string s = (OKNet::STUN_Request + to_string(myUserID) + "," + to_string(friendUserID) + "," + to_string(myPort) + "," + OKNet::endline);

#ifdef _DEBUG
		log.debug("SEND STUN SERVER:" + s.substr(0, s.length() - OKNet::endline.length()));
#endif

	const char* buf = s.c_str();

	int sent = 0;

	//sp<UDPpacket> packet = SDLNet_AllocPacket(s.length());
	UDPpacket packet;
	packet.channel = -1;
	packet.address = *getStunServerIPAddress_S();
	packet.data = (Uint8*)buf;
	packet.len = (int)s.length();
	//SDLNet_FreePacket(packet);

	sent += SDLNet_UDP_Send(getSocket_S(), -1, &packet);

	if (sent==0)
	{
		log.error("Could not send UDP packet to STUN server");
	}
}

//===============================================================================================
sp<UDPPeerConnection> OKNet::addFriendID(long long friendID, int type)
{//===============================================================================================

	//if (type == UDPPeerConnection::FACEBOOK_TYPE)
	{
		for (int i = 0; i < udpConnections->size(); i++)
		{
			if (udpConnections->at(i)->peerUserID == friendID)
			{
				return udpConnections->at(i);
			}
		}

		sp<UDPPeerConnection> f = ms<UDPPeerConnection>(friendID,type);
		udpConnections->push_back(f);
		log.debug("Added peer: " + to_string(friendID));
		return f;
	}
}

//===============================================================================================
void OKNet::sendAllPeers(string s)
{//===============================================================================================
	for (int i = 0; i < udpConnections->size(); i++)
	{
		sp<UDPPeerConnection> c = udpConnections->at(i);
		if (c->getConnectedToPeer_S())
		{
			c->writeReliable_S(s);
		}
	}
}

