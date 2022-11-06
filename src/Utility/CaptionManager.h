//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
class Logger;

#include "src/Engine/EnginePart.h"
#include "src/Utility/Color.h"
#include "src/Utility/BobFont.h"


class Engine;
class Entity;
class Caption;
class PuzzleGame;
class BobColor;
class BobsGame;
class Area;


class CaptionManager : EnginePart
{
public:

	static Logger log;


	ArrayList<shared_ptr<Caption>>* captionList = make_shared<ArrayList><shared_ptr<Caption>>();



public:
	CaptionManager(shared_ptr<Engine> g);

	void update();
	void render(RenderOrder layer); //RenderOrder layer)

	//TODO: add more getCaption creation functions to have lots of nice options?

	shared_ptr<Caption> newManagedCaption(Caption::Position fixedPosition, int x, int y, int ticks, const string& text, shared_ptr<BobFont> font = BobFont::font_normal_8_outlined, shared_ptr<BobColor> textColor = BobColor::black, shared_ptr<BobColor> textAAColor = nullptr, shared_ptr<BobColor> textBGColor = BobColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, int width = 0, shared_ptr<Entity> entity = nullptr, shared_ptr<Area> area = nullptr, bool fadeLetterColorTowardsTop = false, bool centerTextOnMultipleLines = false);
	shared_ptr<Caption> newManagedCaption(Caption::Position fixedPosition, int x, int y, int ticks, const string& text, int fontSize = 8, bool outline = false, shared_ptr<BobColor> textColor = BobColor::black, shared_ptr<BobColor> textBGColor = BobColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, shared_ptr<Entity> entity = nullptr, shared_ptr<Area> area = nullptr);

};

