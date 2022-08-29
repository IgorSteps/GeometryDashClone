#pragma once
#include "Scene.h"


class LevelEditorScene : public Scene
{
public:
	LevelEditorScene(std::string name);
	~LevelEditorScene();
	static LevelEditorScene* getScene();
	static LevelEditorScene* currentScene;
	GameObject* player;
	void init();
	void update(float dt);
	void draw();
};

