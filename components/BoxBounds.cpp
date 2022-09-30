#include "BoxBounds.h"

BoxBounds::BoxBounds(float width, float height) {
	this->width = width;
	this->height = height;
}

BoxBounds::BoxBounds(BoxBounds& bb) 
{
	width = bb.width;
	height = bb.height;
}

void BoxBounds::update(float dt) {
	//std::cout << "We are insside box bounds" << '\n';
}

Component* BoxBounds::copy() 
{
	return new BoxBounds(this->width, this->height);
}

std::string BoxBounds::serialise(int tabSize)
{
	return "";
}