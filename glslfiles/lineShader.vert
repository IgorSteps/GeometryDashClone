#version 150

uniform mat4 ProjectionMatrix;
uniform mat4 ModelViewMatrix;

in vec3 in_Position; // Position coming in
in vec4 in_Color; // colour coming in
out vec4 ex_Color; // colour leaving the vertex,

//this will be sent to the fragment shader
void main(void)
{
	gl_Position = ProjectionMatrix * ModelViewMatrix * vec4(in_Position, 1.0);
	ex_Color = in_Color;
}