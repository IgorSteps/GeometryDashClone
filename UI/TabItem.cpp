#include "TabItem.h"

#include <iostream>
#include <Game.h>
#include <LevelEditorScene.h>
#include <LevelEditorControls.h>

TabItem::TabItem(int x, int y, int width, int height, Sprite* sp, Shader& sh, MainContainer* maincont)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
	m_TabSprite = sp;
	
	m_MainContainer = maincont;
	isSelected = false;
	shader = sh;
}

TabItem::~TabItem()
{
}


TabItem* TabItem::copy()
{
	/*MenuItem* mt  = new MenuItem(m_X, m_Y, m_Width, m_Height, (Sprite*)m_ButtonSprite->copy(), (Sprite*)m_HoveredSprite->copy(), shader);
	mt->m_MyImage = m_MyImage;

	std::cout << "Copy menu item \n";
	return mt;*/
	return nullptr;

}

void TabItem::update(float dt)
{
	if (ML::mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		// check mouse is within the bounds of the little rectangle
		if (!isSelected && ML::getX() > m_X && ML::getX() <= m_X + m_Width && ML::getY() > m_Y && ML::getY() <= m_Y + m_Height)
		{
			isSelected = true;
			m_MainContainer->setHotTab(this->gameObj);
		}
	}
}

void TabItem::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	// todo: make NON selected tabs half-transparent
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_X, m_Y, 1.0f));

	m_TabSprite->draw(shader, ModelViewMatrix, ProjectionMatrix);
}

std::string TabItem::serialise(int tabsize)
{
	return "";
}
