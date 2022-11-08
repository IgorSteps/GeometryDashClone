#include "Scene.h"
#include <Component.h>
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

	for (Component* c : g->getAllComponents())
	{
		c->start();
	}
}

void Scene::removeGameObject(GameObject* g)
{
	gameObjectsToRemove.push_back(g);
}

std::vector<GameObject*> Scene::getAllGameObjects()
{
	return gameObjects;
}
