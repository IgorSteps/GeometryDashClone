#pragma once
#include <string>
#include "Shader.h"
#include <glm/ext/matrix_float4x4.hpp>
#include "Camera.h"
#include "GameObject.h"
#include "Renderer.h"

class Scene
{
public:
	void SceneInit(std::string name) {
		this->camera = new Camera(glm::vec2(0.0f));
		this->renderer = new Renderer(this->camera);
		this->gameObjects = std::vector<GameObject*>();
		this->name = name;
	}

	~Scene() {
		delete camera;
		delete renderer;
	}

	void addGameObject(GameObject* g) {
		gameObjects.push_back(g);
		renderer->submit(g);
	}

	virtual void init()=0;
	virtual void update(float dt)=0;
	virtual void draw()=0;


	std::string name;
	Camera* camera;
	std::vector<GameObject*> gameObjects;
	Renderer* renderer;
};