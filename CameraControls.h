#pragma once
#include "Component.h"
class CameraControls : public Component
{
public:
	CameraControls();
	CameraControls(CameraControls& cc);
	void update(float dt);

private:
	float m_prevMx, m_prevMy;
};

