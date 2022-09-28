#pragma once
#include <ML.h>
class KL
{
public:
	static KL* get();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static bool isKeyPressed(int key);

private:
	//KL();
	~KL();
	static KL* instance;
	bool keyPressed[350] = { 0 };
};

