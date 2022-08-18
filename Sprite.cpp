#include "Sprite.h"
#include "Shader.h"

#include <string>
#include <iostream>

Sprite::Sprite(std::string file)
{
	this->spriteFile = file;
	m_vaoID = 0;
	m_vboID[2] = 0;
	m_eboID[2] = 0;
}

Sprite::Sprite(std::string file, float imgX, float imgY, float tileWidth, float tileHeight, float pW, float pH)
{
	this->spritesheetFile = file;
	m_vaoID = 0;
	m_vboID[2] = 0;
	m_eboID[2] = 0;

	this->m_Height = pH;
	this->m_Width = pW;
	
	this->imgX = imgX;
	this->imgY = imgY;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
}


Sprite::~Sprite() {
	glDeleteBuffers(2, m_vboID);
	glDeleteBuffers(2, m_eboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Sprite::SetHeight(float height) {
	this->m_Height = std::move(height);
}

void Sprite::SetWidth(float width) {
	this->m_Width = std::move(width);
}

void Sprite::initSprite(Shader& shader, float colour[3], float repeatInS, float repeatInT)
{
	//create the texture on the GPU
	glGenTextures(1, &m_TexName);
	glBindTexture(GL_TEXTURE_2D, m_TexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//image loading error checking
	bool success = ImageLoading::loadImage(this->spriteFile);
	if (!success) {
		std::cout << "Unable to load image file" << std::endl;
		glDeleteTextures(1, &m_TexName);
		return;
	}
	else
	{
		std::cout << "Image "<< this->spriteFile <<" loaded " << std::endl;
	}

	float halfWidth  = m_Width/2;
	float halfHeight = m_Height/2;
	
	//Create the geometry
	float vert[] = {
		-halfWidth,		halfHeight,		0.0f,	// top left
		-halfWidth,		-halfHeight,	0.0f,	// bottom left
		halfWidth,		-halfHeight,	0.0f,	// bottom right
		halfWidth,		halfHeight,		0.0f	// top right
	};
	

	//texture coordinates
	float tex[]{
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	// colour array
	float col[]{
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,				// first triangle
		1, 2, 3					// second triangle
	};
	

	//Generate buffers
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(3, m_vboID);		// we need three VBOs - vertices, colours, textures
	glGenBuffers(3, m_eboID);		// we need three m_eboIDs - vertices, colours, textures


	/// --------VERTICIES--------
	// VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);//initialises data storage of VBO
	// m_eboID[0]
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//initialises data storage of m_eboID
	//set the position - linked to the position shader input
	GLint vertexLocation = glGetAttribLocation(shader.handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/// --------COLOURS--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// set the colour - linked to the colour shader input 
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/// --------TEXTURES--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(tex), tex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//set the texture coords - linked to the texcoord shader input.
	GLint texLocation = glGetAttribLocation(shader.handle(), "in_TexCoord");
	glEnableVertexAttribArray(texLocation);
	//location in shader, number of componentns,  type, normalised, stride, pointer to first attribute
	glVertexAttribPointer(texLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//good practice to bind to 0.
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void Sprite::initSubSprite(Shader& shader, float colour[3])
{
	//create the texture on the GPU
	glGenTextures(1, &m_TexName);
	glBindTexture(GL_TEXTURE_2D, m_TexName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	//image loading error checking
	bool success = ImageLoading::loadImage(this->spritesheetFile);
	if (!success) {
		std::cout << "Unable to load image file" << std::endl;
		glDeleteTextures(1, &m_TexName);
		return;
	}
	else
	{
		std::cout << "Image " << this->spritesheetFile << " loaded " << std::endl;
	}

	float halfWidth = 42.0f/2;
	float halfHeight = 42.0f/2;

	//Create the geometry
	float vert[] = {
		-halfWidth,		halfHeight,		0.0f,	// top left
		-halfWidth,		-halfHeight,	0.0f,	// bottom left
		halfWidth,		-halfHeight,	0.0f,	// bottom right
		halfWidth,		halfHeight,		0.0f	// top right
	};

	// normalise coordinates
	float tX = this->imgX / m_Width;
	float tY = this->imgY / m_Height;
	float tW = this->tileWidth / m_Width;
	float tH = this->tileHeight / m_Height;

	//texture coordinates
	float tex[]{
		tX, tY + tH,
		tX, tY,
		tX + tW, tY,
		tX + tW, tY + tH
	};


	// colour array
	float col[]{
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,				// first triangle
		1, 2, 3					// second triangle
	};


	//Generate buffers
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(3, m_vboID);		// we need three VBOs - vertices, colours, textures
	glGenBuffers(3, m_eboID);		// we need three m_eboIDs - vertices, colours, textures


	/// --------VERTICIES--------
	// VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);//initialises data storage of VBO
	// m_eboID[0]
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//initialises data storage of m_eboID
	//set the position - linked to the position shader input
	GLint vertexLocation = glGetAttribLocation(shader.handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/// --------COLOURS--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// set the colour - linked to the colour shader input 
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/// --------TEXTURES--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tex), tex, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[2]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0); //unbind the vertex array object
	glUseProgram(0); //turn off the current shader
}
