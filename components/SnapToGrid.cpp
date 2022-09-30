#include "SnapToGrid.h"
#include "Game.h"
#include "ML.h"
#include "Constants.h"
#include <iostream>

SnapToGrid::SnapToGrid(int gridWidth, int gridHeight, Shader& sh)
{
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
	m_debounceTime = 0.2f;
	m_debounceLeft = 0.0f;
	
	shader = sh;
}

SnapToGrid::~SnapToGrid()
{
	delete object;
}

void SnapToGrid::update(float dt)
{
	m_debounceLeft -= dt;

	if (this->gameObj->getComponent<Sprite>() != nullptr)
	{
		// calculate x,y coord of the mouse on the grid
		float x = static_cast<float>(floor((ML::getX() + Game::game->getCurrentScene()->camera->position.x + ML::getDx()) / m_gridWidth));
		float y = static_cast<float>(floor((ML::getY() + Game::game->getCurrentScene()->camera->position.y + ML::getDy()) / m_gridHeight));

		// transfer to world coord
		// 'y * m_gridHeight' converts to world space
		// 'Game::game->getCurrentScene()->camera->position.x' transforms it local to the window
		// add 21 to center sprite on the mouse cursor
		this->gameObj->transform->position.x = x * m_gridWidth - Game::game->getCurrentScene()->camera->position.x + Constants::PLAYER_CENTER;
		this->gameObj->transform->position.y = y * m_gridHeight - Game::game->getCurrentScene()->camera->position.y + Constants::PLAYER_CENTER;
		
		if (ML::getY() < Constants::BUTTON_OFFSET_Y &&
			ML::mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT) && m_debounceLeft < 0.0f)
		{
			m_debounceLeft = m_debounceTime;

			object = this->gameObj->copy(shader);
			// transform back to world space
			object->transform->position = glm::vec2(x * m_gridWidth + Constants::PLAYER_CENTER, y * m_gridHeight + Constants::PLAYER_CENTER);
			
			Game::game->getCurrentScene()->addGameObject(object);
			
			//test
			//std::cout << "----------------Copy func called----------------" << '\n';
		}
	}
}

void SnapToGrid::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	Sprite* sprite = this->gameObj->getComponent<Sprite>();
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->gameObj->transform->position.x,
		this->gameObj->transform->position.y, 0.0f));
	if (sprite != nullptr)
	{
		sprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}

Component* SnapToGrid::copy() 
{
	return nullptr;
}

std::string SnapToGrid::serialise(int tabSize)
{
	return "";
}