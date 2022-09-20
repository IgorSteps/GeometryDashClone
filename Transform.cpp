#include "Transform.h"
Transform::Transform(glm::vec2 position)
{
	this->position = position;
	this->scale = glm::vec2(1.0f, 1.0f);
	this->rotateion = 0.0f;
}

Transform::Transform(){}

Transform::Transform(Transform* trans)
{
	position = trans->position;
	scale = trans->scale;
	rotateion = trans->rotateion;
}


Transform* Transform::copy()
{
	Transform* tr = new Transform(this->position);
	
	tr->scale = this->scale;
	tr->rotateion = this->rotateion;

	return tr;
}
