#pragma once
#include <Component.h>
#include <Sprite.h>
#include <GameObject.h>
#include <Ground.h>
class Background : public Component
{
public:
	Background(std::string file, std::vector<GameObject*>& backgrounds,
		Ground* gr, bool followingGround, float width, float height, const float color[3]);
	void update(float dt);
	void draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	int m_Height, m_Width;
	int m_Timestamp=0;
	Sprite *sp;
	std::vector<GameObject*> m_Backgrounds;

	// Inherited via Component
	virtual std::string serialise(int tabSize) override;
	virtual Component* copy() override;
private:
	float m_Speed = 80.0f;
	Ground* m_Ground;
	bool m_FollowGround;
};

