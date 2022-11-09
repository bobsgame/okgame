//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "oktypes.h"
class Logger;


class TextWindow;

class TextManager : public EnginePart
{ 

public:
	static Logger log;

	//static sp<TrueTypeFont> ttfFont;

	static string debugtext1;
	static string debugtext2;
	static string debugtext3;
	static string debugtext4;

private:
	bool antiAlias = true;

public:
	vector<sp<TextWindow>> textBox;// = ms<ArrayList><sp<TextWindow>>();


	int width = 64 * 6 * 2; // *2 because we draw everything at 2x to allow for scaling (and higher res 1x unicode fonts)
	int height = 64 * 2;

	//int pow2TexWidth = 0;
	//int pow2TexHeight = 0;

	int spriteWindowWidth = 64 * 2;

	// public int line_size_x=size_x/2; //because the getText box is drawn at 2x (so the texture scales nicely if i zoom it in or out)

	int MAX_LINES = 4;

	string currentText = "";
	int length = 0;
	int position = 0;

	int ticksPerLetter = 8;
	int remainderTicks = 0;


	enum class TextEngineState
	{
		CLOSED,
		OPEN,
		CLOSING,
		ANSWER_BOX_ON,
		ANSWER_BOX_CLOSING,
		KEYBOARD_CLOSING,
		KEYBOARD_ON,
	};
	TextEngineState textEngineState = TextEngineState::CLOSED;


	
	const static int BOTTOM = 0;
	const static int TOP = 1;

	int selectedTextbox = BOTTOM;

	bool topBoxActivated = false;

	bool keepOpenForNewText = false;
	bool waitingForButtonForNewPage = false;
	bool pausedUntilButtonPress = false;
	bool waitingForCancelButtonUnpress = false;
	bool cannotCancel = false;
	bool waitingForButtonPressToClose = false;
	bool waitingForUnpress = false;
	bool buttonAUnpressed = false;
	bool buttonIconIsOn = false;
	bool scrollingUp = false;

	bool delay = false;
	int delayTicks = 0;

	sp<OKFont> font = nullptr; // this isn't per-getText window because we want to share the state across the boxes. is that right, or would per-box be better?
	sp<OKColor> textColor = OKColor::white;
	sp<OKColor> textBGColor = OKColor::black;
	sp<OKColor> textAAColor = OKColor::gray;
	sp<OKColor> textShadowColor = OKColor::darkGray;

	sp<OKColor> tC0 = OKColor::black;
	sp<OKColor> tC1 = OKColor::white;
	sp<OKColor> tC2 = OKColor::gray;
	sp<OKColor> tC3 = OKColor::darkGray;

	bool skipText = false;

	bool buttonIconUpDownToggle = false;
	int buttonTimer = 0;
	sp<OKTexture> buttonTexture = nullptr;
	// TODO: load button texture, draw where appropriate during render

	int MAX_ANSWER_LENGTH = 255;

	sp<Entity> optionTargetEntity1 = nullptr;
	sp<Entity> optionTargetEntity2 = nullptr;
	sp<Entity> optionTargetEntity3 = nullptr;
	sp<Entity> optionTargetEntity4 = nullptr;
	sp<Entity> optionTargetEntity5 = nullptr;
	sp<Entity> optionTargetEntity6 = nullptr;

	int cursorTicks = 0;
	bool cursorPixelUpDownToggle = true;
	float answerBoxY = 0;
	int numberOfAnswers = 0;
	int selectedAnswer = 0;

	sp<ScreenSprite> cursorScreenSprite = nullptr;
	float keyboardY = 0;
	sp<ScreenSprite> keyboardScreenSprite = nullptr;
	sp<ScreenSprite> actionIconScreenSprite = nullptr;
	string optionBuffer;

	//public float BOTTOM_ACTIVE_POSITION_Y=5000;
	//public float BOTTOM_INACTIVE_POSITION_Y=5000;
	//public float TOP_ACTIVE_POSITION_Y=5000;
	//public float TOP_INACTIVE_POSITION_Y=5000;
	//public float POSITION_X=5000;

	static sp<OKTexture> questionMarkTexture;

	//public long textEngineSpeedTicksPerLetter=10;
	//public long drawLetterTicksCounter=100;

	
	TextManager(sp<Engine> g);

	
	bool isTextBoxOpen();

	
	bool isTextAnswerBoxOpen();

	
	void init();

	
	void reset();

	
	void text(const string& s);

	
	void render();

	
	int getLineSizeX();

	
	void update();

	void parseColorizedTags();
	void postparseColorizedTags();
	
	void drawText(long long ticksPassed);

	
	void handleInput();

	
	void doScrolling(long long ticksPassed);

	
	void drawLetter();

	
	void parseOption();

	void dialogue(sp<Dialogue> d);

	void getTextFromOnscreenKeyboard();

	void getNumberFromOnscreenNumpad();

	void getAnswerToQuestionWithQuestionBox(const string& s, int i);
};

