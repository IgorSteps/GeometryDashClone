#include "BoxBounds.h"
#include <Parser.h>
#include <GameObject.h>
#include <Rigidbody.h>
#include <LevelScene.h>

BoxBounds::BoxBounds(float width, float height) {
	m_Width = width;
	m_Height = height;
	m_HalfWidth = m_Width / 2;
	m_HalfHeight = m_Height / 2;
	type = Box;
	m_EnclosingRadius = std::sqrtf(pow(m_HalfHeight, 2) + pow(m_HalfWidth,2));
}

BoxBounds::~BoxBounds()
{
	delete deserialsiedBB;
}


void BoxBounds::update(float dt) {
	//std::cout << "We are insside box bounds" << '\n';
}

Component* BoxBounds::copy() 
{
	return new BoxBounds(m_Width, m_Height);
}

void BoxBounds::resolveCollision(GameObject& player)
{
	BoxBounds* playerBounds = player.getComponent<BoxBounds>();
	float dx = this->gameObj->transform->position.x - playerBounds->gameObj->transform->position.x;
	float dy = this->gameObj->transform->position.y - playerBounds->gameObj->transform->position.y;

	float combinedHalfWidth = playerBounds->m_HalfWidth + this->m_HalfWidth;
	float combinedHalfHeight = playerBounds->m_HalfHeight + this->m_HalfHeight;

	float overlapX = combinedHalfWidth - abs(dx);
	float overlapY = combinedHalfHeight - abs(dy);
	if (overlapX >= overlapY)
	{
		if (dy > 0)
		{
			// Collision on the top of the player
			player.transform->position.y = gameObj->transform->position.y - playerBounds->getHeight();
			player.getComponent<Rigidbody>()->Velocity.y = 0.0f;
			player.getComponent<Player>()->onGround = true;
		}
		else
		{
			// Collision on the bottom of the player
			player.getComponent<Player>()->die();
		}
	}
	else
	{
		// Collision on the ledt or right
		if (dx < 0 && dy <= 0.3f)
		{
			player.transform->position.y = gameObj->transform->position.y - playerBounds->getHeight();
			player.getComponent<Rigidbody>()->Velocity.y = 0.0f;
			player.getComponent<Player>()->onGround = true;
		}
		else
		{
			player.getComponent<Player>()->die();
		}
	}
}

bool BoxBounds::checkCollision(BoxBounds& b1, BoxBounds& b2)
{
	float dx = b1.gameObj->transform->position.x - b2.gameObj->transform->position.x;
	float dy = b1.gameObj->transform->position.y - b2.gameObj->transform->position.y;

	float combinedHalfWidth = b1.m_HalfWidth + b2.m_HalfWidth;
	float combinedHalfHeight = b1.m_HalfHeight + b2.m_HalfHeight;

	if (abs(dx) <= combinedHalfWidth)
	{
		return abs(dy) <= combinedHalfHeight;
	}

	return false;
}

float BoxBounds::getWidth()
{
	return m_Width;
}

float BoxBounds::getHeight()
{
	return m_Height;
}

std::string BoxBounds::serialise(int tabSize)
{
	std::string builder;
	builder.append(beginObjectProperty("BoxBounds", tabSize));
	builder.append(addFloatProperty("Width", m_Width, tabSize + 1, true, true));
	builder.append(addFloatProperty("Height", m_Height, tabSize + 1, true, false));
	builder.append(closeObjectProperty(tabSize));

	return builder;
}

BoxBounds* BoxBounds::deserialise()
{
	float width = Parser::consumeFloatProperty("Width");
	Parser::consume(',');
	float height = Parser::consumeFloatProperty("Height");
	Parser::consumeEndObjectProperty();
	deserialsiedBB = new BoxBounds(width, height);
	return deserialsiedBB;
}


BoxBounds* BoxBounds::deserialsiedBB = nullptr;