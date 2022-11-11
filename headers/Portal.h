#pragma once
#include "Component.h"
#include <Player.h>
#include <Bounds.h>
#include "GameObject.h"

class Portal :
    public Component
{
public:
    Portal(PlayerState state);
    Portal(PlayerState state, GameObject* player);
    ~Portal();

    void start();
    void update(float dt);
    void draw(float dt);

    // Inherited via Component
    virtual std::string serialise(int tabSize) override;
    static Portal* deseriaise() ;
    virtual Component* copy() override;

    PlayerState m_StateChanger;

    static Portal* deserialisedPortal;
private:
    Bounds* bounds;
    GameObject* player;
};

