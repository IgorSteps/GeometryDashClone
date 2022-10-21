#pragma once
#include "Component.h"
#include "MenuItem.h"
#include <vector>
#include <map>


class MainContainer : public Component
{
public:
	MainContainer();
	~MainContainer();

	void init();
	void start();
	Component* copy();
	std::string serialise(int tabsize);
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs);

	std::vector<GameObject*> m_MenuItems;
	std::vector<GameObject*> m_Tabs;
	std::map<GameObject*, std::vector<GameObject*>> m_TabMaps;
	Sprite* m_ContainerBg;
	GameObject* m_CurrentTab;
	GameObject* obj;
	MenuItem* menuItem;
	Shader shader;

private:
	void addTabObjects();
};

