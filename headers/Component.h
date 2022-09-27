#pragma once

#include "Shader.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
class GameObject;

class Component {
public:
	GameObject* gameObj;
	virtual void update(float dt){};
	virtual void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix){};
	virtual Component* copy()=0;
	virtual void start() {};
	virtual ~Component() {};
};