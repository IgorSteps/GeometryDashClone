#include "Scene.h"

Scene::~Scene() {
	delete camera;
	delete renderer;
}

void Scene::SceneInit(std::string name) {
	this->camera = new Camera(glm::vec2(0.0f));
	this->renderer = new Renderer(this->camera);
	this->gameObjects = std::vector<GameObject*>();
	this->name = name;
}

void Scene::addGameObject(GameObject* g) {
	gameObjects.push_back(g);
	renderer->submit(g);
}