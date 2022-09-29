#include "LevelEditorScene.h"


#include <glm/ext/matrix_float4x4.hpp>
#include "SnapToGrid.h"
#include <KL.h>
#include <fstream>
#include <iostream>



LevelEditorScene::LevelEditorScene(std::string name) {
	Scene::SceneInit(name);
}

LevelEditorScene::~LevelEditorScene() {
	delete player;
	delete ground;
	delete layerOne;
	delete layerTwo;
	delete layerThree;
	delete grid;
	delete cameraContrl;
	delete mouseCursor;
	delete objects;
	delete editingButtons;

	delete playerComp;
	delete groundComp;
	delete groundSp;
}

void LevelEditorScene::init()
{
	int Width = Constants::SCREEN_WIDTH;
	int Height = Constants::SCREEN_HEIGHT;

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
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	/// AssetPool
	initAssetPool();
	editingButtons = new MainContainer(myShader);

	/// GRID
	grid = new Grid();

	/// CAMERA CONTROLS
	cameraContrl = new CameraControls();

	/// EDITING BUTTONS
	editingButtons->start();

	/// PLACING BLOCKS
	
	mouseCursor = new GameObject("Mouse cursor", new Transform(glm::vec2(0.0f)));
	mouseCursor->addComponent(new SnapToGrid(Constants::TILE_WIDTH, Constants::TILE_HEIGHT, myShader));


	/// PLAYER
	player = new GameObject("Player game obj", new Transform(glm::vec2(500.0f,350.0f)));

	float red[] = { 1.0f, 0.0f, 0.0f };
	float blue[] = { 0.0f, 1.0f, 0.0f };

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(player->transform->position.x, player->transform->position.y, 0.0f));
	//ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,1.0f));

	layerOne = AssetPool::getSpritesheet("assets/player/layerOne.png");
	layerTwo = AssetPool::getSpritesheet("assets/player/layerTwo.png");
	layerThree = AssetPool::getSpritesheet("assets/player/layerThree.png");

	int spNum = 0;
	playerComp = new Player(
		layerOne->sprites[spNum],
		layerTwo->sprites[spNum],
		layerThree->sprites[spNum],
		red,
		blue);

	player->addComponent(playerComp);

	layerOne->sprites[spNum]->SetHeight(42.0f);
	layerOne->sprites[spNum]->SetWidth(42.0f);

	layerOne->sprites[spNum]->initSubSprite(myShader);

	layerTwo->sprites[spNum]->SetHeight(42.0f);
	layerTwo->sprites[spNum]->SetWidth(42.0f);
	layerTwo->sprites[spNum]->initSubSprite(myShader);

	layerThree->sprites[spNum]->SetHeight(42.0f);
	layerThree->sprites[spNum]->SetWidth(42.0f);
	layerThree->sprites[spNum]->initSubSprite(myShader);

	/// GROUND
	ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, Constants::GROUND_Y)));
	groundSp = new Sprite("assets/grounds/ground01.png");
	groundComp = new Ground(groundSp, myShader);
	ground->addComponent(groundComp);

	// button sprite test, they are broken, remove later
	/*ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, 0.0f)));
	groundSp = new Sprite("assets/player/spaceship.png");
	groundComp = new Ground(groundSp, myShader);
	ground->addComponent(groundComp);*/

	addGameObject(player);
	addGameObject(ground);
}

void LevelEditorScene::initAssetPool()
{
	AssetPool::addSpritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/groundSprites.png", 42.0f, 42.0f, 2.0f, 6, 12, 264.0f, 88.0f);
	AssetPool::addSpritesheet("assets/ui/buttonSprites.png", 60.0f, 60.0f, 2.0f, 2, 2, 124.0f, 62.0f);
}


void LevelEditorScene::update(float dt)
{
	if (camera->position.y > Constants::CAMERA_OFFSET_GROUND_Y)
	{
		camera->position.y = Constants::CAMERA_OFFSET_GROUND_Y;
	}
	
	for (GameObject* g : gameObjects) {
		g->update(dt); 
	}
	
	cameraContrl->update(dt);
	grid->update(dt);
	editingButtons->update(dt);
	mouseCursor->update(dt);

	if (KL::isKeyPressed(GLFW_KEY_SPACE))
	{
		savetoFile("test");
	}
 }

void LevelEditorScene::savetoFile(std::string name)
{
	std::ofstream myfile("levels/" + name + ".json");
	
	if (myfile.is_open())
	{
		//test
		//myfile << "This is a line.\n";
		//myfile << "This is another line.\n";

		int i = 0;
		for (GameObject* g : gameObjects)
		{
			std::string str = g->serialise(0);

			if (str.compare("") != 0)
			{
				myfile << str;
				if (i < gameObjects.size() - 1)
				{
					myfile << ",\n";
				}
			}
			++i;
		}

		myfile.close(); // close IO stream
	}
	else 
	{
		std::cout << "Unable to open " << name << " file\n";
	}
}

void LevelEditorScene::draw()
{
	renderer->render(myShader, ViewMatrix, ProjectionMatrix);
	grid->draw(grid->shader, ModelViewMatrix, ProjectionMatrix);
	editingButtons->draw(myShader, ModelViewMatrix, ProjectionMatrix);
	mouseCursor->draw(myShader, ModelViewMatrix, ProjectionMatrix);
}

