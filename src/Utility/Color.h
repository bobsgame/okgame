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

	static shared_ptr<OKColor> getColorByName(string name);
	static Logger log;

	static ArrayList<shared_ptr<OKColor>> colors;

	static shared_ptr<OKColor> clear;
	static shared_ptr<OKColor> transparent;
	static shared_ptr<OKColor> black;

	static shared_ptr<OKColor> darkerGray;
	static shared_ptr<OKColor> darkGray;
	static shared_ptr<OKColor> gray;
	static shared_ptr<OKColor> lightGray;
	static shared_ptr<OKColor> lighterGray;

	static shared_ptr<OKColor> white;

	static shared_ptr<OKColor> cyan; //, lightCyan, darkCyan);
	static shared_ptr<OKColor> lightCyan; //make_shared<Color>(150,255,255);
	static shared_ptr<OKColor> lighterCyan; //make_shared<Color>(150,255,255);
	static shared_ptr<OKColor> darkCyan; //make_shared<Color>(0,220,220);
	static shared_ptr<OKColor> darkerCyan; //make_shared<Color>(0,180,180);
	static shared_ptr<OKColor> magenta; //, lightMagenta, darkMagenta);
	static shared_ptr<OKColor> lightMagenta; //make_shared<Color>(255,120,127);
	static shared_ptr<OKColor> lighterMagenta; //make_shared<Color>(255,120,127);
	static shared_ptr<OKColor> darkMagenta; //make_shared<Color>(150,0,75);
	static shared_ptr<OKColor> darkerMagenta; //make_shared<Color>(127,0,64);
	static shared_ptr<OKColor> yellow; //, lightYellow, darkYellow);
	static shared_ptr<OKColor> lightYellow; //make_shared<Color>(255,255,127);
	static shared_ptr<OKColor> lighterYellow; //make_shared<Color>(255,255,127);
	static shared_ptr<OKColor> darkYellow; //make_shared<Color>(200,200,0);
	static shared_ptr<OKColor> darkerYellow; //make_shared<Color>(127,127,0);
	static shared_ptr<OKColor> orange; //, lightOrange, darkOrange);
	static shared_ptr<OKColor> lightOrange; //make_shared<Color>(255, 190, 110);
	static shared_ptr<OKColor> lighterOrange; //make_shared<Color>(255, 190, 110);
	static shared_ptr<OKColor> darkOrange; //make_shared<Color>(220, 115, 0);
	static shared_ptr<OKColor> darkerOrange; //make_shared<Color>(150, 90, 0);
	static shared_ptr<OKColor> red; //, lightRed, darkRed);
	static shared_ptr<OKColor> lightRed; //make_shared<Color>(255,127,127);
	static shared_ptr<OKColor> lighterRed; //make_shared<Color>(255,127,127);
	static shared_ptr<OKColor> darkRed; //make_shared<Color>(127,0,0);
	static shared_ptr<OKColor> darkerRed; //make_shared<Color>(64,0,0);
	static shared_ptr<OKColor> pink; //, lightPink, darkPink);
	static shared_ptr<OKColor> lightPink; //make_shared<Color>(255, 127, 255);
	static shared_ptr<OKColor> lighterPink; //make_shared<Color>(255, 127, 255);
	static shared_ptr<OKColor> darkPink; //make_shared<Color>(127, 0, 127);
	static shared_ptr<OKColor> darkerPink; //make_shared<Color>(64, 0, 64);
	static shared_ptr<OKColor> purple; //, lightPurple, darkPurple);
	static shared_ptr<OKColor> darkPurple; //make_shared<Color>(63,0,127);
	static shared_ptr<OKColor> darkerPurple; //make_shared<Color>(63,0,127);
	static shared_ptr<OKColor> lightPurple; //make_shared<Color>(159,63,255);
	static shared_ptr<OKColor> lighterPurple; //make_shared<Color>(159,63,255);
	static shared_ptr<OKColor> blue; //, lightBlue, darkBlue);
	static shared_ptr<OKColor> lightBlue; //make_shared<Color>(150,150,255);
	static shared_ptr<OKColor> lighterBlue; //make_shared<Color>(150,150,255);
	static shared_ptr<OKColor> darkBlue; //make_shared<Color>(0,0,150);
	static shared_ptr<OKColor> darkerBlue; //make_shared<Color>(0,0,64);
	static shared_ptr<OKColor> green;
	static shared_ptr<OKColor> lighterGreen;
	static shared_ptr<OKColor> lightGreen;
	static shared_ptr<OKColor> darkGreen;
	static shared_ptr<OKColor> darkerGreen;
	static shared_ptr<OKColor> aqua;
	static shared_ptr<OKColor> lighterAqua;
	static shared_ptr<OKColor> lightAqua;
	static shared_ptr<OKColor> darkAqua;
	static shared_ptr<OKColor> darkerAqua;
	static shared_ptr<OKColor> turquoise;
	static shared_ptr<OKColor> lighterTurquoise;
	static shared_ptr<OKColor> lightTurquoise;
	static shared_ptr<OKColor> darkTurquoise;
	static shared_ptr<OKColor> darkerTurquoise;
	static shared_ptr<OKColor> olive;
	static shared_ptr<OKColor> lighterOlive;
	static shared_ptr<OKColor> lightOlive;
	static shared_ptr<OKColor> darkOlive;
	static shared_ptr<OKColor> darkerOlive;
	static shared_ptr<OKColor> burgandy;
	static shared_ptr<OKColor> lighterBurgandy;
	static shared_ptr<OKColor> lightBurgandy;
	static shared_ptr<OKColor> darkBurgandy;
	static shared_ptr<OKColor> darkerBurgandy;
	static shared_ptr<OKColor> wine;


	static void initPresetColors();
	static bool colorsInitialized;// = false;

	OKColor();
	//OKColor(shared_ptr<OKColor> c);
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

	// void *multiply(shared_ptr<Color>c);
	//shared_ptr<Color>addToCopy(shared_ptr<Color>c);
	//shared_ptr<Color>scaleCopy(float value);


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