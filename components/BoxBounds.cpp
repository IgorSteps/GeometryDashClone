#include "BoxBounds.h"
#include <Parser.h>
#include <GameObject.h>
#include <Rigidbody.h>
#include <LevelScene.h>
#include <Game.h>

BoxBounds::BoxBounds(float width, float height) {
	m_Width = width;
	m_Height = height;
	m_HalfWidth = m_Width / 2;
	m_HalfHeight = m_Height / 2;
	type = Box;
	m_EnclosingRadius = std::sqrtf(powf(m_HalfHeight, 2) + powf(m_HalfWidth,2));
	// load shader for lines
	if (!shader.load("Line shader", "./glslfiles/lineShader.vert", "./glslfiles/lineShader.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	quad = Line();
	
	float col[] = { 0.0f, 1.0f, 0.0f };
	quad.setColour(col);
	quad.SetWidth(42.0f);
	quad.SetHeight(42.0f);
	quad.setIsGrid(true);
	

}

BoxBounds::~BoxBounds()
{
	delete deserialsiedBB;
}


void BoxBounds::start()
{
	calculateTransform();
}


void BoxBounds::update(float dt) {
	//std::cout << "We are insside box bounds" << '\n';
}

void BoxBounds::draw(Shader& sh, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	if (isSelected)
	{
		//	std::cout << gameObj->transform->position.x << " and " << gameObj->transform->position.y << '\n';
		//std::cout << ModelViewMatrix.po << " and " << gameObj->transform->position.x << '\n';
		//ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f - 21.0f, 0.0f - 21.0f, 1.0f));
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj->transform->position.x - 21.0f, gameObj->transform->position.y - 21.0f, 1.0f));
		
		quad.draw(shader, ModelViewMatrix, ProjectionMatrix);
		
	}
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

void BoxBounds::calculateTransform()
{
	glm::vec2 p1(gameObj->transform->position.x - m_HalfWidth, gameObj->transform->position.y - m_HalfHeight);	// top left
	glm::vec2 p2(gameObj->transform->position.x - m_HalfWidth, gameObj->transform->position.y + m_HalfHeight);  // bottom left
	glm::vec2 p3(gameObj->transform->position.x + m_HalfWidth, gameObj->transform->position.y + m_HalfHeight);  // bottom right
	glm::vec2 p4(gameObj->transform->position.x + m_HalfWidth, gameObj->transform->position.y - m_HalfHeight);	// top right

	quad.init(shader);
	

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

bool BoxBounds::raycast(glm::vec2 position)
{
	return position.x > gameObj->transform->position.x &&
		position.x < gameObj->transform->position.x + m_Width &&
		position.y > gameObj->transform->position.y &&
		position.y < gameObj->transform->position.y + m_Height;
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