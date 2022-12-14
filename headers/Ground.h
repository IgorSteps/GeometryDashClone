#pragma once
#include "Component.h"
#include "Sprite.h"
class Ground : public Component
{
public:
	Ground();
	Ground(Sprite *sp, Shader& sh);
	~Ground();
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Component* copy();
	std::string serialise(int tabSize);

	Sprite* sp;
};

