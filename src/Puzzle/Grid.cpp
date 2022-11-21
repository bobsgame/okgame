#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



Logger Grid::log = Logger("Grid");

sp<Block> Grid::nullBlock(ms<Block>());

//=========================================================================================================================
Grid::Grid(sp<GameLogic> gameInstance)
{//=========================================================================================================================
	this->game = gameInstance;
}

//=========================================================================================================================
float Grid::getXInFBO()
{//=========================================================================================================================

	//this needs to be 0 + playingFieldWidth/2 - gridW, local to the fbo, not local to the screen

	return getXInFBONoShake() + wigglePlayingFieldX + shakePlayingFieldX;

	//return screenX + wigglePlayingFieldX + shakePlayingFieldX;
}

//=========================================================================================================================
float Grid::getYInFBO()
{//=========================================================================================================================

	return getYInFBONoShake() + wigglePlayingFieldY + shakePlayingFieldY;
	//return screenY + wigglePlayingFieldY + shakePlayingFieldY;
}

//=========================================================================================================================
float Grid::getXInFBONoShake()
{//=========================================================================================================================

	return (getGameLogic()->playingFieldX1 - getGameLogic()->playingFieldX0) / 2 - getWidth() * cellW() / 2;

}

//=========================================================================================================================
float Grid::getYInFBONoShake()
{//=========================================================================================================================

	return 5 * cellH();

}

//=========================================================================================================================
float Grid::getXOnScreenNoShake()
{//=========================================================================================================================

	
	return screenX;
}

//=========================================================================================================================
float Grid::getYOnScreenNoShake()
{//=========================================================================================================================

	
	return screenY;
}

//=========================================================================================================================
float Grid::bgX()
{//=========================================================================================================================
	return getXInFBO() + backgroundScrollX;
}

//=========================================================================================================================
float Grid::bgY()
{//=========================================================================================================================
	return getYInFBO() + backgroundScrollY;
}

//=========================================================================================================================
int Grid::getHeight()
{//=========================================================================================================================
	return getGameType()->gridHeight + GameLogic::aboveGridBuffer;
}

//=========================================================================================================================
int Grid::getWidth()
{//=========================================================================================================================
	return getGameType()->gridWidth;
}


//=========================================================================================================================
void Grid::update()
{//=========================================================================================================================

	//update pieces instead of blocks so we can update all the pieces and blocks inside pieces.update
	sp<vector<sp<Piece>>>piecesInGrid = getArrayOfPiecesOnGrid();
	for (int i = 0; i < piecesInGrid->size(); i++)
	{
		sp<Piece> p = piecesInGrid->at(i);
		p->update();
	}

	updateShake();



	//		for(int y=0;y<getHeight();y++)
	//		{
	//			for(int x=0;x<getWidth();x++)
	//			{
	//				Block b = get(x,y);
	//				if(b!=null)b.update(OKGame().ticksPassed());
	//			}
	//		}
}

//=========================================================================================================================
void Grid::reformat(int oldWidth, int oldHeight)
{//=========================================================================================================================

	sp<vector<sp<Block>>>blockList;

	if (blocks->size() > 0)
	{
	
		for (int y = oldHeight - 1; y >= 0; y--)
		{
			for (int x = 0; x < oldWidth; x++)
			{
				if (contains(y * oldWidth + x))
				{
					sp<Block> b = blocks->at(y * oldWidth + x);
					blocks->erase(blocks->begin()+y * oldWidth + x);
#ifdef blocksHashMap
#else
					blocks->insert(blocks->begin()+(y * oldWidth + x), nullBlock);
#endif

					b->xInPiece = 0;
					b->yInPiece = 0;
					b->connectedBlocksByColor->clear();
					b->connectedBlocksByPiece->clear();
					//b.piece = null;

					blockList->push_back(b);
				}
			}
		}
	}

#ifdef blocksHashMap
#else

	blocks->clear();
	for(int i=0;i<getWidth()*getHeight();i++)
	{
		blocks->insert(blocks->begin()+i, nullBlock);
	}
#endif

	//log.warn("Removed "+blockList.Count+" blocks");
	
	int x = 0;
	int y = getHeight() - 1;

	while (blockList->size() > 0 && y >= 0)//blocks above aboveGridBuffer will be cleared and fade out when we replace them with new game pieces
	{
		sp<Block> b = blockList->at(0);
		blockList->erase(blockList->begin()+0);

		add(x, y, b);

		x++;

		if (x >= getWidth())
		{
			y--;
			x = 0;
		}
	}

//	while (blockList->size() > 0)
//	{
//        blockList->at(0);
//		blockList->erase(->begin()+0);
//	}
	
}

//=========================================================================================================================
int Grid::getNumberOfFilledCells()
{//=========================================================================================================================

	int amt = 0;

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);

			if (b != nullptr)
			{
				amt++;
			}
		}
	}

	return amt;
}

//=========================================================================================================================
void Grid::removeAllBlocksOfPieceFromGrid(sp<Piece> p, bool fadeOut)
{//=========================================================================================================================
	for (int i = 0; i < (int)p->blocks->size(); i++)
	{
		sp<Block> b = p->blocks->at(i);
		if(b->setInGrid)remove(b, fadeOut, true);
	}
}

//=========================================================================================================================
void Grid::replaceAllBlocksWithNewGameBlocks()
{//=========================================================================================================================

	sp<vector<sp<Block>>>removedBlocks;

	int maxHeight = 0;

//	if (getCurrentGameType()->currentDifficulty == Difficulty::INSANE)
//	{
//		maxHeight = GameLogic::aboveGridBuffer + 2;
//	}
//	if (getCurrentGameType()->currentDifficulty == Difficulty::HARD)
//	{
		maxHeight = GameLogic::aboveGridBuffer + ((getHeight() - GameLogic::aboveGridBuffer) / 3);
//	}
//	if (getCurrentGameType()->currentDifficulty == Difficulty::NORMAL)
//	{
//		maxHeight = GameLogic::aboveGridBuffer + ((getHeight() - GameLogic::aboveGridBuffer) / 2);
//	}
//	else
//	{
//		maxHeight = GameLogic::aboveGridBuffer + ((getHeight() - GameLogic::aboveGridBuffer) / 3 * 2);
//	}

	for (int y = getHeight() - 1; y >= 0; y--)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (get(x, y) != nullptr)
			{
				sp<Block> a = get(x, y);
				removedBlocks->push_back(a);

				if (y < maxHeight)
				{
					remove(a, true, true); //fade out if above line
				}
				else
				{
					remove(a, false, true);
				}
			}
		}
	}

	sp<vector<sp<BlockType>>>playingFieldBlockTypes = getGameType()->getPlayingFieldBlockTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<PieceType>>>playingFieldPieceTypes = getGameType()->getPlayingFieldPieceTypes(getGameLogic()->getCurrentDifficulty());

	for (int n = 0; n < removedBlocks->size(); n++)
	{
		sp<Block> a = removedBlocks->at(n);
		int x = a->xGrid;
		int y = a->yGrid;

		if (y >= maxHeight)
		{

//			sp<Piece> p = getRandomPiece(playingFieldPieceTypes, playingFieldBlockTypes);
//
//			//remove other blocks and break connections, we only want one block
//			while (p->blocks->size() > 1)
//			{
//				sp<Block> b = p->blocks->at(p->blocks->size() - 1);
//				p->blocks->erase(->begin()+p->blocks->size() - 1);
//				b->breakConnectionsInPiece();
//			}

			sp<Piece> p = putOneBlockPieceInGridCheckingForFillRules(x, y, playingFieldPieceTypes, playingFieldBlockTypes);

			if (p != nullptr)
			{

				if (p->blocks->size() > 1)
				{
					log.error("Should not put a piece with multiple blocks in the grid");//could do this for tetrid, etc
				}

				if (p->blocks->size() > 0)
				{
					sp<Block> b = p->blocks->at(0);
					if (b != nullptr)
					{
						b->lastScreenX = a->lastScreenX;
						b->lastScreenY = a->lastScreenY;
						b->ticksSinceLastMovement = 0;
					}
				}
			}

			//if the old block color exists in the new game, keep it
			//why is this commented out?  i guess i didn't like it. maybe spoiled the randomness?
			//if(b.blockType.colors!=null&&a.blockType.colors!=null)
			//{
			//	for(int i=0;i<b.blockType.colors.length;i++)
			//	if(b.blockType.colors->get(i)==a.getColor())b.setColor(a.getColor());
			//}
		}
	}
}

//=========================================================================================================================
sp<Piece> Grid::dontPutSameColorDiagonalOrNextToEachOtherReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes)
{//=========================================================================================================================

	//sp<vector<sp<BlockType>>>playingFieldBlockTypes = getCurrentGameType()->getPlayingFieldBlockTypes();
	//sp<vector<sp<PieceType>>>playingFieldPieceTypes = getCurrentGameType()->getPlayingFieldPieceTypes();

	sp<vector<sp<OKColor>>>acceptableColors;
	for (int b = 0; b < (int)blockTypes->size(); b++)
	{
		sp<BlockType> blockType = blockTypes->at(b);

		if (blockType->colors->size()>0)
		{
			int amtColors = (int)blockType->colors->size();
			amtColors = min(amtColors, getGameLogic()->getCurrentDifficulty()->maximumBlockTypeColors);

			for (int i = 0; i < amtColors; i++)
			{

				sp<OKColor> c = blockType->colors->at(i);
				//if (acceptableColors->contains(c) == false)
				//{
				//	acceptableColors->push_back(c);
				//}

				bool contains = false;
				for (int j = 0; j < acceptableColors->size(); j++)
				{
					if (acceptableColors->at(j).get() == c.get())
					{
						contains = true;
					}
				}
				if (contains == false)
				{
					acceptableColors->push_back(c);
				}


			}
		}
	}

	//dont use the same color as downleft, or downright
	if (x > 0 && y > 0 && get(x - 1, y - 1) != nullptr && get(x - 1, y - 1)->getColor() != nullptr)
	{
		//acceptableColors.Remove(get(x - 1,y - 1)->getColor()); //upleft
		sp<OKColor> c = get(x - 1, y - 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (x > 0 && y < getHeight() - 1 && get(x - 1, y + 1) != nullptr && get(x - 1, y + 1)->getColor() != nullptr)
	{
		//acceptableColors.Remove(get(x - 1,y + 1)->getColor()); //downleft
		sp<OKColor> c = get(x - 1, y + 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (x > 0 && get(x - 1, y) != nullptr && get(x - 1, y)->getColor() != nullptr)
	{
		//acceptableColors.Remove(get(x - 1,y)->getColor()); //left
		sp<OKColor> c = get(x - 1, y)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (y < getHeight() - 1 && get(x, y + 1) != nullptr && get(x, y + 1)->getColor() != nullptr)
	{
		//acceptableColors.Remove(get(x,y + 1)->getColor()); //down
		sp<OKColor> c = get(x, y + 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (y > 0 && get(x, y - 1) != nullptr && get(x, y - 1)->getColor() != nullptr)
	{
		//acceptableColors.Remove(get(x,y - 1)->getColor()); //up
		sp<OKColor> c = get(x, y - 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}

	if (acceptableColors->size() > 0)
	{
		sp<OKColor>color = acceptableColors->at(getGameLogic()->getRandomIntLessThan(acceptableColors->size(),"dontPutSameColorDiagonalOrNextToEachOtherReturnNull"));

		if (p == nullptr)
		{
			p = getRandomPiece(pieceTypes, blockTypes);

			//remove other blocks and break connections, we only want one block
			while (p->blocks->size() > 1)
			{
				sp<Block> b = p->blocks->at(p->blocks->size() - 1);
				p->blocks->erase(p->blocks->begin()+p->blocks->size() - 1);
				b->breakConnectionsInPiece();
			}
		}

		for (int i = 0; i < (int)p->blocks->size(); i++)
		{
			sp<Block> b = p->blocks->at(i);
			b->setColor(color);
		}


		return p;
	}
	else
	{

		return nullptr;
	}
}

//=========================================================================================================================
sp<Piece> Grid::dontPutSameColorNextToEachOtherOrReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes)
{//=========================================================================================================================

	sp<vector<sp<OKColor>>>acceptableColors;

	for (int b = 0; b < (int)blockTypes->size(); b++)
	{
		sp<BlockType> blockType = blockTypes->at(b);

		if (blockType->colors->size()>0)
		{
			int amtColors = (int)blockType->colors->size();
			amtColors = min(amtColors, getGameLogic()->getCurrentDifficulty()->maximumBlockTypeColors);

			for (int i = 0; i < amtColors; i++)
			{
				sp<OKColor>c = blockType->colors->at(i);

				bool contains = false;
				for (int j = 0; j < acceptableColors->size(); j++)
				{
					if (acceptableColors->at(j).get() == c.get())
					{
						contains = true;
					}
				}
				if (contains == false)
				{
					acceptableColors->push_back(c);
				}
			}
		}
	}

	//dont use the same color as left, above, or below
	if (x > 0 && get(x - 1, y) != nullptr && get(x - 1, y)->getColor() != nullptr)
	{
		 //left
		sp<OKColor>c = get(x - 1, y)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (y < getHeight() - 1 && get(x, y + 1) != nullptr && get(x, y + 1)->getColor() != nullptr)
	{
		//down
		sp<OKColor>c = get(x, y + 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}
	if (y > 0 && get(x, y - 1) != nullptr && get(x, y - 1)->getColor() != nullptr)
	{
		 //up
		sp<OKColor>c = get(x, y - 1)->getColor();
		//if (acceptableColors->contains(c))acceptableColors->remove(c);
		for (int i = 0; i < acceptableColors->size(); i++)
		{
			if (acceptableColors->at(i).get() == c.get())
			{
				acceptableColors->erase(acceptableColors->begin() + i);
				i--;
			}
		}
	}

	if (acceptableColors->size() > 0)
	{
		sp<OKColor>color = acceptableColors->at(getGameLogic()->getRandomIntLessThan((int)acceptableColors->size(),"dontPutSameColorNextToEachOtherOrReturnNull"));

		if (p == nullptr)
		{
			p = getRandomPiece(pieceTypes, blockTypes);

			//remove other blocks and break connections, we only want one block
			while (p->blocks->size() > 1)
			{
				sp<Block> b = p->blocks->at(p->blocks->size() - 1);
				p->blocks->erase(p->blocks->begin()+p->blocks->size() - 1);
				b->breakConnectionsInPiece();
			}

			for (int i = 0; i < (int)p->blocks->size(); i++)
			{
				sp<Block> b = p->blocks->at(i);
				b->setColor(color);
			}
		}
		else
		{
			for (int i = 0; i < (int)p->blocks->size(); i++)
			{
				sp<Block> b = p->blocks->at(i);

				//if(acceptableColors->contains(b->getColor())==false)
				//	b->setColor(color);

				bool contains = false;
				for (int j = 0; j < acceptableColors->size(); j++)
				{
					if (acceptableColors->at(j).get() == b->getColor().get())
					{
						contains = true;
					}
				}
				if (contains == false)
				{
					b->setColor(color);
				}

			}
		}


		return p;
	}
	else
	{
		return nullptr;
	}
}

//=========================================================================================================================
sp<Piece> Grid::dontPutSameBlockTypeNextToEachOtherOrReturnNull(sp<Piece> p, int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes)
{//=========================================================================================================================

	//sp<vector<sp<BlockType>>>playingFieldBlockTypes = getCurrentGameType()->getPlayingFieldBlockTypes();
	//sp<vector<sp<PieceType>>>playingFieldPieceTypes = getCurrentGameType()->getPlayingFieldPieceTypes();

	//dont use the same color as left, above, or below
	
	
	
	sp<vector<sp<BlockType>>>acceptableBlockTypes = blockTypes;//copy so we can modify it

	if (x > 0)//left
	{
		sp<Block> leftBlock = get(x - 1, y);
		if (leftBlock != nullptr)
		{
			if (acceptableBlockTypes->contains(leftBlock->blockType))
			{
				acceptableBlockTypes->remove(leftBlock->blockType);
			}
		}
	}
	if (y < getHeight() - 1)//down
	{
		sp<Block> downBlock = get(x, y + 1);
		if (downBlock != nullptr) 
		{
			if (acceptableBlockTypes->contains(downBlock->blockType))
			{
				acceptableBlockTypes->remove(downBlock->blockType);
			}
		}
	}
	if (y > 0)//up
	{
		sp<Block> upBlock = get(x, y - 1);
		if (upBlock != nullptr) 
		{
			if (acceptableBlockTypes->contains(upBlock->blockType))
			{
				acceptableBlockTypes->remove(upBlock->blockType);
			}
		}
	}

	if (acceptableBlockTypes->size() > 0)
	{

		if (p != nullptr)
		{
			for (int i = 0; i < (int)p->blocks->size(); i++)
			{
				sp<Block> b = p->blocks->at(i);

				if (acceptableBlockTypes->contains(b->blockType) == false)
				{
					p = nullptr;
					break;
				}	
			}
		}

		if(p == nullptr)
		{
			sp<PieceType> pieceType = getRandomPieceType(pieceTypes);
			sp<BlockType> blockType = acceptableBlockTypes->at(getGameLogic()->getRandomIntLessThan(acceptableBlockTypes->size(), "dontPutSameBlockTypeNextToEachOtherOrReturnNull"));

			p = sp<Piece>(ms<Piece>(game, this, pieceType, blockType));
			p->init();

			//remove other blocks and break connections, we only want one block
			while (p->blocks->size() > 1)
			{
				sp<Block> b = p->blocks->at(p->blocks->size() - 1);
				p->blocks->erase(p->blocks->begin()+p->blocks->size() - 1);
				b->breakConnectionsInPiece();
			}
		}
		

		return p;
	}
	else
	{

		return nullptr;
	}
}

//=========================================================================================================================
void Grid::removeAndDestroyAllBlocksInGrid()
{//=========================================================================================================================

	//List<Piece> piecesInGrid = getArrayOfPiecesOnGrid();
	//for (int i = 0; i < piecesInGrid.Count; i++)
	//{
	//Piece p = piecesInGrid->get(i);
	//p.setBlocksInvisible();
	// }

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);

			if (b != nullptr)
			{
				remove(x, y, true, true);
			}

			if (get(x, y) != nullptr)
			{
				log.error("2 blocks in the same place in deleteAllBlocks() fix this");
			}
		}
	}
}

//=========================================================================================================================
sp<Piece> Grid::putOneBlockPieceInGridCheckingForFillRules(int x, int y, sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes)
{//=========================================================================================================================

	sp<Piece> p = nullptr;
	if (getGameType()->stackDontPutSameColorNextToEachOther)
	{
		p = dontPutSameColorNextToEachOtherOrReturnNull(p, x, y, pieceTypes, blockTypes);
	}
	if (getGameType()->stackDontPutSameBlockTypeNextToEachOther)
	{
		p = dontPutSameBlockTypeNextToEachOtherOrReturnNull(p, x, y, pieceTypes, blockTypes);
	}
	if (getGameType()->stackDontPutSameColorDiagonalOrNextToEachOtherReturnNull)
	{
		p = dontPutSameColorDiagonalOrNextToEachOtherReturnNull(p, x, y, pieceTypes, blockTypes);
	}

	if(p == nullptr)
	{
		p = getRandomPiece(pieceTypes, blockTypes);
		
		//remove other blocks and break connections, we only want one block
		while (p->blocks->size() > 1)
		{
			sp<Block> b = p->blocks->at(p->blocks->size() - 1);
			p->blocks->erase(p->blocks->begin()+p->blocks->size() - 1);
			b->breakConnectionsInPiece();
		}
	}

	if (p != nullptr)
	{
		setPiece(p, x, y);

		if (getGameType()->stackLeaveAtLeastOneGapPerRow)
		{
			bool isFull = true;
			for (int xx = 0; xx < getWidth(); xx++)
			{
				if (get(xx, y) == nullptr)
				{
					isFull = false;
				}
			}

			if (isFull == true)
			{
				remove(getGameLogic()->getRandomIntLessThan(getWidth(),"putOneBlockPieceInGridCheckingForFillRules"), y, false, true);
			}
		}
	}

	return p;
}

//=========================================================================================================================
void Grid::randomlyFillGridWithPlayingFieldPieces(int numberOfBlocks, int topY)
{//=========================================================================================================================

	topY += GameLogic::aboveGridBuffer;

	int fieldSize = getWidth() * max((getHeight() - topY), 0);

	//override settings amount of prefilled pieces if there are already pieces on the grid.
	int num = getNumberOfFilledCells();
	if (num > 0)
	{
		if(num < numberOfBlocks)
		{
			numberOfBlocks = num;
		}
	}

	if (numberOfBlocks >= fieldSize)
	{
		numberOfBlocks = fieldSize - 1;
	}

	if (numberOfBlocks < 0)numberOfBlocks = 0;

	//get old blocks and remove them
	sp<vector<sp<Block>>>blockList;
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (contains(x, y))//TODO redundant but trying to find all bad accesses
			{
				sp<Block> b = remove(x, y, false, true);
				if (b != nullptr)
				{
					if (blockList->contains(b) == false)
					{
						blockList->push_back(b);
					}
				}
			}
		}
	}

	sp<vector<sp<BlockType>>>playingFieldBlockTypes = getGameType()->getPlayingFieldBlockTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<PieceType>>>playingFieldPieceTypes = getGameType()->getPlayingFieldPieceTypes(getGameLogic()->getCurrentDifficulty());

	//randomly put roughly the same amount of blocks into playing field (a piece at a time)
	for (int i = 0; i < numberOfBlocks; i++)
	{
		int r = getGameLogic()->getRandomIntLessThan(fieldSize,"randomlyFillGridWithPlayingFieldPieces for");

		int x = r % getWidth();
		int y = (r / getWidth()) + topY;

		int attempt = 0;
		while (get(x, y) != nullptr && attempt < fieldSize)
		{
			r = getGameLogic()->getRandomIntLessThan(fieldSize, "randomlyFillGridWithPlayingFieldPieces while");

			x = r % getWidth();
			y = (r / getWidth()) + topY;

			attempt++;
		}

		if (get(x, y) == nullptr)
		{
			//sp<Piece> p = getRandomPiece(playingFieldPieceTypes, playingFieldBlockTypes);
			sp<Piece> p = putOneBlockPieceInGridCheckingForFillRules(x, y, playingFieldPieceTypes, playingFieldBlockTypes);
			if(p!=nullptr)i += (int)p->blocks->size()-1;//-1 because we already increment i in the loop
		}
	}

	//set the new blocks to the old blocks lastX lastY so there is a neat animation
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr && blockList->size() > 0)
			{
				sp<Block> a = blockList->at(0);
				blockList->erase(blockList->begin()+0);

				b->lastScreenX = a->lastScreenX;
				b->lastScreenY = a->lastScreenY;
				b->ticksSinceLastMovement = 0;
			}
		}
	}

}

//=========================================================================================================================
void Grid::buildRandomStackRetainingExistingBlocks(int numberOfBlocks, int topY)
{//=========================================================================================================================

	topY += GameLogic::aboveGridBuffer;

	//draw grid one block offscreen to allow for scroll
	//getScreenY+=cellH();
	scrollPlayingFieldY = 0;

	//don't put same colors in row or column of 3
	//don't put spaces

	int fieldSize = getWidth() * max((getHeight() - topY),0);

	//override settings amount of prefilled pieces if there are already pieces on the grid.
	int num = getNumberOfFilledCells();
	if (num > 0)
	{
		if (num < numberOfBlocks)
		{
			numberOfBlocks = num;
		}
	}

	if (numberOfBlocks >= fieldSize)
	{
		numberOfBlocks = fieldSize - 1;
	}

	if (numberOfBlocks < 0)numberOfBlocks = 0;

	//get old blocks and remove them
	sp<vector<sp<Block>>>blockList;
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (contains(x, y))//TODO redundant but trying to find all bad accesses
			{
				sp<Block> b = remove(x, y, false, true);
				if (b != nullptr)
				{
					if (blockList->contains(b) == false)
					{
						blockList->push_back(b);
					}
				}
			}
		}
	}


	sp<vector<sp<BlockType>>>playingFieldBlockTypes = getGameType()->getPlayingFieldBlockTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<PieceType>>>playingFieldPieceTypes = getGameType()->getPlayingFieldPieceTypes(getGameLogic()->getCurrentDifficulty());



	int blocksPlaced = 0;
	for (int y = getHeight() - 1; y >= topY; y--)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (get(x, y) != nullptr)
			{
				blocksPlaced++;
				continue;
			}
			else
			{
				//sp<Piece> p = getRandomPiece(playingFieldPieceTypes, playingFieldBlockTypes);
				sp<Piece> p = putOneBlockPieceInGridCheckingForFillRules(x, y, playingFieldPieceTypes, playingFieldBlockTypes);
				if(p!=nullptr)blocksPlaced += (int)p->blocks->size();
			}
		}
	}

	while (blocksPlaced > numberOfBlocks)
	{
		//pick random column
		int x = getGameLogic()->getRandomIntLessThan(getWidth(),"buildRandomStackRetainingExistingBlocks");

		//remove first piece
		for (int y = 0; y < getHeight() && blocksPlaced > numberOfBlocks; y++)
		{
			if (get(x, y) != nullptr)
			{
				//sp<Block> b =
                remove(x, y, false, true);

				blocksPlaced--;
				break;
			}
		}
	}




	//set the new blocks to the old blocks lastX lastY so there is a neat animation
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr && blockList->size() > 0)
			{
				sp<Block> a = blockList->at(0);
				blockList->erase(blockList->begin()+0);

				b->lastScreenX = a->lastScreenX;
				b->lastScreenY = a->lastScreenY;
				b->ticksSinceLastMovement = 0;
			}
		}
	}

}

//=========================================================================================================================
bool Grid::scrollUpStack(sp<Piece> cursorPiece, int amt)
{//=========================================================================================================================

	scrollPlayingFieldY -= amt;

	// all pieces set lastY so it isnt blurry
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr)
			{
				b->lastScreenY = b->getScreenY();
			}
		}
	}

	if (scrollPlayingFieldY < 0 - scrollBlockIncrement)
	{
		//die if there is a piece at the top
		for (int x = 0; x < getWidth(); x++)
		{
			if (get(x, GameLogic::aboveGridBuffer) != nullptr)
			{
				scrollPlayingFieldY = 0 - scrollBlockIncrement;
				return false;
			}
		}

		cursorPiece->yGrid -= 1;
		if (cursorPiece->yGrid < 1 + GameLogic::aboveGridBuffer)
		{
			cursorPiece->yGrid += 1;
		}

		scrollPlayingFieldY += scrollBlockIncrement;

		//move all pieces up
		for (int y = 0; y < getHeight() - 1; y++)
		{
			for (int x = 0; x < getWidth(); x++)
			{
				if (contains(x, y + 1))//TODO redundant but trying to find all bad accesses
				{
					sp<Block> b = remove(x, y + 1, false, false);
					if (b != nullptr)
					{
						add(x, y, b);

						// all pieces set lastY so it isnt blurry
						//b.lastScreenX = b.getScreenX();
						//b.lastScreenY = b.getScreenY();
					}
				}
			}
		}

		sp<vector<sp<BlockType>>>playingFieldBlockTypes = getGameType()->getPlayingFieldBlockTypes(getGameLogic()->getCurrentDifficulty());
		sp<vector<sp<PieceType>>>playingFieldPieceTypes = getGameType()->getPlayingFieldPieceTypes(getGameLogic()->getCurrentDifficulty());

		{
			//create new row of pieces at bottom
			int y = getHeight() - 1;
			for (int x = 0; x < getWidth(); x++)
			{
				//sp<Piece> p = getRandomPiece(playingFieldPieceTypes, playingFieldBlockTypes);
				//sp<Piece> p =
                putOneBlockPieceInGridCheckingForFillRules(x, y, playingFieldPieceTypes, playingFieldBlockTypes);
			}
		}

		getGameLogic()->piecesMadeThisGame++;
	}

	return true;
}

//=========================================================================================================================
sp<Piece> Grid::putGarbageBlock(int x, int y)
{//=========================================================================================================================

	sp<vector<sp<BlockType>>>garbageBlockTypes = getGameType()->getGarbageBlockTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<PieceType>>>garbagePieceTypes = getGameType()->getGarbagePieceTypes(getGameLogic()->getCurrentDifficulty());

	//sp<Piece> p = getRandomPiece(garbagePieceTypes, garbageBlockTypes);
	sp<Piece> p = putOneBlockPieceInGridCheckingForFillRules(x, y, garbagePieceTypes, garbageBlockTypes);

	return p;
}

//=========================================================================================================================
void Grid::makeGarbageRowFromCeiling()
{//=========================================================================================================================
	int y = 0;// + GameLogic::aboveGridBuffer;
	for (int x = 0; x < getWidth(); x++)
	{
		sp<Piece> p = putGarbageBlock(x, y);

		if (p != nullptr)
		{
			for (int i = 0; i < p->getNumBlocksInCurrentRotation() && i < p->blocks->size(); i++)
			{
				sp<Block> b = p->blocks->at(i);

				b->lastScreenX = getXInFBO() + (b->xGrid) * cellW();
				b->lastScreenY = getYInFBO() + b->yInPiece*cellH();
				b->ticksSinceLastMovement = 0;
			}
		}
	}
}

//=========================================================================================================================
void Grid::moveAllRowsUpOne()
{//=========================================================================================================================

	//remove any blocks on top row
	for (int x = 0; x < getWidth(); x++)
	{
		if (contains(x,0))
		{
			sp<Block> b = get(x, 0);
			remove(b, true, true);
		}
	}

	//move all pieces up
	for (int y = 0; y < getHeight() - 1; y++) //height - 1 because y+1 below, it grabs the next row down
	{
		for (int x = 0; x < getWidth(); x++)
		{
			if (contains(x,y+1))
			{
				sp<Block> b = remove(x, y + 1, false, false);
				add(x, y, b);
			}
		}
	}
}

//=========================================================================================================================
void Grid::putGarbageBlockFromFloor(int x, int y)
{//=========================================================================================================================
	sp<Piece> p = putGarbageBlock(x, y);

	if (p != nullptr)
	{
		for (int i = 0; i < p->getNumBlocksInCurrentRotation() && i < p->blocks->size(); i++)
		{
			sp<Block> b = p->blocks->at(i);

			b->lastScreenX = getXInFBO() + (b->xGrid) * cellW();
			b->lastScreenY = getYInFBO() + b->yInPiece*cellH() + getHeight()*cellH();
			b->ticksSinceLastMovement = 0;
		}
	}
}

//=========================================================================================================================
void Grid::makeGarbageRowFromFloor()
{//=========================================================================================================================

	//move all rows up one
	moveAllRowsUpOne();

	{
		//make last row filled depending on garbage rule

		if (getGameType()->playingFieldGarbageType == GarbageType::MATCH_BOTTOM_ROW) //copies bottom row
		{
			int y = getHeight() - 1;
			for (int x = 0; x < getWidth(); x++)
			{
				if (get(x, y - 1) != nullptr)
				{
					putGarbageBlockFromFloor(x, y);
				}
			}
		}

		if (getGameType()->playingFieldGarbageType == GarbageType::RANDOM) //each block is random yes/no
		{
			int y = getHeight() - 1;
			for (int x = 0; x < getWidth(); x++)
			{
				int r = getGameLogic()->getRandomIntLessThan(2,"makeGarbageRowFromFloor");

				if (r == 0)
				{
					putGarbageBlockFromFloor(x, y);
				}
			}
		}

		if (getGameType()->playingFieldGarbageType == GarbageType::ZIGZAG_PATTERN) //this is a zig-zag pattern with one hole
		{
			int y = getHeight() - 1;
			for (int x = 0; x < getWidth(); x++)
			{
				if (x != lastGarbageHoleX)
				{
					putGarbageBlockFromFloor(x, y);
				}
			}

			if (garbageHoleDirectionToggle)
			{
				lastGarbageHoleX++;
				if (lastGarbageHoleX >= getWidth())
				{
					lastGarbageHoleX = getWidth() - 1;
					garbageHoleDirectionToggle = !garbageHoleDirectionToggle;
				}
			}
			else
			{
				lastGarbageHoleX--;
				if (lastGarbageHoleX < 0)
				{
					lastGarbageHoleX = 0;
					garbageHoleDirectionToggle = !garbageHoleDirectionToggle;
				}
			}
		}

	}
}

//=========================================================================================================================
void Grid::cursorSwapBetweenTwoBlocksHorizontal(sp<Piece> cursor)
{//=========================================================================================================================

	sp<Block> a = get(cursor->xGrid, cursor->yGrid);
	sp<Block> b = get(cursor->xGrid + 1, cursor->yGrid);

	if (a != nullptr && a->interpolateSwappingWithX == 0 && a->flashingToBeRemoved == false)
	{
		if (b == nullptr || b->interpolateSwappingWithX == 0)
		{
			a->interpolateSwappingWithX = 1;
		}
	}

	if (b != nullptr && b->interpolateSwappingWithX == 0 && b->flashingToBeRemoved == false)
	{
		if (a == nullptr || a->interpolateSwappingWithX == 1)
		{
			b->interpolateSwappingWithX = -1;
		}
	}

	//		remove(currentPiece.x,currentPiece.y);
	//		remove(currentPiece.x+1,currentPiece.y);

	//		add(currentPiece.x,currentPiece.y,b);
	//		add(currentPiece.x+1,currentPiece.y,a);
}
//=========================================================================================================================
void Grid::cursorSwapBetweenTwoBlocksVertical(sp<Piece> cursor)
{//=========================================================================================================================

	sp<Block> a = get(cursor->xGrid, cursor->yGrid);
	sp<Block> b = get(cursor->xGrid, cursor->yGrid+1);

	if (a != nullptr && a->interpolateSwappingWithY == 0 && a->flashingToBeRemoved == false)
	{
		if (b == nullptr || b->interpolateSwappingWithY == 0)
		{
			a->interpolateSwappingWithY = 1;
		}
	}

	if (b != nullptr && b->interpolateSwappingWithY == 0 && b->flashingToBeRemoved == false)
	{
		if (a == nullptr || a->interpolateSwappingWithY == 1)
		{
			b->interpolateSwappingWithY = -1;
		}
	}
}

//=========================================================================================================================
void Grid::cursorSwapBetweenThreeBlocksHorizontal(sp<Piece> cursor, MovementType rotation)
{//=========================================================================================================================

	sp<Block> a = get(cursor->xGrid - 1, cursor->yGrid);
	sp<Block> b = get(cursor->xGrid, cursor->yGrid);
	sp<Block> c = get(cursor->xGrid + 1, cursor->yGrid);

	if (rotation == MovementType::ROTATE_CLOCKWISE)
	{
		if (a != nullptr && a->interpolateSwappingWithX == 0 && a->flashingToBeRemoved == false)
		{
			if (b == nullptr || b->interpolateSwappingWithX == 0)
			{
				a->interpolateSwappingWithX = 1;
			}
		}

		if (b != nullptr && b->interpolateSwappingWithX == 0 && b->flashingToBeRemoved == false)
		{
			if (c == nullptr || c->interpolateSwappingWithX == -2)
			{
				b->interpolateSwappingWithX = 1;
			}
		}

		if (c != nullptr && c->interpolateSwappingWithX == 0 && c->flashingToBeRemoved == false)
		{
			if (a == nullptr || a->interpolateSwappingWithX == 1)
			{
				c->interpolateSwappingWithX = -2;
			}
		}
	}

	if (rotation == MovementType::ROTATE_COUNTERCLOCKWISE)
	{
		if (a != nullptr && a->interpolateSwappingWithX == 0 && a->flashingToBeRemoved == false)
		{
			if (c == nullptr || c->interpolateSwappingWithX == -1)
			{
				a->interpolateSwappingWithX = 2;
			}
		}

		if (b != nullptr && b->interpolateSwappingWithX == 0 && b->flashingToBeRemoved == false)
		{
			if (a == nullptr || a->interpolateSwappingWithX == 2)
			{
				b->interpolateSwappingWithX = -1;
			}
		}

		if (c != nullptr && c->interpolateSwappingWithX == 0 && c->flashingToBeRemoved == false)
		{
			if (b == nullptr || b->interpolateSwappingWithX == -1)
			{
				c->interpolateSwappingWithX = -1;
			}
		}
	}

	//		remove(currentPiece.x,currentPiece.y);
	//		remove(currentPiece.x+1,currentPiece.y);

	//		add(currentPiece.x,currentPiece.y,b);
	//		add(currentPiece.x+1,currentPiece.y,a);
}
//=========================================================================================================================
void Grid::cursorSwapBetweenThreeBlocksVertical(sp<Piece> cursor, MovementType rotation)
{//=========================================================================================================================

	sp<Block> a = get(cursor->xGrid, cursor->yGrid - 1);
	sp<Block> b = get(cursor->xGrid, cursor->yGrid);
	sp<Block> c = get(cursor->xGrid, cursor->yGrid + 1);

	if (rotation == MovementType::ROTATE_CLOCKWISE)
	{
		if (a != nullptr && a->interpolateSwappingWithY == 0 && a->flashingToBeRemoved == false)
		{
			if (b == nullptr || b->interpolateSwappingWithY == 0)
			{
				a->interpolateSwappingWithY = 1;
			}
		}

		if (b != nullptr && b->interpolateSwappingWithY == 0 && b->flashingToBeRemoved == false)
		{
			if (c == nullptr || c->interpolateSwappingWithY == -2)
			{
				b->interpolateSwappingWithY = 1;
			}
		}

		if (c != nullptr && c->interpolateSwappingWithY == 0 && c->flashingToBeRemoved == false)
		{
			if (a == nullptr || a->interpolateSwappingWithY == 1)
			{
				c->interpolateSwappingWithY = -2;
			}
		}
	}

	if (rotation == MovementType::ROTATE_COUNTERCLOCKWISE)
	{
		if (a != nullptr && a->interpolateSwappingWithY == 0 && a->flashingToBeRemoved == false)
		{
			if (c == nullptr || c->interpolateSwappingWithY == -1)
			{
				a->interpolateSwappingWithY = 2;
			}
		}

		if (b != nullptr && b->interpolateSwappingWithY == 0 && b->flashingToBeRemoved == false)
		{
			if (a == nullptr || a->interpolateSwappingWithY == 2)
			{
				b->interpolateSwappingWithY = -1;
			}
		}

		if (c != nullptr && c->interpolateSwappingWithY == 0 && c->flashingToBeRemoved == false)
		{
			if (b == nullptr || b->interpolateSwappingWithY == -1)
			{
				c->interpolateSwappingWithY = -1;
			}
		}
	}
}

//=========================================================================================================================
void Grid::cursorSwapHoldingBlockWithGrid(sp<Piece> cursor)
{//=========================================================================================================================

	int x = cursor->xGrid;
	int y = cursor->yGrid;

	sp<Block> gridBlock = get(x, y);

	if (gridBlock != nullptr && gridBlock->flashingToBeRemoved == true)
	{
		return;
	}

	sp<Block> heldBlock = cursor->holdingBlock;
	cursor->holdingBlock = gridBlock;

	if (gridBlock != nullptr)
	{
		remove(x, y, false, false);
	}

	if (heldBlock != nullptr)
	{
		add(x, y, heldBlock);
	}
}

//=========================================================================================================================
void Grid::cursorRotateBlocks(sp<Piece> cursor, MovementType rotation)
{//=========================================================================================================================

	sp<Block> a = get(cursor->xGrid, cursor->yGrid);
	sp<Block> b = get(cursor->xGrid + 1, cursor->yGrid);
	sp<Block> c = get(cursor->xGrid, cursor->yGrid + 1);
	sp<Block> d = get(cursor->xGrid + 1, cursor->yGrid + 1);

	if (a != nullptr && a->flashingToBeRemoved == true)
	{
		return;
	}
	if (b != nullptr && b->flashingToBeRemoved == true)
	{
		return;
	}
	if (c != nullptr && c->flashingToBeRemoved == true)
	{
		return;
	}
	if (d != nullptr && d->flashingToBeRemoved == true)
	{
		return;
	}

	if (rotation == MovementType::ROTATE_CLOCKWISE)
	{
		a = remove(cursor->xGrid, cursor->yGrid, false, false);
		b = remove(cursor->xGrid + 1, cursor->yGrid, false, false);
		c = remove(cursor->xGrid, cursor->yGrid + 1, false, false);
		d = remove(cursor->xGrid + 1, cursor->yGrid + 1, false, false);

		if (a != nullptr)add(cursor->xGrid + 1, cursor->yGrid, a);
		if (b != nullptr)add(cursor->xGrid + 1, cursor->yGrid + 1, b);
		if (c != nullptr)add(cursor->xGrid, cursor->yGrid, c);
		if (d != nullptr)add(cursor->xGrid, cursor->yGrid + 1, d);
	}
	if (rotation == MovementType::ROTATE_COUNTERCLOCKWISE)
	{
		a = remove(cursor->xGrid, cursor->yGrid, false, false);
		b = remove(cursor->xGrid + 1, cursor->yGrid, false, false);
		c = remove(cursor->xGrid, cursor->yGrid + 1, false, false);
		d = remove(cursor->xGrid + 1, cursor->yGrid + 1, false, false);

		if (a != nullptr)add(cursor->xGrid, cursor->yGrid + 1, a);
		if (b != nullptr)add(cursor->xGrid, cursor->yGrid, b);
		if (c != nullptr)add(cursor->xGrid + 1, cursor->yGrid + 1, c);
		if (d != nullptr)add(cursor->xGrid + 1, cursor->yGrid, d);
	}
}

//=========================================================================================================================
bool Grid::continueSwappingBlocks()
{//=========================================================================================================================

	//TODO: might want to make swapping instantaneous, why do i do it this way?  so there is a delay on the combo detection i guess

	bool swappingAny = false;

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> a = get(x, y);
			if (a != nullptr)
			{
				if (a->interpolateSwappingWithX != 0)
				{
					sp<Block> b = get(x + a->interpolateSwappingWithX, y);

					swappingAny = true;

					if (a->swapTicks < 17 * 6) // 6 frames from start to finish
					{
						a->swapTicks += getGameLogic()->ticks();
						if (b != nullptr)
						{
							b->swapTicks = a->swapTicks;
						}
					}
					else
					{
						a->swapTicks = 0;
						if (b != nullptr)
						{
							b->swapTicks = 0;
						}

						remove(x, y, false, false);//remove a

						if (contains(x + a->interpolateSwappingWithX,y))//TODO redundant but trying to find all bad accesses
						remove(x + a->interpolateSwappingWithX, y, false, false);

						if(b!=nullptr)add(x, y, b);
						add(x + a->interpolateSwappingWithX, y, a);

						a->interpolateSwappingWithX = 0;
						if (b != nullptr)
						{
							b->interpolateSwappingWithX = 0;
						}
					}
				}

				if (a->interpolateSwappingWithY != 0)
				{
					sp<Block> b = get(x, y + a->interpolateSwappingWithY);

					swappingAny = true;

					if (a->swapTicks < 17 * 6) // 6 frames from start to finish
					{
						a->swapTicks += getGameLogic()->ticks();
						if (b != nullptr)
						{
							b->swapTicks = a->swapTicks;
						}
					}
					else
					{
						a->swapTicks = 0;
						if (b != nullptr)
						{
							b->swapTicks = 0;
						}

						remove(x, y, false, false);//remove a

						if (contains(x, y + a->interpolateSwappingWithY))//TODO redundant but trying to find all bad accesses
							remove(x, y + a->interpolateSwappingWithY, false, false);

						if (b != nullptr)add(x, y, b);
						add(x, y + a->interpolateSwappingWithY, a);

						a->interpolateSwappingWithY = 0;
						if (b != nullptr)
						{
							b->interpolateSwappingWithY = 0;
						}
					}

				}
			}
		}
	}

	return swappingAny;
}

//=========================================================================================================================
void Grid::scrollBackground()
{//=========================================================================================================================

	scrollPlayingFieldBackgroundTicks += getGameLogic()->ticks();

	if (scrollPlayingFieldBackgroundTicks > scrollPlayingFieldBackgroundTicksSpeed)
	{
		scrollPlayingFieldBackgroundTicks = 0;

		// scroll the playingfield background (annoying scrolling blocks)
		if (backgroundScrollX <= 0)
		{
			backgroundScrollX = (cellW() - 1);
		}
		else
		{
			backgroundScrollX--;
		}

		if (backgroundScrollY <= 0)
		{
			backgroundScrollY = (cellH() - 1);
		}
		else
		{
			backgroundScrollY--;
		}
	}
}

//=========================================================================================================================
void Grid::shakeSmall()
{//=========================================================================================================================

	setShakePlayingField(120, 2, 2, 40);//from miniGameEngine

	if(getGameLogic()->player->gameController!=nullptr)
	{
		getGameLogic()->getControlsManager()->doHaptic(getGameLogic()->player->gameController, 120*3, 32767/2, 10, 120, 40);
	}

//	if (effectShakeDurationTicks == 0)
//	{
//		effectShakeDurationTicks = 300;
//	}
//	if (effectShakeMaxX == 0)
//	{
//		effectShakeMaxX = (int)(3 * (GLUtils::getViewportWidth() / 320));
//	}
//	if (effectShakeMaxY == 0)
//	{
//		effectShakeMaxY = (int)(3 * (GLUtils::getViewportWidth() / 320));
//	}
}

//=========================================================================================================================
void Grid::shakeMedium()
{//=========================================================================================================================

	setShakePlayingField(300, 4, 2, 60);//from miniGameEngine

	if (getGameLogic()->player->gameController != nullptr)
	{
		getGameLogic()->getControlsManager()->doHaptic(getGameLogic()->player->gameController, 300*4, 32767/2, 10, 300, 60);
	}
}

//=========================================================================================================================
void Grid::shakeHard()
{//=========================================================================================================================
	setShakePlayingField(600, 10, 10, 60);//from miniGameEngine

	if (getGameLogic()->player->gameController != nullptr)
	{
		getGameLogic()->getControlsManager()->doHaptic(getGameLogic()->player->gameController, 600*4, 32767, 10, 600, 60);
	}
//	effectShakeDurationTicks = 600;
//	effectShakeMaxX = (int)(20 * (GLUtils::getViewportWidth() / 320));
//	effectShakeMaxY = (int)(20 * (GLUtils::getViewportWidth() / 320));
}

//void MiniGameEngine::shakeSmall()
//{ //=========================================================================================================================
//  //getGameEngine()->getCameraman()->setShakeScreen(300,10,10,60);
//}
//
//void MiniGameEngine::shakeHard()
//{ //=========================================================================================================================
//  //getGameEngine()->getCameraman()->setShakeScreen(600,20,20,60);
//}
//void OKGameStadium::shakeSmall()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.1f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(300, 2, 2, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}
//
//void OKGameStadium::shakeHard()
//{ //=========================================================================================================================
//	getClientGameEngine()->getCameraman()->popZOOMto = getClientGameEngine()->getCameraman()->getZoom() - 0.5f;
//	getClientGameEngine()->getCameraman()->setShakeScreen(1000, 5, 5, 30);
//	getClientGameEngine()->getCinematicsManager()->fadeColorFromTransparentToAlphaBackToTransparent(200, 255, 255, 255, 0.5f);
//}

void Grid::setShakePlayingField(int ticksDuration, int maxX, int maxY, int ticksPerShake)
{ //=========================================================================================================================

	if (shakePlayingFieldScreenTicksCounter == 0)
	{
		shakePlayingFieldStartTime = System::currentHighResTimer();
	}

	shakePlayingFieldScreenTicksCounter += ticksDuration;

	shakePlayingFieldTicksDuration = shakePlayingFieldScreenTicksCounter;

	shakePlayingFieldMaxX = maxX;
	shakePlayingFieldMaxY = maxY;

	shakePlayingFieldTicksPerShake = ticksPerShake;
}

void Grid::updateShake()
{ //=========================================================================================================================
	if (shakePlayingFieldScreenTicksCounter > 0)
	{
		shakePlayingFieldScreenTicksCounter -= (int)getGameLogic()->ticks();
		if (shakePlayingFieldScreenTicksCounter < 0)
		{
			shakePlayingFieldScreenTicksCounter = 0;
		}

		long long startTime = shakePlayingFieldStartTime;
		long long currentTime = System::currentHighResTimer();
		int ticksPassed = (int)(System::getTicksBetweenTimes(startTime, currentTime) * getGameLogic()->getOKGame()->engineSpeed);

		double xOverShakeTime = (Easing::easeInOutCircular(shakePlayingFieldTicksDuration/2 + ticksPassed, 0, shakePlayingFieldMaxX, shakePlayingFieldTicksDuration*2));
		double yOverShakeTime = (Easing::easeInOutCircular(shakePlayingFieldTicksDuration/2 + ticksPassed, 0, shakePlayingFieldMaxY, shakePlayingFieldTicksDuration*2));

		shakePlayingFieldTicksPerShakeXCounter += (int)getGameLogic()->ticks();
		if (shakePlayingFieldTicksPerShakeXCounter > shakePlayingFieldTicksPerShake)
		{
			shakePlayingFieldTicksPerShakeXCounter = 0;
			shakePlayingFieldLeftRightToggle = !shakePlayingFieldLeftRightToggle;
		}

		shakePlayingFieldTicksPerShakeYCounter += (int)getGameLogic()->ticks(); //y shakes at half speed
		if (shakePlayingFieldTicksPerShakeYCounter > shakePlayingFieldTicksPerShake * 2)
		{
			shakePlayingFieldTicksPerShakeYCounter = 0;

			shakePlayingFieldUpDownToggle = !shakePlayingFieldUpDownToggle;
		}

		double xThisTime = (Easing::easeInOutCircular(shakePlayingFieldTicksPerShakeXCounter, 0, xOverShakeTime, shakePlayingFieldTicksPerShake));
		double yThisTime = (Easing::easeInOutCircular(shakePlayingFieldTicksPerShakeYCounter, 0, yOverShakeTime, shakePlayingFieldTicksPerShake * 2));

		if (shakePlayingFieldLeftRightToggle)
		{
			shakePlayingFieldX = (int)xThisTime;
		}
		else
		{
			shakePlayingFieldX = (int)(0 - xThisTime);
		}
		if (shakePlayingFieldUpDownToggle)
		{
			shakePlayingFieldY = (int)yThisTime;
		}
		else
		{
			shakePlayingFieldY = (int)(0 - yThisTime);
		}
		if (shakePlayingFieldX > shakePlayingFieldMaxX || shakePlayingFieldX < 0-shakePlayingFieldMaxX)shakePlayingFieldX = 0;
		if (shakePlayingFieldY > shakePlayingFieldMaxY || shakePlayingFieldY < 0-shakePlayingFieldMaxY)shakePlayingFieldY = 0;
	}
	else
	{
		shakePlayingFieldX = 0;
		shakePlayingFieldY = 0;
	}


//	if (effectShakeDurationTicks > 0)
//	{
//		effectShakeTicksCounter += getGameLogic()->ticks();
//
//
//		if (effectShakeTicksCounter > effectShakeDurationTicks)
//		{
//			effectShakeTicksCounter = 0;
//			effectShakeDurationTicks = 0;
//			effectShakeX = 0;
//			effectShakeY = 0;
//			effectShakeMaxX = 0;
//			effectShakeMaxY = 0;
//		}
//	}
}

//=========================================================================================================================
void Grid::wigglePlayingField()
{//=========================================================================================================================

	wigglePlayingFieldTicks += getGameLogic()->ticks();

	if (wigglePlayingFieldTicks > wigglePlayingFieldTicksSpeed)
	{
		wigglePlayingFieldTicks = 0;

		if (wigglePlayingFieldLeftRightToggle == false)
		{
			wigglePlayingFieldX++;
			if (wigglePlayingFieldX > wigglePlayingFieldMaxX)
			{
				wigglePlayingFieldLeftRightToggle = true;
				wigglePlayingFieldX--;
			}
		}
		else
		{
			wigglePlayingFieldX--;
			if (wigglePlayingFieldX < -wigglePlayingFieldMaxX)
			{
				wigglePlayingFieldLeftRightToggle = false;
				wigglePlayingFieldX++;
			}
		}
	}
}

//=========================================================================================================================
void Grid::add(int x, int y, sp<Block> b)
{//=========================================================================================================================
	if (b == nullptr || b == nullBlock)
	{
		log.error("Trying to add a null block to the grid");
		return;
	}

	b->xGrid = x;
	b->yGrid = y;
	b->grid = shared_from_this();

	if (x < 0 || y < 0)
	{
		log.error("Trying to add a negative xy value block to the grid");
		return; //don't put negative values in grid, but still set the xGrid yGrid since it's still attached to the piece.
	}

	if (x >= getWidth() || y >= getHeight())
	{
		log.error("Trying to add a block to the grid with xy value outside the grid");
		return;
	}

	if (contains(x,y))
	{
		log.error("Trying to add a block in an occupied xy value.");
		return;
	}

#ifdef blocksHashMap
	blocks.put(y * getWidth() + x, b);
#else
	blocks->erase(blocks->begin()+y * getWidth() + x);//remove nullBlock
	blocks->insert(blocks->begin()+(y * getWidth() + x), b);
#endif

}
//=========================================================================================================================
bool Grid::contains(int x, int y)
{//=========================================================================================================================

//	if (x < 0 || y < 0)
//	{
//		log.error("Trying to get a block with xy value less than 0");
//		return false;
//	}
//
//
//	if (x >= getWidth() || y >= getHeight())
//	{
//		log.error("Trying to get a block from the grid with xy value greater than width or height");
//		return false;
//	}

	return contains(y * getWidth() + x);
}

//=========================================================================================================================
bool Grid::contains(int index)
{//=========================================================================================================================


//	if (index < 0)
//	{
//		log.error("Trying to get a block with index value less than 0");
//		return false;
//	}
//	if (index >= blocks->size())
//	{
//		log.error("Trying to get a block from the grid with index greater than size");
//		return false;
//	}

	bool exists = false;

#ifdef blocksHashMap
		exists = blocks.containsKey(index);
#else
		exists = blocks->at(index)!=nullBlock;
#endif

	if (exists)
	{
		return true;
	}
	else
	{
		return false;
	}

}

//=========================================================================================================================
sp<Block> Grid::get(int x, int y)
{//=========================================================================================================================

	if (x < 0 || y < 0)
	{
		log.error("Trying to get a block with xy value less than 0");
		return nullptr;
	}

	if (x >= getWidth() || y >= getHeight())
	{
		log.error("Trying to get a block from the grid with xy value greater than width or height");
		return nullptr;
	}

	//if (contains(x,y))
	{
#ifdef blocksHashMap
			sp<Block> b = blocks->at(y * getWidth() + x);
			return b;
#else
		sp<Block> b = blocks->at(y * getWidth() + x);
		if (b == nullBlock)return nullptr;
		return b;
#endif
	}
	//else
	{
		return nullptr;
	}
}

//=========================================================================================================================
sp<Block> Grid::remove(int x, int y, bool fadeOut, bool breakConnections)
{//=========================================================================================================================

	//Debug.log("remove("+x+","+y+","+fadeOut+","+breakConnections+")");

	if (x < 0 || y < 0)
	{
		log.error("Trying to remove a block outside of bounds");
		return nullptr;
	}
	else
	{
		if (contains(x,y) == false)
		{
			//log.error("Trying to remove a block that doesnt exist");

			return nullptr;
		}
		else
		{
			sp<Block> b = blocks->at(y * getWidth() + x);
			blocks->erase(blocks->begin()+y * getWidth() + x);

#ifdef blocksHashMap
#else
			blocks->insert(blocks->begin()+(y * getWidth() + x), nullBlock);
#endif

			if (fadeOut) 
			{
				b->fadingOut = true;

				if (getGameLogic()->fadingOutBlocks->contains(b) == false)
				{
					getGameLogic()->fadingOutBlocks->push_back(b);
				}
			}

			if (breakConnections)
			{
				b->breakConnectionsInPiece();
			}

			if (blocks->containsValue(b))
  			{
  				log.error("Grid still contains block after removing it. Figure out why!");
			}

			return b;
		}
	}
}

//=========================================================================================================================
void Grid::remove(sp<Block> b, bool fadeOut, bool breakConnections)
{//=========================================================================================================================

	if (b->xGrid < 0 || b->yGrid < 0)
	{
		log.error("Trying to remove a block outside of bounds");
		return;
	}

	sp<Block> c = remove(b->xGrid, b->yGrid, fadeOut, breakConnections);

	if (c == nullptr)
	{
		log.warn("Trying to remove null block at " + to_string(b->xGrid) + "," + to_string(b->yGrid) + " Block trying to remove name: " + b->blockType->name + " Current game:" + getGameLogic()->currentGameType->name + " Previous game:" + getGameLogic()->previousGameString);
		return;
	}

	if (c != b)
	{
		string blockInGridName = c->blockType->name;
		log.error("Removed block at " + to_string(b->xGrid) + "," + to_string(b->yGrid) + " does not match requested block, must have been two blocks in the same space"+" Block trying to remove name: "+b->blockType->name+" Block in grid name: "+blockInGridName+ " Current game:" + getGameLogic()->currentGameType->name + " Previous game:" + getGameLogic()->previousGameString);
	}
}

//=========================================================================================================================
void Grid::moveToAndRemoveAndFadeOut(sp<Block> b, int x, int y)
{//=========================================================================================================================
	b->lastScreenX = b->getScreenX();
	b->lastScreenY = b->getScreenY();
	b->ticksSinceLastMovement = 0;

	add(x, y, b);
	remove(b, true, true);
}

//=========================================================================================================================
bool Grid::checkLine(int y)
{//=========================================================================================================================

	for (int x = 0; x < getWidth(); x++)
	{
		if (get(x, y) == nullptr)
		{
			return false;
		}
	}

	return true;
}

//=========================================================================================================================
sp<vector<sp<Piece>>> Grid::getArrayOfPiecesOnGrid()
{//=========================================================================================================================
	sp<vector<sp<Piece>>>piecesOnGrid;

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr && b->piece != nullptr)
			{
				if (piecesOnGrid->contains(b->piece) == false)
				{
					piecesOnGrid->push_back(b->piece);
				}
			}
		}
	}
	
	return piecesOnGrid;
}

//=========================================================================================================================
sp<vector<sp<Block>>> Grid::checkLines(sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes)
{//=========================================================================================================================

	sp<vector<sp<Block>>>blocksOnFullLines;

	for (int y = getHeight() - 1; y >= 0; y--) //this was y>0 but i think its wrong im going to put it to y>=0
	{
		bool lineFull = true;

		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);




			if (b == nullptr || (ignoreTypes->size() > 0 && ignoreTypes->contains(b->blockType)))
			{
				lineFull = false;
				break;
			}
		}

		if (lineFull == true)
		{
			for (int x = 0; x < getWidth(); x++)
			{
				sp<Block> b = get(x, y);


				if (blocksOnFullLines->contains(b) == false)
				{
					blocksOnFullLines->push_back(b);
				}

				//if b is a special flashing piece, also remove any blocks on any lines the flashing block is on.
				if (b->piece != nullptr && b->piece->pieceType != nullptr)
				{
					if (b->piece->pieceType->clearEveryRowPieceIsOnIfAnySingleRowCleared && b->piece->overrideAnySpecialBehavior == false)
					{
						for (int c = 0; c < (int)b->connectedBlocksByPiece->size(); c++)
						{
							sp<Block> connected = b->connectedBlocksByPiece->at(c);
							for (int cx = 0; cx < getWidth(); cx++)
							{
								sp<Block> otherLineBlock = get(cx, connected->yGrid);
								if (otherLineBlock != nullptr)
								{
									if (blocksOnFullLines->contains(otherLineBlock) == false)
									{
										blocksOnFullLines->push_back(otherLineBlock);
									}
								}
							}
						}

						shakeSmall();

						//TODO: play sound flashing piece cleared
					}
				}
			}
		}
	}

	return blocksOnFullLines;
}

//=========================================================================================================================
bool Grid::doBlocksMatchColor(sp<Block> a, sp<Block> b, sp<vector<sp<BlockType>>>ignoreTypes)
{//=========================================================================================================================

	if (a == nullptr || b == nullptr)
	{
		return false;
	}

	if (a->interpolateSwappingWithX != 0 || b->interpolateSwappingWithX != 0)
	{
		return false;
	} //for puzzle, don't check colors that are being swapped

	if (a->flashingToBeRemoved == true || b->flashingToBeRemoved == true)
	{
		return false;
	} //for puzzle, don't check colors that are being swapped

	if (ignoreTypes->size() > 0 && (ignoreTypes->contains(a->blockType) || ignoreTypes->contains(b->blockType)))
	{
		return false;
	} //for dama, don't add closed in blocks

	if (a->getColor() != nullptr && b->getColor() != nullptr && (a->getColor() == b->getColor() || a->getColor()->name == b->getColor()->name))
	{
		return true;
	}

	if (a->specialColor() != nullptr && b->specialColor() != nullptr && (a->specialColor() == b->specialColor() || a->specialColor()->name == b->specialColor()->name))
	{
		return true;
	}

	if (a->blockType->matchAnyColor == true || b->blockType->matchAnyColor == true)
	{
		return true;
	}

	return false;
}

//=========================================================================================================================
sp<vector<sp<Block>>> Grid::getConnectedBlocksUpDownLeftRight(sp<Block> b)
{//=========================================================================================================================

	sp<vector<sp<Block>>>connectedBlocks;

	int xOffset = 1;
	if (b->xGrid + xOffset < getWidth())
	{
		sp<Block> n = get(b->xGrid + xOffset, b->yGrid);
		if (n != nullptr)
		{
			connectedBlocks->push_back(n);
		}
	}

	if (b->xGrid - xOffset >= 0)
	{
		sp<Block> n = get(b->xGrid - xOffset, b->yGrid);
		if (n != nullptr)
		{
			connectedBlocks->push_back(n);
		}
	}

	int yOffset = 1;
	if (b->yGrid + yOffset < getHeight())
	{
		sp<Block> n = get(b->xGrid, b->yGrid + yOffset);
		if (n != nullptr)
		{
			connectedBlocks->push_back(n);
		}
	}

	if (b->yGrid - yOffset >= 0)
	{
		sp<Block> n = get(b->xGrid, b->yGrid - yOffset);
		if (n != nullptr)
		{
			connectedBlocks->push_back(n);
		}
	}

	return connectedBlocks;
}


//=========================================================================================================================
sp<vector<sp<Block>>> Grid::checkBreakerBlocks(int toRow, sp<vector<sp<BlockType>>>ignoreUnlessTouchingBreakerBlockTypes, sp<vector<sp<BlockType>>>breakerBlockTypes)
{//=========================================================================================================================

	sp<vector<sp<Block>>>breakBlocks;

	//check grid for breaker blocks
	//breaker blocks touching any equal color set off that chain

	//checkRecursiveConnectedRowOrColumn(breakBlocks, 2, 0, getWidth(), 0, toRow, ignoreUnlessTouchingBreakerBlockTypes, breakerBlockTypes);
	//
	//	if (breakBlocks->size() >= 2)
	//	{
	//		for (int n = 0; n < breakBlocks->size(); n++)
	//		{
	//			sp<Block> b = breakBlocks->at(n);
	//
	//			if (breakerBlockTypes.contains(b->blockType))
	//			{
	//				//take out any counter pieces it is touching as well
	//				sp<vector<sp<Block>>>surroundingBlocks = getConnectedBlocksUpDownLeftRight(b);
	//
	//				for (int i = 0; i < surroundingBlocks->size(); i++)
	//				{
	//					sp<Block> d = surroundingBlocks->at(i);
	//					if (ignoreUnlessTouchingBreakerBlockTypes.contains(d->blockType))
	//					{
	//						if (breakBlocks.contains(d) == false)
	//						{
	//							breakBlocks.add(d);
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}


	//check grid for breaker blocks
	//breaker blocks touching any equal color set off that chain

	for (int y = 0; y < toRow; y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<vector<sp<Block>>>connected;

			sp<Block> b = get(x, y);

			if (b != nullptr)
			{
				if (breakerBlockTypes->contains(b->blockType))
				{
					//get recursive list of any blocks of the same color it is touching
					//do breaker blocks set off other breaker blocks? yes, of the same color.

					//if (getGameLogic()->getCurrentGameType()->chainRule_CheckRow)
					addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(b, connected, 2, 0, getWidth(), 0, getHeight(), ignoreUnlessTouchingBreakerBlockTypes, breakerBlockTypes);
					addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(b, connected, 2, 0, getWidth(), 0, getHeight(), ignoreUnlessTouchingBreakerBlockTypes, breakerBlockTypes);

					if (connected->size() > 0)
					{
						//recursively add all connected blocks to each connectedBlock
						int size = connected->size();
						for (int i = 0; i < size; i++)
						{
							sp<vector<sp<BlockType>>>emptyBlockTypeArray;
							addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(connected->at(i), connected, 2, 0, getWidth(), 0, getHeight(), ignoreUnlessTouchingBreakerBlockTypes, emptyBlockTypeArray);
							addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(connected->at(i), connected, 2, 0, getWidth(), 0, getHeight(), ignoreUnlessTouchingBreakerBlockTypes, emptyBlockTypeArray);
							if (connected->size() > size)
							{
								size = connected->size();
								i = -1;
							}
						}

						//if we have at least 2 connected pieces, this breaker block will explode.
						if (connected->size() >= 2)
						{
							for (int i = 0; i < connected->size(); i++)
							{
								sp<Block> c = connected->at(i);
								if (breakBlocks->contains(c) == false)
								{
									breakBlocks->push_back(c);
								}
							}

							//take out any counter pieces it is touching as well
							sp<vector<sp<Block>>>surroundingBlocks = getConnectedBlocksUpDownLeftRight(b);

							for (int i = 0; i < surroundingBlocks->size(); i++)
							{
								sp<Block> d = surroundingBlocks->at(i);
								if (ignoreUnlessTouchingBreakerBlockTypes->contains(d->blockType))
								{
									if (breakBlocks->contains(d) == false)
									{
										breakBlocks->push_back(d);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return breakBlocks;

	//DONE when breaker block explodes, also explode any counter blocks it is touching

	//check grid for diamond
	//if diamond sitting on color remove all colors of that color
	//TODO: check exact behavior of this
}

//=========================================================================================================================
void Grid::checkRecursiveConnectedRowOrColumn(sp<vector<sp<Block>>>connectedBlocks, int leastAmountConnected, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes)
{//=========================================================================================================================

	//TODO: refactor this like setColorConnections
	for (int y = startY; y < endY; y++)
	{
		for (int x = startX; x < endX; x++)
		{
			sp<vector<sp<Block>>>connectedToThisBlock;

			sp<Block> b = get(x, y);

			if (b != nullptr)
			{
				if (ignoreTypes->contains(b->blockType) == false)
				{
					addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(b, connectedToThisBlock, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);
					addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(b, connectedToThisBlock, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);

					if (connectedToThisBlock->size() > 0)
					{
						//recursively add all connected blocks to each connectedBlock
						int size = connectedToThisBlock->size();
						for (int i = 0; i < size; i++)
						{
							addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(connectedToThisBlock->at(i), connectedToThisBlock, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);
							addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(connectedToThisBlock->at(i), connectedToThisBlock, 2, startX, endX, startY, endY, ignoreTypes, mustContainAtLeastOneTypes);
							if (connectedToThisBlock->size() > size)
							{
								size = connectedToThisBlock->size();
								i = -1;
							}
						}

						//if we have at least 4 connected pieces in a blob, add to allConnectedBlocks
						if (connectedToThisBlock->size() >= leastAmountConnected)
						{
							for (int i = 0; i < connectedToThisBlock->size(); i++)
							{
								sp<Block> c = connectedToThisBlock->at(i);
								if (connectedBlocks->contains(c) == false)
								{
									connectedBlocks->push_back(c);
								}
							}
						}
					}
				}
			}
		}
	}

	//if (connectedBlocks->size() > 0 && connectedBlocks->size() >= leastAmountConnected)
	//{
	//return connectedBlocks;
	//}

	//return nullptr;
}

//=========================================================================================================================
void Grid::setColorConnections(sp<vector<sp<BlockType>>>ignoreTypes)//, sp<vector<sp<BlockType>>>* mustContainAtLeastOneTypes)
{//=========================================================================================================================

 //there is probably a better way to do this
 //i could optimize it by only checking in one direction and skipping connected blocks
 //right now there is a lot of redundancy, i only need to check down and right for each block and then skip connected blocks in both directions
 //will be tricky to skip connected blocks downward
 //maybe i could mark each block as checked already

	//alt version: clear b->connectedBlocksByColor for every block FIRST
	//then start new loop over grid and then skip a block if b->connectedBlocksByColor isn't clear
	//i would have to recursively check each block connected to it up down left and right, basically every time it find a color blob it navigates it and marks those blocks all complete
	//that would be faster

	//so i want to actually use a different function than addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount

	//TODO: do this for other types of recursive checking!  i do it a lot and this would be helpful!
	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr)// && (ignoreTypes->empty() || ignoreTypes->contains(b->blockType) == false))
			{
				b->connectedBlocksByColor->clear();
			}
		}
	}

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<vector<sp<Block>>>connectedBlocksByColorList;

			sp<Block> b = get(x, y);
			if (b != nullptr && (ignoreTypes->empty() || ignoreTypes->contains(b->blockType) == false))
			{

				if (b->connectedBlocksByColor->size() > 0)continue;

				recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(b, connectedBlocksByColorList, ignoreTypes);

				//set connections from all blocks to all connected blocks
				//if (connectedBlocksList->size() >= 2)
				//{
					for (int i = 0; i < connectedBlocksByColorList->size(); i++)
					{
						sp<Block> c = connectedBlocksByColorList->at(i);
						if (b != c && b->connectedBlocksByColor->contains(c) == false)
						{
							b->connectedBlocksByColor->push_back(c);
						}
					}
				//}
			}
		}
	}

	//old algorithm which is probably slower but i don't really know how to tell, i need to figure out some timing library for this stuff
//
//	for (int y = 0; y < getHeight(); y++)
//	{
//		for (int x = 0; x < getWidth(); x++)
//		{
//			sp<vector<sp<Block>>>* connectedBlocksList = ms<vector><sp<Block>>();
//
//			sp<Block> b = get(x, y);
//			if (b != nullptr && (ignoreTypes->empty() || ignoreTypes->contains(b->blockType) == false))
//			{
//				b->connectedBlocksByColor->clear();
//
//
//				addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(b, connectedBlocksList, 2, 0, getWidth(), 0, getHeight(), ignoreTypes, nullptr);
//
//				if (connectedBlocksList->size() > 0)
//				{
//					//recursively add all connected blocks to each connectedBlock
//					int previousSize = connectedBlocksList->size();
//					for (int i = 0; i < previousSize; i++)
//					{
//						sp<Block> connectedBlock = connectedBlocksList->get(i);
//						addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowOrColumnAtLeastAmount(connectedBlock, connectedBlocksList, 2, 0, getWidth(), 0, getHeight(), ignoreTypes, nullptr);
//						if (connectedBlocksList->size() > previousSize)
//						{
//							previousSize = connectedBlocksList->size();
//							i = -1;
//						}
//					}
//
//					//set connections from all blocks to all connected blocks
//					if (connectedBlocksList->size() >= 2)
//					{
//						for (int i = 0; i < connectedBlocksList->size(); i++)
//						{
//							sp<Block> c = connectedBlocksList->get(i);
//							if (b != c && b->connectedBlocksByColor.contains(b) == false)
//							{
//								b->connectedBlocksByColor.add(c);
//							}
//						}
//					}
//				}
//			}
//
//			delete connectedBlocksList;
//		}
//	}
}

//=========================================================================================================================
void Grid::addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInRowAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes)
{//=========================================================================================================================

   //TODO: find everything using this and try to refactor this like setColorConnections
	{
		sp<vector<sp<Block>>>row;
		row->push_back(b);

		//check all blocks starting from this block to the right
		for (int xOffset = 1; b->xGrid + xOffset < endX; xOffset++) 
		{
			sp<Block> n = get(b->xGrid + xOffset, b->yGrid);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				row->push_back(n);
			}
			else
			{
				break;
			}
		}

		//check all blocks starting from this block to the left
		for (int xOffset = 1; b->xGrid - xOffset >= startX; xOffset++) 
		{
			sp<Block> n = get(b->xGrid - xOffset, b->yGrid);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				row->push_back(n);
			}
			else
			{
				break;
			}
		}

		if (row->size() >= leastInARow)
		{
			if (mustContainAtLeastOneTypes->size() > 0)
			{
				bool containsMandatoryBlocks = false;
				for (int i = 0; i < row->size(); i++)
				{
					if (mustContainAtLeastOneTypes->contains(row->at(i)->blockType))
					{
						containsMandatoryBlocks = true;
					}
				}
				if (containsMandatoryBlocks == false)
				{
					row->clear();
				}
			}

			for (int i = 0; i < row->size(); i++)
			{
				sp<Block> c = row->at(i);
				if (connectedBlocks->contains(c) == false)
				{
					connectedBlocks->push_back(c);
				}
			}
		}
	}


	//return *connectedBlocks;
}

//=========================================================================================================================
void Grid::addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfInColumnAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes)
{//=========================================================================================================================

 //TODO: find everything using this and try to refactor this like setColorConnections
	
	{
		sp<vector<sp<Block>>>column;
		column->push_back(b);

		for (int yOffset = 1; b->yGrid + yOffset < endY; yOffset++) //check all blocks starting from this block to the up
		{
			sp<Block> n = get(b->xGrid, b->yGrid + yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				column->push_back(n);
			}
			else
			{
				break;
			}
		}

		for (int yOffset = 1; b->yGrid - yOffset >= startY; yOffset++) //check all blocks starting from this block to the down
		{
			sp<Block> n = get(b->xGrid, b->yGrid - yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				column->push_back(n);
			}
			else
			{
				break;
			}
		}

		if (column->size() >= leastInARow)
		{
			if (mustContainAtLeastOneTypes->size() > 0)
			{
				bool containsMandatoryBlocks = false;
				for (int i = 0; i < column->size(); i++)
				{
					if (mustContainAtLeastOneTypes->contains(column->at(i)->blockType))
					{
						containsMandatoryBlocks = true;
					}
				}
				if (containsMandatoryBlocks == false)
				{
					column->clear();
				}
			}

			for (int i = 0; i < column->size(); i++)
			{
				sp<Block> c = column->at(i);
				if (connectedBlocks->contains(c) == false)
				{
					connectedBlocks->push_back(c);
				}
			}
		}
	}

	//return *connectedBlocks;
}
//=========================================================================================================================
void Grid::recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(sp<Block> b, sp<vector<sp<Block>>>connectedBlocksByColor, sp<vector<sp<BlockType>>>ignoreTypes)
{//=========================================================================================================================

	//check up, down, left, right
	//if matches, add to array
	//call recursive on new block with array

	if (connectedBlocksByColor->contains(b) == false)
	{
		connectedBlocksByColor->push_back(b);
	}

	sp<vector<sp<Block>>>udlr = getConnectedBlocksUpDownLeftRight(b);

	//check all blocks starting from this block to the right
	for (int i = 0; i < udlr->size(); i++)
	{
		sp<Block> n = udlr->at(i);
		if (doBlocksMatchColor(b, n, ignoreTypes))
		{
			if (connectedBlocksByColor->contains(n) == false)
			{
				connectedBlocksByColor->push_back(n);
				recursivelyGetAllMatchingBlocksConnectedToBlockToArrayIfNotInItAlready(n, connectedBlocksByColor, ignoreTypes);
			}
		}
	}
}


//=========================================================================================================================
void Grid::addBlocksConnectedToBlockToArrayIfNotInItAlreadyIfDiagonalAtLeastAmount(sp<Block> b, sp<vector<sp<Block>>>connectedBlocks, int leastInARow, int startX, int endX, int startY, int endY, sp<vector<sp<BlockType>>>ignoreTypes, sp<vector<sp<BlockType>>>mustContainAtLeastOneTypes)
{//=========================================================================================================================

	{
		sp<vector<sp<Block>>>upLeftDownRight;
		upLeftDownRight->push_back(b);

		for (int xOffset = 1, yOffset = 1; b->xGrid + xOffset < endX && b->yGrid + yOffset < endY; xOffset++ , yOffset++) //down right
		{
			sp<Block> n = get(b->xGrid + xOffset, b->yGrid + yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				upLeftDownRight->push_back(n);
			}
			else
			{
				break;
			}
		}

		for (int xOffset = 1, yOffset = 1; b->xGrid - xOffset >= startX && b->yGrid - yOffset >= startY; xOffset++ , yOffset++) //up left
		{
			sp<Block> n = get(b->xGrid - xOffset, b->yGrid - yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				upLeftDownRight->push_back(n);
			}
			else
			{
				break;
			}
		}

		if (upLeftDownRight->size() >= leastInARow)
		{
			if (mustContainAtLeastOneTypes->size() > 0 && mustContainAtLeastOneTypes->size() > 0)
			{
				bool containsMandatoryBlocks = false;
				for (int i = 0; i < upLeftDownRight->size(); i++)
				{
					if (mustContainAtLeastOneTypes->contains(upLeftDownRight->at(i)->blockType))
					{
						containsMandatoryBlocks = true;
					}
				}
				if (containsMandatoryBlocks == false)
				{
					upLeftDownRight->clear();
				}
			}

			for (int i = 0; i < upLeftDownRight->size(); i++)
			{
				sp<Block> c = upLeftDownRight->at(i);
				if (connectedBlocks->contains(c) == false)
				{
					connectedBlocks->push_back(c);
				}
			}
		}
	}

	{
		sp<vector<sp<Block>>>downLeftUpRight;
		downLeftUpRight->push_back(b);

		for (int xOffset = 1, yOffset = 1; b->xGrid - xOffset >= startX && b->yGrid + yOffset < endY; xOffset++ , yOffset++) //down left
		{
			sp<Block> n = get(b->xGrid - xOffset, b->yGrid + yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				downLeftUpRight->push_back(n);
			}
			else
			{
				break;
			}
		}

		for (int xOffset = 1, yOffset = 1; b->xGrid + xOffset < endX && b->yGrid - yOffset >= startY; xOffset++ , yOffset++) //up right
		{
			sp<Block> n = get(b->xGrid + xOffset, b->yGrid - yOffset);
			if (doBlocksMatchColor(b, n, ignoreTypes))
			{
				downLeftUpRight->push_back(n);
			}
			else
			{
				break;
			}
		}

		if (downLeftUpRight->size() >= leastInARow)
		{
			if (mustContainAtLeastOneTypes->size() > 0)
			{
				bool containsMandatoryBlocks = false;
				for (int i = 0; i < downLeftUpRight->size(); i++)
				{
					if (mustContainAtLeastOneTypes->contains(downLeftUpRight->at(i)->blockType))
					{
						containsMandatoryBlocks = true;
					}
				}
				if (containsMandatoryBlocks == false)
				{
					downLeftUpRight->clear();
				}
			}

			for (int i = 0; i < downLeftUpRight->size(); i++)
			{
				sp<Block> c = downLeftUpRight->at(i);
				if (connectedBlocks->contains(c) == false)
				{
					connectedBlocks->push_back(c);
				}
			}
		}
	}

	//return *connectedBlocks;
}

//=========================================================================================================================
void Grid::renderBackground()
{//=========================================================================================================================

	
	float alpha = 0.85f;

	int height = getHeight();
	if (getGameType()->gameMode == GameMode::STACK)
	{
		height--;
	}
	
	for(int x=-1;x<getWidth();x++)
	{
		//for(int y=-1+GameLogic::aboveGridBuffer;y<getHeight();y++)
		for(int y=-1;y<height;y++)
		{
	
			sp<OKColor>color = getGameLogic()->player->gridCheckeredBackgroundColor1;
	
			if(y%2==0)
			{
				if(x%2==0)color = getGameLogic()->player->gridCheckeredBackgroundColor1;
				else color = getGameLogic()->player->gridCheckeredBackgroundColor2;
			}
			else
			{
				if(x%2==0)color = getGameLogic()->player->gridCheckeredBackgroundColor2;
				else color = getGameLogic()->player->gridCheckeredBackgroundColor1;
			}
	
			float fbgX = bgX() + (x*cellW());
			float fbgY = bgY() + (y*cellH());
	
	
			GLUtils::drawFilledRectXYWH(fbgX,fbgY,(float)cellW(), (float)cellH(),color->rf(),color->gf(),color->bf(),alpha);
		}
	}
	
	float r = getGameLogic()->player->gridCheckeredBackgroundColor1->rf();
	float g = getGameLogic()->player->gridCheckeredBackgroundColor1->gf();
	float b = getGameLogic()->player->gridCheckeredBackgroundColor1->bf();
	
	//draw danger zone
	OKColor c(48, 48, 48);

	float y = getYInFBO();
	float h = (float)cellH()*GameLogic::aboveGridBuffer;
	GLUtils::drawFilledRectXYWH(getXInFBO(), y, (float)cellW()*getWidth(), (float)cellH()*GameLogic::aboveGridBuffer, c.rf(), c.gf(), c.bf(), alpha);

	c = *OKColor::lightGray;
	GLUtils::drawFilledRectXYWH(getXInFBO(), y+h-1, (float)cellW()*getWidth(), 1, c.rf(), c.gf(), c.bf(), alpha);


	
	//clip sides of background so scroll doesn't look dumb.
	GLUtils::drawFilledRectXYWH
	(
		getXInFBO()-cellW(),
		getYInFBO()-cellH(),
		(float)cellW()*(getWidth()+2),
		(float)cellH(),
		r, g, b, alpha
	);
	
	GLUtils::drawFilledRectXYWH
	(
		getXInFBO()-cellW(),
		getYInFBO()-cellH(),
		(float)cellW(),
		(float)cellH()*(height +1),
		r, g, b, alpha
	);
	
	GLUtils::drawFilledRectXYWH
	(
		getXInFBO()+getWidth()*cellW(),
		getYInFBO()-cellH(),
		(float)cellW(),
		(float)cellH()*(height +1),
		r, g, b, alpha
	);
	
	GLUtils::drawFilledRectXYWH
	(
		getXInFBO()-cellW(),
		getYInFBO()+ height*cellH(),
		(float)cellW()*(getWidth()+2),
		(float)cellH(),
		r, g, b, alpha
	);
}

//=========================================================================================================================
void Grid::render()
{//=========================================================================================================================


	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr)
			{
				b->render(getXInFBO() + x * cellW(), getYInFBO() + (scrollPlayingFieldY / scrollBlockIncrement)*cellH() + y * cellH(), 1.0f, 1.0f, true, false);
			}
		}
	}


}

//=========================================================================================================================
void Grid::renderBlockOutlines()
{//=========================================================================================================================
	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			sp<Block> b = get(x, y);
			if (b != nullptr)
			{
				b->renderOutlines(getXInFBO() + x * cellW(), getYInFBO() + (scrollPlayingFieldY / scrollBlockIncrement)*cellH() + y * cellH(), 1.0f);
			}
		}
	}
}

//=========================================================================================================================
void Grid::renderBorder()
{//=========================================================================================================================

//	for (int i = 1; i < cellH(); i++)
//	{
//		//			float r = GameType().gridBorderColor.rf() - (float)((float)(i-1)/(float)cellH());
//		//			float g = GameType().gridBorderColor.gf() - (float)((float)(i-1)/(float)cellH());
//		//			float b = GameType().gridBorderColor.bf() - (float)((float)(i-1)/(float)cellH());
//
//
//		float ratio = (float)((float)(i - 1) / (float)(cellH()));
//
//		float amt = ratio + 0.5f;
//		if (amt > 1.0f)
//		{
//			amt = 1.0f;
//		}
//		amt -= 0.5f;
//
//		if (i < 3)
//		{
//			amt = 1.0f;
//		}
//
//		float r = getCurrentGameType()->gridBorderColor.rf() - amt;
//		float g = getCurrentGameType()->gridBorderColor.gf() - amt;
//		float b = getCurrentGameType()->gridBorderColor.bf() - amt;
//
//		if (r < 0)
//		{
//			r = 0;
//		}
//		if (g < 0)
//		{
//			g = 0;
//		}
//		if (b < 0)
//		{
//			b = 0;
//		}
//
//		//top
//		GLUtils::drawFilledRectXYWH
//			(
//				getXInFBO() - i,
//				getYInFBO() - i,
//				(float)cellW() * (getWidth()) + (i * 2),
//				1,
//				r, g, b, 1.0f
//			);
//
//		//left
//		GLUtils::drawFilledRectXYWH
//			(
//				getXInFBO() - i,
//				getYInFBO() - i,
//				1,
//				(float)cellH() * (getHeight()) + (i * 2),
//				r, g, b, 1.0f
//			);
//
//		//right
//		GLUtils::drawFilledRectXYWH
//			(
//				getXInFBO() + getWidth() * cellW() + i,
//				getYInFBO() - i,
//				1,
//				(float)cellH() * (getHeight()) + (i * 2) + 1,
//				r, g, b, 1.0f
//			);
//
//		//bottom
//		GLUtils::drawFilledRectXYWH
//			(
//				getXInFBO() - i,
//				getYInFBO() + getHeight() * cellH() + i,
//				(float)cellW() * (getWidth()) + (i * 2) + 1,
//				1,
//				r, g, b, 1.0f
//			);
//	}

	float mult = 1.0f;// 1.5f;
	float a = 1.0f;
	int f = GLUtils::FILTER_FBO_LINEAR_NO_MIPMAPPING;

	float leftX0 = getXInFBO() - cellW() * mult;
	float leftX1 = getXInFBO();
	float rightX0 = getXInFBO() + getWidth() * cellW();
	float rightX1 = getXInFBO() + (getWidth() + mult) * cellW();
	float topY0 = getYInFBO() - cellH() * mult;
	float topY1 = getYInFBO();
	float bottomY0 = getYInFBO() + cellH() * getHeight();
	float bottomY1 = getYInFBO() + cellH() * (getHeight() + mult);

	if (getGameType()->gameMode == GameMode::STACK)
	{
		//render border over last grid row so i have a hidden row without a black gap
		bottomY0 = getYInFBO() + cellH() * (getHeight()-1);
		bottomY1 = getYInFBO() + cellH() * ((getHeight()-1) + mult);
	}


	GLUtils::drawTexture(OKGame::upperLeft, leftX0, leftX1, topY0, topY1, a, f);
	GLUtils::drawTexture(OKGame::top, leftX1, rightX0, topY0, topY1, a, f);
	GLUtils::drawTexture(OKGame::upperRight, rightX0, rightX1, topY0, topY1, a, f);
	GLUtils::drawTexture(OKGame::left, leftX0, leftX1, topY1, bottomY0, a, f);
	GLUtils::drawTexture(OKGame::right, rightX0, rightX1, topY1, bottomY0, a, f);
	GLUtils::drawTexture(OKGame::lowerLeft, leftX0, leftX1, bottomY0, bottomY1, a, f);
	GLUtils::drawTexture(OKGame::lowerRight, rightX0, rightX1, bottomY0, bottomY1, a, f);
	GLUtils::drawTexture(OKGame::bottom, leftX1, rightX0, bottomY0, bottomY1, a, f);



}



//=========================================================================================================================
void Grid::renderTransparentOverLastRow()
{//=========================================================================================================================



	float x = getXInFBO();
	float y = getYInFBO() + (getHeight() - 2) * cellH() + cellH()/2;

	float w = (float)getWidth() * cellW();
	float h = (float)((getYInFBO() + getHeight() * cellH()) - y);

	float div = 16;
	for(float i=0; i<div; i++)
	{
		if (i == div - 1)h += 1;
		
		GLUtils::drawFilledRectXYWH
		(
			x,
			y + h/div*i,
			w,
			h/div,
			0,
			0,
			0,
			1.0f/(div-1)*i
		);


	}


//	GLUtils::drawFilledRectXYWH
//	(
//		getXInFBO(), 
//		getYInFBO() + (getHeight() - 1) * cellH(), 
//		(float)getWidth() * cellW(), 
//		(float)cellH() + 1, 
//		0, 
//		0, 
//		0, 
//		1.0f
//	);




	//TODO: render bottom border piece over blocks drawn

	renderBorder();



}

//=========================================================================================================================
void Grid::renderGhostPiece(sp<Piece> currentPiece)
{//=========================================================================================================================
	int ghostY = currentPiece->yGrid;
	for (int y = ghostY; y < getHeight(); y++)
	{
		if (doesPieceFit(currentPiece, currentPiece->xGrid, y) == true)
		{
			ghostY = y;
		}
		else
		{
			break;
		}
	}

	if (ghostY != currentPiece->yGrid)
	{
		float x = getXInFBO() + currentPiece->xGrid * cellW();
		float y = getYInFBO() + ghostY * cellH();

		float alpha = ((float)(ghostY - currentPiece->yGrid)) / ((float)(getHeight()*0.6f));
		if (alpha > 1)alpha = 1;

		currentPiece->renderGhost(x, y, alpha);
	}
}

//=========================================================================================================================
bool Grid::isWithinBounds(sp<Piece> piece, int x, int y)
{//=========================================================================================================================

	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece >= getWidth() || x + piece->blocks->at(b)->xInPiece < 0 || y + piece->blocks->at(b)->yInPiece >= getHeight())
		{
			return false;
		}
	}

	return true;
}

//=========================================================================================================================
bool Grid::isHittingLeft(sp<Piece> piece)
{//=========================================================================================================================
	return isHittingLeft(piece, piece->xGrid, piece->yGrid);
}

//=========================================================================================================================
bool Grid::isHittingLeft(sp<Piece> piece, int x, int y)
{//=========================================================================================================================

	if (x < 0)
	{
		return true;
	}

	//for(int b=0;b<piece.blocksPerPiece;b++)if(y+piece.block->get(b).yOffset<0)return false;

	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece < 0)
		{
			return true;
		}
	}

	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece < x && get(x + piece->blocks->at(b)->xInPiece, y + piece->blocks->at(b)->yInPiece) != nullptr)
		{
			return true;
		}
	}
	return false;
}

//=========================================================================================================================
bool Grid::isHittingRight(sp<Piece> piece)
{//=========================================================================================================================
	return isHittingRight(piece, piece->xGrid, piece->yGrid);
}

//=========================================================================================================================
bool Grid::isHittingRight(sp<Piece> piece, int x, int y)
{//=========================================================================================================================

	if (x >= getWidth())
	{
		return true;
	}

	//for(int b=0;b<piece.blocksPerPiece;b++)if(y+piece.block->get(b).yOffset<0)return false;

	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece >= getWidth())
		{
			return true;
		}
	}

	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece > x && get(x + piece->blocks->at(b)->xInPiece, y + piece->blocks->at(b)->yInPiece) != nullptr)
		{
			return true;
		}
	}
	return false;
}

//=========================================================================================================================
bool Grid::doesPieceFit(sp<Piece> piece)
{//=========================================================================================================================
	return doesPieceFit(piece, piece->xGrid, piece->yGrid);
}

//=========================================================================================================================
bool Grid::doesPieceFit(sp<Piece> piece, int x, int y)
{//=========================================================================================================================

	if (isWithinBounds(piece, x, y) == false)
	{
		return false;
	}
	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (x + piece->blocks->at(b)->xInPiece < 0 || x + piece->blocks->at(b)->xInPiece >= getWidth())
		{
			return false;
		}
	}
	for (int b = 0; b < (int)piece->getNumBlocksInCurrentRotation() && b < piece->blocks->size(); b++)
	{
		if (y + piece->blocks->at(b)->yInPiece >= 0 && get(x + piece->blocks->at(b)->xInPiece, y + piece->blocks->at(b)->yInPiece) != nullptr)
		{
			return false;
		}
	}

	return true;
}

//=========================================================================================================================
void Grid::setPiece(sp<Piece> piece)
{//=========================================================================================================================
	setPiece(piece, piece->xGrid, piece->yGrid);
}

//=========================================================================================================================
void Grid::setPiece(sp<Piece> piece, int x, int y)
{//=========================================================================================================================
	if (isWithinBounds(piece, x, y) == false)
	{
		log.error("Tried to set Piece outside of Grid bounds");
		return;
	}

	if (piece->pieceType != nullptr && piece->pieceType->fadeOutOnceSetInsteadOfAddedToGrid == true)
	{
		for (int i = 0; i < piece->getNumBlocksInCurrentRotation() && i < piece->blocks->size(); i++)
		{
			sp<Block> b = piece->blocks->at(i);
			b->fadingOut = true;
			if (getGameLogic()->fadingOutBlocks->contains(b) == false)
			{
				getGameLogic()->fadingOutBlocks->push_back(b);
			}
		}

		return;
	}


	//set blocks in the grid
	for (int i = 0; i < piece->getNumBlocksInCurrentRotation() && i < piece->blocks->size(); i++)
	{
		sp<Block> b = piece->blocks->at(i);

		add(x + b->xInPiece, y + b->yInPiece, b);

		b->setInGrid = true;
		b->locking = true;
	}

	//if it is a block which changes other blocks into something else do that
	for (int i = 0; i < piece->getNumBlocksInCurrentRotation() && i < piece->blocks->size(); i++)
	{
		sp<Block> b = piece->blocks->at(i);

		if (b->blockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut->size() > 0)
		{
			sp<vector<sp<Block>>>surroundingBlocks = getConnectedBlocksUpDownLeftRight(b);
			for (int k = 0; k < surroundingBlocks->size(); k++)
			{
				sp<Block> touchingBlock = surroundingBlocks->at(k);

				//don't affect blocks in the piece we just placed
				if (piece->blocks->contains(touchingBlock) == false)
				{
					for (int s = 0; s < b->blockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut->size(); s++)
					{
						sp<TurnFromBlockTypeToType>turn = b->blockType->whenSetTurnAllTouchingBlocksOfFromTypesIntoToTypeAndFadeOut->at(s);

						if (touchingBlock->blockType->uuid == turn->fromType_UUID)
						{
							touchingBlock->blockType = getGameType()->getBlockTypeByUUID(turn->toType_UUID);
						}
					}
				}
			}

			//fade out and remove this block from the grid (which we just added)
			//sp<Block> r = 
			remove(x + b->xInPiece, y + b->yInPiece, true, false);

			piece->blocks->remove(b);

			i = -1;
		}
	}

	piece->setInGrid = true;
}

//=========================================================================================================================
bool Grid::moveDownLinesAboveBlankLinesOneLine()
{//=========================================================================================================================

	bool moved = false;

	for (int y = getHeight() - 1; y > 0; y--) //notice y>0 because it grabs the piece above it
	{
		bool lineIsBlank = true;
		for (int x = 0; x < getWidth(); x++)
		{
			if (get(x, y) != nullptr)
			{
				lineIsBlank = false;
			}
		}

		if (lineIsBlank == true)
		{
			for (int x = 0; x < getWidth(); x++)
			{
				sp<Block> b = get(x, y - 1);
				if (b != nullptr)
				{
					remove(x, y - 1, false, false);
					add(x, y, b);

					moved = true;
				}
			}
		}
	}

	return moved;
}

//=========================================================================================================================
bool Grid::moveDownDisconnectedBlocksAboveBlankSpacesOneLine(sp<vector<sp<BlockType>>>ignoreTypes)
{//=========================================================================================================================

	bool moved = false;

	for (int y = getHeight() - 2; y >= 0; y--) //notice getHeight()-2 because it pushes the piece to the line below it
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);

			if (b != nullptr && (ignoreTypes->empty() || ignoreTypes->contains(b->blockType) == false))
			{
				if (b->xGrid != x || b->yGrid != y)
				{
					log.error(("xyGrid does not match! b.xGrid:") + to_string(b->xGrid) + (" b.yGrid:") + to_string(b->yGrid) + (" x:") + to_string(x) + (" y:") + to_string(y));
				}

				sp<Block> c = nullptr;
				for (int i = 0; i < (int)b->connectedBlocksByPiece->size(); i++)
				{
					sp<Block> temp = b->connectedBlocksByPiece->at(i);
					if (blocks->containsValue(temp) == true)
					{
						c = temp;
						break;
					}
				}

				if (c == nullptr)
				{
					if (get(x, y + 1) == nullptr) //if there is no connected block, just move the block down one
					{
						remove(b, false, false);
						add(x, y + 1, b);

						moved = true;
					}
				}
				else
				{
					for (int i = 0; i < (int)b->connectedBlocksByPiece->size(); i++)
					{
						sp<Block> temp = b->connectedBlocksByPiece->at(i);
						if (blocks->containsValue(temp) == true && c != b)
						{
							c = temp;
						}
						else
						{
							continue;
						}

						//if our connected block is above us and there is nothing below us, move us both down
						if (c->yGrid == b->yGrid - 1 && c->xGrid == b->xGrid)
						{
							if (get(x, y + 1) == nullptr)
							{
								remove(b, false, false);
								add(x, y + 1, b);

								remove(c, false, false);
								add(x, y, c);

								moved = true;
							}
						}
						else
						//if our connected block is below us and there is nothing below it, that will be handled already when it cycles through
						{
							//if our connected block is to the left or right and there is nothing underneath it, move us down
							if ((c->xGrid == b->xGrid - 1 || c->xGrid == b->xGrid + 1) && c->yGrid == b->yGrid)
							{
								if (get(b->xGrid, y + 1) == nullptr && get(c->xGrid, y + 1) == nullptr)
								{
									remove(b, false, false);
									add(b->xGrid, y + 1, b);

									remove(c, false, false);
									add(c->xGrid, y + 1, c);

									moved = true;
								}
							}
						}
					}
				}
			}
		}
	}

	return moved;
}

//=========================================================================================================================
bool Grid::moveDownAnyBlocksAboveBlankSpacesOneLine(sp<vector<sp<BlockType>>>ignoreTypes)
{//=========================================================================================================================

	bool moved = false;

	for (int y = getHeight() - 2; y >= 0; y--) //notice getHeight()-2 because it "pushes" the piece to the line below it
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);

			if (b != nullptr && (ignoreTypes->empty() || ignoreTypes->contains(b->blockType) == false))
			{
				if (get(x, y + 1) == nullptr)
				{
					remove(x, y, false, false);
					add(x, y + 1, b);

					moved = true;
				}
			}
		}
	}

	return moved;
}

//=========================================================================================================================
void Grid::setRandomBlockColors()
{//=========================================================================================================================
	//		for(int x=0;x<getWidth();x++)
	//		{
	//			for(int y=0;y<getHeight();y++)
	//			{
	//				if(get(x,y)!=null)
	//				{
	//					if(get(x,y).renderColor==get(x,y).color)get(x,y).renderColor = get(x,y).getRandomColor();
	//					else get(x,y).renderColor = get(x,y).color;
	//				}
	//			}
	//		}
}

//=========================================================================================================================
void Grid::setRandomMatrixBlockColors()
{//=========================================================================================================================
	//
	//		backgroundColor1 = ms<Color>(0.0f,OKGame::randLessThanFloat(1.0f),0.0f);
	//		backgroundColor2 = ms<Color>(0.0f,OKGame::randLessThanFloat(1.0f),0.0f);
	//
	//
	//		for(int x=0;x<getWidth();x++)
	//		{
	//			for(int y=0;y<getHeight();y++)
	//			{
	//				if(get(x,y)!=null)
	//				{
	//					get(x,y).renderColor = (Block.getRandomMatrixColor());
	//
	//				}
	//			}
	//		}
}

//=========================================================================================================================
void Grid::setRandomWholePieceColors(bool grayscale, sp<Piece> currentPiece, sp<vector<sp<Piece>>>nextPieces)
{//=========================================================================================================================

	//TODO
	//TODO
	//TODO
	//TODO
	//TODO
	//TODO
	//TODO
	//
	//		//make array of previously used colors
	//		List<Color> previousColors = ms<List><Color>();
	//
	//		for(int x=0;x<getWidth();x++)
	//		{
	//			for(int y=0;y<getHeight();y++)
	//			{
	//				if(get(x,y)!=null)
	//				{
	//					if(previousColors.Contains(get(x,y).color)==false)previousColors.Add(get(x,y).color);
	//				}
	//			}
	//		}
	//
	//		if(currentPiece!=null)
	//		{
	//			for(int b=0;b<currentPiece.blocks.Count;b++)
	//			{
	//				if(previousColors.Contains(currentPiece.blocks->at(b).color)==false)previousColors.Add(currentPiece.blocks->at(b).color);
	//			}
	//		}
	//		if(nextPieces!=null)
	//		{
	//			for(int p=0;p<nextPieces.length;p++)
	//			{
	//				Piece piece = nextPieces[p];
	//
	//				for(int b=0;b<piece.blocks.Count;b++)
	//				{
	//					if(previousColors.Contains(piece.blocks->at(b).color)==false)previousColors.Add(piece.blocks->at(b).color);
	//				}
	//			}
	//		}
	//
	//
	//		Piece.setRandomPieceColors(grayscale);
	//
	//		//set new color based on index of old color
	//		for(int x=0;x<getWidth();x++)
	//		{
	//			for(int y=0;y<getHeight();y++)
	//			{
	//				if(get(x,y)!=null)
	//				{
	//					int i = previousColors.indexOf(get(x,y).color);
	//					if(i>=0)get(x,y).setColor(Piece.colors->get(i));
	//				}
	//			}
	//		}
	//
	//
	//		if(currentPiece!=null)
	//		{
	//			for(int b=0;b<currentPiece.blocks.Count;b++)
	//			{
	//				int i = previousColors.indexOf(currentPiece.blocks->at(b).color);
	//				if(i>=0)currentPiece.blocks->at(b).setColor(Piece.colors->get(i));
	//			}
	//		}
	//
	//
	//		if(nextPieces!=null)
	//		{
	//			for(int p=0;p<nextPieces.length;p++)
	//			{
	//				Piece piece = nextPieces[p];
	//				for(int b=0;b<piece.blocks.Count;b++)
	//				{
	//					int i = previousColors.indexOf(piece.blocks->at(b).color);
	//					if(i>=0)piece.blocks->at(b).setColor(Piece.colors->get(i));
	//				}
	//			}
	//		}
}

//=========================================================================================================================
void Grid::setRandomPieceGrayscaleColors(sp<Piece> currentPiece, sp<vector<sp<Piece>>>nextPieces)
{//=========================================================================================================================
	setRandomWholePieceColors(true, currentPiece, nextPieces);
}

//=========================================================================================================================
bool Grid::isAnythingAboveThreeQuarters()
{//=========================================================================================================================
	for (int x = 0; x < getWidth(); x++)
	{
		for (int y = 0; y < getHeight(); y++)
		{
			if (get(x, y) != nullptr)
			{
				if (y < GameLogic::aboveGridBuffer + ((getHeight() - GameLogic::aboveGridBuffer) / 4))
				{
					return true;
				}
			}
		}
	}
	return false;
}

//=========================================================================================================================
void Grid::doDeathSequence()
{//=========================================================================================================================

	if (deadX < getWidth())
	{
		sp<Piece> p = getRandomPiece();
		for (int i = 0; i < (int)p->blocks->size(); i++)
		{
			sp<Block> b = p->blocks->at(i);
			b->lastScreenX = getXInFBO() + (deadX + b->xInPiece) * cellW();
			b->lastScreenY = getYInFBO() + (deadY + b->yInPiece) * cellH() + (scrollPlayingFieldY / scrollBlockIncrement)*cellH();
		}

		sp<Block> d = get(deadX, deadY);
		if (d != nullptr)
		{
			removeAllBlocksOfPieceFromGrid(d->piece, true);
		}

		if (doesPieceFit(p, deadX, deadY) && deadY + p->getLowestOffsetY() > 2)
		{
			{
				//if(isWithinBounds(p,deadX,deadY))
				setPiece(p, deadX, deadY);
				deadX += p->getWidth();
				deadY -= p->getHeight();
			}
		}
		else
		{
			deadX += getGameLogic()->getRandomIntLessThan(3,"doDeathSequence");
			deadY -= getGameLogic()->getRandomIntLessThan(3,"doDeathSequence");
		}

		//			for(int i=0;i<p.blocks.Count;i++)
		//			{
		//				Block b = p.blocks->at(i);
		//				deleteBlock(b);
		//			}

		//deadX++;

		if (deadY < 0)
		{
			deadY = getHeight() - 1;
		}

		if (deadX >= getWidth())
		{
			deadX = 0;

			//deadY--;
			//				if(deadY<0)
			//				{
			//
			//					deadY=getHeight()-1;
			//				}
		}
	}
}

//=========================================================================================================================
sp<PieceType> Grid::getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(sp<vector<sp<PieceType>>>pieceTypes)
{//=========================================================================================================================

	sp<vector<sp<PieceType>>>randomBag;

	for (int i = 0; i < pieceTypes->size(); i++)
	{
		sp<PieceType> p = pieceTypes->at(i);
		if (p->frequencySpecialPieceTypeOnceEveryNPieces != 0)
		{
			if (getGameLogic()->createdPiecesCounterForFrequencyPieces >= p->frequencySpecialPieceTypeOnceEveryNPieces)
			{
				randomBag->push_back(p);
			}
		}
	}

	if (randomBag->size() > 0)
	{
		getGameLogic()->createdPiecesCounterForFrequencyPieces = 0;

		sp<PieceType> p = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull"));
		return p;
	}

	//		int randomTotal = 1;
	//		PieceType emptyPieceType(ms<PieceType>());
	//		randomBag.Add(emptyPieceType);
	//		for(int i=0;i<array.Count;i++)
	//		{
	//			PieceType b = array->get(i);
	//			//if(b.randomSpecialPieceChanceOneOutOf>0)randomTotal*=b.randomSpecialPieceChanceOneOutOf;
	//		}

	//		for(int n=0;n<randomTotal;n++)randomBag.Add(emptyPieceType);

	for (int i = 0; i < pieceTypes->size(); i++)
	{
		sp<PieceType> b = pieceTypes->at(i);

		if (b->randomSpecialPieceChanceOneOutOf > 0)
		{
			if (getGameLogic()->getRandomIntLessThan(b->randomSpecialPieceChanceOneOutOf,"getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull") == 0)
			{
				randomBag->push_back(b);
			}
		}
	}

	if (randomBag->size() > 0)
	{
		sp<PieceType> p = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull"));
		//if(p!=emptyPieceType)
		return p;
	}

	return nullptr;
}

//=========================================================================================================================
sp<PieceType> Grid::getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(sp<vector<sp<PieceType>>>arr)
{//=========================================================================================================================

	sp<vector<sp<PieceType>>>randomBag;

	for (int i = 0; i < arr->size(); i++)
	{
		sp<PieceType> b = arr->at(i);
		if (b->randomSpecialPieceChanceOneOutOf == 0 && b->frequencySpecialPieceTypeOnceEveryNPieces == 0)
		{
			randomBag->push_back(b);
		}
	}

	if (randomBag->size() > 0)
	{
		sp<PieceType> b = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomPieceTypeFromArrayExcludingSpecialPieceTypes"));
		return b;
	}

	return nullptr;
}

//=========================================================================================================================
sp<vector<sp<Piece>>> Grid::getBagOfOneOfEachNonRandomNormalPieces()
{//=========================================================================================================================
	sp<vector<sp<PieceType>>>pieceTypes = getGameType()->getNormalPieceTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<BlockType>>>blockTypes = getGameType()->getNormalBlockTypes(getGameLogic()->getCurrentDifficulty());
	sp<vector<sp<Piece>>>tempBag;
	for (int i = 0; i < (int)pieceTypes->size(); i++)
	{
		sp<PieceType> type = pieceTypes->at(i);

		if (type->randomSpecialPieceChanceOneOutOf == 0 && type->frequencySpecialPieceTypeOnceEveryNPieces == 0)
		{
			
			sp<Piece> tempPiece(ms<Piece>(getGameLogic(), this, type, blockTypes));
			tempPiece->init();
			tempBag->push_back(tempPiece);
		}
	}

	return tempBag;
}

//=========================================================================================================================
sp<Piece> Grid::getPieceFromNormalPieceRandomBag()
{//=========================================================================================================================

	sp<Piece> piece = nullptr;

	if (randomBag->empty())
	{
		sp<vector<sp<Piece>>>tempBag = getBagOfOneOfEachNonRandomNormalPieces();

		while (tempBag->size() > 0)
		{
			int i = getGameLogic()->getRandomIntLessThan((int)tempBag->size(),"getPieceFromNormalPieceRandomBag");
			if (randomBag->empty())
			{
				bool anyAllowedAsFirstPiece = false;
				for(int n=0;n<tempBag->size();n++)
				{
					if (tempBag->at(i)->pieceType->disallowAsFirstPiece == false)anyAllowedAsFirstPiece = true;
				}

				if (anyAllowedAsFirstPiece)
				{
					while (tempBag->at(i)->pieceType->disallowAsFirstPiece == true)
					{
						i = getGameLogic()->getRandomIntLessThan((int)tempBag->size(), "getPieceFromNormalPieceRandomBag");
					}
				}
			}

			randomBag->push_back(tempBag->at(i));
			tempBag->erase(tempBag->begin()+i);
		}
	}

	if (randomBag->empty())
	{
		sp<vector<sp<Piece>>>tempBag = getBagOfOneOfEachNonRandomNormalPieces();
		while (tempBag->size() > 0)
		{
			int i = getGameLogic()->getRandomIntLessThan((int)tempBag->size(),"getPieceFromNormalPieceRandomBag");
			randomBag->push_back(tempBag->at(i));
			tempBag->erase(tempBag->begin()+i);
		}
	}

	piece = randomBag->at(0);
	randomBag->erase(randomBag->begin()+0);

	return piece;
}

//=========================================================================================================================
sp<Piece> Grid::getRandomPiece()
{//=========================================================================================================================

	sp<Piece> piece = nullptr;

	sp<vector<sp<BlockType>>>blockTypes = getGameType()->getNormalBlockTypes(getGameLogic()->getCurrentDifficulty());

	{
		//make piece
		sp<vector<sp<PieceType>>>pieceTypes = getGameType()->getNormalPieceTypes(getGameLogic()->getCurrentDifficulty());
		sp<PieceType> pieceType = getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(pieceTypes);

		if (getGameType()->currentPieceRule_getNewPiecesRandomlyOutOfBagWithOneOfEachPieceUntilEmpty)
		{
			if (pieceType != nullptr)
			{
				piece = sp<Piece>(ms<Piece>(getGameLogic(), this, pieceType, blockTypes));
				piece->init();
			}
			else
			{
				piece = getPieceFromNormalPieceRandomBag();
			}
		}
		else
		{
			if (pieceType == nullptr)
			{
				pieceType = getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(pieceTypes);
			}
			if (pieceType == nullptr)pieceType = PieceType::emptyPieceType;
			piece = sp<Piece>(ms<Piece>(getGameLogic(), this, pieceType, blockTypes));
			piece->init();
		}
	}

	return piece;
}

//=========================================================================================================================
sp<Piece> Grid::getRandomPiece(sp<vector<sp<PieceType>>>pieceTypes, sp<vector<sp<BlockType>>>blockTypes)
{//=========================================================================================================================

	sp<Piece> piece(ms<Piece>(getGameLogic(), this, getRandomPieceType(pieceTypes), blockTypes));
	piece->init();
	return piece;
}

//=========================================================================================================================
sp<PieceType> Grid::getRandomPieceType(sp<vector<sp<PieceType>>>pieceTypes)
{//=========================================================================================================================

	sp<PieceType> pieceType = getRandomSpecialPieceTypeFromArrayExcludingNormalPiecesOrNull(pieceTypes);
	if (pieceType == nullptr)
	{
		pieceType = getRandomPieceTypeFromArrayExcludingSpecialPieceTypes(pieceTypes);
	}
	if (pieceType == nullptr)pieceType = PieceType::emptyPieceType;
	return pieceType;
}

//=========================================================================================================================
sp<BlockType> Grid::getRandomBlockType(sp<vector<sp<BlockType>>>arr)
{//=========================================================================================================================

	sp<BlockType> blockType = getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(arr);

	if (blockType == nullptr)
	{
		blockType = getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(arr);
	}
	if (blockType == nullptr)blockType = BlockType::emptyBlockType;
	return blockType;
}

//=========================================================================================================================
sp<BlockType> Grid::getRandomBlockTypeDisregardingSpecialFrequency(sp<vector<sp<BlockType>>>arr)
{//=========================================================================================================================

	sp<BlockType> blockType = arr->at(getGameLogic()->getRandomIntLessThan((int)arr->size(), "getRandomBlockTypeDisregardingSpecialFrequency"));

	if (blockType == nullptr)blockType = BlockType::emptyBlockType;
	return blockType;
}

//=========================================================================================================================
sp<BlockType> Grid::getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull(sp<vector<sp<BlockType>>>arr)
{//=========================================================================================================================

	sp<vector<sp<BlockType>>>randomBag;

	for (int i = 0; i < arr->size(); i++)
	{
		sp<BlockType> b = arr->at(i);
		if (b->frequencySpecialBlockTypeOnceEveryNPieces != 0)
		{
			if (getGameLogic()->createdPiecesCounterForFrequencyPieces >= b->frequencySpecialBlockTypeOnceEveryNPieces - 1)
			{
				randomBag->push_back(b);
			}
		}
	}

	if (randomBag->size() > 0)
	{
		getGameLogic()->createdPiecesCounterForFrequencyPieces = 0;

		sp<BlockType> b = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull"));
		return b;
	}

	//		int randomTotal = 1;
	//		BlockType emptyBlockType(ms<BlockType>());
	//		randomBag.Add(emptyBlockType);
	//		for(int i=0;i<array.Count;i++)
	//		{
	//			BlockType b = array->get(i);
	//			if(b.randomSpecialBlockChanceOneOutOf>0)randomTotal*=b.randomSpecialBlockChanceOneOutOf;
	//		}

	//		for(int n=0;n<randomTotal;n++)randomBag.Add(emptyBlockType);

	for (int i = 0; i < arr->size(); i++)
	{
		sp<BlockType> b = arr->at(i);
		if (b->randomSpecialBlockChanceOneOutOf > 0)
		{
			if (getGameLogic()->getRandomIntLessThan(b->randomSpecialBlockChanceOneOutOf,"getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull") == 0)
			{
				randomBag->push_back(b);
			}
		}

		//			for(int n=0;n<randomTotal/b.randomSpecialBlockChanceOneOutOf;n++)randomBag.Add(b);
	}

	if (randomBag->size() > 0)
	{
		sp<BlockType> b = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomSpecialBlockTypeFromArrayExcludingNormalBlocksOrNull"));

		//			if(b!=emptyBlockType)
		return b;
	}

	return nullptr;
}

//=========================================================================================================================
sp<BlockType> Grid::getRandomBlockTypeFromArrayExcludingSpecialBlockTypes(sp<vector<sp<BlockType>>>arr)
{//=========================================================================================================================

	sp<vector<sp<BlockType>>>randomBag;

	for (int i = 0; i < arr->size(); i++)
	{
		sp<BlockType> b = arr->at(i);

		if (b->isSpecialType() == false)
		{
			randomBag->push_back(b);
		}
	}

	if (randomBag->size() > 0)
	{
		sp<BlockType> b = randomBag->at(getGameLogic()->getRandomIntLessThan((int)randomBag->size(),"getRandomBlockTypeFromArrayExcludingSpecialBlockTypes"));
		return b;
	}

	return sp<BlockType>(BlockType::squareBlockType);
}

//=========================================================================================================================
bool Grid::areAnyBlocksPopping()
{//=========================================================================================================================

	for (int y = 0; y < getHeight(); y++)
	{
		for (int x = 0; x < getWidth(); x++)
		{
			sp<Block> b = get(x, y);

			if (b != nullptr)
			{
				if (b->popping)
				{
					return true;
				}
			}
		}
	}
	return false;
}

//=========================================================================================================================
int Grid::cellW()
{//=========================================================================================================================
	return getGameLogic()->cellW();
}

//=========================================================================================================================
int Grid::cellH()
{//=========================================================================================================================
	return getGameLogic()->cellH();
}

//=========================================================================================================================
sp<GameType> Grid::getGameType()
{//=========================================================================================================================
	return getGameLogic()->currentGameType;
}

//=========================================================================================================================
sp<GameLogic> Grid::getGameLogic()
{//=========================================================================================================================
	return game;
}

