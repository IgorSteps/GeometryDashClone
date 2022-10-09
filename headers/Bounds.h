#pragma once
#include <Component.h>

enum BoundsType {
	Box,
	Triangle
};

class Bounds : public Component
{
public:
	virtual float getWidth() = 0;
	virtual float getHeight()=0;

	BoundsType type;

	static bool checkCollison(Bounds& b1, Bounds& b2);

	// Inherited via Component
	virtual std::string serialise(int tabSize) override;
	virtual Component* copy() override;
};

