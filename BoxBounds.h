#pragma once
#include "Component.h"
#include <string>
class BoxBounds : public Component
{
public:
	std::string name;

	BoxBounds(std::string name);
	void update(float dt);

};

