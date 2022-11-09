#pragma once
#include "Sprite.h"
enum PlayerState
{
	NORMAL,
	FLY
};
class Player : public Component
{
public:
	Player(Sprite* layerOne, Sprite* layerTwo, Sprite* layerThree, float colourOne[3], float colourTwo[3]);
	void update(float dt);
	void draw(Shader& shader, glm::mat4& Model, glm::mat4& Proj);
	Component* copy();
	std::string serialise(int tabSize);
	void die();
	bool onGround = true;
	PlayerState m_State;
private:
	void addJumpForce();
	Sprite* layerOne;
	Sprite* layerTwo;
	Sprite* layerThree;

	const int threshold = 200;
	FIBITMAP* dib = nullptr;
};

