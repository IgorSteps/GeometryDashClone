#version 150

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
	out_Color = vec4(ex_Color);
}