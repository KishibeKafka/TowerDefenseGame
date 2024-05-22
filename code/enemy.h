#pragma once
#include "Vector2D.h"
#include "property.h"
#include "world.h"

extern World main_world;

class Enemy : public Actor
{
public:
    Enemy();
    ~Enemy()
    {
        main_world.enemy_number--;
    }
    void Update();
    void init(int i);
};