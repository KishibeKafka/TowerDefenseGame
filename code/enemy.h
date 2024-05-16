#pragma once
#include "Engine/Vector2D.h"
#include "property.h"

class Enemy : public Actor
{
public:
    Enemy();
    void Update();
    void init(unsigned i, bool is_e, double mH, double mD, double aI, double v,
              int mbn);
};