#include "Game.h"
#include <glm/ext/matrix_float4x4.hpp>
#include "Shader.h"
#include "Sprite.h"
#include <iostream>
#include "GameObject.h"
#include "BoxBounds.h"
#include "AssetPool.h"
#include "Spritesheet.h"
#include "Player.h"

// Coordinate System Data
glm::mat4 ViewMatrix;		// matrix for the modelling and viewing
glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing
glm::mat4 ProjectionMatrix; // matrix for the orthographic projection

// Game Data
Shader myShader;
GameObject* player;
Transform trans = glm::vec2(0.0f);
AssetPool assetPool;


Game::Game( int width,  int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	
}

Game::~Game()
{
	delete player;
}

void Game::Init()
{
	// this proj mat will place an object in the center
	ProjectionMatrix = glm::ortho(
		(static_cast<float>(-this->Width) / 2.0f),
		(static_cast<float>(this->Width) / 2.0f),
		static_cast<float>(-this->Height) / 2.0f,
		static_cast<float>(this->Height) / 2.0f,
		1.0f,
		-1.0f);

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	//Load the GLSL program 
	if (!myShader.load("Shader", "./glslfiles/basicTexture.vert", "./glslfiles/basicTexture.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	//some initial testing of rendering sprites
	float red[] = {255.0f, 0.0f, 0.0f};
	float blue[] = {0.0f, 255.0f, 0.0f };
	

	

	player = new GameObject("Some game obj", trans);
	
	Spritesheet* layerOne	= new Spritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	Spritesheet* layerTwo	= new Spritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	Spritesheet* layerThree = new Spritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	
	int spNum = 52;
	Player* playerComp = new Player(
		layerOne->sprites[spNum],
		layerTwo->sprites[spNum],
		layerThree->sprites[spNum],
		red,
		blue);

	player->addComponent(playerComp);
	layerOne->sprites[spNum]->initSubSprite(myShader);
	layerTwo->sprites[spNum]->initSubSprite(myShader);
	layerThree->sprites[spNum]->initSubSprite(myShader);
	//player->getComponent<Sprite>()->initSubSprite(myShader);


}

void Game::Update(float dt)
{
	//std::cout << testObj->getComponent<BoxBounds>()->name << '\n';
	player->update(dt);
}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
	player->draw(myShader, ViewMatrix, ProjectionMatrix);
}