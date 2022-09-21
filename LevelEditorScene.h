#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "BoxBounds.h"
#include "AssetPool.h"
#include "Spritesheet.h"
#include "Player.h"
#include "Ground.h"
#include "Rigidbody.h"
#include "Grid.h"
#include "CameraControls.h"

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene(std::string name);
	~LevelEditorScene();
 	GameObject* player;
	void init();
	void update(float dt);
	void draw();

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
	Sprite* groundSp;
	Ground* groundComp;
	Player* playerComp;
	Grid* grid;
	CameraControls* cameraContrl;
	Spritesheet* objects;
	GameObject* mouseCursor;
};

