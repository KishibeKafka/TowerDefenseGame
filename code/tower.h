#pragma once
#include "actor.h"
#include "property.h"

class Tower : public Actor
{
public:
    Tower();
    void Update();
    void init(unsigned i);
};