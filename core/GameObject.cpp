#include "GameObject.h"
#include "Component.h"
#include <iostream>
#include "Sprite.h"

GameObject::GameObject(std::string name, Transform* transform) {
	this->name = name;
	this->transform = transform;
	this->components = std::vector<Component*>(); 
}

GameObject* GameObject::copy(Shader& sh)
{
	GameObject* newGameObj = new GameObject("Generated", transform->copy());

	for (Component* c : components) 
	{
		Component* copy = c->copy();
		if (copy != nullptr)
		{
			newGameObj->addComponent(copy);
			newGameObj->getComponent<Sprite>()->initSubSprite(sh);
		}
	}

	return newGameObj;
}

std::string GameObject::serialise(int tabSize)
{
	std::string stringBuilder;

	// Game Object
	stringBuilder.append(beginObjectProperty("GameObject", tabSize));

	// Transform
	stringBuilder.append(transform->serialise(tabSize + 1));
	stringBuilder.append(addEnding(true, true));

	// Name
	if (components.size() > 0)
	{
		stringBuilder.append(addStringProperty("Name", name, tabSize + 1, true, true));
		stringBuilder.append(beginObjectProperty("Components", tabSize + 1));
	}
	else
	{
		stringBuilder.append(addStringProperty("Name", name, tabSize + 1, true, false));
	}

	// Components
	int i = 0;
	for (Component* c : components)
	{
		std::string str = c->serialise(tabSize + 2);
		if (str.compare("") != 0)
		{
			stringBuilder.append(str);
			if (i != components.size() - 1)
			{ 
				stringBuilder.append(addEnding(true, true));
			}
			else 
			{
				stringBuilder.append(addEnding(true, false));
			}
		}
		++i;
	}

	if (components.size() > 0)
	{
		stringBuilder.append(closeObjectProperty(tabSize + 1));
	}

	stringBuilder.append(addEnding(true, false));
	stringBuilder.append(closeObjectProperty(tabSize));

	return stringBuilder;
}

GameObject::~GameObject() { 
};

void GameObject::update(float dt) {
	// testing - prints out game object name and position
	//std::cout << this->name << ", x-coord: " << this->transform.position.x << ", y-coord: " << this->transform.position.y << '\n';
	for (Component* c : this->components) {
		c->update(dt);
	}
}

void GameObject::addComponent(Component* c) {
	this->components.push_back(c);
	c->gameObj = this;
}

std::vector<Component*> GameObject::getAllComponents()
{
	return this->components;
}

void GameObject::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix) {
	for (Component* c : this->components) {
		c->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}