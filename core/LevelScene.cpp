#include "LevelScene.h"

LevelScene::LevelScene(std::string name) {
	Scene::SceneInit(name);
}

LevelScene::~LevelScene() {
	delete player;
	delete ground;
	delete layerOne;
	delete layerTwo;
	delete layerThree;
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

	/// PLAYER
	player = new GameObject("Player game obj", new Transform(glm::vec2(500.0f, 350.0f)));

	float red[] = { 255.0f, 0.0f, 0.0f };
	float blue[] = { 0.0f, 255.0f, 0.0f };

	ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(player->transform->position.x,
		player->transform->position.y, 0.0f));

	ModelViewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(500.0f, 500.0f, 1.0f));

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
	player->addComponent(new Rigidbody(glm::vec2(395.0f, 0.0f)));
	player->addComponent(new BoxBounds(Constants::PLAYER_WIDTH, Constants::PLAYER_HEIGHT));

	 
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
	}

}

void LevelScene::draw()
{
	renderer->render(myShader, ViewMatrix, ProjectionMatrix);
}

LevelScene* LevelScene::currentScene;
