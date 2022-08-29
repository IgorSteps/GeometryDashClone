#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Constants.h"
class Rigidbody : public Component {
public:
	glm::vec2 Velocity;
	Rigidbody(glm::vec2 v) {
		this->Velocity = v;
	}
	void update(float dt) {
		gameObj->transform->position.y += Velocity.y * dt;
		gameObj->transform->position.x += Velocity.x * dt;

		Velocity.y += Constants::GRAVITY * dt;

		if (abs(Velocity.y) > Constants::TERMINAL_VELOCITY) {
			Velocity.y = Velocity.y * Constants::TERMINAL_VELOCITY;
		}
	}
};