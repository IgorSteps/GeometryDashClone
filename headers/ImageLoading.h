#pragma once


#include <string>
#include "FreeImage.h"

class ImageLoading
{
public:
	static bool loadImage(std::string name);
	static FIBITMAP* loadImageTwo(std::string);
	static RGBQUAD getPixelColour(FIBITMAP* dib, int x, int y, RGBQUAD& color);
};

