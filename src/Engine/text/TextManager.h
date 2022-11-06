//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
class Logger;


class TextWindow;

class TextManager : public EnginePart
{ 

public:
	static Logger log;

	//static shared_ptr<TrueTypeFont> ttfFont;

	static string debugtext1;
	static string debugtext2;
	static string debugtext3;
	static string debugtext4;

private:
	bool antiAlias = true;

public:
	ArrayList<shared_ptr<TextWindow>>* textBox = make_shared<ArrayList><shared_ptr<TextWindow>>();


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

	shared_ptr<BobFont> font = nullptr; // this isn't per-getText window because we want to share the state across the boxes. is that right, or would per-box be better?
	shared_ptr<BobColor> textColor = BobColor::white;
	shared_ptr<BobColor> textBGColor = BobColor::black;
	shared_ptr<BobColor> textAAColor = BobColor::gray;
	shared_ptr<BobColor> textShadowColor = BobColor::darkGray;

	shared_ptr<BobColor> tC0 = BobColor::black;
	shared_ptr<BobColor> tC1 = BobColor::white;
	shared_ptr<BobColor> tC2 = BobColor::gray;
	shared_ptr<BobColor> tC3 = BobColor::darkGray;

	bool skipText = false;

	bool buttonIconUpDownToggle = false;
	int buttonTimer = 0;
	shared_ptr<BobTexture> buttonTexture = nullptr;
	// TODO: load button texture, draw where appropriate during render

	int MAX_ANSWER_LENGTH = 255;

	shared_ptr<Entity> optionTargetEntity1 = nullptr;
	shared_ptr<Entity> optionTargetEntity2 = nullptr;
	shared_ptr<Entity> optionTargetEntity3 = nullptr;
	shared_ptr<Entity> optionTargetEntity4 = nullptr;
	shared_ptr<Entity> optionTargetEntity5 = nullptr;
	shared_ptr<Entity> optionTargetEntity6 = nullptr;

	int cursorTicks = 0;
	bool cursorPixelUpDownToggle = true;
	float answerBoxY = 0;
	int numberOfAnswers = 0;
	int selectedAnswer = 0;

	shared_ptr<ScreenSprite> cursorScreenSprite = nullptr;
	float keyboardY = 0;
	shared_ptr<ScreenSprite> keyboardScreenSprite = nullptr;
	shared_ptr<ScreenSprite> actionIconScreenSprite = nullptr;
	string optionBuffer;

	//public float BOTTOM_ACTIVE_POSITION_Y=5000;
	//public float BOTTOM_INACTIVE_POSITION_Y=5000;
	//public float TOP_ACTIVE_POSITION_Y=5000;
	//public float TOP_INACTIVE_POSITION_Y=5000;
	//public float POSITION_X=5000;

	static shared_ptr<BobTexture> questionMarkTexture;

	//public long textEngineSpeedTicksPerLetter=10;
	//public long drawLetterTicksCounter=100;

	
	TextManager(shared_ptr<Engine> g);

	
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

	void dialogue(shared_ptr<Dialogue> d);

	void getTextFromOnscreenKeyboard();

	void getNumberFromOnscreenNumpad();

	void getAnswerToQuestionWithQuestionBox(const string& s, int i);
};

