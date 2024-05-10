#pragma once
#include "actor.h"
#include "base.h"

class Component : public Base
{
protected:
    Actor *pOwner = nullptr;
public:
    virtual void Update() override;
    void setOwner(Actor *owner)
    {
        pOwner = owner;
    }
    virtual void Destruct();
};