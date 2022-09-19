#pragma once
#include <glm/ext/vector_float2.hpp>
class Transform
{
public:
	Transform(glm::vec2 position);
	Transform();
	Transform(Transform& trans);
	glm::vec2 position;
	float rotateion;
	glm::vec2 scale; 
};

