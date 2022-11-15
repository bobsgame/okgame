//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
class Logger;

#include "src/Engine/EnginePart.h"
#include "src/Utility/Color.h"
#include "src/Utility/OKFont.h"


class Engine;
class Entity;
class Caption;
class PuzzleGame;
class OKColor;
class OKGame;
class Area;


class CaptionManager : EnginePart
{
public:

	static Logger log;


	sp<vector<sp<Caption>>>captionList;// = ms<vector><sp<Caption>>();



public:
	CaptionManager(sp<Engine> g);

	void update();
	void render(RenderOrder layer); //RenderOrder layer)

	//TODO: add more getCaption creation functions to have lots of nice options?

	sp<Caption> newManagedCaption(Caption::Position fixedPosition, int x, int y, int ticks, const string& text, sp<OKFont> font = OKFont::font_normal_8_outlined, sp<OKColor> textColor = OKColor::black, sp<OKColor> textAAColor = nullptr, sp<OKColor> textBGColor = OKColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, int width = 0, sp<Entity> entity = nullptr, sp<Area> area = nullptr, bool fadeLetterColorTowardsTop = false, bool centerTextOnMultipleLines = false);
	sp<Caption> newManagedCaption(Caption::Position fixedPosition, int x, int y, int ticks, const string& text, int fontSize = 8, bool outline = false, sp<OKColor> textColor = OKColor::black, sp<OKColor> textBGColor = OKColor::clear, RenderOrder r = RenderOrder::ABOVE_TOP, float scale = 1, sp<Entity> entity = nullptr, sp<Area> area = nullptr);

};

