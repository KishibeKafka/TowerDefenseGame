#pragma once
#include "base.h"

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