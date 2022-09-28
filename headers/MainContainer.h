#pragma once
#include "Component.h"
#include "MenuItem.h"
#include <vector>

class MainContainer : public Component
{
public:
	MainContainer(Shader& sh);
	~MainContainer();

	void init(Shader& sh);
	void start();
	Component* copy();

	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs);

	std::vector<GameObject*> m_MenuItems;
	GameObject* obj;
	MenuItem* menuItem;
};

