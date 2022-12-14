#include "ML.h"
#include <iostream>

ML::ML() {
    m_xPos = 0.0;
    m_yPos = 0.0;
    m_lastX = 0.0;
    m_lastY = 0.0;
   // m_mouseButtonPressed[3]{ 0 };
    inside = false;
}

ML::~ML() {
    delete ML::s_Instance;
}

ML* ML::get() {
    if (ML::s_Instance == nullptr) 
    {
        ML::s_Instance = new ML();
    }

    return ML::s_Instance;
}

void ML::mousePosCallback(GLFWwindow* window, double xpos, double ypos) 
{
    get()->m_lastX = get()->m_xPos;
    get()->m_lastY = get()->m_yPos;
    get()->m_xPos = xpos;
    get()->m_yPos = ypos;
    get()->m_isDragging = get()->m_mouseButtonPressed[0] ||
        get()->m_mouseButtonPressed[1] ||
        get()->m_mouseButtonPressed[2];
    if (xpos < 1280 && ypos < 720) {
        get()->inside = true;
    }
    // test
    //std::cout << "mousePosCallback_TEST   " << "x-coord: " << s_Instance->m_xPos << ", y-coord: " << s_Instance->m_yPos << '\n';
}

void ML::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
    if (action == GLFW_PRESS)
    {
        if (button < 3)
        {
            //test  
            //std::cout << "mouseButtonCallback_TEST   " << "x-coord: " << s_Instance->m_xPos << ", y-coord: " << s_Instance->m_yPos << '\n';
            get()->m_mouseButtonPressed[button] = true;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        if (button < 3)
        {
            get()->m_mouseButtonPressed[button] = false;
            get()->m_isDragging = false;
        }
    }
}

void ML::mouseEnterCallback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        //test
        //std::cout << "inside" << '\n';
        return;
    }
    else
    {
        //test
        //std::cout << "outside" << '\n';
        return;
    }
}

void ML::endFrame() {
    get()->m_lastX = get()->m_xPos;
    get()->m_lastY = get()->m_yPos;
}

float ML::getX() {
    return (float)get()->m_xPos;
}

float ML::getY() {
    return (float)get()->m_yPos;
}

float ML::getDx() {
    return (float)(get()->m_lastX - get()->m_xPos);
}

float ML::getDy() {
    return (float)(get()->m_lastY - get()->m_yPos);
}

//float ML::getOrthoX() {
//    float currentX = getX();
//    currentX = currentX / 1280;
//    return currentX;
//}
//
//float ML::getOrthoY() {
//    float currentY = getY();
//    currentY = currentY / 720;
//    return currentY;
//}

bool ML::isDragging() {
    return get()->m_isDragging;
}

bool ML::mouseButtonDown(int button) 
{
    if (button < 3) 
    {
        return get()->m_mouseButtonPressed[button];
    }
    else 
    {
        return false;
    }
}

ML* ML::s_Instance = nullptr;
