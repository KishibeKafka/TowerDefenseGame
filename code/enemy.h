#pragma once
#include "Vector2D.h"
#include "property.h"

class Enemy : public Actor
{
public:
    Enemy();
    void Update();
    void init(unsigned i);
};