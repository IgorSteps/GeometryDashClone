#pragma once
#include <map>
#include <string>
#include "Sprite.h"
#include <Spritesheet.h>

class AssetPool
{
public:
	static std::map<std::string, Sprite*> sprites;
	static std::map<std::string, Spritesheet*> spritesheets;

	static bool hasSprite(std::string pictureFile);
	static bool hasSpriteSheet(std::string pictureFile);

	static Sprite* getSprite(std::string pictureFile);
	static Spritesheet* getSpritesheet(std::string pictureFile);

	static void addSprite(std::string pictureFile, Sprite* sprite);
	static void addSpritesheet(std::string pictureName, float tileWidth, float tileHeight, float spacing, int columns, int size, float fileW, float fileH);
};
