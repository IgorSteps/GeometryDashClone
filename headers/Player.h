#pragma once
#include "Sprite.h"
class Player : public Component
{
public:
	Player(Sprite* layerOne, Sprite* layerTwo, Sprite* layerThree, float colourOne[3], float colourTwo[3]);
	void draw(Shader& shader, glm::mat4& Model, glm::mat4& Proj);
	Component* copy();

private:
	Sprite* layerOne;
	Sprite* layerTwo;
	Sprite* layerThree;

	const int threshold = 200;
	FIBITMAP* dib = nullptr;
};

