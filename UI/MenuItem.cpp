#include "MenuItem.h"

#include <iostream>
#include <Game.h>
#include <LevelEditorScene.h>
#include <LevelEditorControls.h>
#include <KL.h>

MenuItem::MenuItem(int x, int y, int width, int height, Sprite* buttonSprite, Sprite* hoveredSprite, Shader &sh, MainContainer* maincont)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
	m_ButtonSprite = buttonSprite;
	m_HoveredSprite = hoveredSprite; 
	m_MainContainer = maincont;
	isSelected = false;
	shader = sh;
}

MenuItem::~MenuItem()
{
}

void MenuItem::start()
{
	m_MyImage = gameObj->getComponent<Sprite>();
}

MenuItem* MenuItem::copy()
{
	/*MenuItem* mt  = new MenuItem(m_X, m_Y, m_Width, m_Height, (Sprite*)m_ButtonSprite->copy(), (Sprite*)m_HoveredSprite->copy(), shader);
	mt->m_MyImage = m_MyImage;

	std::cout << "Copy menu item \n";
	return mt;*/
	return nullptr;

}

void MenuItem::update(float dt)  
{
	if (ML::mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) 
	{
		// check mouse is within the bounds of the little rectangle
		if (!isSelected && ML::getX() > m_X && ML::getX() <= m_X + m_Width && ML::getY() > m_Y && ML::getY() <= m_Y + m_Height)
		{
			GameObject* obj = gameObj->copy(shader);
			obj->removeComponent<MenuItem>(); 

			LevelEditorScene* scene = static_cast<LevelEditorScene*>(Game::game->getCurrentScene());
			LevelEditorControls* snapToGrid = scene->mouseCursor->getComponent<LevelEditorControls>();

			obj->addComponent(snapToGrid);
			scene->mouseCursor = obj;

			isSelected = true;
			m_MainContainer->setHotButton(this->gameObj);
		}
	}
	if (KL::isKeyPressed(GLFW_KEY_ESCAPE))
	{
		isSelected = false;
	}
}

void MenuItem::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_X, m_Y, 1.0f));

	m_ButtonSprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
	m_MyImage->draw(shader, ModelViewMatrix, ProjectionMatrix);

	if (isSelected)
	{
		m_HoveredSprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}

std::string MenuItem::serialise(int tabsize)
{
	return "";
}
