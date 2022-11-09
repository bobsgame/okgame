//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


class Logger;



class OKFont
{
public:
	static Logger log;

	static sp<ByteArray> font_Palette_ByteArray;


	static sp<TTF_Font> ttf_bobsgame_8;
	static sp<TTF_Font> ttf_bobsgame_16;
	static sp<TTF_Font> ttf_6; 
	static sp<TTF_Font> ttf_7; 
	static sp<TTF_Font> ttf_8; 
	static sp<TTF_Font> ttf_9; 
	static sp<TTF_Font> ttf_10;
	static sp<TTF_Font> ttf_11;
	static sp<TTF_Font> ttf_12;
	static sp<TTF_Font> ttf_13;
	static sp<TTF_Font> ttf_14;
	static sp<TTF_Font> ttf_15;
	static sp<TTF_Font> ttf_16;
	static sp<TTF_Font> ttf_17;
	static sp<TTF_Font> ttf_18;
	static sp<TTF_Font> ttf_19;
	static sp<TTF_Font> ttf_20;
	static sp<TTF_Font> ttf_21;
	static sp<TTF_Font> ttf_22;
	static sp<TTF_Font> ttf_23;
	static sp<TTF_Font> ttf_24;
	static sp<TTF_Font> ttf_25;
	static sp<TTF_Font> ttf_26;
	static sp<TTF_Font> ttf_27;
	static sp<TTF_Font> ttf_28;
	static sp<TTF_Font> ttf_29;
	static sp<TTF_Font> ttf_30;
	static sp<TTF_Font> ttf_31;
	static sp<TTF_Font> ttf_32;
	static sp<TTF_Font> ttf_48;
	static sp<TTF_Font> ttf_64;
	static sp<TTF_Font> ttf_outline_6;
	static sp<TTF_Font> ttf_outline_7;
	static sp<TTF_Font> ttf_outline_8;
	static sp<TTF_Font> ttf_outline_9;
	static sp<TTF_Font> ttf_outline_10;
	static sp<TTF_Font> ttf_outline_11;
	static sp<TTF_Font> ttf_outline_12;
	static sp<TTF_Font> ttf_outline_13;
	static sp<TTF_Font> ttf_outline_14;
	static sp<TTF_Font> ttf_outline_15;
	static sp<TTF_Font> ttf_outline_16;
	static sp<TTF_Font> ttf_outline_17;
	static sp<TTF_Font> ttf_outline_18;
	static sp<TTF_Font> ttf_outline_19;
	static sp<TTF_Font> ttf_outline_20;
	static sp<TTF_Font> ttf_outline_21;
	static sp<TTF_Font> ttf_outline_22;
	static sp<TTF_Font> ttf_outline_23;
	static sp<TTF_Font> ttf_outline_24;
	static sp<TTF_Font> ttf_outline_25;
	static sp<TTF_Font> ttf_outline_26;
	static sp<TTF_Font> ttf_outline_27;
	static sp<TTF_Font> ttf_outline_28;
	static sp<TTF_Font> ttf_outline_29;
	static sp<TTF_Font> ttf_outline_30;
	static sp<TTF_Font> ttf_outline_31;
	static sp<TTF_Font> ttf_outline_32;
	static sp<TTF_Font> ttf_outline_48;
	static sp<TTF_Font> ttf_outline_64;


	string filename;
	int maxCharHeight = 12; //this is from the very top to the bottom below the baseline, including shadow
	//public int baselineHeight;//this is where the underhang part of "qypgj" starts and most letters end
	//public int shadowWidth;//this is how many pixels past the letter should be drawn but not counted as space

	int blockHeight = 32; //this is the height of each character block, including spacing between glyphs
	int blockWidth = 32; //this is the width of the input bitmap

	sp<ByteArray> byteArray = nullptr; //this holds the actual indexed pixel data

	bool outlined = false;


	OKFont(const string& filename, int maxCharHeight, int blockHeight, bool outlined);


	//static public byte[] fontTinyByteArray;
	//static public byte[] fontHugeByteArray;


	//	font_bob_16_hq2x.bin ... ok
	//	font_bob_16_shadow2_hq2x.bin ... ok

	//	font_bob_8.bin ... ok
	//	font_bob_8_shadow1.bin ... ok

	//	font_normal_11.bin ... ok
	//	font_normal_11_outlined.bin ... ok
	//	font_normal_11_shadow1.bin ... ok

	//	font_normal_16_hq2x.bin ... ok
	//	font_normal_16_outlined.bin ... ok
	//	font_normal_16_outlined_shadow1.bin
	//	font_normal_16_shadow_hq2x.bin ...

	//	font_normal_8.bin ... ok
	//	font_normal_8_outlined.bin ... ok
	//	font_normal_8_outlined_shadow1.bin
	//	font_normal_8_outlined_shadow2.bin

	//	font_normal_8_shadow1.bin ... ok
	//	font_normal_8_shadow3.bin ... ok

	//	font_small_16_hq2x.bin ... ok
	//	font_small_16_shadow3_hq2x.bin ...

	//	font_small_8.bin ... ok
	//	font_small_8_outlined.bin ... ok
	//	font_small_8_shadow1.bin ... ok

public:
	static sp<OKFont> font_32;

	static sp<OKFont> font_bob_16;
	static sp<OKFont> font_bob_16_shadow2;

	static sp<OKFont> font_bob_8;
	static sp<OKFont> font_bob_8_shadow1;

	static sp<OKFont> font_normal_11;
	static sp<OKFont> font_normal_11_outlined;
	static sp<OKFont> font_normal_11_shadow1;

	static sp<OKFont> font_normal_16;
	static sp<OKFont> font_normal_16_outlined_smooth;
	static sp<OKFont> font_normal_16_outlined_blocky;
	static sp<OKFont> font_normal_16_outlined_blocky_shadow1;
	static sp<OKFont> font_normal_16_shadow1;

	static sp<OKFont> font_normal_8;
	static sp<OKFont> font_normal_8_outlined;
	static sp<OKFont> font_normal_8_outlined_shadow1;
	static sp<OKFont> font_normal_8_outlined_shadow2;
	static sp<OKFont> font_normal_8_shadow1;
	static sp<OKFont> font_normal_8_shadow3;

	static sp<OKFont> font_small_16;
	static sp<OKFont> font_small_16_shadow3;
	static sp<OKFont> font_small_16_outlined_smooth;
	static sp<OKFont> font_small_16_outlined_smooth_shadow;
	static sp<OKFont> font_small_16_outlined_blocky;

	static sp<OKFont> font_small_8;
	static sp<OKFont> font_small_8_outlined;
	static sp<OKFont> font_small_8_shadow1;


	//static public int FONT_TINY_HEIGHT=7;
	//static public int FONT_HUGE_HEIGHT=12;


	//static public int FONT_HUGE_ID=3;
	//static public int FONT_TINY_ID=1;


	static void initFonts();
	static void cleanup();


	void change_font();


	static bool is_a_vowel(char c);


	static int getFontIndexForChar(char c);


	static int getNextWordLength(const string& text, int in_position, sp<OKFont> font);


	static bool isCurrentPositionANewline(const string& t, int position);


	static int getFontPixelValueAtIndex(int index, sp<OKFont> font);


	static int getCharWidth(int letter_index, sp<OKFont> font);


	//		 CHAR DEFINES


	static int CHAR_A;
	static int CHAR_B;
	static int CHAR_C;
	static int CHAR_D;
	static int CHAR_E;
	static int CHAR_F;
	static int CHAR_G;
	static int CHAR_H;
	static int CHAR_I;
	static int CHAR_J;
	static int CHAR_K;
	static int CHAR_L;
	static int CHAR_M;
	static int CHAR_N;
	static int CHAR_O;
	static int CHAR_P;
	static int CHAR_Q;
	static int CHAR_R;
	static int CHAR_S;
	static int CHAR_T;
	static int CHAR_U;
	static int CHAR_V;
	static int CHAR_W;
	static int CHAR_X;
	static int CHAR_Y;
	static int CHAR_Z;
	static int CHAR_a;
	static int CHAR_b;
	static int CHAR_c;
	static int CHAR_d;
	static int CHAR_e;
	static int CHAR_f;
	static int CHAR_g;
	static int CHAR_h;
	static int CHAR_i;
	static int CHAR_j;
	static int CHAR_k;
	static int CHAR_l;
	static int CHAR_m;
	static int CHAR_n;
	static int CHAR_o;
	static int CHAR_p;
	static int CHAR_q;
	static int CHAR_r;
	static int CHAR_s;
	static int CHAR_t;
	static int CHAR_u;
	static int CHAR_v;
	static int CHAR_w;
	static int CHAR_x;
	static int CHAR_y;
	static int CHAR_z;
	static int CHAR_0;
	static int CHAR_1;
	static int CHAR_2;
	static int CHAR_3;
	static int CHAR_4;
	static int CHAR_5;
	static int CHAR_6;
	static int CHAR_7;
	static int CHAR_8;
	static int CHAR_9;
	static int CHAR_EXCLAMATION;
	static int CHAR_QUESTIONMARK;
	static int CHAR_PERIOD;
	static int CHAR_COMMA;
	static int CHAR_QUOTE;
	static int CHAR_DOUBLEQUOTE;
	static int CHAR_COLON;
	static int CHAR_SEMICOLON;
	static int CHAR_FRONTSLASH;
	static int CHAR_BACKSLASH;
	static int CHAR_ASTERISK;
	static int CHAR_PLUS;
	static int CHAR_MINUS;
	static int CHAR_EQUALS;
	static int CHAR_UNDERSCORE;
	static int CHAR_CARET;
	static int CHAR_BACKQUOTE;
	static int CHAR_TILDE;
	static int CHAR_OPENPARENTHESIS;
	static int CHAR_CLOSEPARENTHESIS;
	static int CHAR_OPENANGLEBRACKET;
	static int CHAR_CLOSEANGLEBRACKET;
	static int CHAR_OPENCURLYBRACKET;
	static int CHAR_CLOSECURLYBRACKET;
	static int CHAR_OPENSQUAREBRACKET;
	static int CHAR_CLOSESQUAREBRACKET;
	static int CHAR_PIPE;
	static int CHAR_AT;
	static int CHAR_POUND;
	static int CHAR_DOLLAR;
	static int CHAR_PERCENT;
	static int CHAR_AMPERSAND;
	static int CHAR_BLOCK;
	static int CHAR_SPACE;

	//spanish
	static int CHAR_dN;
	static int CHAR_aa;
	static int CHAR_ae;
	static int CHAR_ai;
	static int CHAR_ao;
	static int CHAR_au;
	static int CHAR_dn;
	static int CHAR_iE;
	static int CHAR_iQ;
	static int CHAR_aE;
	static int CHAR_aI;
	static int CHAR_aA;

	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�


	//french
	static int CHAR_RR;
	static int CHAR_LL;
	static int CHAR_ca;
	static int CHAR_ce;
	static int CHAR_ci;
	static int CHAR_co;
	static int CHAR_cu;
	static int CHAR_ga;
	static int CHAR_ge;
	static int CHAR_de;
	static int CHAR_cc;
	static int CHAR_lo;

	static int CHAR_aO;
	static int CHAR_gu;


	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�

	//�
	//�


	static int CHAR_dI;
	static int CHAR_dA;
	static int CHAR_dO;
	static int CHAR_dU;
	static int CHAR_da;
	static int CHAR_do;
	static int CHAR_du;
	static int CHAR_dB;

	//�
	//�
	//�
	//�
	//�
	//�
	//�
	//�
};

