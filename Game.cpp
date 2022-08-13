#include "Game.h"
#include <glm/ext/matrix_float4x4.hpp>
#include "Shader.h"
#include "Sprite.h"
#include <iostream>
#include "GameObject.h"
#include "BoxBounds.h"
#include "AssetPool.h"

// Coordinate System Data
glm::mat4 ViewMatrix;		// matrix for the modelling and viewing
glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing
glm::mat4 ProjectionMatrix; // matrix for the orthographic projection

// Game Data
Shader myShader;
GameObject* testObj;
Transform trans = glm::vec2(0.0f);
AssetPool assetPool;


Game::Game( int width,  int height)
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	
}

Game::~Game()
{
	delete testObj;
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
	float red[3] = { 1.0f, 0.0f, 0.0f };
	

	

	testObj = new GameObject("Some game obj", trans);
	testObj->addComponent(new BoxBounds("BoxBounds"));
	testObj->addComponent(assetPool.getSprite("textures/background.png"));
	testObj->getComponent<Sprite>()->SetHeight(200.0f);
	testObj->getComponent<Sprite>()->SetWidth(200.0f);
	testObj->getComponent<Sprite>()->Init(myShader, red, 3.0f, 3.0f);
}

void Game::Update(float dt)
{
	//std::cout << testObj->getComponent<BoxBounds>()->name << '\n';
	testObj->update(dt);
}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
	testObj->draw(myShader, ViewMatrix, ProjectionMatrix);
}