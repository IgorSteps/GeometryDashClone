#include "Rigidbody.h"
#define signum(x)  ((signbit(x) ?  -1 : 1)

Rigidbody::Rigidbody(glm::vec2 v) {
	this->Velocity = v;
}

void Rigidbody::update(float dt) {
	gameObj->transform->position.y += Velocity.y * dt;
	gameObj->transform->position.x += Velocity.x * dt;

	Velocity.y += Constants::GRAVITY * dt;

	if (abs(Velocity.y) > Constants::TERMINAL_VELOCITY) {
		Velocity.y = signum(Velocity.y) * Constants::TERMINAL_VELOCITY);
	}
}