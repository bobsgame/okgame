//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "Logger.h"


int HARDWARE_RGB(int r, int g, int b);
void HARDWARE_create_brightened_palette(int* pal, int* newpal, int bright);


void adjust_color(int* pr, int* pg, int* pb);



class OKColor
{
	//various color utilities lifted from other libraries

public:

	//this is only because boost serialize was referencing other colors with exact data and it was breaking deserialization
	//string uuid = "";


	string name = "";
	u8 r = 0;
	u8 g = 0;
	u8 b = 0;
	u8 a = 0;

	template <typename Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
//		if (version > 0)
//		{
//			ar & BOOST_SERIALIZATION_NVP(uuid);
//		}
			ar & BOOST_SERIALIZATION_NVP(name);
			ar & BOOST_SERIALIZATION_NVP(r);
			ar & BOOST_SERIALIZATION_NVP(g);
			ar & BOOST_SERIALIZATION_NVP(b);
			ar & BOOST_SERIALIZATION_NVP(a);
	}

	

public:

	bool operator==(const OKColor& rhs) const
	{
		return
			r == rhs.r
			&& g == rhs.g
			&& b == rhs.b
			&& a == rhs.a
			&& name == rhs.name
			;
	}
	bool operator!=(const OKColor& rhs) const
	{
		return
			(*this == rhs) == false
			;
	}

//	OKColor& OKColor::operator=(const OKColor rhs)
//	{
//		//don't copy uuid
//
//		this->name = rhs.name;
//		this->r = rhs.r;
//		this->g = rhs.g;
//		this->b = rhs.b;
//		this->a = rhs.a;
//		
//		return *this;
//	}

	static sp<OKColor> getColorByName(string name);
	static Logger log;

	static ArrayList<sp<OKColor>> colors;

	static sp<OKColor> clear;
	static sp<OKColor> transparent;
	static sp<OKColor> black;

	static sp<OKColor> darkerGray;
	static sp<OKColor> darkGray;
	static sp<OKColor> gray;
	static sp<OKColor> lightGray;
	static sp<OKColor> lighterGray;

	static sp<OKColor> white;

	static sp<OKColor> cyan; //, lightCyan, darkCyan);
	static sp<OKColor> lightCyan; //ms<Color>(150,255,255);
	static sp<OKColor> lighterCyan; //ms<Color>(150,255,255);
	static sp<OKColor> darkCyan; //ms<Color>(0,220,220);
	static sp<OKColor> darkerCyan; //ms<Color>(0,180,180);
	static sp<OKColor> magenta; //, lightMagenta, darkMagenta);
	static sp<OKColor> lightMagenta; //ms<Color>(255,120,127);
	static sp<OKColor> lighterMagenta; //ms<Color>(255,120,127);
	static sp<OKColor> darkMagenta; //ms<Color>(150,0,75);
	static sp<OKColor> darkerMagenta; //ms<Color>(127,0,64);
	static sp<OKColor> yellow; //, lightYellow, darkYellow);
	static sp<OKColor> lightYellow; //ms<Color>(255,255,127);
	static sp<OKColor> lighterYellow; //ms<Color>(255,255,127);
	static sp<OKColor> darkYellow; //ms<Color>(200,200,0);
	static sp<OKColor> darkerYellow; //ms<Color>(127,127,0);
	static sp<OKColor> orange; //, lightOrange, darkOrange);
	static sp<OKColor> lightOrange; //ms<Color>(255, 190, 110);
	static sp<OKColor> lighterOrange; //ms<Color>(255, 190, 110);
	static sp<OKColor> darkOrange; //ms<Color>(220, 115, 0);
	static sp<OKColor> darkerOrange; //ms<Color>(150, 90, 0);
	static sp<OKColor> red; //, lightRed, darkRed);
	static sp<OKColor> lightRed; //ms<Color>(255,127,127);
	static sp<OKColor> lighterRed; //ms<Color>(255,127,127);
	static sp<OKColor> darkRed; //ms<Color>(127,0,0);
	static sp<OKColor> darkerRed; //ms<Color>(64,0,0);
	static sp<OKColor> pink; //, lightPink, darkPink);
	static sp<OKColor> lightPink; //ms<Color>(255, 127, 255);
	static sp<OKColor> lighterPink; //ms<Color>(255, 127, 255);
	static sp<OKColor> darkPink; //ms<Color>(127, 0, 127);
	static sp<OKColor> darkerPink; //ms<Color>(64, 0, 64);
	static sp<OKColor> purple; //, lightPurple, darkPurple);
	static sp<OKColor> darkPurple; //ms<Color>(63,0,127);
	static sp<OKColor> darkerPurple; //ms<Color>(63,0,127);
	static sp<OKColor> lightPurple; //ms<Color>(159,63,255);
	static sp<OKColor> lighterPurple; //ms<Color>(159,63,255);
	static sp<OKColor> blue; //, lightBlue, darkBlue);
	static sp<OKColor> lightBlue; //ms<Color>(150,150,255);
	static sp<OKColor> lighterBlue; //ms<Color>(150,150,255);
	static sp<OKColor> darkBlue; //ms<Color>(0,0,150);
	static sp<OKColor> darkerBlue; //ms<Color>(0,0,64);
	static sp<OKColor> green;
	static sp<OKColor> lighterGreen;
	static sp<OKColor> lightGreen;
	static sp<OKColor> darkGreen;
	static sp<OKColor> darkerGreen;
	static sp<OKColor> aqua;
	static sp<OKColor> lighterAqua;
	static sp<OKColor> lightAqua;
	static sp<OKColor> darkAqua;
	static sp<OKColor> darkerAqua;
	static sp<OKColor> turquoise;
	static sp<OKColor> lighterTurquoise;
	static sp<OKColor> lightTurquoise;
	static sp<OKColor> darkTurquoise;
	static sp<OKColor> darkerTurquoise;
	static sp<OKColor> olive;
	static sp<OKColor> lighterOlive;
	static sp<OKColor> lightOlive;
	static sp<OKColor> darkOlive;
	static sp<OKColor> darkerOlive;
	static sp<OKColor> burgandy;
	static sp<OKColor> lighterBurgandy;
	static sp<OKColor> lightBurgandy;
	static sp<OKColor> darkBurgandy;
	static sp<OKColor> darkerBurgandy;
	static sp<OKColor> wine;


	static void initPresetColors();
	static bool colorsInitialized;// = false;

	OKColor();
	//OKColor(sp<OKColor> c);
	//OKColor(const OKColor &c);
	OKColor(OKColor c, u8 a);
	//OKColor(OKColor c, float af);
	//OKColor(OKColor c, float af);
	//OKColor(float rf, float gf, float bf);
	//OKColor(float rf, float gf, float bf, float af);
	OKColor(u8 r, u8 g, u8 b);
	OKColor(u8 r, u8 g, u8 b, u8 a);
	OKColor(float hf, float sf, float bf, float af, bool hsbOverload);
	OKColor(int rgb);
	float rf();
	float gf();
	float bf();
	float af();
	u8 ri();
	u8 gi();
	u8 bi();
	u8 ai();
	static float* RGBtoHSB(u8 r, u8 g, u8 b);
	static int HSBtoRGB(float hue, float saturation, float brightness);
	void darker();
	void darker(float scale);
	void lighter();
	void lighter(float scale);

	// void *multiply(sp<Color>c);
	//sp<Color>addToCopy(sp<Color>c);
	//sp<Color>scaleCopy(float value);


	//static int rgbatoABGRInt(u8 r, u8 g, u8 b, u8 a);
	//static int HexToDec(const string &hexst);
	static int DecToRed(int dec);
	static int DecToGreen(int dec);
	static int DecToBlue(int dec);
	int getRGBA();
	static int getRGBA(u8 r, u8 g, u8 b, u8 a);
};

BOOST_CLASS_VERSION(OKColor, 1)
BOOST_CLASS_TRACKING(OKColor, boost::serialization::track_never)