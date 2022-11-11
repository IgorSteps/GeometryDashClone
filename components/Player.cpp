#include "Player.h"
#include "GameObject.h"
#include <iostream>
#include <KL.h>
#include <Rigidbody.h>
#include <Game.h>
#include <AssetPool.h>

Player::Player(Sprite* layerOne, Sprite* layerTwo, Sprite* layerThree,
	Sprite* spShip, float colourOne[], float colourTwo[], Shader& sh)
{
	noColor = sh;
	spaceship = spShip;
	m_State = NORMAL;
	
	spaceship->SetHeight(42.0f);
	spaceship->SetWidth(42.0f);	


	this->layerOne = layerOne;
	this->layerTwo = layerTwo;
	this->layerThree = layerThree;
	this->dib=ImageLoading::loadImageTwo("assets/player/layerOne.png");
	RGBQUAD colour;

	for (int y = 0; y < layerOne->getFileWidth(); y++)
	{
		for (int x = 0; x < layerOne->getFileHeight(); x++)
		{
			FreeImage_GetPixelColor(this->dib, x, y, &colour);
			if (colour.rgbRed > this->threshold && colour.rgbBlue > this->threshold && colour.rgbGreen > this->threshold)
			{
				layerOne->colour[0] = colourOne[0];
				layerOne->colour[1] = colourOne[1];
				layerOne->colour[2] = colourOne[2];
			}
			
		}
	}

	
	this->dib = ImageLoading::loadImageTwo("assets/player/layerTwo.png");
	for (int y = 0; y < layerTwo->getFileWidth(); y++)
	{
		for (int x = 0; x < layerTwo->getFileHeight(); x++)
		{
			FreeImage_GetPixelColor(this->dib, x, y, &colour);
			if (colour.rgbRed > this->threshold && colour.rgbBlue > this->threshold && colour.rgbGreen > this->threshold)
			{
				layerTwo->colour[0] = colourTwo[0];
				layerTwo->colour[1] = colourTwo[1];
				layerTwo->colour[2] = colourTwo[2];
			}

		}
	}
	
}


void Player::update(float dt)
{
	if (onGround && KL::isKeyPressed(GLFW_KEY_SPACE))
	{
		addJumpForce(); 
		onGround = false;
	}
	// debugging info of player's y coord
	//std::cout << "Player y: " << this->gameObj->transform->position.y << '\n';

	if (!onGround)
	{
		gameObj->transform->rotateion += 200.0f * dt;
	}
	else 
	{
		// snap rotation and set rotation between 0 to 360 degrees
		gameObj->transform->rotateion = (int)gameObj->transform->rotateion % 360;

		if (gameObj->transform->rotateion > 180 && gameObj->transform->rotateion < 360)
		{
			gameObj->transform->rotateion = 0;
		}
		else if (gameObj->transform->rotateion > 0 && gameObj->transform->rotateion < 180)
		{
			gameObj->transform->rotateion = 0;
		}
	}

	
}

void Player::addJumpForce()
{
	gameObj->getComponent<Rigidbody>()->Velocity.y = -650.0f;
}

void Player::die()
{
	gameObj->transform->position.x = 500;
	gameObj->transform->position.y = 350;
	gameObj->getComponent<Rigidbody>()->Velocity.y = 0;
	gameObj->transform->rotateion = 0.0f;
	Game::game->getCurrentScene()->camera->position.x = 0;
}

void Player::draw(Shader& shader, glm::mat4& Model, glm::mat4& Proj) {
	// translate
	Model = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj->transform->position.x,
			gameObj->transform->position.y, 1.0f));
	// rotate
	Model = glm::rotate(Model, glm::radians(gameObj->transform->rotateion),
		glm::vec3(0.0f, 0.0f, 1.0f));
	// scale
	Model = glm::scale(Model, glm::vec3(gameObj->transform->scale, 1.0f));

	if(m_State == NORMAL)
	{
		layerOne->draw(shader, Model, Proj);
		layerTwo->draw(shader, Model, Proj);
		layerThree->draw(shader, Model, Proj);
	}
	else
	{
		spaceship->draw(noColor, Model, Proj);
	}
}

Component* Player::copy()
{
	return nullptr;
}

std::string Player::serialise(int tabSize)
{
	return "";
}
