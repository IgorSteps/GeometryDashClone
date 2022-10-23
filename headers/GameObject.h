#pragma once
#include "Transform.h"
#include "glm\gtc\matrix_transform.hpp"
class Component;

#include <vector>
#include <memory>
#include "Shader.h"
#include "Serialise.h"


class GameObject : public Serialise
{
public:
	GameObject(std::string name, Transform* transform);
	GameObject();
	~GameObject();

	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	GameObject* copy(Shader& sh);
	std::string serialise(int tabSize);
	static GameObject* deserialise();
	void setNonserialisable();
	void setUi(bool var);
	Transform* transform; //make a smart pointer?
	GameObject* newGameObj; // copy
	static GameObject* go; // deserialised
	static Transform* deserialisedTransform;


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
		components.erase(std::remove_if(components.begin(), components.end(),
			[&](Component* c) { return dynamic_cast<T*>(c); }), components.end());
	}

	void addComponent(Component* c);
	std::vector<Component*> getAllComponents();

	bool isUi = false;
	std::string name;
private:
	std::vector<Component*> components;
	
	bool serialisable;
};

