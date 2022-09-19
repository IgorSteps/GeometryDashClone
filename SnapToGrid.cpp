#include "SnapToGrid.h"
#include "Game.h"
#include "ML.h"
#include <iostream>

SnapToGrid::SnapToGrid(int gridWidth, int gridHeight)
{
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
	m_debounceTime = 0.2f;
	m_debounceLeft = 0.0f;
}

void SnapToGrid::update(float dt)
{
	if (this->gameObj->getComponent<Sprite>() != nullptr)
	{
		// calculate x,y coord of the mouse on the grid
		float x = static_cast<float>(floor((ML::getX() + Game::game->getCurrentScene()->camera->position.x + ML::getDx()) / m_gridWidth));
		float y = static_cast<float>(floor((ML::getY() + Game::game->getCurrentScene()->camera->position.y + ML::getDy()) / m_gridHeight));

		// transfer to world coord
		// 'y * m_gridHeight' converts to world space
		// 'Game::game->getCurrentScene()->camera->position.x' transforms it local to the window
		// add 21 to center sprite on the mouse cursor
		this->gameObj->transform->position.x = x * m_gridWidth - Game::game->getCurrentScene()->camera->position.x + 21;
		this->gameObj->transform->position.y = y * m_gridHeight - Game::game->getCurrentScene()->camera->position.y + 21;
		

		if (ML::mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		{
			GameObject* object = this->gameObj->copy();
			//Game::game->getCurrentScene()->addGameObject(object);
			std::cout << "-------------Copy constructor called--------------" << '\n';
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
