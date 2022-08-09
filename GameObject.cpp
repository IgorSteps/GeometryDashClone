#include "GameObject.h"
#include <iostream>

GameObject::GameObject(std::string name, Transform transform) {
	this->name = name;
	this->transform = transform;
	this->components = std::vector<Component*>(); 
}

GameObject::~GameObject() {};

void GameObject::update(float dt) {
	// testing - prints out game object name and position
	//std::cout << this->name << ", x-coord: " << this->transform.position.x << ", y-coord: " << this->transform.position.y << '\n';
	for (Component* c : this->components) {
		c->update(dt);
	}
}


//Component* GameObject::getComponent() {
//	for (auto &comp: this->components)
//	{
//		if(dynamic_cast<Component*>(comp)){
//			return dynamic_cast<Component*>(comp);
//		}
//	}
//	return NULL;
//}

void GameObject::addComponent(Component* c) {
	this->components.push_back(c);
}