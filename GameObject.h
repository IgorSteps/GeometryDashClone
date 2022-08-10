#pragma once
#include <vector>
#include <string>
#include "Component.h"
#include <memory>
#include "Transform.h"

class GameObject
{
public:
	GameObject(std::string name, Transform transform);
	~GameObject();
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Transform transform; //make a smart pointer?
	template <typename T>
	T* getComponent() {
		for (auto& comp : this->components)
		{
			if (dynamic_cast<T*>(comp)) {
				return dynamic_cast<T*>(comp);
			}
		}
		return NULL;
	}
	void addComponent(Component* c);
private:
	std::vector<Component*> components;
	std::string name;
};

