#include "Constants.h"
#include "LevelEditorScene.h"
#include "GameObject.h"
#include "BoxBounds.h"
#include "AssetPool.h"
#include "Spritesheet.h"
#include "Player.h"
#include "Ground.h"
#include "Rigidbody.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>


// Coordinate System Data
glm::mat4 ViewMatrix;		// matrix for the modelling and viewing
glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing
glm::mat4 ProjectionMatrix; // matrix for the orthographic projection

// Game Data
Shader myShader;
GameObject* ground;
Spritesheet* layerOne;
Spritesheet* layerTwo;
Spritesheet* layerThree;
Transform* trans;
AssetPool assetPool;


LevelEditorScene::LevelEditorScene(std::string name) {
	Scene::SceneInit(name);
}

LevelEditorScene* LevelEditorScene::getScene() {
	if (LevelEditorScene::currentScene == nullptr) {
		LevelEditorScene::currentScene = new LevelEditorScene("Scene");
	}
	return LevelEditorScene::currentScene;
}



LevelEditorScene::~LevelEditorScene() {
	delete player;
	delete ground;
	delete layerOne;
	delete layerTwo;
	delete layerThree;
}

void LevelEditorScene::init()
{
	int Width = Constants::SCREEN_WIDTH;
	int Height = Constants::SCREEN_HEIGHT;
	// this proj mat will place an object in the center
	//ProjectionMatrix = glm::ortho(
	//	(static_cast<float>(-Width) / 2.0f),	//left
	//	(static_cast<float>(Width) / 2.0f),		//right
	//	static_cast<float>(-Height) / 2.0f,		//bottom
	//	static_cast<float>(Height) / 2.0f,		//top
	//	1.0f,
	//	-1.0f);
	ProjectionMatrix = glm::ortho(
		0.0f,
		(static_cast<float>(Constants::SCREEN_WIDTH)),
		(static_cast<float>(Constants::SCREEN_HEIGHT)),
		0.0f,
		-1.0f,
		1.0f);


	//Load the GLSL program 
	if (!myShader.load("Shader", "./glslfiles/basicTexture.vert", "./glslfiles/basicTexture.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	/// PLAYER
	player = new GameObject("Player game obj", new Transform(glm::vec2(500.0f,350.0f)));

	float red[] = { 255.0f, 0.0f, 0.0f };
	float blue[] = { 0.0f, 255.0f, 0.0f };

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(player->transform->position.x,
		player->transform->position.y, 0.0f));

	ModelViewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(500.0f,500.0f,1.0f));

	layerOne = new Spritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	layerTwo = new Spritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	layerThree = new Spritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);

	int spNum = 0;
	Player* playerComp = new Player(
		layerOne->sprites[spNum],
		layerTwo->sprites[spNum],
		layerThree->sprites[spNum],
		red,
		blue);

	player->addComponent(playerComp);
	player->addComponent(new Rigidbody(glm::vec2(30.0f, 0.0f)));
	player->addComponent(new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT));

	gameObjects.push_back(player);

	layerOne->sprites[spNum]->initSubSprite(myShader);
	layerTwo->sprites[spNum]->initSubSprite(myShader);
	layerThree->sprites[spNum]->initSubSprite(myShader);

	/// GROUND
	ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, Constants::GROUND_Y)));
	Sprite* sp = new Sprite("assets/grounds/ground01.png");
	Ground* groundComp = new Ground(sp, myShader);
	ground->addComponent(groundComp);
	gameObjects.push_back(ground);


	renderer->submit(player); 
	renderer->submit(ground); 
}

void LevelEditorScene::update(float dt)
{
	if (player->transform->position.x - camera->position.x > Constants::CAMERA_OFFSET_X)
	{
		camera->position.x = player->transform->position.x - Constants::CAMERA_OFFSET_X;
	}
	if (player->transform->position.y - camera->position.y > Constants::CAMERA_OFFSET_Y)
	{
		camera->position.y = player->transform->position.y - Constants::CAMERA_OFFSET_Y;
	}
	if (camera->position.y > Constants::CAMERA_OFFSET_GROUND_Y)
	{
		camera->position.y = Constants::CAMERA_OFFSET_GROUND_Y;
	}
	
	
	//player->transform->rotateion += 100.0f * dt;

	for (GameObject* g : gameObjects) {
		g->update(dt);
	}
	
 }

void LevelEditorScene::draw()
{
	renderer->render(myShader, ViewMatrix, ProjectionMatrix);
}

LevelEditorScene* LevelEditorScene::currentScene;
