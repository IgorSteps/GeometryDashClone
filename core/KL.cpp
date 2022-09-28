#include "KL.h"

KL::~KL() 
{
	delete KL::instance;
}

KL* KL::get()
{
	if (KL::instance == nullptr)
	{
		KL::instance = new KL();
	}
	return KL::instance;
}

void KL::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		get()->keyPressed[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		get()->keyPressed[key] = false;
	}
}

bool KL::isKeyPressed(int key)
{
	return KL::get()->keyPressed[key];
}

KL* KL::instance = nullptr;
