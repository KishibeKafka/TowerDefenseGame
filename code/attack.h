#pragma once
#include "Engine/actor.h"
#include "Engine/component.h"
#include "Engine/timer.h"
#include "collider.h"
#include "property.h"
#include <algorithm>

class Attack : public Component
{
private:
    Property *property;
    Collider *collider;
    Timer timer;
    double last_attack;
public:
    Attack() {}
    ~Attack() {}
    void Update()
    {
        if (timer.getCurrrentTime().count() - last_attack >
            property->getAttackInterval())
        {
            if (!collider->getCollidingActors().empty())
            {
                close_attack();
                last_attack = timer.getCurrrentTime().count();
            } else if (!collider->getDetectedActors().empty())
            {
                distant_attack();
                last_attack = timer.getCurrrentTime().count();
            }
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
    void init()
    {
        property = pOwner->getComponentByClass< Property >();
        collider = pOwner->getComponentByClass< Collider >();
        timer.start_timer();
        last_attack = 0;
    }

    void close_attack()
    {
        property->setStatus(Attacking);
        Actor *refugee = collider->getCollidingActors().at(0);
        for (auto &p_actor : collider->getCollidingActors())
        {
            if (p_actor->getComponentByClass< Property >()->getCurHP() <
                refugee->getComponentByClass< Property >()->getCurHP())
                refugee = p_actor;
        }  // 先打血量最少的
        auto refugee_property = refugee->getComponentByClass< Property >();
        std::cout << pOwner->getName() << "close attacked "
                  << refugee->getName() << '\n';
        refugee_property->addHP(-property->getCurDMG());
        if (refugee_property->getCurHP() <= 0)
            refugee_property->setStatus(Dead);
    }
    void distant_attack()
    {
        ;
    }
};