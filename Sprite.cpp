#include "Sprite.h"
#include "Shader.h"


#include <string>

#include <iostream>

Sprite::Sprite(std::string filename)
{
	m_vaoID = 0;
	m_vboID[0] = 0;
	m_vboID[1] = 0;
	m_NumberOfVerts = 0;

	this->filename = filename;
}

Sprite::~Sprite() {
	glDeleteBuffers(2, m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Sprite::SetHeight(float height) {
	this->m_Height = std::move(height);
}

void Sprite::SetWidth(float width) {
	this->m_Width = std::move(width);
}

void Sprite::Init(Shader& shader, float colour[3], float repeatInS, float repeatInT)
{
	//load png image
	int imageHeight = 0;
	int imageWidth = 0;

	//create the texture on the GPU
	glGenTextures(1, &m_TexName);

	glBindTexture(GL_TEXTURE_2D, m_TexName);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // if coordintates s and t are out of range ie more than 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// 0-1 use GL_REPEAT to wrap texture to render multiple times across square
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	//otherwise use GL_CLAMP


	//image loading error checking
	bool success = ImageLoading::loadImage(this->filename);
	if (!success) {
		std::cout << "Unable to load image file" << std::endl;
		glDeleteTextures(1, &m_TexName);
		return;
	}
	else
	{
		std::cout << "Image "<< this->filename <<" loaded " << std::endl;
	}


	//Create the geometry
	m_NumberOfVerts = 6;
	float vert[18];	// create a vertex array

	float halfWidth = m_Width / 2.0f;
	float halfHeight = m_Height / 2.0f;
	//x,y,z values for each vertex
	vert[0] = -halfWidth; vert[1] = halfHeight;  vert[2] = 0.0;
	vert[3] = -halfWidth; vert[4] = -halfHeight; vert[5] = 0.0;
	vert[6] = halfWidth; vert[7] = -halfHeight; vert[8] = 0.0;

	vert[9] = -halfWidth; vert[10] = halfHeight;  vert[11] = 0.0;
	vert[12] = halfWidth; vert[13] = halfHeight;  vert[14] = 0.0;
	vert[15] = halfWidth; vert[16] = -halfHeight; vert[17] = 0.0;

	//texture coordinates
	float tex[12];
	tex[0] = 0.0f;	 tex[1] = repeatInT;
	tex[2] = 0.0f;	 tex[3] = 0.0f;
	tex[4] = repeatInS;	 tex[5] = 0.0f;

	tex[6] = 0.0f;	 tex[7] = repeatInT;
	tex[8] = repeatInS;	 tex[9] = repeatInT;
	tex[10] = repeatInS;	 tex[11] = 0.0f;

	// colour array
	float col[18];
	col[0] = colour[0]; col[1] = colour[1]; col[2] = colour[2]; //r,g,b values for each vertex
	col[3] = colour[0]; col[4] = colour[1]; col[5] = colour[2]; //r,g,b values for each vertex
	col[6] = colour[0]; col[7] = colour[1]; col[8] = colour[2]; //r,g,b values for each vertex
	col[9] = colour[0]; col[10] = colour[1]; col[11] = colour[2]; //r,g,b values for each vertex
	col[12] = colour[0]; col[13] = colour[1]; col[14] = colour[2]; //r,g,b values for each vertex
	col[15] = colour[0]; col[16] = colour[1]; col[17] = colour[2]; //r,g,b values for each vertex

	//VAO allocation
	glGenVertexArrays(1, &m_vaoID);

	// First VAO setup
	glBindVertexArray(m_vaoID);

	glGenBuffers(3, m_vboID); // we need three VBOs - one for the vertices and one for the colours
							//and an extra one for the texture coordinates

	//Lets set up the vertices.
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);

	//initialises data storage of vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, m_NumberOfVerts * 3 * sizeof(GLfloat), vert, GL_STATIC_DRAW);

	//set the position - linked to the position shader input
	GLint vertexLocation = glGetAttribLocation(shader.handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Now set up the colours
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, m_NumberOfVerts * 3 * sizeof(GLfloat), col, GL_STATIC_DRAW);

	//set the colour - linked to the colour shader input.
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	//location in shader, number of componentns,  type, normalised, stride, pointer to first attribute
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Now set up the texture coordinates
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, m_NumberOfVerts * 3 * sizeof(GLfloat), tex, GL_DYNAMIC_DRAW);

	//set the texture coords - linked to the texcoord shader input.
	GLint texLocation = glGetAttribLocation(shader.handle(), "in_TexCoord");
	glEnableVertexAttribArray(texLocation);
	//location in shader, number of componentns,  type, normalised, stride, pointer to first attribute
	glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//good practice to bind to 0.
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Sprite::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	glUseProgram(shader.handle());  // use the shader

	//set the DiffuseMap in GLSL to the texture unit 0.
	glUniform1i(glGetUniformLocation(shader.handle(), "DiffuseMap"), 0);

	glBindTexture(GL_TEXTURE_2D, m_TexName);

	//set the uniform for the projectionmatrix
	glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	//pass the uniform for the ModelView matrix to the shader
	glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	//Draw the object
	glBindVertexArray(m_vaoID);		// select first VAO
	glDrawArrays(GL_TRIANGLES, 0, m_NumberOfVerts);	// draw first object

	glBindVertexArray(0); //unbind the vertex array object
	glUseProgram(0); //turn off the current shader
}
