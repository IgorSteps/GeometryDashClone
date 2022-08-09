#pragma once
class Component {
public:
	virtual void update(float dt){};
	virtual void draw(){};
	virtual ~Component() {};
};