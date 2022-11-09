//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "oktypes.h"
class Logger;


#include "Logger.h"


class OKColor;


class BufferedImage
{
public:
	//static Logger log;

	u8* rgbadata = nullptr;
	int w = 0;
	int h = 0;

	sp<OKColor> currentFillColor = nullptr;

	BufferedImage();
	BufferedImage(u8* rgbadata, int w, int h);
	BufferedImage(int w, int h);
	void setRGB(int x, int y, int rgb);
	int getRGBA(int x, int y);
	u8* getData();
	void setColor(sp<OKColor> c);
	void fillRect(int x, int y, int w, int h);
	static sp<BufferedImage> loadFromPNG(string filename);
	const static int TYPE_INT_ARGB = 0;
	int getWidth();
	int getHeight();
};

