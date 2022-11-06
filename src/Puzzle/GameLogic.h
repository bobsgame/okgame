//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
#include <thread>
#include <mutex>
#include <queue>
#include "GameSequence.h"
#include "Stats/UserStatsForSpecificGameAndDifficulty.h"
#include "Stats/LeaderBoardAndHighScoreBoardEntry.h"

class PuzzlePlayer;
class Logger;
class Room;
#include <random>

#include "./../../src/Engine/EnginePart.h"
#include "./../Utility/Caption.h"
#include "OKGame.h"
#include "GameType.h"
#include "Piece.h"
#include "Block.h"
#include "Grid.h"

class Logger;

//=========================================================================================================================
enum class MovementType
{//=========================================================================================================================
	UP,
	DOWN,
	RIGHT,
	LEFT,
	ROTATE_COUNTERCLOCKWISE,
	ROTATE_CLOCKWISE,
	ROTATE_180,
	HARD_DROP,
};

//
//enum class SideType
//{
//	LEFT,
//	RIGHT,
//	MIDDLE
//};

//
//class ControlsState
//{
//public:
//
//
//	template <typename Archive>
//	void serialize(Archive & ar, const unsigned int version)
//	{
//
//
//	}
//};

//=========================================================================================================================
class FrameState
{//=========================================================================================================================
public:
	//ControlsState controlsState;
	long long ticksPassed = 0;
	int receivedGarbageAmount = 0;
	bool ROTATECW_HELD = false;
	bool HOLDRAISE_HELD = false;
	bool ROTATECCW_HELD = false;
	bool UP_HELD = false;
	bool LEFT_HELD = false;
	bool DOWN_HELD = false;
	bool RIGHT_HELD = false;
	bool SLAM_HELD = false;
	string gridString;
	//string currentGameString;
	int randomInt = 0;
	//long long totalTicksPassed = 0;

	bool slamLock = true;
	bool singleDownLock = false;
	bool doubleDownLock = true;

	//DropLockType dropLockType = DropLockType::HARD_DROP_INSTANT_LOCK; 

	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================

		//ar & BOOST_SERIALIZATION_NVP(controlsState);
		ar & BOOST_SERIALIZATION_NVP(ticksPassed);
		ar & BOOST_SERIALIZATION_NVP(receivedGarbageAmount);
		ar & BOOST_SERIALIZATION_NVP(ROTATECW_HELD);
		ar & BOOST_SERIALIZATION_NVP(HOLDRAISE_HELD);
		ar & BOOST_SERIALIZATION_NVP(ROTATECCW_HELD);
		ar & BOOST_SERIALIZATION_NVP(UP_HELD);
		ar & BOOST_SERIALIZATION_NVP(LEFT_HELD);
		ar & BOOST_SERIALIZATION_NVP(DOWN_HELD);
		ar & BOOST_SERIALIZATION_NVP(RIGHT_HELD);
		ar & BOOST_SERIALIZATION_NVP(SLAM_HELD);
		ar & BOOST_SERIALIZATION_NVP(gridString);
		//ar & BOOST_SERIALIZATION_NVP(currentGameString);
		ar & BOOST_SERIALIZATION_NVP(randomInt);
		//ar & BOOST_SERIALIZATION_NVP(dropLockType);
		//ar & BOOST_SERIALIZATION_NVP(totalTicksPassed);
		ar & BOOST_SERIALIZATION_NVP(slamLock);
		ar & BOOST_SERIALIZATION_NVP(singleDownLock);
		ar & BOOST_SERIALIZATION_NVP(doubleDownLock);
	}

	//=========================================================================================================================
	static string getFrameStatesAsBase64LZ4XML(ArrayList<FrameState> &n)
	{ //=========================================================================================================================

		std::stringstream ss;
		boost::archive::xml_oarchive oarchive(ss);
		oarchive << BOOST_SERIALIZATION_NVP(n);
		string b64lz4 = FileUtils::lz4StringToBase64String(ss.str());
		return b64lz4;

	}

	//=========================================================================================================================
	static ArrayList<FrameState> getFramesArrayFromBase64LZ4XML(const string &b64LZ4XML)
	{ //=========================================================================================================================

		string xml = FileUtils::unlz4Base64StringToString(b64LZ4XML);

		if (xml == "" || xml.length() == 0)
		{
			return ArrayList<FrameState>();
		}

		stringstream ss;
		ss << xml;

		boost::archive::xml_iarchive ia(ss);
		ArrayList<FrameState> n;
		try
		{
			ia >> BOOST_SERIALIZATION_NVP(n);
		}
		catch (exception)
		{
			Main::log.error("Could not unserialize FramesArray");
		}

		return n;
	}

};
BOOST_CLASS_VERSION(FrameState, 1)
BOOST_CLASS_TRACKING(FrameState, boost::serialization::track_never)


//=========================================================================================================================
class GameLogic : public EnginePart
{//=========================================================================================================================
public:

	static Logger log;

	//static OKColor noColor;
	//static ArrayList<OKColor> emptyColors;

	shared_ptr<GameSequence >currentGameSequence = nullptr;
	shared_ptr<PuzzlePlayer> player = nullptr;

public:

	//CaptionManager captionManager;

	//virtual shared_ptr<CaptionManager> getCaptionManager() override;

	
	ArrayList<shared_ptr<GameType>> gameTypeRandomBag;
	shared_ptr<GameType> currentGameType = nullptr;//currentGameType

	shared_ptr<Grid> grid = nullptr;

	shared_ptr<OKGame> getOKGame();
	shared_ptr<Room> getRoom();

	int blockWidth = 1;
	int blockHeight = 1;

	static int aboveGridBuffer;
	//static int gameTypeCount;

	GameLogic(shared_ptr<Engine> g, long long seed);
	~GameLogic();

	void initializeRandomGenerator();
	void fillGameTypeRandomBag();
	shared_ptr<GameType> getGameTypeFromRandomBag();

	bool dontResetNextPieces = false;

private:
	long long lockInputCountdownTicks = 0;

	bool canPressRotateCW = false;
	bool canPressRotateCCW = false;
	bool canPressRight = false;
	bool canPressLeft = false;
	bool canPressDown = false;
	bool canPressUp = false;
	bool canPressHoldRaise = false;
	bool canPressSlam = false;

	long long ticksHoldingRotateCW = 0;
	long long ticksHoldingRotateCCW = 0;
	long long ticksHoldingRight = 0;
	long long ticksHoldingLeft = 0;
	long long ticksHoldingDown = 0;
	long long ticksHoldingUp = 0;
	long long ticksHoldingHoldRaise = 0;
	long long ticksHoldingSlam = 0;

	bool repeatStartedRotateCW = false;
	bool repeatStartedRotateCCW = false;
	bool repeatStartedHoldRaise = false;
	bool repeatStartedUp = false;
	bool repeatStartedDown = false;
	bool repeatStartedLeft = false;
	bool repeatStartedRight = false;
	bool repeatStartedSlam = false;

	int timesToFlashBlocks = 20;
	long long flashBlockSpeedTicks = 30;

	long long flashScreenSpeedTicks = 50;
	int flashScreenTimesPerLevel = 4;

public:
	bool won = false;
	bool lost = false;

	bool died = false;
private:
	bool startedDeathSequence = false;
	bool startedWinSequence = false;
	bool startedLoseSequence = false;

public:
	bool complete = false;
private:
	bool creditScreenInitialized = false;
	bool firstInit = true;
public:
	bool didInit = false;

	bool madeBeginnerStackAnnouncement = false;

private:
	bool extraStage1 = false;
	bool extraStage2 = false;
	bool extraStage3 = false;
	bool extraStage4 = false;
	long extraStageTicksPassed = 0;//TODO:

	bool gravityThisFrame = false;

	bool pieceSetAtBottom = false;
	bool switchedHoldPieceAlready = false;
	bool playingFastMusic = false;
	bool firstDeath = false;

	float gameSpeed = 0.0f;
	long long currentLineDropSpeedTicks = 0;
	long long currentStackRiseSpeedTicks = 0;
	long long lockDelayTicksCounter = 0;
	long long lineDropTicksCounter = 0;
	long long spawnDelayTicksCounter = 0;
	long long lineClearDelayTicksCounter = 0;
	long long moveDownLineTicksCounter = 0;

	long long currentTotalYLockDelay = 0;
	long long adjustedMaxLockDelayTicks = 0;
	long long adjustedSpawnDelayTicksAmount = 0;
	long long currentFloorMovements = 0;

	string playingMusic = "";

	//used for panel
	long long stackRiseTicksCounter = 0;
	long long stopStackRiseTicksCounter = 0;
	long long manualStackRiseTicksCounter = 0;
	int manualStackRiseSoundToggle = 0;

	int timesToFlashScreenQueue = 0;
	long long flashScreenTicksCounter = 0;
	bool flashScreenOnOffToggle = false;

	long long flashBlocksTicksCounter = 0;
	int timesToFlashBlocksQueue = 0;
	long long removeBlocksTicksCounter = 0;
	ArrayList<shared_ptr<Block>> currentChainBlocks;
public:
	ArrayList<shared_ptr<Block>> fadingOutBlocks;

	shared_ptr<Piece> currentPiece = nullptr;
	shared_ptr<Piece> lastPiece = nullptr;

	shared_ptr<Piece> holdPiece = nullptr;
	ArrayList<shared_ptr<Piece>> nextPieces;
	ArrayList<shared_ptr<Piece>> nextPieceSpecialBuffer;

	int lastKnownLevel = 0;
	int currentLevel = 0;

	int piecesMadeThisGame = 0;
	int lastPiecesMadeThisGame = 0;
	int blocksClearedThisGame = 0;
	int linesClearedThisGame = 0;

	int piecesMadeThisLevel = 0;
	int blocksClearedThisLevel = 0;
	int linesClearedThisLevel = 0;

	int blocksMadeTotal = 0;
	int piecesMadeTotal = 0;
	int piecesPlacedTotal = 0;
	int lastPiecesMadeTotal = 0;//TODO:
	int blocksClearedTotal = 0;
	int linesClearedTotal = 0;

	long long timeStarted = 0;
	long long timeEnded = 0;
	long long lastTicksPassed = 0;
	long long totalTicksPassed = 0;
public:
	int createdPiecesCounterForFrequencyPieces = 0;

private:
	bool waitingForStart = true;
	bool waitingForReady = true;
	bool playedReadySound = false;
	long long readyTicksCounter = 0;

	long long playingFieldGarbageValueCounter = 0;

public:
	bool forceGravityThisFrame = false;
	string previousGameString = "";
	//string currentGameString = "";
private:
	//GameType currentGameType = (GameType)0;

	bool mute = false;

	int currentChain = 0;
	int currentCombo = 0;
	int comboChainTotal = 0;

public:
	int totalCombosMade = 0;
	int biggestComboChain = 0;

public:
	//only used for local multiplayer games, specific network garbage rules must be coordinated by server
	int lastSentGarbageToPlayerIndex = 0;

	int queuedVSGarbageAmountToSend = 0;

private:
	int queuedVSGarbageAmountFromOtherPlayer = 0;
	int garbageWaitForPiecesSetCount = 0;

	//shared_ptr<Block> garbageBlock = nullptr;

	bool checkForChainAgainIfNoBlocksPopping = false;

public:
	void setGameType(shared_ptr<GameType> gameType);
	shared_ptr<DifficultyType> getCurrentDifficulty();
private:
	void initGame();

public:
	//void setGridXY(shared_ptr<PuzzlePlayer >p, int gameIndex, int numGames);

private:
	void flashScreen();
	void flashChainBlocks();
	void removeFlashedChainBlocks();
	void updateSpecialPiecesAndBlocks();
	void waitForPressStart();
	void waitForReady();

public:
	bool testing = true; //turn me off to restore "press start"
	void update(int gameIndex, int numGames, float forceWidth = 0, float forceHeight = 0);

private:
	void setControlsState();


private:
	void processFrame();
	void addToChainBlocks(ArrayList<shared_ptr<Block>> &arr);
	bool detectedChain();
	void checkForChain();

	//need to add queuedGarbageAmountToSend to queuedGarbageAmountFromOtherPlayer when received in frame
	//need to add "ReceivedGarbageAmount" to frame state

	void handleNewChain();
	//float getStackRiseBasedOnCurrentLineDropSpeedTicks();
	void doStackRiseGame();
	void doFallingBlockGame();
public:
	void manuallyApplyGravityWithoutChainChecking();

private:
	bool moveDownBlocksOverBlankSpaces();
	void pieceMoved();

public:
	bool movePiece(MovementType move);

private:
	void setCurrentPieceAtTop();
	void setPiece();
	void newRandomPiece();

	//need to add queuedGarbageAmountToSend to queuedGarbageAmountFromOtherPlayer when received in frame
	//need to add "ReceivedGarbageAmount" to frame state

public:
	void gotVSGarbageFromOtherPlayer(int amount);
	void processQueuedGarbageSentFromOtherPlayer();
	void queueVSGarbageToSend(int amount);

private:
	void processGarbageRules();
	void makeGarbageRowFromFloor();
	void makeGarbageRowFromCeiling();

	//	private void renderBackground()
	//	{
	//
	//		if(side==OKGame::LEFT)
	//		{
	//			// fill screen with black
	//			GLUtils::drawFilledRectXYWH(0,0,getWidth()/2,getHeight(),GameType().screenBackgroundColor.r(),GameType().screenBackgroundColor.g(),GameType().screenBackgroundColor.b(),1.0f);
	//		}
	//		else
	//		{
	//			GLUtils::drawFilledRectXYWH(getWidth()/2,0,getWidth()/2,getHeight(),GameType().screenBackgroundColor.r(),GameType().screenBackgroundColor.g(),GameType().screenBackgroundColor.b(),1.0f);
	//		}
	//
	//		//TODO: winamp style visualizations, milkdrop, geiss, fractals, electric sheep, maybe grab movie of old shaders, stepmania?
	//
	//	}

	void renderQueuedGarbage();
	void renderHoldPiece();
	bool nextPieceEnabled();
	void renderNextPiece();
	void renderCurrentPiece();
	void renderOverlays();

public:
	void renderBackground();
	void renderBlocks();
	void renderForeground();
	void renderHighScoreMeters();
	void showResultsRanking();

private:
	void doExtraStageEffects();
	string getRandomMakePieceSound();
	float getSoundEffectSpeed();
	float getVolume();
	void checkForFastMusic();

public:
	void updateKeyInput();

private:
	void wonSequence();
	void lostSequence();
	void diedSequence();
	void creditsSequence();

	//---------------------------------------------------
	// captions
	//----------------------------------------------------

	float captionY = -1;
	float captionX = 0;
public:

	float playingFieldX0 = 0;
	float playingFieldX1 = 0;
	float playingFieldY0 = 0;
	float playingFieldY1 = 0;
private:

	float captionColorCycleHueValue = 0;
	bool captionColorCycleHueInOutToggle = false;

	float captionScale = 1.0f;
	int captionYSize = (int)(14 * 1.0f); // captionScale);

	shared_ptr<OKColor> captionTextColor = nullptr;// = Color::white;
	shared_ptr<OKColor> captionBGColor = nullptr;// = Color::black;
	int captionFontSize = 0;// = OKFont::font_normal_8;

	float announcementCaptionScale = 0.3f;
	shared_ptr<OKColor> announcementCaptionTextColor = nullptr;// = Color::white;
	shared_ptr<OKColor> announcementCaptionBGColor = nullptr;// = Color::clear;
	int announcementCaptionFontSize = 0;// = OKFont::font_32;
	int resultCaptionFontSize = 0;// = OKFont::font_32;

	int mediumCaptionFontSize = 0;// = OKFont::font_normal_16_outlined_smooth;

public:
	shared_ptr<Caption> levelCaption = nullptr;
	string levelCaptionText = "levelCaptionText";

	shared_ptr<Caption> gameTypeCaption = nullptr;
	shared_ptr<Caption> rulesCaption1 = nullptr;
	shared_ptr<Caption> rulesCaption2 = nullptr;
	shared_ptr<Caption> rulesCaption3 = nullptr;

	shared_ptr<Caption> difficultyCaption = nullptr;
	//string difficultyCaptionText = "difficultyCaptionText";

	shared_ptr<Caption> stopCounterCaption = nullptr;
	string stopCounterCaptionText = "Go!";

	shared_ptr<Caption> xCaption = nullptr;
	shared_ptr<Caption> yCaption = nullptr;
	shared_ptr<Caption> lineDropTicksCaption = nullptr;
	shared_ptr<Caption> lockDelayCaption = nullptr;
	shared_ptr<Caption> spawnDelayCaption = nullptr;
	shared_ptr<Caption> lineClearDelayCaption = nullptr;
	shared_ptr<Caption> gravityCaption = nullptr;
	shared_ptr<Caption> rotationCaption = nullptr;
	shared_ptr<Caption> holdCaption = nullptr;
	shared_ptr<Caption> nextCaption = nullptr;

	shared_ptr<Caption> totalLinesClearedCaption = nullptr;
	shared_ptr<Caption> totalBlocksClearedCaption = nullptr;
	shared_ptr<Caption> totalPiecesMadeCaption = nullptr;

	shared_ptr<Caption> linesClearedThisGameCaption = nullptr;
	shared_ptr<Caption> blocksClearedThisGameCaption = nullptr;
	shared_ptr<Caption> piecesMadeThisGameCaption = nullptr;

	shared_ptr<Caption> blocksInGridCaption = nullptr;
	shared_ptr<Caption> currentChainCaption = nullptr;
	shared_ptr<Caption> currentComboCaption = nullptr;
	shared_ptr<Caption> comboChainTotalCaption = nullptr;
	shared_ptr<Caption> seedCaption = nullptr;
	shared_ptr<Caption> bgCaption = nullptr;

	shared_ptr<Caption> piecesToLevelUpThisLevelCaption = nullptr;
	shared_ptr<Caption> piecesLeftToLevelUpCaption = nullptr;

private:
	ArrayList<shared_ptr<Caption>> infoCaptions;// = make_shared<ArrayList><shared_ptr<Caption>>();
	ArrayList<shared_ptr<Caption>> announcementCaptions;// = make_shared<ArrayList><shared_ptr<Caption>>();

public:
	shared_ptr<Caption> totalTicksPassedCaption = nullptr;
private:
	int timeCaptionStandardizedWidth = 0;

public:
	shared_ptr<Caption> pressStartCaption = nullptr;
	shared_ptr<Caption> waitingForPlayerCaption = nullptr;
	shared_ptr<Caption> creditsCaption = nullptr;
	shared_ptr<Caption> deadCaption = nullptr;
	shared_ptr<Caption> winCaption = nullptr;
	shared_ptr<Caption> loseCaption = nullptr;
	shared_ptr<Caption> garbageWaitCaption = nullptr;

	shared_ptr<OKGameUserStatsForSpecificGameAndDifficulty >myHighScore = nullptr;
	OKGameLeaderBoardAndHighScoreBoard::OKGameLeaderBoardAndHighScoreBoardEntry *currentLeaderboardEntry = nullptr;
	bool triedToGetHighScore = false;
	shared_ptr<Caption> scoreBarTypeCaption = nullptr;
	shared_ptr<Caption> myScoreBarCaption = nullptr;
	shared_ptr<Caption> myHighScoreBarCaption = nullptr;
	shared_ptr<Caption> leaderboardBarCaption = nullptr;

	//lines cleared
	//blocks cleared
	//dobules
	//triples
	//tetrises

	//pieces
	//blocks

	//moves total
	//moves left
	//moves right
	//rotations cw
	//rotations ccw

	//hard drops
	//soft drops
	//spins
	//tspins
	//wallkicks
	//floor kicks

	//time

	//stackrise

	//combos
	//chains

	//garbage

private:
	void makeAnnouncementCaption(const string& text);
	void makeAnnouncementCaption(const string& text, shared_ptr<OKColor> color);
	void makeRandomLevelUpCaption();
	void updateCaptionFadeValues();
	shared_ptr<Caption> makeInfoCaption(const string& text);

public:
	void deleteAllCaptions();

	void deleteScoreBarCaptions();
	void deleteInfoCaptions();
	void updateInfoCaptionsXY();
	void updateCaptions();

public:
	void resetNextPieces();
	void changeGame();

public:
	void updateScore();

	//long long engineTicksPassed();
	//shared_ptr<GameType> getGameType();
	//void setCurrentGameType(shared_ptr<GameType> settings);
	int getRandomIntLessThan(int i, string whereCalledFrom);
	int cellW();
	int cellH();
	int gridW();
	int gridH();

public:


	long long ticks();
	shared_ptr<FrameState> getFrameState();



	//-----------------
	//networking
	//-----------------

	bool isNetworkPlayer = false;

	ArrayList<FrameState> framesArray;
	FrameState frameState;

	long long randomSeed = -1;
	string uuid = "";
	mt19937 randomGenerator;
	

	int lastSentPacketID = 0;

	typedef ArrayList<string> ArrayListString;
	ArrayListString outboundPacketQueueVector;
	
	typedef HashMap<string, string> HashMapStringString;
	HashMapStringString outboundPacketQueueHashMap;

	long long lastIncomingFramePacketID = 0;
	long long storePacketsTicksCounter = 0;

	typedef ArrayList<FrameState> FrameStateArray;
	ArrayList<FrameStateArray> allNetworkPacketsSentUpUntilNow;

	void sendPacketsToOtherPlayers();
	bool waitingForNetworkFrames = true;

	void incoming_FramePacket(const string &s);

	long long checkLastTrafficTime = 0;
	long long lastIncomingTrafficTime = 0;
	bool theyForfeit = false;
	long long getLastTimeGotIncomingTraffic();
	void setLastTimeGotIncomingTraffic();
	bool getTheyForfeit();
	void setTheyForfeit(bool b);

	bool pauseMiniMenuShowing = false;


	//------------------------------------
	//threading
	//------------------------------------

	ArrayListString _gotPacketsLog;
	bool packetProcessThreadStarted = false;
	thread packetProcessThread;
	static void _packetProcessThreadLoop(shared_ptr<GameLogic >g);
	void _processIncomingPackets();
private:
		bool _stopThread = false;
		mutex _stopThread_Mutex;
public:
	bool getStopThread_S()
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		return _stopThread;
	}
	void setStopThread_S(bool b)
	{
		lock_guard<mutex> lock(_stopThread_Mutex);
		_stopThread = b;
	}

	//------------------------------------

private:
	queue<string> *_incomingPacketQueue = new queue<string>();
	mutex _incomingPacketQueue_Mutex;
public:
	string incomingPacketQueueFront_S()
	{
		lock_guard<mutex> lock(_incomingPacketQueue_Mutex);
		return _incomingPacketQueue->front();
	}
	int incomingPacketQueueSize_S()
	{
		lock_guard<mutex> lock(_incomingPacketQueue_Mutex);
		return (int)_incomingPacketQueue->size();
	}
	void incomingPacketQueuePop_S()
	{
		lock_guard<mutex> lock(_incomingPacketQueue_Mutex);
		_incomingPacketQueue->pop();
	}
	void incomingPacketQueuePush_S(const string &p)
	{
		lock_guard<mutex> lock(_incomingPacketQueue_Mutex);
		_incomingPacketQueue->push(p);
	}

	//------------------------------------
private:
	typedef ArrayList<FrameState> ArrayListFrameState;
	typedef HashMap<long long, ArrayListFrameState> HashMapLongLongArrayListFrameState;
	HashMapLongLongArrayListFrameState _incomingFramePackets;
	mutex _incomingFramePackets_Mutex;
public:
	ArrayListFrameState incomingFramePacketsGet_S(long long k)
	{
		lock_guard<mutex> lock(_incomingFramePackets_Mutex);
		return _incomingFramePackets.get(k);
	}
	int incomingFramePacketsSize_S()
	{
		lock_guard<mutex> lock(_incomingFramePackets_Mutex);
		return _incomingFramePackets.size();
	}
	void incomingFramePacketsRemoveAt_S(long long k)
	{
		lock_guard<mutex> lock(_incomingFramePackets_Mutex);
		_incomingFramePackets.removeAt(k);
	}
	void incomingFramePacketsPut_S(long long k, ArrayListFrameState v)
	{
		lock_guard<mutex> lock(_incomingFramePackets_Mutex);
		_incomingFramePackets.put(k,v);
	}
	bool incomingFramePacketsContainsKey_S(long long k)
	{
		lock_guard<mutex> lock(_incomingFramePackets_Mutex);
		return _incomingFramePackets.containsKey(k);
	}
};

