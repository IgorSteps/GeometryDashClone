#pragma once
#include <GLFW/glfw3.h>
class ML
{

public:
	static ML* get();
	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void endFrame();
	static bool mouseButtonDown(int button);

	static float getX();
	static float getY();
	static float getDx();
	static float getDy();
	static bool isDragging();

private:
	ML();
	~ML();
	static ML* s_Instance;
	double m_xPos, m_yPos, m_lastX, m_lastY;
	bool m_mouseButtonPressed[3];
	bool m_isDragging;
};

