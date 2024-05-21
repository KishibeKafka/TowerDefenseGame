#pragma once
#include "actor.h"

class Tower : public Actor
{
public:
    Tower();
    void Update();
    void init(unsigned i);
};