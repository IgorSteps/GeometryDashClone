#pragma once
#include "Camera.h"
#include "GameObject.h"
class Renderer
{
public:
	Renderer(Camera* camera);
	~Renderer();
	void submit(GameObject* gameObj);
	void render(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	
	std::vector<GameObject*> gameObjects;
	Camera* camera;
	Transform* oldTransform;
	Shader sh;
};

