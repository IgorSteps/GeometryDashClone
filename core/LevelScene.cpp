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

	float red[] = { 255.0f, 0.0f, 0.0f };
	float blue[] = { 0.0f, 255.0f, 0.0f };

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
	player->addComponent(new Rigidbody(glm::vec2(395.0f, 0.0f)));
	player->addComponent(new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT));
	playerBounds = new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT);
	player->addComponent(playerBounds);
	// init player sprites
	layerOne->sprites[spNum]->initSubSprite(myShader);
	layerTwo->sprites[spNum]->initSubSprite(myShader);
	layerThree->sprites[spNum]->initSubSprite(myShader);

	/// GROUND
	ground = new GameObject("Ground game object", new Transform(glm::vec2(0.0f, Constants::GROUND_Y)));
	Sprite* sp = new Sprite("assets/grounds/ground01.png");
	Ground* groundComp = new Ground(sp, myShader);
	ground->addComponent(groundComp);


	addGameObject(player);
	addGameObject(ground);

	importLevel("test");
}

void LevelScene::initAssetPool()
{
	AssetPool::addSpritesheet("assets/player/layerOne.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerTwo.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/player/layerThree.png", 42, 42, 2, 13, 13 * 5, 572.0f, 220.0f);
	AssetPool::addSpritesheet("assets/groundSprites.png", 42.0f, 42.0f, 2.0f, 6, 12, 264.0f, 88.0f);
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

	for (auto& g : gameObjects) {
		g->update(dt);

		Bounds* b = g->getComponent<Bounds>();
		if (g != player && b != nullptr)
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
