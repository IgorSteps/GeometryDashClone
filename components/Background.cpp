#include "Background.h"
#include <Game.h>
#include <Constants.h>
#include <AssetPool.h>
#include <iostream>
Background::Background(std::string file, std::vector<GameObject*>* backgrounds, Ground* gr, bool followingGround, float width, float height, const float color[3])
{
	sp = AssetPool::getSprite(file);
	sp->setColour(color);
	sp->SetWidth(width);
	sp->SetHeight(height);

	// in this case same as sprite width/height
	m_Width = width;
	m_Height = height;
	m_Backgrounds = backgrounds;
	m_Ground = gr;

	if (followingGround)
	{
		m_Speed = Constants::PLAYER_SPEED - 35;
	}

	m_FollowGround = followingGround;

}

void Background::update(float dt)
{
	++m_Timestamp;

	this->gameObj->transform->position.x -= dt * m_Speed;
	this->gameObj->transform->position.x = (float) floor(this->gameObj->transform->position.x);

	if (this->gameObj->transform->position.x < -m_Width)
	{
		float maxX = 0;
		int timestamp = 0;
		for (int i=0; i < 7; ++i)
		{
			GameObject* go = m_Backgrounds->at(i);
			if (go->transform->position.x > maxX)
			{
				maxX = go->transform->position.x;
				timestamp = go->getComponent<Background>()->m_Timestamp;
			}
		}

		if (m_Timestamp == timestamp)
		{
			this->gameObj->transform->position.x = m_Width + maxX;
		}
		else
		{
			this->gameObj->transform->position.x = (float)floor((maxX + m_Width) - (dt * m_Speed));
		}
	}

	if (m_FollowGround)
	{
		this->gameObj->transform->position.y = m_Ground->gameObj->transform->position.y;
	}
}

void Background::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	if (m_FollowGround)
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->gameObj->transform->position.x,
			this->gameObj->transform->position.y - Game::game->getCurrentScene()->camera->position.y, 1.0f));

		sp->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
	else
	{
		int height = std::min((int)m_Ground->gameObj->transform->position.y - (int)Game::game->getCurrentScene()->camera->position.y, Constants::SCREEN_HEIGHT);

		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(this->gameObj->transform->position.x, this->gameObj->transform->position.y, 1.0f));

		sp->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}

std::string Background::serialise(int tabSize)
{
	return std::string();
}

Component* Background::copy()
{
	return nullptr;
}
