#pragma once
#include "Scene.h"

class LevelEditorScene : public Scene
{
public:
	LevelEditorScene(std::string name);
	~LevelEditorScene();
	void init();
	void update(float dt);
	void draw();
};

