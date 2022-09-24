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

void GameObject::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix) {
	for (Component* c : this->components) {
		c->draw(shader, ModelViewMatrix, ProjectionMatrix);
	}
}