#include "CameraControls.h"
#include "ML.h"
#include "Game.h"
#include <iostream>


CameraControls::CameraControls() 
{
	m_prevMx = 0.0f;
	m_prevMy = 0.0f;
}

CameraControls::CameraControls(CameraControls& cc)
{
	m_prevMx = cc.m_prevMx;
	m_prevMy = cc.m_prevMy;
}

void CameraControls::update(float dt) 
{
	if (ML::mouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		float dx = ML::getX() + ML::getDx() - m_prevMx;
		float dy = ML::getY() + ML::getDy() - m_prevMy;
		
		Game::game->getCurrentScene()->camera->position.x -= dx;
		Game::game->getCurrentScene()->camera->position.y -= dy;
		//test
		//std::cout << "camera controls event fired\n";
	}

	m_prevMx = ML::getX() + ML::getDx();
	m_prevMy = ML::getY() + ML::getDy();
}

Component* CameraControls::copy()
{
	return nullptr;
}