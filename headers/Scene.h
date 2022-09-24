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
	~Scene();

	void SceneInit(std::string name);
	void addGameObject(GameObject* g);

	virtual void init()=0;
	virtual void update(float dt)=0;
	virtual void draw()=0;

	std::string name;
	Camera* camera;
	std::vector<GameObject*> gameObjects;
	Renderer* renderer;
};