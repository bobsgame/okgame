
//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
#include <src/Engine/EnginePart.h>
#include "Color.h"
#include "Caption.h"
#include "gl/GLUtils.h"


//class OKSubMenu;
//=========================================================================================================================
class OKMenu : public EnginePart
{//=========================================================================================================================
public:
	//do autofit/scrolling, only scroll menu items below info captions

	//do render within xywh

	//add graphic

	//gl draw ratio fit between height or width

private:
	//sp<TTF_Font >font = OKFont::ttf_18;

	int fontSize = 22;
	int scaledFontSize = 22;
public:


	static sp<OKColor> menuColor;
	static sp<OKColor> disabledMenuColor;
	static sp<OKColor> warningMenuColor;
	static sp<OKColor> clearColor;
	static sp<OKColor> infoColor;
	static sp<OKColor> statusColor;
	static sp<OKColor> errorColor;
	static sp<OKColor> bgColor;

	sp<OKColor> defaultMenuColor = nullptr;

	sp<Caption> titleCaption = nullptr;
	sp<Caption> subtitleCaption = nullptr;
	
	bool outline = true;
	
	bool scaleFontSizeToFit = true;

	int cursorPosition = 0;
	static sp<OKTexture> rectangleCursorTexture;
	static sp<OKTexture> cursorTexture;
	static sp<OKTexture> upCursorTexture;
	static sp<OKTexture> downCursorTexture;
	static long long cursorInOutToggleTicks;
	static bool cursorInOutToggle;
	static int lastMX;
	static int lastMY;

	long long rectangleCursorPulseLastTime = 0;
	int rectangleCursorPulsePeriodTicks = 300;
	float rectangleCursorPulseFromAlpha = 0.1f;
	float rectangleCursorPulseToAlpha = 0.2f;
	float rectangleCursorPulseCurrentAlpha = 0.2f;
	bool rectangleCursorPulseInOut = false;
	long long rectangleCursorMovementLastTime = 0;
	int rectangleCursorMovementPeriodTicks = 60;
	float rectangleCursorFromY = 0;
	float rectangleCursorToY = 0;
	float rectangleCursorCurrentY = 0;

	
	static sp<vector<sp<OKMenu>>>activeMenus;

	sp<OKTexture>graphic = nullptr;
	int filter = GLUtils::FILTER_NEAREST;
	float spacing = 1.0f;
	bool center = true;
	
	int graphicWidth = 0;
	int maxGraphicHeight = 0;
	int graphicYStartPosition = 0;
	
	//=========================================================================================================================
	class MenuItem
	{//=========================================================================================================================
	public:
		sp<Caption> caption = nullptr;
		string id = "";
		sp<OKColor>color = nullptr;
		bool hidden = false;
		bool info = false;
		bool isYesNoType = false;
		bool yesNoValue = true;
		string captionText = "";

		bool outline = true;

		//sp<OKSubMenu>subMenu = nullptr;

		~MenuItem();
		void setYesNo(bool yesNo);
		void toggle();
		void setColor(sp<OKColor> color, bool outline = true);
		void setText(string s);
	};

	sp<vector<sp<MenuItem>>>menuItems;

	sp<MenuItem> topMenuItemDrawn = nullptr;

	int lastWidth = 0;
	int lastHeight = 0;

	OKMenu(sp<Engine>g, string title = "", string subtitle = "");
	~OKMenu();

	void setGraphic(sp<OKTexture> t = nullptr, int graphicWidth = 0, int graphicYStartPosition = 0, int maxGraphicHeight = 0, int filter = GLUtils::FILTER_NEAREST);
	void clear();
	void setAllCaptionsToFullAlpha();
	static void update(sp<Engine>g, int ticksPassed);

private:
	bool areAllMenusDisabled();
public:

	void up(bool noSound = false);
	void down(bool noSound = false);
	sp<MenuItem> addInfo(string caption, string id = "", sp<OKColor>color = nullptr);
	sp<MenuItem> add(string caption, string id = "", sp<OKColor>color = nullptr);
	sp<MenuItem> addYesNo(string caption, bool yesNo);

	int getAmountOfMenuItems();
	sp<vector<string>> getArrayListOfMenuItemIDs();

	//returns bottom of graphic y position
	void render(
		int y = 0, 
		int x = 0, 
		int endY = GLUtils::getViewportHeight(), 
		bool drawCursor = true, 
		int* returnBottomOfGraphic = nullptr, 
		int* returnBottomOfCaptions = nullptr, 
		bool renderBackgroundAndBorder = false, 
		int* returnLeftX = nullptr, 
		int* returnRightX = nullptr
	);

	void setHidden(string id, bool b);
	void setAllInvisible();
	void setAllVisible();
	bool isSelectedID(string id, bool clicked = false, int mx = 0, int my = 0);
	void setSelectedID(string id);
	sp<Caption> getCaptionByID(string id);
	sp<MenuItem> getMenuItemByID(string id);
	sp<MenuItem> getSelectedMenuItem();

	void setFontSize(int size);

	//bool cancelToQuit = true;
	//bool confirmToConfirm = true;
	//bool *onQuitToggle;

	//	//=========================================================================================================================
	//	sp<OKSubMenu> addSubMenu(string caption, string id, sp<OKGame>b, void(*f) (sp<OKGame>, string))
	//	{//=========================================================================================================================
	//		
	//
	//
	//
	//	}

};
//
////=========================================================================================================================
//class OKSubMenu : public OKMenu
//{//=========================================================================================================================
//public:
//	sp<OKMenu>parentMenu = nullptr;
//	sp<OKGame>bobsGame = nullptr;
//	void (*callBack)(sp<OKGame>, string) = nullptr;
//	bool isOpen = false;
//
//	OKSubMenu(sp<Engine>g) : OKMenu(g, "")
//	{
//		
//	}
//	~OKSubMenu()
//	{
//		
//	}
//	sp<MenuItem> add(string caption, string id = "", sp<OKColor>color = menuColor)
//	{
//		sp<MenuItem> m = OKMenu::add(caption, id, color);
//		menuItems->get(menuItems->size()-1)->caption->visible = false;
//		return m;
//
//	}
//	void onSelected()
//	{
//		if(callBack!=nullptr)callBack(bobsGame, getSelectedMenuItem()->id);
//	}
//
//
//};

