#include "MainContainer.h"
#include <Spritesheet.h>
#include <Constants.h>
#include <AssetPool.h>
#include <BoxBounds.h>

MainContainer::MainContainer(Shader& sh) : m_MenuItems()
{
	init(sh);
}

MainContainer::~MainContainer()
{
	delete obj;
	delete menuItem;
}

void MainContainer::init(Shader& sh)
{
	Spritesheet* groundSprites = AssetPool::getSpritesheet("assets/groundSprites.png");
	Spritesheet* buttonSprite = AssetPool::getSpritesheet("assets/ui/buttonSprites.png");

	for (int i = 0; i < groundSprites->sprites.size(); ++i)
	{
		Sprite* currentSprite = groundSprites->sprites[i];
		//currentSprite->initSubSprite(sh);

		// currentSprite->column * Constants::BUTTON_WIDTH		how many buttons are before this
		// currentSprite->column * Constants::BUTTON_SPACING_HZ how many spaces are before this
		int x = Constants::BUTTON_OFFSET_X + (currentSprite->column * Constants::BUTTON_WIDTH) +
			(currentSprite->column * Constants::BUTTON_SPACING_HZ);
		int y = Constants::BUTTON_OFFSET_Y + (currentSprite->row * Constants::BUTTON_HEIGHT) +
			(currentSprite->row * Constants::BUTTON_SPACING_VT);

		obj = new GameObject("Genereted", new Transform(glm::vec2(x, y)));
		obj->addComponent(currentSprite->copy());
		obj->getComponent<Sprite>()->initSubSprite(sh);

		menuItem = new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
			buttonSprite->sprites[0], buttonSprite->sprites[1], sh);
		obj->addComponent(menuItem);
		obj->addComponent(new BoxBounds(Constants::TILE_WIDTH, Constants::TILE_HEIGHT));
		buttonSprite->sprites[0]->initSubSprite(sh);
		buttonSprite->sprites[1]->initSubSprite(sh);

		m_MenuItems.push_back(obj);
	}
}

void MainContainer::start() {
	for (GameObject* g : m_MenuItems)
	{
		for (Component* c : g->getAllComponents())
		{
			c->start();
		}
	}
}

Component* MainContainer::copy()
{
	return nullptr;
}

void MainContainer::update(float dt)
{
	for (GameObject* g : m_MenuItems)
	{
		g->update(dt);
	}
}

void MainContainer::draw(Shader& shader, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs)
{
	for (GameObject* g : m_MenuItems)
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(g->transform->position.x, g->transform->position.y, 1.0f));
		g->draw(shader, ModelViewMatrix, ProjectionMatrixs);
	}
}

std::string MainContainer::serialise(int tabsize)
{
	return "";
}
