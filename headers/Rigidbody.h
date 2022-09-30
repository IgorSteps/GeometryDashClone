#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Constants.h"
class Rigidbody : public Component {
public:
	Rigidbody(glm::vec2 v);
	void update(float dt);
	Component* copy();
	std::string serialise(int tabSize);


	glm::vec2 Velocity;
};