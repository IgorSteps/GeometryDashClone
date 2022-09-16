#include "Grid.h"
#include "Game.h"
#include "Constants.h"

#include <iostream>


Grid::Grid()
{
	camera = Game::game->getCurrentScene()->camera;
	m_gridHeight = Constants::TILE_HEIGHT;
	m_gridWidth = Constants::TILE_WIDTH;
	numXLines = 10;
	numYLines = 10;

	// initilise line
	line = Line();
	float col[3] = { 1.0f, 0.0f, 0.0f };
	line.setColour(col);
	line.SetWidth(50.0f);
	line.SetHeight(Constants::SCREEN_HEIGHT);

	// load line shader
	if (!shader.load("Line", "./glslfiles/lineShader.vert", "./glslfiles/lineShader.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	// initlise opengl stuff
	line.init(shader);
}

void Grid::update(float dt) {};

void Grid::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix) {
	float startX = floor(camera->position.x / m_gridWidth) * m_gridWidth - camera->position.x;
	float startY = floor(camera->position.y / m_gridHeight) * m_gridHeight - camera->position.y;

	for (int column = 0; column < numYLines; ++column)
	{
		// todo: draw verical lines
		line.draw(shader, ModelViewMatrix, ProjectionMatrix);
		startX += m_gridWidth;
	}

	for (int row = 0; row < numXLines; ++row)
	{
		// todo: draw horizontal lines
		line.draw(shader, ModelViewMatrix, ProjectionMatrix);
		startY += m_gridHeight;
	}
}
