#pragma once
#include "Engine/actor.h"
#include "property.h"

class Tower : public Actor
{
public:
    Tower();
    void Update();
    void init(unsigned i, bool is_e, double mH, double mD, double aI, int mbn,
              int c);
};