
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
Caption::Caption(shared_ptr<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, shared_ptr<OKFont> font, shared_ptr<OKColor> textColor, shared_ptr<OKColor> textAAColor, shared_ptr<OKColor> textBGColor, RenderOrder layer, float scale, int maxWidth, shared_ptr<Entity> entity, shared_ptr<Area> area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines)
{//=========================================================================================================================
	init(g, fixedPosition, screenX, screenY, ticks, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
}
//=========================================================================================================================
Caption::Caption(shared_ptr<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, int fontSize, bool outline, shared_ptr<OKColor> textColor, shared_ptr<OKColor> textBGColor, RenderOrder layer, float scale, shared_ptr<Entity> entity, shared_ptr<Area> area)
{//=========================================================================================================================

	initTTF(g, fixedPosition, screenX, screenY, ticks, text, fontSize, textColor, textBGColor, layer, scale, entity, area, outline);
}

//=========================================================================================================================
Caption::Caption(shared_ptr<Engine> g, Position fixedPosition, float screenX, float screenY, int ticks, const string& text, int fontSize, bool outline, shared_ptr<OKColor> textColor, RenderOrder layer)
{//=========================================================================================================================

	initTTF(g, fixedPosition, screenX, screenY, ticks, text, fontSize, textColor, OKColor::clear, layer, 1, nullptr, nullptr, outline);
}
//=========================================================================================================================
void Caption::setText(const string& text, bool force)
{//=========================================================================================================================

	if (force == false && (text == this->text || (text=="" && this->text == " ")))
	{
		return;
	}


	if (texture != nullptr)
	{
		texture->release();
		//delete texture;
		texture = nullptr;
	}


	if (ttfFont != nullptr)initTTF(e, fixedPosition, screenX, screenY, ticksToRemain, text, fontSize, textColor, textBGColor, layer, scale, entity, area, outline);
	else init(e, fixedPosition, screenX, screenY, ticksToRemain, text, font, textColor, textAAColor, textBGColor, layer, scale, maxWidth, entity, area, fadeLetterColorTowardsTop, centerTextOnMultipleLines);
	
	updateScreenXY();
}

//=========================================================================================================================
shared_ptr<OKColor> Caption::getTextColor()
{//=========================================================================================================================
	return textColor;


}


//=========================================================================================================================
void Caption::setTextColor(shared_ptr<OKColor> fg, shared_ptr<OKColor> aa, shared_ptr<OKColor> bg)
{//=========================================================================================================================


	if ((fg!=nullptr && *fg == *this->textColor) && (bg!=nullptr && *bg == *this->textBGColor) && (font->outlined==true || aa == this->textAAColor))
	{
		return;
	}

	//-----------------------------
	//set color
	//-----------------------------

	//color 0 = bg color
	//color 1 = getText color
	//color 2 = antialiasing color

	shared_ptr<OKColor> tempFG = this->textColor;
	shared_ptr<OKColor> tempBG = this->textBGColor;
	shared_ptr<OKColor> tempAA = this->textAAColor;


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

		if (font->outlined == true) { tempAA = OKColor::black; }
		else
		if (tempBG == OKColor::white)
		{
			tempAA = make_shared<OKColor>(*fg);
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
			if (tempBG == OKColor::black) //||textBGColor==Color.CLEAR)
			{
				tempAA = make_shared<OKColor>(*fg);
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
				if (tempBG == OKColor::clear)
				{
					tempAA = make_shared<OKColor>((fg->rf()) * 255, (fg->gf()) * 255, (fg->bf()) * 255, (fg->af() / 2.0f)*255);
				}
			}
		}
	}

	if (initialized == true) //don't replace the getText if we haven't drawn the bitmap yet
	{
		if (*tempFG != *this->textColor || *tempBG != *this->textBGColor || (tempAA!=nullptr && *tempAA != *this->textAAColor)) //dont replace if the colors havent changed
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
void Caption::initTTF(shared_ptr<Engine> g, Position fixedPosition, float screenX, float screenY, long long ticks, const string& text, int fontSize, shared_ptr<OKColor> textColor, shared_ptr<OKColor> textBGColor, RenderOrder layer, float scale, shared_ptr<Entity> entity, shared_ptr<Area> area, bool outline)
{//=========================================================================================================================
	this->e = g;

	this->initialized = false;


	//get length
	this->textCharacterLength = (int)text.length();
	this->text = text;
	if (this->text.length() == 0)this->text = " ";

	this->screenX = screenX;
	this->screenY = screenY;
	this->layer = layer;
	this->scale = scale;
	this->ticksToRemain = ticks;
	
	this->fontSize = fontSize;

	this->actionCaptionType = ActionManager::ACTIONCAPTIONTYPE_NONE;
	this->entity = entity;
	this->area = area;

	this->entityXWhenCreated = 0;
	this->entityYWhenCreated = 0;

	setEntity(entity);


	//handle fixed positions
	//if (screenX < 0)
	{
		this->fixedPosition = fixedPosition;
	}


	if (texture != nullptr)
	{
		texture->release();
		//delete texture;
		texture = nullptr;
	}

	if (textBGColor == nullptr)textBGColor = OKColor::clear;
	setTextColor(textColor, textAAColor, textBGColor);


	

	

	shared_ptr<SDL_Surface*> surface = nullptr;


	shared_ptr<TTF_Font> outlineFont = nullptr;

	if (fontSize < 7)  { this->ttfFont = OKFont::ttf_6;  outlineFont = OKFont::ttf_outline_6;  this->fontSize = 6; }
	if (fontSize == 7)  { this->ttfFont = OKFont::ttf_7;  outlineFont = OKFont::ttf_outline_7;  }
	if (fontSize == 8)  { this->ttfFont = OKFont::ttf_8;  outlineFont = OKFont::ttf_outline_8;  }
	if (fontSize == 9)  { this->ttfFont = OKFont::ttf_9;  outlineFont = OKFont::ttf_outline_9;  }
	if (fontSize == 10) { this->ttfFont = OKFont::ttf_10; outlineFont = OKFont::ttf_outline_10; }
	if (fontSize == 11) { this->ttfFont = OKFont::ttf_11; outlineFont = OKFont::ttf_outline_11; }
	if (fontSize == 12) { this->ttfFont = OKFont::ttf_12; outlineFont = OKFont::ttf_outline_12; }
	if (fontSize == 13) { this->ttfFont = OKFont::ttf_13; outlineFont = OKFont::ttf_outline_13; }
	if (fontSize == 14) { this->ttfFont = OKFont::ttf_14; outlineFont = OKFont::ttf_outline_14; }
	if (fontSize == 15) { this->ttfFont = OKFont::ttf_15; outlineFont = OKFont::ttf_outline_15; }
	if (fontSize == 16) { this->ttfFont = OKFont::ttf_16; outlineFont = OKFont::ttf_outline_16; }
	if (fontSize == 17) { this->ttfFont = OKFont::ttf_17; outlineFont = OKFont::ttf_outline_17; }
	if (fontSize == 18) { this->ttfFont = OKFont::ttf_18; outlineFont = OKFont::ttf_outline_18; }
	if (fontSize == 19) { this->ttfFont = OKFont::ttf_19; outlineFont = OKFont::ttf_outline_19; }
	if (fontSize == 20) { this->ttfFont = OKFont::ttf_20; outlineFont = OKFont::ttf_outline_20; }
	if (fontSize == 21) { this->ttfFont = OKFont::ttf_21; outlineFont = OKFont::ttf_outline_21; }
	if (fontSize == 22) { this->ttfFont = OKFont::ttf_22; outlineFont = OKFont::ttf_outline_22; }
	if (fontSize == 23) { this->ttfFont = OKFont::ttf_23; outlineFont = OKFont::ttf_outline_23; }
	if (fontSize == 24) { this->ttfFont = OKFont::ttf_24; outlineFont = OKFont::ttf_outline_24; }
	if (fontSize == 25) { this->ttfFont = OKFont::ttf_25; outlineFont = OKFont::ttf_outline_25; }
	if (fontSize == 26) { this->ttfFont = OKFont::ttf_26; outlineFont = OKFont::ttf_outline_26; }
	if (fontSize == 27) { this->ttfFont = OKFont::ttf_27; outlineFont = OKFont::ttf_outline_27; }
	if (fontSize == 28) { this->ttfFont = OKFont::ttf_28; outlineFont = OKFont::ttf_outline_28; }
	if (fontSize == 29) { this->ttfFont = OKFont::ttf_29; outlineFont = OKFont::ttf_outline_29; }
	if (fontSize == 30) { this->ttfFont = OKFont::ttf_30; outlineFont = OKFont::ttf_outline_30; }
	if (fontSize == 31) { this->ttfFont = OKFont::ttf_31; outlineFont = OKFont::ttf_outline_31; }
	if (fontSize >= 32 && fontSize < 48) { this->ttfFont = OKFont::ttf_32; outlineFont = OKFont::ttf_outline_32; this->fontSize = 32; }
	if (fontSize >= 48 && fontSize < 64) { this->ttfFont = OKFont::ttf_48; outlineFont = OKFont::ttf_outline_48; this->fontSize = 48; }
	if (fontSize >= 64) { this->ttfFont = OKFont::ttf_64; outlineFont = OKFont::ttf_outline_64; this->fontSize = 64; }

	if (outline)this->outline = true;
	if (outline)
	{

		int OUTLINE_SIZE = 1;
		// render text and text outline 
		
		SDL_Color textSDLColor = { (Uint8)textColor->ri() ,(Uint8)textColor->gi(),(Uint8)textColor->bi(),(Uint8)textColor->ai() };

		OKColor outlineOKColor = OKColor(*textColor);
		outlineOKColor.darker();
		outlineOKColor.darker();
		SDL_Color outlineColor = { (Uint8)outlineOKColor.ri() ,(Uint8)outlineOKColor.gi(),(Uint8)outlineOKColor.bi(),(Uint8)outlineOKColor.ai() };
		surface = TTF_RenderText_Blended(outlineFont.get(), this->text.c_str(), outlineColor);
		shared_ptr<SDL_Surface*> fg_surface = TTF_RenderText_Blended(ttfFont.get(), this->text.c_str(), textSDLColor);
		SDL_Rect rect = { OUTLINE_SIZE, OUTLINE_SIZE, fg_surface->w, fg_surface->h };

		// blit text onto its outline 
		SDL_SetSurfaceBlendMode(fg_surface, SDL_BLENDMODE_BLEND);
		SDL_BlitSurface(fg_surface, NULL, surface, &rect);

		this->width = fg_surface->w + OUTLINE_SIZE * 2;
		this->height = fg_surface->h + OUTLINE_SIZE * 2;

		SDL_FreeSurface(fg_surface);

		if (surface == NULL || surface == nullptr)
		{
			log.error("surface is null");
		}



		//another way
		//TTF_SetFontOutline(font_outline, 2);
		//SDL_Color white = { 0xFF, 0xFF, 0xFF };
		//SDL_Color black = { 0x00, 0x00, 0x00 };
		//shared_ptr<SDL_Surface >black_text_surface = TTF_RenderText_Blended(font_outline, text, black);
		//shared_ptr<SDL_Surface >white_text_surface = TTF_RenderText_Blended(font, text,white);
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

		SDL_Color textSDLColor = { (Uint8)textColor->ri() ,(Uint8)textColor->gi(),(Uint8)textColor->bi(),(Uint8)textColor->ai() };
		SDL_Color bgSDLColor = { (Uint8)textBGColor->ri() ,(Uint8)textBGColor->gi(),(Uint8)textBGColor->bi(),(Uint8)textBGColor->ai() };

		surface = nullptr;
		if (textBGColor != OKColor::clear)surface = TTF_RenderText_Shaded(ttfFont.get(), this->text.c_str(), textSDLColor, bgSDLColor);
		else surface = TTF_RenderText_Blended(ttfFont.get(), this->text.c_str(), textSDLColor);// , bgSDLColor);

		this->width = surface->w;
		this->height = surface->h;

		if (surface == NULL || surface == nullptr)
		{
			log.error("surface is null");
		}

	}




	this->texture = GLUtils::loadTextureFromSurface("Caption" + to_string(rand()) + to_string(rand()), surface);
	SDL_FreeSurface(surface);

	this->texWidth = texture->getTextureWidth();
	this->texHeight = texture->getTextureHeight();

	this->initialized = true;
}



//=========================================================================================================================
void Caption::init(shared_ptr<Engine> g, Position fixedPosition, float screenX, float screenY, long long ticks, const string& text, shared_ptr<OKFont> font, shared_ptr<OKColor> textColor, shared_ptr<OKColor> textAAColor, shared_ptr<OKColor> textBGColor, RenderOrder layer, float scale, int maxWidth, shared_ptr<Entity> entity, shared_ptr<Area> area, bool fadeLetterColorTowardsTop, bool centerTextOnMultipleLines)
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
	//if (screenX < 0)
	{
		this->fixedPosition = (fixedPosition);
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
		delete texture;
		texture = nullptr;
	}

	if (textureByteArray != nullptr)
	{
		delete textureByteArray;
		textureByteArray = nullptr;
	}



	//textureByteArray->data() = (u8*)malloc(sizeof(u8)*texWidth * texHeight * 4);
	textureByteArray = make_shared<ByteArray>(texWidth * texHeight * 4);


	for (int i = 0; i < texWidth * texHeight; i++)
	{
		textureByteArray->data()[(i * 4) + 0] = 0;
		textureByteArray->data()[(i * 4) + 1] = 0;
		textureByteArray->data()[(i * 4) + 2] = 0;
		textureByteArray->data()[(i * 4) + 3] = 0; //255 for debug
	}


	bool debug = true;
	if (debug == true)
	{
		for (int i = 0; i < texWidth * texHeight; i++)
		{
			textureByteArray->data()[(i * 4) + 0] = 255;
			textureByteArray->data()[(i * 4) + 1] = 0;
			textureByteArray->data()[(i * 4) + 2] = 255;
			textureByteArray->data()[(i * 4) + 3] = 255; //255 for debug
		}

		for (int x = 0; x < (maxWidth) && x < texWidth; x++)
		{
			for (int y = 0; y < (height); y++)
			{
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 0] = 0;
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 1] = 255;
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 2] = 0;
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 3] = 255; //255 for debug
			}
		}

		for (int x = 0; x < (longestLineWidth); x++)
		{
			for (int y = 0; y < (height); y++)
			{
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 0] = 0;
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 1] = 0;
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 2] = 255; //255 for debug
				textureByteArray->data()[(((y * texWidth) + x) * 4) + 3] = 255;
			}
		}
	}


	drawText();


	this->texture = GLUtils::getTextureFromData("Caption"+to_string(rand()) + to_string(rand()), texWidth, texHeight, textureByteArray);
	delete textureByteArray;
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
	x1 = (float)((int)((screenX) +getWidth()));
	y0 = (float)((int)(screenY));
	y1 = (float)((int)((screenY) +getHeight()));


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
		if (OKFont::isCurrentPositionANewline(text, position) == true)
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

		int nextWordLength = OKFont::getNextWordLength(text, position, font);

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

	while (nextWordPosition < textCharacterLength && (text[nextWordPosition] != ' ' || nextWordPosition == position) && OKFont::isCurrentPositionANewline(text, nextWordPosition) == false) //if it's the start of the string or it's not a space
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
		if (OKFont::isCurrentPositionANewline(text, position) == true)
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

		int nextWordLength = OKFont::getNextWordLength(text, position, font);

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
			if (OKFont::isCurrentPositionANewline(text, position) == true)
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

			int nextWordLength = OKFont::getNextWordLength(text, position, font);

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
		log->error("calculateTextureWidthAndHeightByParsingEachLine font is null!");
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
			int nextWordLength = OKFont::getNextWordLength(text, position, font);

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

		if (OKFont::isCurrentPositionANewline(text, position) == true)
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


		int i = OKFont::getFontIndexForChar(text[position]);
		drawLetter(i);
		position++;
	}
}

void Caption::parseOptions(const string& optionBuffer)
{ //=========================================================================================================================

	if (optionBuffer.compare("BLACK") == 0)
	{
		textBGColor = OKColor::white;
		textColor = OKColor::black;
		textAAColor = OKColor::lightGray;
	}
	else
	{
		if (optionBuffer.compare("WHITE") == 0)
		{
			textBGColor = OKColor::black;
			textColor = OKColor::white;
			textAAColor = OKColor::gray;
		}
		else
		{
			if (optionBuffer.compare("GRAY") == 0)
			{
				textColor = OKColor::gray;
				if (textBGColor == OKColor::black)
				{
					textAAColor = OKColor::darkGray;
				}
				else if (textBGColor == OKColor::white)
				{
					textAAColor = OKColor::lightGray;
				}
			}
			else
			{
				if (optionBuffer.compare("RED") == 0)
				{
					textColor = OKColor::red;
					if (textBGColor == OKColor::black)
					{
						textAAColor = OKColor::darkRed;
					}
					else if (textBGColor == OKColor::white)
					{
						textAAColor = OKColor::lightRed;
					}
				}
				else
				{
					if (optionBuffer.compare("ORANGE") == 0)
					{
						textColor = OKColor::orange;
						if (textBGColor == OKColor::black)
						{
							textAAColor = OKColor::darkOrange;
						}
						else if (textBGColor == OKColor::white)
						{
							textAAColor = OKColor::lightOrange;
						}
					}
					else
					{
						if (optionBuffer.compare("YELLOW") == 0)
						{
							textColor = OKColor::yellow;
							if (textBGColor == OKColor::black)
							{
								textAAColor = OKColor::darkYellow;
							}
							else if (textBGColor == OKColor::white)
							{
								textAAColor = OKColor::lightYellow;
							}
						}
						else
						{
							if (optionBuffer.compare("GREEN") == 0)
							{
								textColor = OKColor::green;
								if (textBGColor == OKColor::black)
								{
									textAAColor = OKColor::darkGreen;
								}
								else if (textBGColor == OKColor::white)
								{
									textAAColor = OKColor::lightGreen;
								}
							}
							else
							{
								if (optionBuffer.compare("BLUE") == 0)
								{
									textColor = OKColor::blue;
									if (textBGColor == OKColor::black)
									{
										textAAColor = OKColor::darkBlue;
									}
									else if (textBGColor == OKColor::white)
									{
										textAAColor = OKColor::lightBlue;
									}
								}
								else
								{
									if (optionBuffer.compare("PURPLE") == 0)
									{
										textColor = OKColor::purple;
										if (textBGColor == OKColor::black)
										{
											textAAColor = OKColor::darkPurple;
										}
										else if (textBGColor == OKColor::white)
										{
											textAAColor = OKColor::lightPurple;
										}
									}
									else
									{
										if (optionBuffer.compare("PINK") == 0)
										{
											textColor = OKColor::pink;
											if (textBGColor == OKColor::black)
											{
												textAAColor = OKColor::darkPink;
											}
											else if (textBGColor == OKColor::white)
											{
												textAAColor = OKColor::lightPink;
											}
										}
										else
										{
											if (optionBuffer.compare("BGBLACK") == 0)
											{
												textBGColor = OKColor::black;
												//TODO: if(textColor==COLOR)textAAColor=DARKCOLOR;
											}
											else
											{
												if (optionBuffer.compare("BGWHITE") == 0)
												{
													textBGColor = OKColor::white;
													//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
												}
												else
												{
													if (optionBuffer.compare("BGCLEAR") == 0)
													{
														textBGColor = OKColor::clear;
														//if(textColor==COLOR)textAAColor=LIGHTCOLOR;
													}
													else
													{
														Main::console->debug("Unknown getText tag: " + optionBuffer);
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

	int index = OKFont::getFontPixelValueAtIndex((letterIndex * blockHeight * blockWidth) + (y * blockWidth) + xInLetter, font);

	return index;
}

void Caption::setPixel(int index, shared_ptr<OKColor> c)
{ //=========================================================================================================================

	if (c == nullptr)
	{
		log->error("setPixel Color c was null, should never happen!");
		return;
	}

	
	textureByteArray->data()[index + 0] = static_cast<u8>(c->ri());
	textureByteArray->data()[index + 1] = static_cast<u8>(c->gi());
	textureByteArray->data()[index + 2] = static_cast<u8>(c->bi());
	textureByteArray->data()[index + 3] = static_cast<u8>(c->ai());
	


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
int Caption::reduceHeightByOne()
{//=========================================================================================================================

	if (ttfFont == nullptr)return 0;

	fontSize--;
	if (fontSize < 6)fontSize = 6;

	setText(text, true);

	return fontSize;
								

}
//=========================================================================================================================
int Caption::increaseHeightByOne()
{//=========================================================================================================================

	if (ttfFont == nullptr)return 0;

	fontSize++;
	if (fontSize > 32)fontSize = 48;
	if (fontSize > 48)fontSize = 64;
	if (fontSize > 64)fontSize = 64;

	setText(text, true);

	return fontSize;

}

//=========================================================================================================================
float Caption::getWidth()
{//=========================================================================================================================

	float screenWidth = width * scale;
	//float screenHeight = height * scale;

//	if (ttfFont != nullptr)
//	{
//		screenHeight = (fontSize + 4)*scale;
//		float heightRatio = screenHeight / (height * scale);
//		screenWidth = (width * scale)*heightRatio;
//	}

	return screenWidth;
}

//=========================================================================================================================
float Caption::getHeight()
{//=========================================================================================================================

	//float screenWidth = width * scale;
	float screenHeight = height * scale;

//	if (ttfFont != nullptr)
//	{
//		screenHeight = (fontSize + 4)*scale;
//		float heightRatio = screenHeight / (height * scale);
//		screenWidth = (width * scale)*heightRatio;
//	}

	return screenHeight;
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

		shared_ptr<OKColor> c = nullptr;

		if (index == 0)
		{
			c = make_shared<OKColor>(*textBGColor);
		}
		else if (index == 1)
		{
			c = make_shared<OKColor>(*textColor);
		}
		else if (index == 2)
		{
			c = make_shared<OKColor>(*textAAColor);
		}
		else if (index > 2) //additional aa pixels, use the color value to set the opacity
		{
			//get the gray color from the getText palette
			int byte1 = (int)(OKFont::font_Palette_ByteArray->data()[index * 2 + 0] & 255);
			//int byte2 = (int)(OKFont::font_Palette_ByteArray[index * 2 + 1] & 255);
			//int abgr1555 = (byte2 << 8) + byte1;
			int r = 255 - (int)((((byte1 & 31)) / 32.0f) * 255.0f);
			//int r = 255-(int)((((byte1&0b00011111))/32.0f)*255.0f);
			//Color gray = make_shared<Color>(b,b,b);


			int a = r; //gray.getRed();
			if (a < 0)
			{
				a = 0;
			}

			a *= textAAColor->ai();

			//shared_ptr<Color> tc = textColor;
			c = make_shared<OKColor>(textColor->ri(), textColor->gi(), textColor->bi(), a);
		}


		if (fadeLetterColorTowardsTop)
		{
			if ((index > 0) && y < maxCharHeight * 0.75f && (index != 2 || outlined == false))
			{
				u8 r = (int)(min(255, (int)(c->ri() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				u8 g = (int)(min(255, (int)(c->gi() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				u8 b = (int)(min(255, (int)(c->bi() + (((float)(maxCharHeight - y) / (float)(maxCharHeight))*255.0f))));
				u8 a = c->ai();

				if (c != nullptr)delete c;
				c = make_shared<OKColor>(r, g, b, a);
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

	int letterWidth = OKFont::getCharWidth(letterIndex, font);

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
	if (fixedPosition == Position::CENTERED_OVER_ENTITY)
	{
		shared_ptr<Entity>e = entity;
		if (e == nullptr)e = getPlayer();

		if(e!=nullptr)
		{
			screenX = (float)floor(e->getScreenLeft() + (e->getWidth() * getCameraman()->getZoom() / 2.0f)) - (width * scale / 2.0f);//no g.zoom on getCaption width, they arent affected by zoom!


			int captionOverHeadOffset = 0;
			for (int i = getCaptionManager()->captionList->size() - 1; i >= 0; i--)
			{
				shared_ptr<Caption> tempC = getCaptionManager()->captionList->get(i);
				if (tempC->fixedPosition == Position::CENTERED_OVER_ENTITY)
				{
					if (tempC == this)break;

					captionOverHeadOffset += (int)((tempC->height + 2) * tempC->scale);
				}
			}

			screenY = (float)floor(e->getScreenTop()) - (captionOverHeadOffset + (height + 2) * scale);
		}
	}
	else
	{
		if (fixedPosition == Position::CENTERED_SCREEN)
		{
			screenX = (float)(((int)(GLUtils::getViewportWidth() / 2.0f)) - (int)((width * scale) / 2.0f));
			screenY = (float)((int)(GLUtils::getViewportHeight() / 2.0f));
		}
		else
		{
			if (fixedPosition == Position::CENTERED_X)
			{
				screenX = (float)((int)(GLUtils::getViewportWidth() / 2.0f) - (int)((width * scale) / 2.0f));
			}
		}
	}

	//-----------------------------
	//don't let captions wrap offscreen
	//-----------------------------
	if (screenX + getWidth() >= GLUtils::getViewportWidth())
	{
		screenX = (float)(GLUtils::getViewportWidth() - (int)(getWidth() + 1));
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
		ticksPassed = Engine::realWorldTicksPassed();
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
			delete texture;
			texture = nullptr;
		}

		deleteMe = true;

		
	}
}


void Caption::setEntity(shared_ptr<Entity> e)
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

