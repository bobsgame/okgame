
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
	//TTF_shared_ptr<Font >font = OKFont::ttf_18;

	int fontSize = 22;
	int scaledFontSize = 22;
public:


	static shared_ptr<OKColor> menuColor;
	static shared_ptr<OKColor> disabledMenuColor;
	static shared_ptr<OKColor> warningMenuColor;
	static shared_ptr<OKColor> clearColor;
	static shared_ptr<OKColor> infoColor;
	static shared_ptr<OKColor> statusColor;
	static shared_ptr<OKColor> errorColor;
	static shared_ptr<OKColor> bgColor;

	shared_ptr<OKColor> defaultMenuColor = nullptr;

	shared_ptr<Caption> titleCaption = nullptr;
	shared_ptr<Caption> subtitleCaption = nullptr;
	
	bool outline = true;
	
	bool scaleFontSizeToFit = true;

	int cursorPosition = 0;
	static shared_ptr<OKTexture> rectangleCursorTexture;
	static shared_ptr<OKTexture> cursorTexture;
	static shared_ptr<OKTexture> upCursorTexture;
	static shared_ptr<OKTexture> downCursorTexture;
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

	
	static ArrayList<shared_ptr<OKMenu>> activeMenus;

	shared_ptr<OKTexture >graphic = nullptr;
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
		shared_ptr<Caption> caption = nullptr;
		string id = "";
		shared_ptr<OKColor >color = nullptr;
		bool hidden = false;
		bool info = false;
		bool isYesNoType = false;
		bool yesNoValue = true;
		string captionText = "";

		bool outline = true;

		//shared_ptr<OKSubMenu >subMenu = nullptr;

		~MenuItem();
		void setYesNo(bool yesNo);
		void toggle();
		void setColor(shared_ptr<OKColor> color, bool outline = true);
		void setText(string s);
	};

	ArrayList<shared_ptr<MenuItem>> menuItems;

	shared_ptr<MenuItem> topMenuItemDrawn = nullptr;

	int lastWidth = 0;
	int lastHeight = 0;

	OKMenu(shared_ptr<Engine >g, string title = "", string subtitle = "");
	~OKMenu();

	void setGraphic(shared_ptr<OKTexture> t = nullptr, int graphicWidth = 0, int graphicYStartPosition = 0, int maxGraphicHeight = 0, int filter = GLUtils::FILTER_NEAREST);
	void clear();
	void setAllCaptionsToFullAlpha();
	static void update(shared_ptr<Engine >g, int ticksPassed);

private:
	bool areAllMenusDisabled();
public:

	void up(bool noSound = false);
	void down(bool noSound = false);
	shared_ptr<MenuItem> addInfo(string caption, string id = "", shared_ptr<OKColor >color = nullptr);
	shared_ptr<MenuItem> add(string caption, string id = "", shared_ptr<OKColor >color = nullptr);
	shared_ptr<MenuItem> addYesNo(string caption, bool yesNo);

	int getAmountOfMenuItems();
	ArrayList<string> getArrayListOfMenuItemIDs();

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
	shared_ptr<Caption> getCaptionByID(string id);
	shared_ptr<MenuItem> getMenuItemByID(string id);
	shared_ptr<MenuItem> getSelectedMenuItem();

	void setFontSize(int size);

	//bool cancelToQuit = true;
	//bool confirmToConfirm = true;
	//bool *onQuitToggle;

	//	//=========================================================================================================================
	//	shared_ptr<OKSubMenu> addSubMenu(string caption, string id, shared_ptr<OKGame >b, void(*f) (shared_ptr<OKGame>, string))
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
//	shared_ptr<OKMenu >parentMenu = nullptr;
//	shared_ptr<OKGame >bobsGame = nullptr;
//	void (*callBack)(shared_ptr<OKGame>, string) = nullptr;
//	bool isOpen = false;
//
//	OKSubMenu(shared_ptr<Engine >g) : OKMenu(g, "")
//	{
//		
//	}
//	~OKSubMenu()
//	{
//		
//	}
//	shared_ptr<MenuItem> add(string caption, string id = "", shared_ptr<OKColor >color = menuColor)
//	{
//		shared_ptr<MenuItem > m = OKMenu::add(caption, id, color);
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

