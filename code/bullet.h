#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "property.h"
#include "world.h"
#include <cmath>
#include <iostream>

extern World main_world;

class Bullet : public Actor
{
private:
    Actor *receiver;
    double damage;
    double bullet_velocity;
public:
    Bullet() {}
    ~Bullet() {}
    void Update()
    {
        if (main_world.GameActors.find(receiver) != main_world.GameActors.end())
        {
            Property *r_p = receiver->getComponentByClass< Property >();
            if (Vector2D::Distance(getWorldPosition(),
                                   receiver->getWorldPosition()) <
                r_p->getRadius() + bullet_velocity)
            {
                addPosition(receiver->getWorldPosition() + -getWorldPosition());
                r_p->addHP(damage);
                std::cout << "HIT!\n";
                if (r_p->getCurHP() <= 0)
                    receiver->Destroy();
                Destroy();
            } else
            {
                double angle = Vector2D::getAngle(getWorldPosition(),
                                                  receiver->getWorldPosition());
                Vector2D delta(bullet_velocity * cos(angle),
                               bullet_velocity * sin(angle));
                addPosition(delta);
            }

        } else
        {
            Destroy();
        }
    }

    void init(Actor *r, double d)
    {
        receiver = r;
        damage = d;
        bullet_velocity = 10 * PPU;
    }
};