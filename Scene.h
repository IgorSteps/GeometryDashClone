#pragma once
#include <string>
#include "Shader.h"
#include <glm/ext/matrix_float4x4.hpp>
class Scene
{
public:
	std::string name;

	void SceneInit(std::string name) {
		this->name = name;
	}

	virtual void init()=0;
	virtual void update(float dt)=0;
	virtual void draw()=0;
};