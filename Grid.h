#pragma once

#include "Camera.h"
#include "Line.h"

class Grid : public Component
{
public:
	Grid();
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);

	Camera* camera;
	int m_gridWidth, m_gridHeight;
	int numYLines, numXLines;

	Shader shader;
	Line lineVert, lineHoriz;
};

