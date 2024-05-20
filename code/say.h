#pragma once
#include "actor.h"
#include "component.h"
#include "property.h"
#include "timer.h"
#include "world.h"
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
                << pOwner->getName() << " facing angle "
                << (pOwner->getComponentByClass< Property >()->getDirection())
                << "\n\n";
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
};