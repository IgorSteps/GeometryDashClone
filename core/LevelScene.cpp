#include "LevelScene.h"
#include <Parser.h>
#include "Rigidbody.h"


LevelScene::LevelScene(std::string name) {
	Scene::SceneInit(name);
}

LevelScene::~LevelScene() {
	delete player;
	delete ground;
	delete layerOne;
	delete layerTwo;
	delete layerThree;
	delete playerBounds;
	delete bg;
	delete groundBg;
	delete go;
	delete groundGo;
}

void LevelScene::init()
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
	/// Asset Pool
	initAssetPool();

	/// PLAYER
	player = new GameObject("Player game obj", new Transform(glm::vec2(500.0f, 350.0f)));

	float red[] = { 1.0f, 0.0f, 0.0f };
	float blue[] = { 0.0f, 1.0f, 0.0f };

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(player->transform->position.x,
		player->transform->position.y, 0.0f));

	//ModelViewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(500.0f, 500.0f, 1.0f));

	layerOne = AssetPool::getSpritesheet("assets/player/layerOne.png");
	layerTwo = AssetPool::getSpritesheet("assets/player/layerTwo.png");
	layerThree = AssetPool::getSpritesheet("assets/player/layerThree.png");

	int spNum = 0;
	Player* playerComp = new Player(
		layerOne->sprites[spNum],
		layerTwo->sprites[spNum],
		layerThree->sprites[spNum],
		red,
		blue);

	player->addComponent(playerComp);
	player->addComponent(new Rigidbody(glm::vec2(Constants::PLAYER_SPEED, 0.0f)));
	player->addComponent(new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT));
	playerBounds = new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	player->addComponent(playerBounds);
	// init player sprites
	layerOne->sprites[spNum]->initSubSprite(myShader);
	layerTwo->sprites[spNum]->initSubSprite(myShader);
	layerThree->sprites[spNum]->initSubSprite(myShader);

	/// GROUND


	renderer->submit(player);
	

	initBackgrounds();

	importLevel("test");
}

void LevelScene::initAssetPool()
{
	AssetPool::addSpritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/groundSprites.png", 42.0f, 42.0f, 2.0f, 6, 12, 264.0f, 88.0f);
}

void LevelScene::initBackgrounds()
{
	ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, Constants::GROUND_Y)));
	ground->addComponent(new Ground());
	addGameObject(ground);

	int numOfBackgrounds = 7;

	// todo: delete em?
	std::vector<GameObject*>* backgrounds = new std::vector<GameObject*>;
	std::vector<GameObject*>* groundBgs = new std::vector<GameObject*>;
	
	for (int i = 0; i < numOfBackgrounds; ++i)
	{
		// Backgrounds
		bg= new Background("assets/backgrounds/bg01.png", backgrounds, ground->getComponent<Ground>(), false, 512.0f, 512.0f, Constants::BG_COLOUR); 
		bg->sp->initSprite(myShader);
		float x = i * bg->sp->getWidth();
		float y = 0;

		go = new GameObject("Background " + std::to_string(i), new Transform(glm::vec2(x, y)));
		go->setUi(true);
		go->addComponent(bg);
		backgrounds->push_back(go);

		// Ground
		groundBg = new Background("assets/grounds/ground01.png", groundBgs, ground->getComponent<Ground>(), true, 256.0f, 256.0f, Constants::GROUND_COLOUR);
		groundBg->sp->initSprite(myShader);
		x = i * groundBg->sp->getWidth();
		y = bg->sp->getHeight();

		groundGo = new GameObject("GroundBackground " + std::to_string(i), new Transform(glm::vec2(x, y)));
		groundGo->setUi(true);
		groundGo->addComponent(groundBg);
		groundBgs->push_back(groundGo);

		// Add to renderer
		addGameObject(go);
		addGameObject(groundGo);
	}
}

void LevelScene::update(float dt)
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
	player->update(dt);
	player->getComponent<Player>()->onGround = false;
	for (auto& g : gameObjects) 
	{
		g->update(dt);

		Bounds* b = g->getComponent<Bounds>();
		if (b != nullptr)
		{
			if (Bounds::checkCollison(*playerBounds, *b))
			{
				Bounds::resolveCollison(b, *player);
			}
		}
	}
}

void LevelScene::importLevel(std::string filename)
{
	Parser::openFile(filename);

	GameObject* go = Parser::parseGameObject();

	while (go != nullptr) {
		addGameObject(go);
		go->getComponent<Sprite>()->initSubSprite(myShader);
		go = Parser::parseGameObject();
	}

}

void LevelScene::draw()
{
	renderer->render(myShader, ViewMatrix, ProjectionMatrix);
}

LevelScene* LevelScene::currentScene;
