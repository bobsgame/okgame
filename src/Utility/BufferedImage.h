//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;


#include "Logger.h"


class BobColor;


class BufferedImage
{
public:
	//static Logger log;

	u8* rgbadata = nullptr;
	int w = 0;
	int h = 0;

	BobColor* currentFillColor = nullptr;

	BufferedImage();
	BufferedImage(u8* rgbadata, int w, int h);
	BufferedImage(int w, int h);
	void setRGB(int x, int y, int rgb);
	int getRGBA(int x, int y);
	u8* getData();
	void setColor(BobColor* c);
	void fillRect(int x, int y, int w, int h);
	static BufferedImage* loadFromPNG(string filename);
	const static int TYPE_INT_ARGB = 0;
	int getWidth();
	int getHeight();
};

