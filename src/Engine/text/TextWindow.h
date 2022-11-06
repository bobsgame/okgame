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


	shared_ptr<OKTexture> textBoxTexture = nullptr;
	shared_ptr<OKTexture> spriteBoxTexture = nullptr;
	static shared_ptr<OKTexture> borderTexture;


	float scrollPercent = 0;

	shared_ptr<ByteArray> textBoxTextureByteArray = nullptr;
	//u8* textBoxTexturePixelsByteBuffer;

	shared_ptr<ByteArray> spriteWindowTextureByteArray = nullptr;
	//u8* spriteWindowTexturePixelsByteBuffer;


	float voicePitch = 0;
	string label = "";

	int xInLine = 0;
	int line = 0;

	shared_ptr<Entity> spriteWindowEntity = nullptr;

	shared_ptr<OKTexture> spriteWindowTexture = nullptr;

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

	TextWindow(shared_ptr<Engine> g);


	void init();


	void render();


	void updateSpriteWindowTexture();


	void setSpriteWindow(shared_ptr<Entity> entity, shared_ptr<OKTexture> texture, const string& newLabel);


	void updateTextureFromByteArray();


	void clearByteArray();


	int getPixelValue(int letter_index, int y, int x_in_letter, bool blank);


	void setPixel(int index, shared_ptr<OKColor> c);


	void drawColumn(int letter_index, int x_in_letter, bool blank);
};

