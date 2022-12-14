#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Scene.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState               State;
    bool                    Keys[1024], isInEditor;
     int            Width, Height;
    // constructor/destructor
    Game( int width,  int height);
    Game(){};
    ~Game();
    static Game* game;
    // Scene
    Scene* currentScene;
    void changeScene(int scene);
    Scene* getCurrentScene();
    Scene* getScene();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
};

