#pragma once
#include "actor.h"

class Enemy : public Actor
{
private:
    double velocity_x;
public:
    Enemy();
    void Update();
};