#include "stdafx.h"

//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


//#pragma once



Logger OKColor::log = Logger("Color");
bool OKColor::colorsInitialized = false;


sp<vector<sp<OKColor>>> OKColor::colors;

sp<OKColor> OKColor::clear = ms<OKColor>(0, 0, 0, 0);
sp<OKColor> OKColor::transparent = clear;
sp<OKColor> OKColor::black = ms<OKColor>(0, 0, 0);
sp<OKColor> OKColor::darkerGray = ms<OKColor>(0.2f * 255, 0.2f * 255, 0.2f * 255);
sp<OKColor> OKColor::darkGray = ms<OKColor>(0.35f * 255, 0.35f * 255, 0.35f * 255);
sp<OKColor> OKColor::gray = ms<OKColor>(0.5f * 255, 0.5f * 255, 0.5f * 255);
sp<OKColor> OKColor::lightGray = ms<OKColor>(0.65f * 255, 0.65f * 255, 0.65f * 255);
sp<OKColor> OKColor::lighterGray = ms<OKColor>(0.8f * 255, 0.8f * 255, 0.8f * 255);
sp<OKColor> OKColor::white = ms<OKColor>(1.0f*255, 1.0f * 255, 1.0f * 255);

sp<OKColor> OKColor::cyan = ms<OKColor>(0, 255, 255);
sp<OKColor> OKColor::lightCyan = ms<OKColor>(0, 255, 255); //cyan->lighter();
sp<OKColor> OKColor::lighterCyan = ms<OKColor>(0, 255, 255); //cyan->lighter();
sp<OKColor> OKColor::darkCyan = ms<OKColor>(0, 255, 255); //cyan->darker();
sp<OKColor> OKColor::darkerCyan = ms<OKColor>(0, 255, 255); //cyan->darker()->darker();

sp<OKColor> OKColor::magenta = ms<OKColor>(255, 0, 127);
sp<OKColor> OKColor::lightMagenta = ms<OKColor>(255, 0, 127); //magenta->lighter();
sp<OKColor> OKColor::lighterMagenta = ms<OKColor>(255, 0, 127); //magenta->lighter();
sp<OKColor> OKColor::darkMagenta = ms<OKColor>(255, 0, 127); //magenta->darker();
sp<OKColor> OKColor::darkerMagenta = ms<OKColor>(255, 0, 127); //magenta->darker()->darker();

sp<OKColor> OKColor::yellow = ms<OKColor>(255, 255, 0);
sp<OKColor> OKColor::lightYellow = ms<OKColor>(255, 255, 0); //yellow->lighter();
sp<OKColor> OKColor::lighterYellow = ms<OKColor>(255, 255, 0); //yellow->lighter();
sp<OKColor> OKColor::darkYellow = ms<OKColor>(255, 255, 0); //yellow->darker();
sp<OKColor> OKColor::darkerYellow = ms<OKColor>(255, 255, 0); //yellow->darker()->darker();

sp<OKColor> OKColor::orange = ms<OKColor>(255, 140, 0);
sp<OKColor> OKColor::lightOrange = ms<OKColor>(255, 140, 0); //orange->lighter();
sp<OKColor> OKColor::lighterOrange = ms<OKColor>(255, 140, 0); //orange->lighter();
sp<OKColor> OKColor::darkOrange = ms<OKColor>(255, 140, 0); //orange->darker();
sp<OKColor> OKColor::darkerOrange = ms<OKColor>(255, 140, 0); //orange->darker()->darker();

sp<OKColor> OKColor::red = ms<OKColor>(255, 0, 0);
sp<OKColor> OKColor::lightRed = ms<OKColor>(255, 0, 0); //red->lighter();
sp<OKColor> OKColor::lighterRed = ms<OKColor>(255, 0, 0); //red->lighter();
sp<OKColor> OKColor::darkRed = ms<OKColor>(255, 0, 0); //red->darker();
sp<OKColor> OKColor::darkerRed = ms<OKColor>(255, 0, 0); //red->darker()->darker();

sp<OKColor> OKColor::pink = ms<OKColor>(255, 0, 255);
sp<OKColor> OKColor::lightPink = ms<OKColor>(255, 0, 255); //pink->lighter();
sp<OKColor> OKColor::lighterPink = ms<OKColor>(255, 0, 255); //pink->lighter();
sp<OKColor> OKColor::darkPink = ms<OKColor>(255, 0, 255); //pink->darker();
sp<OKColor> OKColor::darkerPink = ms<OKColor>(255, 0, 255); //pink->darker()->darker();

sp<OKColor> OKColor::purple = ms<OKColor>(127, 0, 255);
sp<OKColor> OKColor::lightPurple = ms<OKColor>(127, 0, 255); //purple->lighter();
sp<OKColor> OKColor::lighterPurple = ms<OKColor>(127, 0, 255); //purple->lighter();
sp<OKColor> OKColor::darkPurple = ms<OKColor>(127, 0, 255); //purple->darker();
sp<OKColor> OKColor::darkerPurple = ms<OKColor>(127, 0, 255); //purple->darker()->darker();


sp<OKColor> OKColor::blue = ms<OKColor>(0, 0, 255);
sp<OKColor> OKColor::lighterBlue = ms<OKColor>(0, 0, 255); //blue->lighter();
sp<OKColor> OKColor::lightBlue = ms<OKColor>(0, 0, 255); //blue->lighter();
sp<OKColor> OKColor::darkBlue = ms<OKColor>(0, 0, 255); //blue->darker();
sp<OKColor> OKColor::darkerBlue = ms<OKColor>(0, 0, 255); //blue->darker()->darker();

sp<OKColor> OKColor::green = ms<OKColor>(0, 255, 0);
sp<OKColor> OKColor::lighterGreen = ms<OKColor>(0, 255, 0); //green->lighter()->lighter();
sp<OKColor> OKColor::lightGreen = ms<OKColor>(0, 255, 0); //green->lighter();
sp<OKColor> OKColor::darkGreen = ms<OKColor>(0, 255, 0); //green->darker();
sp<OKColor> OKColor::darkerGreen = ms<OKColor>(0, 255, 0); //green->darker()->darker();

sp<OKColor> OKColor::aqua = ms<OKColor>(0, 150, 255);
sp<OKColor> OKColor::lighterAqua = ms<OKColor>(0, 150, 255); //aqua->lighter()->lighter();
sp<OKColor> OKColor::lightAqua = ms<OKColor>(0, 150, 255); //aqua->lighter();
sp<OKColor> OKColor::darkAqua = ms<OKColor>(0, 150, 255); //aqua->darker();
sp<OKColor> OKColor::darkerAqua = ms<OKColor>(0, 150, 255); //aqua->darker()->darker();

sp<OKColor> OKColor::turquoise = ms<OKColor>(0, 255, 150);
sp<OKColor> OKColor::lighterTurquoise = ms<OKColor>(0, 255, 150); //turquoise->lighter()->lighter();
sp<OKColor> OKColor::lightTurquoise = ms<OKColor>(0, 255, 150); //turquoise->lighter();
sp<OKColor> OKColor::darkTurquoise = ms<OKColor>(0, 255, 150); //turquoise->darker();
sp<OKColor> OKColor::darkerTurquoise = ms<OKColor>(0, 255, 150); //turquoise->darker()->darker();

sp<OKColor> OKColor::olive = ms<OKColor>(64, 72, 0);
sp<OKColor> OKColor::darkerOlive = ms<OKColor>(64, 72, 0);
sp<OKColor> OKColor::darkOlive = ms<OKColor>(64, 72, 0);
sp<OKColor> OKColor::lighterOlive = ms<OKColor>(64, 72, 0);
sp<OKColor> OKColor::lightOlive = ms<OKColor>(64, 72, 0);

sp<OKColor> OKColor::burgandy = ms<OKColor>(220, 70, 0);
sp<OKColor> OKColor::darkerBurgandy = ms<OKColor>(220, 70, 0);
sp<OKColor> OKColor::darkBurgandy = ms<OKColor>(220, 70, 0);
sp<OKColor> OKColor::lighterBurgandy = ms<OKColor>(220, 70, 0);
sp<OKColor> OKColor::lightBurgandy = ms<OKColor>(220, 70, 0);


sp<OKColor> OKColor::wine = ms<OKColor>(200, 80, 0);



//==========================================================================================================================
int HARDWARE_RGB(int r, int g, int b)
{//==========================================================================================================================
	return ((1 << 15) + (r) + ((g) << 5) + ((b) << 10));
}


//==========================================================================================================================
void RGBToHSL(float r, float g, float b, float* h, float* s, float* l)
{//==========================================================================================================================


	//float fmin = min(min(r, g), b);    //Min. value of RGB
	//float fmax = max(max(r, g), b);    //Max. value of RGB
	float fmin = r;
	if (g < fmin)fmin = g;
	if (b < fmin)fmin = b;

	float fmax = r;
	if (g > fmax)fmax = g;
	if (b > fmax)fmax = b;

	float delta = fmax - fmin; //Delta RGB value

	*l = (fmax + fmin) / 2.0f; // Luminance

	if (delta == 0.0f) //This is a gray, no chroma...
	{
		*h = 0.0f; // Hue
		*s = 0.0f; // Saturation
	}
	else //Chromatic data...
	{
		if (*l < 0.5f)
			*s = delta / (fmax + fmin); // Saturation
		else
			*s = delta / (2.0f - fmax - fmin); // Saturation

		float deltaR = (((fmax - r) / 6.0f) + (delta / 2.0f)) / delta;
		float deltaG = (((fmax - g) / 6.0f) + (delta / 2.0f)) / delta;
		float deltaB = (((fmax - b) / 6.0f) + (delta / 2.0f)) / delta;

		if (r == fmax)
			*h = deltaB - deltaG; // Hue
		else if (g == fmax)
			*h = (1.0f / 3.0f) + deltaR - deltaB; // Hue
		else if (b == fmax)
			*h = (2.0f / 3.0f) + deltaG - deltaR; // Hue

		if (*h < 0.0f)
			*h += 1.0f; // Hue
		else if (*h > 1.0f)
			*h -= 1.0f; // Hue
	}
}

//==========================================================================================================================
float HueToRGB(float f1, float f2, float hue)
{//==========================================================================================================================
	if (hue < 0.0f)
		hue += 1.0f;
	else if (hue > 1.0f)
		hue -= 1.0f;
	float res;
	if ((6.0f * hue) < 1.0f)
		res = f1 + (f2 - f1) * 6.0f * hue;
	else if ((2.0f * hue) < 1.0f)
		res = f2;
	else if ((3.0f * hue) < 2.0f)
		res = f1 + (f2 - f1) * ((2.0f / 3.0f) - hue) * 6.0f;
	else
		res = f1;
	return res;
}

//==========================================================================================================================
void HSLToRGB(float h, float s, float l, float* r, float* g, float* b)
{//==========================================================================================================================


	if (s == 0.0f)
	{
		*r = l;
		*g = l;
		*b = l;
	}
	else
	{
		float f2;

		if (l < 0.5f)
			f2 = l * (1.0f + s);
		else
			f2 = (l + s) - (s * l);

		float f1 = 2.0f * l - f2;

		*r = HueToRGB(f1, f2, h + (1.0f / 3.0f));
		*g = HueToRGB(f1, f2, h);
		*b = HueToRGB(f1, f2, h - (1.0f / 3.0f));
	}
}

//float adjust_gamma = 1.0f;
//float adjust_brightness = 1.0f;
//float adjust_lightness = 1.0f;

//==========================================================================================================================
void adjust_color(int* pr, int* pg, int* pb)
{//==========================================================================================================================

	int r, g, b;
	r = *pr;
	g = *pg;
	b = *pb;

	//if its not black
	if (r != b || r != g || (r == b && r == g && r > 16))
	{
		float fr, fg, fb, fh, fs, fl;
		fr = (float)((float)r / 256.0f);
		fg = (float)((float)g / 256.0f);
		fb = (float)((float)b / 256.0f);


		//gamma
		//fr = pow(fr,0.8f);
		//fg = pow(fg,0.8f);
		//fb = pow(fb,0.8f);

		//increase blue hue unless color is gray
		if (r != b || r != g)
			fb = fb + (5.0f / 256.0f);

		//increase lightness
		RGBToHSL(fr, fg, fb, &fh, &fs, &fl);
		fl += (10.0f / 256.0f);
		fs += (5.0f / 256.0f);
		if (fl > 1.0f)fl = 1.0f;
		if (fs > 1.0f)fs = 1.0f;
		HSLToRGB(fh, fs, fl, &fr, &fg, &fb);

		//brighten
		//fr*=1.1f;
		//fg*=1.1f;
		//fb*=1.1f;


		r = (int)(fr * 256.0f);
		g = (int)(fg * 256.0f);
		b = (int)(fb * 256.0f);

		if (r > 255)r = 255;
		if (g > 255)g = 255;
		if (b > 255)b = 255;
	}

	*pr = r;
	*pb = b;
	*pg = g;

	/*
	vec3 hslcolor = RGBToHSL(color);
	//hslcolor.x+=(3.0f/255.0f);
	hslcolor.z+=(5.0f/255.0f);
	color = HSLToRGB(hslcolor);


	color = ContrastSaturationBrightness(color,1.0,1.0,1.1);

	*/
}


//==========================================================================================================================
void HARDWARE_create_brightened_palette(int* pal, int* newpal, int bright)//HARDWARE_CreatePalBright
{//==========================================================================================================================

	int x = 0;
	for (x = 0; x < 256; x++)
	{
		//bgr->rgb->hsl->lighten->rgb->bgr
		/*

		int bgr=pal[x];

		//bgr to r g b

		int r=((((bgr%32))*8));
		int g=((((bgr/32)%32))*8);
		int b=(((bgr/1024))*8);


		//r g b to h s l

		float hue, saturation, brightness;

		int cmax = (r > g) ? r : g;
		if (b > cmax) cmax = b;
		int cmin = (r < g) ? r : g;
		if (b < cmin) cmin = b;

		brightness = ((float) cmax) / 255.0f;
		if (cmax != 0)
		saturation = ((float) (cmax - cmin)) / ((float) cmax);
		else
		saturation = 0;
		if (saturation == 0)
		hue = 0;
		else {
		float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
		float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
		float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
		if (r == cmax)
		hue = bluec - greenc;
		else if (g == cmax)
		hue = 2.0f + redc - bluec;
		else
		hue = 4.0f + greenc - redc;
		hue = hue / 6.0f;
		if (hue < 0)
		hue = hue + 1.0f;
		}


		//h s l lighten

		brightness=brightness*((((float)bright)+31.0f)/31.0f);
		if(brightness<0.0f)brightness=0.0f;
		//if(brightness>1.0f)brightness=1.0f;

		//h s l to r g b



		if (saturation == 0)
		{
		r = g = b = (int) (brightness * 255.0f + 0.5f);
		}
		else
		{
		float h = (hue - (float)floor(hue)) * 6.0f;
		float f = h - (float)floor(h);
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int) h)
		{
		case 0:
		r = (int) (brightness * 255.0f + 0.5f);
		g = (int) (t * 255.0f + 0.5f);
		b = (int) (p * 255.0f + 0.5f);
		break;
		case 1:
		r = (int) (q * 255.0f + 0.5f);
		g = (int) (brightness * 255.0f + 0.5f);
		b = (int) (p * 255.0f + 0.5f);
		break;
		case 2:
		r = (int) (p * 255.0f + 0.5f);
		g = (int) (brightness * 255.0f + 0.5f);
		b = (int) (t * 255.0f + 0.5f);
		break;
		case 3:
		r = (int) (p * 255.0f + 0.5f);
		g = (int) (q * 255.0f + 0.5f);
		b = (int) (brightness * 255.0f + 0.5f);
		break;
		case 4:
		r = (int) (t * 255.0f + 0.5f);
		g = (int) (p * 255.0f + 0.5f);
		b = (int) (brightness * 255.0f + 0.5f);
		break;
		case 5:
		r = (int) (brightness * 255.0f + 0.5f);
		g = (int) (p * 255.0f + 0.5f);
		b = (int) (q * 255.0f + 0.5f);
		break;
		}
		}

		//r g b to bgr
		if(r>255)r=255;
		if(g>255)g=255;
		if(b>255)b=255;

		int newbgr =((b/8)*1024)+((g/8)*32)+((r/8));
		*/

		//plain old rgb lightening

		int r, g, b;

		r = pal[x] & 31;
		r += bright;
		if (r < 0) r = 0;
		if (r > 31) r = 31;
		g = (pal[x] >> 5) & 31;
		g += bright;
		if (g < 0) g = 0;
		if (g > 31) g = 31;
		b = (pal[x] >> 10) & 31;
		b += bright;
		if (b < 0) b = 0;
		if (b > 31) b = 31;
		newpal[x] = HARDWARE_RGB(r, g, b);
	}
}


//=========================================================================================================================
void OKColor::initPresetColors()
{//=========================================================================================================================
	if (colorsInitialized)return;

	colorsInitialized = true;
	OKColor c;

	lightCyan->lighter();
	lighterCyan->lighter();
	lighterCyan->lighter();
	darkCyan->darker();
	darkerCyan->darker();
	darkerCyan->darker();


	lightMagenta->lighter();
	lighterMagenta->lighter();
	lighterMagenta->lighter();
	darkMagenta->darker();
	darkerMagenta->darker();
	darkerMagenta->darker();


	lightYellow->lighter();
	lighterYellow->lighter();
	lighterYellow->lighter();
	darkYellow->darker();
	darkerYellow->darker();
	darkerYellow->darker();


	lightOrange->lighter();
	darkOrange->darker();
	darkerOrange->darker();
	darkerOrange->darker();


	lightRed->lighter();
	lighterRed->lighter();
	lighterRed->lighter();
	darkRed->darker();
	darkerRed->darker();
	darkerRed->darker();


	lightPink->lighter();
	lighterPink->lighter();
	lighterPink->lighter();
	darkPink->darker();
	darkerPink->darker();
	darkerPink->darker();


	lightPurple->lighter();
	lighterPurple->lighter();
	lighterPurple->lighter();
	darkPurple->darker();
	darkerPurple->darker();
	darkerPurple->darker();


	lightBlue->lighter();
	lighterBlue->lighter();
	lighterBlue->lighter();
	darkBlue->darker();
	darkerBlue->darker();
	darkerBlue->darker();


	lighterGreen->lighter();
	lighterGreen->lighter();
	lightGreen->lighter();
	darkGreen->darker();
	darkerGreen->darker();
	darkerGreen->darker();


	lighterAqua->lighter();
	lighterAqua->lighter();
	lightAqua->lighter();
	darkAqua->darker();
	darkerAqua->darker();
	darkerAqua->darker();


	lighterTurquoise->lighter();
	lighterTurquoise->lighter();
	lightTurquoise->lighter();
	darkTurquoise->darker();
	darkerTurquoise->darker();
	darkerTurquoise->darker();

	lighterOlive->lighter();
	lighterOlive->lighter();
	lightOlive->lighter();
	darkOlive->darker();
	darkerOlive->darker();
	darkerOlive->darker();

	lighterBurgandy->lighter();
	lighterBurgandy->lighter();
	lightBurgandy->lighter();
	darkBurgandy->darker();
	darkerBurgandy->darker();
	darkerBurgandy->darker();

	clear->name="clear";
	black->name="black";
	darkerGray->name="darkerGray";
	darkGray->name="darkGray";
	gray->name="gray";
	lightGray->name="lightGray";
	lighterGray->name="lighterGray";
	white->name="white";

	cyan->name="cyan";
	lightCyan->name="lightCyan";
	lighterCyan->name="lighterCyan";
	darkCyan->name="darkCyan";
	darkerCyan->name="darkerCyan";

	magenta->name="magenta";
	lightMagenta->name="lightMagenta";
	lighterMagenta->name="lighterMagenta";
	darkMagenta->name="darkMagenta";
	darkerMagenta->name="darkerMagenta";

	yellow->name="yellow";
	lightYellow->name="lightYellow";
	lighterYellow->name="lighterYellow";
	darkYellow->name="darkYellow";
	darkerYellow->name="darkerYellow";

	orange->name="orange";
	lightOrange->name="lightOrange";
	lighterOrange->name="lighterOrange";
	darkOrange->name="darkOrange";
	darkerOrange->name="darkerOrange";

	red->name="red";
	lightRed->name="lightRed";
	lighterRed->name="lighterRed";
	darkRed->name="darkRed";
	darkerRed->name="darkerRed";

	pink->name="pink";
	lightPink->name="lightPink";
	lighterPink->name="lighterPink";
	darkPink->name="darkPink";
	darkerPink->name="darkerPink";

	purple->name="purple";
	lightPurple->name="lightPurple";
	lighterPurple->name="lighterPurple";
	darkPurple->name="darkPurple";
	darkerPurple->name="darkerPurple";


	blue->name="blue";
	lighterBlue->name="lighterBlue";
	lightBlue->name="lightBlue";
	darkBlue->name="darkBlue";
	darkerBlue->name="darkerBlue";

	green->name="green";
	lighterGreen->name="lighterGreen";
	lightGreen->name="lightGreen";
	darkGreen->name="darkGreen";
	darkerGreen->name="darkerGreen";

	aqua->name="aqua";
	lighterAqua->name="lighterAqua";
	lightAqua->name="lightAqua";
	darkAqua->name="darkAqua";
	darkerAqua->name="darkerAqua";

	turquoise->name="turquoise";
	lighterTurquoise->name="lighterTurquoise";
	lightTurquoise->name="lightTurquoise";
	darkTurquoise->name="darkTurquoise";
	darkerTurquoise->name="darkerTurquoise";

	olive->name="olive";
	lighterOlive->name = "lighterOlive";
	lightOlive->name = "lightOlive";
	darkOlive->name = "darkOlive";
	darkerOlive->name = "darkerOlive";

	burgandy->name="burgandy";
	lighterBurgandy->name = "lighterBurgandy";
	lightBurgandy->name = "lightBurgandy";
	darkBurgandy->name = "darkBurgandy";
	darkerBurgandy->name = "darkerBurgandy";

	wine->name="wine";


	colors->push_back(clear);
	colors->push_back(transparent);
	colors->push_back(black);
	colors->push_back(darkerGray);
	colors->push_back(darkGray);
	colors->push_back(gray);
	colors->push_back(lightGray);
	colors->push_back(lighterGray);
	colors->push_back(white);
	colors->push_back(cyan);
	colors->push_back(lightCyan);
	colors->push_back(lighterCyan);
	colors->push_back(darkCyan);
	colors->push_back(darkerCyan);
	colors->push_back(magenta);
	colors->push_back(lightMagenta);
	colors->push_back(lighterMagenta);
	colors->push_back(darkMagenta);
	colors->push_back(darkerMagenta);
	colors->push_back(yellow);
	colors->push_back(lightYellow);
	colors->push_back(lighterYellow);
	colors->push_back(darkYellow);
	colors->push_back(darkerYellow);
	colors->push_back(orange);
	colors->push_back(lightOrange);
	colors->push_back(lighterOrange);
	colors->push_back(darkOrange);
	colors->push_back(darkerOrange);
	colors->push_back(red);
	colors->push_back(lightRed);
	colors->push_back(lighterRed);
	colors->push_back(darkRed);
	colors->push_back(darkerRed);
	colors->push_back(pink);
	colors->push_back(lightPink);
	colors->push_back(lighterPink);
	colors->push_back(darkPink);
	colors->push_back(darkerPink);
	colors->push_back(purple);
	colors->push_back(darkPurple);
	colors->push_back(darkerPurple);
	colors->push_back(lightPurple);
	colors->push_back(lighterPurple);
	colors->push_back(blue);
	colors->push_back(lightBlue);
	colors->push_back(lighterBlue);
	colors->push_back(darkBlue);
	colors->push_back(darkerBlue);
	colors->push_back(green);
	colors->push_back(lighterGreen);
	colors->push_back(lightGreen);
	colors->push_back(darkGreen);
	colors->push_back(darkerGreen);
	colors->push_back(aqua);
	colors->push_back(lighterAqua);
	colors->push_back(lightAqua);
	colors->push_back(darkAqua);
	colors->push_back(darkerAqua);
	colors->push_back(turquoise);
	colors->push_back(lighterTurquoise);
	colors->push_back(lightTurquoise);
	colors->push_back(darkTurquoise);
	colors->push_back(darkerTurquoise);
	colors->push_back(olive);
	colors->push_back(lighterOlive);
	colors->push_back(lightOlive);
	colors->push_back(darkOlive);
	colors->push_back(darkerOlive);
	colors->push_back(burgandy);
	colors->push_back(lighterBurgandy);
	colors->push_back(lightBurgandy);
	colors->push_back(darkBurgandy);
	colors->push_back(darkerBurgandy);
	colors->push_back(wine);

}


//==========================================================================================================================
sp<OKColor> OKColor::getColorByName(string name)
{//==========================================================================================================================

	if (name == "" || name == "empty")return nullptr;
	for(int i=0;i<colors->size();i++)
	{
		sp<OKColor>c = colors->at(i);

		if (c->name == name)return c;

	}
	return nullptr;


}


//=========================================================================================================================
OKColor::OKColor()
{//=========================================================================================================================
	name = "empty";

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

}
////=========================================================================================================================
//OKColor::OKColor(sp<OKColor> c)
//{//=========================================================================================================================
//	if (c != nullptr)
//	{
//		name = c->name;
//		r = c->ri();
//		g = c->gi();
//		b = c->bi();
//		a = c->ai();
//	}
//	else
//		log->error("Color c was null!");
//}
//
////=========================================================================================================================
//OKColor::OKColor(const OKColor &c)
//{//=========================================================================================================================
//
////	boost::uuids::random_generator generator;
////	uuid = to_string(generator());
//
//		name = c.name;
//		r = c.r;
//		g = c.g;
//		b = c.b;
//		a = c.a;
//
//}
//=========================================================================================================================
OKColor::OKColor(OKColor c, u8 a)
{//=========================================================================================================================
//
//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	this->name = c.name;
	this->r = c.ri();
	this->g = c.gi();
	this->b = c.bi();
	this->a = a;

}


////=========================================================================================================================
//OKColor::OKColor(OKColor c, float af)
//{//=========================================================================================================================
////
////	boost::uuids::random_generator generator;
////	uuid = to_string(generator());
//
//	name = c.name;
//	r = c.ri();
//	g = c.gi();
//	b = c.bi();
//	a = (int)(af * 255.0f);
//
//}
//
////=========================================================================================================================
//OKColor::OKColor(OKColor c, float af)
//{//=========================================================================================================================
//	if (c != nullptr)
//	{
//		name = c.name;
//		r = c.ri();
//		g = c.gi();
//		b = c.bi();
//		a = (int)(af * 255.0f);
//	}
//	else
//		log->error("Color c was null!");
//}
////=========================================================================================================================
//OKColor::OKColor(float rf, float gf, float bf)
//{//=========================================================================================================================
//
////	boost::uuids::random_generator generator;
////	uuid = to_string(generator());
//
//	r = (int)(rf * 255.0f);
//	g = (int)(gf * 255.0f);
//	b = (int)(bf * 255.0f);
//	a = 255;
//}
//
//
////=========================================================================================================================
//OKColor::OKColor(float rf, float gf, float bf, float af)
//{//=========================================================================================================================
//
////	boost::uuids::random_generator generator;
////	uuid = to_string(generator());
//
//	r = (int)(rf * 255.0f);
//	g = (int)(gf * 255.0f);
//	b = (int)(bf * 255.0f);
//	a = (int)(af * 255.0f);
//}


//=========================================================================================================================
OKColor::OKColor(u8 r, u8 g, u8 b)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}


//=========================================================================================================================
OKColor::OKColor(u8 r, u8 g, u8 b, u8 a)
{//=========================================================================================================================
//
//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


//=========================================================================================================================
OKColor::OKColor(int rgb)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());


	u8 r = (rgb >> 24) & 0xFF;
	u8 g = (rgb >> 16) & 0xFF;
	u8 b = (rgb >> 8) & 0xFF;
	u8 a = (rgb >> 0) & 0xFF;

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


//=========================================================================================================================
OKColor::OKColor(float hf, float sf, float bf, float af, bool hsbOverload)
{//=========================================================================================================================

//	boost::uuids::random_generator generator;
//	uuid = to_string(generator());

	int rgb = HSBtoRGB(hf, sf, bf);
	u8 r = (rgb >> 16) & 0xFF;
	u8 g = (rgb >> 8) & 0xFF;
	u8 b = (rgb >> 0) & 0xFF;
	u8 a = (u8)(af * 255.0f);

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}


//=========================================================================================================================
float OKColor::rf()
{//=========================================================================================================================
	return (float)(r / 255.0f);
}


//=========================================================================================================================
float OKColor::gf()
{//=========================================================================================================================
	return (float)(g / 255.0f);
}


//=========================================================================================================================
float OKColor::bf()
{//=========================================================================================================================
	return (float)(b / 255.0f);
}


//=========================================================================================================================
float OKColor::af()
{//=========================================================================================================================
	return (float)(a / 255.0f);
}


//=========================================================================================================================
u8 OKColor::ri()
{//=========================================================================================================================
	return r;
}


//=========================================================================================================================
u8 OKColor::gi()
{//=========================================================================================================================
	return g;
}


//=========================================================================================================================
u8 OKColor::bi()
{//=========================================================================================================================
	return b;
}


//=========================================================================================================================
u8 OKColor::ai()
{//=========================================================================================================================
	return a;
}


//=========================================================================================================================
float* OKColor::RGBtoHSB(u8 r, u8 g, u8 b)
{//=========================================================================================================================
	float hue, saturation, brightness;


	int cmax = (r > g) ? r : g;
	if (b > cmax)
	{
		cmax = b;
	}
	int cmin = (r < g) ? r : g;
	if (b < cmin)
	{
		cmin = b;
	}

	brightness = ((float)(cmax)) / 255.0f;
	if (cmax != 0)
	{
		saturation = ((float)(cmax - cmin)) / ((float)(cmax));
	}
	else
	{
		saturation = 0;
	}
	if (saturation == 0)
	{
		hue = 0;
	}
	else
	{
		float redc = ((float)(cmax - r)) / ((float)(cmax - cmin));
		float greenc = ((float)(cmax - g)) / ((float)(cmax - cmin));
		float bluec = ((float)(cmax - b)) / ((float)(cmax - cmin));
		if (r == cmax)
		{
			hue = bluec - greenc;
		}
		else if (g == cmax)
		{
			hue = 2.0f + redc - bluec;
		}
		else
		{
			hue = 4.0f + greenc - redc;
		}
		hue = hue / 6.0f;
		if (hue < 0)
		{
			hue = hue + 1.0f;
		}
	}

	float* hsbvals = new float[3];
	hsbvals[0] = hue;
	hsbvals[1] = saturation;
	hsbvals[2] = brightness;
	return hsbvals;
}


//=========================================================================================================================
int OKColor::HSBtoRGB(float hue, float saturation, float brightness)
{//=========================================================================================================================
	int r = 0, g = 0, b = 0;
	if (saturation == 0)
	{
		r = g = b = (int)(brightness * 255.0f + 0.5f);
	}
	else
	{
		float h = (hue - (float)(floor(hue))) * 6.0f;
		float f = h - (float)(floor(h));
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int)(h))
		{
		case 0:
			r = (int)(brightness * 255.0f + 0.5f);
			g = (int)(t * 255.0f + 0.5f);
			b = (int)(p * 255.0f + 0.5f);
			break;
		case 1:
			r = (int)(q * 255.0f + 0.5f);
			g = (int)(brightness * 255.0f + 0.5f);
			b = (int)(p * 255.0f + 0.5f);
			break;
		case 2:
			r = (int)(p * 255.0f + 0.5f);
			g = (int)(brightness * 255.0f + 0.5f);
			b = (int)(t * 255.0f + 0.5f);
			break;
		case 3:
			r = (int)(p * 255.0f + 0.5f);
			g = (int)(q * 255.0f + 0.5f);
			b = (int)(brightness * 255.0f + 0.5f);
			break;
		case 4:
			r = (int)(t * 255.0f + 0.5f);
			g = (int)(p * 255.0f + 0.5f);
			b = (int)(brightness * 255.0f + 0.5f);
			break;
		case 5:
			r = (int)(brightness * 255.0f + 0.5f);
			g = (int)(p * 255.0f + 0.5f);
			b = (int)(q * 255.0f + 0.5f);
			break;
		}
	}

	unsigned int rs = static_cast<unsigned int>(r << 16);
	unsigned int gs = static_cast<unsigned int>(g << 8);
	unsigned int bs = static_cast<unsigned int>(b << 0);

	return (int)(0xff000000 | rs | gs | bs);
}


//=========================================================================================================================
void OKColor::darker()
{//=========================================================================================================================
	darker(0.4f);
}


//=========================================================================================================================
void OKColor::darker(float scale)
{//=========================================================================================================================
	scale = 1 - scale;

	float* hsbvals = RGBtoHSB(ri(), gi(), bi());


	//if already darkest increase saturation
	if (hsbvals[2] == 0.0f)
	{
		hsbvals[1] *= 1.0f / scale;
		if (hsbvals[1] > 1.0f)
		{
			hsbvals[1] = 1.0f;
		}
	}

	hsbvals[2] *= scale;
	if (hsbvals[2] < 0.0f)
	{
		hsbvals[2] = 0.0f;
	}

	int rgb = HSBtoRGB(hsbvals[0], hsbvals[1], hsbvals[2]);
	u8 ri = (rgb >> 16) & 0xFF;
	u8 gi = (rgb >> 8) & 0xFF;
	u8 bi = (rgb >> 0) & 0xFF;

	r = ri;
	g = gi;
	b = bi;
}


//=========================================================================================================================
void OKColor::lighter()
{//=========================================================================================================================

	//if(lighter!=null)return lighter;

	lighter(0.4f);
}


//=========================================================================================================================
void OKColor::lighter(float scale)
{//=========================================================================================================================

	if (scale < 1.0f)
	{
		scale += 1.0f;
	}


	float* hsbvals = RGBtoHSB(ri(), gi(), bi());

	//if already lightest, decrease saturation instead
	if (hsbvals[2] == 1.0f)
	{
		hsbvals[1] *= 1.0f / scale;
		if (hsbvals[1] < 0.0f)
		{
			hsbvals[1] = 0.0f;
		}
	}

	hsbvals[2] *= scale;
	if (hsbvals[2] > 1.0f)
	{
		hsbvals[2] = 1.0f;
	}

	int rgb = HSBtoRGB(hsbvals[0], hsbvals[1], hsbvals[2]);
	u8 ri = (rgb >> 16) & 0xFF;
	u8 gi = (rgb >> 8) & 0xFF;
	u8 bi = (rgb >> 0) & 0xFF;

	r = ri;
	g = gi;
	b = bi;
}

/*
void Color::multiply(sp<Color>c)
{
   return ms<Color>(rf() * c->rf(), gf() * c->gf(), bf() * c->bf(), af() * c->af());
}

void Color::addToCopy(sp<Color>c)
{
   return ms<Color>(rf() + c->rf(), gf() + c->gf(), bf() + c->bf(), af() + c->af());
}

void Color::scaleCopy(float value)
{
   return ms<Color>(rf() * value, gf() * value, bf() * value, af() * value);
}
*/


//int OKColor::rgbatoABGRInt(u8 r, u8 g, u8 b, u8 a)
//{ //==========================================================================================================================
//	return ((a << 15) + ((b) << 10) + ((g) << 5) + (r));
//}

//int Color::HexToDec(const string &hexst)
//{ //===============================================================================================
//   return int::valueOf(hexst, 16);
//}

int OKColor::DecToRed(int dec)
{ //===============================================================================================
	return (dec % 32) * 8;
}

int OKColor::DecToGreen(int dec)
{ //===============================================================================================
	return ((dec / 32) % 32) * 8;
}

int OKColor::DecToBlue(int dec)
{ //===============================================================================================
	return (dec / 1024) * 8;
}

//==========================================================================================================================
int OKColor::getRGBA()
{//==========================================================================================================================
	return (r << 24) + (g << 16) + (b << 8) + a;
}

int OKColor::getRGBA(u8 r, u8 g, u8 b, u8 a)
{
	return (r << 24) + (g << 16) + (b << 8) + a;
}
