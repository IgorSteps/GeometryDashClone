#include "LevelEditorScene.h"


#include <glm/ext/matrix_float4x4.hpp>
#include "SnapToGrid.h"

#include <KL.h>
#include <fstream>
#include <iostream>
#include <Parser.h>
#include <Game.h>



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

	delete bg;
	delete groundBg;
	delete go;
	delete groundGo;
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
	if (!myShader.load("Color Shader", "./glslfiles/basicTexture.vert", "./glslfiles/basicTexture.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	/// AssetPool
	initAssetPool();
	initBackgrounds();
	editingButtons = new MainContainer();

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

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(player->transform->position.x, player->transform->position.y, 1.0f));
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

	layerOne->sprites[spNum]->initSubSprite(myShader);
	layerTwo->sprites[spNum]->initSubSprite(myShader);
	layerThree->sprites[spNum]->initSubSprite(myShader);

	/// GROUND
	

	
	player->setNonserialisable();
	addGameObject(player);
	
}

void LevelEditorScene::initAssetPool()
{
	AssetPool::addSpritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/groundSprites.png", 42.0f, 42.0f, 2.0f, 6, 12, 264.0f, 88.0f);
	AssetPool::addSpritesheet("assets/ui/buttonSprites.png", 60.0f, 60.0f, 2.0f, 2, 2, 124.0f, 62.0f);
	AssetPool::addSpritesheet("assets/ui/tabs.png", Constants::TAB_WIDTH, Constants::TAB_HEIGHT, 2.0f, 6, 6, 462.0f, 40.0f);
	AssetPool::addSpritesheet("assets/spikes.png", 42.0f, 42.0f, 2.0f, 6, 4, 174.0f, 44.0f);
	AssetPool::addSpritesheet("assets/bigSprites.png", 84.0f, 84.0f, 2.0f, 2, 2, 172.0f, 86.0f);
	AssetPool::addSpritesheet("assets/smallBlocks.png", 42.0f, 42.0f, 2.0f, 6, 4, 264.0f, 44.0f);
	AssetPool::addSpritesheet("assets/portal.png", 44.0f, 85.0f, 2.0f, 2, 2 , 92.0f, 87.0f);
}

void LevelEditorScene::initBackgrounds()
{
	ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, Constants::GROUND_Y)));
	ground->addComponent(new Ground());
	ground->setNonserialisable();
	addGameObject(ground);

	int numOfBackgrounds = 7;

	// todo: delete em?
	std::vector<GameObject*>* backgrounds = new std::vector<GameObject*>;
	std::vector<GameObject*>* groundBgs = new std::vector<GameObject*>;

	for (int i = 0; i < numOfBackgrounds; ++i)
	{
		// Backgroundss
		bg = new Background("assets/backgrounds/bg01.png", nullptr, ground->getComponent<Ground>(), false, 512.0f, 512.0f, Constants::BG_COLOUR);
		bg->sp->initSprite(myShader);
		float x = i * bg->sp->getWidth();
		float y = 0;

		go = new GameObject("Background " + std::to_string(i), new Transform(glm::vec2(x, y)));
		go->setUi(true);
		go->setColor(true);
		go->setNonserialisable();
		go->addComponent(bg);
		backgrounds->push_back(go);

		// Ground
		groundBg = new Background("assets/grounds/ground01.png", nullptr, ground->getComponent<Ground>(), true, 256.0f, 256.0f, Constants::GROUND_COLOUR);
		groundBg->sp->initSprite(myShader);
		x = i * groundBg->sp->getWidth();
		y = ground->transform->position.y;

		groundGo = new GameObject("GroundBackground " + std::to_string(i), new Transform(glm::vec2(x, y)));
		groundGo->setUi(true);
		groundGo->setColor(true);
		groundGo->setNonserialisable();
		groundGo->addComponent(groundBg);
		groundBgs->push_back(groundGo);

		// Add to renderer
		addGameObject(go);
		addGameObject(groundGo);
	}
}

void LevelEditorScene::update(float dt)
{
	if (camera->position.y > Constants::CAMERA_OFFSET_GROUND_Y + 70)
	{
		camera->position.y = Constants::CAMERA_OFFSET_GROUND_Y + 70;
	}
	
	for (GameObject* g : gameObjects) {
		g->update(dt); 
	}
	
	cameraContrl->update(dt);
	grid->update(dt);
	editingButtons->update(dt);
	mouseCursor->update(dt);

	if (KL::isKeyPressed(GLFW_KEY_1))
	{
		savetoFile("test");
	}
	else if (KL::isKeyPressed(GLFW_KEY_2))
	{
		importLevel("test");
	}
	else if (KL::isKeyPressed(GLFW_KEY_3))
	{
		Game::game->changeScene(1);
	}
 }

void LevelEditorScene::importLevel(std::string filename)
{
	Parser::openFile(filename);

	GameObject* go = Parser::parseGameObject();

	while (go != nullptr) {
		addGameObject(go);
		go->getComponent<Sprite>()->initSubSprite(myShader);
		go = Parser::parseGameObject();
		
		std::cout << "magic inside\n";
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

