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
	void initLine(Shader& shader, float startX, float startY, float endX, float endY);
	void initTriangle(Shader& shader, glm::vec2 xy1, glm::vec2 xy2, glm::vec2 xy3);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	Component* copy();
	std::string serialise(int tabSize);


	void SetWidth(float size);
	void SetHeight(float size);
	void setIsGrid(bool var);
	void setIsTriangle(bool var);
	float const& getWidth();
	float const& getHeight();
	float colour[3];
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[2];	// ids for Vertex Buffer Objects
	unsigned int m_eboID[2];	// ids for Element Buffer Objects
	bool isGrid = true;
	bool isTriangle = false;;
	//Dimensions of the sprite.
	float m_Width;
	float m_Height;


};

