#pragma once
#include <map>
#include <string>
#include "Sprite.h"

class AssetPool
{
public:
	static std::map<std::string, Sprite*> sprites;
	static bool hasSprite(std::string pictureFile);
	static Sprite* getSprite(std::string pictureFile);
	static void addSprite(std::string pictureFile, Sprite* sprite);
};
