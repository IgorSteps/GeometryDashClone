#include "LevelEditorControls.h"
#include "Game.h"
#include "ML.h"
#include "KL.h"
#include "Constants.h"
#include <iostream>
#include <Bounds.h>

LevelEditorControls::LevelEditorControls(int gridWidth, int gridHeight, Shader& sh)
{
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
	m_debounceTime = 0.2f;
	m_debounceLeft = 0.0f;
	
	shader = sh;
	
}

LevelEditorControls::~LevelEditorControls()
{
	delete object;
}

void LevelEditorControls::updateSpritePosition()
{
	// calculate x,y coord of the mouse on the grid
	m_WorldX = static_cast<float>(floor((ML::getX() + Game::game->getCurrentScene()->camera->position.x + ML::getDx()) / m_gridWidth));
	m_WorldY = static_cast<float>(floor((ML::getY() + Game::game->getCurrentScene()->camera->position.y + ML::getDy()) / m_gridHeight));

	// transfer to world coord
	// 'y * m_gridHeight' converts to world space
	// 'Game::game->getCurrentScene()->camera->position.x' transforms it local to the window
	// add 21 to center sprite on the mouse cursor
	this->gameObj->transform->position.x = m_WorldX * m_gridWidth - Game::game->getCurrentScene()->camera->position.x + Constants::PLAYER_CENTER;
	this->gameObj->transform->position.y = m_WorldY * m_gridHeight - Game::game->getCurrentScene()->camera->position.y + Constants::PLAYER_CENTER;
}

void LevelEditorControls::copyGameObjectToScene()
{
	object = this->gameObj->copy(shader);
	// transform back to world space
	object->transform->position = glm::vec2(m_WorldX * m_gridWidth + Constants::PLAYER_CENTER, m_WorldY * m_gridHeight + Constants::PLAYER_CENTER);

	Game::game->getCurrentScene()->addGameObject(object);
}

void LevelEditorControls::addGameObjectToSelected(glm::vec2 mousePos)
{
	mousePos.x += Game::game->getCurrentScene()->camera->position.x;
	mousePos.y += Game::game->getCurrentScene()->camera->position.y;
	for (GameObject* go : Game::game->getCurrentScene()->getAllGameObjects())
	{
		Bounds* bounds = go->getComponent<Bounds>();
		if (bounds != nullptr && bounds->raycast(mousePos))
		{
			selectedGameObjects.push_back(go);
			bounds->isSelected = true;
			break;
		}
	}
}

void LevelEditorControls::clearSelectedObjectsAndAdd(glm::vec2 mousePos)
{
	for (GameObject* go : selectedGameObjects)
	{
		go->getComponent<Bounds>()->isSelected = false;
	}
	selectedGameObjects.clear();
	addGameObjectToSelected(mousePos);
}

void LevelEditorControls::update(float dt)
{
	m_debounceLeft -= dt;
	if (!isEditing && gameObj->getComponent<Sprite>())
	{
		isEditing = true;
	}
	if (isEditing)
	{
		updateSpritePosition();
	}

	if (ML::getY() < Constants::TAB_OFFSET_Y &&
		ML::mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT) &&
		m_debounceLeft < 0.0f)
	{
		m_debounceLeft = m_debounceTime;
		if (isEditing)
		{
			copyGameObjectToScene();
		}
		else if(KL::isKeyPressed(GLFW_KEY_LEFT_SHIFT)) 
		{
			addGameObjectToSelected(glm::vec2(ML::getX(), ML::getY()));
		}
		else
		{
			clearSelectedObjectsAndAdd(glm::vec2(ML::getX(), ML::getY()));
		}
	}
	
}

void LevelEditorControls::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	Sprite* sprite = this->gameObj->getComponent<Sprite>();
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->gameObj->transform->position.x,
		this->gameObj->transform->position.y, 0.0f));
	if (sprite != nullptr)
	{
		sprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}

Component* LevelEditorControls::copy() 
{
	return nullptr;
}

std::string LevelEditorControls::serialise(int tabSize)
{
	return "";
}