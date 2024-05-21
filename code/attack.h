#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "bullet.h"
#include "collider.h"
#include "component.h"
#include "property.h"
#include "timer.h"
#include "world.h"
#include <algorithm>

extern World main_world;

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
        {
            refugee->Destroy();
            main_world.enemy_number--;
        }
    }
    void distant_attack()
    {
        Actor *refugee = collider->getDetectedActors().at(0);
        for (auto &p_actor : collider->getDetectedActors())
        {
            if (Vector2D::Distance(p_actor->getWorldPosition(),
                                   p_actor->getComponentByClass< Property >()
                                       ->getRoute()
                                       .back()) <
                Vector2D::Distance(refugee->getWorldPosition(),
                                   refugee->getComponentByClass< Property >()
                                       ->getRoute()
                                       .back()))
                refugee = p_actor;
        }  // 先打距离家最近的
        Property *refugee_property = refugee->getComponentByClass< Property >();
        std::cout << pOwner->getName() << "distant attacked "
                  << refugee->getName() << '\n';
        refugee_property->addHP(-property->getCurDMG());
        if (refugee_property->getCurHP() <= 0)
        {
            refugee->Destroy();
            main_world.enemy_number--;
        }
        // GameStatics::createActor< Bullet >()->init(refugee,
        //                                            property->getCurDMG());
    }
};