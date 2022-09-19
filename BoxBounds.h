#pragma once
#include "Component.h"
#include <string>
class BoxBounds : public Component
{
public:
	float width, height;

	BoxBounds(float width, float height);
	BoxBounds(BoxBounds& boxB);
	void update(float dt);

};

