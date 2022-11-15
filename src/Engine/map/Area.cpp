#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

//#pragma once



Logger Area::log = Logger("Area");

Area::Area()
{ //=========================================================================================================================
}

Area::Area(sp<Engine> g, sp<Map> m)
{ //=========================================================================================================================
	this->e = g;

	this->map = m;

}

Area::Area(sp<Engine> g, sp<AreaData> a, sp<Map> m)
{ //=========================================================================================================================
	this->e = g;

	this->data = a;

	this->mapX = a->getMapXPixelsHQ();
	this->mapY = a->getMapYPixelsHQ();

	this->map = m;

	if (getEventData() != nullptr)
	{

		this->event = ms<Event>(g, getEventData(), this);
		//this->event = getEventManager()->getEventByIDCreateIfNotExist(getEventData()->getID());
		//event->area = this;
	}
}

sp<Map> Area::getMap()
{ //=========================================================================================================================

	//sp<Map> map = getMapManager()->getMapByIDBlockUntilLoaded(mapID());

	return this->map;
}

void Area::renderActionIcon()
{ //=========================================================================================================================

	if (showActionIcon == false)
	{
		return;
	}

	if (getEventData() == nullptr)
	{
		return;
	}
	//if(isAnAction==false)return;

	//get distance from player

	//Texture actionTexture = EntityManager.actionTexture;

	//if(actionTexture==null)return;

	float doorAlpha = 1.0f;

	if (this->inRangeOfEntityByAmount(getPlayer(), 256) == false)
	{
		return;
	}

	doorAlpha = (256.0f - this->getDistanceFromEntity(getPlayer())) / 256.0f;
	if (doorAlpha > 1.0f)
	{
		doorAlpha = 1.0f;
	}

	/*
	      float tx0 = 0.0f;
	      float tx1 = 32.0f/((float)actionTexture.getTextureWidth());
	      float ty0 = (float)(32.0f*EntityManager.actionTextureFrame)/((float)actionTexture.getTextureHeight());
	      float ty1 = (float)(32.0f*(EntityManager.actionTextureFrame+1))/((float)actionTexture.getTextureHeight());
	
	
	
	      float screenMiddleX = getScreenLeft()+((screenRight()-getScreenLeft())/2);
	      float screenMiddleY = getScreenTop()+((screenBottom()-getScreenTop())/2);// - 128 + entMan().actionTextureFrame*1;
	
	
	      float x0 = screenMiddleX-16*getCameraman()->zoom;
	      float x1 = screenMiddleX+16*getCameraman()->zoom;
	      float y0 = screenMiddleY-16*getCameraman()->zoom;
	      float y1 = screenMiddleY+16*getCameraman()->zoom;
	
	      //GL.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, 1);
	
	
	
	
	      actionTexture = ACTION_icon_sprite.spriteAsset.texture;
	
	      if(actionTexture==null)return;
	
	
	      if(this.in_range_of_entity_by_amount(getPlayer(), 256)==false)return;
	
	      doorAlpha = (256.0f-this.getDistanceFromEntity(getPlayer()))/256.0f;
	      if(doorAlpha>1.0f)doorAlpha=1.0f;
	
	
	      tx0 = 0.0f;
	      tx1 = 32.0f/((float)actionTexture.getTextureWidth());
	      ty0 = (float)(32.0f*ACTION_icon_sprite.frameIndexInTexture)/((float)actionTexture.getTextureHeight());
	      ty1 = (float)(32.0f*(ACTION_icon_sprite.frameIndexInTexture+1))/((float)actionTexture.getTextureHeight());
	
	
	
	      screenMiddleX = getScreenLeft()+((screenRight()-getScreenLeft())/2);
	      screenMiddleY = getScreenTop()+((screenBottom()-getScreenTop())/2);
	
	
	      x0 = screenMiddleX-8*getCameraman()->zoom;
	      x1 = screenMiddleX+8*getCameraman()->zoom;
	      y0 = screenMiddleY-8*getCameraman()->zoom	;
	      y1 = screenMiddleY+8*getCameraman()->zoom;
	
	      //GL.drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, 1);
	*/

	float x0 = screenLeft();
	float x1 = screenRight();
	float y0 = screenTop();
	float y1 = screenBottom();

	float distanceAlpha = (255.0f - this->getDistanceFromEntity(getPlayer())) / 511.0f;
	if (distanceAlpha < 0)
	{
		distanceAlpha = 0;
	}

	if (fadingInOut == true)
	{
		fadeAlpha += getEngine()->engineTicksPassed() * distanceAlpha * 2.0f;

		if (fadeAlpha >= 127.0f)
		{
			fadeAlpha = 127.0f;
			fadingInOut = false;
		}
	}
	else
	{
		fadeAlpha -= getEngine()->engineTicksPassed() * distanceAlpha * 2.0f;

		if (fadeAlpha <= 0.0f)
		{
			fadeAlpha = 0.0f;
			fadingInOut = true;
		}
	}

	doorAlpha = distanceAlpha * (fadeAlpha / 63.0f);
	//doorAlpha+=(Engine.lastRenderHighResTime%1000)/3000.0f;

	if (doorAlpha > 1.0f)
	{
		doorAlpha = 1.0f;
	}

	sp<OKTexture> actionTexture = getSpriteManager()->actionTexture;
	float tx0 = 0.0f;
	float tx1 = 32.0f / ((float)(actionTexture->getTextureWidth()));
	float ty0 = (float)(32.0f * 10) / ((float)(actionTexture->getTextureHeight()));
	float ty1 = (float)(32.0f * (10 + 1)) / ((float)(actionTexture->getTextureHeight()));

	GLUtils::drawTexture(actionTexture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, doorAlpha, GLUtils::FILTER_LINEAR);

	//FileUtils::drawFilledRect(255, 255, 255, x0, x1, y0, y1, doorAlpha);
}

void Area::update()
{ //=========================================================================================================================

	//if(getEngine()==null)setGame(map.getEngine());

	if (event != nullptr)
	{
		//sp<Event> e = getEventManager()->getEventByIDCreateIfNotExist(getEventData()->getID());
		getEventManager()->addToEventQueueIfNotThere(event); //events update their own network data inside their run function
	}

	sp<Map> map = getMap();

	if (map == getEngine()->getCurrentMap())
	{
		if (map->utilityLayersLoaded == true) //dont start spawning until getHit layer exists
		{
			//handle random spawn point
			if (randomNPCSpawnPoint() && (triedSpawn == false || randomSpawnOnlyTryOnce() == false) && map->randomSpawnEnabled)
			{
				//TODO: make this within screen bounds AND AMOUNT, two screens over?
				if (map->isXYWithinScreenByAmt(middleX(), middleY(), 128) == true)
				{
					ticksSinceSpawnTry += getEngine()->engineTicksPassed();

					if (ticksSinceSpawnTry >= randomSpawnDelay())
					{
						ticksSinceSpawnTry = 0;

						triedSpawn = true;

						if (Math::random() < randomSpawnChance()) //this is correct.
						{
							//TODO: don't spawn if there are too many randoms, have map limit?

							if (randomNPCStayHere() == true)
							{
								if (spawned == false)
								{
									spawned = true;
									sp<RandomCharacter> r = ms<RandomCharacter>(getEngine(), map, (int)middleX(), (int)middleY(), randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), randomSpawnCars());

									r->currentAreaTYPEIDTarget = "stayHere";
									r->cameFrom = getName();
									if (standSpawnDirection() != -1)
									{
										if (standSpawnDirection() == 0)
										{
											r->movementDirection = Entity::UP;
										}
										if (standSpawnDirection() == 1)
										{
											r->movementDirection = Entity::DOWN;
										}
										if (standSpawnDirection() == 2)
										{
											r->movementDirection = Entity::LEFT;
										}
										if (standSpawnDirection() == 3)
										{
											r->movementDirection = Entity::RIGHT;
										}
									}
								}
							}
							else
							{
								sp<vector<string>> targetTYPEIDList = ms<vector><string>();

								//if this door has connections, set target to one of this door's connections
								if (connectionTYPEIDList()->size() > 0)
								{
									for (int i = 0; i < connectionTYPEIDList()->size(); i++)
									{
										targetTYPEIDList->add(connectionTYPEIDList()->get(i));
									}
								}
								else
								{
									targetTYPEIDList = map->getListOfRandomPointsOfInterestTYPEIDs();
								}

								if (targetTYPEIDList->size() > 0)
								{
									//don't spawn if all the possible random points are full
									while (targetTYPEIDList->size() > 0)
									{
										int i = Math::randLessThan(targetTYPEIDList->size());

										//don't count this door
										if (targetTYPEIDList->get(i) == getTYPEIDString())
										{
											targetTYPEIDList->erase(->begin()+i);
											continue;
										}

										bool canMakeRandom = false;

										//if there is another exit, keep pumping out randoms, they will go there.
										if (OKString::startsWith(targetTYPEIDList->get(i), "DOOR."))
										{
											canMakeRandom = true;
										}
										else
										{
											//else we should check to make sure there is a random point of interest to go to, otherwise he will have nowhere to go and just stand there.
											sp<Area> a = map->getAreaOrWarpAreaByTYPEID(targetTYPEIDList->get(i));

											if (a != nullptr)
											{
												if (getMap()->findOpenSpaceInArea(a, 32, 32) == nullptr)
												//entMan().isAnyoneStandingInArea(a)==true
												//||
												//entMan().isAnyoneTryingToGoToArea(a)==true
												//||
												{
													targetTYPEIDList->erase(->begin()+i);
													continue;
												}
												else
												{
													canMakeRandom = true;
												}
											}
											else
											{
												targetTYPEIDList->erase(->begin()+i);
												//this is a serious error, prints out on System.err in getAreaOrWarpAreaByName
											}
										}

										if (canMakeRandom == true)
										{
											sp<RandomCharacter> r = ms<RandomCharacter>(getEngine(), map, (int)middleX(), (int)middleY(), randomSpawnKids(), randomSpawnAdults(), randomSpawnMales(), randomSpawnFemales(), randomSpawnCars());

											r->currentAreaTYPEIDTarget = targetTYPEIDList->get(i);
											r->cameFrom = getName();

											if (standSpawnDirection() != -1)
											{
												// set initial direction and frame.
												if (standSpawnDirection() == 0)
												{
													r->movementDirection = Entity::UP;
												}
												if (standSpawnDirection() == 1)
												{
													r->movementDirection = Entity::DOWN;
												}
												if (standSpawnDirection() == 2)
												{
													r->movementDirection = Entity::LEFT;
												}
												if (standSpawnDirection() == 3)
												{
													r->movementDirection = Entity::RIGHT;
												}
											}

											if (waitHereTicks() > 0)
											{
												if (randomWaitTime() == true)
												{
													r->ticksToStand = Math::randLessThan(waitHereTicks());
												}
												else
												{
													r->ticksToStand = waitHereTicks();
												}
											}

											targetTYPEIDList->clear();
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Area::renderDebugBoxes()
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();
	sp<Map> map = getMap();

	int r = 0;
	int g = 0;
	int b = 0;

	if ((dynamic_cast<sp<WarpArea>>(this) != NULL))
	{
		r = 200;
		g = 0;
		b = 255;
	} //purple
	else if (randomNPCSpawnPoint())
	{
		r = 255;
		g = 0;
		b = 255;
	} //magenta
	else if (randomPointOfInterestOrExit())
	{
		r = 255;
		g = 255;
		b = 255;
	} //white
	else
	{
		r = 255;
		g = 200;
		b = 0;
	} //orange

	//outline
	GLUtils::drawBox(screenLeft(), screenRight() - 1, screenTop(), screenBottom() - 1, r, g, b); //-1 so the box is inside one pixel

	//warparea arrival point
	if ((dynamic_cast<sp<WarpArea>>(this) != NULL))
	{
		float ax = map->getScreenX((static_cast<sp<WarpArea>>(this))->arrivalXPixelsHQ(), 16);
		float ay = map->getScreenY((static_cast<sp<WarpArea>>(this))->arrivalYPixelsHQ(), 16);

		GLUtils::drawBox(ax, ax + (16 * zoom) - 1, ay, ay + (16 * zoom) - 1, 200, 0, 255);

		GLUtils::drawLine(screenLeft() + (getWidth() / 2) * zoom, screenTop() + (getHeight() / 2) * zoom, ax + (8 * zoom), ay + (8 * zoom), 255, 255, 255);
	}

	for (int i = 0; i < connectionTYPEIDList()->size(); i++)
	{
		//draw connections to doors
		if (OKString::startsWith(connectionTYPEIDList()->get(i), "DOOR."))
		{
			//go through doorlist
			for (int d = 0; d < (int)map->doorList->size(); d++)
			{
				sp<Door> door = map->doorList.get(d);

				if (connectionTYPEIDList()->get(i) == door->getTYPEIDString())
				{
					float dx = door->getScreenLeft() + (door->getWidth() / 2) * zoom;
					float dy = door->getScreenTop() + (door->getHeight()) * zoom;

					GLUtils::drawArrowLine(screenLeft() + (getWidth() / 2) * zoom, screenTop() + (getHeight() / 2) * zoom, dx, dy, 0, 255, 0);
				}
			}
		}
		else
		{
			//draw connections to areas
			//go through area hashlist
			//         java::util::Iterator<sp<Area>> aEnum = map->currentState::areaByNameHashtable::elements();
			//         //areas
			//         while (aEnum->hasMoreElements())
			//         {
			//            sp<Area> area = aEnum->nextElement();
			//            if (getConnectionTYPEIDList()->get(i) == area->getTYPEIDString())
			//            {
			//               float ax = area->getScreenLeft() + (area->getWidth() / 2) * zoom;
			//               float ay = area->getScreenTop() + (area->getHeight() / 2) * zoom;
			//
			//               GLUtils::drawArrowLine(getScreenLeft() + (getWidth() / 2) * zoom, getScreenTop() + (getHeight() / 2) * zoom, ax, ay, 0, 255, 0);
			//            }
			//         }

			sp<vector<sp<Area>>>areas = map->currentState->areaByNameHashtable.getAllValues();
			for (int n = 0; n<areas->size(); n++)
			{
				sp<Area> a = areas->get(n);

				if (connectionTYPEIDList()->get(i) == a->getTYPEIDString())
				{
					float ax = a->screenLeft() + (a->getWidth() / 2) * zoom;
					float ay = a->screenTop() + (a->getHeight() / 2) * zoom;

					GLUtils::drawArrowLine(screenLeft() + (getWidth() / 2) * zoom, screenTop() + (getHeight() / 2) * zoom, ax, ay, 0, 255, 0);
				}
			}

			//if not found, go through warparea list
			for (int j = 0; j < (int)map->warpAreaList->size(); j++)
			{
				sp<Area> area = map->warpAreaList.get(j);

				if (connectionTYPEIDList()->get(i) == area->getTYPEIDString())
				{
					float ax = area->screenLeft() + (area->getWidth() / 2) * zoom;
					float ay = area->screenTop() + (area->getHeight() / 2) * zoom;

					GLUtils::drawArrowLine(screenLeft() + (getWidth() / 2) * zoom, screenTop() + (getHeight() / 2) * zoom, ax, ay, 0, 255, 0);
				}
			}
		}
	}
}

void Area::renderDebugInfo()
{ //=========================================================================================================================

	float x = screenLeft();
	float y = screenTop();

	int strings = -1;

	if ((dynamic_cast<sp<WarpArea>>(this) != nullptr) == false)
	{
		GLUtils::drawOutlinedString(getName(), x, y - 9, OKColor::white);
	}

	//if(isAnAction)GL.drawOutlinedString("Is An Action", x, y+(++strings*9),Color.red);
	if (getEventData() != nullptr)
	{
		GLUtils::drawOutlinedString("Event ID: " + to_string(getEventData()->getID()), x, y + (++strings * 9), OKColor::white);
	}
	if (waitHereTicks() == -1)
	{
		GLUtils::drawOutlinedString("Stop Here", x, y + (++strings * 9), OKColor::yellow);
	}
	if (waitHereTicks() > 0 && randomWaitTime() == false)
	{
		GLUtils::drawOutlinedString("Wait " + to_string(waitHereTicks()), x, y + (++strings * 9), OKColor::yellow);
	}
	if (waitHereTicks() > 0 && randomWaitTime() == true)
	{
		GLUtils::drawOutlinedString("Wait Random < " + to_string(waitHereTicks()), x, y + (++strings * 9), OKColor::yellow);
	}
	if (onlyOneAllowed())
	{
		GLUtils::drawOutlinedString("Only 1", x, y + (++strings * 9), OKColor::green);
	}
	if (standSpawnDirection() != -1)
	{
		if (standSpawnDirection() == 0)
		{
			GLUtils::drawOutlinedString("Dir: Up", x, y + (++strings * 9), OKColor::yellow);
		}
		if (standSpawnDirection() == 1)
		{
			GLUtils::drawOutlinedString("Dir: Down", x, y + (++strings * 9), OKColor::yellow);
		}
		if (standSpawnDirection() == 2)
		{
			GLUtils::drawOutlinedString("Dir: Left", x, y + (++strings * 9), OKColor::yellow);
		}
		if (standSpawnDirection() == 3)
		{
			GLUtils::drawOutlinedString("Dir: Right", x, y + (++strings * 9), OKColor::yellow);
		}
	}

	if (randomPointOfInterestOrExit())
	{
		GLUtils::drawOutlinedString("Random Point Of Interest Or Exit", x, y + (++strings * 9), OKColor::white);
	}

	if (randomNPCSpawnPoint())
	{
		GLUtils::drawOutlinedString("Random Spawn Point | Chance: " + to_string(randomSpawnChance()), x, y + (++strings * 9), OKColor::magenta);
	}

	if (randomNPCSpawnPoint())
	{
		GLUtils::drawOutlinedString("Spawn Delay: " + to_string(randomSpawnDelay()), x, y + (++strings * 9), OKColor::white);
	}

	if (randomNPCSpawnPoint())
	{
		string allowedTypes = "";
		if (randomSpawnKids())
		{
			allowedTypes = allowedTypes + " Kids";
		}
		if (randomSpawnAdults())
		{
			allowedTypes = allowedTypes + " Adults";
		}
		if (randomSpawnMales())
		{
			allowedTypes = allowedTypes + " Males";
		}
		if (randomSpawnFemales())
		{
			allowedTypes = allowedTypes + " Females";
		}
		if (randomSpawnCars())
		{
			allowedTypes = allowedTypes + " Cars";
		}
		GLUtils::drawOutlinedString("Spawn Types: " + allowedTypes, x, y + (++strings * 9), OKColor::magenta);
	}
	if (randomNPCStayHere())
	{
		GLUtils::drawOutlinedString("Random Stay Here", x, y + (++strings * 9), OKColor::white);
	}
	if (randomSpawnOnlyTryOnce())
	{
		GLUtils::drawOutlinedString("Random Only Try Once: " + to_string(randomSpawnChance()), x, y + (++strings * 9), OKColor::white);
	}
	if (randomSpawnOnlyOffscreen())
	{
		GLUtils::drawOutlinedString("Random Only Offscreen", x, y + (++strings * 9), OKColor::white);
	}
}

sp<OKBool> Area::checkServerTalkedToTodayValueAndResetAfterSuccessfulReturn()
{
	// TODO
	return ms<OKBool>();
}

void Area::tellServerTalkedToToday()
{
	// TODO
}

bool Area::isWithinScreenBounds()
{ //=========================================================================================================================

	//float zoom = getCameraman()->getZoom();

	float mapCameraXPixelsHQ = (float)(getMap()->mapCamX());
	float mapCameraYPixelsHQ = (float)(getMap()->mapCamY());

	//*************
	//flooring these fixes all the sprite jitter
	//nope, don't need to do this now, basing all the coords on the offset of the floored mapScreenXY in render, like the map chunk offsets.
	//*************
	float left = (float)(getX());
	float right = (float)(getX() + getWidth());
	float top = (float)(getY()); //we want the actual hitBoxTop() of the sprite, NOT the getHit box
	float bottom = (float)(getY() + getHeight());

	float screenleft = mapCameraXPixelsHQ;
	float screenright = mapCameraXPixelsHQ + getEngine()->getWidthRelativeToZoom(); //actual game rendering is done at 2x so half screen dimensions
	float screentop = mapCameraYPixelsHQ;
	float screenbottom = mapCameraYPixelsHQ + getEngine()->getHeightRelativeToZoom();

	if (right < screenleft || left > screenright || bottom < screentop || top > screenbottom) //so shadow can show even if sprite walks above screen
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Area::inRangeOfEntityByAmount(sp<Entity> e, int amt)
{ //=========================================================================================================================

	float eX = e->getMiddleX();
	float eY = e->getMiddleY();

	if (middleX() + amt >= eX && middleX() - amt <= eX && middleY() + amt >= eY && middleY() - amt <= eY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float Area::getDistanceFromEntity(sp<Entity> e)
{ //=========================================================================================================================

	float eX = e->getMiddleX();
	float eY = e->getMiddleY();

	return Math::distance(middleX(), middleY(), eX, eY);
}

bool Area::isEntityHitBoxTouchingMyBoundary(sp<Entity> e)
{ //=========================================================================================================================
	return isEntityHitBoxTouchingMyBoundaryByAmount(e, 0);
}

bool Area::isAreaCenterTouchingMyBoundary(sp<Area> a)
{ //=========================================================================================================================
	return isAreaCenterTouchingMyBoundaryByAmount(a, 0);
}

bool Area::isAreaBoundaryTouchingMyBoundary(sp<Area> a)
{ //=========================================================================================================================
	return isAreaBoundaryTouchingMyBoundaryByAmount(a, 0);
}

bool Area::isXYTouchingMyBoundary(float x, float y)
{ //=========================================================================================================================
	return isXYTouchingMyBoundaryByAmount(x, y, 0);
}

bool Area::isXYXYTouchingMyBoundary(float left, float top, float right, float bottom)
{ //=========================================================================================================================
	return isXYXYTouchingMyBoundaryByAmount(left, top, right, bottom, 0);
}

bool Area::isAreaBoundaryTouchingMyCenter(sp<Area> a)
{ //=========================================================================================================================
	return isAreaBoundaryTouchingMyCenterByAmount(a, 0);
}

bool Area::isEntityMiddleXYTouchingMyCenter(sp<Entity> e)
{ //=========================================================================================================================
	return isEntityMiddleXYTouchingMyCenterByAmount(e, 1);
}

bool Area::isAreaCenterTouchingMyCenter(sp<Area> a)
{ //=========================================================================================================================
	return isAreaCenterTouchingMyCenterByAmount(a, 0);
}

bool Area::isXYTouchingMyCenter(float x, float y)
{ //=========================================================================================================================
	return isXYTouchingMyCenterByAmount(x, y, 0);
}

bool Area::isXYXYTouchingMyCenter(float left, float top, float right, float bottom)
{ //=========================================================================================================================
	return isXYXYTouchingMyCenterByAmount(left, top, right, bottom, 0);
}

bool Area::isEntityHitBoxTouchingMyBoundaryByAmount(sp<Entity> e, int amt)
{ //=========================================================================================================================
	return Math::isXYXYTouchingXYXYByAmount(getLeft(), getTop(), getRight(), getBottom(), e->getLeft(), e->getTop(), e->getRight(), e->getBottom(), amt);
}

bool Area::isAreaCenterTouchingMyBoundaryByAmount(sp<Area> a, int amt)
{ //=========================================================================================================================
	return isXYTouchingMyBoundaryByAmount(a->middleX(), a->middleY(), amt);
}

bool Area::isAreaBoundaryTouchingMyBoundaryByAmount(sp<Area> a, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingMyBoundaryByAmount(a->getLeft(), a->getTop(), a->getRight(), a->getBottom(), amt);
}

bool Area::isXYTouchingMyBoundaryByAmount(float x, float y, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingMyBoundaryByAmount(x, y, x, y, amt);
}

bool Area::isXYXYTouchingMyBoundaryByAmount(float left, float top, float right, float bottom, int amt)
{ //=========================================================================================================================
	return Math::isXYXYTouchingXYXYByAmount(getLeft(), getTop(), getRight(), getBottom(), left, top, right, bottom, amt);
}

bool Area::isAreaBoundaryTouchingMyCenterByAmount(sp<Area> a, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingMyCenterByAmount(a->getLeft(), a->getTop(), a->getRight(), a->getBottom(), amt);
}

bool Area::isEntityMiddleXYTouchingMyCenterByAmount(sp<Entity> e, int amt)
{ //=========================================================================================================================
	return isXYTouchingMyCenterByAmount(e->getMiddleX(), e->getMiddleY(), amt);
}

bool Area::isAreaCenterTouchingMyCenterByAmount(sp<Area> a, int amt)
{ //=========================================================================================================================
	return isXYTouchingMyCenterByAmount(a->middleX(), a->middleY(), amt);
}

bool Area::isXYTouchingMyCenterByAmount(float x, float y, int amt)
{ //=========================================================================================================================
	return isXYXYTouchingMyCenterByAmount(x, y, x, y, amt);
}

bool Area::isXYXYTouchingMyCenterByAmount(float left, float top, float right, float bottom, int amt)
{ //=========================================================================================================================
	return Math::isXYXYTouchingXYXYByAmount(middleX(), middleY(), middleX(), middleY(), left, top, right, bottom, amt);
}

float Area::getTop()
{ //=========================================================================================================================
	return (getY());
}

float Area::getLeft()
{ //=========================================================================================================================
	return (getX());
}

float Area::getRight()
{ //=========================================================================================================================
	return (getX() + getWidth());
}

float Area::getBottom()
{ //=========================================================================================================================
	return (getY() + getHeight());
}

float Area::middleX()
{ //=========================================================================================================================
	return (getX() + (getWidth() / 2));
}

float Area::middleY()
{ //=========================================================================================================================
	return (getY() + getHeight() / 2);
}

float Area::roundedMiddleX()
{
	return round(middleX());
}

float Area::roundedMiddleY()
{
	return round(middleY());
}

float Area::screenX()
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	float mapCameraXPixelsHQ = getMap()->mapCamX();

	//flooring these fixes the jitter for lights
	float left = (float)(floor(getX()));
	float right = (float)(floor(getX() + getWidth()));

	float screenleft = mapCameraXPixelsHQ;
	float screenright = mapCameraXPixelsHQ + getEngine()->getWidthRelativeToZoom();

	float screenXPixelsHQ = (left - screenleft);

	//if overlapping left side of screen
	if (right >= screenleft && left < screenleft)
	{
		screenXPixelsHQ = (0.0f - (screenleft - left));
	}

	//if onscreen and not overlapping the left side
	if (left >= screenleft && left < screenright)
	{
		screenXPixelsHQ = (left - screenleft);
	}

	return screenXsp<PixelsHQ> zoom;
}

float Area::screenY()
{ //=========================================================================================================================

	float zoom = getCameraman()->getZoom();

	float mapCameraYPixelsHQ = getMap()->mapCamY();

	//flooring these fixes the jitter for lights
	float top = (float)(floor(getY()));
	float bottom = (float)(floor(getY() + getHeight()));

	float screentop = mapCameraYPixelsHQ;
	float screenbottom = mapCameraYPixelsHQ + getEngine()->getHeightRelativeToZoom();

	float screenYPixelsHQ = top - screentop;

	//if overlapping top side of screen
	if (bottom >= screentop && top < screentop)
	{
		screenYPixelsHQ = 0.0f - (screentop - top);
	}

	//if onscreen and not overlapping the top side
	if (top >= screentop && top < screenbottom)
	{
		screenYPixelsHQ = top - screentop;
	}

	return screenYsp<PixelsHQ> zoom;
}

float Area::screenLeft()
{ //=========================================================================================================================
	return screenX();
}

float Area::screenRight()
{ //=========================================================================================================================

	return screenX() + (float)(getWidth()) * getCameraman()->getZoom();
}

float Area::screenTop()
{ //=========================================================================================================================
	return screenY();
}

float Area::screenBottom()
{ //=========================================================================================================================
	return screenY() + (float)(getHeight()) * getCameraman()->getZoom();
}

sp<AreaData> Area::getData()
{
	return data;
}

float Area::getX()
{
	return mapX;
}

float Area::getY()
{
	return mapY;
}

int Area::getWidth()
{
	return getData()->getWidthPixelsHQ();
}

int Area::getHeight()
{
	return getData()->getHeightPixelsHQ();
}

string& Area::getName()
{
	return getData()->getName();
}

string& Area::getComment()
{
	return getData()->getComment();
}

int Area::getID()
{
	return getData()->getID();
}

//int Area::mapID()
//{
//	return getData()->getMapID();
//}

float Area::arrivalXPixelsHQ()
{
	return getData()->getArrivalXPixelsHQ();
}

float Area::arrivalYPixelsHQ()
{
	return getData()->getArrivalYPixelsHQ();
}

bool Area::isWarpArea()
{
	return getData()->getIsWarpArea();
}

bool Area::randomPointOfInterestOrExit()
{
	return getData()->getRandomPointOfInterestOrExit();
}

bool Area::randomNPCSpawnPoint()
{
	return getData()->getRandomNPCSpawnPoint();
}

int Area::standSpawnDirection()
{
	return getData()->getStandSpawnDirection();
}

int Area::waitHereTicks()
{
	return getData()->getWaitHereTicks();
}

bool Area::randomWaitTime()
{
	return getData()->getRandomWaitTime();
}

bool Area::onlyOneAllowed()
{
	return getData()->getOnlyOneAllowed();
}

bool Area::randomNPCStayHere()
{
	return getData()->getRandomNPCStayHere();
}

float Area::randomSpawnChance()
{
	return getData()->getRandomSpawnChance();
}

bool Area::randomSpawnOnlyTryOnce()
{
	return getData()->getRandomSpawnOnlyTryOnce();
}

bool Area::randomSpawnOnlyOffscreen()
{
	return getData()->getRandomSpawnOnlyOffscreen();
}

int Area::randomSpawnDelay()
{
	return getData()->getRandomSpawnDelay();
}

bool Area::randomSpawnKids()
{
	return getData()->getRandomSpawnKids();
}

bool Area::randomSpawnAdults()
{
	return getData()->getRandomSpawnAdults();
}

bool Area::randomSpawnMales()
{
	return getData()->getRandomSpawnMales();
}

bool Area::randomSpawnFemales()
{
	return getData()->getRandomSpawnFemales();
}

bool Area::randomSpawnCars()
{
	return getData()->getRandomSpawnCars();
}

bool Area::autoPilot()
{
	return getData()->getAutoPilot();
}

bool Area::playerFaceDirection()
{
	return getData()->getPlayerFaceDirection();
}

bool Area::suckPlayerIntoMiddle()
{
	return getData()->getSuckPlayerIntoMiddle();
}

sp<EventData> Area::getEventData()
{
	return getData()->getEventData();
}

sp<vector<string>> Area::connectionTYPEIDList()
{
	return getData()->getConnectionTYPEIDList();
}

string Area::getTYPEIDString()
{
	return getData()->getTYPEIDString();
}

string& Area::destinationTYPEIDString()
{
	if (getData()->getDestinationTYPEIDString() == "" || getData()->getDestinationTYPEIDString().length() == 0)
	{
		getData()->setDestinationTYPEIDString(getTYPEIDString());
	}
	return getData()->getDestinationTYPEIDString();
}

