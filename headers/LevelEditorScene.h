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
#include <MainContainer.h>
#include <Background.h>

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene(std::string name);
	~LevelEditorScene();
 	GameObject* player;
	void init();
	void initAssetPool();
	void initBackgrounds();
	void update(float dt);
	void draw();

	// Coordinate System Data
	glm::mat4 ViewMatrix;		// matrix for the modelling and viewing
	glm::mat4 ModelViewMatrix;  // matrix for the modelling and viewing
	glm::mat4 ProjectionMatrix; // matrix for the orthographic projection

	// Game Data
	Shader myShader;
	Shader noColorShader;
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
	MainContainer* editingButtons;

private:
	void savetoFile(std::string);
	void importLevel(std::string);
	Background* bg;
	Background* groundBg;
	GameObject* groundGo;
	GameObject* go;
};

