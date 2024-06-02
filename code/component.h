#pragma once
#include "base.h"
#include <random>
class Actor;

class Component : public Base
{
protected:
    Actor *pOwner = nullptr;
public:
    virtual ~Component() {}
    virtual void Update() override;
    void setOwner(Actor *owner)
    {
        pOwner = owner;
    }
    virtual void Destruct();
};

int get_random(unsigned a = 1, unsigned b = 100);