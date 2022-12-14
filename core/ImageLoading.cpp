
#include "ImageLoading.h"
#include <iostream>
#include <glad/glad.h>


bool ImageLoading::loadImage(std::string filename)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP* dib = nullptr;
	//pointer to the image data
	BYTE* bits = nullptr;
	//image width and height
	//unsigned int width(0), height(0);

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return false;
	
	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename.c_str());
	//if the image failed to load, return failure
	if (!dib)
		return false;

	// OpenGL has the origin in the lower left corner,
	// unlike most windowing systems in use, where the origin is in the upper left corner.
	// this method flips the image vertically
	FreeImage_FlipVertical(dib);
	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	int outWidth = FreeImage_GetWidth(dib);
	int outHeight = FreeImage_GetHeight(dib);

	//if one of these failed (they shouldn't), return failure
	if ((bits == 0) || (outWidth == 0) || (outHeight == 0))
		return false;


	FREE_IMAGE_COLOR_TYPE colType = FreeImage_GetColorType(dib);

	//bits are stored in BGR order.
	if (colType == FIC_RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outWidth,
			outHeight, 0, GL_BGR, GL_UNSIGNED_BYTE,
			bits);
	}
	else if (colType == FIC_RGBALPHA)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, outWidth,
			outHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE,
			bits);
	}
	else
	{
		std::cout << "Image is not RGB or RGBA" << std::endl;
		FreeImage_Unload(dib);
		return false;
	}

	FreeImage_Unload(dib);

	return true;
}

FIBITMAP* ImageLoading::loadImageTwo(std::string file)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP* dib = nullptr;
	
	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(file.c_str(), 0);
	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif)) {
		dib = FreeImage_Load(fif, file.c_str());
		std::cout << "Player image dib for colour is loaded" << '\n';
	} else 
		std::cout << "Player image dib for colour is NOT loaded" << '\n';

	return dib;
}



//RGBQUAD ImageLoading::getPixelColour(FIBITMAP* dib, int x, int y, RGBQUAD color)
//{
//
//	FreeImage_GetPixelColor(dib, x, y, &color);
//
//	return color;
//};


