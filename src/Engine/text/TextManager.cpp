
#include "stdafx.h"


//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once




Logger TextManager::log = Logger("TextManager");


sp<OKTexture> TextManager::questionMarkTexture = nullptr;

TextManager::TextManager(sp<Engine> g)
{ //=========================================================================================================================
	this->e = g;


	if (actionIconScreenSprite == nullptr)
	{
		actionIconScreenSprite = ms<ScreenSprite>(g, "button", "actionIcon"); //HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,actionx-8,actiony+1,255);
		actionIconScreenSprite->draw = false;

		actionIconScreenSprite->setScale(2);

		actionIconScreenSprite->setAnimateLoopThroughAllFrames();
		actionIconScreenSprite->setRandomUpToTicksBetweenAnimationLoop(false);
		actionIconScreenSprite->setTicksBetweenFrames(60);
		actionIconScreenSprite->setTicksBetweenAnimationLoop(0);
	}
}

bool TextManager::isTextBoxOpen()
{ //=========================================================================================================================

	if (textEngineState != TextEngineState::CLOSED)
	{
		return true;
	}

	return false;
}

bool TextManager::isTextAnswerBoxOpen()
{ //=========================================================================================================================

	if ((int)textEngineState > (int)TextEngineState::CLOSING)
	{
		return true;
	}

	return false;
}

void TextManager::init()
{ //=========================================================================================================================

	//log.debug("Init TextManager");
	/*
	 * // load a default java font
	 * try
	 * {
	 * OKFont awtFont = ms<OKFont>("bobsgame", OKFont.PLAIN, 8);
	 * font = ms<TrueTypeFont>(awtFont, antiAlias);
	 * }
	 * catch (Exception e)
	 * {
	 * e.printStackTrace();
	 * }
	 */

	// load font from file
	//   try
	//   {
	//      sp<InputStream> inputStream = FileUtils::getResourceAsStream("res/fonts/bobsgame.ttf");
	//
	//      java::awt::Osp<KFont> awtFont = java::awt::OKFont::createFont(java::awt::OKFont::TRUETYPE_FONT, inputStream);
	//      awtFont = awtFont->deriveFont(8.0f); // set font size
	//      ttfFont = ms<TrueTypeFont>(awtFont, antiAlias);
	//   }
	//   catch (exception& e)
	//   {
	//      e.printStackTrace();
	//   }

	if (questionMarkTexture == nullptr)
	{
		questionMarkTexture = GLUtils::getTextureFromPNGExePath("data/textbox/questionmark.png");
	}


	//width = (int)((getEngine()->getWidth()*0.66f)/(64*2))*(64*2);

	//pow2TexWidth = Math::getClosestPowerOfTwo(width);
	//pow2TexHeight = Math::getClosestPowerOfTwo(height);

	textBox->clear();
	textBox->push_back(ms<TextWindow>(getEngine()));
	textBox->push_back(ms<TextWindow>(getEngine()));

	textBox->at(0)->init();
	textBox->at(1)->init();
}

void TextManager::reset()
{ //=========================================================================================================================


	font = OKFont::font_normal_8;

	textBGColor = OKColor::black;
	textColor = OKColor::white;
	textAAColor = OKColor::darkerGray;
	textShadowColor = OKColor::darkerGray;

	selectedTextbox = BOTTOM;
	topBoxActivated = false;
	delay = false;

	ticksPerLetter = 8;

	waitingForCancelButtonUnpress = false;
	getActionManager()->deleteCaptionWithBlipSound();

	textBox->at(0)->scrollPercent = 0;
	textBox->at(1)->scrollPercent = 0;

	textBox->at(0)->setSpriteWindow(getCameraman()->targetEntity, nullptr, "");
	textBox->at(1)->setSpriteWindow(getCameraman()->targetEntity, questionMarkTexture, "???");


	int i = 0;
	for (i = 0; i < 2; i++)
	{
		textBox->at(i)->clearByteArray();

		textBox->at(i)->line = 0;
		textBox->at(i)->xInLine = 0;

		textBox->at(i)->redraw = true;
	}
}

void TextManager::text(const string& s)
{ //=========================================================================================================================
	if (currentText == "")
	{
		length = (int)s.length();
		currentText = s;
		update();
	}
	else
	{
		// TODO: error, this should never happen, but i could handle it gracefully somehow.
	}
}

void TextManager::render()
{ //=========================================================================================================================

	if (textEngineState != TextEngineState::CLOSED)
	{
		if (textBox->at(0) != nullptr)
		{
			textBox->at(0)->render();
		}
		if (textBox->at(1) != nullptr)
		{
			textBox->at(1)->render();
		}
	}
}

int TextManager::getLineSizeX()
{ //=========================================================================================================================
	// check font. if height is greater than 12, we aren't drawing at 2x, so return full length.

	int h = getTextManager()->font->maxCharHeight;

	bool draw2X = true;

	if (h > 12)
	{
		draw2X = false;
	}

	// otherwise we are drawing at floatsize, so return half length.

	if (draw2X == true)
	{
		return width / 2;
	}
	else
	{
		return width;
	}
}

void TextManager::update()
{ //=========================================================================================================================


	//BOTTOM_ACTIVE_POSITION_Y=((getEngine()->getHeight()-textWindowHeight)-16)-16;
	//BOTTOM_INACTIVE_POSITION_Y=getEngine()->getHeight()+16;
	//TOP_ACTIVE_POSITION_Y=((0+16)+16+24);
	//TOP_INACTIVE_POSITION_Y=((0-textWindowHeight)-16);
	//POSITION_X=((getEngine()->getWidth()-(textWindowWidth+spriteWindowWidth))/2)+spriteWindowWidth;


	//drawLetterTicksCounter+=getEngine()->engineTicksPassed();

	long long ticksPassed = getEngine()->realWorldTicksPassed();


	{
		//while(drawLetterTicksCounter>=textEngineSpeedTicksPerLetter)
		//drawLetterTicksCounter-=textEngineSpeedTicksPerLetter;

		// -----------------------------
		// if there's new getText
		// -----------------------------
		if (currentText != "")
		{
			// -----------------------------
			// if it's the beginning of the getText
			// -----------------------------
			if (position == 0)
			{
				// -----------------------------
				// if the getText window is offscreen
				// -----------------------------
				if (textEngineState == TextEngineState::CLOSED)
				{
					// -----------------------------
					// and it's not paused, start the getText engine
					// -----------------------------

					reset();

					// zoom the camera to the talking NPC
					getCameraman()->setTarget(textBox->at(0)->spriteWindowEntity);
					getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);
					getCameraman()->ignoreCameraFXBoundaries = true; // avoid camera boundaries

					getAudioManager()->playSound("blah", 0.5f, textBox->at(selectedTextbox)->voicePitch + Math::randLessThanFloat(2.0f), 1);

					scrollingUp = true; // wait for the getText box to scroll up before drawing getText in it.

					textEngineState = TextEngineState::OPEN; // getText box is open
				}

				if (textEngineState == TextEngineState::OPEN)
				{
					// -----------------------------
					// if it's set to stay open, draw the getText into it
					// (this is for sending another getText string into an already-open getText box.)
					// -----------------------------
					if (keepOpenForNewText == true)
					{
						keepOpenForNewText = false;

						// start a new line of getText.
						textBox->at(selectedTextbox)->xInLine = 0;
						textBox->at(selectedTextbox)->line++;

						if (textBox->at(selectedTextbox)->line > MAX_LINES)
						{
							waitingForButtonForNewPage = true;
						}
					}
				}
			}

			if (textEngineState == TextEngineState::OPEN)
			{
				// -----------------------------
				// parse options (even if the getText box is paused)
				// -----------------------------
				if (position < length)
				{
					while (position < length && currentText[position] == '<' && waitingForButtonForNewPage == false && pausedUntilButtonPress == false)
					{
						parseOption();
						position++;
					}
				}

				if (delay == true)
				{
					if (delayTicks > 0)
					{
						delayTicks -= (int)ticksPassed;
					}
					else
					{
						delay = false;
					}
				}


				drawText(ticksPassed);

				handleInput();
				
			}

			// TODO: what if there's getText, it isn't at the beginning of the getText, and the getText box is closed?
			// this should never happen, but what if it does?
		}




		doScrolling(ticksPassed);

		textBox->at(0)->updateTextureFromByteArray();
		textBox->at(1)->updateTextureFromByteArray();
	}


	actionIconScreenSprite->draw = buttonIconIsOn;
}


void TextManager::parseColorizedTags()
{

		// automatically colorize "Yuu"

		if (position < length - 2 && OKString::startsWith(currentText.substr(position), "Yuu"))
		{
			tC0 = textBGColor;
			tC1 = textColor;
			tC2 = textAAColor;
			tC3 = textShadowColor;

			textColor = OKColor::purple;
			if (textBGColor == OKColor::black)
			{
				textAAColor = OKColor::darkerPurple;
			}
			else
			{
				textAAColor = OKColor::lightPurple;
			}
			if (textBGColor == OKColor::black)
			{
				textShadowColor = OKColor::darkerPurple;
			}
			else
			{
				textShadowColor = OKColor::lightPurple;
			}
		}

		//"bob's game"
		else
		{
			if (position < length - 11 && OKString::startsWith(currentText.substr(position), "\"bob's game\""))
			{
				tC0 = textBGColor;
				tC1 = textColor;
				tC2 = textAAColor;
				tC3 = textShadowColor;

				textColor = OKColor::green;
				if (textBGColor == OKColor::black)
				{
					textAAColor = OKColor::darkerGreen;
				}
				else
				{
					textAAColor = OKColor::lightGreen;
				}

				if (textBGColor == OKColor::black)
				{
					textShadowColor = OKColor::darkerGreen;
				}
				else
				{
					textShadowColor = OKColor::lightGreen;
				}
			}
			else
			{
				if (position < length - 9 && OKString::startsWith(currentText.substr(position), "bob's game") && (position >= length - 10 || OKString::startsWith(currentText.substr(position), "bob's game\"") == false))
				{
					tC0 = textBGColor;
					tC1 = textColor;
					tC2 = textAAColor;
					tC3 = textShadowColor;

					textColor = OKColor::green;
					if (textBGColor == OKColor::black)
					{
						textAAColor = OKColor::darkerGreen;
					}
					else
					{
						textAAColor = OKColor::lightGreen;
					}

					if (textBGColor == OKColor::black)
					{
						textShadowColor = OKColor::darkerGreen;
					}
					else
					{
						textShadowColor = OKColor::lightGreen;
					}
				}
				else //bob's
				{
					if (position < length - 4 && OKString::startsWith(currentText.substr(position), "bob's") && (position >= length - 9 || OKString::startsWith(currentText.substr(position), "bob's game") == false))
					{
						tC0 = textBGColor;
						tC1 = textColor;
						tC2 = textAAColor;
						tC3 = textShadowColor;

						textColor = OKColor::green;
						if (textBGColor == OKColor::black)
						{
							textAAColor = OKColor::darkGreen;
						}
						else
						{
							textAAColor = OKColor::lightGreen;
						}

						if (textBGColor == OKColor::black)
						{
							textShadowColor = OKColor::darkerGreen;
						}
						else
						{
							textShadowColor = OKColor::lightGreen;
						}
					}
					else //bob
					{
						if (position < length - 2 && OKString::startsWith(currentText.substr(position), "bob") && (position >= length - 4 || OKString::startsWith(currentText.substr(position), "bob's") == false))
						{
							tC0 = textBGColor;
							tC1 = textColor;
							tC2 = textAAColor;
							tC3 = textShadowColor;

							textColor = OKColor::green;
							if (textBGColor == OKColor::black)
							{
								textAAColor = OKColor::darkerGreen;
							}
							else
							{
								textAAColor = OKColor::lightGreen;
							}

							if (textBGColor == OKColor::black)
							{
								textShadowColor = OKColor::darkerGreen;
							}
							else
							{
								textShadowColor = OKColor::lightGreen;
							}
						}
						else //nD
						{
							if (position < length - 1 && OKString::startsWith(currentText.substr(position), "nD"))
							{
								tC0 = textBGColor;
								tC1 = textColor;
								tC2 = textAAColor;
								tC3 = textShadowColor;

								textColor = OKColor::green;
								if (textBGColor == OKColor::black)
								{
									textAAColor = OKColor::darkerGreen;
								}
								else
								{
									textAAColor = OKColor::lightGreen;
								}

								if (textBGColor == OKColor::black)
								{
									textShadowColor = OKColor::darkerGreen;
								}
								else
								{
									textShadowColor = OKColor::lightGreen;
								}
							}
						}
					}
				}
			}
		}
	
}

void TextManager::postparseColorizedTags()
{

	// automatically colorize "Yuu" back to white

	if (position >= 2 && OKString::startsWith(currentText.substr(position - 2), "Yuu"))
	{
		textBGColor = tC0;
		textColor = tC1;
		textAAColor = tC2;
		textShadowColor = tC3;
	}

	//"bob's game"
	else
	{
		if (position >= 11 && OKString::startsWith(currentText.substr(position - 11), "\"bob's game\""))
		{
			textBGColor = tC0;
			textColor = tC1;
			textAAColor = tC2;
			textShadowColor = tC3;
		}
		else
		{
			if (position >= 9 && OKString::startsWith(currentText.substr(position - 9), "bob's game") && (position >= length - 1 || OKString::startsWith(currentText.substr(position - 9), "bob's game\"") == false))
			{
				textBGColor = tC0;
				textColor = tC1;
				textAAColor = tC2;
				textShadowColor = tC3;
			}
			else
			{
				if (position >= 4 && OKString::startsWith(currentText.substr(position - 4), "bob's") && (position >= length - 5 || OKString::startsWith(currentText.substr(position - 4), "bob's game") == false))
				{
					textBGColor = tC0;
					textColor = tC1;
					textAAColor = tC2;
					textShadowColor = tC3;
				}
				else
				{
					if (position >= 2 && OKString::startsWith(currentText.substr(position - 2), "bob") && (position >= length - 2 || OKString::startsWith(currentText.substr(position - 2), "bob's") == false))
					{
						textBGColor = tC0;
						textColor = tC1;
						textAAColor = tC2;
						textShadowColor = tC3;
					}
					else
					{
						if (position >= 1 && OKString::startsWith(currentText.substr(position - 1), "nD"))
						{
							textBGColor = tC0;
							textColor = tC1;
							textAAColor = tC2;
							textShadowColor = tC3;
						}
						else
						{
							if (OKString::startsWith(currentText.substr(position), "nD"))
							{
								textColor = OKColor::purple;
								if (textBGColor == OKColor::black)
								{
									textAAColor = OKColor::darkerPurple;
								}
								else
								{
									textAAColor = OKColor::lightPurple;
								}
								if (textBGColor == OKColor::black)
								{
									textShadowColor = OKColor::darkerPurple;
								}
								else
								{
									textShadowColor = OKColor::lightPurple;
								}
							}
						}
					}
				}
			}
		}
	}

}

void TextManager::drawText(long long ticksPassed)
{ //=========================================================================================================================


	ticksPassed += remainderTicks;


	int lettersToDraw = (int)(ticksPassed / ticksPerLetter);
	remainderTicks = ticksPassed % ticksPerLetter;

	for (int i = 0; i <= lettersToDraw && delay==false && scrollingUp == false; i++)
	{
		// -----------------------------
		// draw getText
		// -----------------------------

		if (position < length && waitingForButtonForNewPage == false && pausedUntilButtonPress == false)
		{
			parseColorizedTags();

			// parse option tags
			// this should never happen, it should be parsed above.
			if (currentText[position] == '<')
			{
				parseOption();

				string e = "A tag was parsed inside drawText()";
				Main::console->error(e);
				log.error(e);
			}

			else

				// -----------------------------
				// handle space
				// -----------------------------
			{
				if (currentText[position] == ' ')
				{
					// get next word length including the space
					int nextWordLength = OKFont::getNextWordLength(currentText, position, font);

					// THIS SKIPS WORDS LONGER THEN THE MAXIMUM LENGTH
					if (nextWordLength > getLineSizeX())
					{
						//TODO: skip next word

						string e = "A word was too long for the getText engine.";
						Main::console->error(e);
						log.error(e);

						nextWordLength = OKFont::getNextWordLength(currentText, position, font);
					}

					// see if it fits on the current line
					int pixelsLeftInLine = getLineSizeX() - textBox->at(selectedTextbox)->xInLine;
					if (textBox->at(selectedTextbox)->line == MAX_LINES)
					{
						pixelsLeftInLine -= 32; // for the getText button icon
					}

					// if it doesnt fit, go to the next line
					if (pixelsLeftInLine < nextWordLength)
					{
						textBox->at(selectedTextbox)->xInLine = 0;
						textBox->at(selectedTextbox)->line++;

						// if we're on the last line, wait for input
						if (textBox->at(selectedTextbox)->line > MAX_LINES)
						{
							waitingForButtonForNewPage = true;
						}
					}

					// play a sound for each word. if the last word was a question, raise voice.
					// if(getText[temp_position-1]=='?')MusicAndSoundManager().playSound("blah",127,TEXT_textbox[TEXT_selected_textbox].voice_pitch+(30000),0);
					// else MusicAndSoundManager().playSound("blah",127,TEXT_textbox[TEXT_selected_textbox].voice_pitch+(rand()%20000),0);

					// only draw the space if we're not at the beginning of the getText box
					if (textBox->at(selectedTextbox)->xInLine != 0)
					{
						drawLetter();
					}
				}
				else
				{
					// if TEXT_font_pointer<FONT_JAPANESE
					drawLetter();
				}
			}

			postparseColorizedTags();


			if (position + 1 < length - 3 && OKString::startsWith(currentText.substr(position + 1), "<.") == false)
			{
				//auto delay on punctuation
				if ((currentText[position] == '.' || currentText[position] == '?' || currentText[position] == '!'))
				{
					delay = true;
					delayTicks = 500;//500
				}

				if (currentText[position] == ',')
				{
					delay = true;
					delayTicks = 300;//300
				}

				if (currentText[position] == '-')
				{
					delay = true;
					delayTicks = 400;
				}

				if (currentText[position] == '!')
				{
					textBox->at(selectedTextbox)->shakeTicksYTotal = 300;//300
					//textBox->at(selectedTextbox).shakeTicksLeft = textBox->at(selectedTextbox).shakeTicksTotal;
				}

				if (currentText[position] == '?')
				{
					textBox->at(selectedTextbox)->shakeTicksXTotal = 300;//300
					//textBox->at(selectedTextbox).shakeTicksLeft = textBox->at(selectedTextbox).shakeTicksTotal;
				}
			}
			// increment the string
			position++;
		}
	}
}

void TextManager::handleInput()
{ //=========================================================================================================================

	if (scrollingUp == false && delay == false)
	{

		if (waitingForButtonForNewPage == true)
		{
			if (getControlsManager()->bgClient_CANCELRUN_Pressed() == true && waitingForCancelButtonUnpress != true)
			{
				waitingForCancelButtonUnpress = true;
				getAudioManager()->playSound("blip", 0.25f, 0.5f, 1);
			}

			if (waitingForCancelButtonUnpress == true)
			{
				if (getControlsManager()->bgClient_CANCELRUN_Pressed() == false)
				{
					waitingForCancelButtonUnpress = false;
					if (cannotCancel == false)
					{
						waitingForButtonPressToClose = true;
						waitingForUnpress = true;
						pausedUntilButtonPress = false;
					}
				}
			}

			if (buttonIconIsOn == false)
			{
				if (selectedTextbox == BOTTOM)
				{
					// TEXT_textbox->at(0).button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox->at(0).screen_y+64-8-2,255);
				}
				if (selectedTextbox == TOP)
				{
					// TEXT_textbox->at(0).button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-2,255);
				}
				buttonIconIsOn = true;
			}

			if ((getControlsManager()->bgClient_ACTION_Pressed() == true || skipText == true) && waitingForUnpress == false)
			{
				waitingForUnpress = true;
				getAudioManager()->playSound("blip", 0.25f, 1.5f, 1);
			}

			if (waitingForUnpress == true)
			{
				if ((getControlsManager()->bgClient_ACTION_Pressed() == false) || skipText == true)
				{
					waitingForUnpress = false;
					buttonAUnpressed = true;
				}
			}

			if (buttonAUnpressed == true)
			{
				if (buttonIconIsOn == true)
				{
					buttonIconIsOn = false;
					// HARDWARE_delete_sprite(TEXT_textbox->at(0).button_sprite);
				}

				buttonAUnpressed = false;
				textBox->at(selectedTextbox)->clearByteArray();

				if (waitingForButtonPressToClose == false && textEngineState != TextEngineState::CLOSING)
				{
					textBox->at(selectedTextbox)->redraw = true;
				}

				textBox->at(selectedTextbox)->line = 0;
				textBox->at(selectedTextbox)->xInLine = 0;
				waitingForButtonForNewPage = false;
			}
		}


		if (pausedUntilButtonPress == true)
		{
			if (getControlsManager()->bgClient_CANCELRUN_Pressed() == true && waitingForCancelButtonUnpress != true)
			{
				waitingForCancelButtonUnpress = true;


				getAudioManager()->playSound("blip", 0.25f, 0.5f, 1);
			}
			if (waitingForCancelButtonUnpress == true)
			{
				if (getControlsManager()->bgClient_CANCELRUN_Pressed() == false)
				{
					waitingForCancelButtonUnpress = false;
					if (cannotCancel == false)
					{
						waitingForButtonPressToClose = true;
						waitingForUnpress = true;
					}
				}
			}
			if (buttonIconIsOn == false)
			{
				if (selectedTextbox == BOTTOM)
				{
					// TEXT_textbox->at(0).button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox->at(0).screen_y+64-8-2,255);
				}


				if (selectedTextbox == TOP)
				{
					// TEXT_textbox->at(0).button_sprite = HARDWARE_create_sprite(TEXT_button_icon_GFX,0,1,1.0f,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-2,255);
				}


				buttonIconIsOn = true;
			}
			if ((getControlsManager()->bgClient_ACTION_Pressed() == true || skipText == true) && waitingForUnpress == false)
			{
				waitingForUnpress = true;

				getAudioManager()->playSound("blip", 0.25f, 1.5f, 1);
			}
			if (waitingForUnpress == true)
			{
				if ((getControlsManager()->bgClient_ACTION_Pressed() == false) || skipText == true)
				{
					waitingForUnpress = false;
					buttonAUnpressed = true;
				}
			}
			if (buttonAUnpressed == true)
			{
				pausedUntilButtonPress = false;
				if (buttonIconIsOn == true)
				{
					buttonIconIsOn = false;

					// HARDWARE_delete_sprite(TEXT_textbox->at(0).button_sprite);
				}

				buttonAUnpressed = false;
			}
		}


		if (position >= length && waitingForButtonPressToClose == false)
		{
			if (keepOpenForNewText == false)
			{
				waitingForButtonForNewPage = true;
				waitingForButtonPressToClose = true;
			}
			else
			{
				// TODO: set getText string to log
				currentText = "";

				// /log conversations, parse NPC names
				// /log entered room name
				// /log items, interactions

				position = 0;
			}
		}


		if (waitingForButtonPressToClose == true && waitingForButtonForNewPage == false)
		{
			waitingForButtonPressToClose = false;


			currentText = "";

			position = 0;
			cannotCancel = false;
			pausedUntilButtonPress = false;


			topBoxActivated = false; // if getText box 2 is on, it will scroll up

			textEngineState = TextEngineState::CLOSING;
		}
	}
}

void TextManager::doScrolling(long long ticksPassed)
{ //=========================================================================================================================



	/*
	 * TEXT_scale = 1.0f;
	 * HARDWARE_sprite_set_scale(1,TEXT_box_1_sprite_window_id,TEXT_scale*2);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_2_sprite_window_id,TEXT_scale*2);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_1_id,TEXT_scale);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_2_id,TEXT_scale);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_1_chunk_3_id,TEXT_scale);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_1_id,TEXT_scale);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_2_id,TEXT_scale);
	 * HARDWARE_sprite_set_scale(1,TEXT_box_2_chunk_3_id,TEXT_scale);
	 */


	textBox->at(0)->alpha = textBox->at(0)->scrollPercent;
	textBox->at(1)->alpha = textBox->at(1)->scrollPercent;


	float fastScroll = 0.003f * ticksPassed;
	//float mediumScroll = 0.001f * ticksPassed;


	if (topBoxActivated == true && textBox->at(1)->scrollPercent != 1.0f)
	{
		textBox->at(1)->scrollPercent += fastScroll;
		if (textBox->at(1)->scrollPercent > 1.0f)
		{
			textBox->at(1)->scrollPercent = 1.0f;
		}
	}


	if (topBoxActivated == false && textBox->at(1)->scrollPercent != 0.0f)
	{
		textBox->at(1)->scrollPercent -= fastScroll;
		if (textBox->at(1)->scrollPercent < 0.0f)
		{
			textBox->at(1)->scrollPercent = 0.0f;
		}
	}


	if (textEngineState == TextEngineState::ANSWER_BOX_ON) // ANSWER BOX TURNED ON,SCROLL TEXT BOX UP,ANSWER BOX UP
	{
		//			if(textBox->at(0).scrollPercent>BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
		//			{
		//				textBox->at(0).scrollPercent-=mediumScroll;
		//				if(textBox->at(0).scrollPercent<BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
		//					textBox->at(0).scrollPercent=BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2;
		//			}
		//
		//			if(textBox->at(0).scrollPercent==BOTTOM_ACTIVE_POSITION_Y-(11*numberOfAnswers)-2)
		//			{
		//				if(answerBoxY>textBox->at(0).scrollPercent+textWindowHeight+8-2)
		//				{
		//					answerBoxY-=fastScroll;
		//					if(answerBoxY<textBox->at(0).scrollPercent+textWindowHeight+8-2) answerBoxY=textBox->at(0).scrollPercent+textWindowHeight+8-2;
		//				}
		//			}

		if (selectedAnswer != 0)
		{
			if (cursorScreenSprite != nullptr)
			{
				cursorScreenSprite->screenYPixelsHQ = answerBoxY + 1 + ((selectedAnswer - 1) * 11);
			}
		}


		cursorTicks += (int)getEngine()->engineTicksPassed();

		if (cursorTicks > 300)
		{
			cursorTicks = 0;

			if (cursorPixelUpDownToggle == true)
			{
				cursorPixelUpDownToggle = false;
				//if(cursorScreenSprite!=null)
				//cursorScreenSprite.screenXPixelsHQ=textBox->at(0).getScreenX+(64*3)-(64*4)-8-1;//TODO
			}
			else
			{
				cursorPixelUpDownToggle = true;
				//if(cursorScreenSprite!=null)
				//cursorScreenSprite.screenXPixelsHQ=textBox->at(0).getScreenX+(64*3)-(64*4)-8;
			}
		}
	}
	else if (textEngineState == TextEngineState::ANSWER_BOX_CLOSING) // ANSWER BOX TURNED OFF,SCROLL TEXT BOX DOWN,SCROLL ANSWER BOX DOWN,DELETE ANSWER BOX
	{
		if (answerBoxY < getEngine()->getHeight())
		{
			answerBoxY += fastScroll;
		}

		//			if(textBox->at(0).scrollPercent<BOTTOM_ACTIVE_POSITION_Y)
		//			{
		//				textBox->at(0).scrollPercent+=mediumScroll;
		//				if(textBox->at(0).scrollPercent>BOTTOM_ACTIVE_POSITION_Y)
		//					textBox->at(0).scrollPercent=BOTTOM_ACTIVE_POSITION_Y;
		//			}
		//			else
		//			{
		//				textEngineState=OPEN;
		//			}
	}
	else if (textEngineState == TextEngineState::KEYBOARD_ON) // KEYBOARD TURNED ON,SCROLL TEXT BOX UP,KEYBOARD BOX UP
	{
		//			if(textBox->at(0).scrollPercent>BOTTOM_ACTIVE_POSITION_Y-64-2)
		//			{
		//				textBox->at(0).scrollPercent-=mediumScroll;
		//				if(textBox->at(0).scrollPercent<BOTTOM_ACTIVE_POSITION_Y-64-2) textBox->at(0).scrollPercent=BOTTOM_ACTIVE_POSITION_Y-64-2;
		//			}
		//
		//			if(textBox->at(0).scrollPercent==BOTTOM_ACTIVE_POSITION_Y-64-2)
		//			{
		//				if(keyboardY>textBox->at(0).scrollPercent+64+8-2)
		//				{
		//					keyboardY-=fastScroll;
		//					if(keyboardY<textBox->at(0).scrollPercent+64+8-2) keyboardY=textBox->at(0).scrollPercent+64+8-2;
		//
		//					if(keyboardScreenSprite!=null) keyboardScreenSprite.screenYPixelsHQ=keyboardY;
		//				}
		//			}
	}
	else if (textEngineState == TextEngineState::KEYBOARD_CLOSING) // KEYBOARD TURNED OFF,SCROLL TEXT BOX DOWN,SCROLL KEYBOARD DOWN,DELETE KEYBOARD
	{
		if (keyboardY < getEngine()->getHeight())
		{
			keyboardY += fastScroll;


			if (keyboardScreenSprite != nullptr)
			{
				keyboardScreenSprite->screenYPixelsHQ = keyboardY;
			}
		}
		if (textBox->at(0)->scrollPercent > 0.0f)
		{
			textBox->at(0)->scrollPercent -= fastScroll;
			if (textBox->at(0)->scrollPercent < 0.0f)
			{
				textBox->at(0)->scrollPercent = 0.0f;
			}
		}
		else
		{
			textEngineState = TextEngineState::OPEN;
		}
	}
	else


	{
		if (textEngineState == TextEngineState::OPEN) // ==================================TEXT BOX IS IN RUNNING STATE==============================
		{
			if (textBox->at(0)->scrollPercent >= 1.0f)
			{
				textBox->at(0)->scrollPercent = 1.0f;
				scrollingUp = false;
			}
			else if (textBox->at(0)->scrollPercent < 1.0f)
			{
				textBox->at(0)->scrollPercent += fastScroll;
				scrollingUp = true;
			}



			for (int i = 0; i < 2; i++)
			{
				if (textBox->at(i)->shakeTicksXTotal > 0)
				{
					if (textBox->at(i)->shakeTicksXTotal > 0)
					{
						textBox->at(i)->shakeTicksXTotal -= (int)ticksPassed;
					}
					if (textBox->at(i)->shakeTicksXTotal < 0)
					{
						textBox->at(i)->shakeTicksXTotal = 0;
					}


					textBox->at(i)->shakeTicksLeftRightCounter += (int)ticksPassed;

					if (textBox->at(i)->shakeTicksLeftRightCounter > 10)
					{
						textBox->at(i)->shakeTicksLeftRightCounter = 0;

						if (textBox->at(i)->shakeLeftRightToggle == true)
						{
							textBox->at(i)->shakeX++;
							if (textBox->at(i)->shakeX >= textBox->at(i)->shakeMaxX)
							{
								textBox->at(i)->shakeLeftRightToggle = !textBox->at(i)->shakeLeftRightToggle;
							}
						}
						else
						{
							textBox->at(i)->shakeX--;
							if (textBox->at(i)->shakeX <= 0 - textBox->at(i)->shakeMaxX)
							{
								textBox->at(i)->shakeLeftRightToggle = !textBox->at(i)->shakeLeftRightToggle;
							}
						}
					}
				}
				else
				{
					textBox->at(i)->shakeX = 0;
				}


				if (textBox->at(i)->shakeTicksYTotal > 0)
				{
					if (textBox->at(i)->shakeTicksYTotal > 0)
					{
						textBox->at(i)->shakeTicksYTotal -= (int)ticksPassed;
					}
					if (textBox->at(i)->shakeTicksYTotal < 0)
					{
						textBox->at(i)->shakeTicksYTotal = 0;
					}


					textBox->at(i)->shakeTicksUpDownCounter += (int)ticksPassed;

					if (textBox->at(i)->shakeTicksUpDownCounter > 10)
					{
						textBox->at(i)->shakeTicksUpDownCounter = 0;

						if (textBox->at(i)->shakeUpDownToggle == true)
						{
							textBox->at(i)->shakeY++;
							if (textBox->at(i)->shakeY >= textBox->at(i)->shakeMaxY)
							{
								textBox->at(i)->shakeUpDownToggle = !textBox->at(i)->shakeUpDownToggle;
							}
						}
						else
						{
							textBox->at(i)->shakeY--;
							if (textBox->at(i)->shakeY <= 0 - textBox->at(i)->shakeMaxY)
							{
								textBox->at(i)->shakeUpDownToggle = !textBox->at(i)->shakeUpDownToggle;
							}
						}
					}
				}
				else
				{
					textBox->at(i)->shakeY = 0;
				}
			}
		} // END IF TEXT BOX ON

		else if (textEngineState == TextEngineState::CLOSING) // ===========================TEXT BOX IS IN SCROLLING DOWN STATE. WHEN FINISHED,DELETE TEXT BOX===================
		{
			if (textBox->at(0)->scrollPercent > 0.0f)
			{
				textBox->at(0)->scrollPercent -= fastScroll;
			}

			if (textBox->at(0)->scrollPercent < 0.0f)
			{
				textBox->at(0)->scrollPercent = 0.0f;


				getCameraman()->ignoreCameraFXBoundaries = false; // TODO: restore previous state
				getCameraman()->setTarget(getPlayer()); // TODO: restore previous cameraman target and speed
				getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);


				textEngineState = TextEngineState::CLOSED;
			}
		}


		else if (textEngineState == TextEngineState::CLOSED)
		{
			textBox->at(0)->scrollPercent = 0.0f;
			textBox->at(1)->scrollPercent = 0.0f;
		}
	}


	//		if(buttonIconIsOn==true)
	//		{
	//
	//			// if(TEXT_selected_textbox==false)
	//			// HARDWARE_set_sprite_xy(TEXT_textbox->at(0).button_sprite,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox->at(0).screen_y+64-8-(TEXT_button_icon_down*2));
	//
	//
	//			// if(TEXT_selected_textbox==true)
	//			// HARDWARE_set_sprite_xy(TEXT_textbox->at(0).button_sprite,TEXT_textbox->at(0).screen_x+(64*3)-8,TEXT_textbox[1].screen_y+64-8-(TEXT_button_icon_down*2));
	//
	//			if(buttonTimer>500)
	//			{
	//				buttonTimer=0;
	//
	//				if(buttonIconUpDownToggle==false)
	//				{
	//					buttonIconUpDownToggle=true;
	//				}
	//				else
	//				{
	//					buttonIconUpDownToggle=false;
	//				}
	//			}
	//			buttonTimer+=getEngine()->engineTicksPassed();
	//		}
}

void TextManager::drawLetter()
{ //=========================================================================================================================


	int letterIndex = OKFont::getFontIndexForChar(currentText[position]);
	if (letterIndex == -1)
	{
		return;
	}


	int letterWidth = OKFont::getCharWidth(letterIndex, font);


	// play sound sometimes, for vowels
	if ((textBox->at(selectedTextbox)->xInLine == 0 && textBox->at(selectedTextbox)->line == 0) || (position % 2 == 0 && position < length - 1 && (OKFont::is_a_vowel(currentText[position - 1]) != OKFont::is_a_vowel(currentText[position]) || OKFont::is_a_vowel(currentText[position]) != OKFont::is_a_vowel(currentText[position + 1]))))
	{
		if (font == OKFont::font_bob_16)
		{
			getAudioManager()->playSound("blah", 0.5f, textBox->at(selectedTextbox)->voicePitch + ((10 + Math::randUpToIncluding(20)) / 10.0f), 1);
		}
		else
		{
			getAudioManager()->playSound("blah", 0.5f, textBox->at(selectedTextbox)->voicePitch + (Math::randUpToIncluding(20) / 10.0f), 1);
		}

		delay = true; // /why do i do this? slight delay on vowels so the sound has time to play?
		delayTicks = 50;
	}


	bool putInSpaceAlready = false;

	int xInLetter = 0;
	for (xInLetter = 0; xInLetter < letterWidth; xInLetter++)
	{
		if (textBox->at(selectedTextbox)->xInLine > getLineSizeX())
		{
			textBox->at(selectedTextbox)->xInLine = 0;
			textBox->at(selectedTextbox)->line++;
		}


		if (textBox->at(selectedTextbox)->line > MAX_LINES)
		{
			// PAUSE,CLEAR,START OVER
			waitingForButtonForNewPage = true;
		}


		// it it's a space on the last tile/chunk/pixel, skip it
		if (currentText[position] == ' ' && textBox->at(selectedTextbox)->xInLine >= getLineSizeX())
		{
			textBox->at(selectedTextbox)->xInLine = 0;
			textBox->at(selectedTextbox)->line++;

			xInLetter = letterWidth;

			putInSpaceAlready = true;

			if (textBox->at(selectedTextbox)->line > MAX_LINES)
			{
				waitingForButtonForNewPage = true;
			}
		}

		if (waitingForButtonForNewPage == false && putInSpaceAlready == false)
		{
			textBox->at(selectedTextbox)->drawColumn(letterIndex, xInLetter, false);
			textBox->at(selectedTextbox)->xInLine++;
		}
	}


	// ===================================INSERT SPACE
	// if(getText[TEXT_string_position]==' ')put_in_space_already=true; breaks the pixel length count.. i'd have to make it width-1 in get_text_length


	if (textBox->at(selectedTextbox)->line <= MAX_LINES && textBox->at(selectedTextbox)->xInLine < getLineSizeX() && putInSpaceAlready == false)
	{
		textBox->at(selectedTextbox)->drawColumn(0, 0, true);
		textBox->at(selectedTextbox)->xInLine++;

//		textBox->at(selectedTextbox)->drawColumn(0, 0, true);
//		textBox->at(selectedTextbox)->xInLine++;

		putInSpaceAlready = true;
	}

	if (textBox->at(selectedTextbox)->xInLine > getLineSizeX())
	{
		textBox->at(selectedTextbox)->xInLine = 0;
		textBox->at(selectedTextbox)->line++;
	}


	if (textBox->at(selectedTextbox)->line > MAX_LINES)
	{
		// PAUSE,CLEAR,START OVER
		waitingForButtonForNewPage = true;
	}


	// END INSERT SPACE===================================================================
	// /TEXT_update_textbox_sprite_textures();
	textBox->at(selectedTextbox)->redraw = true;
}

void TextManager::parseOption()
{ //=========================================================================================================================
	int optionLength = 0;
	// char TEXT_option_buffer[] = new char[MAX_ANSWER_LENGTH*6+5+2];


	position++;
	while (currentText[position + optionLength] != '>' && position + optionLength < length)
	{
		// if(TEXT_option_length<MAX_ANSWER_LENGTH*6+5+1)
		// TEXT_option_buffer.concat(TEXT_text.substring(TEXT_string_position+TEXT_option_length,TEXT_string_position+TEXT_option_length+1)); //fix fox longer than 6 longest answers


		// else {
		// TEXT_option_buffer[TEXT_option_length]=null;
		// u16 amt=0;
		// while(getText[TEXT_string_position+amt]!='>')amt++;
		// TEXT_string_position+=amt-TEXT_option_length;
		// break;

		// }

		//			if(currentText.charAt(position+optionLength)==':')
		//			{
		//				int tempAnswerLength=0;
		//
		//				while(currentText.charAt(position+optionLength+1+tempAnswerLength)!=':'
		//						&&
		//						currentText.charAt(position+optionLength+1+tempAnswerLength)!='>')
		//				{
		//					tempAnswerLength++;
		//				}
		//
		//				// TODO: fix this
		//				/*
		//				 * if(TEXT_temp_answer_length>MAX_ANSWER_LENGTH-1)
		//				 * {
		//				 * //cuts off answers longer than 50. increments the length by 50,only takes 50 from the answer,increments position by the whole thing
		//				 * int i=0;
		//				 * for(i=0;i<MAX_ANSWER_LENGTH-1;i++)
		//				 * TEXT_option_buffer[TEXT_option_length+1+i]=TEXT_text.charAt(TEXT_string_position+TEXT_option_length+1+i);
		//				 * TEXT_option_length+=MAX_ANSWER_LENGTH-1; //increments below
		//				 * TEXT_string_position+=(TEXT_temp_answer_length-1)-(MAX_ANSWER_LENGTH-1-1);
		//				 * }
		//				 */
		//			}

		optionLength++;
	}

	optionBuffer = currentText.substr(position, optionLength);
	position += optionLength;

	/*
	 * #define CLEAR 0
	 * #define BLACK 1
	 * #define WHITE 2
	 * #define GRAY 3
	 * #define RED 4
	 * #define ORANGE 5
	 * #define YELLOW 6
	 * #define GREEN 7
	 * #define BLUE 8
	 * #define PURPLE 9
	 * #define PINK 10
	 */
	if (optionBuffer == ".") // if i change this from "." remember to change get_next_word_length above.
	{
		waitingForButtonForNewPage = true;
	}
	else if (optionBuffer == "0" || optionBuffer == "BOTTOM")
	{
		selectedTextbox = BOTTOM;
		getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity); // if is not null!! else yuu
		getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);
	}
	else if (optionBuffer == "1" || optionBuffer == "TOP")
	{
		selectedTextbox = TOP;
		topBoxActivated = true;
		getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);
	}
	else if (optionBuffer == "PAUSE")
	{
		pausedUntilButtonPress = true;
	}
	else if (optionBuffer == "BOB")
	{
		font = OKFont::font_bob_16;
	}
	else if (optionBuffer == "SMALL")
	{
		font = OKFont::font_small_16;
	}
	else if (optionBuffer == "NORMAL")
	{
		font = OKFont::font_normal_16;
	}
	else if (optionBuffer == "BLACK")
	{
		textBGColor = OKColor::white;
		textColor = OKColor::black;
		textAAColor = OKColor::lightGray;
		textShadowColor = OKColor::gray;
	}
	else if (optionBuffer == "WHITE")
	{
		textBGColor = OKColor::black;
		textColor = OKColor::white;
		textAAColor = OKColor::gray;
		textShadowColor = OKColor::darkGray;
	}
	else if (optionBuffer == "GRAY")
	{
		textColor = OKColor::gray;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkGray;
		}
		else
		{
			textAAColor = OKColor::lightGray;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerGray;
		}
		else
		{
			textShadowColor = OKColor::lightGray;
		}
	}
	else if (optionBuffer == "RED")
	{
		textColor = OKColor::red;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkRed;
		}
		else
		{
			textAAColor = OKColor::lightRed;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerRed;
		}
		else
		{
			textShadowColor = OKColor::lightRed;
		}
	}
	else if (optionBuffer == "ORANGE")
	{
		textColor = OKColor::orange;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkOrange;
		}
		else
		{
			textAAColor = OKColor::lightOrange;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerOrange;
		}
		else
		{
			textShadowColor = OKColor::lightOrange;
		}
	}
	else if (optionBuffer == "YELLOW")
	{
		textColor = OKColor::yellow;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkYellow;
		}
		else
		{
			textAAColor = OKColor::lightYellow;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerYellow;
		}
		else
		{
			textShadowColor = OKColor::lightYellow;
		}
	}
	else if (optionBuffer == "GREEN")
	{
		textColor = OKColor::green;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkGreen;
		}
		else
		{
			textAAColor = OKColor::lightGreen;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerGreen;
		}
		else
		{
			textShadowColor = OKColor::lightGreen;
		}
	}
	else if (optionBuffer == "BLUE")
	{
		textColor = OKColor::blue;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkBlue;
		}
		else
		{
			textAAColor = OKColor::lightBlue;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerBlue;
		}
		else
		{
			textShadowColor = OKColor::lightBlue;
		}
	}
	else if (optionBuffer == "PURPLE")
	{
		textColor = OKColor::purple;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkPurple;
		}
		else
		{
			textAAColor = OKColor::lightPurple;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerPurple;
		}
		else
		{
			textShadowColor = OKColor::lightPurple;
		}
	}
	else if (optionBuffer == "PINK")
	{
		textColor = OKColor::pink;
		if (textBGColor == OKColor::black)
		{
			textAAColor = OKColor::darkPink;
		}
		else
		{
			textAAColor = OKColor::lightPink;
		}
		if (textBGColor == OKColor::black)
		{
			textShadowColor = OKColor::darkerPink;
		}
		else
		{
			textShadowColor = OKColor::lightPink;
		}
	}
	else if (optionBuffer == "BGBLACK")
	{
		textBGColor = OKColor::black;
		// TODO: if(textColor==COLOR)textAAColor=DARKCOLOR;
	}
	else if (optionBuffer == "BGWHITE")
	{
		textBGColor = OKColor::white;
		// TODO: if(textColor==COLOR)textAAColor=LIGHTCOLOR;
	}

	else if (optionBuffer == "CAM0" || optionBuffer == "CAMBOTTOM")
	{
		getCameraman()->setTarget(textBox->at(BOTTOM)->spriteWindowEntity);
		getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);
	}
	else if (optionBuffer == "CAM1" || optionBuffer == "CAMTOP")
	{
		getCameraman()->setTarget(textBox->at(TOP)->spriteWindowEntity);
		getCameraman()->setTicksPerPixelMoved((float)getCameraman()->ticksPerPixel_CAMERA_CONVERSATION);
	}
	else if (optionBuffer == "CLOSE1" || optionBuffer == "CLOSETOP")
	{
		selectedTextbox = BOTTOM;
		topBoxActivated = false;
	}
	else if (optionBuffer == "SHAKE1SEC")
	{
		textBox->at(selectedTextbox)->shakeTicksXTotal = 1000;
		//textBox->at(selectedTextbox).shakeTicksLeft = textBox->at(selectedTextbox).shakeTicksTotal;
	}
	else if (optionBuffer == "SHAKE2SEC")
	{
		textBox->at(selectedTextbox)->shakeTicksXTotal = 2000;
		//textBox->at(selectedTextbox).shakeTicksLeft = textBox->at(selectedTextbox).shakeTicksTotal;
	}

	else if (OKString::startsWith(optionBuffer, "SHAKE:"))
	{
		int ticks = 0;
		try
		{
			ticks = stoi(optionBuffer.substr(optionBuffer.find(":") + 1));
		}
		catch (exception)
		{
			log.error("Could not parse ticks in optionBuffer");
		}
		textBox->at(selectedTextbox)->shakeTicksXTotal = ticks;
		//textBox->at(selectedTextbox).shakeTicksLeft = textBox->at(selectedTextbox).shakeTicksTotal;
	}
	else
	{
		if (optionBuffer == "CLEAR")
		{
			textBox->at(selectedTextbox)->line = 0;
			textBox->at(selectedTextbox)->xInLine = 0;
			textBox->at(selectedTextbox)->clearByteArray();
			// /TEXT_update_textbox_sprite_textures();
			textBox->at(selectedTextbox)->redraw = true;
		}
		else if (optionBuffer == "NEXTLINE" || optionBuffer == "NEWLINE")
		{
			textBox->at(selectedTextbox)->xInLine = 0;
			textBox->at(selectedTextbox)->line++;
			if (textBox->at(selectedTextbox)->line > MAX_LINES)
			{
				waitingForButtonForNewPage = true;
			}
		}
		else if (optionBuffer == "DELAY")
		{
			delay = true;
			delayTicks = 300;
		}
		else if (optionBuffer == "DELAY30")
		{
			delay = true;
			delayTicks = 500;
		}
		else if (optionBuffer == "DELAY60")
		{
			delay = true;
			delayTicks = 1000;
		}
		else if (optionBuffer == "DELAY1SEC")
		{
			delay = true;
			delayTicks = 1000;
		}
		else if (optionBuffer == "DELAY2SEC")
		{
			delay = true;
			delayTicks = 2000;
		}
		else if (OKString::startsWith(optionBuffer, "DELAY:"))
		{
			int ticks = 0;
			try
			{
				ticks = stoi(optionBuffer.substr(optionBuffer.find(":") + 1));
			}
			catch (exception)
			{
				log.error("Could not parse ticks in optionBuffer");
			}
			delay = true;
			delayTicks = ticks;
		}
		else if (OKString::startsWith(optionBuffer, "TICKSPERLETTER:"))
		{
			int ticks = 0;
			try
			{
				ticks = stoi(optionBuffer.substr(optionBuffer.find(":") + 1));
			}
			catch (exception)
			{
				log.error("Could not parse ticks in optionBuffer");
			}

			ticksPerLetter = ticks;
		}
		else if (optionBuffer == "KEEPOPENAFTER")
		{
			keepOpenForNewText = true;
		}
		else if (optionBuffer == "NOCANCEL")
		{
			cannotCancel = true;
		}
		else if (optionBuffer == "YUU" || optionBuffer == "PLAYER")
		{
			if (getPlayer() != nullptr)
			{
				textBox->at(selectedTextbox)->setSpriteWindow(getPlayer(), nullptr, "");
				getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
			}
			else
			{
				textBox->at(selectedTextbox)->setSpriteWindow(getCameraman()->targetEntity, nullptr, "");
			}
		}
		else if (optionBuffer == "MOM")
		{
			sp<Entity> e = getCurrentMap()->getEntityByName("mom");
			if (e == nullptr)
			{
				return;
			}
			textBox->at(selectedTextbox)->setSpriteWindow(e, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "DAD")
		{
			sp<Entity> e = getCurrentMap()->getEntityByName("dad");
			if (e == nullptr)
			{
				return;
			}
			textBox->at(selectedTextbox)->setSpriteWindow(e, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "BROTHER")
		{
			sp<Entity> e = getCurrentMap()->getEntityByName("brother");
			if (e == nullptr)
			{
				return;
			}
			textBox->at(selectedTextbox)->setSpriteWindow(e, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC1")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity1, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC2")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity2, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC3")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity3, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC4")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity4, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC5")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity5, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (optionBuffer == "NPC6")
		{
			textBox->at(selectedTextbox)->setSpriteWindow(optionTargetEntity6, nullptr, "");
			getCameraman()->setTarget(textBox->at(selectedTextbox)->spriteWindowEntity);
		}
		else if (OKString::startsWith(optionBuffer, "SETSPRITEBOX0TOENTITY:"))
		{
			string s = optionBuffer.substr(optionBuffer.find(":") + 1);
			sp<Entity> e = getCurrentMap()->getEntityByName(s);
			if (e != nullptr)
			{
				textBox->at(0)->setSpriteWindow(e, nullptr, "");
			}
		}
		else if (OKString::startsWith(optionBuffer, "SETSPRITEBOX1TOENTITY:"))
		{
			string s = optionBuffer.substr(optionBuffer.find(":") + 1);
			sp<Entity> e = getCurrentMap()->getEntityByName(s);
			if (e != nullptr)
			{
				textBox->at(1)->setSpriteWindow(e, nullptr, "");
			}
		}
		else if (OKString::startsWith(optionBuffer, "SETSPRITEBOX0TOSPRITE:"))
		{
			string s = optionBuffer.substr(optionBuffer.find(":") + 1);
			sp<Sprite> e = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("SPRITE." + s);
			if (e != nullptr)
			{
				textBox->at(0)->setSpriteWindow(nullptr, e->texture, e->getDisplayName());
			}
		}
		else if (OKString::startsWith(optionBuffer, "SETSPRITEBOX1TOSPRITE:"))
		{
			string s = optionBuffer.substr(optionBuffer.find(":") + 1);
			sp<Sprite> e = getSpriteManager()->getSpriteByNameOrRequestFromServerIfNotExist("SPRITE." + s);
			if (e != nullptr)
			{
				textBox->at(1)->setSpriteWindow(nullptr, e->texture, e->getDisplayName());
			}
		}
		else if (OKString::startsWith(optionBuffer, "PITCH:"))
		{
			float pitch = 1.0f;
			try
			{
				pitch = stof(optionBuffer.substr(6));
			}
			catch(exception)
			{
				log.error("Could not parse pitch");
			}

			textBox->at(selectedTextbox)->voicePitch = pitch;
		}
		else if (OKString::startsWith(optionBuffer, "Q:"))
		{
			getAnswerToQuestionWithQuestionBox(optionBuffer, optionLength);
		}
		else if (optionBuffer == "KEYBOARD")
		{
			getTextFromOnscreenKeyboard();
		}
		else if (optionBuffer == "NUMPAD")
		{
			getNumberFromOnscreenNumpad();
		}
		else
		{
			string e = "Unknown tag parsed in TextEngine: " + optionBuffer;
			Main::console->error(e);
			log.error(e);
		}
	}
}

void TextManager::dialogue(sp<Dialogue> d)
{
	// TODO

	text(d->text());
	// d.tellServerDialogueDone();//do this after getText is completed.

	d->setDialogueDoneValue_S(true); // tells the server we have completed this getText
	// TODO: need to set this value after the getText has completed, otherwise it gets set even if we skip the getText.
}

void TextManager::getTextFromOnscreenKeyboard()
{
	// TODO
	// TODO
	// TODO
	// TODO
	// TODO
}

void TextManager::getNumberFromOnscreenNumpad()
{
	// TODO
	// TODO
	// TODO
	// TODO
	// TODO
}

void TextManager::getAnswerToQuestionWithQuestionBox(const string& s, int i)
{
	// TODO
	// TODO
	// TODO
	// TODO
	// TODO
}

