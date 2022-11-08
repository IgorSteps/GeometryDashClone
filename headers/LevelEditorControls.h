#pragma once
#include "Sprite.h"
#include <vector>
#include "Line.h"
enum Direction {
	UP, DOWN, LEFT, RIGHT
};
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
	void escapeKeyPressed();
	void clearSelected();
	void moveObjects(Direction direction, float scale);
	void duplicate();
	void rotate(float d);
	std::vector<GameObject*> boxSelect(float x, float y, float w, float h);
	// copy() method to copy components
	Component* copy();
	std::string serialise(int tabSize);

	// shader for initlising copied component
	Shader shader;
	Shader shaderLine;
	// copied game object
	GameObject* object;
	float m_WorldX, m_WorldY;

private:
	// when user presses it only registers one click
	float m_debounceTime, m_debounceLeft;
	float m_debounceKey, m_debounceKeyLeft;
	std::vector<glm::vec2> mousePos;
	int m_gridWidth, m_gridHeight;

	bool isEditing = false;
	bool shiftPressed = false;
	
	std::vector<GameObject*> selectedGameObjects;
	
	// box select
	bool wasDragged = false;
	Line box;
	float m_DragY, m_DragX, m_DragWidth, m_DragHeight;
};

