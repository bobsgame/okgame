//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;




class TextWindow : public EnginePart
{ //=========================================================================================================================


public:
	static Logger log;


	sp<OKTexture> textBoxTexture = nullptr;
	sp<OKTexture> spriteBoxTexture = nullptr;
	static sp<OKTexture> borderTexture;


	float scrollPercent = 0;

	sp<ByteArray> textBoxTextureByteArray = nullptr;
	//u8* textBoxTexturePixelsByteBuffer;

	sp<ByteArray> spriteWindowTextureByteArray = nullptr;
	//u8* spriteWindowTexturePixelsByteBuffer;


	float voicePitch = 0;
	string label = "";

	int xInLine = 0;
	int line = 0;

	sp<Entity> spriteWindowEntity = nullptr;

	sp<OKTexture> spriteWindowTexture = nullptr;

	bool redraw = false;

	float alpha = 1.0f;


	int shakeTicksXTotal = 0;
	//public int shakeTicksLeft=0;
	int shakeTicksLeftRightCounter = 0;
	float shakeX = 0;
	int shakeMaxX = 2;
	bool shakeLeftRightToggle = false;


	int shakeTicksYTotal = 0;
	//public int shakeTicksLeft=0;
	int shakeTicksUpDownCounter = 0;
	float shakeY = 0;
	int shakeMaxY = 2;
	bool shakeUpDownToggle = false;

	TextWindow(sp<Engine> g);


	void init();


	void render();


	void updateSpriteWindowTexture();


	void setSpriteWindow(sp<Entity> entity, sp<OKTexture> texture, const string& newLabel);


	void updateTextureFromByteArray();


	void clearByteArray();


	int getPixelValue(int letter_index, int y, int x_in_letter, bool blank);


	void setPixel(int index, sp<OKColor> c);


	void drawColumn(int letter_index, int x_in_letter, bool blank);
};

