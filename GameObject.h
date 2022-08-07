#pragma once
#include <vector>
#include <string>
#include <glm/ext/vector_float2.hpp>
#include "Component.h"
#include <memory>
#include "Transform.h"
class GameObject
{
public:
	GameObject(std::string name, Transform& transform);
	~GameObject();
	void update(float dt);
	Transform transform; //make a smart pointer?

private:
	std::vector<std::unique_ptr<Component>> components;
	std::string name;
};

