#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "BoxBounds.h"
#include "AssetPool.h"
#include "Spritesheet.h"
#include "Player.h"
#include "Ground.h"
#include "Constants.h"
#include "Background.h"

#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>

class LevelScene : public Scene
{
public:
	LevelScene(std::string name);
	~LevelScene();
	static LevelScene* currentScene;
	GameObject* player;
	BoxBounds* playerBounds;
	void init();
	void initAssetPool();
	void update(float dt);
	void draw();
	void initBackgrounds(); 
	void importLevel(std::string filename);

	// Coordinate System Data
	glm::mat4 ViewMatrix;		// matrix for the modelling and viewing
	glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing
	glm::mat4 ProjectionMatrix; // matrix for the orthographic projection

	// Game Data
	Shader myShader;
	Shader noColor;
	Player* playerComp;
	GameObject* ground;
	Spritesheet* layerOne;
	Spritesheet* layerTwo;
	Spritesheet* layerThree;
	Transform* trans;
	AssetPool assetPool;
	Background* bg;
	Background* groundBg;
	GameObject* groundGo;
	GameObject* go;
};

