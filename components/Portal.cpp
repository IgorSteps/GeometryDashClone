#include "Portal.h"
#include "BoxBounds.h"
#include "Game.h"
#include "LevelScene.h"
#include "Parser.h"
#include <iostream>

Portal::Portal(PlayerState state)
{
    m_StateChanger = state;
}

Portal::Portal(PlayerState state, GameObject* p)
{
    m_StateChanger = state;
    player = p;
}

Portal::~Portal()
{
    delete deserialisedPortal;
}

void Portal::start()
{
    bounds = gameObj->getComponent<Bounds>();
    LevelScene* scene = (LevelScene*)Game::game->getCurrentScene();
    if (scene != nullptr)
    {
        player = scene->player;
    }
}

void Portal::update(float dt)
{

    if(player != nullptr)
    {
        Bounds* playerBounds = player->getComponent<Bounds>();
        if (playerBounds!=nullptr)
        {
            if (player->getComponent<Player>()->m_State != m_StateChanger &&
                BoxBounds::checkCollison(*bounds, *playerBounds))
            {
                player->getComponent<Player>()->m_State = m_StateChanger;
            }
        }
    }
}

std::string Portal::serialise(int tabSize)
{
    std::string builder;
    int state = m_StateChanger ? 1 : 0;
    builder.append(beginObjectProperty("Portal", tabSize));
    builder.append(addIntProperty("StateChanger", state, tabSize + 1, true, false));
    builder.append(closeObjectProperty(tabSize));

    return builder;
}

Portal* Portal::deseriaise()
{
    int state = Parser::consumeIntProperty("StateChanger");
    Parser::consumeEndObjectProperty();

    PlayerState stateChanger = state == 1 ? FLY : NORMAL;
    deserialisedPortal = new Portal(stateChanger);
    return deserialisedPortal;
}

Component* Portal::copy()
{
    return new Portal(m_StateChanger, player);
}

 Portal* Portal::deserialisedPortal = nullptr;
