#include "AssetPool.h"
#include <iostream>

bool AssetPool::hasSprite(std::string pictureFile) {
	return sprites.contains(pictureFile);
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

std::map<std::string, Sprite*> AssetPool::sprites;