#include "Renderer.h"

Renderer::Renderer(Camera* camera)
{
	this->camera = camera;
	this->gameObjects = std::vector < GameObject*>();
}

void Renderer::submit(GameObject* gameObj)
{
	this->gameObjects.push_back(gameObj);
}

void Renderer::render(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	for (GameObject* g : gameObjects) {
		Transform oldTransform = Transform(g->transform.position);
		oldTransform.rotateion = g->transform.rotateion;
		oldTransform.scale = g->transform.scale;

		g->transform.position = glm::vec2(g->transform.position.x - camera->position.x,
			g->transform.position.y - camera->position.y);

		g->draw(shader, ModelViewMatrix, ProjectionMatrix);
		g->transform = oldTransform;
	}
}
