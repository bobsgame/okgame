//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include <string>
#include "bobtypes.h"
#include "GameLogic.h"
#include "GameType.h"
#include "GameSequence.h"
#include <src/Engine/network/GameSave.h>
#include <src/Engine/network/UDPPeerConnection.h>

class Logger;

#include "src/Utility/AssetData.h"
#include "src/Utility/ArrayList.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/audio/Sound.h"
#include "src/Utility/ControlsManager.h"
#include "src/Utility/BobMenu.h"
#include "../Engine/Engine.h"
#include "../Engine/nd/NDGameEngine.h"

#include "CustomGameEditor.h"
#include "GameSequenceEditor.h"

//#include "Stats/GameStats.h"
#include "Stats/UserStatsForSpecificGameAndDifficulty.h"
#include "Stats/LeaderBoardAndHighScoreBoardEntry.h"
//#include "GameTestMenu.h"

class BobsGameGameStats;

class GameTestMenuControl;
//class Engine;
//class NDGameEngine;
class Logger;
class ControlsManager;
class SpriteManager;
class AudioManager;
class PreloadedSprite;
class BobFont;
class CaptionManager;
class Room;


//=========================================================================================================================
class BobsGame : public NDGameEngine
{//=========================================================================================================================
private:
	typedef NDGameEngine super;
public:
	static Logger log;

protected:
	bool bgShaderFBOTextureToggle = false;

public:

	//static shared_ptr<BobsGame> b;
	shared_ptr<Sound >music = nullptr;
	shared_ptr<BobTexture> keyboardTexture = nullptr;
	shared_ptr<BobTexture> controllerTexture = nullptr;
	shared_ptr<BobTexture> controllerIconTexture = nullptr;
	shared_ptr<BobTexture> keyboardIconTexture = nullptr;
	shared_ptr<BobTexture> onlineTexture = nullptr;
	shared_ptr<BobTexture> networkIconTexture = nullptr;
	shared_ptr<BobTexture> gearsTexture = nullptr;
	shared_ptr<BobTexture> chartTexture = nullptr;

	static shared_ptr<BobTexture> upperLeft;
	static shared_ptr<BobTexture> top;
	static shared_ptr<BobTexture> upperRight;
	static shared_ptr<BobTexture> left;
	static shared_ptr<BobTexture> right;
	static shared_ptr<BobTexture> lowerLeft;
	static shared_ptr<BobTexture> bottom;
	static shared_ptr<BobTexture> lowerRight;

	shared_ptr<GameLogic> getPlayer1Game();
	shared_ptr<PuzzlePlayer> getPlayer1();
	void setBobsGameFBOSize();
	void renderGameIntoFBO(shared_ptr<GameLogic> g, bool useColorFilter);
	void drawBobsGameFBO(float x0, float x1, float y0, float y1);
	virtual void render() override;

	BobsGame();
	BobsGame(ND* nD);
	virtual ~BobsGame() override;
	virtual void init() override;



	void initPlayer();
	bool isMultiplayer();
	
	//long long randomSeed = -1;
	//shared_ptr<GameType> originalSettings = nullptr;
	long long timeRenderBegan = 0;

	virtual bool isNetworkGame() override;
	void debugKeys();
	virtual void update() override;

	
	int shaderCount = rand() % GLUtils::bgShaderCount;
	void changeBG();
	virtual void shakeSmall() override;
	virtual void shakeHard() override;
	

	static shared_ptr<Sprite> bobsGameLogoSmall;

	void initAssets();
	shared_ptr<Sprite> getSpriteFromName(const string& name);
	//shared_ptr<BobsGame> getThis();

	virtual void updateControls() override;
	virtual void resetPressedButtons() override;
	virtual void setButtonStates() override;

	ArrayList<shared_ptr<PuzzlePlayer>> players;
	

	

	//-----------------
	//menus
	//-----------------

		
	shared_ptr<Caption> pressEnterToRestartCaption = nullptr;

	virtual void setupMenus() override;
	virtual bool renderMenus() override;
	virtual bool updateMenus() override;

	bool startScreenMenuShowing = false;
	shared_ptr<BobMenu >startScreenMenu = nullptr;
	shared_ptr<BobMenu >infoMenu = nullptr;
	shared_ptr<BobMenu >patreonMenu = nullptr;
	shared_ptr<BobMenu >forumMenu = nullptr;
	shared_ptr<BobMenu >activityMenu = nullptr;
	int startScreenMenuCursorPosition = 0;
	void startScreenMenuUpdate();
	void startScreenMenuRender();


	static ArrayList<string> activityStream;
	bool sentActivityStreamRequest = false;
	//bool gotActivityStream = false;
	//long long lastCheckedActivityResponseTime = 0;

	shared_ptr<BobMenu >gettingGamesFromServerMenu = nullptr;
	void gettingGamesFromServerMenuUpdate();
	void gettingGamesFromServerMenuRender();
	bool gettingGamesFromServerMenuShowing = false;
	long long gettingGamesFromServerDotsTime = 0;
	int gettingGamesFromServerCount = 0;

	string cycleDots(int tries);

	virtual void updateTitleScreenLogo() override;
	virtual void updateTitleMenuLogoTexture() override;
	virtual void titleMenuUpdate() override;
	virtual void titleMenuRender() override;

	//shared_ptr<Caption> pressEnterCaption = nullptr;

	virtual void pauseMenuUpdate() override;
	virtual void pauseMenuRender() override;
	long long timeLastChangedSetting = 0;
	long long timeStartedChangedSetting = 0;

	void difficultyMenuUpdate();
	//void difficultyMenuRender();
	bool difficultyMenuShowing = false;
	shared_ptr<BobMenu >difficultyMenu = nullptr;
	int difficultyMenuCursorPosition = 0;

	void controllerMenuUpdate();
	void controllerMenuRender();
	bool controllerMenuShowing = false;
	shared_ptr<BobMenu >controllerMenu = nullptr;
	int controllerMenuCursorPosition = 0;
	bool controllerMenuTestingButtons = false;

	void localMultiplayerPlayerJoinMenuUpdate();
	void localMultiplayerPlayerJoinMenuRender();
	bool localMultiplayerPlayerJoinMenuShowing = false;
	shared_ptr<BobMenu >localMultiplayerPlayerJoinMenu = nullptr;
	int localMultiplayerPlayerJoinMenuCursorPosition = 0;
	shared_ptr<Caption> localMultiplayerPressStartCaption = nullptr;

	void playerDifficultyMiniMenuUpdate(shared_ptr<PuzzlePlayer >p);
	void playerDifficultyMiniMenuRender(shared_ptr<PuzzlePlayer >p, float x, float y);

	void playerControllerSettingsMenuInit(shared_ptr<BobMenu> m, shared_ptr<PuzzlePlayer >p);
	void playerControllerSettingsMenuToggle(shared_ptr<BobMenu> m, shared_ptr<PuzzlePlayer >p);
	void playerSettingsMenuInit(shared_ptr<BobMenu> m, shared_ptr<PuzzlePlayer >p);
	void playerSettingsMenuLeft(shared_ptr<BobMenu> m, shared_ptr<PuzzlePlayer >p);
	void playerSettingsMenuRight(shared_ptr<BobMenu> m, shared_ptr<PuzzlePlayer >p);
	void playerPauseMiniMenuUpdate(shared_ptr<PuzzlePlayer >p);
	void playerPauseMiniMenuRender(shared_ptr<PuzzlePlayer >p, float x0, float x1, float y0, float y1);

	void loginMenuUpdate();
	void loginMenuRender();
	bool loginMenuShowing = false;
	shared_ptr<BobMenu >loginMenu = nullptr;
	int loginMenuCursorPosition = 0;
	bool textStarted = false;
	string saveRoomConfigNameText = "";
	string userNameOrEmailText = "";
	string userNameText = "";
	string emailText = "";
	//bool showPasswordStars = false;
	string passwordText = "";
	string passwordStarsText = "";
	string confirmPasswordText = "";
	string confirmPasswordStarsText = "";
	bool stayLoggedIn = true;

	shared_ptr<Caption> errorLabel = nullptr;
	shared_ptr<Caption> statusLabel = nullptr;

	//bool loggedIn = false;

	void createAccountMenuUpdate();
	void createAccountMenuRender();
	bool createAccountMenuShowing = false;
	int lastMX = 0;
	int lastMY = 0;
	shared_ptr<BobMenu >createAccountMenu = nullptr;
	int createAccountMenuCursorPosition = 0;
	
	ArrayList<shared_ptr<Room>> rooms;
	shared_ptr<Room> currentRoom = nullptr;

	void addToRoomsMenu(shared_ptr<Room> c, string name, string id);
	void populateRoomsMenu();
	void networkMultiplayerLobbyMenuUpdate();
	void networkMultiplayerLobbyMenuRender();
	void selectGameSequenceOrSingleGameTypeFilterMenuUpdate();
	void selectGameSequenceFilterMenuUpdate();
	void selectSingleGameTypeFilterMenuUpdate();
	bool networkMultiplayerLobbyMenuShowing = false;
	bool selectGameSequenceFilterMenuShowing = false;
	bool selectSingleGameTypeFilterMenuShowing = false;
	bool selectGameSequenceOrSingleGameTypeFilterMenuShowing = false;
	//ArrayList<shared_ptr<Caption>> *hostingFriendCaptions = make_shared<ArrayList><shared_ptr<Caption>>();
	//ArrayList<shared_ptr<Caption>> *playingFriendCaptions = make_shared<ArrayList><shared_ptr<Caption>>();
	//int hostingFriendsCursorPosition = 0;
	shared_ptr<BobMenu >networkMultiplayerLobbyMenu = nullptr;
	shared_ptr<BobMenu >yourStatsMenu = nullptr;
	shared_ptr<BobMenu >leaderBoardMenu = nullptr;
	shared_ptr<BobMenu >roomsMenu = nullptr;
	shared_ptr<BobMenu >friendsOnlineMenu = nullptr;
	//shared_ptr<Caption >onlineFriendsLabel = nullptr;
	int networkMultiplayerLobbyMenuCursorPosition = 0;
	bool selectingHostedGame = false;
	//shared_ptr<UDPPeerConnection >hostPeer = nullptr;
	ArrayList<shared_ptr<UDPPeerConnection>> *joinedPeers = make_shared<ArrayList><shared_ptr<UDPPeerConnection>>();
	bool hostStartedGame = false;
	string friendUserName = "";

	void networkMultiplayerPlayerJoinMenuUpdate();
	void networkMultiplayerPlayerJoinMenuRender();
	shared_ptr<BobMenu >networkMultiplayerPlayerJoinMenu = nullptr;
	shared_ptr<BobMenu >networkMultiplayerJoinedPeersMenu = nullptr;
	shared_ptr<BobMenu >networkMultiplayerRoomRulesMenu = nullptr;
	shared_ptr<Caption> networkMultiplayerPlayerJoinMenuPressStartCaption = nullptr;
	bool networkMultiplayerPlayerJoinMenuShowing = false;
	bool hosting = false;
	bool joining = false;
	
	bool hidePrivateRooms = false;
	bool hidePublicRooms = false;
	bool hideFreePlayRooms = false;
	bool hideTournamentRooms = false;
	string filterByGameSequenceName = "";
	string filterByGameSequenceUUID = "";
	string filterByGameTypeName = "";
	string filterByGameTypeUUID = "";
	string filterByKeyword = "";
	int filterByMaxPlayers = -1;

	long long lastSentPlayersUpdateTime = 0;
	long long lastSentServerRoomUpdateTime = 0;
	long long updatedJoinedPeersListTime = 0;
	//NETWORK

	long long lastTimeTriedToCloseGame = 0;
	virtual void tryToCloseGame() override;

	shared_ptr<CustomGameEditorControl >customGameEditor = nullptr;
	shared_ptr<GameSequenceEditorControl >gameSequenceEditor = nullptr;
	shared_ptr<GameTestMenuControl >gameTestMenu = nullptr;

	void customGameEditorMenuUpdate();
	void customGameEditorMenuRender();
	shared_ptr<BobMenu >customGameEditorMenu = nullptr;
	bool customGameEditorMenuShowing = false;
	int customGameEditorMenuCursorPosition = 0;
    

	void gameSequenceEditorMenuUpdate();
	void gameSequenceEditorMenuRender();
	shared_ptr<BobMenu >gameSequenceEditorMenu = nullptr;
	bool gameSequenceEditorMenuShowing = false;
	int gameSequenceEditorMenuCursorPosition = 0;

	void gameTestMenuUpdate();
	void gameTestMenuRender();
	//shared_ptr<BobMenu >gameTestMenu = nullptr;
	bool gameTestMenuShowing = false;
	int gameTestMenuCursorPosition = 0;


	void settingsMenuInit(shared_ptr<BobMenu> m, bool isSettingsMenu);
	void settingsMenuToggle(shared_ptr<BobMenu> m);
	void settingsMenuLeft(shared_ptr<BobMenu> m);
	void settingsMenuRight(shared_ptr<BobMenu> m);
	void settingsMenuSetDefaults(shared_ptr<BobMenu> m, bool isSettingsMenu);
	void globalSettingsMenuUpdate();
	void globalSettingsMenuRender();
	shared_ptr<BobMenu >globalSettingsMenu = nullptr;
	bool globalSettingsMenuShowing = false;
	int globalSettingsMenuCursorPosition = 0;

	void statsMenuUpdate();
	void statsMenuRender();
	shared_ptr<BobMenu >statsMenu = nullptr;
	shared_ptr<BobMenu >whichStatsMiniMenu = nullptr;
	bool whichStatsMiniMenuShowing = false;
	void resetAllStatsMenuVars();
	void whichStatsMiniMenuUpdate();
	bool statsMenuShowing = false;
	int statsMenuCursorPosition = 0;
	string statsMenu_difficultyName = "OVERALL";
	string statsMenu_gameSequenceOrTypeUUID = "OVERALL";
	string statsMenu_gameSequenceOrTypeName = "OVERALL";
	string statsMenu_objectiveName = "Play To Credits";
	bool updateStatsMenu = true;
	bool statsMenu_totalTimePlayed = false;
	bool statsMenu_totalBlocksCleared = false;
	bool statsMenu_planeswalkerPoints = false;
	bool statsMenu_eloScore = false;
	bool statsMenu_timeLasted = true;
	bool statsMenu_blocksCleared = false;


	void leftRightMenuAdjustFloat(float& variable, float min, float max, float minIncrement, float maxIncrement);
	void leftRightMenuAdjustInt(int& variable, int min, int max, int minIncrement, int maxIncrement);

	void saveRoomConfigMenuUpdate();
	shared_ptr<BobMenu >saveRoomConfigMenu = nullptr;
	bool saveRoomConfigMenuShowing = false;
	int saveRoomConfigMenuCursorPosition = 0;

	void loadRoomConfigMenuUpdate();
	shared_ptr<BobMenu >loadRoomConfigMenu = nullptr;
	bool loadRoomConfigMenuShowing = false;
	int loadRoomConfigMenuCursorPosition = 0;


	void roomOptionsMenuUpdate();
	//void roomOptionsMenuRender();
	shared_ptr<BobMenu >roomOptionsMenu = nullptr;
	bool roomOptionsMenuShowing = false;
	int roomOptionsMenuCursorPosition = 0;

	shared_ptr<Caption> descriptionCaption = nullptr;


	void gameSetupMenuUpdate();
	void gameSetupMenuRender();
	shared_ptr<BobMenu >gameSetupMenu = nullptr;
	bool gameSetupMenuShowing = false;
	int gameSetupMenuCursorPosition = 0;
	int selectedDifficultyIndex = 0;
	//int selectedObjectiveIndex = 0;

	//void selectedGameSequence(string name);
	//void selectedGameType(string name);
	//void selectedDifficulty(string name);
	//void selectedObjective(string name);

	void selectGameSequenceOrSingleGameTypeMenuUpdate();
	void selectGameSequenceOrSingleGameTypeMenuRender();
	shared_ptr<BobMenu >selectGameSequenceOrSingleGameTypeMenu = nullptr;
	bool selectGameSequenceOrSingleGameTypeMenuShowing = false;
	int selectGameSequenceOrSingleGameTypeMenuCursorPosition = 0;

	void selectGameSequenceMenuUpdate();
	void selectGameSequenceMenuRender();
	shared_ptr<BobMenu >selectGameSequenceMenu = nullptr;
	bool selectGameSequenceMenuShowing = false;
	int selectGameSequenceMenuCursorPosition = 0;

	double wilsonScore(double up, double total, double confidence = 1.644853);
	typedef pair<string, shared_ptr<BobColor>> StringColorPair;
	typedef pair<shared_ptr<GameType>, StringColorPair> GameTypeStringColorPairPair;
	typedef pair<shared_ptr<GameSequence>, StringColorPair> GameSequenceStringColorPairPair;

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	shared_ptr<BobsGameUserStatsForSpecificGameAndDifficulty> getUserStatsForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString);
	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	void populateUserStatsForSpecificGameAndDifficultyMenu(shared_ptr<BobMenu >menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString);

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	shared_ptr<BobsGameLeaderBoardAndHighScoreBoard> getLeaderboardOrHighScoreBoardForGame(string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
		bool totalTimePlayed,
		bool totalBlocksCleared,
		bool planeswalkerPoints,
		bool eloScore,
		bool timeLasted,
		bool blocksCleared);

	//gameTypeOrSequenceString or difficulty string can be "OVERALL"
	string populateLeaderBoardOrHighScoreBoardMenu(shared_ptr<BobMenu >menu, string gameTypeOrSequenceUUID, string difficultyString, string objectiveString,
		bool totalTimePlayed,
		bool totalBlocksCleared,
		bool planeswalkerPoints,
		bool eloScore,
		bool timeLasted,
		bool blocksCleared
	);

	ArrayList<GameTypeStringColorPairPair> getSortedGameTypes();
	ArrayList<GameSequenceStringColorPairPair> getSortedGameSequences();
	void populateGameTypesMenu(shared_ptr<BobMenu >m);
	void populateGameSequencesMenu(shared_ptr<BobMenu >m);
	void selectSingleGameTypeMenuUpdate();
	//void selectSingleGameTypeMenuRender();
	shared_ptr<BobMenu >selectSingleGameTypeMenu = nullptr;
	bool selectSingleGameTypeMenuShowing = false;
	int selectSingleGameTypeMenuCursorPosition = 0;

	bool upRepeatedStarted = false;
	bool upRepeating = false;
	long long upLastTime = 0;

	bool downRepeatedStarted = false;
	bool downRepeating = false;
	long long downLastTime = 0;

	void gameSequenceOptionsMenuUpdate();
	void gameSequenceOptionsMenuRender();
	shared_ptr<BobMenu >gameSequenceOptionsMenu = nullptr;
	bool gameSequenceOptionsMenuShowing = false;
	int gameSequenceOptionsMenuCursorPosition = 0;

	void gameObjectiveMenuUpdate();
	//void gameObjectiveMenuRender();
	shared_ptr<BobMenu >gameObjectiveMenu = nullptr;
	bool gameObjectiveMenuShowing = false;
	int gameObjectiveMenuCursorPosition = 0;

	void sendGarbageToMenuUpdate();
	//void sendGarbageToMenuRender();
	shared_ptr<BobMenu >sendGarbageToMenu = nullptr;
	bool sendGarbageToMenuShowing = false;
	int sendGarbageToMenuCursorPosition = 0;

	void multiplayerOptionsMenuUpdate();
	void multiplayerOptionsMenuRender();
	shared_ptr<BobMenu >multiplayerOptionsMenu = nullptr;
	bool multiplayerOptionsMenuShowing = false;
	int multiplayerOptionsMenuCursorPosition = 0;

	//bool multiplayer_AllowDifferentDifficulties = true;
	//bool multiplayer_AllowDifferentGameSequences = true;
	//bool multiplayer_GameEndsWhenOnePlayerRemains = true;
	//bool multiplayer_GameEndsWhenSomeoneCompletesCreditsLevel = true;
	//bool multiplayer_DisableVSGarbage = false;
	bool localMultiplayer = false;
	bool networkMultiplayer = false;
	//shared_ptr<GameSequence >multiplayer_SelectedGameSequence = nullptr;
	//string multiplayer_SelectedDifficultyName = "Beginner";

	void sendGameStatsToServer();
	void doVoting();

	shared_ptr<BobMenu> statsUploadMenu = nullptr;
	bool sentStats = false;
	bool gotStatsResponse = false;
	long long firstCheckedStatsResponseTime = 0;
	long long lastCheckedStatsResponseTime = 0;

	shared_ptr<BobMenu> voteMenu = nullptr;
	bool sentVote = false;
	//bool voteUpDown = false;

	


	void playerGameSequenceMiniMenuUpdate(shared_ptr<PuzzlePlayer >p);
	void playerGameSequenceMiniMenuRender(shared_ptr<PuzzlePlayer >p, float x, float y);




	static ArrayList<shared_ptr<BobsGameUserStatsForSpecificGameAndDifficulty>> userStatsPerGameAndDifficulty;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topPlayersByTotalTimePlayed;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topPlayersByTotalBlocksCleared;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topPlayersByPlaneswalkerPoints;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topPlayersByEloScore;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topGamesByTimeLasted;
	static ArrayList<shared_ptr<BobsGameLeaderBoardAndHighScoreBoard>> topGamesByBlocksCleared;



	void sendAllJoinedPeers(const string& s);
	void sendPeer(shared_ptr<UDPPeerConnection >c, const string& s);
	void sendAllPeers(const string& s);

	static const string lobbyCommand_STARTGAME;
	static const string lobbyCommand_CANCELGAME;
	static const string lobbyCommand_PEERGAMEJOIN;
	static const string lobbyCommand_PEERGAMELEAVE;
	static const string lobbyCommand_JOINEDPEER;
	static const string lobbyCommand_PLAYERCONFIRM;
	static const string lobbyCommand_PLAYERJOIN;
	static const string lobbyCommand_PLAYERLEAVE;
	static const string lobbyCommand_PLAYERFORFEIT;
	static const string lobbyCommandAllPeers_PLAYING;
	static const string lobbyCommandAllPeers_HOSTING;
	static const string lobbyCommandAllPeers_NOT_HOSTING;

	static const string netCommand_START;
	static const string netCommand_FRAME;
	static const string netCommand_FORFEIT;

	//ArrayList<shared_ptr<PuzzlePlayer>>* bobsGameNetworkPlayers = make_shared<ArrayList><shared_ptr<PuzzlePlayer>>();

	void tellAllPeersOneOfMyPlayersForfeitsGame(shared_ptr<PuzzlePlayer >p);
	//void cancelNetworkGame();
	void tellHostPeerIAmJoiningTheirGame();
	void tellAllPeersIAmHosting();
	void tellAllPeersIAmNotHosting();
	void tellAllJoinedPeersThatANewPeerHasJoinedMyHostedGame(shared_ptr<UDPPeerConnection >c);
	void tellAllPeersIAmPlayingAGame();
	void tellAllJoinedPeersIHaveCanceledMyHostedGame();
	void tellAllJoinedPeersMyHostedGameHasStarted();
	void tellAllJoinedPeersIHaveLeftTheGame();
	void tellAllJoinedPeersOneOfMyPlayersHasLeftTheLobby(shared_ptr<PuzzlePlayer >p);
	void tellAllJoinedPeersOneOfMyPlayersHasJoinedTheLobby(shared_ptr<PuzzlePlayer >p);
	void tellPeerThatOtherPeerHasJoined(shared_ptr<UDPPeerConnection> peerToTell, shared_ptr<UDPPeerConnection> joinedPeer);
	void tellPeerThatIHaveJoined(shared_ptr<UDPPeerConnection> peerToTell);
	void tellPeerThatPlayerHasJoined(shared_ptr<UDPPeerConnection> peerToTell, shared_ptr<PuzzlePlayer >p);
	void tellPeerThatPlayerHasConfirmedAndSendGameSequence(shared_ptr<UDPPeerConnection> peerToTell, shared_ptr<PuzzlePlayer >p);
	void tellAllPeersThatPlayerHasConfirmedAndSendGameSequence(shared_ptr<PuzzlePlayer >p);
	void tellServerIAmHostingOrUpdateRoomStatus(const string& roomDescription);
	void tellServerIHaveCanceledTheGame(const string& roomUUID);
	void tellServerIHaveStartedTheGame(const string& roomUUID);
	void tellServerTheGameHasEnded(const string& roomUUID, const string& results);
	static void getUserIDAndRandomSeedAndUUIDFromPlayerIDString(string s, long long &userID, long long &randomSeed, string& uuid);
	virtual bool udpPeerMessageReceived(shared_ptr<UDPPeerConnection >c, string s) override;

  
	static ArrayList<shared_ptr<GameType>> loadedGameTypes;
	static ArrayList<shared_ptr<GameSequence>> loadedGameSequences;
	static ArrayList<shared_ptr<Sprite>> loadedSprites;
	void loadGameSequencesFromXML();
	void loadGameTypesFromXML();

	static void saveRoomConfigToFile(shared_ptr<Room> currentRoom, string name);
	static ArrayList<string> getRoomConfigsList();
	static shared_ptr<Room> loadRoomConfig(string configName);

	static void saveUnknownGameSequencesAndTypesToXML(shared_ptr<GameSequence >gs);
	static void saveGameSequenceToXML(shared_ptr<GameSequence >gs, bool downloaded);
	static void saveGameTypeToXML(shared_ptr<GameType >gt, bool downloaded);
	static void loadGameSequenceUUIDsToGamesArray(shared_ptr<GameSequence >g);
	static shared_ptr<GameType> getGameTypeByName(string name);
	static shared_ptr<GameType> getGameTypeByUUID(string uuid);
	static shared_ptr<GameSequence> getGameSequenceByName(string name);
	static shared_ptr<GameSequence> getGameSequenceByUUID(string uuid);

	void increaseVolume();
	void decreaseVolume();

	void updateVersion0ToVersion1();



	bool wasAuthorizedWhenSent = false;
	bool gotGamesFromServer = false;
	bool sentHighScoresAndLeaderboardsRequestWhileLoggedIn = false;
	bool sentServerGamesRequest = false;
	long long lastCheckedGamesFromServerTime = 0;
	void getGameTypesAndSequencesFromServer();
	static void parseIncomingGameTypesAndSequencesFromServer_S(string &s);
	

	//------------------------------------

private:
	static queue<shared_ptr<GameType>> _incomingGameTypes;
	static mutex _incomingGameTypes_Mutex;
public:
	static int incomingGameTypesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		return (int)_incomingGameTypes.size();
	}
	static shared_ptr<GameType> incomingGameTypesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		shared_ptr<GameType >g = _incomingGameTypes.front();
		_incomingGameTypes.pop();
		return g;
	}
	static void incomingGameTypesQueuePush_S(shared_ptr<GameType >p)
	{
		lock_guard<mutex> lock(_incomingGameTypes_Mutex);
		_incomingGameTypes.push(p);
	}
	//------------------------------------

	//------------------------------------

private:
	static queue<shared_ptr<GameSequence>> _incomingGameSequences;
	static mutex _incomingGameSequences_Mutex;
public:
	static int incomingGameSequencesQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		return (int)_incomingGameSequences.size();
	}
	static shared_ptr<GameSequence> incomingGameSequencesQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		shared_ptr<GameSequence >g = _incomingGameSequences.front();
		_incomingGameSequences.pop();
		return g;
	}
	static void incomingGameSequencesQueuePush_S(shared_ptr<GameSequence >p)
	{
		lock_guard<mutex> lock(_incomingGameSequences_Mutex);
		_incomingGameSequences.push(p);
	}
	//------------------------------------

	//------------------------------------
	private:
		static bool _gotIncomingGamesFromServer;
		static mutex _gotIncomingGamesFromServer_Mutex;
public:
	static void setGotIncomingGamesFromServer_S(bool b)
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		_gotIncomingGamesFromServer = b;
	}
	static bool getAndResetGotIncomingGamesFromServer_S()
	{
		lock_guard<mutex> lock(_gotIncomingGamesFromServer_Mutex);
		if(_gotIncomingGamesFromServer)
		{
			_gotIncomingGamesFromServer = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------

	long long lastCheckedGotIncomingGamesFromServerTime = 0;
};


