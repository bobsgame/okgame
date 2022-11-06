//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
enum class MovementType;
class Logger;


class GameLogic;
class Block;
class Piece;
class BlockType;
class PieceType;
class GameType;

//=========================================================================================================================
class Grid
{//=========================================================================================================================
public:

	static Logger log;

	//Color noColor;
	//PieceType noPieceType;
	//BlockType noBlockType;
	//ArrayList<Color> emptyColors;

	shared_ptr<GameLogic> game = nullptr;

	float screenX = 0;
	float screenY = 0;

//#define blockHashMap

#ifdef blocksHashMap
	HashMap<int, shared_ptr<Block>>* blocks = make_shared<HashMap><int, shared_ptr<Block>>();
#else
	ArrayList<shared_ptr<Block>> blocks;
#endif

	static shared_ptr<Block> nullBlock;

private:
	int wigglePlayingFieldTicksSpeed = 60;
	int wigglePlayingFieldMaxX = 0;
	int wigglePlayingFieldMaxY = 0;
	float wigglePlayingFieldX = 0;
	float wigglePlayingFieldY = 0;
	long long wigglePlayingFieldTicks = 0;
	bool wigglePlayingFieldLeftRightToggle = false;

	int shakePlayingFieldScreenTicksCounter = 0;
	long long shakePlayingFieldStartTime = 0;
	int shakePlayingFieldTicksDuration = 0;
	int shakePlayingFieldMaxX = 0;
	int shakePlayingFieldMaxY = 0;
	int shakePlayingFieldTicksPerShake = 0;
	int shakePlayingFieldTicksPerShakeXCounter = 0;
	bool shakePlayingFieldLeftRightToggle = false;
	int shakePlayingFieldTicksPerShakeYCounter = 0;
	bool shakePlayingFieldUpDownToggle = false;
	int shakePlayingFieldX = 0;
	int shakePlayingFieldY = 0;
	void setShakePlayingField(int ticksDuration, int maxX, int maxY, int ticksPerShake);
	void updateShake();

//	long long effectShakeDurationTicks = 0;
//	long long effectShakeTicksCounter = 0;
//	int effectShakeMaxX = 0;
//	int effectShakeMaxY = 0;
//	int effectShakeX = 0;
//	int effectShakeY = 0;

public:
	float scrollPlayingFieldY = 0; //for stack based games
	float scrollBlockIncrement = 60; //for stack based games

private:
	int scrollPlayingFieldBackgroundTicksSpeed = 30;
	int backgroundScrollX = 0;
	int backgroundScrollY = 0;
	long long scrollPlayingFieldBackgroundTicks = 0;

	int deadX = 0;
	int deadY = 0;

public:
	int lastGarbageHoleX = 0;
	bool garbageHoleDirectionToggle = true;
	ArrayList<shared_ptr<Piece>> randomBag;;
	Grid(shared_ptr<GameLogic> gameInstance);
	float getXInFBO();
	float getXInFBONoShake();
	float getXOnScreenNoShake();
	float getYInFBO();
	float getYInFBONoShake();
	float getYOnScreenNoShake();
	float bgX();
	float bgY();
	int getHeight();
	int getWidth();
	void update();
	void reformat(int oldWidth, int oldHeight);
	int getNumberOfFilledCells();
	void removeAllBlocksOfPieceFromGrid(shared_ptr<Piece> p, bool fadeOut);
	void replaceAllBlocksWithNewGameBlocks();
	shared_ptr<Piece> dontPutSameColorDiagonalOrNextToEachOtherReturnNull(shared_ptr<Piece> p, int x, int y, ArrayList<shared_ptr<PieceType>> &pieceTypes, ArrayList<shared_ptr<BlockType>> &blockTypes);
	shared_ptr<Piece> dontPutSameColorNextToEachOtherOrReturnNull(shared_ptr<Piece> p, int x, int y, ArrayList<shared_ptr<PieceType>> &pieceTypes, ArrayList<shared_ptr<BlockType>> &blockTypes);
	shared_ptr<Piece> dontPutSameBlockTypeNextToEachOtherOrReturnNull(shared_ptr<Piece> p, int x, int y, ArrayList<shared_ptr<PieceType>> &pieceTypes, ArrayList<shared_ptr<BlockType>> &blockTypes);
	void removeAndDestroyAllBlocksInGrid();
	shared_ptr<Piece> putOneBlockPieceInGridCheckingForFillRules(int x, int y, ArrayList<shared_ptr<PieceType>> &pieceTypes, ArrayList<shared_ptr<BlockType>> &blockTypes);
	void randomlyFillGridWithPlayingFieldPieces(int numberOfBlocks, int topY);
	void buildRandomStackRetainingExistingBlocks(int numberOfBlocks, int topY);
	bool scrollUpStack(shared_ptr<Piece> cursorPiece, int amt);
	shared_ptr<Piece> putGarbageBlock(int x, int y);
	void makeGarbageRowFromCeiling();
	void moveAllRowsUpOne();
	void putGarbageBlockFromFloor(int x, int y);
	void makeGarbageRowFromFloor();
	void cursorSwapBetweenTwoBlocksHorizontal(shared_ptr<Piece> cursor);
	void cursorSwapBetweenTwoBlocksVertical(shared_ptr<Piece> cursor);
	void cursorSwapBetweenThreeBlocksHorizontal(shared_ptr<Piece> cursor, MovementType rotation);
	void cursorSwapBetweenThreeBlocksVertical(shared_ptr<Piece> cursor, MovementType rotation);
	void cursorSwapHoldingBlockWithGrid(shared_ptr<Piece> cursor);
	void cursorRotateBlocks(shared_ptr<Piece> cursor, MovementType rotation);
	bool continueSwappingBlocks();
	void scrollBackground();
	void shakeSmall();
	void shakeMedium();
	void shakeHard();
	void wigglePlayingField();
	void add(int x, int y, shared_ptr<Block> b);
	bool contains(int index);
	bool contains(int x, int y);
	shared_ptr<Block> get(int x, int y);

private:
	shared_ptr<Block> remove(int x, int y, bool fadeOut, bool breakConnections);

public:
	void remove(shared_ptr<Block> b, bool fadeOut, bool breakConnections);
	void moveToAndRemoveAndFadeOut(shared_ptr<Block> b, int x, int y);
	bool checkLine(int y);
	ArrayList<shared_ptr<Piece>> getArrayOfPiecesOnGrid();
	ArrayList<shared_ptr<Block>> checkLines(ArrayList<shared_ptr<BlockType>> &ignoreTypes, ArrayList<shared_ptr<BlockType>> &mustContainAtLeastOneTypes);
	bool doBlocksMatchColor(shared_ptr<Block> a, shared_ptr<Block> b, ArrayList<shared_ptr<BlockType>> &ignoreTypes);
	ArrayList<shared_ptr<Block>> getConnectedBlocksUpDownLeftRight(shared_ptr<Block> b);
	void checkRecursiveConnectedRowOrColumn(ArrayList<shared_ptr<Block>> &connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, ArrayList<shared_ptr<BlockType>> &ignoreTypes, ArrayList<shared_ptr<BlockType>> &mustContainAtLeastOneTypes);
	void setColorConnections(ArrayList<shared_ptr<BlockType>> &ignoreTypes);// , ArrayList<shared_ptr<BlockType>>* mustContainAtLeastOneTypes);
	ArrayList<shared_ptr<Block>> checkBreakerBlocks(int toRow, ArrayList<shared_ptr<BlockType>> &ignoreUnlessTouchingBreakerBlockTypes, ArrayList<shared_ptr<BlockType>> &breakerBlockTypes);
	void recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(shared_ptr<Block> b, ArrayList<shared_ptr<Block>> &connectedBlocks, ArrayList<shared_ptr<BlockType>> &ignoreTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(shared_ptr<Block> b, ArrayList<shared_ptr<Block>> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<shared_ptr<BlockType>> &ignoreTypes, ArrayList<shared_ptr<BlockType>> &mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(shared_ptr<Block> b, ArrayList<shared_ptr<Block>> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<shared_ptr<BlockType>> &ignoreTypes, ArrayList<shared_ptr<BlockType>> &mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(shared_ptr<Block> b, ArrayList<shared_ptr<Block>> &connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, ArrayList<shared_ptr<BlockType>> &ignoreTypes, ArrayList<shared_ptr<BlockType>> &mustContainAtLeastOneTypes);
	void renderBackground();
	void render();
	void renderBlockOutlines();
	void renderBorder();
	void renderTransparentOverLastRow();
	void renderGhostPiece(shared_ptr<Piece> currentPiece);
	bool isWithinBounds(shared_ptr<Piece> piece, int x, int y);
	bool isHittingLeft(shared_ptr<Piece> piece);
	bool isHittingLeft(shared_ptr<Piece> piece, int x, int y);
	bool isHittingRight(shared_ptr<Piece> piece);
	bool isHittingRight(shared_ptr<Piece> piece, int x, int y);
	bool doesPieceFit(shared_ptr<Piece> piece);
	bool doesPieceFit(shared_ptr<Piece> piece, int x, int y);
	void setPiece(shared_ptr<Piece> piece);
	void setPiece(shared_ptr<Piece> piece, int x, int y);
	bool moveDownLinesAboveBlankLinesOneLine();
	bool moveDownDisconnectedBlocksAboveBlankSpacesOneLine(ArrayList<shared_ptr<BlockType>> &ignoreTypes);
	bool moveDownAnyBlocksAboveBlankSpacesOneLine(ArrayList<shared_ptr<BlockType>> &ignoreTypes);
	void setRandomBlockColors();
	void setRandomMatrixBlockColors();
	void setRandomWholePieceColors(bool grayscale, shared_ptr<Piece> currentPiece, ArrayList<shared_ptr<Piece>> &nextPieces);
	void setRandomPieceGrayscaleColors(shared_ptr<Piece> currentPiece, ArrayList<shared_ptr<Piece>> &nextPieces);
	bool isAnythingAboveThreeQuarters();
	void doDeathSequence();
	shared_ptr<PieceType> getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(ArrayList<shared_ptr<PieceType>> &arr);
	shared_ptr<PieceType> getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(ArrayList<shared_ptr<PieceType>> &arr);
	ArrayList<shared_ptr<Piece>> getBagOfOneOfEachNonRandomNormalPieces();
	shared_ptr<Piece> getPieceFromNormalPieceRandomBag();
	shared_ptr<Piece> getRandomPiece();
	shared_ptr<Piece> getRandomPiece(ArrayList<shared_ptr<PieceType>> &pieceArray, ArrayList<shared_ptr<BlockType>> &blockArray);
	shared_ptr<PieceType> getRandomPieceType(ArrayList<shared_ptr<PieceType>> &arr);
	shared_ptr<BlockType> getRandomBlockType(ArrayList<shared_ptr<BlockType>> &arr);
	shared_ptr<BlockType> getRandomBlockTypeDisregardingSpecialFrequency(ArrayList<shared_ptr<BlockType>> &arr);
	shared_ptr<BlockType> getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(ArrayList<shared_ptr<BlockType>> &arr);
	shared_ptr<BlockType> getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(ArrayList<shared_ptr<BlockType>> &arr);
	bool areAnyBlocksPopping();
	int cellW();
	int cellH();
	shared_ptr<GameType> getGameType();
	shared_ptr<GameLogic> getGameLogic();
};

