#pragma once
#include "Bounds.h"
#include <string>
#include <Line.h>
class BoxBounds : public Bounds
{
public:
	BoxBounds(float width, float height);
	~BoxBounds();
	
	void update(float dt);
	void draw(Shader& sh, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	std::string serialise(int tabSize);
	static BoxBounds* deserialise();
	void start();
	Component* copy();
	void resolveCollision(GameObject& player);

	void calculateTransform();
	

	// Inherited via Bounds
	static bool checkCollision(BoxBounds& b1, BoxBounds& b2);
	virtual float getWidth() override;
	virtual float getHeight() override;
	float m_EnclosingRadius;

	static BoxBounds* deserialsiedBB;
	float m_Width, m_Height;
	float m_HalfWidth, m_HalfHeight;

	// Inherited via Bounds
	virtual bool raycast(glm::vec2 position) override;
private:
	Line line1;
	Line line2;
	Line line3;
	Line line4;
	Shader shader;
};

