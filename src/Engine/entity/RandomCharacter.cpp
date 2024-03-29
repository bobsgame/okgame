#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger RandomCharacter::log = Logger("RandomCharacter");


RandomCharacter::RandomCharacter(sp<Engine> g, sp<Map> map, int spawnXPixels1X, int spawnYPixels1X, bool kid, bool adult, bool male, bool female, bool car)
{ //=========================================================================================================================

	//DONE: randomly decide what kind of character to create

	//spawn at mapX, mapY


	sp<EntityData> data = ms<EntityData>(-1, "Random", "", spawnXPixels1X, spawnYPixels1X);
	initEntity(data);
	initCharacter();


	if (getEventData() != nullptr)this->event = ms<Event>(g, getEventData(), this);

	sp<vector<string>>spriteNameList;// = ms<vector><string>;

	if (kid == true)
	{
		if (male == true)
		{
			spriteNameList->push_back("RANDOMBoyBuzzedHairLongSleeve");
			spriteNameList->push_back("RANDOMBoyBuzzedHairShortSleeve");
			spriteNameList->push_back("RANDOMBoyBuzzedHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMBoyBuzzedHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMBoyMessyHairLongSleeve");
			spriteNameList->push_back("RANDOMBoyMessyHairShortSleeve");
			spriteNameList->push_back("RANDOMBoyMessyHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMBoyMessyHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMBoyNormalHairLongSleeve");
			spriteNameList->push_back("RANDOMBoyNormalHairShortSleeve");
			spriteNameList->push_back("RANDOMBoyNormalHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMBoyNormalHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMBoyShortHairLongSleeve");
			spriteNameList->push_back("RANDOMBoyShortHairShortSleeve");
			spriteNameList->push_back("RANDOMBoyShortHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMBoyShortHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyBuzzedHairLongSleeve");
			spriteNameList->push_back("RANDOMLittleBoyBuzzedHairShortSleeve");
			spriteNameList->push_back("RANDOMLittleBoyBuzzedHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyBuzzedHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyMessyHairLongSleeve");
			spriteNameList->push_back("RANDOMLittleBoyMessyHairShortSleeve");
			spriteNameList->push_back("RANDOMLittleBoyMessyHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyMessyHairShortSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyNormalHairLongSleeve");
			spriteNameList->push_back("RANDOMLittleBoyNormalHairShortSleeve");
			spriteNameList->push_back("RANDOMLittleBoyNormalHairLongSleeveShorts");
			spriteNameList->push_back("RANDOMLittleBoyNormalHairShortSleeveShorts");
		}


		if (female == true)
		{
			spriteNameList->push_back("RANDOMGirlLongHairDress");
			spriteNameList->push_back("RANDOMGirlLongHairSkirt");
			spriteNameList->push_back("RANDOMGirlLongHairSkirtHalter");
			spriteNameList->push_back("RANDOMGirlLongHairJeans");
			spriteNameList->push_back("RANDOMGirlLongHairJeansHalter");
			spriteNameList->push_back("RANDOMGirlLongHairShortsHalter");
			spriteNameList->push_back("RANDOMGirlPonytailDress");
			spriteNameList->push_back("RANDOMGirlPonytailSkirt");
			spriteNameList->push_back("RANDOMGirlPonytailSkirtHalter");
			spriteNameList->push_back("RANDOMGirlPonytailJeans");
			spriteNameList->push_back("RANDOMGirlPonytailJeansHalter");
			spriteNameList->push_back("RANDOMGirlPonytailShortsHalter");
			spriteNameList->push_back("RANDOMGirlShortHairDress");
			spriteNameList->push_back("RANDOMGirlShortHairSkirt");
			spriteNameList->push_back("RANDOMGirlShortHairSkirtHalter");
			spriteNameList->push_back("RANDOMGirlShortHairJeans");
			spriteNameList->push_back("RANDOMGirlShortHairJeansHalter");
			spriteNameList->push_back("RANDOMGirlShortHairShortsHalter");
			spriteNameList->push_back("RANDOMLittleGirlLongHairDress");
			spriteNameList->push_back("RANDOMLittleGirlLongHairSkirt");
			spriteNameList->push_back("RANDOMLittleGirlLongHairSkirtHalter");
			spriteNameList->push_back("RANDOMLittleGirlLongHairJeans");
			spriteNameList->push_back("RANDOMLittleGirlLongHairJeansHalter");
			spriteNameList->push_back("RANDOMLittleGirlLongHairShortsHalter");
			spriteNameList->push_back("RANDOMLittleGirlPonytailDress");
			spriteNameList->push_back("RANDOMLittleGirlPonytailSkirt");
			spriteNameList->push_back("RANDOMLittleGirlPonytailSkirtHalter");
			spriteNameList->push_back("RANDOMLittleGirlPonytailJeans");
			spriteNameList->push_back("RANDOMLittleGirlPonytailJeansHalter");
			spriteNameList->push_back("RANDOMLittleGirlPonytailShortsHalter");
			spriteNameList->push_back("RANDOMLittleGirlShortHairDress");
			spriteNameList->push_back("RANDOMLittleGirlShortHairSkirt");
			spriteNameList->push_back("RANDOMLittleGirlShortHairSkirtHalter");
			spriteNameList->push_back("RANDOMLittleGirlShortHairJeans");
			spriteNameList->push_back("RANDOMLittleGirlShortHairJeansHalter");
			spriteNameList->push_back("RANDOMLittleGirlShortHairShortsHalter");
		}
	}

	if (adult == true)
	{
		if (male == true)
		{
			spriteNameList->push_back("RANDOMManBaldUndershirt");
			spriteNameList->push_back("RANDOMManBaldShortSleeve");
			spriteNameList->push_back("RANDOMManBaldSuit");
			spriteNameList->push_back("RANDOMManBaldSweats");
			spriteNameList->push_back("RANDOMManBaldLongSleeve");
			spriteNameList->push_back("RANDOMManBaldingUndershirt");
			spriteNameList->push_back("RANDOMManBaldingShortSleeve");
			spriteNameList->push_back("RANDOMManBaldingSuit");
			spriteNameList->push_back("RANDOMManBaldingSweats");
			spriteNameList->push_back("RANDOMManBaldingLongSleeve");
			spriteNameList->push_back("RANDOMManBeardUndershirt");
			spriteNameList->push_back("RANDOMManBeardShortSleeve");
			spriteNameList->push_back("RANDOMManBeardSuit");
			spriteNameList->push_back("RANDOMManBeardSweats");
			spriteNameList->push_back("RANDOMManBeardLongSleeve");
			spriteNameList->push_back("RANDOMManNormalHairUndershirt");
			spriteNameList->push_back("RANDOMManNormalHairShortSleeve");
			spriteNameList->push_back("RANDOMManNormalHairSuit");
			spriteNameList->push_back("RANDOMManNormalHairSweats");
			spriteNameList->push_back("RANDOMManNormalHairLongSleeve");
			spriteNameList->push_back("RANDOMManShortHairUndershirt");
			spriteNameList->push_back("RANDOMManShortHairShortSleeve");
			spriteNameList->push_back("RANDOMManShortHairSuit");
			spriteNameList->push_back("RANDOMManShortHairSweats");
			spriteNameList->push_back("RANDOMManShortHairLongSleeve");
		}


		if (female == true)
		{
			spriteNameList->push_back("RANDOMWomanBunDress");
			spriteNameList->push_back("RANDOMWomanBunSkirt");
			spriteNameList->push_back("RANDOMWomanBunSkirtHalter");
			spriteNameList->push_back("RANDOMWomanBunJeans");
			spriteNameList->push_back("RANDOMWomanBunJeansHalter");
			spriteNameList->push_back("RANDOMWomanBunShortsHalter");
			spriteNameList->push_back("RANDOMWomanLongHairDress");
			spriteNameList->push_back("RANDOMWomanLongHairSkirt");
			spriteNameList->push_back("RANDOMWomanLongHairSkirtHalter");
			spriteNameList->push_back("RANDOMWomanLongHairJeans");
			spriteNameList->push_back("RANDOMWomanLongHairJeansHalter");
			spriteNameList->push_back("RANDOMWomanLongHairShortsHalter");
			spriteNameList->push_back("RANDOMWomanPonytailDress");
			spriteNameList->push_back("RANDOMWomanPonytailSkirt");
			spriteNameList->push_back("RANDOMWomanPonytailSkirtHalter");
			spriteNameList->push_back("RANDOMWomanPonytailJeans");
			spriteNameList->push_back("RANDOMWomanPonytailJeansHalter");
			spriteNameList->push_back("RANDOMWomanPonytailShortsHalter");
			spriteNameList->push_back("RANDOMWomanPoofyHairDress");
			spriteNameList->push_back("RANDOMWomanPoofyHairSkirt");
			spriteNameList->push_back("RANDOMWomanPoofyHairSkirtHalter");
			spriteNameList->push_back("RANDOMWomanPoofyHairJeans");
			spriteNameList->push_back("RANDOMWomanPoofyHairJeansHalter");
			spriteNameList->push_back("RANDOMWomanPoofyHairShortsHalter");
			spriteNameList->push_back("RANDOMWomanShortHairDress");
			spriteNameList->push_back("RANDOMWomanShortHairSkirt");
			spriteNameList->push_back("RANDOMWomanShortHairSkirtHalter");
			spriteNameList->push_back("RANDOMWomanShortHairJeans");
			spriteNameList->push_back("RANDOMWomanShortHairJeansHalter");
			spriteNameList->push_back("RANDOMWomanShortHairShortsHalter");
		}
	}

	if (car == true)
	{
		spriteNameList->push_back("RANDOMcar");
		spriteNameList->push_back("RANDOMmotorcycle");
		spriteNameList->push_back("RANDOMvan");
		spriteNameList->push_back("RANDOMtruck");
		spriteNameList->push_back("RANDOMsuv");
		spriteNameList->push_back("RANDOMferrari");
		spriteNameList->push_back("RANDOMminivan");
	}


	getData()->setSpriteName(spriteNameList->at(Math::randLessThan((int)spriteNameList->size())));

	this->sprite = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist(getSpriteName());

	if (sprite != nullptr)
	{
		initCurrentAnimationFromSprite();
	}


	setTicksPerPixelMoved(8);
	//getTicksPerPixelMoved = 4+Math::randLessThan(5); //this still breaks walking.
	//TODO: find out why getTicksPerPixelMoved<5 breaks walking!

	setNonWalkable(false);

	setScale(1.25f);
	setToAlpha(1.0f);


	this->kid = kid;
	this->adult = adult;
	this->male = male;
	this->female = female;
	this->car = car;


	if (car)
	{
		setNonWalkable(true);
		clipShadow = false;
		shadowSize = 1.1f;
		setScale(1.5f);
	}


	//setX(mapX);//already done in data
	//setY(mapY);

	setX(mapX - (getHitBoxFromLeft() + (getMiddleX() - getLeft())));
	setY(mapY - (getMiddleY() - getY()));
}

sp<Map> RandomCharacter::getCurrentMap()
{ //=========================================================================================================================


	log.error("Bug: Don't use getCurrentMap() in Characters. Use this.map or getMap()");

	return nullptr;
}

//The following method was originally marked 'synchronized':
sp<ByteArray> RandomCharacter::getByteBuffer_S()
{ //=========================================================================================================================
	return textureByteBuffer_S;
}

//The following method was originally marked 'synchronized':
void RandomCharacter::setByteBuffer_S(sp<ByteArray> bb)
{ //=========================================================================================================================
	textureByteBuffer_S = bb;
}

int RandomCharacter::selectRandomSet(sp<Sprite> s)
{ //=========================================================================================================================

	int set = 0;

	int w = s->getImageWidth();
	int h = s->getImageHeight();

	if (set == 0)
	{
		int maxSets = 0;
		for (int v = 1; v < h; v++)
		{
			if ((s->indexDataIntArray->data()[v * w] & 0xFF) == 0)
			{
				maxSets = v - 1;
				break;
			}
		}

		if (kid && s == getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"))
		{
			set = Math::randLessThan(maxSets - 3) + 1; //dont give kids gray hair
		}
		else
		{
			set = Math::randLessThan(maxSets - 1) + 1;
		}
	}

	return set;
}

void RandomCharacter::createRandomTexture()
{ //=========================================================================================================================

	if (createdThread == false)
	{
		if (car)
		{
			carSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors"));
		}
		else
		{
			eyeSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors"));
			skinSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors"));
			hairSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors"));
			shirtSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors"));
			pantsSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors"));
			shoeSet = selectRandomSet(getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors"));
		}

		//      if (MapManager::useThreads)
		//      {
		//         if (Sprite::generatePNGExecutorService == nullptr)
		//         {
		//            Sprite::generatePNGExecutorService = Executors::newFixedThreadPool(1);
		//         }
		//         Sprite::generatePNGExecutorService->execute([&] ()
		//            {
		//               Thread::currentThread().setName("RandomCharacter_createRandomSpriteTexture");
		//
		//
		//               sp<ByteArray> bb = sprite->createRandomSpriteTextureByteBuffer_S(eyeSet, skinSet, hairSet, shirtSet, pantsSet, shoeSet, carSet);
		//               setByteBuffer_S(bb);
		//            }
		//         );
		//      }
		//      else
		{
			sp<ByteArray> bb = sprite->createRandomSpriteTextureByteBuffer_S(eyeSet, skinSet, hairSet, shirtSet, pantsSet, shoeSet, carSet);
			setByteBuffer_S(bb);
		}

		createdThread = true;
	}
}

void RandomCharacter::update()
{ //=========================================================================================================================


	//if set to action, continue towards action


	//else select new random point of interest


	Character::update();


	//TODO: if my custom texture is null, check to see if spriteAsset has the indexed data md5 yet.
	//TODO: create a custom texture for randomcharacter here.
	//create a new thread, and set the texture through a synchronized call.
	//then override render() with something that uses MY texture.


	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMcarColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMeyeColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMskinColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMhairColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshirtColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMpantsColors")->loadTextures();
	getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("RANDOMshoeColors")->loadTextures();


	if (uniqueTexture == nullptr)
	{
		if (sprite->indexDataIntArray != nullptr) //the indexed data is loaded
		{
			if (createdThread == false)
			{
				createRandomTexture();
			}
			else
			{
				//we're waiting for the thread to finish generating the bytebuffer

				sp<ByteArray> bb = getByteBuffer_S();
				if (bb != nullptr)
				{
					uniqueTexture = GLUtils::getTextureFromData("random" + to_string(Math::randLessThan(500)), sprite->getImageWidth(), sprite->getImageHeight() * sprite->getNumFrames(), bb);

					setByteBuffer_S(nullptr);
					//delete bb;
					bb = nullptr;
				}
			}
		}
	}


	//if(hitBoxTop()>(3*16))
	//hitBoxFromTopPixelsHQ = (int)((3*16)/getScale);


	//DONE: need to store "where came from" and don't select that as the first currentAreaTarget if currentAreaTarget is empty.
	//this is done in Door and WarpArea upon spawn, it finds an appropriate initial target, not including itself.
	//did end up adding "cameFrom" but isn't used yet.


	//avoid_entity(player(),16);
	//avoid_nearest_character(8);

	if (ticksToStand > 0)
	{
		ticksToStand -= (int)getEngine()->engineTicksPassed();

		//do standing animation here
		//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now
	}
	else
	{
		if (currentAreaTYPEIDTarget == "stayHere" == true)
		{
			//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now
		}
		else
		{
			if (currentAreaTYPEIDTarget.length() > 0)
			{
				//if we aren't there yet, let's go there.
				if (gotThere == false)
				{
					if (OKString::startsWith(currentAreaTYPEIDTarget, "DOOR.") == true)
					{
						//handle walking through door.
						sp<Door> d = getMap()->getDoorByTYPEID(currentAreaTYPEIDTarget);

						//walk towards x and y
						int there = 0;
						if (getMap()->getIsOutside() == false)
						{
							there = walkToXYWithPathFinding(d->getMiddleX(), d->getMiddleY());
						}
						else
						{
							there = walkToXYNoHitAvoidOthersPushMain(d->getMiddleX(), d->getMiddleY());
						}

						//if we are there, pick a new point
						if (there == 1)
						{
							d->setOpenAnimation(true);

							fadeOutAndDelete();
						}
						if (there == -1)
						{
							//no path to the door, pick another point.
							currentAreaTYPEIDTarget = "";
						}
					}
					else //find current area
					{
						if (OKString::startsWith(currentAreaTYPEIDTarget, "DOOR.") == false)
						{
							//get current area x and y
							sp<Area> a = getMap()->getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);


							//TODO: if the area is a single tile, just touching the edge should be fine.


							//TODO: find where it checks is sprite is in the area, in pathfinding. make it if sprite is touching it at all.


							//we store the position in the area so that we can find a unique place inside large areas. don't need to do this for doors.
							if (targetX == -1 && targetY == -1)
							{
								//if this area is bigger than one tile and allows multiple people, find a suitable place inside it.
								if (a->onlyOneAllowed() == false && (a->getWidth() > 32 || a->getHeight() > 32))
								{
									//divide area into tiles, check midpoint of each tile for enough room to stand

									int w = (int)(getRight() - getLeft());
									int h = (int)(getBottom() - getTop());

									//TODO: try the middle of the edge closest to sprite.

									//first try the exact middle.
									/*
									if(
									   entMan().isAnyoneOverlappingXYXY(a.getMapXPixelsHQ+a.getWidthPixelsHQ/2-w/2, a.getMapYPixelsHQ+a.getHeightPixelsHQ/2-h/2, a.getMapXPixelsHQ+a.getWidthPixelsHQ/2+w/2, a.getMapYPixelsHQ+a.getHeightPixelsHQ/2+h/2)==false
									   &&
									   entMan().isAnyOtherRandomCharacterTryingToGoToXY(a.getMapXPixelsHQ+a.getWidthPixelsHQ/2, a.getMapYPixelsHQ+a.getHeightPixelsHQ/2)==false
									)
									{
									   targetX = a.getMapXPixelsHQ+a.getWidthPixelsHQ/2;
									   targetY = a.getMapYPixelsHQ+a.getHeightPixelsHQ/2;
								   
									   //DONE: could also check all the other random characters targetX and targetY to make sure nobody is TRYING to go here
								   
								   
									}
									else
									*/
									{
										int* xy = getMap()->findOpenSpaceInArea(a, w, h);

										if (xy != nullptr)
										{
											targetX = xy[0];
											targetY = xy[1];
										}
									}

									//if there is no space available, get another point.
									if (targetX == -1 && targetY == -1)
									{
										currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();
										targetX = -1;
										targetY = -1;
									}
								}
								else
								{
									targetX = (int)a->middleX(); //getMapXPixelsHQ + a.getWidthPixelsHQ/2;
									targetY = (int)a->middleY(); //a.getMapYPixelsHQ + a.getHeightPixelsHQ/2;
								}
							}


							if (targetX != -1 && targetY != -1)
							{
								//walk towards x and y
								//int there = walk_to_xy_pathfind(targetX, targetY);
								int there = 0;
								if (getMap()->getIsOutside() == false && getMap()->getWidthTiles1X() < 100 && getMap()->getHeightTiles1X() < 100)
								{
									there = walkToXYWithPathFinding((float)targetX, (float)targetY);
								}
								else
								{
									there = walkToXYNoHitAvoidOthersPushMain((float)targetX, (float)targetY);
								}

								//if we are there, pick a new point
								if (there == 1 || there == -1)
								{
									//check area for variables: stay here, wait x ms, face direction
									if (a->standSpawnDirection() != -1)
									{
										if (a->standSpawnDirection() == 0)
										{
											movementDirection = UP;
										}
										if (a->standSpawnDirection() == 1)
										{
											movementDirection = DOWN;
										}
										if (a->standSpawnDirection() == 2)
										{
											movementDirection = LEFT;
										}
										if (a->standSpawnDirection() == 3)
										{
											movementDirection = RIGHT;
										}
									}

									//set standing ticks to current ticks
									if (a->waitHereTicks() > 0)
									{
										if (a->randomWaitTime() == true)
										{
											ticksToStand = Math::randLessThan(a->waitHereTicks());
										}
										else
										{
											ticksToStand = a->waitHereTicks();
										}
									}
									else
									{
										ticksToStand = 0;
									}


									gotThere = true;


									//getPushable=true;
								}
								//						else
								//						if(there==-1)//no path, select another point.
								//						{
								//							gotThere=true;
								//						}
							}
						}
					}
				}
				else
				{
					if (gotThere == true) //this is only for areas. doors will just immediately delete the entity. this is so we can change modes and be getPushable after we've reached our destination and waiting for a new one.
					{
						if (OKString::startsWith(currentAreaTYPEIDTarget, "DOOR.") == false)
						{
							//get current area x and y
							sp<Area> a = getMap()->getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);


							//avoid_nearest_entity(32);


							//if
							//(
							//avoid_entity(player(),16)==1
							//&&
							//avoid_nearest_character(16)==1
							//&&
							//(Math.abs(getMiddleX()-finalPathX)>4||Math.abs(getMiddleY()-finalPathY)>4)
							//);
							//walk_to_xy_nohit(finalPathX,finalPathY);

							//walk_to_xy_intelligenthit_avoidothers_pushmain(5, targetX,targetY);


							//if getRandomNPCStayHere, don't pick a new target! just stay here and do whatever
							if (a->randomNPCStayHere() || a->waitHereTicks() == -1)
							{
								currentAreaTYPEIDTarget = "stayHere";
							}

							if ((dynamic_cast<WarpArea*>(a.get()) != nullptr) && (a->randomPointOfInterestOrExit() == true) && a->randomNPCStayHere() == false)
							{
								fadeOutAndDelete();
							}
							else
							{
								{
									string tempTarget = currentAreaTYPEIDTarget;

									//if current target area has connections, pick a connection and go there.
									if (a->connectionTYPEIDList()->size() > 0)
									{
										currentAreaTYPEIDTarget = getRandomConnectionTYPEIDFromCurrentPoint();
									}
									else
									{ //go through all areas on map and randomly select one

										currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();
									}

									//if we didn't find a new target, it must be blocked. let's stand and shuffle.
									if (currentAreaTYPEIDTarget == tempTarget)
									{
										//doStandingAnimation();//should be handled by checkIfMoved and doCharacterAnimation now
									}
									else
									{
										//we have a new target, let's reset targetX and Y
										targetX = -1;
										targetY = -1;
										gotThere = false;
										//getPushable=false;
									}
								}
							}
						}
					}
				}
			}
			else
			{
				//else pick a new point

				//go through all map areas, find random point of interest.

				currentAreaTYPEIDTarget = getRandomAreaWarpOrDoorTYPEID();
				targetX = -1;
				targetY = -1;
			}
		}
	}


	//this is done here regardless of controls so that external movements still trigger animation and sound, i.e. cutscenes
	checkIfMoved();

	doCharacterAnimation();
}

string RandomCharacter::getRandomAreaWarpOrDoorTYPEID()
{ //=========================================================================================================================


	sp<vector<string>> areaTYPEIDList = getMap()->getListOfRandomPointsOfInterestTYPEIDs();


	if (areaTYPEIDList->empty())
	{
		return currentAreaTYPEIDTarget;
	}


	int index = Math::randLessThan((int)areaTYPEIDList->size());


	//don't select the target we already have
	if (areaTYPEIDList->size() > 1)
	{
		while (areaTYPEIDList->at(index) == currentAreaTYPEIDTarget)
		{
			index = Math::randLessThan((int)areaTYPEIDList->size());
		}
	}


	string nextTYPEIDTarget = areaTYPEIDList->at(index);
	{
		//don't select targets more than a screen away


		float distance = 0;

		if (OKString::startsWith(nextTYPEIDTarget, "DOOR.") == true)
		{
			sp<Door> d = getMap()->getDoorByTYPEID(nextTYPEIDTarget);
			distance = Math::distance(getMiddleX(), getMiddleY(), d->getMiddleX(), d->getMiddleY());
		}
		else
		{
			sp<Area> n = getMap()->getAreaOrWarpAreaByTYPEID(nextTYPEIDTarget);

			distance = Math::distance(getMiddleX(), getMiddleY(), n->middleX(), n->middleY());
		}


		//TODO: make this "on screen" or "two screens away"
		if (distance > 500)
		{
			return currentAreaTYPEIDTarget;
		}
	}

	//TODO: don't go to doors or warp areas that are exits AND don't spawn my type.


	if (OKString::startsWith(nextTYPEIDTarget, "DOOR.") == false)
	{
		//go through all other entities, if this target is "only one allowed" and any of them have this area as a target, find another one.

		sp<Area> n = getMap()->getAreaOrWarpAreaByTYPEID(nextTYPEIDTarget);

		if (n != nullptr && n->onlyOneAllowed())
		{
			if (getMap()->isAnyoneTryingToGoToArea(n) == true)
			{
				return currentAreaTYPEIDTarget;
			}
			//if(entMan().isAnyoneStandingInArea(n)==true)return currentAreaTarget;
		}
	}

	return nextTYPEIDTarget;
}

string RandomCharacter::getRandomConnectionTYPEIDFromCurrentPoint()
{ //=========================================================================================================================


	sp<Area> a = getMap()->getAreaOrWarpAreaByTYPEID(currentAreaTYPEIDTarget);
	string nextTargetTYPEID = a->connectionTYPEIDList()->at(Math::randLessThan((int)a->connectionTYPEIDList()->size()));


	if (OKString::startsWith(nextTargetTYPEID, "DOOR.") == false)
	{
		//go through all other entities, if this target is "only one allowed" and any of them have this area as a target, find another one.

		sp<Area> n = getMap()->getAreaOrWarpAreaByTYPEID(nextTargetTYPEID);

		if (n != nullptr && n->onlyOneAllowed())
		{
			if (getMap()->isAnyoneTryingToGoToArea(n) == true)
			{
				nextTargetTYPEID = currentAreaTYPEIDTarget;
			}
			//if(entMan().isAnyoneStandingInArea(n)==true)nextTarget=currentAreaTarget;
		}

		if (n == nullptr)
		{
			//serious error, area doesn't exit. outputs to System.err in getAreaOrWarpAreaByName
			nextTargetTYPEID = currentAreaTYPEIDTarget;
		}
	}

	return nextTargetTYPEID;
}

