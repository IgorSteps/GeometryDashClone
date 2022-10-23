#include "MainContainer.h"
#include <Constants.h>
#include <AssetPool.h>
#include <BoxBounds.h>
#include <iostream>
#include <Game.h>

MainContainer::MainContainer() : m_MenuItems()
{
	m_ContainerBg = AssetPool::getSprite("assets/ui/menuContainerBackground.png");
	m_ContainerBg->SetHeight(180.0f);
	m_ContainerBg->SetWidth(1280.0f);
	init();
}

MainContainer::~MainContainer()
{
	delete obj;
	delete menuItem;
	delete tabObj;

	delete m_ContainerBg;
	delete tabsprites;
	delete groundSprites;
	delete buttonSprite;
	delete spikeSprites;
	delete bigSprites;
	delete smallBlocks;
	delete portalSprites;
}

void MainContainer::init()
{
	if (!shader.load("No Color Shader", "./glslfiles/noColorVert.vert", "./glslfiles/noColorFrag.frag"))
	{
		std::cout << "failed to load shader" << std::endl;
	}
	
	tabsprites = AssetPool::getSpritesheet("assets/ui/tabs.png");
	m_ContainerBg->initSprite(shader);

	for (int i = 0; i < tabsprites->sprites.size(); ++i)
	{
		Sprite* currentTab = tabsprites->sprites.at(i);
		currentTab->initSubSprite(shader);

		int x = Constants::TAB_OFFSET_X + (currentTab->column * Constants::TAB_WIDTH)
			+ (currentTab->column * Constants::TAB_HORIZONTAL_SPACING);
		int y = Constants::TAB_OFFSET_Y;

		tabObj = new GameObject("Tab " + std::to_string(i), new Transform(glm::vec2(x, y)));
		tabObj->setUi(true);
		tabObj->addComponent(currentTab);

		
		m_Tabs.push_back(tabObj);
		m_TabMaps.insert(std::pair(tabObj, std::vector<GameObject*>()));

		Game::game->getCurrentScene()->addGameObject(tabObj);
	}
	m_CurrentTab = m_Tabs.at(0);

	addTabObjects();
}

void MainContainer::addTabObjects()
{
	groundSprites = AssetPool::getSpritesheet("assets/groundSprites.png");
	buttonSprite = AssetPool::getSpritesheet("assets/ui/buttonSprites.png");
	spikeSprites = AssetPool::getSpritesheet("assets/spikes.png");
	bigSprites = AssetPool::getSpritesheet("assets/bigSprites.png");
	smallBlocks = AssetPool::getSpritesheet("assets/smallBlocks.png");
	portalSprites = AssetPool::getSpritesheet("assets/portal.png");

	for (int i = 0; i < groundSprites->sprites.size(); ++i)
	{
		Sprite* currentSprite = groundSprites->sprites[i];

		// currentSprite->column * Constants::BUTTON_WIDTH		how many buttons are before this
		// currentSprite->column * Constants::BUTTON_SPACING_HZ how many spaces are before this
		int x = Constants::BUTTON_OFFSET_X + (currentSprite->column * Constants::BUTTON_WIDTH) +
			(currentSprite->column * Constants::BUTTON_SPACING_HZ);
		int y = Constants::BUTTON_OFFSET_Y + (currentSprite->row * Constants::BUTTON_HEIGHT) +
			(currentSprite->row * Constants::BUTTON_SPACING_VT);

		// Add first tab container objs
		obj = new GameObject("First tab", new Transform(glm::vec2(x, y)));
		obj->setUi(true);
		obj->setNonserialisable();
		obj->addComponent(currentSprite->copy());
		obj->getComponent<Sprite>()->initSubSprite(shader);

		menuItem = new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
			buttonSprite->sprites[0], buttonSprite->sprites[1], shader, this);
		obj->addComponent(menuItem);
		obj->addComponent(new BoxBounds(Constants::TILE_WIDTH, Constants::TILE_HEIGHT));
		buttonSprite->sprites[0]->initSubSprite(shader);
		buttonSprite->sprites[1]->initSubSprite(shader);

		m_TabMaps.at(m_Tabs.at(0)).push_back(obj);

		//// Add second tab container objs
		if (i < smallBlocks->sprites.size())
		{
			obj = new GameObject("Second tab", new Transform(glm::vec2(x, y)));
			obj->setUi(true);
			obj->setNonserialisable();
			menuItem = new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
				(Sprite*)buttonSprite->sprites[0]->copy(), (Sprite*)buttonSprite->sprites[1]->copy(), shader, this);
			menuItem->m_ButtonSprite->initSubSprite(shader);
			menuItem->m_HoveredSprite->initSubSprite(shader);
			obj->addComponent(smallBlocks->sprites.at(i));
			smallBlocks->sprites.at(i)->initSubSprite(shader);
			obj->addComponent(menuItem);

			if (i == 0)
			{
				obj->addComponent(new BoxBounds(Constants::TILE_WIDTH, 16.0f));
			}
			m_TabMaps.at(m_Tabs.at(1)).push_back(obj);
		}

		// Add forth tab container objs
		if (i < spikeSprites->sprites.size())
		{
			obj = new GameObject("Forth tab", new Transform(glm::vec2(x, y)));
			obj->setUi(true);
			obj->setNonserialisable();
			menuItem = new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
				(Sprite*)buttonSprite->sprites[0]->copy(), (Sprite*)buttonSprite->sprites[1]->copy(), shader, this);
			menuItem->m_ButtonSprite->initSubSprite(shader);
			menuItem->m_HoveredSprite->initSubSprite(shader);
			obj->addComponent(spikeSprites->sprites.at(i));
			spikeSprites->sprites.at(i)->initSubSprite(shader);
			obj->addComponent(menuItem);

			// todo: add triangle bounds component later
			m_TabMaps.at(m_Tabs.at(3)).push_back(obj);
		} 

		// Add fifth tab container objs
		if (i == 0)
		{
			obj = new GameObject("Fifth tab", new Transform(glm::vec2(x, y)));
			obj->setUi(true);
			obj->setNonserialisable();
			menuItem = new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
				(Sprite*)buttonSprite->sprites[0]->copy(), (Sprite*)buttonSprite->sprites[1]->copy(), shader, this);
			menuItem->m_ButtonSprite->initSubSprite(shader);
			menuItem->m_HoveredSprite->initSubSprite(shader);
			obj->addComponent(menuItem);
			obj->addComponent(bigSprites->sprites.at(i));
			bigSprites->sprites.at(i)->initSubSprite(shader);
			obj->addComponent(new BoxBounds(Constants::TILE_WIDTH * 2, 56.0f));

			m_TabMaps.at(m_Tabs.at(4)).push_back(obj);
		}
		
		// Add sixth tab container objs
		if (i < portalSprites->sprites.size())
		{
			obj = new GameObject("Fifth tab", new Transform(glm::vec2(x, y)));
			obj->setUi(true);
			obj->setNonserialisable();
			menuItem =new MenuItem(x, y, Constants::BUTTON_WIDTH, Constants::BUTTON_HEIGHT,
				(Sprite*)buttonSprite->sprites[0]->copy(), (Sprite*)buttonSprite->sprites[1]->copy(), shader, this);
			menuItem->m_ButtonSprite->initSubSprite(shader);
			menuItem->m_HoveredSprite->initSubSprite(shader);
			obj->addComponent(menuItem);
			obj->addComponent(portalSprites->sprites.at(i));
			portalSprites->sprites.at(i)->initSubSprite(shader);
			obj->addComponent(new BoxBounds(44.0f, 85.0f));

			// todo: add portal component

			m_TabMaps.at(m_Tabs.at(5)).push_back(obj);
		}
		
	}
}

void MainContainer::start() {
	for (GameObject* g : m_Tabs)
	{
		for (GameObject* g2 : m_TabMaps.at(g))
		{
			for (Component* c : g2->getAllComponents())
			{
				c->start();
			}
		}
	}
}

Component* MainContainer::copy()
{
	return nullptr;
}

void MainContainer::update(float dt)
{
	for (GameObject* g : m_TabMaps.at(m_CurrentTab))
	{
		g->update(dt);

		MenuItem* mItem = g->getComponent<MenuItem>();
		if (g != m_HotButton && mItem->isSelected)
		{
			mItem->isSelected = false;
		}
	}
}

void MainContainer::draw(Shader& sh, glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrixs)
{
	ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, Constants::CONTAINER_OFFSET_Y, 1.0f));
	m_ContainerBg->draw(shader, ModelViewMatrix, ProjectionMatrixs);
	for (GameObject* g : m_TabMaps.at(m_CurrentTab))
	{
		ModelViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(g->transform->position.x, g->transform->position.y, 1.0f));
		g->draw(shader, ModelViewMatrix, ProjectionMatrixs);
	}
}

std::string MainContainer::serialise(int tabsize)
{
	return "";
}

void MainContainer::setHotButton(GameObject* go)
{
	m_HotButton = go;
}