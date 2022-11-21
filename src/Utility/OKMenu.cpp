
#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------



sp<OKTexture> OKMenu::rectangleCursorTexture = nullptr;
sp<OKTexture> OKMenu::cursorTexture = nullptr;
sp<OKTexture> OKMenu::upCursorTexture = nullptr;
sp<OKTexture> OKMenu::downCursorTexture = nullptr;
long long OKMenu::cursorInOutToggleTicks = 0;
bool OKMenu::cursorInOutToggle = false;
int OKMenu::lastMX = 0;
int OKMenu::lastMY = 0;

sp<OKColor> OKMenu::menuColor = nullptr;
sp<OKColor> OKMenu::disabledMenuColor = nullptr;
sp<OKColor> OKMenu::warningMenuColor = nullptr;
sp<OKColor> OKMenu::clearColor = nullptr;
sp<OKColor> OKMenu::infoColor = nullptr;
sp<OKColor> OKMenu::statusColor = nullptr;
sp<OKColor> OKMenu::errorColor = nullptr;
sp<OKColor> OKMenu::bgColor = nullptr;

sp<vector<sp<OKMenu>>> OKMenu::activeMenus;


//=========================================================================================================================
OKMenu::MenuItem::~MenuItem()
{//=========================================================================================================================
	if (caption != nullptr)
	{
		//caption->setToBeDeletedImmediately();
		//delete caption;
		caption = nullptr;
	}
	

	//if (subMenu != nullptr)delete subMenu;
}

//=========================================================================================================================
void OKMenu::MenuItem::setYesNo(bool yesNo)
{//=========================================================================================================================
	yesNoValue = yesNo;
	if (isYesNoType)
	{
		//string value = "";
		//if (yesNo)value = "Yes";
		//else value = "   ";
		//if (caption != nullptr)caption->replaceText("(" + value + ") " + captionText);
		if (yesNo == false) 
		{
			setColor(disabledMenuColor, true);
		}
		else 
		{
			setColor(menuColor,true);
		}
		
	}
}

//=========================================================================================================================
void OKMenu::MenuItem::toggle()
{//=========================================================================================================================
	setYesNo(!yesNoValue);
}

//=========================================================================================================================
void OKMenu::MenuItem::setColor(sp<OKColor> color, bool outline)
{//=========================================================================================================================

	if (color == disabledMenuColor || color == infoColor)caption->outline = false;
	else caption->outline = outline;

	caption->setTextColor(color);
	this->color = color;

}

//=========================================================================================================================
void OKMenu::MenuItem::setText(string s)
{//=========================================================================================================================
	caption->setText(s);
}

//sp<OKSubMenu> OKMenu::addSubMenu(string caption, string id, sp<OKGame>b, void(*f) (sp<OKGame>, string))
//{
//	sp<MenuItem>m = ms<MenuItem>();
//	m->caption = getCaptionManager()->newManagedCaption(Caption::CENTERED_X, 0, -1, caption, font, menuColor, OKColor::clear, RenderOrder::OVER_GUI);
//	m->subMenu = ms<OKSubMenu>(e);
//	m->subMenu->parentMenu = this;
//	m->subMenu->bobsGame = b;
//	m->subMenu->callBack = f;
//
//	if (id == "")id = caption;
//	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
//	m->id = id;
//	menuItems.add(m);
//
//	return m->subMenu;
//}

//=========================================================================================================================
OKMenu::OKMenu(sp<Engine>g, string title, string subtitle)
{//=========================================================================================================================
	this->e = g;
	if (rectangleCursorTexture == nullptr)rectangleCursorTexture = GLUtils::getTextureFromPNGExePath("data/textbox/rectangleCursor.png");
	if (cursorTexture == nullptr)cursorTexture = GLUtils::getTextureFromPNGExePath("data/textbox/outlinedCursor.png");
	if (upCursorTexture == nullptr)upCursorTexture = GLUtils::getTextureFromPNGExePath("data/textbox/upCursor.png");
	if (downCursorTexture == nullptr)downCursorTexture = GLUtils::getTextureFromPNGExePath("data/textbox/downCursor.png");

	cursorInOutToggleTicks = 0;
	cursorInOutToggle = false;

	if (menuColor == nullptr)menuColor = OKColor::lighterGray;
	if (disabledMenuColor == nullptr)disabledMenuColor = OKColor::lightGray;
	if (warningMenuColor == nullptr)warningMenuColor = OKColor::lightRed;
	if (clearColor == nullptr)clearColor = OKColor::clear;
	if (infoColor == nullptr)infoColor = OKColor::gray;
	if (statusColor == nullptr)statusColor = OKColor::lightGreen;
	if (errorColor == nullptr)errorColor = OKColor::lightRed;
	if (bgColor == nullptr)bgColor = OKColor::white;

	if (defaultMenuColor == nullptr)defaultMenuColor = menuColor;

	if (title != "")
	{
		titleCaption = ms<Caption>(e, Caption::Position::CENTERED_X, 0, 0, -1, title, 32, true, menuColor, RenderOrder::OVER_GUI);
	}

	if(subtitle !="")
	{
		subtitleCaption = ms<Caption>(e, Caption::Position::NONE, 0, 0, -1, subtitle, 22, false, infoColor, RenderOrder::OVER_GUI);
	}

	activeMenus->push_back(shared_from_this());
}
//=========================================================================================================================
OKMenu::~OKMenu()
{//=========================================================================================================================
	if (titleCaption != nullptr)
	{
		//delete titleCaption;// titleCaption->setToBeDeletedImmediately();
		titleCaption = nullptr;
	}
	if (subtitleCaption != nullptr)
	{
		//delete subtitleCaption;// titleCaption->setToBeDeletedImmediately();
		subtitleCaption = nullptr;
	}
	menuItems->clear();
	
	activeMenus->remove(this);
}

//int graphicWidth = 0;
//int graphicYStartPosition = 0;
//=========================================================================================================================
void OKMenu::setGraphic(sp<OKTexture> t, int graphicWidth, int graphicYStartPosition, int maxGraphicHeight, int filter)
{//=========================================================================================================================
	this->graphic = t;
	this->graphicWidth = graphicWidth;
	this->graphicYStartPosition = graphicYStartPosition;
	this->maxGraphicHeight = maxGraphicHeight;
	this->filter = filter;
}

//=========================================================================================================================
void OKMenu::clear()
{//=========================================================================================================================
	menuItems->clear();
	topMenuItemDrawn = nullptr;
}

//=========================================================================================================================
void OKMenu::setAllCaptionsToFullAlpha()
{//=========================================================================================================================
	for (int i = 0; i < menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if(m->caption!=nullptr)m->caption->setAlphaImmediately(1.0f);
	}
}

//=========================================================================================================================
void OKMenu::update(sp<Engine>g, int ticksPassed)
{//=========================================================================================================================
	cursorInOutToggleTicks += ticksPassed;
	if (cursorInOutToggleTicks > 300)
	{
		cursorInOutToggleTicks = 0;
		cursorInOutToggle = !cursorInOutToggle;
	}

	int mx = g->getControlsManager()->getMouseX();
	int my = g->getControlsManager()->getMouseY();
	bool checkMouse = false;
	if(mx!=lastMX || my!=lastMY)
	{
		checkMouse = true;
		lastMX = mx;
		lastMY = my;
	}

	for(int i = 0; i < (int)activeMenus->size(); i++)
	{
		sp<OKMenu>m = activeMenus->at(i);

		for(int n = 0; n < (int)m->menuItems->size(); n++)
		{
			sp<MenuItem>mi = m->menuItems->at(n);

			if (mi->info)continue;
			if (mi->hidden)continue;


			sp<Caption>c = mi->caption;
			if (c->visible == false)continue;

			int x0 = c->screenX + (c->getWidth() * 0.05);
			int x1 = c->screenX + c->getWidth() - (c->getWidth() * 0.05);
			int y0 = c->screenY + (c->getHeight() * 0.05);
			int y1 = c->screenY + c->getHeight() - (c->getHeight() * 0.05);

			if (checkMouse)
			{
				if (x0 < mx && x1 > mx && y0 < my && y1 > my)
				{
					m->cursorPosition = n;
				}
			}
		}
	}

}

//=========================================================================================================================
bool OKMenu::areAllMenusDisabled()
{//=========================================================================================================================
	bool allDisabled = true;
	for (int i = 0; i < (int)menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->hidden == false && m->info == false)
		{
			allDisabled = false;
		}
	}
	if (allDisabled)return true;
	return false;
}

//=========================================================================================================================
void OKMenu::up(bool noSound)
{//=========================================================================================================================
	if (areAllMenusDisabled())return;
	do
	{
		cursorPosition--;
		if (cursorPosition < 0)cursorPosition = (int)menuItems->size() - 1;
	} while (getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true);
	rectangleCursorMovementLastTime = System::currentHighResTimer();
	if(noSound==false)getAudioManager()->playSound("tick", 0.5f, 1.0f);

}

//=========================================================================================================================
void OKMenu::down(bool noSound)
{//=========================================================================================================================
	if (areAllMenusDisabled())return;
	do
	{
		cursorPosition++;
		if (cursorPosition > (int)menuItems->size() - 1)cursorPosition = 0;
	} while (getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true);
	rectangleCursorMovementLastTime = System::currentHighResTimer();
	if (noSound == false)getAudioManager()->playSound("tick", 0.5f, 1.0f);
}

//=========================================================================================================================
sp<OKMenu::MenuItem> OKMenu::addInfo(string caption, string id, sp<OKColor>color)
{//=========================================================================================================================

	if (color == nullptr)color = infoColor;

	

	sp<MenuItem>m = ms<MenuItem>();

	//outline = false;
	m->outline = false;

	m->caption = ms<Caption>(e, Caption::Position::CENTERED_X, 0, 0, -1, caption, fontSize, m->outline, color, RenderOrder::OVER_GUI);
	m->captionText = caption;
	m->color = color;
	m->id = id;
	m->hidden = false;
	m->info = true;
	
	
	if (id == "")id = caption;
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	m->id = id;
	menuItems->push_back(m);
	return m;
}

//=========================================================================================================================
sp<OKMenu::MenuItem> OKMenu::add(string caption, string id, sp<OKColor>color)
{//=========================================================================================================================

	if (color == nullptr)color = defaultMenuColor;

	sp<MenuItem>m = ms<MenuItem>();
	m->outline = outline;
	m->caption = ms<Caption>(e, Caption::Position::CENTERED_X, 0, 0, -1, caption, fontSize, m->outline, color, RenderOrder::OVER_GUI);
	m->captionText = caption;
	m->color = color;
	if (id == "")id = caption;
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	m->id = id;
	menuItems->push_back(m);
	return m;
}

//=========================================================================================================================
sp<OKMenu::MenuItem> OKMenu::addYesNo(string caption, bool yesNo)
{//=========================================================================================================================
	//string value = "";
	//if (yesNo==false)value = " - (No)";
	//else value = "   ";
	//sp<MenuItem>m = add(caption + value, caption);
	sp<MenuItem>m = add(caption, caption);
	m->captionText = caption;
	
	m->isYesNoType = true;
	m->yesNoValue = yesNo;
	if (yesNo == false)m->setColor(disabledMenuColor,m->outline);
	else m->setColor(menuColor, m->outline);
	return m;
}

//=========================================================================================================================
void OKMenu::setHidden(string id, bool b)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	for (int i = 0; i<menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->id == id)
		{
			m->hidden = b;
		}
	}
}

//=========================================================================================================================
void OKMenu::setAllInvisible()
{//=========================================================================================================================
	for (int i = 0; i < menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->caption != nullptr)m->caption->visible = false;
	}
}

//=========================================================================================================================
void OKMenu::setAllVisible()
{//=========================================================================================================================
	for (int i = 0; i < menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->caption != nullptr)m->caption->visible = true;
	}
}

//=========================================================================================================================
bool OKMenu::isSelectedID(string id, bool clicked, int mx, int my)
{//=========================================================================================================================

	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	if(clicked)
	{
		for(int i=0;i<menuItems->size();i++)
		{
			sp<MenuItem>m = menuItems->at(i);
			if (m->id != id)continue;

			sp<Caption>c = m->caption;
			if (c->visible == false)continue;

			int x0 = c->screenX + (c->getWidth()*0.01);
			int x1 = c->screenX + c->getWidth() - (c->getWidth()*0.01);
			int y0 = c->screenY + (c->getHeight()*0.01);
			int y1 = c->screenY + c->getHeight() - (c->getHeight()*0.01);

			if(x0 < mx && x1 > mx && y0 < my && y1 > my)
			{
				cursorPosition = i;
				getAudioManager()->playSound("touchblock", 0.5f, 1.0f);
				return true;
			}
		}
		return false;
	}
	else
	{
		if(menuItems->at(cursorPosition)->id == id)
		{
			//getAudioManager()->playSound("touchblock", 0.5f,1.0f);
			return true;
		}
		else return false;
	}

	
}

//=========================================================================================================================
void OKMenu::setSelectedID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);
	for (int i = 0; i < menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->id == id)
		{
			cursorPosition = i;
		}
	}
}
//=========================================================================================================================
sp<Caption> OKMenu::getCaptionByID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	for (int i = 0; i<menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->id == id)
		{
			return m->caption;
		}
	}
	return nullptr;
}

//=========================================================================================================================
sp<OKMenu::MenuItem> OKMenu::getMenuItemByID(string id)
{//=========================================================================================================================
	std::transform(id.begin(), id.end(), id.begin(), ::tolower);

	for (int i = 0; i<menuItems->size(); i++)
	{
		sp<MenuItem>m = menuItems->at(i);
		if (m->id == id)
		{
			return m;
		}
	}
	return nullptr;
}

//=========================================================================================================================
sp<OKMenu::MenuItem> OKMenu::getSelectedMenuItem()
{//=========================================================================================================================
	if (cursorPosition >= menuItems->size())return nullptr;
	return menuItems->at(cursorPosition);
}


//=========================================================================================================================
void OKMenu::setFontSize(int size)
{//=========================================================================================================================

//	switch (size)
//	{
//		case 6: font = OKFont::ttf_6;break;
//		case 7: 	font = OKFont::ttf_7;	 break;
//		case 8: 	font = OKFont::ttf_8;	 break;
//		case 9: 	font = OKFont::ttf_9;	 break;
//		case 10: 	font = OKFont::ttf_10;	 break;
//		case 11: 	font = OKFont::ttf_11;	 break;
//		case 12: 	font = OKFont::ttf_12;	 break;
//		case 13: 	font = OKFont::ttf_13;	 break;
//		case 14: 	font = OKFont::ttf_14;	 break;
//		case 15: 	font = OKFont::ttf_15;	 break;
//		case 16: 	font = OKFont::ttf_16;	 break;
//		case 17: 	font = OKFont::ttf_17;	 break;
//		case 18: 	font = OKFont::ttf_18;	 break;
//		case 19: 	font = OKFont::ttf_19;	 break;
//		case 20: 	font = OKFont::ttf_20;	 break;
//		case 21: 	font = OKFont::ttf_21;	 break;
//		case 22: 	font = OKFont::ttf_22;	 break;
//		case 23: 	font = OKFont::ttf_23;	 break;
//		case 24: 	font = OKFont::ttf_24;	 break;
//		case 25: 	font = OKFont::ttf_25;	 break;
//		case 26: 	font = OKFont::ttf_26;	 break;
//		case 27: 	font = OKFont::ttf_27;	 break;
//		case 28: 	font = OKFont::ttf_28;	 break;
//		case 29: 	font = OKFont::ttf_29;	 break;
//		case 30: 	font = OKFont::ttf_30;	 break;
//		case 31: 	font = OKFont::ttf_31;	 break;
//		case 32: 	font = OKFont::ttf_32;	 break;
//		case 48: 	font = OKFont::ttf_48;	 break;
//		case 64: 	font = OKFont::ttf_64;	 break;
//	}

	fontSize = size;

}


int OKMenu::getAmountOfMenuItems()
{
	return (int)menuItems->size();
}

sp<vector<string>> OKMenu::getArrayListOfMenuItemIDs()
{
	sp<vector<string>>ids;

	for(int i=0;i<(int)menuItems->size();i++)
	{
		ids->push_back(menuItems->at(i)->id);
	}

	return ids;
}




//=========================================================================================================================
//returns bottom of graphic y position
void OKMenu::render
(
	int y, 
	int x, 
	int endY, 
	bool drawCursor, 
	int* returnBottomOfGraphic, 
	int* returnBottomOfCaptions, 
	bool renderBackgroundAndBorder, 
	int* returnLeftX, 
	int* returnRightX
	

)
{//=========================================================================================================================

	if (y == 0 && titleCaption != nullptr)y = titleCaption->getHeight() + 8;

	float leftX = (float)GLUtils::getViewportWidth();
	float rightX = 0;
	float topY = 0;
	float bottomY = 0;

	if (graphic != nullptr)
	{
		float tx0 = 0;
		float tx1 = (float)(graphic->getImageWidth()) / (float)(graphic->getTextureWidth());
		float ty0 = 0;
		float ty1 = (float)((float)(graphic->getImageHeight()) / (float)(graphic->getTextureHeight()))-0.01;

		

		float screenWidth = graphicWidth;
		if(graphicWidth==0)
		{
			screenWidth = graphic->getImageWidth();
		}
		float ratio = (float)(graphicWidth) / (float)(graphic->getImageWidth());

		float screenHeight = graphic->getImageHeight() * ratio;

		if(maxGraphicHeight > 0 && screenHeight > maxGraphicHeight)
		{
			screenHeight = maxGraphicHeight;
			float widthToHeightRatio = (float)(screenHeight) / (float)(graphic->getImageHeight());
			screenWidth = graphic->getImageWidth() * widthToHeightRatio;
		}

		float sx0 = (float)((int)((getEngine()->getWidth() - screenWidth) / 2));
		float sx1 = (float)floor((int)(sx0 + screenWidth));

		float sy0 = (float)graphicYStartPosition;
		float sy1 = (float)floor((int)(sy0 + (float)(screenHeight)));

		y = (int)(sy1 + 40);

		GLUtils::drawTexture(graphic, tx0, tx1, ty0, ty1, sx0, sx1, sy0, sy1, 1.0f, filter);
	}

	if (returnBottomOfGraphic != nullptr)*returnBottomOfGraphic = y;

	topY = (float)y;

	if (subtitleCaption != nullptr)
	{
		if (x != 0)
		{
			subtitleCaption->fixedPosition = Caption::Position::NONE;
			if (center)subtitleCaption->screenX = (float)(x - subtitleCaption->getWidth() / 2);
			else subtitleCaption->screenX = (float)(x);
		}
		else
		{
			if (center == false)
			{
				subtitleCaption->fixedPosition = Caption::Position::NONE;
				subtitleCaption->screenX = (float)(x);
			}
		}

		if (subtitleCaption->screenX < leftX)leftX = subtitleCaption->screenX;
		if (subtitleCaption->screenX + subtitleCaption->getWidth() > rightX)rightX = subtitleCaption->screenX + subtitleCaption->getWidth();

		subtitleCaption->screenY = y;
		y += (subtitleCaption->getHeight() + 8);

	}

	if (menuItems->size() == 0)return;

	//if selected disabled, move down
	if (areAllMenusDisabled()==false && (getSelectedMenuItem() == nullptr || getSelectedMenuItem()->hidden == true || getSelectedMenuItem()->info == true))down(true);

	int bottomOfCaptions = 0;

	sp<vector<sp<MenuItem>>>visibleMenuItems;

	
	{

		//populate visibleMenuItems
		for (int i = 0; i < menuItems->size(); i++)
		{
			sp<MenuItem>m = menuItems->at(i);
			sp<Caption>c = m->caption;

			if (c != nullptr)
			{
				if (m->hidden)
				{
					c->visible = false;
					continue;
				}
				else
				{
					visibleMenuItems->push_back(m);
				}
			}
		}


		int menuItemsToShow = 0;
		
		int minSize = 6;
		int tries = 0;
		bool stillIncreasingSize = false;
		do
		{

			menuItemsToShow = (int)visibleMenuItems->size();

			int lowestHeight = y;
			bool pastEnd = false;

			int captionHeight = 0;

			for (int i = 0; i < (int)visibleMenuItems->size(); i++)
			{
				sp<MenuItem>m = visibleMenuItems->at(i);
				sp<Caption>c = m->caption;

				if (c != nullptr)
				{
					captionHeight = (int)(c->getHeight()*spacing);

					lowestHeight += (int)(c->getHeight()*spacing);

					//if we are past endY already
					if (lowestHeight >= endY && pastEnd == false)
					{
						pastEnd = true;

						//leave room for arrows
						menuItemsToShow = i - 3;

						//always show at least one menu item
						if (menuItemsToShow <= 0) { menuItemsToShow = 1; y = endY - (c->getHeight() + 20); }
						
					}
					
				}
			}

			

						
			if(
				scaleFontSizeToFit && 
				menuItemsToShow < visibleMenuItems->size()
			)
			{
				//decrease the font size for all menu items
				for (int i = 0; i < menuItems->size(); i++)
				{
					sp<MenuItem>m = menuItems->at(i);
					sp<Caption>c = m->caption;
					scaledFontSize = c->reduceHeightByOne();

					topMenuItemDrawn = nullptr;
				}
			}

			stillIncreasingSize = false;

			if(
				scaleFontSizeToFit && 
				menuItemsToShow == visibleMenuItems->size() && 
				scaledFontSize < fontSize && 
				pastEnd == false && 
				endY - lowestHeight >= captionHeight*2
			)
			{
				//increase the font size for all menu items only up to the default size
				for (int i = 0; i < menuItems->size(); i++)
				{
					sp<MenuItem>m = menuItems->at(i);
					sp<Caption>c = m->caption;
					scaledFontSize = c->increaseHeightByOne();

					topMenuItemDrawn = nullptr;
					stillIncreasingSize = true;
				}
			}

			tries++;

			//we want to decrease the font size until the menu fits between startY and endY
		} while 
		(
			scaleFontSizeToFit
			&&
			(
				(menuItemsToShow < visibleMenuItems->size() && scaledFontSize > minSize)
				||
				(menuItemsToShow == visibleMenuItems->size() && stillIncreasingSize)
			)
			
			&& tries < 20
		);




		//set them all invisible so i can only enable the ones to fit on the screen
		for (int i = 0; i < visibleMenuItems->size(); i++)
		{
			sp<MenuItem>m = visibleMenuItems->at(i);
			sp<Caption>c = m->caption;

			if (c != nullptr)
			{
				c->visible = false;
			}
		}

		
		sp<MenuItem> selectedMenuItem = getSelectedMenuItem();

		int numVisibleMenuItemsBeforeCursor = visibleMenuItems->size();
		if (selectedMenuItem != nullptr)
		{
			//figure out visible menu items before cursor
			for (int i = 0; i < visibleMenuItems->size(); i++)
			{
				if (visibleMenuItems->at(i) == selectedMenuItem)
				{
					numVisibleMenuItemsBeforeCursor = i;
				}
			}
		}

		int numDrawn = 0;
		float firstCaptionX = 0;

		bool drawUpArrow = false;
		float upArrowY = 0;
		bool drawDownArrow = false;
		float downArrowY = 0;

		int topVisibleMenuItemIndex = 0;


		//get index of last menu item drawn
		if (topMenuItemDrawn != nullptr)
		{
			bool found = false;
			for (int i = 0; i < visibleMenuItems->size(); i++)
			{
				if (topMenuItemDrawn == visibleMenuItems->at(i))
				{
					found = true;
					topVisibleMenuItemIndex = i;
					break;
				}
			}
			if (found == false)topMenuItemDrawn = nullptr;
		}

		

		int selectedVisibleMenuItemIndex = 0;
		for (int i = 0; i < (int)visibleMenuItems->size(); i++)
		{
			if (menuItems->at(cursorPosition) == visibleMenuItems->at(i))
			{
				selectedVisibleMenuItemIndex = i;
				break;
			}
		}
		if (selectedVisibleMenuItemIndex < topVisibleMenuItemIndex)topVisibleMenuItemIndex = selectedVisibleMenuItemIndex;
		if (selectedVisibleMenuItemIndex >= topVisibleMenuItemIndex + menuItemsToShow)topVisibleMenuItemIndex = selectedVisibleMenuItemIndex - menuItemsToShow;
		if (topVisibleMenuItemIndex < 0)topVisibleMenuItemIndex = 0;

		



		for (int i = 0; i < (int)visibleMenuItems->size() && numDrawn <= menuItemsToShow; i++)
		{

			//figure out first caption to show
			//scroll down until the rest of the menus show on the screen
			if (numDrawn == 0)
			{
				if (topMenuItemDrawn != nullptr)
				{
					//if selected menu item is top visible menu item and topMenuItemIndex > 0, topMenuItemIndex--(scroll menu up)
					if (selectedVisibleMenuItemIndex == topVisibleMenuItemIndex && topVisibleMenuItemIndex > 0)topVisibleMenuItemIndex--;

					//if selected menu item is topMenuItemIndex+menuItemsToShow and topMenuItemIndex+menuItemsToShow < visibleMenuItems, topMenuItemIndex++(scroll menu down)
					int bottomIndex = topVisibleMenuItemIndex + menuItemsToShow;
					if (bottomIndex >= (int)visibleMenuItems->size())bottomIndex = (int)visibleMenuItems->size()-1;
					if (selectedVisibleMenuItemIndex == bottomIndex && bottomIndex < (int)visibleMenuItems->size() - 1)topVisibleMenuItemIndex++;
				}
				//set topMenuItemDrawn to top menu item
				topMenuItemDrawn = visibleMenuItems->at(topVisibleMenuItemIndex);

				if (topVisibleMenuItemIndex > 0 && menuItemsToShow < (int)visibleMenuItems->size())
				{
					//if cursor > menuItemsToShow / 2, draw up arrow, start on cursor position - menuItemsToShow/2 - 1
					//draw up arrow
					drawUpArrow = true;
					upArrowY = (float)(y - 16);
				}

				//jump i to topMenuItemIndex
				i = topVisibleMenuItemIndex;
			}
			if (i < 0)i = 0;

			sp<MenuItem>m = visibleMenuItems->at(i);
			sp<Caption>c = m->caption;

			if (c != nullptr)
			{
				c->updateScreenXY();

				if (numDrawn == 0)
				{
					firstCaptionX = c->screenX;
				}
				

				c->visible = true;

				c->screenY = (float)(y + numDrawn * c->getHeight()*spacing);
				bottomOfCaptions = (int)(y + (numDrawn + 1) * c->getHeight()*spacing);

				if (x != 0)
				{
					c->fixedPosition = Caption::Position::NONE;
					if (center)c->screenX = (float)(x - c->getWidth() / 2);
					else c->screenX = (float)(x);
				}
				else
				{
					if (center == false)
					{
						c->fixedPosition = Caption::Position::NONE;
						c->screenX = (float)(firstCaptionX);
					}
				}

				if (c->screenX < leftX)leftX = c->screenX;
				if (c->screenX + c->getWidth() > rightX)rightX = c->screenX + c->getWidth();

				numDrawn++;
			}
		}
		if (topVisibleMenuItemIndex + menuItemsToShow < visibleMenuItems->size()-1)
		{
			drawDownArrow = true;
			downArrowY = (float)bottomOfCaptions;
			bottomOfCaptions += 16;
		}

		if (returnBottomOfCaptions != nullptr)*returnBottomOfCaptions = bottomOfCaptions;

		bottomY = (float)bottomOfCaptions;

		lastHeight = (bottomY + 15) - (topY - 15);

		if (returnLeftX != nullptr)*returnLeftX = leftX - 25;
		if (returnRightX != nullptr)*returnRightX = rightX + 25;
		lastWidth = (rightX + 25) - (leftX - 25);

		if (renderBackgroundAndBorder)
		{
			GLUtils::drawFilledRect(0, 0, 0, leftX - 24, rightX + 24, topY - 16, bottomY + 16, 1);
			GLUtils::drawFilledRect(255, 255, 255, leftX - 22, rightX + 22, topY - 14, bottomY + 14, 1);

		}

		if (subtitleCaption != nullptr)
		{
			int stx = subtitleCaption->screenX;
			int sty = subtitleCaption->screenY + subtitleCaption->getHeight() + 3;
			GLUtils::drawFilledRect(0, 0, 0, stx, stx + subtitleCaption->getWidth(), sty, sty + 1, 0.75f);
		}

		//draw transparent cursor rectangle
		//interpolate cursor rectangle location
		//pulse fade
		if(menuItems->at(cursorPosition)->info==false)menuItems->at(cursorPosition)->caption->setTextColor(OKColor::green);

		if (areAllMenusDisabled() == false && drawCursor)
		{

			long long currentTime = System::currentHighResTimer();
			long long startTime = rectangleCursorPulseLastTime;
			int pulseTicks = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (pulseTicks > rectangleCursorPulsePeriodTicks)
			{
				rectangleCursorPulseLastTime = currentTime;
				rectangleCursorPulseInOut = !rectangleCursorPulseInOut;
			}
			else
			{
				float whereInPeriod = (float)pulseTicks / (float)rectangleCursorPulsePeriodTicks;
				float alphaChange = rectangleCursorPulseToAlpha - rectangleCursorPulseFromAlpha;
				if (rectangleCursorPulseInOut)
				{
					rectangleCursorPulseCurrentAlpha = rectangleCursorPulseFromAlpha + ((1.0f - whereInPeriod) * alphaChange);
				}
				else
				{
					rectangleCursorPulseCurrentAlpha = rectangleCursorPulseFromAlpha + (whereInPeriod * alphaChange);
				}
			}

			rectangleCursorToY = menuItems->at(cursorPosition)->caption->screenY - 2;

			if (rectangleCursorFromY < y || rectangleCursorCurrentY < y)
			{
				rectangleCursorFromY = rectangleCursorToY;
				rectangleCursorCurrentY = rectangleCursorToY;
			}

			if (rectangleCursorMovementLastTime == 0)rectangleCursorMovementLastTime = currentTime;

			startTime = rectangleCursorMovementLastTime;
			int moveTicks = (int)(System::getTicksBetweenTimes(startTime, currentTime));
			if (moveTicks > rectangleCursorMovementPeriodTicks)
			{
				rectangleCursorMovementLastTime = currentTime;
				rectangleCursorCurrentY = rectangleCursorToY;
				rectangleCursorFromY = rectangleCursorToY;
			}
			else
			{
				float whereInPeriod = (float)moveTicks / (float)rectangleCursorMovementPeriodTicks;
				float moveChange = rectangleCursorToY - rectangleCursorFromY;

				rectangleCursorCurrentY = rectangleCursorFromY + (whereInPeriod * moveChange);

				if (rectangleCursorCurrentY == rectangleCursorToY)rectangleCursorFromY = rectangleCursorToY;
			}



			sp<OKTexture>cursor = rectangleCursorTexture;

			if (cursor != nullptr && menuItems->size() > 0)
			{
				
				float sx0 = leftX - 24;
				float sx1 = rightX + 24;

				float sy0 = rectangleCursorCurrentY;
				float sy1 = sy0 + menuItems->at(cursorPosition)->caption->getHeight() + 4;

				GLUtils::drawTexture(cursor, sx0, sx1, sy0, sy1, rectangleCursorPulseCurrentAlpha, GLUtils::FILTER_NEAREST);
			}
		}

		//getCaptionManager()->render(RenderOrder::OVER_GUI);
		for (int i = 0; i < menuItems->size(); i++)
		{
			sp<MenuItem>m = menuItems->at(i);
			if (i != cursorPosition)m->caption->setTextColor(m->color);
			sp<Caption>c = m->caption;
			c->update();
			c->render();
		}
		if (titleCaption != nullptr)
		{
			titleCaption->update();
			titleCaption->render();
		}
		if (subtitleCaption != nullptr)
		{
			subtitleCaption->update();
			subtitleCaption->render();
		}

		//			if (areAllMenusDisabled() == false && drawCursor)
		//			{
		//
		//				sp<OKTexture>cursor = cursorTexture;
		//
		//				if (cursor != nullptr && menuItems != nullptr && menuItems->size() > 0)
		//				{
		//
		//					float sx0 = menuItems->at(cursorPosition)->caption->screenX - 18;
		//					if (cursorInOutToggle)sx0 += 2;
		//					float sx1 = sx0 + 16;
		//
		//					float sy0 = menuItems->at(cursorPosition)->caption->screenY + 4;
		//					float sy1 = sy0 + 16;
		//
		//					GLUtils::drawTexture(cursor, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
		//				}
		//			}

		if (drawUpArrow)
		{
			sp<OKTexture>t = upCursorTexture;
			if (t != nullptr)
			{
				float sx0 = (float)(GLUtils::getViewportWidth() / 2 - 4);
				if (x != 0) sx0 = (float)x;
				float sx1 = sx0 + 16;

				float sy0 = upArrowY;
				float sy1 = sy0 + 16;

				if (cursorInOutToggle)sy1 -= 1;
				if (cursorInOutToggle)sy0 -= 1;

				GLUtils::drawTexture(t, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
			}
		}

		if (drawDownArrow)
		{
			sp<OKTexture>t = downCursorTexture;
			if (t != nullptr)
			{
				float sx0 = (float)(GLUtils::getViewportWidth() / 2 - 4);
				if (x != 0) sx0 = (float)x;
				float sx1 = sx0 + 16;

				float sy0 = downArrowY;
				float sy1 = sy0 + 16;

				if (cursorInOutToggle)sy1 += 1;
				if (cursorInOutToggle)sy0 += 1;

				GLUtils::drawTexture(t, 0, 1, 0, 1, sx0, sx1, sy0, sy1, 1.0f, GLUtils::FILTER_NEAREST);
			}
		}
	}

}

