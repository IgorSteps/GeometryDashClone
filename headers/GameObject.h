#pragma once
#include "Transform.h"
#include "glm\gtc\matrix_transform.hpp"
class Component;

#include <vector>
#include <string>
#include <memory>
#include "Shader.h"


class GameObject
{
public:
	GameObject(std::string name, Transform* transform);
	GameObject();
	~GameObject();

	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	GameObject* copy(Shader& sh);

	Transform* transform; //make a smart pointer?
	
	template <typename T> T* getComponent() 
	{
		for (auto& comp : this->components)
		{
			if (dynamic_cast<T*>(comp)) {
				return dynamic_cast<T*>(comp);
			}
		}
		return NULL;
	}

	template <typename T> void removeComponent() 
	{
		for (auto it = begin(components); it != end(components);) {
			it = components.erase(it);
		}
	}

	void addComponent(Component* c);
	std::vector<Component*> getAllComponents();
private:
	std::vector<Component*> components;
	std::string name;
};
