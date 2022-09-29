#pragma once
#include "Component.h"
class CameraControls : public Component
{
public:
	CameraControls();
	CameraControls(CameraControls& cc);
	void update(float dt);
	Component* copy();
	std::string serialise(int tabSize);

private:
	float m_prevMx, m_prevMy;
};

