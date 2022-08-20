#pragma once
#include <vector>
#include "Sprite.h"
class Spritesheet
{
public:
	Spritesheet(std::string file, float tW, float tH, float sp, int columns, int size, float fileW, float fileH);
	std::vector<Sprite*> sprites;
	float tileWidth, tileHeight, spacing;
};

