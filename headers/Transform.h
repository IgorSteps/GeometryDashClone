#pragma once
#include <glm/ext/vector_float2.hpp>
#include <Serialise.h>
class Transform : public Serialise
{
public:
	Transform(glm::vec2 position);
	Transform();
	Transform(Transform* trans);
	Transform* copy();

	std::string serialise(int tabsize);
	static Transform* deserialise();

	glm::vec2 position;
	float rotateion;
	glm::vec2 scale; 
};

