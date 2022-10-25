#pragma once
#include "Bounds.h"
#include <string>
class BoxBounds : public Bounds
{
public:
	BoxBounds(float width, float height);
	~BoxBounds();
	
	void update(float dt);
	std::string serialise(int tabSize);
	static BoxBounds* deserialise();
	Component* copy();
	void resolveCollision(GameObject& player);


	

	// Inherited via Bounds
	static bool checkCollision(BoxBounds& b1, BoxBounds& b2);
	virtual float getWidth() override;
	virtual float getHeight() override;
	float m_EnclosingRadius;

	static BoxBounds* deserialsiedBB;
	float m_Width, m_Height;
	float m_HalfWidth, m_HalfHeight;
};

