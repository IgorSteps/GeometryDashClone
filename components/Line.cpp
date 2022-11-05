#include "Line.h"

Line::Line()
{
	m_vaoID = 0;
	m_vboID[0] = { 0 };
	m_vboID[1] = { 0 };
	m_vboID[2] = { 0 };
	m_eboID[0] = { 0 };
	m_eboID[1] = { 0 };
	m_eboID[2] = { 0 };

	colour[0] = { 0 };
	colour[1] = { 0 };
	colour[2] = { 0 };
	m_Height = 0;
	m_Width = 0;
}

Line::~Line() {
	glDeleteBuffers(2, m_vboID);
	glDeleteBuffers(2, m_eboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Line::setColour(float col[3]) 
{
	colour[0] = col[0];
	colour[1] = col[1];
	colour[2] = col[2];
}

void Line::SetWidth(float size)
{
	m_Width = size;
}

void Line::SetHeight(float size)
{
	m_Height = size;
}

void Line::setIsGrid(bool var)
{
	isGrid = var;
}

void Line::setIsTriangle(bool var)
{
	isTriangle = var;
}

// set up a quad not an actual line
void Line::init(Shader& shader) 
{
	//Create the geometry
	float vert[] = {
		0.0f,		0.0f,		0.0f,	// top left
		0.0f,		m_Height,	0.0f,	// bottom left
		m_Width,	m_Height,	0.0f,	// bottom right
		m_Width,	0.0f,		0.0f	// top right
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
	glGenBuffers(2, m_vboID);		// we need three VBOs - vertices, colours, textures
	glGenBuffers(2, m_eboID);		// we need three m_eboIDs - vertices, colours, textures
	
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

	/// --------colourS--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// set the colour - linked to the colour shader input 
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//good practice to bind to 0.
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Line::initLine(Shader& shader, float startX, float startY, float endX, float endY)
{
	float vert[] = {
			 startX, startY,0.0f,
			 endX,	endY,	0.0f,
	};
	// colour array
	float col[]{
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
	};

	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(2, m_vboID);
	

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	GLint vertexLocation = glGetAttribLocation(shader.handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	// set the colour - linked to the colour shader input 
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Line::initTriangle(Shader& shader, glm::vec2 p1, glm::vec2 p2, glm::vec2 p3)
{
	//Create the geometry
	float vert[] = {
		p1.x,		p1.y,	0.0f,	// left
		p2.x,		p2.y,	0.0f,	// top 
		p3.x,		p3.y,	0.0f,	// right
	};

	// colour array
	float col[]{
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
		colour[0], colour[1], colour[2],
	};

	//Generate buffers
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);
	glGenBuffers(2, m_vboID);		// we need 2 VBOs - vertices, colours

	/// --------VERTICIES--------
	// VBO[0]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);//initialises data storage of VBO
	//set the position - linked to the position shader input
	GLint vertexLocation = glGetAttribLocation(shader.handle(), "in_Position");
	glEnableVertexAttribArray(vertexLocation);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	/// --------COLOURS--------
	// Bind and initilise storage of VBO[1] & m_eboID[1]
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col), col, GL_STATIC_DRAW);
	// set the colour - linked to the colour shader input 
	GLint colorLocation = glGetAttribLocation(shader.handle(), "in_Color");
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//good practice to bind to 0.
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

// draw a quad or an actual line
void Line::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	glUseProgram(shader.handle());  // use the shader

	//set the DiffuseMap in GLSL to the texture unit 0.
	//glUniform1i(glGetUniformLocation(shader.handle(), "DiffuseMap"), 0);

	//set the uniform for the projectionmatrix
	glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ProjectionMatrix"), 1, GL_FALSE, &ProjectionMatrix[0][0]);

	//pass the uniform for the ModelView matrix to the shader
	glUniformMatrix4fv(glGetUniformLocation(shader.handle(), "ModelViewMatrix"), 1, GL_FALSE, &ModelViewMatrix[0][0]);

	//Draw the object
	glBindVertexArray(m_vaoID);		// select first VAO
	if (isGrid)
	{
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	else if (isTriangle)
	{
		glDrawArrays(GL_LINE_LOOP, 0, 3);
	}
	else
	{
		glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, 0);
	}

	
	glBindVertexArray(0); //unbind the vertex array object
	glUseProgram(0); //turn off the current shader
}

Component* Line::copy() 
{
	return nullptr;
}

std::string Line::serialise(int tabSize)
{
	return "";
}
