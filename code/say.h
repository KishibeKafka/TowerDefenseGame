#pragma once
#include "Engine/actor.h"
#include "Engine/component.h"
#include <iostream>

class Say : public Component
{
public:
    ~Say() {}
    void Update()
    {
        if (pOwner)
        {
            std::cout << "Enemy at " << (pOwner->root)->getLocalPosition()
                      << '\n';
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
};