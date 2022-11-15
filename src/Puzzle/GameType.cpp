#include "stdafx.h"
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

Logger GameType::log = Logger("GameType");

sp<DifficultyType> GameType::difficulty_BEGINNER = nullptr;
sp<DifficultyType> GameType::difficulty_EASY = nullptr;
sp<DifficultyType> GameType::difficulty_NORMAL = nullptr;
sp<DifficultyType> GameType::difficulty_HARD = nullptr;
sp<DifficultyType> GameType::difficulty_INSANE = nullptr;
sp<DifficultyType> GameType::difficulty_IMPOSSIBLE = nullptr;

//=========================================================================================================================
template <typename Archive>
void DifficultyType::serialize(Archive & ar, const unsigned int version)
{//=========================================================================================================================
    
    //---------------------------------------------------
    //game rules
    //---------------------------------------------------
    
    ar & BOOST_SERIALIZATION_NVP(name);
    ar & BOOST_SERIALIZATION_NVP(initialLineDropSpeedTicks);
    ar & BOOST_SERIALIZATION_NVP(minStackRise);
    ar & BOOST_SERIALIZATION_NVP(maxStackRise);
    ar & BOOST_SERIALIZATION_NVP(minimumLineDropSpeedTicks);
    ar & BOOST_SERIALIZATION_NVP(extraStage1Level);
    ar & BOOST_SERIALIZATION_NVP(extraStage2Level);
    ar & BOOST_SERIALIZATION_NVP(extraStage3Level);
    ar & BOOST_SERIALIZATION_NVP(extraStage4Level);
    ar & BOOST_SERIALIZATION_NVP(creditsLevel);
    ar & BOOST_SERIALIZATION_NVP(playingFieldGarbageSpawnRuleAmount);
    ar & BOOST_SERIALIZATION_NVP(maximumBlockTypeColors);


	if (version > 1)
	{
		ar & BOOST_SERIALIZATION_NVP(randomlyFillGrid);
		ar & BOOST_SERIALIZATION_NVP(randomlyFillGridStartY);
	}

    ar & BOOST_SERIALIZATION_NVP(randomlyFillGridAmount);


	if (version < 2)
	{
		int randomlyFillStackAmount = 0;
		ar & BOOST_SERIALIZATION_NVP(randomlyFillStackAmount);
		if (randomlyFillStackAmount < randomlyFillGridAmount || randomlyFillStackAmount > 30)randomlyFillGridAmount = randomlyFillStackAmount;
	}


	if (version == 0)
	{
		sp<vector<PieceType>>importExport_pieceTypesToDisallow;
		ar & BOOST_SERIALIZATION_NVP(importExport_pieceTypesToDisallow);
		pieceTypesToDisallow_DEPRECATED->clear();
		for (int i = 0; i < importExport_pieceTypesToDisallow->size(); i++)
		{
			PieceType b = importExport_pieceTypesToDisallow.get(i);
			sp<PieceType> bp(ms<PieceType>());
			*bp = b;
			pieceTypesToDisallow_DEPRECATED.add(bp);
		}
		importExport_pieceTypesToDisallow->clear();
		//---------------------------------------------------

		sp<vector<BlockType>>importExport_blockTypesToDisallow;
		ar & BOOST_SERIALIZATION_NVP(importExport_blockTypesToDisallow);
		blockTypesToDisallow_DEPRECATED->clear();
		for (int i = 0; i < importExport_blockTypesToDisallow->size(); i++)
		{
			BlockType b = importExport_blockTypesToDisallow.get(i);
			sp<BlockType> bp(ms<BlockType>());
			*bp = b;
			blockTypesToDisallow_DEPRECATED.add(bp);
		}
		importExport_blockTypesToDisallow->clear();
		//---------------------------------------------------
	}
	else
	{
		ar & BOOST_SERIALIZATION_NVP(pieceTypesToDisallow_UUID);
		ar & BOOST_SERIALIZATION_NVP(blockTypesToDisallow_UUID);
	}
}




//=========================================================================================================================
template <typename Archive>
void GameType::serialize(Archive & ar, const unsigned int version)
{//=========================================================================================================================
    
    
    ar & BOOST_SERIALIZATION_NVP(uuid);

	if (version < 7)
	{
		bool builtInType = false;
		ar & BOOST_SERIALIZATION_NVP(builtInType);
	}
	if (version < 3)
	{
		string loadedFilename = "";
		ar & BOOST_SERIALIZATION_NVP(loadedFilename);
	}
    //---------------------------------------------------
    //game rules
    //---------------------------------------------------
    
    ar & BOOST_SERIALIZATION_NVP(name);

	if(version > 7)
	{
		ar & BOOST_SERIALIZATION_NVP(rules1);
		ar & BOOST_SERIALIZATION_NVP(rules2);
		ar & BOOST_SERIALIZATION_NVP(rules3);
	}
	if (version < 8)
	{
		string rules = "";
		ar & BOOST_SERIALIZATION_NVP(rules);
		rules1 = rules;
		rules2 = "";
		rules3 = "";
	}

    ar & BOOST_SERIALIZATION_NVP(scoreType);
    ar & BOOST_SERIALIZATION_NVP(scoreTypeAmountPerLevelGained);
    
    ar & BOOST_SERIALIZATION_NVP(nextPieceEnabled);
    ar & BOOST_SERIALIZATION_NVP(numberOfNextPiecesToShow);
    
    ar & BOOST_SERIALIZATION_NVP(holdPieceEnabled);
    ar & BOOST_SERIALIZATION_NVP(resetHoldPieceRotation);
    
    ar & BOOST_SERIALIZATION_NVP(chainRule_AmountPerChain);
    ar & BOOST_SERIALIZATION_NVP(chainRule_CheckEntireLine);

	if (version > 0)
	{
		ar & BOOST_SERIALIZATION_NVP(chainRule_CheckRow);
		ar & BOOST_SERIALIZATION_NVP(chainRule_CheckColumn);
	}

    ar & BOOST_SERIALIZATION_NVP(chainRule_CheckRowOrColumn);
	if(chainRule_CheckRowOrColumn)
	{
		chainRule_CheckRow = true;
		chainRule_CheckColumn = true;
	}

    ar & BOOST_SERIALIZATION_NVP(chainRule_CheckDiagonal);
    ar & BOOST_SERIALIZATION_NVP(chainRule_CheckRecursiveConnections);
    ar & BOOST_SERIALIZATION_NVP(chainRule_CheckTouchingBreakerBlocksChain);
    
    ar & BOOST_SERIALIZATION_NVP(gravityRule_onlyMoveDownDisconnectedBlocks);
    
    ar & BOOST_SERIALIZATION_NVP(playingFieldGarbageType);
    ar & BOOST_SERIALIZATION_NVP(playingFieldGarbageSpawnRule);
    //ar & BOOST_SERIALIZATION_NVP(playingFieldGarbageSpawnRuleAmount);
    
    ar & BOOST_SERIALIZATION_NVP(hardDropPunchThroughToLowestValidGridPosition);
    
    ar & BOOST_SERIALIZATION_NVP(twoSpaceWallKickAllowed);
    ar & BOOST_SERIALIZATION_NVP(diagonalWallKickAllowed);
    ar & BOOST_SERIALIZATION_NVP(pieceClimbingAllowed);
    ar & BOOST_SERIALIZATION_NVP(flip180Allowed);
    ar & BOOST_SERIALIZATION_NVP(floorKickAllowed);
    
    ar & BOOST_SERIALIZATION_NVP(readyTicksAmount);
    
    //----------------------------------------------------
    //VS rules
    //----------------------------------------------------
    
    ar & BOOST_SERIALIZATION_NVP(vsGarbageRule);
    
    
    //---------------------------------------------------
    //grid
    //---------------------------------------------------
    ar & BOOST_SERIALIZATION_NVP(gridWidth);
    ar & BOOST_SERIALIZATION_NVP(gridHeight);
	
    ar & BOOST_SERIALIZATION_NVP(gridPixelsBetweenRows);
    ar & BOOST_SERIALIZATION_NVP(gridPixelsBetweenColumns);
    
    ar & BOOST_SERIALIZATION_NVP(gameMode);
    
	bool import_randomlyFillGrid = false;
	int import_randomlyFillGridStartY = 0;

	if (version < 6)
	{
		bool randomlyFillGrid = false;
		int randomlyFillGridStartY = 0;
		ar & BOOST_SERIALIZATION_NVP(randomlyFillGrid);
		//ar & BOOST_SERIALIZATION_NVP(randomlyFillGridAmount);
		ar & BOOST_SERIALIZATION_NVP(randomlyFillGridStartY);

		if (randomlyFillGrid)import_randomlyFillGrid = true;
		if (randomlyFillGridStartY>0)import_randomlyFillGridStartY = randomlyFillGridStartY;
	}

	
    //ar & BOOST_SERIALIZATION_NVP(stackRiseGame);
    ar & BOOST_SERIALIZATION_NVP(stackDontPutSameColorNextToEachOther);
    ar & BOOST_SERIALIZATION_NVP(stackDontPutSameBlockTypeNextToEachOther);
    ar & BOOST_SERIALIZATION_NVP(stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull);
    ar & BOOST_SERIALIZATION_NVP(stackLeaveAtLeastOneGapPerRow);
    

	if (version < 6)
	{
		bool randomlyFillStack = false;
		int randomlyFillStackStartY = 0;


		ar & BOOST_SERIALIZATION_NVP(randomlyFillStack);
		//ar & BOOST_SERIALIZATION_NVP(randomlyFillStackAmount);
		ar & BOOST_SERIALIZATION_NVP(randomlyFillStackStartY);

		if (randomlyFillStack)import_randomlyFillGrid = true;
		if (randomlyFillStackStartY>0)import_randomlyFillGridStartY = randomlyFillStackStartY;
	}
    
    ar & BOOST_SERIALIZATION_NVP(stackCursorType);
    //ar & BOOST_SERIALIZATION_NVP(useCurrentPieceAsCursor);
    //ar & BOOST_SERIALIZATION_NVP(makeNewPiece);
    //ar & BOOST_SERIALIZATION_NVP(makeCursorPiece);
    //ar & BOOST_SERIALIZATION_NVP(cursorPieceSize);
    
	if (version < 5)
	{
		OKColor gridBorderColor = OKColor();
		OKColor gridCheckeredBackgroundColor1 = OKColor();
		OKColor gridCheckeredBackgroundColor2 = OKColor();
		OKColor screenBackgroundColor = OKColor();
		ar & BOOST_SERIALIZATION_NVP(gridBorderColor);
		ar & BOOST_SERIALIZATION_NVP(gridCheckeredBackgroundColor1);
		ar & BOOST_SERIALIZATION_NVP(gridCheckeredBackgroundColor2);
		ar & BOOST_SERIALIZATION_NVP(screenBackgroundColor);

		bool gridRule_showWarningForFieldThreeQuartersFilled = false;
		ar & BOOST_SERIALIZATION_NVP(gridRule_showWarningForFieldThreeQuartersFilled);
	}
    
   
    
    //---------------------------------------------------
    //block
    //---------------------------------------------------
    //ar & BOOST_SERIALIZATION_NVP(whenGeneratingBlockDontGetBlockColorThatIsntOnGrid);
    
    ar & BOOST_SERIALIZATION_NVP(blockRule_drawDotToSquareOffBlockCorners);
    ar & BOOST_SERIALIZATION_NVP(drawDotOnCenterOfRotation);
    ar & BOOST_SERIALIZATION_NVP(gridRule_outlineOpenBlockEdges);
    ar & BOOST_SERIALIZATION_NVP(fadeBlocksDarkerWhenLocking);
    ar & BOOST_SERIALIZATION_NVP(blockRule_drawBlocksDarkerWhenLocked);
    ar & BOOST_SERIALIZATION_NVP(blockRule_fillSolidSquareWhenSetInGrid);
	
    ar & BOOST_SERIALIZATION_NVP(blockRule_drawBlocksConnectedByPieceIgnoringColor);
    ar & BOOST_SERIALIZATION_NVP(blockRule_drawBlocksConnectedByColorIgnoringPiece);
    ar & BOOST_SERIALIZATION_NVP(blockRule_drawBlocksConnectedByColorInPiece);
	
    ar & BOOST_SERIALIZATION_NVP(blockMovementInterpolationTicks);
    ar & BOOST_SERIALIZATION_NVP(blockAnimationTicksRandomUpToBetweenLoop);
	//---------------------------------------------------
    importExport_blockTypes->clear();
    for (int i = 0; i < blockTypes->size(); i++)
    {
        sp<BlockType> bp = blockTypes.get(i);
		BlockType b;
		b = *bp;
        importExport_blockTypes.add(b);
    }
    ar & BOOST_SERIALIZATION_NVP(importExport_blockTypes);
    blockTypes->clear();
    for (int i = 0; i < importExport_blockTypes->size(); i++)
    {
        BlockType b = importExport_blockTypes.get(i);
        sp<BlockType> bp(ms<BlockType>());
		*bp = b;
        blockTypes.add(bp);
    }
    importExport_blockTypes->clear();
	//---------------------------------------------------
    
    
    //---------------------------------------------------
    //piece
    //---------------------------------------------------
    ar & BOOST_SERIALIZATION_NVP(whenGeneratingPieceDontMatchAllBlockColors);
    ar & BOOST_SERIALIZATION_NVP(whenGeneratingPieceDontMatchTwoBlocksOfTheSameSpecialRandomTypeAndColor);
    ar & BOOST_SERIALIZATION_NVP(whenGeneratingPieceDontMatchNormalBlockWithBlockOfDifferentTypeAndSameColor);
    
    //ar & BOOST_SERIALIZATION_NVP(currentPieceRenderAsNormalPiece);
    //ar & BOOST_SERIALIZATION_NVP(drawCursorInsteadOfCurrentPiece);
    ar & BOOST_SERIALIZATION_NVP(currentPieceOutlineFirstBlockRegardlessOfPosition);
    ar & BOOST_SERIALIZATION_NVP(currentPieceRule_OutlineBlockAtZeroZero);
    //ar & BOOST_SERIALIZATION_NVP(currentPieceRenderHoldingBlock);
    //ar & BOOST_SERIALIZATION_NVP(currentPieceMoveUpHalfABlock);
    
    ar & BOOST_SERIALIZATION_NVP(currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty);
    
	//---------------------------------------------------
    //if we are exporting a new one, importExport will be empty
    //if we are importing a new one, both importExport and pieceTypes will be empty
    //if we are exporting an imported one, we want importExport to be empty and pieceTypes to be full
    //we should never import an exported one
    importExport_pieceTypes->clear();
    for (int i = 0; i < pieceTypes->size(); i++)
    {
        sp<PieceType> bp = pieceTypes.get(i);
		PieceType b;
		b = *bp;
        importExport_pieceTypes.add(b);
    }
    ar & BOOST_SERIALIZATION_NVP(importExport_pieceTypes);
    pieceTypes->clear();
    for (int i = 0; i<importExport_pieceTypes->size(); i++)
    {
        PieceType b = importExport_pieceTypes.get(i);
        sp<PieceType> bp(ms<PieceType>());
		*bp = b;
        pieceTypes.add(bp);
    }
    importExport_pieceTypes->clear();
	//---------------------------------------------------
    
    
	//---------------------------------------------------
    importExport_difficulties->clear();
    for (int i = 0; i < difficultyTypes->size(); i++)
    {
        sp<DifficultyType>bp = difficultyTypes.get(i);
		DifficultyType b;
		b = *bp;
        importExport_difficulties.add(b);
    }
    ar & BOOST_SERIALIZATION_NVP(importExport_difficulties);
    difficultyTypes->clear();
    for (int i = 0; i<importExport_difficulties->size(); i++)
    {
        DifficultyType b = importExport_difficulties.get(i);
        sp<DifficultyType>bp = ms<DifficultyType>();
		*bp = b;
        difficultyTypes.add(bp);
    }
    importExport_difficulties->clear();
	//---------------------------------------------------

	if (version < 6)//move randomly fill grid options into difficulty and combine randomly fill grid and stack
	{

		for (int i = 0; i < difficultyTypes->size(); i++)
		{
			sp<DifficultyType>bp = difficultyTypes.get(i);
			bp->randomlyFillGrid = import_randomlyFillGrid;
		}
		


		for (int i = 0; i < difficultyTypes->size(); i++)
		{
			sp<DifficultyType>bp = difficultyTypes.get(i);
			bp->randomlyFillGridStartY = import_randomlyFillGridStartY;
		}
		
	}
    
    //---------------------------------------------------
    //timing
    //---------------------------------------------------
	
    //not user settable ----
    //ar & BOOST_SERIALIZATION_NVP(initialLineDropSpeedTicks);
    //ar & BOOST_SERIALIZATION_NVP(minStackRise);
    //ar & BOOST_SERIALIZATION_NVP(maxStackRise);
    //ar & BOOST_SERIALIZATION_NVP(minimumLineDropSpeedTicks);
    //
    //ar & BOOST_SERIALIZATION_NVP(extraStage1Level);
    //ar & BOOST_SERIALIZATION_NVP(extraStage2Level);
    //ar & BOOST_SERIALIZATION_NVP(extraStage3Level);
    //ar & BOOST_SERIALIZATION_NVP(extraStage4Level);
    //ar & BOOST_SERIALIZATION_NVP(creditsLevel);
    
    
    
    //ar & BOOST_SERIALIZATION_NVP(flashBlockSpeedTicks);
    
    //ar & BOOST_SERIALIZATION_NVP(flashScreenSpeedTicks);
    //ar & BOOST_SERIALIZATION_NVP(flashScreenTimesPerLevel);

	if(version<2)
	{
		int timesToFlashBlocks = 1;

		ar & BOOST_SERIALIZATION_NVP(timesToFlashBlocks);

	}
    
    ar & BOOST_SERIALIZATION_NVP(bloomIntensity);
    ar & BOOST_SERIALIZATION_NVP(bloomTimes);
    
    //----------
    
    
    
    //TODO: max stack wait delay
    ar & BOOST_SERIALIZATION_NVP(maxLockDelayTicks);
    ar & BOOST_SERIALIZATION_NVP(spawnDelayTicksAmountPerPiece);
    ar & BOOST_SERIALIZATION_NVP(lineClearDelayTicksAmountPerLine);
    ar & BOOST_SERIALIZATION_NVP(lineClearDelayTicksAmountPerBlock);
    
    
    ar & BOOST_SERIALIZATION_NVP(gravityRule_ticksToMoveDownBlocksOverBlankSpaces);
    ar & BOOST_SERIALIZATION_NVP(moveDownAllLinesOverBlankSpacesAtOnce);
    
    ar & BOOST_SERIALIZATION_NVP(removingBlocksDelayTicksBetweenEachBlock);
        
    //---------------------------------------------------
    //controls
    //---------------------------------------------------
    
	if (version < 2)
	{

		//DEPRECATED AND MOVED ELSEWHERE, ONLY HERE FOR COMPATIBILITY!
		DropLockType dropLockType = DropLockType::HARD_DROP_INSTANT_LOCK; //TODO: this should be moved to user settings
		int repeatDelayRotateCW = 100;
		int repeatDelayRotateCCW = 100;
		int repeatDelayHoldRaise = 100;
		int repeatDelayUp = 100;//if stack game, 50
		int repeatDelayDown = 30;//if stack game, 50
		int repeatDelayLeft = 50;
		int repeatDelayRight = 50;
		int repeatDelaySlam = 100;
		bool repeatEnabledRotateCW = false;
		bool repeatEnabledRotateCCW = false;
		bool repeatEnabledHoldRaise = false;
		bool repeatEnabledUp = false;//if stack game, true
		bool repeatEnabledDown = true;
		bool repeatEnabledLeft = true;
		bool repeatEnabledRight = true;
		bool repeatEnabledSlam = false;
		int repeatStartDelayRotateCW = 150;
		int repeatStartDelayRotateCCW = 150;
		int repeatStartDelayHoldRaise = 150;
		int repeatStartDelayUp = 150;
		int repeatStartDelayDown = 30; //if stack game, 150
		int repeatStartDelayLeft = 150;
		int repeatStartDelayRight = 150;
		int repeatStartDelaySlam = 150;

		ar & BOOST_SERIALIZATION_NVP(dropLockType);

		ar & BOOST_SERIALIZATION_NVP(repeatDelayRotateCW);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayRotateCCW);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayHoldRaise);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayUp);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayDown);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayLeft);
		ar & BOOST_SERIALIZATION_NVP(repeatDelayRight);
		ar & BOOST_SERIALIZATION_NVP(repeatDelaySlam);

		ar & BOOST_SERIALIZATION_NVP(repeatEnabledRotateCW);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledRotateCCW);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledHoldRaise);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledUp);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledDown);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledLeft);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledRight);
		ar & BOOST_SERIALIZATION_NVP(repeatEnabledSlam);

		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayRotateCW);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayRotateCCW);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayHoldRaise);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayUp);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayDown);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayLeft);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelayRight);
		ar & BOOST_SERIALIZATION_NVP(repeatStartDelaySlam);
	}

	if (version>2)
	{
		ar & BOOST_SERIALIZATION_NVP(creatorUserID);
		ar & BOOST_SERIALIZATION_NVP(creatorUserName);
		ar & BOOST_SERIALIZATION_NVP(dateCreated);
		ar & BOOST_SERIALIZATION_NVP(lastModified);
		ar & BOOST_SERIALIZATION_NVP(howManyTimesUpdated);
		ar & BOOST_SERIALIZATION_NVP(upVotes);
		ar & BOOST_SERIALIZATION_NVP(downVotes);

		
	}
	if(version==3)
	{
		bool haveYouVoted = false;
		ar & BOOST_SERIALIZATION_NVP(haveYouVoted);
	}
	if(version>3)
	{
		ar & BOOST_SERIALIZATION_NVP(yourVote);
	}
    
}

//=========================================================================================================================

string GameType::toBase64GZippedXML()
{//=========================================================================================================================
	sp<GameType>s = this;
	GameType gs = GameType();
	gs = *s;
	std::stringstream ss;
	boost::archive::xml_oarchive oarchive(ss);
	oarchive << BOOST_SERIALIZATION_NVP(gs);
	log->debug(ss.str());
	string zip = FileUtils::zipStringToBase64String(ss.str());
	return zip;
}

//=========================================================================================================================
sp<GameType>GameType::fromBase64GZippedXML(string b64GZipXML)
{//=========================================================================================================================
	string xml = FileUtils::unzipBase64StringToString(b64GZipXML);

	if (xml == "" || xml.length() == 0)
	{
		return nullptr;
	}

	stringstream ss;
	ss << xml;
	boost::archive::xml_iarchive ia(ss);

	GameType gt;
	try
	{
		ia >> BOOST_SERIALIZATION_NVP(gt);
		sp<GameType>s = ms<GameType>();
		*s = gt;
		return s;
	}
	catch(exception)
	{
		log->error("Could not unserialize GameType");
	}

	return nullptr;
}


//	public void addRandomSpecialPieceType(sp<PieceType> pieceType)
//	{
//
//		randomSpecialPieceTypes.Add(pieceType);
//	}
//
//
//
//	
//	public void addRegularFrequencySpecialPieceType(sp<PieceType> pieceType)
//	{
//
//		regularFrequencySpecialPieceTypes.Add(pieceType);
//	}

vector<sp<BlockType>> GameType::getNormalBlockTypes(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<BlockType>>>arr;
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->useInNormalPieces)
		{
			bool found = false;
			for(int n=0;n<d->blockTypesToDisallow_UUID->size();n++)
			{	
				if(d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if(found==false)arr.add(b);
		}
	}
	return arr;
}

vector<sp<BlockType>> GameType::getGarbageBlockTypes(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<BlockType>>>arr;
	for(int i=0;i<blockTypes->size();i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->useAsGarbage)
		{
			bool found = false;
			for (int n = 0; n<d->blockTypesToDisallow_UUID->size(); n++)
			{
				if (d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;
}

vector<sp<BlockType>> GameType::getPlayingFieldBlockTypes(sp<DifficultyType>d)
{//=========================================================================================================================

	sp<vector<sp<BlockType>>>arr;
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->useAsPlayingFieldFiller)
		{
			bool found = false;
			for (int n = 0; n<d->blockTypesToDisallow_UUID->size(); n++)
			{
				if (d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;
}

vector<sp<BlockType>> GameType::getBlockTypesToIgnoreWhenCheckingChain(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<BlockType>>>arr;
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->ignoreWhenCheckingChainConnections)
		{
			bool found = false;
			for (int n = 0; n<d->blockTypesToDisallow_UUID->size(); n++)
			{
				if (d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;

}

vector<sp<BlockType>> GameType::getBlockTypesToIgnoreWhenMovingDown(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<BlockType>>>arr;
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->ignoreWhenMovingDownBlocks)
		{
			bool found = false;
			for (int n = 0; n<d->blockTypesToDisallow_UUID->size(); n++)
			{
				if (d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;

}

vector<sp<BlockType>> GameType::getBlockTypesChainMustContain(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<BlockType>>>arr;
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> b = blockTypes.get(i);
		if (b->chainConnectionsMustContainAtLeastOneBlockWithThisTrue)
		{
			bool found = false;
			for (int n = 0; n<d->blockTypesToDisallow_UUID->size(); n++)
			{
				if (d->blockTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;

}


vector<sp<PieceType>> GameType::getNormalPieceTypes(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<PieceType>>>arr;
	for (int i = 0; i<pieceTypes->size(); i++)
	{
		sp<PieceType> b = pieceTypes.get(i);
		if (b->useAsNormalPiece)
		{
			bool found = false;
			for (int n = 0; n<d->pieceTypesToDisallow_UUID->size(); n++)
			{
				if (d->pieceTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;
}

vector<sp<PieceType>> GameType::getGarbagePieceTypes(sp<DifficultyType>d)
{//=========================================================================================================================
	sp<vector<sp<PieceType>>>arr;
	for (int i = 0; i<pieceTypes->size(); i++)
	{
		sp<PieceType> b = pieceTypes.get(i);
		if (b->useAsGarbagePiece)
		{
			bool found = false;
			for (int n = 0; n<d->pieceTypesToDisallow_UUID->size(); n++)
			{
				if (d->pieceTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;
}

vector<sp<PieceType>> GameType::getPlayingFieldPieceTypes(sp<DifficultyType>d)
{//=========================================================================================================================

	sp<vector<sp<PieceType>>>arr;
	for (int i = 0; i<pieceTypes->size(); i++)
	{
		sp<PieceType> b = pieceTypes.get(i);
		if (b->useAsPlayingFieldFillerPiece)
		{
			bool found = false;
			for (int n = 0; n<d->pieceTypesToDisallow_UUID->size(); n++)
			{
				if (d->pieceTypesToDisallow_UUID.get(n) == b->uuid)found = true;
			}

			if (found == false)arr.add(b);
		}
	}
	return arr;
}

GameType::GameType()
{//=========================================================================================================================

	boost::uuids::random_generator generator;

	uuid = to_string(generator());

	//setTimingBasedOnDifficulty(currentDifficulty);

	if(difficulty_BEGINNER==nullptr)
	{
		difficulty_BEGINNER = ms<DifficultyType>();
		difficulty_BEGINNER->name = "Beginner";
		difficulty_BEGINNER->initialLineDropSpeedTicks = 2000;
		difficulty_BEGINNER->minimumLineDropSpeedTicks = 1000;
		difficulty_BEGINNER->minStackRise = 600;
		difficulty_BEGINNER->maxStackRise = 1500;
		difficulty_BEGINNER->extraStage1Level = 5;
		difficulty_BEGINNER->extraStage2Level = 6;
		difficulty_BEGINNER->extraStage3Level = 7;
		difficulty_BEGINNER->extraStage4Level = 8;
		difficulty_BEGINNER->creditsLevel = 9;
		difficulty_BEGINNER->playingFieldGarbageSpawnRuleAmount = 10;

		difficulty_EASY = ms<DifficultyType>();
		difficulty_EASY->name = "Easy";
		difficulty_EASY->initialLineDropSpeedTicks = 1500;
		difficulty_EASY->minimumLineDropSpeedTicks = 500;
		difficulty_EASY->minStackRise = 300;
		difficulty_EASY->maxStackRise = 800;
		difficulty_EASY->extraStage1Level = 10;
		difficulty_EASY->extraStage2Level = 11;
		difficulty_EASY->extraStage3Level = 12;
		difficulty_EASY->extraStage4Level = 13;
		difficulty_EASY->creditsLevel = 15;
		difficulty_EASY->playingFieldGarbageSpawnRuleAmount = 8;

		difficulty_NORMAL = ms<DifficultyType>();
		difficulty_NORMAL->name = "Normal";
		difficulty_NORMAL->initialLineDropSpeedTicks = 1000;
		difficulty_NORMAL->minimumLineDropSpeedTicks = 30;
		difficulty_NORMAL->minStackRise = 400;
		difficulty_NORMAL->maxStackRise = 64;
		difficulty_NORMAL->extraStage1Level = 10;
		difficulty_NORMAL->extraStage2Level = 15;
		difficulty_NORMAL->extraStage3Level = 20;
		difficulty_NORMAL->extraStage4Level = 25;
		difficulty_NORMAL->creditsLevel = 30;
		difficulty_NORMAL->playingFieldGarbageSpawnRuleAmount = 5;

		difficulty_HARD = ms<DifficultyType>();
		difficulty_HARD->name = "Hard";
		difficulty_HARD->initialLineDropSpeedTicks = 500;
		difficulty_HARD->minimumLineDropSpeedTicks = 20;
		difficulty_HARD->minStackRise = 15;
		difficulty_HARD->maxStackRise = 300;
		difficulty_HARD->extraStage1Level = 20;
		difficulty_HARD->extraStage2Level = 30;
		difficulty_HARD->extraStage3Level = 40;
		difficulty_HARD->extraStage4Level = 50;
		difficulty_HARD->creditsLevel = 60;
		difficulty_HARD->playingFieldGarbageSpawnRuleAmount = 4;

		difficulty_INSANE = ms<DifficultyType>();
		difficulty_INSANE->name = "Insane";
		difficulty_INSANE->initialLineDropSpeedTicks = 128;
		difficulty_INSANE->minimumLineDropSpeedTicks = 8;
		difficulty_INSANE->minStackRise = 15;
		difficulty_INSANE->maxStackRise = 200;
		difficulty_INSANE->extraStage1Level = 50;
		difficulty_INSANE->extraStage2Level = 60;
		difficulty_INSANE->extraStage3Level = 70;
		difficulty_INSANE->extraStage4Level = 80;
		difficulty_INSANE->creditsLevel = 99;
		difficulty_INSANE->playingFieldGarbageSpawnRuleAmount = 3;

		difficulty_IMPOSSIBLE = ms<DifficultyType>();
		difficulty_IMPOSSIBLE->name = "Impossible";
		difficulty_IMPOSSIBLE->initialLineDropSpeedTicks = 32;
		difficulty_IMPOSSIBLE->minimumLineDropSpeedTicks = 2;
		difficulty_IMPOSSIBLE->minStackRise = 2;
		difficulty_IMPOSSIBLE->maxStackRise = 128;
		difficulty_IMPOSSIBLE->extraStage1Level = 50;
		difficulty_IMPOSSIBLE->extraStage2Level = 60;
		difficulty_IMPOSSIBLE->extraStage3Level = 70;
		difficulty_IMPOSSIBLE->extraStage4Level = 80;
		difficulty_IMPOSSIBLE->creditsLevel = 99;
		difficulty_IMPOSSIBLE->playingFieldGarbageSpawnRuleAmount = 2;

	}

	sp<DifficultyType> beginner = ms<DifficultyType>(*difficulty_BEGINNER);
	sp<DifficultyType> easy = ms<DifficultyType>(*difficulty_EASY);
	sp<DifficultyType> normal = ms<DifficultyType>(*difficulty_NORMAL);
	sp<DifficultyType> hard = ms<DifficultyType>(*difficulty_HARD);
	sp<DifficultyType> insane = ms<DifficultyType>(*difficulty_INSANE);

	difficultyTypes->clear();
	difficultyTypes.add(beginner);
	difficultyTypes.add(easy);
	difficultyTypes.add(normal);
	difficultyTypes.add(hard);
	difficultyTypes.add(insane);

	//currentDifficulty = normal;
}

sp<BlockType> GameType::getBlockTypeByName(string s)
{//=========================================================================================================================
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> d = blockTypes.get(i);
		if (d->name == s)
		{
			return d;
		}
	}

	log->error("Could not find blockType: " + s + " in " + name);

	return nullptr;
}

sp<PieceType> GameType::getPieceTypeByName(string s)
{//=========================================================================================================================
	for (int i = 0; i<pieceTypes->size(); i++)
	{
		sp<PieceType> d = pieceTypes.get(i);
		if (d->name == s)
		{
			return d;
		}
	}

	log->error("Could not find PieceType: " + s + " in " + name);

	return nullptr;
}

sp<BlockType> GameType::getBlockTypeByUUID(string s)
{//=========================================================================================================================
	for (int i = 0; i<blockTypes->size(); i++)
	{
		sp<BlockType> d = blockTypes.get(i);
		if (d->uuid == s)
		{
			return d;
		}
	}

	log->error("Could not find blockType: " + s + " in " + name);

	return nullptr;
}

sp<PieceType> GameType::getPieceTypeByUUID(string s)
{//=========================================================================================================================
	for (int i = 0; i<pieceTypes->size(); i++)
	{
		sp<PieceType> d = pieceTypes.get(i);
		if (d->uuid == s)
		{
			return d;
		}
	}

	log->error("Could not find PieceType: " + s + " in " + name);

	return nullptr;
}

sp<DifficultyType> GameType::getDifficultyByName(string s)
{//=========================================================================================================================

	//bool found = false;
	for (int i = 0; i<difficultyTypes->size(); i++)
	{
		sp<DifficultyType>d = difficultyTypes.get(i);
		if (d->name == s)
		{
			return d;
		}
	}

	log->error("Could not find difficulty: " + s + " in " + name);
	
	return nullptr;
}


//GameType::GameType(sp<DifficultyType> d)
//{
//	currentDifficulty = d;
//	//setTimingBasedOnDifficulty(d);
//}

//void GameType::setTimingBasedOnDifficulty(sp<DifficultyType> d)
//{
//	currentDifficulty = d;
//
//
//	initialLineDropSpeedTicks = initialLineDropSpeedTicks;
//	minimumLineDropSpeedTicks = minimumLineDropSpeedTicks;
//	minStackRise = minStackRise;
//	maxStackRise = maxStackRise;
//
//	extraStage1Level = extraStage1Level_BEGINNER;
//	extraStage2Level = extraStage2Level_BEGINNER;
//	extraStage3Level = extraStage3Level_BEGINNER;
//	extraStage4Level = extraStage4Level_BEGINNER;
//	creditsLevel = creditsLevel_BEGINNER;
//	
//}

////=========================================================================================================================
//void GameType::addNormalPieceType(sp<PieceType> pieceType)
//{//=========================================================================================================================
//	pieceType.useAsNormalPiece = true;
//	pieceTypes.add(pieceType);
//}
//
////=========================================================================================================================
//void GameType::addPlayingFieldPieceType(sp<PieceType> pieceType)
//{//=========================================================================================================================
//	pieceType.useAsPlayingFieldFillerPiece = true;
//	pieceTypes.add(pieceType);
//}
//
////=========================================================================================================================
//void GameType::addDisallowedFirstPieceType(sp<PieceType> pieceType)
//{//=========================================================================================================================
//	pieceType.disallowAsFirstPiece = true;
//	pieceTypes.add(pieceType);
//}

////=========================================================================================================================
//bool GameType::isFirstPieceTypeAllowed(sp<PieceType> pieceType)
//{//=========================================================================================================================
//	for (int i = 0; i < disallowedFirstPieceTypes->size(); i++)
//	{
//		if (pieceType == disallowedFirstPieceTypes.get(i))
//		{
//			return false;
//		}
//	}
//	return true;
//}

////=========================================================================================================================
//void GameType::addBlockType(sp<BlockType> blockClass)
//{//=========================================================================================================================
//
//	blockTypes.add(blockClass);
//}

////=========================================================================================================================
//void GameType::addPlayingFieldBlockType(sp<BlockType> blockClass)
//{//=========================================================================================================================
//
//	playingFieldBlockTypes.add(blockClass);
//}
//
////=========================================================================================================================
//void GameType::addGarbageBlockType(sp<BlockType> blockClass)
//{//=========================================================================================================================
//
//	garbageBlockTypes.add(blockClass);
//}

//	//=========================================================================================================================
//	public void addRandomSpecialBlockType(sp<BlockType> blockClass)
//	{//=========================================================================================================================
//
//		randomSpecialBlockTypes.Add(blockClass);
//	}
//
//	//=========================================================================================================================
//	public void addRegularFrequencySpecialBlockType(sp<BlockType> blockClass)
//	{//=========================================================================================================================
//
//		regularFrequencySpecialBlockTypes.Add(blockClass);
//	}
