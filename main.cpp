#include <glad/glad.h>
#include "Game.h"
#include "Constants.h"
#include "KL.h"


#include <iostream>

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


Game GeometryDashClone(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);
    glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT, "Geometry Dash", nullptr, nullptr);
    glfwMakeContextCurrent(window);
   
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, KL::keyCallback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, ML::mousePosCallback);
    glfwSetMouseButtonCallback(window, ML::mouseButtonCallback);
    glfwSetCursorEnterCallback(window, ML::mouseEnterCallback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    GeometryDashClone.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        GeometryDashClone.ProcessInput(deltaTime);

        // update game state
        // -----------------
        GeometryDashClone.Update(deltaTime);
     
        // render
        // ------
        glClearColor(15.0f / 255.0f, 98.0f / 255.0f, 212.0f / 255.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //std::cout << glGetError() << std::endl;
        GeometryDashClone.Render();

        if (KL::isKeyPressed(GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, true);

        ML::endFrame();
        glfwSwapBuffers(window);
    }

    // delete all loaded resources ?
    glfwTerminate();
    return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
