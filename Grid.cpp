#include "Grid.h"
#include "Game.h"
#include "Constants.h"

#include <iostream>


Grid::Grid()
{
	camera = Game::game->getCurrentScene()->camera;
	m_gridHeight = Constants::TILE_HEIGHT;
	m_gridWidth = Constants::TILE_WIDTH;
	numYLines = 33; // number of vertical lines
	numXLines = 15; // number of horizontal lines

	// lines color
	float col[] = { .75f, .75f, .75f };

	// initilise vertical lines
	lineVert = Line();
	lineVert.setColour(col);
	lineVert.SetWidth(2.5f);
	lineVert.SetHeight(Constants::GROUND_Y);

	//initilise horizontal lines
	lineHoriz = Line();
	lineHoriz.setColour(col);
	lineHoriz.SetWidth(Constants::SCREEN_WIDTH);
	lineHoriz.SetHeight(2.5f);
	
	// load shader for lines
	if (!shader.load("lineVert", "./glslfiles/lineShader.vert", "./glslfiles/lineShader.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}

	// initlise opengl stuff
	lineVert.init(shader);
	lineHoriz.init(shader);
}

void Grid::update(float dt) {};

void Grid::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix) {
	float startX = floor(camera->position.x / m_gridWidth) * m_gridWidth - camera->position.x;
	float startY = floor(camera->position.y / m_gridHeight) * m_gridHeight - camera->position.y;

	// vertical lines
	for (int column = 0; column < numYLines; ++column)
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(startX, 0.0f, 0.0f));
		lineVert.draw(shader, ModelViewMatrix, ProjectionMatrix);
		startX += m_gridWidth;
	}

	// horizontal lines
	for (int row = 0; row < numXLines; ++row)
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, startY, 0.0f));
		lineHoriz.draw(shader, ModelViewMatrix, ProjectionMatrix);
		startY += m_gridHeight;
	}
}
