#pragma once

#include <Sprite.h>
#include <ML.h>
#include <GameObject.h>

class MenuItem : public Component
{
public:
	MenuItem(int x, int y, int width, int height, Sprite* buttonSprite, Sprite* hoveredSprite, Shader& sh);
	~MenuItem();
	void start();
	MenuItem* copy();
	std::string serialise(int tabsize);

	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs);
	bool isSelected;

	int m_X, m_Y, m_Width, m_Height;
	Sprite* m_ButtonSprite;
	Sprite* m_HoveredSprite;
	Sprite* m_MyImage;
	Shader shader;
};

