#include "Ground.h"
#include "GameObject.h"
#include "Constants.h"
#include "BoxBounds.h"
#include "LevelEditorScene.h"


Ground::Ground(Sprite* sp, Shader& sh) {
	this->sp = sp;
	sp->SetWidth(Constants::SCREEN_WIDTH);
	sp->SetHeight(Constants::SCREEN_HEIGHT);
	sp->initSprite(sh);
}

Ground::~Ground() {

}
void Ground::update(float dt) {
	GameObject* player = LevelEditorScene::getScene()->player;

	if (player->transform->position.y + player->getComponent<BoxBounds>()->height > gameObj->transform->position.y) {
		player->transform->position.y = gameObj->transform->position.y - player->getComponent<BoxBounds>()->height;
	}
} 

void Ground::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix)
{
	// Translate
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj->transform->position.x,
		gameObj->transform->position.y, 0.0f));
	// Rotate
	ModelViewMatrix = glm::scale(ModelViewMatrix, glm::vec3(gameObj->transform->scale, 1.0f));

	// Draw ground
	this->sp->draw(shader, ModelViewMatrix, ProjectionMatrix);
}
