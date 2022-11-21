//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "src/Engine/rpg/event/ActionManager.h"
#include "src/Engine/EnginePart.h"
#include "OKFont.h"
#include "OKColor.h"

class Logger;
class OKGame;
class Engine;
class OKColor;
class CaptionManager;
class Entity;
class Area;
class OKTexture;





class Caption : public EnginePart
{
public:
	static Logger log;



	//   int Caption::CENTERED_OVER_ENTITY = -1;
	//   int Caption::CENTERED_SCREEN = -2;
	//   int Caption::CENTERED_X = -3;
	//   int Caption::DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
	//   int Caption::STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;

	//x position modifiers


	enum class Position
	{
		NONE,
		CENTERED_OVER_ENTITY,
		CENTERED_SCREEN,
		CENTERED_X,
	};

	//seconds modifiers
	static const int DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
	static const int STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;



	string text = "";
	sp<OKFont> font = OKFont::font_normal_8;
	sp<TTF_Font> ttfFont = nullptr;
	int fontSize = 8;
	bool outline = false;

private:
	sp<OKColor> textBGColor = OKColor::black;
	sp<OKColor> textColor = OKColor::white;
	sp<OKColor> textAAColor = OKColor::gray;

public:
	float screenX = 0;
	float screenY = 0;
	RenderOrder layer = RenderOrder::ABOVE_TOP;
	float scale = 1.0f;
	long long ticksAge = 0;
	long long ticksToRemain = 0;
	bool visible = true;

	//Caption manager will delete it
	bool deleteMe = false;
private:
	float alpha = 0.0f;
	float alphaTo = 1.0f;
	bool beingDeletedWhenAlphaHitsZero = false;
	


public:
	float entityXWhenCreated = 0;
	float entityYWhenCreated = 0;
	sp<Entity> entity = nullptr;
	int actionCaptionType = ActionManager::ACTIONCAPTIONTYPE_NONE;
	sp<Area> area = nullptr;
	int actionRangeX = 0;
	int actionRangeY = 0;

	bool fadeLetterColorTowardsTop = true;

	int textCharacterLength = 0;
private:
	int width = 0;
	int height = 0;
public:
	int lines = 1;
	int maxWidth = 0;

	int xInLine = 0;
	int line = 0;
	int longestLineWidth = 0;

private:
	bool initialized = false;

public:
	sp<OKTexture> texture = nullptr;
	sp<ByteArray> textureByteArray = nullptr;
	int texWidth = 0;
	int texHeight = 0;

public:
	Position fixedPosition = Position::NONE;
	bool flashing = false;
	int flashingTicksPerFlash = 0;
	bool centerTextOnMultipleLines = false;
	long long flashingTicksCount = 0;


	//bool drawAbove = false;



	Caption(sp<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, sp<OKFont> font = OKFont::font_normal_8_outlined, sp<OKColor> textColor = OKColor::black, sp<OKColor> textAAColor=nullptr, sp<OKColor> textBGColor = OKColor::clear, RenderOrder layer = RenderOrder::ABOVE_TOP, float scale=1, int maxWidth=0, sp<Entity> entity = nullptr, sp<Area> area = nullptr, bool fadeLetterColorTowardsTop = false, bool centerTextOnMultipleLines = false);
	Caption(sp<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, int fontSize = 16, bool outline = false, sp<OKColor> textColor = OKColor::black, sp<OKColor> textBGColor = OKColor::clear, RenderOrder layer = RenderOrder::ABOVE_TOP, float scale=1, sp<Entity> entity = nullptr, sp<Area> area = nullptr);
	Caption(sp<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, int fontSize = 16, bool outline = false, sp<OKColor> textColor = OKColor::black, RenderOrder layer = RenderOrder::ABOVE_TOP);

	void setText(const string& text, bool force = false);
	sp<OKColor> getTextColor();
	void setTextColor(sp<OKColor> fg, sp<OKColor> aa = nullptr, sp<OKColor> bg = nullptr);
	void initTTF(sp<Engine> g, Position fixedPosition, float screenX, float screenY, long long ticks, const string& text, int fontSize, sp<OKColor> textColor, sp<OKColor> textBGColor, RenderOrder layer, float scale, sp<Entity> entity, sp<Area> area, bool outline);
	void init(sp<Engine> g, Position fixedPosition, float screenX, float screenY, long long ticks, const string& text, sp<OKFont> font, sp<OKColor> textColor, sp<OKColor> textAAColor, sp<OKColor> textBGColor, RenderOrder layer, float scale, int maxWidth, sp<Entity> entity, sp<Area> area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines);
	void render();
private:
	void increaseMaxWidthToLongestWord();
	int skipNextWord(int position);
	int getCurrentLineLength(int position);
	void calculateTextureWidthAndHeightByParsingEachLine();
	void drawText();
	void parseOptions(const string& optionBuffer);
	int getLetterPixelColor(int letterIndex, int y, int xInLetter, bool blank);
	void setPixel(int index, sp<OKColor> c);
public:
	float getAlphaTo();
	float getAlpha();
	void setAlphaTo(float a);
	void setAlphaImmediately(float a);
	float getWidth();
	int reduceHeightByOne();
	int increaseHeightByOne();
	float getHeight();
private:
	void drawBlankColumn();
	void drawColumn(int xInLetter, int letterIndex, bool blank);
	void drawLetter(int letterIndex);
public:
	void updateScreenXY();
	void setToFadeOutAndBeDeleted();
	void setToBeDeletedImmediately();
	bool getBeingDeletedWhenFadeOutStatus();
	void update();
	void setEntity(sp<Entity> e);
};

