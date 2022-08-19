#include "Player.h"
#include <iostream>

Player::Player(Sprite* layerOne, Sprite* layerTwo, Sprite* layerThree, float colourOne[], float colourTwo[])
{
	this->layerOne = layerOne;
	this->layerTwo = layerTwo;
	this->layerThree = layerThree;
	this->dib=ImageLoading::loadImageTwo("assets/player/layerOne.png");
	RGBQUAD colour;

	for (int y = 0; y < layerOne->getWidth(); y++)
	{
		for (int x = 0; x < layerOne->getHeight(); x++)
		{
			FreeImage_GetPixelColor(this->dib, x, y, &colour);
			if (colour.rgbRed > this->threshold && colour.rgbBlue > this->threshold && colour.rgbGreen > this->threshold)
			{
				layerOne->colour[0] = colourOne[0];
				layerOne->colour[1] = colourOne[1];
				layerOne->colour[2] = colourOne[2];
			}
			
		}
	}

	
	this->dib = ImageLoading::loadImageTwo("assets/player/layerTwo.png");
	for (int y = 0; y < layerTwo->getWidth(); y++)
	{
		for (int x = 0; x < layerTwo->getHeight(); x++)
		{
			FreeImage_GetPixelColor(this->dib, x, y, &colour);
			if (colour.rgbRed > this->threshold && colour.rgbBlue > this->threshold && colour.rgbGreen > this->threshold)
			{
				layerTwo->colour[0] = colourTwo[0];
				layerTwo->colour[1] = colourTwo[1];
				layerTwo->colour[2] = colourTwo[2];
			}

		}
	}
	
}



void Player::draw(Shader& shader, glm::mat4& Model, glm::mat4& Proj) {
	layerOne->draw(shader, Model, Proj);
	layerTwo->draw(shader, Model, Proj);
	layerThree->draw(shader, Model, Proj);
}
