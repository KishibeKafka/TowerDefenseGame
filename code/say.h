#pragma once
#include "Engine/actor.h"
#include "Engine/component.h"
#include "Engine/timer.h"
#include "Engine/world.h"
#include "property.h"
#include <chrono>
#include <iostream>
class Say : public Component
{
public:
    ~Say() {}
    void Update()
    {
        if (pOwner)
        {
            std::cout << "time at :"
                      << main_world.timer.getCurrrentTime().count() << '\n';
            std::cout << pOwner->getName() << " at "
                      << pOwner->getWorldPosition() << '\n';
            std::cout
                << "Enemy facing angle "
                << (pOwner->getComponentByClass< Property >()->getDirection())
                << '\n';
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
};