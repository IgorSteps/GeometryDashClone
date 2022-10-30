#pragma once
#include "Sprite.h"
#include <vector>
class LevelEditorControls : public Component
{
public:
	LevelEditorControls(int gridWidth, int gridHeight, Shader& sh);
	~LevelEditorControls();

	void updateSpritePosition();
	void copyGameObjectToScene();
	void addGameObjectToSelected(glm::vec2 pos);
	void clearSelectedObjectsAndAdd(glm::vec2 mousePos);
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	// copy() method to copy components
	Component* copy();
	std::string serialise(int tabSize);

	// shader for initlising copied component
	Shader shader;
	// copied game object
	GameObject* object;
	float m_WorldX, m_WorldY;

private:
	// when user presses it only registers one click
	float m_debounceTime, m_debounceLeft;
	int m_gridWidth, m_gridHeight;
	bool isEditing = false;
	std::vector<GameObject*> selectedGameObjects;
};

