#pragma once


#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glad\glad.h"
#include "Shader.h"
#include "Component.h"
#include "ImageLoading.h"
#include <string>

class Sprite : public Component
{
public:
	Sprite(std::string filename);	//default constructor
	Sprite(int imgX, int imgY, int tileWidth, int tileHeight);
	~Sprite();
	void Init(Shader& shader, float colour[3], float repeatInS, float repeatInT);
	void initSubSprite(Shader& shader, float colour[3]);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);

	void SetWidth(float size);
	void SetHeight(float size);
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[3];	// ids for Vertex Buffer Objects
	unsigned int m_NumberOfVerts;//number of vertices in the object
	unsigned int EBO[3];
	//Dimensions of the sprite.
	float m_Width;
	float m_Height;

	//sub sprite data
	int imgX, imgY, tileWidth, tileHeight;

	// picture file name
	std::string filename;

	//identifier for the texture
	GLuint m_TexName; 
	ImageLoading image;

};

