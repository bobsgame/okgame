
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------






Logger Caption::log = Logger("Caption");

//   int Caption::CENTERED_OVER_ENTITY = -1;
//   int Caption::CENTERED_SCREEN = -2;
//   int Caption::CENTERED_X = -3;
//   int Caption::DELETE_WHEN_MAIN_SPRITE_MOVES = -2;
//   int Caption::STAY_ONSCREEN_UNTIL_MANUALLY_DELETE = -1;

/**
If Engine is Client(), it will draw outside the nD. If it is getEngine() inside an nD game, it will draw inside the nD.
If getScreenX is Caption.CENTERED_OVER_ENTITY it will center itself over this.entity.
If no entity is set, it will use getPlayer() if not null.
If getScreenX is Caption.CENTERED_SCREEN it will ignore Y and center both X and Y in the screen.
If seconds is Caption.DELETE_WHEN_ENTITY_MOVES it will delete when attached entity (or player if not null) moves.
If seconds is Caption.STAY_ONSCREEN_UNTIL_MANUALLY_DELETE it must be deleted manually.

TODO: if layer is outside the screen, don't getScale with the screen.

Scale is default at 2X for 1.0f. for 1:1 pixels use 0.5f.
SetWidth is the width to truncate to a newline. It won't truncate words. setWidth 0 or -1 will just default to half the screen width at maximum.

*/
//=========================================================================================================================
Caption::Caption(Engine* g, float screenX, float screenY, int ticks, const string& text, BobFont* font, BobColor* textColor, BobColor* textAAColor, BobColor* textBGColor, RenderOrder layer, float scale, int maxWidth, Entity* entity, Area* area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines)
{//=========================================================================================================================
	init(g, screenX, screenY, ticks, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
}
//=========================================================================================================================
Caption::Caption(Engine* g, float screenX, float screenY, int ticks, const string& text, TTF_Font* ttfFont, BobColor* textColor, BobColor* textBGColor, RenderOrder layer, float scale, Entity* entity, Area* area, bool outline)
{//=========================================================================================================================

	initTTF(g, screenX, screenY, ticks, text, ttfFont, textColor, textBGColor, layer, scale, entity, area, outline);
}

//=========================================================================================================================
Caption::Caption(Engine* g, float screenX, float screenY, int ticks, const string& text, TTF_Font* ttfFont, BobColor* textColor, RenderOrder layer, bool outline)
{//=========================================================================================================================

	initTTF(g, screenX, screenY, ticks, text, ttfFont, textColor, BobColor::clear, layer, 1, nullptr, nullptr, outline);
}
//=========================================================================================================================
void Caption::setText(const string& text, bool force)
{//=========================================================================================================================

	if (force == false && text == this->text)
	{
		return;
	}


	if (texture != nullptr)
	{
		texture->release();
		texture = nullptr;
	}


	if (ttfFont != nullptr)initTTF(e, screenX, screenY, ticksToRemain, text, ttfFont, textColor, textBGColor, layer, scale, entity, area, outline);
	else init(e, screenX, screenY, ticksToRemain, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	
	updateScreenXY();
}

//=========================================================================================================================
BobColor* Caption::getTextColor()
{//=========================================================================================================================
	return textColor;


}


//=========================================================================================================================
void Caption::setTextColor(BobColor* fg, BobColor* aa, BobColor* bg)
{//=========================================================================================================================


	if (fg == this->textColor && bg == this->textBGColor && aa == this->textAAColor)
	{
		return;
	}

	//-----------------------------
	//set color
	//-----------------------------

	//color 0 = bg color
	//color 1 = getText color
	//color 2 = antialiasing color

	BobColor* tempFG = this->textColor;
	BobColor* tempBG = this->textBGColor;
	BobColor* tempAA = this->textAAColor;

	if (fg != nullptr)
	{
		tempFG = fg;
	}
	if (bg != nullptr)
	{
		tempBG = bg;
	}

	if (aa != nullptr)
	{
		tempAA = aa;
	}
	else
	{
		// if (this.font.outlined == true) { tempAA = Color.BLACK; }
		// else
		if (tempBG == BobColor::white)
		{
			tempAA = new BobColor(*fg);
			tempAA->lighter();
			tempAA->lighter();
			tempAA->lighter();

			//				if(textColor==Color.BLACK)this.textAAColor=Color.LIGHTERGRAY;
			//				if(textColor==Color.GRAY)this.textAAColor=Color.LIGHTERGRAY;
			//
			//				if(textColor==Color.GREEN)this.textAAColor=Color.LIGHTGREEN;
			//				if(textColor==Color.BLUE)this.textAAColor=Color.LIGHTBLUE;
			//				if(textColor==Color.PURPLE)this.textAAColor=Color.LIGHTPURPLE;
			//				if(textColor==Color.PINK)this.textAAColor=Color.LIGHTPINK;
			//				if(textColor==Color.RED)this.textAAColor=Color.LIGHTRED;
			//				if(textColor==Color.ORANGE)this.textAAColor=Color.LIGHTORANGE;
			//				if(textColor==Color.YELLOW)this.textAAColor=Color.LIGHTYELLOW;
		}
		else
		{
			if (tempBG == BobColor::black) //||textBGColor==Color.CLEAR)
			{
				tempAA = new BobColor(*fg);
				tempAA->darker();
				tempAA->darker();
				tempAA->darker();

				//				if(textColor==Color.WHITE)this.textAAColor=Color.DARKGRAY;
				//				if(textColor==Color.GRAY)this.textAAColor=Color.DARKERGRAY;
				//
				//				if(textColor==Color.GREEN)this.textAAColor=Color.DARKERGREEN;
				//				if(textColor==Color.BLUE)this.textAAColor=Color.DARKBLUE;
				//				if(textColor==Color.PURPLE)this.textAAColor=Color.DARKPURPLE;
				//				if(textColor==Color.PINK)this.textAAColor=Color.DARKPINK;
				//				if(textColor==Color.RED)this.textAAColor=Color.DARKRED;
				//				if(textColor==Color.ORANGE)this.textAAColor=Color.DARKORANGE;
				//				if(textColor==Color.YELLOW)this.textAAColor=Color.DARKYELLOW;
			}
			else
			{
				if (tempBG == BobColor::clear)
				{
					BobColor* c = fg;
					tempAA = new BobColor(c->rf(), c->gf(), c->bf(), c->af() / 2.0f);
				}
			}
		}
	}

	if (initialized == true) //don't replace the getText if we haven't drawn the bitmap yet
	{
		if (tempFG != this->textColor || tempBG != this->textBGColor || tempAA != this->textAAColor) //dont replace if the colors havent changed
		{
			this->textColor = tempFG;
			this->textBGColor = tempBG;
			this->textAAColor = tempAA;

			setText(text, true);
		}
	}
	else
	{
		this->textColor = tempFG;
		this->textBGColor = tempBG;
		this->textAAColor = tempAA;
	}







}


//=========================================================================================================================
void Caption::initTTF(Engine* g, float screenX, float screenY, long long ticks, const string& text, TTF_Font* font, BobColor* textColor, BobColor* textBGColor, RenderOrder layer, float scale, Entity* entity, Area* area, bool outline)
{//=========================================================================================================================
	this->e = g;

	this->initialized = false;

	//get length
	this->textCharacterLength = (int)text.length();
	this->text = text;
	this->screenX = screenX;
	this->screenY = screenY;
	this->layer = layer;
	this->scale = scale;
	this->ticksToRemain = ticks;
	this->ttfFont = font;

	this->actionCaptionType = ActionManager::ACTIONCAPTIONTYPE_NONE;
	this->entity = entity;
	this->area = area;

	this->entityXWhenCreated = 0;
	this->entityYWhenCreated = 0;

	setEntity(entity);


	//handle fixed positions
	if (screenX < 0)
	{
		this->fixedPosition = (int)(screenX);
	}


	if (texture != nullptr)
	{
		texture->release();
		texture = nullptr;
	}

	if (textBGColor == nullptr)textBGColor = BobColor::clear;
	setTextColor(textColor, textAAColor, textBGColor);


	SDL_Color textSDLColor = { (Uint8)textColor->ri() ,(Uint8)textColor->gi(),(Uint8)textColor->bi(),(Uint8)textColor->ai() };
	SDL_Color bgSDLColor = { (Uint8)textBGColor->ri() ,(Uint8)textBGColor->gi(),(Uint8)textBGColor->bi(),(Uint8)textBGColor->ai() };

	if (this->text.length() == 0)this->text = " ";

	SDL_Surface* surface = nullptr;


	if (outline)this->outline = true;
	if (outline)
	{
		TTF_Font* outlineFont = nullptr;
		if (ttfFont == BobFont::ttf_6)outlineFont = BobFont::ttf_outline_6;
		if (ttfFont == BobFont::ttf_7)outlineFont = BobFont::ttf_outline_7;
		if (ttfFont == BobFont::ttf_8)outlineFont = BobFont::ttf_outline_8;
		if (ttfFont == BobFont::ttf_9)outlineFont = BobFont::ttf_outline_9;
		if (ttfFont == BobFont::ttf_10)outlineFont = BobFont::ttf_outline_10;
		if (ttfFont == BobFont::ttf_11)outlineFont = BobFont::ttf_outline_11;
		if (ttfFont == BobFont::ttf_12)outlineFont = BobFont::ttf_outline_12;
		if (ttfFont == BobFont::ttf_13)outlineFont = BobFont::ttf_outline_13;
		if (ttfFont == BobFont::ttf_14)outlineFont = BobFont::ttf_outline_14;
		if (ttfFont == BobFont::ttf_15)outlineFont = BobFont::ttf_outline_15;
		if (ttfFont == BobFont::ttf_16)outlineFont = BobFont::ttf_outline_16;
		if (ttfFont == BobFont::ttf_17)outlineFont = BobFont::ttf_outline_17;
		if (ttfFont == BobFont::ttf_18)outlineFont = BobFont::ttf_outline_18;
		if (ttfFont == BobFont::ttf_19)outlineFont = BobFont::ttf_outline_19;
		if (ttfFont == BobFont::ttf_20)outlineFont = BobFont::ttf_outline_20;
		if (ttfFont == BobFont::ttf_21)outlineFont = BobFont::ttf_outline_21;
		if (ttfFont == BobFont::ttf_22)outlineFont = BobFont::ttf_outline_22;
		if (ttfFont == BobFont::ttf_23)outlineFont = BobFont::ttf_outline_23;
		if (ttfFont == BobFont::ttf_24)outlineFont = BobFont::ttf_outline_24;
		if (ttfFont == BobFont::ttf_25)outlineFont = BobFont::ttf_outline_25;
		if (ttfFont == BobFont::ttf_26)outlineFont = BobFont::ttf_outline_26;
		if (ttfFont == BobFont::ttf_27)outlineFont = BobFont::ttf_outline_27;
		if (ttfFont == BobFont::ttf_28)outlineFont = BobFont::ttf_outline_28;
		if (ttfFont == BobFont::ttf_29)outlineFont = BobFont::ttf_outline_29;
		if (ttfFont == BobFont::ttf_30)outlineFont = BobFont::ttf_outline_30;
		if (ttfFont == BobFont::ttf_31)outlineFont = BobFont::ttf_outline_31;
		if (ttfFont == BobFont::ttf_32)outlineFont = BobFont::ttf_outline_32;
		if (ttfFont == BobFont::ttf_48)outlineFont = BobFont::ttf_outline_48;
		if (ttfFont == BobFont::ttf_64)outlineFont = BobFont::ttf_outline_64;

		int OUTLINE_SIZE = 1;
		// render text and text outline 
		
		BobColor outlineBobColor = BobColor(*textColor);
		outlineBobColor.darker();
		outlineBobColor.darker();
		SDL_Color outlineColor = { (Uint8)outlineBobColor.ri() ,(Uint8)outlineBobColor.gi(),(Uint8)outlineBobColor.bi(),(Uint8)outlineBobColor.ai() };
		surface = TTF_RenderText_Blended(outlineFont, this->text.c_str(), outlineColor);
		SDL_Surface *fg_surface = TTF_RenderText_Blended(ttfFont, this->text.c_str(), textSDLColor);
		SDL_Rect rect = { OUTLINE_SIZE, OUTLINE_SIZE, fg_surface->w, fg_surface->h };
		
		// blit text onto its outline 
		SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(fg_surface, NULL, surface, &rect);
		SDL_FreeSurface(fg_surface);

		if (surface == NULL || surface == nullptr)
		{
			log.error("surface is null");
		}

		this->width = fg_surface->w + OUTLINE_SIZE * 2;
		this->height = fg_surface->h + OUTLINE_SIZE * 2;

		//another way
		//TTF_SetFontOutline(font_outline, 2);
		//SDL_Color white = { 0xFF, 0xFF, 0xFF };
		//SDL_Color black = { 0x00, 0x00, 0x00 };
		//SDL_Surface *black_text_surface = TTF_RenderText_Blended(font_outline, text, black);
		//SDL_Surface *white_text_surface = TTF_RenderText_Blended(font, text,white);
		//SDL_TextureID black_text = SDL_CreateTextureFromSurface(0,black_text_surface);
		//SDL_TextureID white_text = SDL_CreateTextureFromSurface(0,white_text_surface);
		//SDL_Rect black_rect = { x, y, black_text_surface->w,black_text_surface->h };
		//SDL_Rect white_rect = { x + 2, y + 2, white_text_surface->w,white_text_surface->h };
		//SDL_RenderCopy(black_text, NULL, &black_rect);
		//SDL_RenderCopy(white_text, NULL, &white_rect);
		//SDL_FreeSurface(black_text_surface); SDL_FreeSurface(white_text_surface);
		//SDL_DestroyTexture(black_text); SDL_DestroyTexture(white_text);
	}
	else
	{
		if (textBGColor != BobColor::clear)surface = TTF_RenderText_Shaded(ttfFont, this->text.c_str(), textSDLColor, bgSDLColor);
		else surface = TTF_RenderText_Blended(ttfFont, this->text.c_str(), textSDLColor);// , bgSDLColor);

		if (surface == NULL || surface == nullptr)
		{
			log.error("surface is null");
		}

		this->width = surface->w;
		this->height = surface->h;

	}




	this->texture = GLUtils::loadTextureFromSurface("Caption" + to_string(rand()) + to_string(rand()), surface);
	SDL_FreeSurface(surface);

	this->texWidth = texture->getTextureWidth();
	this->texHeight = texture->getTextureHeight();

	this->initialized = true;
}



//=========================================================================================================================
void Caption::init(Engine* g, float screenX, float screenY, long long ticks, const string& text, BobFont* font, BobColor* textColor, BobColor* textAAColor, BobColor* textBGColor, RenderOrder layer, float scale, int maxWidth, Entity* entity, Area* area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines)
{//=========================================================================================================================
	this->e = g;

	this->initialized = false;

	//get length
	this->textCharacterLength = (int)text.length();
	this->text = text;
	this->screenX = screenX;
	this->screenY = screenY;
	this->layer = layer;
	this->scale = scale;
	this->ticksToRemain = ticks;
	this->font = font;

	this->centerTextOnMultipleLines = centerTextOnMultipleLines;


	this->actionCaptionType = ActionManager::ACTIONCAPTIONTYPE_NONE;
	this->entity = entity;
	this->area = area;
	this->fadeLetterColorTowardsTop = fadeLetterColorTowardsTop;
	this->entityXWhenCreated = 0;
	this->entityYWhenCreated = 0;

	setEntity(entity);


	//handle fixed positions
	if (screenX < 0)
	{
		this->fixedPosition = (int)(screenX);
	}


	//TODO: width presets
	//WIDTH_FULL_SCREEN/getScale*2 (default 2x getScale, 0.5f getScale will be actual 1x pixels)
	//WIDTH_HALF_SCREEN/getScale*2
	//WIDTH_QUARTER_SCREEN/getScale*2
	//if it doesn't fit, just split where necessary
	//if preferred width is 0 then put it all on a single line, unless it doesn't fit.
	if (maxWidth == 0 || maxWidth == -1)
	{
		this->maxWidth = (int)(GLUtils::getViewportWidth() / 2 / scale);
	}
	else
	{
		this->maxWidth = (int)(maxWidth); //TODO: experiment and see if i want this /getScale
	}


	setTextColor(textColor, textAAColor, textBGColor);


	increaseMaxWidthToLongestWord();
	calculateTextureWidthAndHeightByParsingEachLine();

	if (width > this->maxWidth)
	{
		width = this->maxWidth;
	}

	//-----------------------------
	//allocate the indexed gfx data array, buffer, and texture
	//-----------------------------

	this->texWidth = Math::getClosestPowerOfTwo(width);
	this->texHeight = Math::getClosestPowerOfTwo(height);


	if (texture != nullptr)
	{
		texture->release();
		texture = nullptr;

	}



	//textureByteArray = (u8*)malloc(sizeof(u8)*texWidth * texHeight * 4);
	textureByteArray = new u8[texWidth * texHeight * 4];


	for (int i = 0; i < texWidth * texHeight; i++)
	{
		textureByteArray[(i * 4) + 0] = 0;
		textureByteArray[(i * 4) + 1] = 0;
		textureByteArray[(i * 4) + 2] = 0;
		textureByteArray[(i * 4) + 3] = 0; //255 for debug
	}


	bool debug = true;
	if (debug == true)
	{
		for (int i = 0; i < texWidth * texHeight; i++)
		{
			textureByteArray[(i * 4) + 0] = 255;
			textureByteArray[(i * 4) + 1] = 0;
			textureByteArray[(i * 4) + 2] = 255;
			textureByteArray[(i * 4) + 3] = 255; //255 for debug
		}

		for (int x = 0; x < (maxWidth) && x < texWidth; x++)
		{
			for (int y = 0; y < (height); y++)
			{
				textureByteArray[(((y * texWidth) + x) * 4) + 0] = 0;
				textureByteArray[(((y * texWidth) + x) * 4) + 1] = 255;
				textureByteArray[(((y * texWidth) + x) * 4) + 2] = 0;
				textureByteArray[(((y * texWidth) + x) * 4) + 3] = 255; //255 for debug
			}
		}

		for (int x = 0; x < (longestLineWidth); x++)
		{
			for (int y = 0; y < (height); y++)
			{
				textureByteArray[(((y * texWidth) + x) * 4) + 0] = 0;
				textureByteArray[(((y * texWidth) + x) * 4) + 1] = 0;
				textureByteArray[(((y * texWidth) + x) * 4) + 2] = 255; //255 for debug
				textureByteArray[(((y * texWidth) + x) * 4) + 3] = 255;
			}
		}
	}


	drawText();


	this->texture = GLUtils::getTextureFromData("Caption"+to_string(rand()) + to_string(rand()), texWidth, texHeight, textureByteArray);
	delete[] textureByteArray;
	textureByteArray = nullptr;


	this->initialized = true;
}


void Caption::render()
{ //=========================================================================================================================


	if (visible == false)return;
	float tx0 = 0.0f;
	float tx1 = 1.0f;
	float ty0 = 0.0f;
	float ty1 = 1.0f;

	float x0 = 0;
	float x1 = 100;
	float y0 = 0;
	float y1 = 100;

	tx0 = 0.0f;
	tx1 = (float)(width) / (float)(texWidth);
	ty0 = 0.0f;
	ty1 = (float)(height) / (float)(texHeight);

	x0 = (float)((int)(screenX));
	x1 = (float)((int)((screenX) + (width * scale)));
	y0 = (float)((int)(screenY));
	y1 = (float)((int)((screenY) + (height * scale)));


	int filter = 0;
	if (scale == 1.0f || scale == 2.0f)//|| scale == 0.5f)
	{
		filter = GLUtils::FILTER_FBO_NEAREST_NO_MIPMAPPING;
	}
	else
	{
		filter = GLUtils::FILTER_FBO_LINEAR_NO_MIPMAPPING;
	}

	if (font!=nullptr && font->outlined && scale == 0.5f)
	{
		filter = GLUtils::FILTER_FBO_LINEAR_NO_MIPMAPPING;
	}

	GLUtils::drawTexture(texture, tx0, tx1, ty0, ty1, x0, x1, y0, y1, alpha, filter);
}


void Caption::increaseMaxWidthToLongestWord()
{ //=========================================================================================================================

	//-----------------------------
	//go through string word by word, checking length of each word against the set width.
	//if a word won't fit, then we must increase the set width to fit that word.
	//-----------------------------

	int position = 0;

	while (position < textCharacterLength)
	{
		//skip over newlines
		if (BobFont::isCurrentPositionANewline(text, position) == true)
		{
			//skip over <NEWLINE> and <NEXTLINE> and <.>
			if (text[position] == '<')
			{
				while (text[position] != '>')
				{
					position++;
				}
			}

			position++; //skip '\n' or '>'
			lines++;
			continue;
		}

		//skip over over tags
		if (text[position] == '<')
		{
			while (text[position] != '>')
			{
				position++;
			}
			position++; //skip '>'
			continue;
		}

		int nextWordLength = BobFont::getNextWordLength(text, position, font);

		if (text[position] == ' ')
		{
			nextWordLength -= 3; //skip the space (3 + 1)
			//if(font_id!=TM.FONT_OUTLINED_ID)
			nextWordLength--;
		}

		//-----------------------------
		//if any word is greater than set width, increase set width to word size
		//-----------------------------
		if (nextWordLength + 1 > maxWidth)
		{
			maxWidth = nextWordLength + 1; //for the space at the beginning
		}

		//-----------------------------
		//skip next word, as we've added its length and we need to jump forward in the string
		//-----------------------------
		position = skipNextWord(position);
	}
}

int Caption::skipNextWord(int position)
{ //=========================================================================================================================
	int nextWordPosition = position;

	while (nextWordPosition < textCharacterLength && (text[nextWordPosition] != ' ' || nextWordPosition == position) && BobFont::isCurrentPositionANewline(text, nextWordPosition) == false) //if it's the start of the string or it's not a space
	{
		//we should be starting on a space or the beginning of the test. include the starting space, up to the next space
		//skip over tags
		while (text[nextWordPosition] == '<')
		{
			int x = 0;
			while (nextWordPosition + x < textCharacterLength && text[nextWordPosition + x] != '>')
			{
				x++;
			}
			nextWordPosition += x;
		}

		nextWordPosition++;
	}

	return nextWordPosition;
}

int Caption::getCurrentLineLength(int position)
{ //=========================================================================================================================

	int currentLineWidth = 1; //for the space at the beginning

	while (position < textCharacterLength)
	{
		//-----------------------------
		//skip over newlines
		//-----------------------------
		if (BobFont::isCurrentPositionANewline(text, position) == true)
		{
			//skip over <NEWLINE> and <NEXTLINE> and <.>
			if (text[position] == '<')
			{
				while (text[position] != '>')
				{
					position++;
				}
			}

			position++; //skip '\n' or '>'

			return currentLineWidth;
		}

		//-----------------------------
		//skip over other tags
		//-----------------------------
		if (text[position] == '<')
		{
			while (text[position] != '>')
			{
				position++;
			}
			position++; //skip '>'
			continue;
		}

		int nextWordLength = BobFont::getNextWordLength(text, position, font);

		//-----------------------------
		//if the next word will fit within the set width, add it
		//-----------------------------
		if (currentLineWidth + nextWordLength <= maxWidth)
		{
			currentLineWidth += nextWordLength;
		}
		else
		{
			return currentLineWidth;
		}


		//-----------------------------
		//skip next word, as we've added its length and we need to jump forward in the string
		//-----------------------------
		position = skipNextWord(position);
	}

	return currentLineWidth;
}

void Caption::calculateTextureWidthAndHeightByParsingEachLine()
{ //=========================================================================================================================


	//-----------------------------
	//go through string word by word, checking length of each line against the set width.
	//find out how many lines we will need so we can set the graphics array size accordingly.
	//check for newlines and tags as well
	//-----------------------------

	lines = 1; //we are on the first line
	longestLineWidth = 0;

	{
		int position = 0;
		int currentLineWidth = 1; //for the space at the beginning

		while (position < textCharacterLength)
		{
			//skip over newlines
			if (BobFont::isCurrentPositionANewline(text, position) == true)
			{
				//skip over <NEWLINE> and <NEXTLINE> and <.>
				if (text[position] == '<')
				{
					while (text[position] != '>')
					{
						position++;
					}
				}

				position++; //skip '\n' or '>'
				lines++;
				currentLineWidth = 1;
				continue;
			}

			//skip over other tags
			if (text[position] == '<')
			{
				while (text[position] != '>')
				{
					position++;
				}
				position++; //skip '>'
				continue;
			}

			int nextWordLength = BobFont::getNextWordLength(text, position, font);

			//-----------------------------
			//if the next word will fit within the set width, add it
			//-----------------------------
			if (currentLineWidth + nextWordLength <= maxWidth)
			{
				currentLineWidth += nextWordLength;
			}
			else //add it to the next line
			{
				if (text[position] == ' ')
				{
					nextWordLength -= 3; //skip the space (3 + 1)
					//if(font_id!=TM.FONT_OUTLINED_ID)
					nextWordLength--;
				}

				lines++;
				currentLineWidth = nextWordLength + 1; //for the space at the beginning
			}

			//-----------------------------
			//track longest line, make array size based on this
			//-----------------------------
			if (currentLineWidth > longestLineWidth)
			{
				longestLineWidth = currentLineWidth;
			}


			//-----------------------------
			//skip next word, as we've added its length and we need to jump forward in the string
			//-----------------------------
			position = skipNextWord(position);
		}
	}

	//-----------------------------
	//now temp_position should be at the end of the string
	//-----------------------------
	int maxCharHeight = 0;
	if (font != nullptr)maxCharHeight = font->maxCharHeight;
	else
	{
		log.error("calculateTextureWidthAndHeightByParsingEachLine font is null!");
	}

	width = longestLineWidth;
	height = (maxCharHeight + 2) * (lines);

	//DebugConsole.add("Caption longest line pixel width: " + caption_width);
	//DebugConsole.add("Caption lines: " + lines);
}

void Caption::drawText()
{ //=========================================================================================================================

	//-----------------------------
	//fill the indexed gfx data with getText
	//-----------------------------

	this->xInLine = 0;
	this->line = 0;


	int position = 0;

	while (position < textCharacterLength)
	{
		if (xInLine == 0)
		{
			//draw the space at the beginning
			drawBlankColumn();
			xInLine++;

			if (centerTextOnMultipleLines)
			{
				//get size of line remaining
				//see how many words we can fit into it
				//get the length of those words

				int lineWidthOnThisLine = getCurrentLineLength(position);

				//skip (width - length) / 2 space before start drawing
				if (lineWidthOnThisLine < maxWidth)
				{
					int leftover = maxWidth - lineWidthOnThisLine;

					for (int i = 0; i < leftover / 2 - 1; i++)
					{
						drawBlankColumn();
						xInLine++;
					}
				}
			}
		}


		//check each word length and start a new line if it is too long to fit
		if (position == 0 || text[position] == ' ') //if we're on a space
		{
			int nextWordLength = BobFont::getNextWordLength(text, position, font);

			if (xInLine + nextWordLength > maxWidth) //if the next word won't fit in the remaining space
			{
				//skip the space on the newline
				if (text[position] == ' ')
				{
					position++;
				}

				line++;
				xInLine = 0;
				continue;
			}
		}

		if (BobFont::isCurrentPositionANewline(text, position) == true)
		{
			//skip over tags here
			if (text[position] == '<')
			{
				while (text[position] != '>')
				{
					position++;
				}
			}

			//now we are on '>'
			position++; //skip the '>'

			line++;
			xInLine = 0;
			continue;
		}


		if (text[position] == '<')
		{
			position++;
			int optionLength = 0;
			while (text[position + optionLength] != '>' && position + optionLength < textCharacterLength)
			{
				optionLength++;
			}

			parseOptions(text.substr(position, optionLength));

			position += optionLength;

			//string position is now on '>'
			position++; //skip the '>'

			continue;
		}


		int i = BobFont::getFontIndexForChar(text[position]);
		drawLetter(i);
		position++;
	}
}

void Caption::parseOptions(const string& optionBuffer)
{ //=========================================================================================================================

	if (optionBuffer.compare("BLACK") == 0)
	{
		textBGColor = BobColor::white;
		textColor = BobColor::black;
		textAAColor = BobColor::lightGray;
	}
	else
	{
		if (optionBuffer.compare("WHITE") == 0)
		{
			textBGColor = BobColor::black;
			textColor = BobColor::white;
			textAAColor = BobColor::gray;
		}
		else
		{
			if (optionBuffer.compare("GRAY") == 0)
			{
				textColor = BobColor::gray;
				if (textBGColor == BobColor::black)
				{
					textAAColor = BobColor::darkGray;
				}
				else if (textBGColor == BobColor::white)
				{
					textAAColor = BobColor::lightGray;
				}
			}
			else
			{
				if (optionBuffer.compare("RED") == 0)
				{
					textColor = BobColor::red;
					if (textBGColor == BobColor::black)
					{
						textAAColor = BobColor::darkRed;
					}
					else if (textBGColor == BobColor::white)
					{
						textAAColor = BobColor::lightRed;
					}
				}
				else
				{
					if (optionBuffer.compare("ORANGE") == 0)
					{
						textColor = BobColor::orange;
						if (textBGColor == BobColor::black)
						{
							textAAColor = BobColor::darkOrange;
						}
						else if (textBGColor == BobColor::white)
						{
							textAAColor = BobColor::lightOrange;
						}
					}
					else
					{
						if (optionBuffer.compare("YELLOW") == 0)
						{
							textColor = BobColor::yellow;
							if (textBGColor == BobColor::black)
							{
								textAAColor = BobColor::darkYellow;
							}
							else if (textBGColor == BobColor::white)
							{
								textAAColor = BobColor::lightYellow;
							}
						}
						else
						{
							if (optionBuffer.compare("GREEN") == 0)
							{
								textColor = BobColor::green;
								if (textBGColor == BobColor::black)
								{
									textAAColor = BobColor::darkGreen;
								}
								else if (textBGColor == BobColor::white)
								{
									textAAColor = BobColor::lightGreen;
								}
							}
							else
							{
								if (optionBuffer.compare("BLUE") == 0)
								{
									textColor = BobColor::blue;
									if (textBGColor == BobColor::black)
									{
										textAAColor = BobColor::darkBlue;
									}
									else if (textBGColor == BobColor::white)
									{
										textAAColor = BobColor::lightBlue;
									}
								}
								else
								{
									if (optionBuffer.compare("PURPLE") == 0)
									{
										textColor = BobColor::purple;
										if (textBGColor == BobColor::black)
										{
											textAAColor = BobColor::darkPurple;
										}
										else if (textBGColor == BobColor::white)
										{
											textAAColor = BobColor::lightPurple;
										}
									}
									else
									{
										if (optionBuffer.compare("PINK") == 0)
										{
											textColor = BobColor::pink;
											if (textBGColor == BobColor::black)
											{
												textAAColor = BobColor::darkPink;
											}
											else if (textBGColor == BobColor::white)
											{
												textAAColor = BobColor::lightPink;
											}
										}
										else
										{
											if (optionBuffer.compare("BGBLACK") == 0)
											{
												textBGColor = BobColor::black;
												//TODO: if(textColor==COLOR)textAAColor=DARKCOLOR;
											}
											else
											{
												if (optionBuffer.compare("BGWHITE") == 0)
												{
													textBGColor = BobColor::white;
													//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
												}
												else
												{
													if (optionBuffer.compare("BGCLEAR") == 0)
													{
														textBGColor = BobColor::clear;
														//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
													}
													else
													{
														Console::debug(string("Unknown getText tag: ") + optionBuffer);
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	//TODO: handle other useful tags
}

int Caption::getLetterPixelColor(int letterIndex, int y, int xInLetter, bool blank)
{ //=========================================================================================================================

	if (blank == true)
	{
		return 0;
	}

	int blockHeight = 0;
	int blockWidth = 0;
	if (font != nullptr)blockHeight = font->blockHeight;
	if (font != nullptr)blockWidth = font->blockWidth;

	int index = BobFont::getFontPixelValueAtIndex((letterIndex * blockHeight * blockWidth) + (y * blockWidth) + xInLetter, font);

	return index;
}

void Caption::setPixel(int index, BobColor* c)
{ //=========================================================================================================================

	if (c == nullptr)
	{
		log.error("setPixel Color c was null, should never happen!");
		return;
	}

	
	textureByteArray[index + 0] = static_cast<u8>(c->ri());
	textureByteArray[index + 1] = static_cast<u8>(c->gi());
	textureByteArray[index + 2] = static_cast<u8>(c->bi());
	textureByteArray[index + 3] = static_cast<u8>(c->ai());
	


}


//=========================================================================================================================
float Caption::getAlphaTo()
{//=========================================================================================================================
	return alphaTo;
}


//=========================================================================================================================
float Caption::getAlpha()
{//=========================================================================================================================
	return alpha;
}


//=========================================================================================================================
void Caption::setAlphaTo(float a)
{//=========================================================================================================================
	if (beingDeletedWhenAlphaHitsZero == false)
	{
		alphaTo = a;
	}
}


//=========================================================================================================================
void Caption::setAlphaImmediately(float a)
{//=========================================================================================================================
	alpha = a;
}


//=========================================================================================================================
float Caption::getWidth()
{//=========================================================================================================================
	return width * scale;
}

//=========================================================================================================================
int Caption::reduceHeightByOne()
{//=========================================================================================================================

	if (ttfFont == nullptr)return 0;

	if (ttfFont == BobFont::ttf_6)	{return 6;							   }
	if (ttfFont == BobFont::ttf_7)	{ttfFont = BobFont::ttf_6;	setText(text, true); return 6; }
	if (ttfFont == BobFont::ttf_8)	{ttfFont = BobFont::ttf_7;	setText(text, true); return 7; }
	if (ttfFont == BobFont::ttf_9)	{ttfFont = BobFont::ttf_8;	setText(text, true); return 8; }
	if (ttfFont == BobFont::ttf_10)	{ttfFont = BobFont::ttf_9;	setText(text, true); return 9; }
	if (ttfFont == BobFont::ttf_11)	{ttfFont = BobFont::ttf_10;	setText(text, true); return 10; }
	if (ttfFont == BobFont::ttf_12)	{ttfFont = BobFont::ttf_11;	setText(text, true); return 11; }
	if (ttfFont == BobFont::ttf_13)	{ttfFont = BobFont::ttf_12;	setText(text, true); return 12; }
	if (ttfFont == BobFont::ttf_14)	{ttfFont = BobFont::ttf_13;	setText(text, true); return 13; }
	if (ttfFont == BobFont::ttf_15)	{ttfFont = BobFont::ttf_14;	setText(text, true); return 14; }
	if (ttfFont == BobFont::ttf_16)	{ttfFont = BobFont::ttf_15;	setText(text, true); return 15; }
	if (ttfFont == BobFont::ttf_17)	{ttfFont = BobFont::ttf_16;	setText(text, true); return 16; }
	if (ttfFont == BobFont::ttf_18)	{ttfFont = BobFont::ttf_17;	setText(text, true); return 17; }
	if (ttfFont == BobFont::ttf_19)	{ttfFont = BobFont::ttf_18;	setText(text, true); return 18; }
	if (ttfFont == BobFont::ttf_20)	{ttfFont = BobFont::ttf_19;	setText(text, true); return 19; }
	if (ttfFont == BobFont::ttf_21)	{ttfFont = BobFont::ttf_20;	setText(text, true); return 20; }
	if (ttfFont == BobFont::ttf_22)	{ttfFont = BobFont::ttf_21;	setText(text, true); return 21; }
	if (ttfFont == BobFont::ttf_23)	{ttfFont = BobFont::ttf_22;	setText(text, true); return 22; }
	if (ttfFont == BobFont::ttf_24)	{ttfFont = BobFont::ttf_23;	setText(text, true); return 23; }
	if (ttfFont == BobFont::ttf_25)	{ttfFont = BobFont::ttf_24;	setText(text, true); return 24; }
	if (ttfFont == BobFont::ttf_26)	{ttfFont = BobFont::ttf_25;	setText(text, true); return 25; }
	if (ttfFont == BobFont::ttf_27)	{ttfFont = BobFont::ttf_26;	setText(text, true); return 26; }
	if (ttfFont == BobFont::ttf_28)	{ttfFont = BobFont::ttf_27;	setText(text, true); return 27; }
	if (ttfFont == BobFont::ttf_29)	{ttfFont = BobFont::ttf_28;	setText(text, true); return 28; }
	if (ttfFont == BobFont::ttf_30)	{ttfFont = BobFont::ttf_29;	setText(text, true); return 29; }
	if (ttfFont == BobFont::ttf_31)	{ttfFont = BobFont::ttf_30;	setText(text, true); return 30; }
	if (ttfFont == BobFont::ttf_32)	{ttfFont = BobFont::ttf_31;	setText(text, true); return 31; }
	if (ttfFont == BobFont::ttf_48)	{ttfFont = BobFont::ttf_32;	setText(text, true); return 32; }
	if (ttfFont == BobFont::ttf_64)	{ttfFont = BobFont::ttf_48;	setText(text, true); return 48; }
								

	
	return 0;
	


}
//=========================================================================================================================
int Caption::increaseHeightByOne()
{//=========================================================================================================================

	if (ttfFont == nullptr)return 0;

	if (ttfFont == BobFont::ttf_6)	{ttfFont = BobFont::ttf_7;	setText(text, true);	return 7; 	 }
	if (ttfFont == BobFont::ttf_7)	{ttfFont = BobFont::ttf_8;	setText(text, true);	return 8; 	 }
	if (ttfFont == BobFont::ttf_8)	{ttfFont = BobFont::ttf_9;	setText(text, true);	return 9; 	 }
	if (ttfFont == BobFont::ttf_9)	{ttfFont = BobFont::ttf_10;	setText(text, true);	return 10;	 }
	if (ttfFont == BobFont::ttf_10)	{ttfFont = BobFont::ttf_11;	setText(text, true);	return 11;	 }
	if (ttfFont == BobFont::ttf_11)	{ttfFont = BobFont::ttf_12;	setText(text, true);	return 12;	 }
	if (ttfFont == BobFont::ttf_12)	{ttfFont = BobFont::ttf_13;	setText(text, true);	return 13;	 }
	if (ttfFont == BobFont::ttf_13)	{ttfFont = BobFont::ttf_14;	setText(text, true);	return 14;	 }
	if (ttfFont == BobFont::ttf_14)	{ttfFont = BobFont::ttf_15;	setText(text, true);	return 15;	 }
	if (ttfFont == BobFont::ttf_15)	{ttfFont = BobFont::ttf_16;	setText(text, true);	return 16;	 }
	if (ttfFont == BobFont::ttf_16)	{ttfFont = BobFont::ttf_17;	setText(text, true);	return 17;	 }
	if (ttfFont == BobFont::ttf_17)	{ttfFont = BobFont::ttf_18;	setText(text, true);	return 18;	 }
	if (ttfFont == BobFont::ttf_18)	{ttfFont = BobFont::ttf_19;	setText(text, true);	return 19;	 }
	if (ttfFont == BobFont::ttf_19)	{ttfFont = BobFont::ttf_20;	setText(text, true);	return 20;	 }
	if (ttfFont == BobFont::ttf_20)	{ttfFont = BobFont::ttf_21;	setText(text, true);	return 21;	 }
	if (ttfFont == BobFont::ttf_21)	{ttfFont = BobFont::ttf_22;	setText(text, true);	return 22;	 }
	if (ttfFont == BobFont::ttf_22)	{ttfFont = BobFont::ttf_23;	setText(text, true);	return 23;	 }
	if (ttfFont == BobFont::ttf_23)	{ttfFont = BobFont::ttf_24;	setText(text, true);	return 24;	 }
	if (ttfFont == BobFont::ttf_24)	{ttfFont = BobFont::ttf_25;	setText(text, true);	return 25;	 }
	if (ttfFont == BobFont::ttf_25)	{ttfFont = BobFont::ttf_26;	setText(text, true);	return 26;	 }
	if (ttfFont == BobFont::ttf_26)	{ttfFont = BobFont::ttf_27;	setText(text, true);	return 27;	 }
	if (ttfFont == BobFont::ttf_27)	{ttfFont = BobFont::ttf_28;	setText(text, true);	return 28;	 }
	if (ttfFont == BobFont::ttf_28)	{ttfFont = BobFont::ttf_29;	setText(text, true);	return 29;	 }
	if (ttfFont == BobFont::ttf_29)	{ttfFont = BobFont::ttf_30;	setText(text, true);	return 30;	 }
	if (ttfFont == BobFont::ttf_30)	{ttfFont = BobFont::ttf_31;	setText(text, true);	return 31;	 }
	if (ttfFont == BobFont::ttf_31)	{ttfFont = BobFont::ttf_32;	setText(text, true);	return 32;	 }
	if (ttfFont == BobFont::ttf_32)	{ttfFont = BobFont::ttf_48;	setText(text, true);	return 48;	 }
	if (ttfFont == BobFont::ttf_48)	{ttfFont = BobFont::ttf_64;	setText(text, true);	return 64;	 }
	if (ttfFont == BobFont::ttf_64)	{return 64;								 }
								

	return 0;

}

//=========================================================================================================================
float Caption::getHeight()
{//=========================================================================================================================
	return height * scale;
}


void Caption::drawBlankColumn()
{ //=========================================================================================================================
	drawColumn(0, 0, true);
}


//int timesbeenhere = 0;

void Caption::drawColumn(int xInLetter, int letterIndex, bool blank)
{ //=========================================================================================================================


	//timesbeenhere++;


	int y;
	int maxCharHeight = 0;
	bool outlined = false;

	if (font != nullptr)maxCharHeight = font->maxCharHeight;
	if (font != nullptr)outlined = font->outlined;

	for (y = 0; y < maxCharHeight + 2; y++)
	{
		int index = 0;

		//set the top pixel black
		if (y == 0)
		{
			index = getLetterPixelColor(letterIndex, y - 1, xInLetter, true);
		}
		else
		{
			index = getLetterPixelColor(letterIndex, y - 1, xInLetter, blank);
		}

		BobColor* c = nullptr;

		if (index == 0)
		{
			c = new BobColor(*textBGColor);
		}
		else if (index == 1)
		{
			c = new BobColor(*textColor);
		}
		else if (index == 2)
		{
			c = new BobColor(*textAAColor);
		}
		else if (index > 2) //additional aa pixels, use the color value to set the opacity
		{
			//get the gray color from the getText palette
			int byte1 = (int)(BobFont::font_Palette_ByteArray[index * 2 + 0] & 255);
			//int byte2 = (int)(BobFont::font_Palette_ByteArray[index * 2 + 1] & 255);
			//int abgr1555 = (byte2 << 8) + byte1;
			int r = 255 - (int)((((byte1 & 31)) / 32.0f) * 255.0f);
			//int r = 255-(int)((((byte1&0b00011111))/32.0f)*255.0f);
			//Color gray = new Color(b,b,b);


			int a = r; //gray.getRed();
			if (a < 0)
			{
				a = 0;
			}

			a *= textAAColor->ai();

			//Color* tc = textColor;
			c = new BobColor(textColor->ri(), textColor->gi(), textColor->bi(), a);
		}


		if (fadeLetterColorTowardsTop)
		{
			if ((index > 0) && y < maxCharHeight * 0.75f && (index != 2 || outlined == false))
			{
				int r = (int)(min(255, (int)(c->ri() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				int g = (int)(min(255, (int)(c->gi() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				int b = (int)(min(255, (int)(c->bi() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				int a = c->ai();

				if (c != nullptr)delete c;
				c = new BobColor(r, g, b, a);
			}
		}


		//draw each pixel 4 times (2x getScale)
		//for(int yy=0;yy<2;yy++)
		//for(int xx=0;xx<2;xx++)
		{
			int lineIndex = (texWidth * line * ((maxCharHeight + 2)));
			int xIndex = ((xInLine));
			int yIndex = (texWidth * ((y)));

			setPixel((lineIndex + yIndex + xIndex) * 4, c);
		}
		if (c != nullptr)
			delete c;
	}
}

void Caption::drawLetter(int letterIndex)
{ //=========================================================================================================================

	int letterWidth = BobFont::getCharWidth(letterIndex, font);

	int xInLetter = 0;
	for (xInLetter = 0; xInLetter < letterWidth; xInLetter++)
	{
		drawColumn(xInLetter, letterIndex, false);
		xInLine++;
	}

	//-----------------------------
	//insert space (blank column)
	//-----------------------------
	//if(font_id!=TM.FONT_OUTLINED_ID)
	{
		drawBlankColumn();
		xInLine++;
	}
}


//=========================================================================================================================
void Caption::updateScreenXY()
{//=========================================================================================================================

	//TODO: track how many captions are centered over sprite, make sure they aren't covering each other

	//-----------------------------
	//set getCaption screen x and y
	//-----------------------------
	if (fixedPosition == Caption::CENTERED_OVER_ENTITY)
	{
		//			if(entity!=null)
		{
			screenX = (float)floor(entity->getScreenLeft() + (entity->getWidth() * getCameraman()->getZoom() / 2.0f)) - (width * scale / 2.0f);//no g.zoom on getCaption width, they arent affected by zoom!


			int captionOverHeadOffset = 0;
			for (int i = getCaptionManager()->captionList->size() - 1; i >= 0; i--)
			{
				Caption* tempC = getCaptionManager()->captionList->get(i);
				if (tempC->fixedPosition == Caption::CENTERED_OVER_ENTITY)
				{
					if (tempC == this)break;

					captionOverHeadOffset += (int)((tempC->height + 2) * tempC->scale);
				}
			}

			screenY = (float)floor(entity->getScreenTop()) - (captionOverHeadOffset + (height + 2) * scale);
		}
	}
	else
	{
		if (fixedPosition == Caption::CENTERED_SCREEN)
		{
			screenX = (float)(((int)(GLUtils::getViewportWidth() / 2.0f)) - (int)((width * scale) / 2.0f));
			screenY = (float)((int)(GLUtils::getViewportHeight() / 2.0f));
		}
		else
		{
			if (fixedPosition == Caption::CENTERED_X)
			{
				screenX = (float)((int)(GLUtils::getViewportWidth() / 2.0f) - (int)((width * scale) / 2.0f));
			}
		}
	}

	//-----------------------------
	//don't let captions wrap offscreen
	//-----------------------------
	if (screenX + width * scale >= GLUtils::getViewportWidth())
	{
		screenX = (float)(GLUtils::getViewportWidth() - (int)(width * scale + 1));
	}
	if (screenX < 0)
	{
		screenX = 0;
	}

	///turned off for castroom
	//TODO: make this an option

	if (screenY >= GLUtils::getViewportHeight())
	{
		screenY = (float)(GLUtils::getViewportHeight());
	}

	if (screenY < 0)
	{
		screenY = 0;
	}
}


//=========================================================================================================================
void Caption::setToFadeOutAndBeDeleted()
{//=========================================================================================================================
	beingDeletedWhenAlphaHitsZero = true;
}


//=========================================================================================================================
void Caption::setToBeDeletedImmediately()
{//=========================================================================================================================
	beingDeletedWhenAlphaHitsZero = true;
	alpha = 0.0f;
	alphaTo = 0.0f;
}


//=========================================================================================================================
bool Caption::getBeingDeletedWhenFadeOutStatus()
{//=========================================================================================================================
	return beingDeletedWhenAlphaHitsZero;
	//TODO: do check to see if this is a managed caption or not, if it's not, throw a warning that it has to be manually deleted
}


//=========================================================================================================================
void Caption::update()
{//=========================================================================================================================


	int ticksPassed = 0;
	if (e != nullptr)
	{
		ticksPassed = e->engineTicksPassed();
	}
	else
	{
		ticksPassed = State::realWorldTicksPassed();
	}

	ticksAge += ticksPassed;

	updateScreenXY();

	//-----------------------------
	//delete if sprite moved
	//-----------------------------
	if (
        (
         ticksToRemain == 0
         ||
         ticksToRemain == Caption::DELETE_WHEN_MAIN_SPRITE_MOVES
        )
		&&
		(
			entity != nullptr
			&&
			(
				entity->getX() != entityXWhenCreated//and sprite has moved
				||
				entity->getY() != entityYWhenCreated
			)
		)
	)
	{
		beingDeletedWhenAlphaHitsZero = true;
	}


	if (beingDeletedWhenAlphaHitsZero == true)
	{
		alphaTo = 0.0f;
	}

	if (flashing && beingDeletedWhenAlphaHitsZero == false)
	{
		flashingTicksCount += e->engineTicksPassed();

		if (flashingTicksCount > flashingTicksPerFlash)
		{
			flashingTicksCount = 0;
		}

		if (flashingTicksCount < flashingTicksPerFlash / 2)
		{
			alpha = ((float)(flashingTicksCount) / ((float)(flashingTicksPerFlash) / 3.0f)) * alphaTo;
			if (alpha > alphaTo)
			{
				alpha = alphaTo;
			}
			if (alpha < 0.0f)
			{
				alpha = 0.0f;
			}
		}
		else
		{
			alpha = ((float)(flashingTicksPerFlash - flashingTicksCount) / ((float)(flashingTicksPerFlash) / 3.0f)) * alphaTo;

			if (alpha > alphaTo)
			{
				alpha = alphaTo;
			}
			if (alpha < 0.0f)
			{
				alpha = 0.0f;
			}
		}
	}
	else
	{
		//-----------------------------
		//do fade in/out
		//-----------------------------

		if (alpha != alphaTo)
		{
			if (alpha > alphaTo)
			{
				alpha -= 0.005f * ticksPassed;
				if (alpha < alphaTo)
				{
					alpha = alphaTo;
				}
			}

			if (alpha < alphaTo)
			{
				alpha += 0.005f * ticksPassed;
				if (alpha > alphaTo)
				{
					alpha = alphaTo;
				}
			}
		}
	}


	//-----------------------------
	//delete if delete is 1
	//-----------------------------
	if (beingDeletedWhenAlphaHitsZero == true && alpha == 0.0f)
	{
		alpha = 0.0f;

		if (texture != nullptr)
		{
			texture->release();
			texture = nullptr;
		}

		deleteMe = true;

		
	}
}


void Caption::setEntity(Entity* e)
{
	this->entity = e;

	if (e == nullptr && getPlayer() != nullptr)
	{
		this->entity = getPlayer();
	}

	if (this->entity != nullptr)
	{
		this->entityXWhenCreated = this->entity->getX();
		this->entityYWhenCreated = this->entity->getY();
	}
}

