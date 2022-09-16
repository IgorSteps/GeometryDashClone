#include "Game.h"
#include "LevelEditorScene.h"
#include "LevelScene.h"
#include <iostream>


Game::Game( int width,  int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height), isInEditor(true)
{
	this->currentScene = nullptr;
	Game::game = this;
}

Game::~Game()
{
	delete this->currentScene;
}

Scene* Game::getCurrentScene() {
	return this->currentScene;
}

void Game::changeScene(int scene)
{
	switch (scene) {
	case 0:
		isInEditor = true;
		currentScene = new LevelEditorScene("Level Editor");
		break;
	case 1:
		isInEditor = false;
		currentScene = new LevelScene("Level");
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

Game* Game::game;