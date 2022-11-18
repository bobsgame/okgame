#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------





Logger OKFont::log = Logger("OKFont");


sp<TTF_Font> OKFont::ttf_bobsgame_8 = nullptr;
sp<TTF_Font> OKFont::ttf_bobsgame_16 = nullptr;
sp<TTF_Font> OKFont::ttf_6 = nullptr;
sp<TTF_Font> OKFont::ttf_7 = nullptr;
sp<TTF_Font> OKFont::ttf_8 = nullptr;
sp<TTF_Font> OKFont::ttf_9 = nullptr;
sp<TTF_Font> OKFont::ttf_10 = nullptr;
sp<TTF_Font> OKFont::ttf_11 = nullptr;
sp<TTF_Font> OKFont::ttf_12 = nullptr;
sp<TTF_Font> OKFont::ttf_13 = nullptr;
sp<TTF_Font> OKFont::ttf_14 = nullptr;
sp<TTF_Font> OKFont::ttf_15 = nullptr;
sp<TTF_Font> OKFont::ttf_16 = nullptr;
sp<TTF_Font> OKFont::ttf_17 = nullptr;
sp<TTF_Font> OKFont::ttf_18 = nullptr;
sp<TTF_Font> OKFont::ttf_19 = nullptr;
sp<TTF_Font> OKFont::ttf_20 = nullptr;
sp<TTF_Font> OKFont::ttf_21 = nullptr;
sp<TTF_Font> OKFont::ttf_22 = nullptr;
sp<TTF_Font> OKFont::ttf_23 = nullptr;
sp<TTF_Font> OKFont::ttf_24 = nullptr;
sp<TTF_Font> OKFont::ttf_25 = nullptr;
sp<TTF_Font> OKFont::ttf_26 = nullptr;
sp<TTF_Font> OKFont::ttf_27 = nullptr;
sp<TTF_Font> OKFont::ttf_28 = nullptr;
sp<TTF_Font> OKFont::ttf_29 = nullptr;
sp<TTF_Font> OKFont::ttf_30 = nullptr;
sp<TTF_Font> OKFont::ttf_31 = nullptr;
sp<TTF_Font> OKFont::ttf_32 = nullptr;
sp<TTF_Font> OKFont::ttf_48 = nullptr;
sp<TTF_Font> OKFont::ttf_64 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_6 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_7 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_8 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_9 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_10 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_11 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_12 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_13 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_14 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_15 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_16 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_17 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_18 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_19 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_20 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_21 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_22 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_23 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_24 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_25 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_26 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_27 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_28 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_29 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_30 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_31 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_32 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_48 = nullptr;
sp<TTF_Font> OKFont::ttf_outline_64 = nullptr;


sp<OKFont> OKFont::font_32 = nullptr;
sp<OKFont> OKFont::font_bob_16 = nullptr;
sp<OKFont> OKFont::font_bob_16_shadow2 = nullptr;
sp<OKFont> OKFont::font_bob_8 = nullptr;
sp<OKFont> OKFont::font_bob_8_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_11 = nullptr;
sp<OKFont> OKFont::font_normal_11_outlined = nullptr;
sp<OKFont> OKFont::font_normal_11_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_16 = nullptr;
sp<OKFont> OKFont::font_normal_16_outlined_smooth = nullptr;
sp<OKFont> OKFont::font_normal_16_outlined_blocky = nullptr;
sp<OKFont> OKFont::font_normal_16_outlined_blocky_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_16_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_8 = nullptr;
sp<OKFont> OKFont::font_normal_8_outlined = nullptr;
sp<OKFont> OKFont::font_normal_8_outlined_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_8_outlined_shadow2 = nullptr;
sp<OKFont> OKFont::font_normal_8_shadow1 = nullptr;
sp<OKFont> OKFont::font_normal_8_shadow3 = nullptr;
sp<OKFont> OKFont::font_small_16 = nullptr;
sp<OKFont> OKFont::font_small_16_shadow3 = nullptr;
sp<OKFont> OKFont::font_small_16_outlined_smooth = nullptr;
sp<OKFont> OKFont::font_small_16_outlined_smooth_shadow = nullptr;
sp<OKFont> OKFont::font_small_16_outlined_blocky = nullptr;
sp<OKFont> OKFont::font_small_8 = nullptr;
sp<OKFont> OKFont::font_small_8_outlined = nullptr;
sp<OKFont> OKFont::font_small_8_shadow1 = nullptr;

//=========================================================================================================================
OKFont::OKFont(const string& filename, int maxCharHeight, int blockHeight, bool outlined)
{//=========================================================================================================================


	this->filename = filename;
	this->maxCharHeight = maxCharHeight;
	this->blockHeight = blockHeight;
	this->outlined = outlined;
	//this.blockWidth = blockWidth;

	byteArray = FileUtils::loadByteFileFromExePath(filename);
}


//=========================================================================================================================
void OKFont::initFonts()
{//=========================================================================================================================

	log.debug("Init fonts");

	Uint64 start=0, now=0, totalStart, totalNow;
	start = SDL_GetPerformanceCounter();
	totalStart = SDL_GetPerformanceCounter();

 //-----------------------------
 //init TTF
 //-----------------------------
	TTF_Init();

	now = SDL_GetPerformanceCounter();
	log.debug("TTF Init took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();


	string path = Main::getPath();
	ttf_bobsgame_8 = ms<TTF_Font>(TTF_OpenFont(string(path+"data/fonts/bobsgame.ttf").c_str(), 8));
	ttf_bobsgame_16 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/bobsgame.ttf").c_str(), 16));

	ttf_6 =  ms<TTF_Font>(TTF_OpenFont(string(path+"data/fonts/Muli-Bold.ttf").c_str(), 6));
	ttf_7 =  ms<TTF_Font>(TTF_OpenFont(string(path+"data/fonts/Muli-Bold.ttf").c_str(), 7));
	ttf_8 =  ms<TTF_Font>(TTF_OpenFont(string(path+"data/fonts/Muli-Bold.ttf").c_str(), 8));
	ttf_9 =  ms<TTF_Font>(TTF_OpenFont(string(path+"data/fonts/Muli-Bold.ttf").c_str(), 9));
	ttf_10 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 10));
	ttf_11 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 11));
	ttf_12 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 12));
	ttf_13 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 13));
	ttf_14 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 14));
	ttf_15 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 15));
	ttf_16 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 16));
	ttf_17 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 17));
	ttf_18 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 18));
	ttf_19 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 19));
	ttf_20 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 20));
	ttf_21 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 21));
	ttf_22 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 22));
	ttf_23 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 23));
	ttf_24 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 24));
	ttf_25 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 25));
	ttf_26 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 26));
	ttf_27 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 27));
	ttf_28 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 28));
	ttf_29 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 29));
	ttf_30 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 30));
	ttf_31 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 31));
	ttf_32 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 32));
	ttf_48 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 48));
	ttf_64 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 64));

	now = SDL_GetPerformanceCounter();
	log.debug("Load fonts took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();

	ttf_outline_6 =  ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 6));
	ttf_outline_7 =  ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 7));
	ttf_outline_8 =  ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 8));
	ttf_outline_9 =  ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 9));
	ttf_outline_10 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 10));
	ttf_outline_11 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 11));
	ttf_outline_12 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 12));
	ttf_outline_13 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 13));
	ttf_outline_14 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 14));
	ttf_outline_15 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 15));
	ttf_outline_16 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 16));
	ttf_outline_17 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 17));
	ttf_outline_18 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 18));
	ttf_outline_19 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 19));
	ttf_outline_20 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 20));
	ttf_outline_21 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 21));
	ttf_outline_22 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 22));
	ttf_outline_23 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 23));
	ttf_outline_24 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 24));
	ttf_outline_25 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 25));
	ttf_outline_26 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 26));
	ttf_outline_27 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 27));
	ttf_outline_28 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 28));
	ttf_outline_29 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 29));
	ttf_outline_30 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 30));
	ttf_outline_31 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 31));
	ttf_outline_32 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 32));
	ttf_outline_48 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 48));
	ttf_outline_64 = ms<TTF_Font>(TTF_OpenFont(string(path + "data/fonts/Muli-Bold.ttf").c_str(), 64));

	TTF_SetFontOutline(ttf_outline_6.get(), 1);
	TTF_SetFontOutline(ttf_outline_7.get(), 1);
	TTF_SetFontOutline(ttf_outline_8.get(), 1);
	TTF_SetFontOutline(ttf_outline_9.get(), 1);
	TTF_SetFontOutline(ttf_outline_10.get(), 1);
	TTF_SetFontOutline(ttf_outline_11.get(), 1);
	TTF_SetFontOutline(ttf_outline_12.get(), 1);
	TTF_SetFontOutline(ttf_outline_13.get(), 1);
	TTF_SetFontOutline(ttf_outline_14.get(), 1);
	TTF_SetFontOutline(ttf_outline_15.get(), 1);
	TTF_SetFontOutline(ttf_outline_16.get(), 1);
	TTF_SetFontOutline(ttf_outline_17.get(), 1);
	TTF_SetFontOutline(ttf_outline_18.get(), 1);
	TTF_SetFontOutline(ttf_outline_19.get(), 1);
	TTF_SetFontOutline(ttf_outline_20.get(), 1);
	TTF_SetFontOutline(ttf_outline_21.get(), 1);
	TTF_SetFontOutline(ttf_outline_22.get(), 1);
	TTF_SetFontOutline(ttf_outline_23.get(), 1);
	TTF_SetFontOutline(ttf_outline_24.get(), 1);
	TTF_SetFontOutline(ttf_outline_25.get(), 1);
	TTF_SetFontOutline(ttf_outline_26.get(), 1);
	TTF_SetFontOutline(ttf_outline_27.get(), 1);
	TTF_SetFontOutline(ttf_outline_28.get(), 1);
	TTF_SetFontOutline(ttf_outline_29.get(), 1);
	TTF_SetFontOutline(ttf_outline_30.get(), 1);
	TTF_SetFontOutline(ttf_outline_31.get(), 1);
	TTF_SetFontOutline(ttf_outline_32.get(), 1);
	TTF_SetFontOutline(ttf_outline_48.get(), 1);
	TTF_SetFontOutline(ttf_outline_64.get(), 1);

	now = SDL_GetPerformanceCounter();
	log.debug("Load outline fonts took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();

	//sp<FreeTypeFontGenerator>generator = ms<FreeTypeFontGenerator>(Gdx::files::internal("fonts/OpenSans-Regular.ttf"));
	//sp<BitmapFont>font12 = generator->generateFont(12); // font size 12 pixels
	//sp<BitmapFont>font25 = generator->generateFont(25); // font size 25 pixels
	//generator->dispose(); // don't forget to dispose to avoid memory leaks!


	//font12.draw(batch,str,x,y);


	font_Palette_ByteArray = FileUtils::loadByteFileFromExePath("data/fonts/text.pal");// "assets/fonts/getText.pal");


	//fontTinyByteArray = FileUtils::HARDWARE_load_file("assets/fonts/font_tiny.bin");
	//fontHugeByteArray = FileUtils::HARDWARE_load_file("assets/fonts/font_huge.bin");


	font_32 = ms<OKFont>("data/fonts/font_32.bin", 32, 64, false);
	font_32->blockWidth = 64;

	font_bob_16 = ms<OKFont>("data/fonts/font_bob_16_hq2x.bin", 36, 32, false); //fix height
	font_bob_16_shadow2 = ms<OKFont>("data/fonts/font_bob_16_hq2x_shadow2.bin", 38, 32, false); //fix height

	font_bob_8 = ms<OKFont>("data/fonts/font_bob_8.bin", 20, 16, false); //fix height
	font_bob_8_shadow1 = ms<OKFont>("data/fonts/font_bob_8_shadow1.bin", 22, 16, false); //fix height

	font_normal_11 = ms<OKFont>("data/fonts/font_normal_11.bin", 15, 24, false);
	font_normal_11_outlined = ms<OKFont>("data/fonts/font_normal_11_outlined.bin", 17, 24, true);
	font_normal_11_shadow1 = ms<OKFont>("data/fonts/font_normal_11_shadow1.bin", 16, 24, false);

	font_normal_16 = ms<OKFont>("data/fonts/font_normal_16_hq2x.bin", 20, 32, false);
	font_normal_16_outlined_smooth = ms<OKFont>("data/fonts/font_normal_16_hq2x_outlined.bin", 22, 32, true);
	font_normal_16_outlined_blocky = ms<OKFont>("data/fonts/font_normal_16_nearest2x_outlined.bin", 22, 32, true);
	font_normal_16_outlined_blocky_shadow1 = ms<OKFont>("data/fonts/font_normal_16_nearest2x_outlined_shadow1.bin", 23, 32, true);
	font_normal_16_shadow1 = ms<OKFont>("data/fonts/font_normal_16_hq2x_shadow.bin", 22, 32, false);

	font_normal_8 = ms<OKFont>("data/fonts/font_normal_8.bin", 10, 16, false);
	font_normal_8_outlined = ms<OKFont>("data/fonts/font_normal_8_outlined.bin", 12, 16, true);
	font_normal_8_outlined_shadow1 = ms<OKFont>("data/fonts/font_normal_8_outlined_shadow1.bin", 13, 16, true);
	font_normal_8_outlined_shadow2 = ms<OKFont>("data/fonts/font_normal_8_outlined_shadow2.bin", 14, 16, true);
	font_normal_8_shadow1 = ms<OKFont>("data/fonts/font_normal_8_shadow1.bin", 11, 16, false);
	font_normal_8_shadow3 = ms<OKFont>("data/fonts/font_normal_8_shadow3.bin", 13, 16, false);

	font_small_16 = ms<OKFont>("data/fonts/font_small_16_hq2x.bin", 18, 32, false);
	font_small_16_shadow3 = ms<OKFont>("data/fonts/font_small_16_hq2x_shadow3.bin", 20, 32, false);
	font_small_16_outlined_smooth = ms<OKFont>("data/fonts/font_small_16_hq2x_outlined.bin", 20, 32, true);
	font_small_16_outlined_smooth_shadow = ms<OKFont>("data/fonts/font_small_16_hq2x_outlined_shadow2.bin", 20, 32, true);
	font_small_16_outlined_blocky = ms<OKFont>("data/fonts/font_small_16_nearest2x_outlined.bin", 20, 32, true);

	font_small_8 = ms<OKFont>("data/fonts/font_small_8.bin", 9, 16, false);
	font_small_8_outlined = ms<OKFont>("data/fonts/font_small_8_outlined.bin", 11, 16, true);
	font_small_8_shadow1 = ms<OKFont>("data/fonts/font_small_8_shadow1.bin", 10, 16, false);


	now = SDL_GetPerformanceCounter();
	log.debug("Load bitmap fonts took " + to_string((double)((now - start) * 1000) / SDL_GetPerformanceFrequency()) + "ms");
	start = SDL_GetPerformanceCounter();


	totalNow = SDL_GetPerformanceCounter();
	log.debug("Init fonts took " + to_string((double)((totalNow - totalStart) * 1000) / SDL_GetPerformanceFrequency()) + "ms");


}


//=========================================================================================================================
void OKFont::cleanup()
{//=========================================================================================================================

	log.info("OKFont::cleanup");

	TTF_CloseFont(ttf_bobsgame_8.get());
	TTF_CloseFont(ttf_bobsgame_16.get());

	

}




//=========================================================================================================================
void OKFont::change_font()
{//=========================================================================================================================
}


//=========================================================================================================================
bool OKFont::is_a_vowel(char c)
{//=========================================================================================================================

	switch (c)
	{
	case 'a':
	case 'e':
	case 'i':
	case 'o':
	case 'u':
	case 'y':
	case 'A':
	case 'E':
	case 'I':
	case 'O':
	case 'U':
	case 'Y':
		return true;
	default:
		return false;
	}
}


//=========================================================================================================================
int OKFont::getFontIndexForChar(char c)
{//=========================================================================================================================
	int i = -1;
	switch (c)
	{
	case 'A':
		{
			i = CHAR_A;
			break;
		}
	case 'B':
		{
			i = CHAR_B;
			break;
		}
	case 'C':
		{
			i = CHAR_C;
			break;
		}
	case 'D':
		{
			i = CHAR_D;
			break;
		}
	case 'E':
		{
			i = CHAR_E;
			break;
		}
	case 'F':
		{
			i = CHAR_F;
			break;
		}
	case 'G':
		{
			i = CHAR_G;
			break;
		}
	case 'H':
		{
			i = CHAR_H;
			break;
		}
	case 'I':
		{
			i = CHAR_I;
			break;
		}
	case 'J':
		{
			i = CHAR_J;
			break;
		}
	case 'K':
		{
			i = CHAR_K;
			break;
		}
	case 'L':
		{
			i = CHAR_L;
			break;
		}
	case 'M':
		{
			i = CHAR_M;
			break;
		}
	case 'N':
		{
			i = CHAR_N;
			break;
		}
	case 'O':
		{
			i = CHAR_O;
			break;
		}
	case 'P':
		{
			i = CHAR_P;
			break;
		}
	case 'Q':
		{
			i = CHAR_Q;
			break;
		}
	case 'R':
		{
			i = CHAR_R;
			break;
		}
	case 'S':
		{
			i = CHAR_S;
			break;
		}
	case 'T':
		{
			i = CHAR_T;
			break;
		}
	case 'U':
		{
			i = CHAR_U;
			break;
		}
	case 'V':
		{
			i = CHAR_V;
			break;
		}
	case 'W':
		{
			i = CHAR_W;
			break;
		}
	case 'X':
		{
			i = CHAR_X;
			break;
		}
	case 'Y':
		{
			i = CHAR_Y;
			break;
		}
	case 'Z':
		{
			i = CHAR_Z;
			break;
		}
	case 'a':
		{
			i = CHAR_a;
			break;
		}
	case 'b':
		{
			i = CHAR_b;
			break;
		}
	case 'c':
		{
			i = CHAR_c;
			break;
		}
	case 'd':
		{
			i = CHAR_d;
			break;
		}
	case 'e':
		{
			i = CHAR_e;
			break;
		}
	case 'f':
		{
			i = CHAR_f;
			break;
		}
	case 'g':
		{
			i = CHAR_g;
			break;
		}
	case 'h':
		{
			i = CHAR_h;
			break;
		}
	case 'i':
		{
			i = CHAR_i;
			break;
		}
	case 'j':
		{
			i = CHAR_j;
			break;
		}
	case 'k':
		{
			i = CHAR_k;
			break;
		}
	case 'l':
		{
			i = CHAR_l;
			break;
		}
	case 'm':
		{
			i = CHAR_m;
			break;
		}
	case 'n':
		{
			i = CHAR_n;
			break;
		}
	case 'o':
		{
			i = CHAR_o;
			break;
		}
	case 'p':
		{
			i = CHAR_p;
			break;
		}
	case 'q':
		{
			i = CHAR_q;
			break;
		}
	case 'r':
		{
			i = CHAR_r;
			break;
		}
	case 's':
		{
			i = CHAR_s;
			break;
		}
	case 't':
		{
			i = CHAR_t;
			break;
		}
	case 'u':
		{
			i = CHAR_u;
			break;
		}
	case 'v':
		{
			i = CHAR_v;
			break;
		}
	case 'w':
		{
			i = CHAR_w;
			break;
		}
	case 'x':
		{
			i = CHAR_x;
			break;
		}
	case 'y':
		{
			i = CHAR_y;
			break;
		}
	case 'z':
		{
			i = CHAR_z;
			break;
		}
	case '.':
		{
			i = CHAR_PERIOD;
			break;
		}
	case ',':
		{
			i = CHAR_COMMA;
			break;
		}
	case '\'':
		{
			i = CHAR_QUOTE;
			break;
		} // /'
		//   case '�':
		//      {
		//         i = CHAR_QUOTE;
		//         break;
		//      } // /'
	case '!':
		{
			i = CHAR_EXCLAMATION;
			break;
		}

	case '?':
	{
		i = CHAR_QUESTIONMARK;
		break;
	}
		
	case '=':
		{
			i = CHAR_EQUALS;
			break;
		}
	case '\\':
		{
			i = CHAR_BACKSLASH;
			break;
		}
	case '/':
		{
			i = CHAR_FRONTSLASH;
			break;
		}
	case '^':
		{
			i = CHAR_CARET;
			break;
		}
	case '_':
		{
			i = CHAR_UNDERSCORE;
			break;
		}
	case '&':
		{
			i = CHAR_AMPERSAND;
			break;
		}
	case '+':
		{
			i = CHAR_PLUS;
			break;
		}
	case '#':
		{
			i = CHAR_POUND;
			break;
		}
	case '$':
		{
			i = CHAR_DOLLAR;
			break;
		}
	case '%':
		{
			i = CHAR_PERCENT;
			break;
		}
	case '(':
		{
			i = CHAR_OPENPARENTHESIS;
			break;
		}
	case ')':
		{
			i = CHAR_CLOSEPARENTHESIS;
			break;
		}
	case '"':
		{
			i = CHAR_DOUBLEQUOTE;
			break;
		}
	case '*':
		{
			i = CHAR_ASTERISK;
			break;
		}
	case '-':
		{
			i = CHAR_MINUS;
			break;
		}
	case ':':
		{
			i = CHAR_COLON;
			break;
		}
	case ';':
		{
			i = CHAR_SEMICOLON;
			break;
		}
	case '|':
		{
			i = CHAR_PIPE;
			break;
		}
	case '`':
		{
			i = CHAR_BACKQUOTE;
			break;
		}
	case '~':
		{
			i = CHAR_TILDE;
			break;
		}
	case '@':
		{
			i = CHAR_AT;
			break;
		}
	case '{':
		{
			i = CHAR_OPENCURLYBRACKET;
			break;
		}
	case '}':
		{
			i = CHAR_CLOSECURLYBRACKET;
			break;
		}
	case '[':
		{
			i = CHAR_OPENSQUAREBRACKET;
			break;
		}
	case ']':
		{
			i = CHAR_CLOSESQUAREBRACKET;
			break;
		}
	case '0':
		{
			i = CHAR_0;
			break;
		}
	case '1':
		{
			i = CHAR_1;
			break;
		}
	case '2':
		{
			i = CHAR_2;
			break;
		}
	case '3':
		{
			i = CHAR_3;
			break;
		}
	case '4':
		{
			i = CHAR_4;
			break;
		}
	case '5':
		{
			i = CHAR_5;
			break;
		}
	case '6':
		{
			i = CHAR_6;
			break;
		}
	case '7':
		{
			i = CHAR_7;
			break;
		}
	case '8':
		{
			i = CHAR_8;
			break;
		}
	case '9':
		{
			i = CHAR_9;
			break;
		}
		/*
		case '�':
		{
		   i = CHAR_dN;
		   break;
		}
		case '�':
		{
		   i = CHAR_aa;
		   break;
		}
		case '�':
		{
		   i = CHAR_ae;
		   break;
		}
		case '�':
		{
		   i = CHAR_ai;
		   break;
		}
		case '�':
		{
		   i = CHAR_ao;
		   break;
		}
		case '�':
		{
		   i = CHAR_au;
		   break;
		}
		case '�':
		{
		   i = CHAR_dn;
		   break;
		}
		case '�':
		{
		   i = CHAR_iE;
		   break;
		}
		case '�':
		{
		   i = CHAR_iQ;
		   break;
		}
		case '�':
		{
		   i = CHAR_aE;
		   break;
		}
		case '�':
		{
		   i = CHAR_aI;
		   break;
		}
		case '�':
		{
		   i = CHAR_aA;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_RR;
		   break;
		}
		case '�':
		{
		   i = CHAR_LL;
		   break;
		}
		case '�':
		{
		   i = CHAR_ca;
		   break;
		}
		case '�':
		{
		   i = CHAR_ce;
		   break;
		}
		case '�':
		{
		   i = CHAR_ci;
		   break;
		}
		case '�':
		{
		   i = CHAR_co;
		   break;
		}
		case '�':
		{
		   i = CHAR_cu;
		   break;
		}
		case '�':
		{
		   i = CHAR_ga;
		   break;
		}
		case '�':
		{
		   i = CHAR_ge;
		   break;
		}
		case '�':
		{
		   i = CHAR_de;
		   break;
		}
		case '�':
		{
		   i = CHAR_cc;
		   break;
		}
		case '�':
		{
		   i = CHAR_lo;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_aO;
		   break;
		}
		case '�':
		{
		   i = CHAR_gu;
		   break;
		}
  
		case '�':
		{
		   i = CHAR_dI;
		   break;
		}
		case '�':
		{
		   i = CHAR_dA;
		   break;
		}
		case '�':
		{
		   i = CHAR_dO;
		   break;
		}
		case '�':
		{
		   i = CHAR_dU;
		   break;
		}
		case '�':
		{
		   i = CHAR_da;
		   break;
		}
		case '�':
		{
		   i = CHAR_do;
		   break;
		}
		case '�':
		{
		   i = CHAR_du;
		   break;
		}
		case '�':
		{
		   i = CHAR_dB;
		   break;
		}
		*/

	case ' ':
		{
			i = CHAR_SPACE;
			break;
		}

	case '\n':
		{
			i = -1;
			break;
		}

	case '<':
		{
			string e = "Parsed a '<'.";

			log.error(e);

			i = -1;
			break;
		}
	case '>':
		{
			string e = "Parsed a '>'.";

			log.error(e);

			i = -1;
			break;
		}

	default:
		{
			i = CHAR_BLOCK;
			break;
		}
	}

	return i;
}


//=========================================================================================================================
int OKFont::getNextWordLength(const string& text, int in_position, sp<OKFont> font)
{//=========================================================================================================================

	int next_word_length = 0;

	int length = (int)text.length();

	int temp_position = in_position;

	while (temp_position < length && (text[temp_position] != ' ' || temp_position == in_position) && isCurrentPositionANewline(text, temp_position) == false)
	//we should be starting on a space or the beginning of the test. include the starting space, up to the next space
	//&&
	//getText.charAt(temp_position)!='<'
	{
		//skip over tags
		if (temp_position < length && text[temp_position] == '<')
		{
			int x = 0;
			while (temp_position + x < length && text[temp_position + x] != '>')
			{
				x++;
			}
			temp_position += x;
			temp_position++; //for the '>'

			continue;
		}

		if (temp_position < length)
		{
			next_word_length += getCharWidth(OKFont::getFontIndexForChar(text[temp_position]), font);
			//add a space between letters for all fonts but outlined
			//if(font_id!=OKFont.FONT_OUTLINED_ID)
			next_word_length++;

			temp_position++;
		}
	}


	return next_word_length;
}


//=========================================================================================================================
bool OKFont::isCurrentPositionANewline(const string& t, int position)
{//=========================================================================================================================
	if ((t[position] == '\n') || (position < (int)t.length() - 1 && t[position] == '<' && t[position + 1] == '.') || (position < (int)t.length() - 2 && t[position] == '<' && t[position + 1] == 'N' && t[position + 2] == 'E')) //newline - or its a newline
	{
		return true;
	}
	else
	{
		return false;
	}
}


//=========================================================================================================================
int OKFont::getFontPixelValueAtIndex(int index, sp<OKFont> font)
{//=========================================================================================================================

	if(font==nullptr || font == NULL)
	{
		log.error("OKFont::getFontPixelValueAtIndex font is null");
		return 0;
	}

//	int size = 0;
//	if (font != nullptr && font->byteArray != nullptr)size = (int)GOOGLE_ARRAYSIZE(font->byteArray);
//
//
//	if (index >= size)
//	{
//		log.error("OKFont::getFontPixelValueAtIndex index >=size should never happen!");
//		return -1;
//	}
	return font->byteArray->data()[index];
}


//=========================================================================================================================
int OKFont::getCharWidth(int letter_index, sp<OKFont> font)
{//=========================================================================================================================

	if (letter_index == -1)
	{
		return 0;
	}

	int x = 0;
	int y = 0;
	int w = 0;
	int blockWidth = 0;
	int blockHeight = 0;
	int maxCharHeight = 0;

	if (font != nullptr)blockWidth = font->blockWidth;
	if (font != nullptr)blockHeight = font->blockHeight;
	if (font != nullptr)maxCharHeight = font->maxCharHeight;

	for (x = blockWidth - 1; x >= 0; x--)
	{
		for (y = 0; y < maxCharHeight; y++)
		{
			if (OKFont::getFontPixelValueAtIndex((letter_index * blockWidth * blockHeight) + (y * blockWidth) + x, font) != 0)
			{
				w = x + 1;
				x = -1;
				y = maxCharHeight;
				break;
			}
		}
	}

	if (letter_index == OKFont::getFontIndexForChar(' '))
	{
		w = 3;

		if (maxCharHeight > 10)
		{
			w = 5;
		}

		//WIDTH OF SPACE IS DETERMINED HERE //was 3?
	}

	return w;
}

int OKFont::CHAR_A = 0;
int OKFont::CHAR_B = 1;
int OKFont::CHAR_C = 2;
int OKFont::CHAR_D = 3;
int OKFont::CHAR_E = 4;
int OKFont::CHAR_F = 5;
int OKFont::CHAR_G = 6;
int OKFont::CHAR_H = 7;
int OKFont::CHAR_I = 8;
int OKFont::CHAR_J = 9;
int OKFont::CHAR_K = 10;
int OKFont::CHAR_L = 11;
int OKFont::CHAR_M = 12;
int OKFont::CHAR_N = 13;
int OKFont::CHAR_O = 14;
int OKFont::CHAR_P = 15;
int OKFont::CHAR_Q = 16;
int OKFont::CHAR_R = 17;
int OKFont::CHAR_S = 18;
int OKFont::CHAR_T = 19;
int OKFont::CHAR_U = 20;
int OKFont::CHAR_V = 21;
int OKFont::CHAR_W = 22;
int OKFont::CHAR_X = 23;
int OKFont::CHAR_Y = 24;
int OKFont::CHAR_Z = 25;
int OKFont::CHAR_a = 26;
int OKFont::CHAR_b = 27;
int OKFont::CHAR_c = 28;
int OKFont::CHAR_d = 29;
int OKFont::CHAR_e = 30;
int OKFont::CHAR_f = 31;
int OKFont::CHAR_g = 32;
int OKFont::CHAR_h = 33;
int OKFont::CHAR_i = 34;
int OKFont::CHAR_j = 35;
int OKFont::CHAR_k = 36;
int OKFont::CHAR_l = 37;
int OKFont::CHAR_m = 38;
int OKFont::CHAR_n = 39;
int OKFont::CHAR_o = 40;
int OKFont::CHAR_p = 41;
int OKFont::CHAR_q = 42;
int OKFont::CHAR_r = 43;
int OKFont::CHAR_s = 44;
int OKFont::CHAR_t = 45;
int OKFont::CHAR_u = 46;
int OKFont::CHAR_v = 47;
int OKFont::CHAR_w = 48;
int OKFont::CHAR_x = 49;
int OKFont::CHAR_y = 50;
int OKFont::CHAR_z = 51;
int OKFont::CHAR_0 = 52;
int OKFont::CHAR_1 = 53;
int OKFont::CHAR_2 = 54;
int OKFont::CHAR_3 = 55;
int OKFont::CHAR_4 = 56;
int OKFont::CHAR_5 = 57;
int OKFont::CHAR_6 = 58;
int OKFont::CHAR_7 = 59;
int OKFont::CHAR_8 = 60;
int OKFont::CHAR_9 = 61;
int OKFont::CHAR_EXCLAMATION = 62;
int OKFont::CHAR_QUESTIONMARK = 63;
int OKFont::CHAR_PERIOD = 64;
int OKFont::CHAR_COMMA = 65;
int OKFont::CHAR_QUOTE = 66;
int OKFont::CHAR_DOUBLEQUOTE = 67;
int OKFont::CHAR_COLON = 68;
int OKFont::CHAR_SEMICOLON = 69;
int OKFont::CHAR_FRONTSLASH = 70;
int OKFont::CHAR_BACKSLASH = 71;
int OKFont::CHAR_ASTERISK = 72;
int OKFont::CHAR_PLUS = 73;
int OKFont::CHAR_MINUS = 74;
int OKFont::CHAR_EQUALS = 75;
int OKFont::CHAR_UNDERSCORE = 76;
int OKFont::CHAR_CARET = 77;
int OKFont::CHAR_BACKQUOTE = 78;
int OKFont::CHAR_TILDE = 79;
int OKFont::CHAR_OPENPARENTHESIS = 80;
int OKFont::CHAR_CLOSEPARENTHESIS = 81;
int OKFont::CHAR_OPENANGLEBRACKET = 82;
int OKFont::CHAR_CLOSEANGLEBRACKET = 83;
int OKFont::CHAR_OPENCURLYBRACKET = 84;
int OKFont::CHAR_CLOSECURLYBRACKET = 85;
int OKFont::CHAR_OPENSQUAREBRACKET = 86;
int OKFont::CHAR_CLOSESQUAREBRACKET = 87;
int OKFont::CHAR_PIPE = 88;
int OKFont::CHAR_AT = 89;
int OKFont::CHAR_POUND = 90;
int OKFont::CHAR_DOLLAR = 91;
int OKFont::CHAR_PERCENT = 92;
int OKFont::CHAR_AMPERSAND = 93;
int OKFont::CHAR_BLOCK = 94;
int OKFont::CHAR_SPACE = 95;
int OKFont::CHAR_dN = 96;
int OKFont::CHAR_aa = 97;
int OKFont::CHAR_ae = 98;
int OKFont::CHAR_ai = 99;
int OKFont::CHAR_ao = 100;
int OKFont::CHAR_au = 101;
int OKFont::CHAR_dn = 102;
int OKFont::CHAR_iE = 103;
int OKFont::CHAR_iQ = 104;
int OKFont::CHAR_aE = 105;
int OKFont::CHAR_aI = 106;
int OKFont::CHAR_aA = 107;
int OKFont::CHAR_RR = 108;
int OKFont::CHAR_LL = 109;
int OKFont::CHAR_ca = 110;
int OKFont::CHAR_ce = 111;
int OKFont::CHAR_ci = 112;
int OKFont::CHAR_co = 113;
int OKFont::CHAR_cu = 114;
int OKFont::CHAR_ga = 115;
int OKFont::CHAR_ge = 116;
int OKFont::CHAR_de = 117;
int OKFont::CHAR_cc = 118;
int OKFont::CHAR_lo = 119;
int OKFont::CHAR_aO = 120;
int OKFont::CHAR_gu = 121;
int OKFont::CHAR_dI = 122;
int OKFont::CHAR_dA = 123;
int OKFont::CHAR_dO = 124;
int OKFont::CHAR_dU = 125;
int OKFont::CHAR_da = 126;
int OKFont::CHAR_do = 127;
int OKFont::CHAR_du = 128;
int OKFont::CHAR_dB = 129;

