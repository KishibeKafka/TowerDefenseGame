#pragma once
#include "actor.h"

class Enemy : public Actor
{
public:
    void Update()
    {
        components_iter = components.begin();
        for (; components_iter != components.end(); components_iter++)
        {
            (*components_iter)->Update();
        }
    }
};