#include "AssetPool.h"
#include <iostream>

bool AssetPool::hasSprite(std::string pictureFile) {
	return sprites.contains(pictureFile);
}

bool AssetPool::hasSpriteSheet(std::string pictureFile)
{
	return spritesheets.contains(pictureFile);
}

Sprite* AssetPool::getSprite(std::string pictureFile) {
	if (hasSprite(pictureFile)) {
		return sprites.at(pictureFile);
	}
	else {
		Sprite* sprite = new Sprite(pictureFile);
		addSprite(pictureFile, sprite); 
		return sprites.at(pictureFile);
	}
	
}

Spritesheet* AssetPool::getSpritesheet(std::string pictureFile) {
	if (hasSpriteSheet(pictureFile)) {
		return spritesheets.at(pictureFile);
	}
	else 
	{
		std::cout << "Spritesheet " << pictureFile << " doesn't exist\n";
		exit(-1);
	}

	return nullptr;
}

void AssetPool::addSprite(std::string pictureName, Sprite* sprite) {
	if (!hasSprite(pictureName)) {
		sprites.insert_or_assign(pictureName, sprite);
	}
	else
	{
		std::cout << "AssetPool alread has asset: " << pictureName << '\n';
		exit(-1);
	}
}

void AssetPool::addSpritesheet(std::string pictureName, float tileWidth, float tileHeight, float spacing, int columns, int size, float fileW, float fileH)
{
	if (!hasSpriteSheet(pictureName)) 
	{
		Spritesheet *mySpritesheet = new Spritesheet(pictureName, tileWidth, tileHeight, spacing, columns, size, fileW, fileH);
		spritesheets.insert_or_assign(pictureName, mySpritesheet);
	}

}

std::map<std::string, Sprite*> AssetPool::sprites; 
std::map<std::string, Spritesheet*> AssetPool::spritesheets;