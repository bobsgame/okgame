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
	//sp<vector<Color>>emptyColors;

	sp<GameLogic> game = nullptr;

	float screenX = 0;
	float screenY = 0;

//#define blockHashMap

#ifdef blocksHashMap
	HashMap<int, sp<Block>>* blocks = ms<HashMap><int, sp<Block>>();
#else
	sp<vector<sp<Block>>>blocks;
#endif

	static sp<Block> nullBlock;

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
	sp<vector<sp<Piece>>>randomBag;;
	Grid(sp<GameLogic> gameInstance);
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
	void removeAllBlocksOfPieceFromGrid(sp<Piece> p, bool fadeOut);
	void replaceAllBlocksWithNewGameBlocks();
	sp<Piece> dontPutSameColorDiagonalOrNextToEachOtherReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes);
	sp<Piece> dontPutSameColorNextToEachOtherOrReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes);
	sp<Piece> dontPutSameBlockTypeNextToEachOtherOrReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes);
	void removeAndDestroyAllBlocksInGrid();
	sp<Piece> putOneBlockPieceInGridCheckingForFillRules(int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes);
	void randomlyFillGridWithPlayingFieldPieces(int numberOfBlocks, int topY);
	void buildRandomStackRetainingExistingBlocks(int numberOfBlocks, int topY);
	bool scrollUpStack(sp<Piece> cursorPiece, int amt);
	sp<Piece> putGarbageBlock(int x, int y);
	void makeGarbageRowFromCeiling();
	void moveAllRowsUpOne();
	void putGarbageBlockFromFloor(int x, int y);
	void makeGarbageRowFromFloor();
	void cursorSwapBetweenTwoBlocksHorizontal(sp<Piece> cursor);
	void cursorSwapBetweenTwoBlocksVertical(sp<Piece> cursor);
	void cursorSwapBetweenThreeBlocksHorizontal(sp<Piece> cursor, MovementType rotation);
	void cursorSwapBetweenThreeBlocksVertical(sp<Piece> cursor, MovementType rotation);
	void cursorSwapHoldingBlockWithGrid(sp<Piece> cursor);
	void cursorRotateBlocks(sp<Piece> cursor, MovementType rotation);
	bool continueSwappingBlocks();
	void scrollBackground();
	void shakeSmall();
	void shakeMedium();
	void shakeHard();
	void wigglePlayingField();
	void add(int x, int y, sp<Block> b);
	bool contains(int index);
	bool contains(int x, int y);
	sp<Block> get(int x, int y);

private:
	sp<Block> remove(int x, int y, bool fadeOut, bool breakConnections);

public:
	void remove(sp<Block> b, bool fadeOut, bool breakConnections);
	void moveToAndRemoveAndFadeOut(sp<Block> b, int x, int y);
	bool checkLine(int y);
	sp<vector<sp<Piece>>> getArrayOfPiecesOnGrid();
	sp<vector<sp<Block>>> checkLines(sp<vector<sp<BlockType>>> ignoreTypes, sp<vector<sp<BlockType>>> mustContainAtLeastOneTypes);
	bool doBlocksMatchColor(sp<Block> a, sp<Block> b, sp<vector<sp<BlockType>>>ignoreTypes);
	sp<vector<sp<Block>>> getConnectedBlocksUpDownLeftRight(sp<Block> b);
	void checkRecursiveConnectedRowOrColumn(sp<vector<sp<Block>>>connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes);
	void setColorConnections(sp<vector<sp<BlockType>>>ignoreTypes);// , sp<vector<sp<BlockType>>>* mustContainAtLeastOneTypes);
	sp<vector<sp<Block>>> checkBreakerBlocks(int toRow, sp<vector<sp<BlockType>>>ignoreUnlessTouchingBreakerBlockTypes, sp<vector<sp<BlockType>>>breakerBlockTypes);
	void recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, sp<vector<sp<BlockType>>> ignoreTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes);
	void addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes);
	void renderBackground();
	void render();
	void renderBlockOutlines();
	void renderBorder();
	void renderTransparentOverLastRow();
	void renderGhostPiece(sp<Piece> currentPiece);
	bool isWithinBounds(sp<Piece> piece, int x, int y);
	bool isHittingLeft(sp<Piece> piece);
	bool isHittingLeft(sp<Piece> piece, int x, int y);
	bool isHittingRight(sp<Piece> piece);
	bool isHittingRight(sp<Piece> piece, int x, int y);
	bool doesPieceFit(sp<Piece> piece);
	bool doesPieceFit(sp<Piece> piece, int x, int y);
	void setPiece(sp<Piece> piece);
	void setPiece(sp<Piece> piece, int x, int y);
	bool moveDownLinesAboveBlankLinesOneLine();
	bool moveDownDisconnectedBlocksAboveBlankSpacesOneLine(sp<vector<sp<BlockType>>> ignoreTypes);
	bool moveDownAnyBlocksAboveBlankSpacesOneLine(sp<vector<sp<BlockType>>> ignoreTypes);
	void setRandomBlockColors();
	void setRandomMatrixBlockColors();
	void setRandomWholePieceColors(bool grayscale, sp<Piece> currentPiece, sp<vector<sp<Piece>>> nextPieces);
	void setRandomPieceGrayscaleColors(sp<Piece> currentPiece, sp<vector<sp<Piece>>>&nextPieces);
	bool isAnythingAboveThreeQuarters();
	void doDeathSequence();
	sp<PieceType> getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(sp<vector<sp<PieceType>>> arr);
	sp<PieceType> getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(sp<vector<sp<PieceType>>> arr);
	sp<vector<sp<Piece>>> getBagOfOneOfEachNonRandomNormalPieces();
	sp<Piece> getPieceFromNormalPieceRandomBag();
	sp<Piece> getRandomPiece();
	sp<Piece> getRandomPiece(sp<vector<sp<PieceType>>> pieceArray, sp<vector<sp<BlockType>>> blockArray);
	sp<PieceType> getRandomPieceType(sp<vector<sp<PieceType>>> arr);
	sp<BlockType> getRandomBlockType(sp<vector<sp<BlockType>>> arr);
	sp<BlockType> getRandomBlockTypeDisregardingSpecialFrequency(sp<vector<sp<BlockType>>> arr);
	sp<BlockType> getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(sp<vector<sp<BlockType>>> arr);
	sp<BlockType> getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(sp<vector<sp<BlockType>>> arr);
	bool areAnyBlocksPopping();
	int cellW();
	int cellH();
	sp<GameType> getGameType();
	sp<GameLogic> getGameLogic();
};

