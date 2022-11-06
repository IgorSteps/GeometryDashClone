#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Camera* camera)
{
	this->camera = camera;
	this->gameObjects = std::vector<GameObject*>();
	this->oldTransform = nullptr;

	if (!sh.load("No Color Shader", "./glslfiles/noColorVert.vert", "./glslfiles/noColorFrag.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}
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
		if (g->isUi)
		{
			ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(g->transform->position.x,
				g->transform->position.y, 1.0f));
			ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(g->transform->rotateion),
				glm::vec3(0.0f, 0.0f, 1.0f));
			if (g->isColor)
			{
				g->draw(shader, ModelViewMatrix, ProjectionMatrix);
			}
			else
			{
				g->draw(sh, ModelViewMatrix, ProjectionMatrix);
			}
		}
		else
		{
			oldTransform = new Transform(g->transform->position);
			oldTransform->rotateion = g->transform->rotateion;
			oldTransform->scale = g->transform->scale;

			g->transform->position = glm::vec2(g->transform->position.x - camera->position.x,
				g->transform->position.y - camera->position.y);

			// pass game object position to the model view matrix
			ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(g->transform->position.x, g->transform->position.y, 1.0f));
			ModelViewMatrix = glm::rotate(ModelViewMatrix, glm::radians(g->transform->rotateion),
				glm::vec3(0.0f, 0.0f, 1.0f));
			g->draw(shader, ModelViewMatrix, ProjectionMatrix);
			g->transform = oldTransform;
		}
	}
}
