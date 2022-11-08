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
	


	// initilise a box select sprite
	if (!shaderLine.load("Line Shader for LevelEditorControls", "./glslfiles/lineShader.vert", "./glslfiles/lineShader.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}
	box = Line();
	box.SetHeight(10.0f);
	box.SetWidth(10.0f);
	float col[] = { 1.0f, 1.0f, 1.0f, .3f };
	box.setColour(col);
	box.setIsGrid(true);
	box.init(shaderLine);
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
		m_debounceLeft < 0.0f &&
		!wasDragged)
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
	else if (!ML::mouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT) && wasDragged)
	{
		wasDragged = false;
		clearSelected();
		std::vector<GameObject*> objs = boxSelect(mousePos.at(0).x, mousePos.at(0).y, m_DragWidth, m_DragHeight);
		for (GameObject* go : objs)
		{
			selectedGameObjects.push_back(go);
			Bounds* b = go->getComponent<Bounds>();
			if (b != nullptr)
			{
				b->isSelected = true;
			}
		}
	}
	else
	{
		// clear mouse pos when no drag is happening
		mousePos.clear();
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
	}
}

void LevelEditorControls::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	if (isEditing)
	{
		Sprite* sprite = this->gameObj->getComponent<Sprite>();
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->gameObj->transform->position.x,
			this->gameObj->transform->position.y, 0.0f));
		if (sprite != nullptr)
		{
			sprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
		}
		
	}
	else if (ML::isDragging() && ML::mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		/*if (!wasDragged)
		{
			mousePos.clear();
		}*/
		wasDragged = true;

		m_DragX = ML::getX();
		m_DragY = ML::getY();
		// to center
		mousePos.push_back(glm::vec2(m_DragX, m_DragY));

		m_DragWidth = ML::getX() - mousePos.at(0).x  ;
		m_DragHeight =  ML::getY() - mousePos.at(0).y ;

		// scale factors
		float scaleX = m_DragWidth;
		float scaleY = m_DragHeight;

		// we need width and height +ve
		if (m_DragWidth < 0)
		{
			m_DragWidth *= -1;
		}
		if (m_DragHeight < 0)
		{
			m_DragHeight *= -1;
		}

		// scale factor
		glm::vec2 scale(scaleX /10.0f, scaleY /10.0f);
		// origin at first mouse X and Y
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(mousePos.at(0).x, mousePos.at(0).y, 1.0f));
		// scale in drag w and h
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(scale, 1.0f));
		
		box.draw(shaderLine, ModelViewMatrix, ProjectionMatrix);
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

std::vector<GameObject*> LevelEditorControls::boxSelect(float x, float y, float w, float h)
{
	float x0 = x + Game::game->getCurrentScene()->camera->position.x;
	float y0 = y + Game::game->getCurrentScene()->camera->position.y;
	std::vector<GameObject*> objs;
	for (GameObject* go : Game::game->getCurrentScene()->getAllGameObjects())
	{
		Bounds* b = go->getComponent<Bounds>();
		if (b != nullptr)
		{
			// as our origin is stationary we need to subtract w or h to check if
			// object is within box select if user selects from the bottom right/left
			// and top right
			if(go->transform->position.x + b->getWidth() <= x0 + w &&
				go->transform->position.y + b->getHeight() <= y0 + h &&
				go->transform->position.x >= x0 - w &&
				go->transform->position.y >= y0 - h)
				{
					objs.push_back(go);
				}
		}
	}
	return objs;
}

Component* LevelEditorControls::copy() 
{
	return nullptr;
}

std::string LevelEditorControls::serialise(int tabSize)
{
	return "";
}