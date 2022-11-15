//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------
#pragma once
#include "oktypes.h"
#include "OKGame.h"

class Logger;
class Grid;
class GameLogic;
class BlockType;
class Block;
class Rotation;
class GameType;

//=========================================================================================================================
enum class RotationType //static
{//=========================================================================================================================
	SRS,
	SEGA,
	NES,
	GB,
	DTET,
};

//=========================================================================================================================
class BlockOffset //static
{//=========================================================================================================================
public:
	int x = 0;
	int y = 0;

	//=========================================================================================================================
	bool operator==(const BlockOffset& rhs) const
	{//=========================================================================================================================
		return
			x == rhs.x
			&& y == rhs.y
			;
	}
	//=========================================================================================================================
	bool operator!=(const BlockOffset& rhs) const
	{//=========================================================================================================================
		return
			(*this == rhs) == false
			;
	}
	//=========================================================================================================================
	BlockOffset()
	{//=========================================================================================================================
		
	}
	//=========================================================================================================================
	BlockOffset(int x, int y)
	{//=========================================================================================================================
		this->x = x;
		this->y = y;
	}
	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================
		ar & BOOST_SERIALIZATION_NVP(x);
		ar & BOOST_SERIALIZATION_NVP(y);
	}
};

BOOST_CLASS_VERSION(BlockOffset, 1)
BOOST_CLASS_TRACKING(BlockOffset, boost::serialization::track_never)

//=========================================================================================================================
class Rotation //static
{//=========================================================================================================================

public:
	sp<vector<sp<BlockOffset>>>blockOffsets;
private:
	vector<BlockOffset>importExport_blockOffsets;
public:
	//=========================================================================================================================
	bool operator==(const Rotation& rhs) const
	{//=========================================================================================================================
		return
			blockOffsets == rhs.blockOffsets
			;
	}
	//=========================================================================================================================
	bool operator!=(const Rotation& rhs) const
	{//=========================================================================================================================
		return
			(*this == rhs) == false
			;
	}
	//=========================================================================================================================
	Rotation()
	{//=========================================================================================================================

	}
	//=========================================================================================================================
	void push_back(sp<BlockOffset> b)
	{//=========================================================================================================================
		blockOffsets->push_back(b);
	}
	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================
		//ar & BOOST_SERIALIZATION_NVP(blockOffsets);

		importExport_blockOffsets.clear();
		{
			for (int i = 0; i<blockOffsets->size(); i++)
			{
				sp<BlockOffset>b = blockOffsets->at(i);
				importExport_blockOffsets.push_back(*b);
			}
		}
		ar & BOOST_SERIALIZATION_NVP(importExport_blockOffsets);
		blockOffsets->clear();
		{
			for (int i = 0; i<importExport_blockOffsets.size(); i++)
			{
				BlockOffset b = importExport_blockOffsets.at(i);
				sp<BlockOffset>bp = ms<BlockOffset>(b);
				//*bp = b;
				blockOffsets->push_back(bp);
			}
		}
		importExport_blockOffsets.clear();
	}
};
BOOST_CLASS_VERSION(Rotation, 1)
BOOST_CLASS_TRACKING(Rotation, boost::serialization::track_never)

//=========================================================================================================================
class RotationSet
{//=========================================================================================================================

public:
	string name = "";

	sp<vector<sp<Rotation>>>rotationSet;
private:
	vector<Rotation>importExport_rotationSet;
public:
	//=========================================================================================================================
	RotationSet()
	{//=========================================================================================================================

	}
	//=========================================================================================================================
	RotationSet(string name)
	{//=========================================================================================================================
		this->name = name;
	}
	//=========================================================================================================================
	void push_back(sp<Rotation> r)
	{//=========================================================================================================================
		rotationSet->push_back(r);
	}

	int size() { return (int)rotationSet->size(); }
	sp<Rotation> at(int i) { return rotationSet->at(i); }
	void clear() { rotationSet->clear(); }
	void removeAt(int i) { rotationSet->erase(rotationSet->begin()+i); }

	//=========================================================================================================================
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{//=========================================================================================================================
		ar & BOOST_SERIALIZATION_NVP(name);
		//ar & BOOST_SERIALIZATION_NVP(rotationSet);

		importExport_rotationSet.clear();
		{
			for (int i = 0; i<rotationSet->size(); i++)
			{
				Rotation b = rotationSet->at(i);
				importExport_rotationSet.push_back(b);
			}
		}
		ar & BOOST_SERIALIZATION_NVP(importExport_rotationSet);
		rotationSet->clear();
		{
			for (int i = 0; i<importExport_rotationSet.size(); i++)
			{
				Rotation b = importExport_rotationSet.at(i);
				sp<Rotation>bp = ms<Rotation>(b);
				//*bp = b;
				rotationSet->push_back(bp);
			}
		}
		importExport_rotationSet.clear();
	}

};
BOOST_CLASS_VERSION(RotationSet, 1)
BOOST_CLASS_TRACKING(RotationSet, boost::serialization::track_never)

//=========================================================================================================================
class PieceType
{//=========================================================================================================================
public:

	string name = "";														Info name_Info = Info("Name", "Unique name of piece type.");
	string uuid = "";
	//int numBlocks = 1;
	//int lastRotation = 0;

	sp<OKColor>color = nullptr;												Info color_Info = Info("Color", "If this is set, the blocks in the piece will have this color, ONLY if the block does not have a color already.  If the piece is set to Special Flashing Type, it will override the block color until it turns back into a normal piece.");
private:
	OKColor importExport_color;
public:

	sp<RotationSet> rotationSet;												Info rotationSet_Info = Info("Block Placement And Rotation", "Design the layout of the blocks and rotation of the piece.");

	int frequencySpecialPieceTypeOnceEveryNPieces = 0;						Info frequencySpecialPieceTypeOnceEveryNPieces_Info = Info("Special Piece Type Once Every N Pieces", "This piece will be created once every n pieces.");
	int randomSpecialPieceChanceOneOutOf = 0;								Info randomSpecialPieceChanceOneOutOf_Info = Info("Special Piece Random Chance One Out Of", "This piece has a random chance of occuring 1 out of n times.");
	bool flashingSpecialType = false;										Info flashingSpecialType_Info = Info("Flashing Special Type", "This entire piece will flash, and if it is flashing any blocks that are cleared out of it will activate any special properties it is assigned.");
	bool clearEveryRowPieceIsOnIfAnySingleRowCleared = false;				Info clearEveryRowPieceIsOnIfAnySingleRowCleared_Info = Info("Special: Clear Every Row Piece Is On If Any Single Row Cleared", "If any block of this piece is cleared while it is flashing, clear every row that any block of this piece is on.");
	int turnBackToNormalPieceAfterNPiecesLock = -1;							Info turnBackToNormalPieceAfterNPiecesLock_Info = Info("Turn Back To Normal Piece After N Pieces Lock", "After n pieces are set at the bottom, remove any special properties from this piece.");
	bool fadeOutOnceSetInsteadOfAddedToGrid = false;						Info fadeOutOnceSetInsteadOfAddedToGrid_Info = Info("Fade Out Once Set Instead Of Added To Grid", "When this piece is placed down, fade it out and remove it instead of setting it into the grid.");

	bool useAsNormalPiece = false;											Info useAsNormalPiece_Info = Info("Use As Normal Piece", "This piece should be used as a normal piece when generating next pieces.  There must be at least one normal piece type.");
	bool useAsGarbagePiece = false;											Info useAsGarbagePiece_Info = Info("Use As Garbage Piece", "One block from this piece type and its properties will be used when creating garbage blocks from the bottom of the screen.");
	bool useAsPlayingFieldFillerPiece = false;								Info useAsPlayingFieldFillerPiece_Info = Info("Use As Playing Field Filler Piece", "One block from this piece type and its properties will be used when filling the playing field.");
	bool disallowAsFirstPiece = false;										Info disallowAsFirstPiece_Info = Info("Disallow As First Piece", "This piece cannot be the first piece.");

	string spriteName = "";													Info spriteName_Info = Info("Sprite Name", "The preset sprite graphics that this piece should use.  The sprite will cover the entire piece, overriding the individual block sprites.");

	bool bombPiece = false;													Info bombPiece_Info = Info("Bomb Piece", "This piece will explode when it is placed, destroying any surrounding blocks.");
	bool weightPiece = false;												Info weightPiece_Info = Info("Weight Piece", "This piece will slam down to the bottom of the grid, destroying any blocks in its path.");
	bool pieceRemovalShooterPiece = false;									Info pieceRemovalShooterPiece_Info = Info("Piece Removal Shooter Piece", "This piece will vacuum up blocks below it when the rotate button is pressed.");
	bool pieceShooterPiece = false;											Info pieceShooterPiece_Info = Info("Piece Shooter Piece", "This piece will create blocks below it when the rotate button is pressed.");

	//don't use!!! use uuid!
	sp<vector<sp<BlockType>>>overrideBlockTypes_DEPRECATED;					Info overrideBlockTypes_Info = Info("Override Block Types", "This piece will always be made with these blocks, not the randomly chosen normal type blocks.");
	sp<vector<string>>overrideBlockTypes_UUID;
private:
	//sp<vector<BlockType>>importExport_overrideBlockTypes;
public:

	bool operator==(const PieceType& rhs) const;
	bool operator!=(const PieceType& rhs) const;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version);
	

//	PieceType();
//	PieceType(sp<Color> color, int numBlocks, sp<vector<sp<Rotation>>>* rotationSet);
//	PieceType(sp<Color> color, int numBlocks, sp<vector<sp<Rotation>>>* rotationSet, int randomSpecialPieceChanceOneOutOf, int frequencySpecialPieceTypeOnceEveryNPieces);
//	PieceType(const string& spriteName, sp<Color> color, int numBlocks, sp<vector<sp<Rotation>>>* rotationSet, int randomSpecialPieceChanceOneOutOf, int frequencySpecialPieceTypeOnceEveryNPieces);
//	PieceType(int numBlocks, sp<vector<sp<Rotation>>>* rotationSet);

	static sp<PieceType> emptyPieceType;
	static sp<PieceType> oneBlockCursorPieceType;
	static sp<PieceType> twoBlockHorizontalCursorPieceType;
	static sp<PieceType> twoBlockVerticalCursorPieceType;
	static sp<PieceType> threeBlockHorizontalCursorPieceType;
	static sp<PieceType> threeBlockVerticalCursorPieceType;
	static sp<PieceType> fourBlockCursorPieceType;
	//=========================================================================================================================
	PieceType()
	{//=========================================================================================================================
		this->name = "empty";

		boost::uuids::random_generator generator;
		uuid = to_string(generator());

		//this->numBlocks = 1;
		//this->lastRotation = 0;

		sp<BlockOffset> b;// = ms<BlockOffset>(0, 0);
		sp<Rotation> r;// = ms<Rotation>();
		r->push_back(b);
		//rotationSet = ms<vector><sp<Rotation>>();
		rotationSet = ms<RotationSet>("");
		rotationSet->push_back(r);
	}

	//=========================================================================================================================
	PieceType(const string &name, const string& spriteName = "", sp<OKColor>color = nullptr, int numBlocks = 1, sp<RotationSet> rotationSet = ms<RotationSet>("") , int randomSpecialPieceChanceOneOutOf = 0, int frequencySpecialPieceTypeOnceEveryNPieces = 0)
	{//=========================================================================================================================
		this->name = name;

		boost::uuids::random_generator generator;
		uuid = to_string(generator());

		this->spriteName = spriteName;
		this->color = color;
		//this->numBlocks = numBlocks;
		this->rotationSet = rotationSet;
		//this->lastRotation = rotationSet->size() - 1;
		this->randomSpecialPieceChanceOneOutOf = randomSpecialPieceChanceOneOutOf;
		this->frequencySpecialPieceTypeOnceEveryNPieces = frequencySpecialPieceTypeOnceEveryNPieces;
	}


};

BOOST_CLASS_VERSION(PieceType, 1)
BOOST_CLASS_TRACKING(PieceType, boost::serialization::track_never)
//=========================================================================================================================
class Piece : public std::enable_shared_from_this<Piece>
{//=========================================================================================================================
public:

	static Logger log;

	//Color noColor;
	//PieceType noPieceType;
	//BlockType noBlockType;
	//sp<vector<Color>>emptyColors;

	sp<Grid> grid = nullptr;
	sp<GameLogic> game = nullptr;

	int currentRotation = 0;

	int xGrid = 0;
	int yGrid = 0;

	sp<vector<sp<Block>>>blocks;

	float cursorAlphaFrom = 0.3f;
	float cursorAlphaTo = 1.0f;
	long long cursorFadeTicksPerPhase = 200;
private:
	float cursorAlpha = 0.3f; // cursorAlphaFrom;
	long long cursorFadeTicks = 0;
	bool cursorFadeInOutToggle = false;

public:
	float ghostAlphaFrom = 0.5f;
	float ghostAlphaTo = 0.8f;
	long long ghostFadeTicksPerPhase = 200;
private:
	float ghostAlpha = 0.5f; // ghostAlphaFrom;
	long long ghostFadeTicks = 0;
	bool ghostFadeInOutToggle = false;

public:
	sp<Block> holdingBlock = nullptr;
	sp<PieceType> pieceType = nullptr;
	bool overrideAnySpecialBehavior = false;
	int piecesSetSinceThisPieceSet = 0;
	bool setInGrid = false;

//	bool operator==(const Piece& rhs) const
//	{
//		return
//			currentRotation == rhs.currentRotation
//			&& xGrid == rhs.xGrid
//			&& blocks == rhs.blocks
//			&& cursorAlphaFrom == rhs.cursorAlphaFrom
//			&& cursorAlphaTo == rhs.cursorAlphaTo
//			&& cursorFadeTicksPerPhase == rhs.cursorFadeTicksPerPhase
//			&& cursorAlpha == rhs.cursorAlpha
//			&& cursorFadeTicks == rhs.cursorFadeTicks
//			&& cursorFadeInOutToggle == rhs.cursorFadeInOutToggle
//			&& ghostAlphaFrom == rhs.ghostAlphaFrom
//			&& ghostAlphaTo == rhs.ghostAlphaTo
//			&& ghostFadeTicksPerPhase == rhs.ghostFadeTicksPerPhase
//			&& ghostAlpha == rhs.ghostAlpha
//			&& ghostFadeTicks == rhs.ghostFadeTicks
//			&& ghostFadeInOutToggle == rhs.ghostFadeInOutToggle
//			&& holdingBlock == rhs.holdingBlock
//			&& pieceType == rhs.pieceType
//			&& overrideAnySpecialBehavior == rhs.overrideAnySpecialBehavior
//			&& piecesSetSinceThisPieceSet == rhs.piecesSetSinceThisPieceSet
//			&& setInGrid == rhs.setInGrid
//			;
//	}
//	bool operator!=(const Piece& rhs) const
//	{
//		return
//			(*this == rhs) == false
//			;
//	}

	Piece(sp<GameLogic> gameInstance, sp<Grid> grid, sp<PieceType> pieceType, sp<vector<sp<BlockType>>> blockTypes);
	Piece(sp<GameLogic> gameInstance, sp<Grid> grid, sp<PieceType> pieceType, sp<BlockType> blockType);
	void init();
	void initColors();
	void setPieceBlockConnections();
	void setBlockColorConnectionsInPiece();
	int getNumBlocksInCurrentRotation();
	void update();
	float getScreenX();
	float getScreenY();
	void renderOutlineFirstBlock(float x, float y, float alpha, bool asGhost);
	void renderOutlineBlockZeroZero(float x, float y, float alpha, bool asGhost);
	void renderAsCurrentPiece();
	void renderAsCurrentPiece(float x, float y);
	void render(float x, float y);
	void renderGhost(float x, float y, float alpha);
	void setBlocksSlamming();
	int getWidth();
	int getHeight();
	int getLowestOffsetX();
	int getLowestOffsetY();
	int getHighestOffsetX();
	int getHighestOffsetY();
	void rotateCCW();
	void rotateCW();
	void setRandomPieceColors(bool grayscale);
	void setRotation(int rotation);
	static RotationSet get2BlockRotateAround00RotationSet();
	static RotationSet get2BlockBottomLeftAlwaysFilledRotationSet();
	static RotationSet get1BlockCursorRotationSet();
	static RotationSet get2BlockHorizontalCursorRotationSet();
	static RotationSet get2BlockVerticalCursorRotationSet();
	static RotationSet get3BlockHorizontalCursorRotationSet();
	static RotationSet get3BlockVerticalCursorRotationSet();
	static RotationSet get4BlockCursorRotationSet();
	static RotationSet get3BlockVerticalRotationSet();
	static RotationSet get3BlockHorizontalRotationSet();
	static RotationSet get3BlockTRotationSet();
	static RotationSet get3BlockLRotationSet();
	static RotationSet get3BlockJRotationSet();
	static RotationSet get3BlockIRotationSet();
	static RotationSet get3BlockCRotationSet();
	static RotationSet get3BlockDRotationSet();
	static RotationSet get4BlockORotationSet();
	static RotationSet get4BlockSolidRotationSet();
	static RotationSet get9BlockSolidRotationSet();
	static RotationSet get4BlockIRotationSet(RotationType type);
	static RotationSet get4BlockJRotationSet(RotationType type);
	static RotationSet get4BlockLRotationSet(RotationType type);
	static RotationSet get4BlockSRotationSet(RotationType type);
	static RotationSet get4BlockTRotationSet(RotationType type);
	static RotationSet get4BlockZRotationSet(RotationType type);
	int cellW();
	int cellH();
	sp<GameType> getGameType();
	sp<GameLogic> getGameLogic();
};

