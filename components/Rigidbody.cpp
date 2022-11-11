#include "Rigidbody.h"
#include "GameObject.h"
#include "Player.h"

Rigidbody::Rigidbody(glm::vec2 v) {
	this->Velocity = v;
}

void Rigidbody::update(float dt) {
	gameObj->transform->position.y += Velocity.y * dt;
	gameObj->transform->position.x += Velocity.x * dt;
	if(gameObj->getComponent<Player>()->m_State == FLY)
	{
		Velocity.y += 800 * dt;
	}
	else
	{
		Velocity.y += Constants::GRAVITY * dt;
	}
	
	if (abs(Velocity.y) > Constants::TERMINAL_VELOCITY) 
	{
   		Velocity.y = signum(Velocity.y) * Constants::TERMINAL_VELOCITY;
	}
}

Component* Rigidbody::copy()
{
	return nullptr;
}

std::string Rigidbody::serialise(int tabSize)
{
	return "";
}