#include "Renderer.h"

Renderer::Renderer(Camera* camera)
{
	this->camera = camera;
	this->gameObjects = std::vector<GameObject*>();
	this->oldTransform = nullptr;
}

Renderer::~Renderer()
{
	delete oldTransform;
}

void Renderer::submit(GameObject* gameObj)
{
	this->gameObjects.push_back(gameObj);
}

void Renderer::render(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	for (auto& g : gameObjects) {
		oldTransform = new Transform(g->transform->position);
		oldTransform->rotateion = g->transform->rotateion;
		oldTransform->scale = g->transform->scale;

		g->transform->position = glm::vec2(g->transform->position.x - camera->position.x,
			g->transform->position.y - camera->position.y);

		// pass game object position to the model view matrix
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(g->transform->position.x, g->transform->position.y, 1.0f));

		g->draw(shader, ModelViewMatrix, ProjectionMatrix);
		g->transform = oldTransform;
	}
}
