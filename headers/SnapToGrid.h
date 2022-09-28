#pragma once
#include "Sprite.h"
class SnapToGrid : public Component
{
public:
	SnapToGrid(int gridWidth, int gridHeight, Shader& sh);
	~SnapToGrid();
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	// copy() method to copy components
	Component* copy();
	// shader for initlising copied component
	Shader shader;
	// copied game object
	GameObject* object;

private:
	// when user presses it only registers one click
	float m_debounceTime, m_debounceLeft;
	int m_gridWidth, m_gridHeight;
};

