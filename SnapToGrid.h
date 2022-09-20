#pragma once
#include "Sprite.h"
class SnapToGrid : public Component
{
public:
	SnapToGrid(int gridWidth, int gridHeight);
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Component* copy();
	Shader shader;

private:
	// when user presses it only registers one click
	float m_debounceTime, m_debounceLeft;
	int m_gridWidth, m_gridHeight;
};

