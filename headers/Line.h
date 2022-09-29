#pragma once

#include "Component.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glad\glad.h"

class Line : public Component
{
public:
	Line(); 
	~Line();

	void setColour(float colour[3]);

	void init(Shader& shader);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Component* copy();
	std::string serialise(int tabSize);


	void SetWidth(float size);
	void SetHeight(float size);
	float const& getWidth();
	float const& getHeight();
	float colour[3];
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[2];	// ids for Vertex Buffer Objects
	unsigned int m_eboID[2];	// ids for Element Buffer Objects
	
	//Dimensions of the sprite.
	float m_Width;
	float m_Height;


};

