//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "Logger.h"


int HARDWARE_RGB(int r, int g, int b);
void HARDWARE_create_brightened_palette(int* pal, int* newpal, int bright);


void adjust_color(int* pr, int* pg, int* pb);



class BobColor
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

	bool operator==(const BobColor& rhs) const
	{
		return
			r == rhs.r
			&& g == rhs.g
			&& b == rhs.b
			&& a == rhs.a
			&& name == rhs.name
			;
	}
	bool operator!=(const BobColor& rhs) const
	{
		return
			(*this == rhs) == false
			;
	}

//	BobColor& BobColor::operator=(const BobColor rhs)
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

	static shared_ptr<BobColor> getColorByName(string name);
	static Logger log;

	static ArrayList<shared_ptr<BobColor>> colors;

	static shared_ptr<BobColor> clear;
	static shared_ptr<BobColor> transparent;
	static shared_ptr<BobColor> black;

	static shared_ptr<BobColor> darkerGray;
	static shared_ptr<BobColor> darkGray;
	static shared_ptr<BobColor> gray;
	static shared_ptr<BobColor> lightGray;
	static shared_ptr<BobColor> lighterGray;

	static shared_ptr<BobColor> white;

	static shared_ptr<BobColor> cyan; //, lightCyan, darkCyan);
	static shared_ptr<BobColor> lightCyan; //make_shared<Color>(150,255,255);
	static shared_ptr<BobColor> lighterCyan; //make_shared<Color>(150,255,255);
	static shared_ptr<BobColor> darkCyan; //make_shared<Color>(0,220,220);
	static shared_ptr<BobColor> darkerCyan; //make_shared<Color>(0,180,180);
	static shared_ptr<BobColor> magenta; //, lightMagenta, darkMagenta);
	static shared_ptr<BobColor> lightMagenta; //make_shared<Color>(255,120,127);
	static shared_ptr<BobColor> lighterMagenta; //make_shared<Color>(255,120,127);
	static shared_ptr<BobColor> darkMagenta; //make_shared<Color>(150,0,75);
	static shared_ptr<BobColor> darkerMagenta; //make_shared<Color>(127,0,64);
	static shared_ptr<BobColor> yellow; //, lightYellow, darkYellow);
	static shared_ptr<BobColor> lightYellow; //make_shared<Color>(255,255,127);
	static shared_ptr<BobColor> lighterYellow; //make_shared<Color>(255,255,127);
	static shared_ptr<BobColor> darkYellow; //make_shared<Color>(200,200,0);
	static shared_ptr<BobColor> darkerYellow; //make_shared<Color>(127,127,0);
	static shared_ptr<BobColor> orange; //, lightOrange, darkOrange);
	static shared_ptr<BobColor> lightOrange; //make_shared<Color>(255, 190, 110);
	static shared_ptr<BobColor> lighterOrange; //make_shared<Color>(255, 190, 110);
	static shared_ptr<BobColor> darkOrange; //make_shared<Color>(220, 115, 0);
	static shared_ptr<BobColor> darkerOrange; //make_shared<Color>(150, 90, 0);
	static shared_ptr<BobColor> red; //, lightRed, darkRed);
	static shared_ptr<BobColor> lightRed; //make_shared<Color>(255,127,127);
	static shared_ptr<BobColor> lighterRed; //make_shared<Color>(255,127,127);
	static shared_ptr<BobColor> darkRed; //make_shared<Color>(127,0,0);
	static shared_ptr<BobColor> darkerRed; //make_shared<Color>(64,0,0);
	static shared_ptr<BobColor> pink; //, lightPink, darkPink);
	static shared_ptr<BobColor> lightPink; //make_shared<Color>(255, 127, 255);
	static shared_ptr<BobColor> lighterPink; //make_shared<Color>(255, 127, 255);
	static shared_ptr<BobColor> darkPink; //make_shared<Color>(127, 0, 127);
	static shared_ptr<BobColor> darkerPink; //make_shared<Color>(64, 0, 64);
	static shared_ptr<BobColor> purple; //, lightPurple, darkPurple);
	static shared_ptr<BobColor> darkPurple; //make_shared<Color>(63,0,127);
	static shared_ptr<BobColor> darkerPurple; //make_shared<Color>(63,0,127);
	static shared_ptr<BobColor> lightPurple; //make_shared<Color>(159,63,255);
	static shared_ptr<BobColor> lighterPurple; //make_shared<Color>(159,63,255);
	static shared_ptr<BobColor> blue; //, lightBlue, darkBlue);
	static shared_ptr<BobColor> lightBlue; //make_shared<Color>(150,150,255);
	static shared_ptr<BobColor> lighterBlue; //make_shared<Color>(150,150,255);
	static shared_ptr<BobColor> darkBlue; //make_shared<Color>(0,0,150);
	static shared_ptr<BobColor> darkerBlue; //make_shared<Color>(0,0,64);
	static shared_ptr<BobColor> green;
	static shared_ptr<BobColor> lighterGreen;
	static shared_ptr<BobColor> lightGreen;
	static shared_ptr<BobColor> darkGreen;
	static shared_ptr<BobColor> darkerGreen;
	static shared_ptr<BobColor> aqua;
	static shared_ptr<BobColor> lighterAqua;
	static shared_ptr<BobColor> lightAqua;
	static shared_ptr<BobColor> darkAqua;
	static shared_ptr<BobColor> darkerAqua;
	static shared_ptr<BobColor> turquoise;
	static shared_ptr<BobColor> lighterTurquoise;
	static shared_ptr<BobColor> lightTurquoise;
	static shared_ptr<BobColor> darkTurquoise;
	static shared_ptr<BobColor> darkerTurquoise;
	static shared_ptr<BobColor> olive;
	static shared_ptr<BobColor> lighterOlive;
	static shared_ptr<BobColor> lightOlive;
	static shared_ptr<BobColor> darkOlive;
	static shared_ptr<BobColor> darkerOlive;
	static shared_ptr<BobColor> burgandy;
	static shared_ptr<BobColor> lighterBurgandy;
	static shared_ptr<BobColor> lightBurgandy;
	static shared_ptr<BobColor> darkBurgandy;
	static shared_ptr<BobColor> darkerBurgandy;
	static shared_ptr<BobColor> wine;


	static void initPresetColors();
	static bool colorsInitialized;// = false;

	BobColor();
	//BobColor(shared_ptr<BobColor> c);
	//BobColor(const BobColor &c);
	BobColor(BobColor c, u8 a);
	//BobColor(BobColor c, float af);
	//BobColor(BobColor c, float af);
	//BobColor(float rf, float gf, float bf);
	//BobColor(float rf, float gf, float bf, float af);
	BobColor(u8 r, u8 g, u8 b);
	BobColor(u8 r, u8 g, u8 b, u8 a);
	BobColor(float hf, float sf, float bf, float af, bool hsbOverload);
	BobColor(int rgb);
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

	// void *multiply(shared_ptr<Color >c);
	//shared_ptr<Color >addToCopy(shared_ptr<Color >c);
	//shared_ptr<Color >scaleCopy(float value);


	//static int rgbatoABGRInt(u8 r, u8 g, u8 b, u8 a);
	//static int HexToDec(const string &hexst);
	static int DecToRed(int dec);
	static int DecToGreen(int dec);
	static int DecToBlue(int dec);
	int getRGBA();
	static int getRGBA(u8 r, u8 g, u8 b, u8 a);
};

BOOST_CLASS_VERSION(BobColor, 1)
BOOST_CLASS_TRACKING(BobColor, boost::serialization::track_never)