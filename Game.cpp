#include "Game.h"
#include "LevelEditorScene.h"
#include <iostream>


Game::Game( int width,  int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	this->currentScene = nullptr;
}

Game::~Game()
{
	delete this->currentScene;
}

void Game::changeScene(int scene)
{
	switch (scene) {
	case 0:
		currentScene = LevelEditorScene::getScene();
		break;
	default:
		std::cout << "Don't know which scene" << '\n';
		this->currentScene = nullptr;
		break;
	}
}

void Game::Init()
{
	changeScene(0);
	this->currentScene->init();
}

void Game::Update(float dt)
{
	this->currentScene->update(dt);
}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
	this->currentScene->draw();
}