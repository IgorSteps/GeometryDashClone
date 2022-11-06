#include "LevelEditorControls.h"
#include "Game.h"
#include "ML.h"
#include "KL.h"
#include "Constants.h"
#include <iostream>
#include <Bounds.h>
#include <LevelEditorScene.h>
#include <Game.h>
#include <TriangleBounds.h>

LevelEditorControls::LevelEditorControls(int gridWidth, int gridHeight, Shader& sh)
{
	m_gridWidth = gridWidth;
	m_gridHeight = gridHeight;
	m_debounceTime = 0.2f;
	m_debounceLeft = 0.0f;
	m_debounceKey = 0.2f;
	m_debounceKeyLeft=0.0f;
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
	clearSelected();
	addGameObjectToSelected(mousePos);
}

void LevelEditorControls::update(float dt)
{
	m_debounceLeft -= dt;
	m_debounceKeyLeft -= dt;
	if (!isEditing && gameObj->getComponent<Sprite>())
	{
		isEditing = true;
	}
	if (isEditing)
	{
		if (selectedGameObjects.size() != 0)
		{
			clearSelected();
		}
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

	if (KL::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		escapeKeyPressed();
	}

	if (KL::isKeyPressed(GLFW_KEY_LEFT_SHIFT))
	{
		shiftPressed = true;
	} 
	else
	{
		shiftPressed = false;
	}
	
	if (m_debounceKeyLeft <= 0 && KL::isKeyPressed(GLFW_KEY_LEFT))
	{
		moveObjects(LEFT, shiftPressed ? 0.1f : 1.0f); 
		m_debounceKeyLeft = m_debounceKey;
	}
	else if (m_debounceKeyLeft <= 0 && KL::isKeyPressed(GLFW_KEY_RIGHT))
	{
		moveObjects(RIGHT, shiftPressed ? 0.1f : 1.0f);
		m_debounceKeyLeft = m_debounceKey;
	} 
	else if (m_debounceKeyLeft <= 0 &&  KL::isKeyPressed(GLFW_KEY_UP))
	{
		moveObjects(UP, shiftPressed ? 0.1f : 1.0f);
		m_debounceKeyLeft = m_debounceKey;
	}
	else if (m_debounceKeyLeft <= 0 &&  KL::isKeyPressed(GLFW_KEY_DOWN))
	{
		moveObjects(DOWN, shiftPressed ? 0.1f : 1.0f);
		m_debounceKeyLeft = m_debounceKey;
	}

	if (m_debounceKeyLeft <= 0 && KL::isKeyPressed(GLFW_KEY_D))
	{
		if (KL::isKeyPressed(GLFW_KEY_LEFT_CONTROL))
		{
			duplicate();
			m_debounceKeyLeft = m_debounceKey;
		}
	}


	if (m_debounceKeyLeft <= 0 && KL::isKeyPressed(GLFW_KEY_Q))
	{
		rotate(90.0f);
		m_debounceKeyLeft = m_debounceKey;
	}
	else if (m_debounceKeyLeft <= 0 && KL::isKeyPressed(GLFW_KEY_E))
	{
		rotate(-90.0f);
		m_debounceKeyLeft = m_debounceKey;
		std::cout << "Rotating\n";
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

void LevelEditorControls::escapeKeyPressed()
{
	GameObject* newGameObject = new GameObject("Mouse Cursor", gameObj->transform->copy());
	newGameObject->addComponent(this);
	LevelEditorScene* scene = (LevelEditorScene*)Game::game->getCurrentScene();
	scene->mouseCursor = newGameObject;
	isEditing = false;
}

void LevelEditorControls::clearSelected()
{
	for (GameObject* go : selectedGameObjects)
	{
		go->getComponent<Bounds>()->isSelected = false;
	}
	selectedGameObjects.clear();
}

void LevelEditorControls::moveObjects(Direction direction, float scale)
{
	glm::vec2 distance{};

	switch (direction)
	{
		case UP:
			distance.y -= Constants::TILE_HEIGHT * scale;
			break;
		case DOWN:
			distance.y = Constants::TILE_HEIGHT * scale;
			break;
		case LEFT:
			distance.x -= Constants::TILE_WIDTH * scale;
			break;
		case RIGHT:
			distance.x = Constants::TILE_WIDTH * scale;
			break;
		default:
			std::cout << "Unknown direction enum: '" << direction << "'" << std::endl;
			exit(-1);
			break; 
	}

	for (GameObject* go : selectedGameObjects)
	{
		go->transform->position.x += distance.x;
		go->transform->position.y += distance.y;
	}
}

void LevelEditorControls::duplicate()
{
	for (GameObject* go : selectedGameObjects)
	{
		Game::game->getCurrentScene()->addGameObject(go->copy(shader));
	}
}

void LevelEditorControls::rotate(float d)
{
	for (GameObject* go : selectedGameObjects)
	{
		go->transform->rotateion += d;
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