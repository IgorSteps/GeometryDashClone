#pragma once
#include <Component.h>
#include <Sprite.h>
#include <ML.h>
#include <GameObject.h>
class MainContainer;
class TabItem : public Component
{
public:
	TabItem(int x, int y, int width, int height, Sprite* sp, Shader& sh, MainContainer* mContianer);
	~TabItem();
	
	TabItem* copy();
	std::string serialise(int tabsize);

	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs);
	bool isSelected;

	Shader shader;

private:
	Sprite* m_TabSprite;
	MainContainer* m_MainContainer;
	int m_X, m_Y, m_Width, m_Height;
};

