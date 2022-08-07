#include "GameObject.h"
#include <iostream>

GameObject::GameObject(std::string name, Transform& transform) {
	this->name = name;
	this->transform = transform;
	this->components.push_back(nullptr);
	//this->components = new std::vector<std::unique_ptr<Component>>; //why doesn't this work???
}

GameObject::~GameObject() {};

void GameObject::update(float dt) {
	// testing - prints out game object name and position
	std::cout << this->name << ", x-coord: " << this->transform.position.x << ", y-coord: " << this->transform.position.y << '\n';
}