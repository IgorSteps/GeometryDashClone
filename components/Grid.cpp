#include "Grid.h"
#include "Game.h"
#include "Constants.h"

#include <iostream>
#include <algorithm>

Grid::Grid()
{
	camera = Game::game->getCurrentScene()->camera;
	m_gridHeight = Constants::TILE_HEIGHT;
	m_gridWidth = Constants::TILE_WIDTH;
	numYLines = 33; // number of vertical lines
	numXLines = 18; // number of horizontal lines

	// lines color
	float col[] = { .75f, .75f, .75f };

	// initilise vertical lines
	lineVert = Line();
	lineVert.setColour(col);
	lineVert.SetWidth(1.5f);
	lineVert.SetHeight(Constants::GROUND_Y);
	lineVert.setIsGrid(true);

	//initilise horizontal lines
	lineHoriz = Line();
	lineHoriz.setColour(col);
	lineHoriz.SetWidth(Constants::SCREEN_WIDTH);
	lineHoriz.SetHeight(1.5f);
	lineHoriz.setIsGrid(true);
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
	// finds where the bottom y coord for vertical lines is
	float bottom = std::min((Constants::GROUND_Y - camera->position.y), static_cast<float>(Constants::SCREEN_HEIGHT));
	// scale factor for vertical lines to scale vertical lines whenever user goes up and ground disappears
	float scaleFact = bottom / Constants::GROUND_Y ;

	// knowing camera's x,y - calculate wherever the first 42px mark is
	float startX = floor(camera->position.x / m_gridWidth) * m_gridWidth - camera->position.x;
	float startY = floor(camera->position.y / m_gridHeight) * m_gridHeight - camera->position.y;

	// vertical lines
	for (int column = 0; column < numYLines; ++column)
	{
		// translate every 42px
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(startX, 0.0f, 0.0f));
		// scale in y direction
		ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(glm::vec2(1.0f, scaleFact), 1.0f));
		lineVert.draw(shader, ModelViewMatrix, ProjectionMatrix);
		startX += m_gridWidth;
	}

	// horizontal lines
	for (int row = 0; row < numXLines; ++row)
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, startY, 0.0f));
		if (camera->position.y + startY < Constants::GROUND_Y) 
		{
			lineHoriz.draw(shader, ModelViewMatrix, ProjectionMatrix);
			startY += m_gridHeight;
		}
	}
}

Component* Grid::copy()
{
	return nullptr;
}


std::string Grid::serialise(int tabSize)
{
	return "";
}
