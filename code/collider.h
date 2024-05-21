#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "component.h"
#include "property.h"
#include "world.h"
#include <iostream>
#include <vector>

extern World main_world;

class Collider : public Component  // 这边就只用圆形的
{
private:
    int detectlayer;  // 可以检测到的层
    int layer;        // 自身所处层
    std::vector< Actor * > collidingActors;
    std::vector< Actor * > detectedActors;
    Property *property;
public:
    Collider() {}
    ~Collider() {}
    void init()
    {
        property = pOwner->getComponentByClass< Property >();
        if (property->getType() == 0)
        {
            layer = 0;
            detectlayer = 1;
        } else if (property->getType() == 1)
        {
            layer = 1;
            detectlayer = 0;
        }
        // ...
    }
    void Update()
    {
        detectCollide();
        detectActor();
        Recycle();
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }

    void Recycle()
    {
        // 回收已经死掉的actor
        for (auto iter = collidingActors.begin();
             iter != collidingActors.end();)
        {
            if (main_world.GameActors.find(*iter) ==
                main_world.GameActors.end())
                iter = collidingActors.erase(iter);
            else
                iter++;
        }
        // 恢复速度
        if (collidingActors.empty())
            property->setCurrentVelocity(property->getVelocity());

        for (auto iter = detectedActors.begin(); iter != detectedActors.end();)
        {
            if (main_world.GameActors.find(*iter) ==
                main_world.GameActors.end())
                iter = detectedActors.erase(iter);
            else
                iter++;
        }
    }

    void detectCollide()
    {
        for (auto &actor : main_world.GameActors)
        {
            Collider *other = actor->getComponentByClass< Collider >();
            if (other && other->getLayer() == detectlayer)
            {
                // 排除已有的碰撞对象
                bool find = false;
                if (!collidingActors.empty())
                {
                    for (auto &c_actors : collidingActors)
                    {
                        if (c_actors == actor)
                            find = true;
                    }
                }
                if (find)
                    continue;

                if (Vector2D::Distance(pOwner->getWorldPosition(),
                                       other->pOwner->getWorldPosition()) <=
                    property->getRadius() + other->property->getRadius())
                {
                    std::cout << pOwner->getName() << " Collding "
                              << actor->getName() << '\n';
                    collidingActors.push_back(actor);
                    property->setCurrentVelocity(0);
                }
            }
        }
    }
    void detectActor()
    {
        for (auto &actor : main_world.GameActors)
        {
            Collider *other = actor->getComponentByClass< Collider >();
            if (other && other->getLayer() == detectlayer)
            {
                bool find = false;
                if (!detectedActors.empty())
                {
                    for (auto &d_actors : detectedActors)
                    {
                        if (d_actors == actor)
                            find = true;
                    }
                }
                if (find)
                    continue;

                auto it = property->getRangeIter();
                while (it != property->getAttackRange().end())
                {
                    Vector2D real_southwest(
                        pOwner->getWorldPosition() +
                        Vector2D::Rotate(property->getDirection(),
                                         it->southwest) +
                        Vector2D(-other->property->getRadius(),
                                 -other->property->getRadius()));
                    Vector2D real_northeast(
                        pOwner->getWorldPosition() +
                        Vector2D::Rotate(property->getDirection(),
                                         it->northeast) +
                        Vector2D(other->property->getRadius(),
                                 other->property->getRadius()));

                    if ((actor->getWorldPosition().x - real_southwest.x) *
                                (actor->getWorldPosition().x -
                                 real_northeast.x) <
                            0 &&
                        (actor->getWorldPosition().y - real_southwest.y) *
                                (actor->getWorldPosition().y -
                                 real_northeast.y) <
                            0)
                    {
                        detectedActors.push_back(actor);
                    }
                    it++;
                }
            }
        }
    }

    int getLayer()
    {
        return layer;
    }
    int getDetectLayer()
    {
        return detectlayer;
    }
    std::vector< Actor * > &getCollidingActors()
    {
        return collidingActors;
    }
    std::vector< Actor * > &getDetectedActors()
    {
        return detectedActors;
    }
};