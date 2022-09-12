#pragma once
#include <glm/ext/vector_float2.hpp>

class Camera
{
public:
	glm::vec2 position;

	Camera(glm::vec2 position) {
		this->position = position;
	};
	Camera(){};
};

