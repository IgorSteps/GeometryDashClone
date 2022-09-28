#pragma once

#include "Component.h"
#include "ImageLoading.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glad\glad.h"
#include <string>

class Sprite : public Component
{
public:
	Sprite(std::string filename);	//Sprite constructor 
	Sprite(std::string filename, float imgX, float imgY, float tileWidth, float tileHeight, float pW, float pH, int row, int column, int index); //Spritesheet constructor
	Sprite();
	Sprite(Sprite& sp);
	~Sprite();

	void setColour(float colour[2]);

	void initSprite(Shader& shader);
	void initSubSprite(Shader& shader);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Component* copy();


	void SetWidth(float size);
	void SetHeight(float size);
	float const& getFileWidth();
	float const& getFileHeight();
	float colour[3];
	// is sprite from image or a spritesheet
	bool isSubSprite = false;
	// sub sprite data
	int row, column, index;
	float fileW, fileH;
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[3];	// ids for Vertex Buffer Objects
	unsigned int m_eboID[3];	// ids for Element Buffer Objects
	//Dimensions of the sprite.
	float m_Width = 0.0f;
	float m_Height = 0.0f;
	//sub sprite data
	float imgX, imgY, tileWidth, tileHeight;	
	// picture file name
	std::string spriteFile, spritesheetFile;
	//identifier for the texture
	GLuint m_TexName; 
	ImageLoading image;
};

