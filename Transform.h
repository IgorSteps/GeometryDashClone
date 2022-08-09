#pragma once
#include <glm/ext/vector_float2.hpp>
class Transform
{
public:
	Transform(glm::vec2 position);
	Transform();
	glm::vec2 position;
};

