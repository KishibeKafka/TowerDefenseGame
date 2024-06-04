#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "component.h"
#include "property.h"
#include "timer.h"
#include "world.h"
#include <algorithm>
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
    Timer timer;
    double last_attack;
public:
    Collider() {}
    ~Collider() {}
    void init()
    {
        property = pOwner->getComponentByClass< Property >();
        timer.start_timer();
        last_attack = 0;
        if (property->getType() == 0)  // tower
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
        Attack();
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }

    bool in_range(Actor *pactor)
    {
        if (main_world.GameActors_to_delete.find(pactor) !=
                main_world.GameActors_to_delete.end() ||
            pactor == nullptr || !pactor->alive)
            return false;
        auto it = property->getRangeIter();
        while (it != property->getAttackRange().end())
        {
            Vector2D real_southwest(
                pOwner->getWorldPosition() +
                Vector2D::Rotate(property->getDirection(), it->southwest) +
                Vector2D(
                    -pactor->getComponentByClass< Property >()->getRadius(),
                    -pactor->getComponentByClass< Property >()->getRadius()));
            Vector2D real_northeast(
                pOwner->getWorldPosition() +
                Vector2D::Rotate(property->getDirection(), it->northeast) +
                Vector2D(
                    pactor->getComponentByClass< Property >()->getRadius(),
                    pactor->getComponentByClass< Property >()->getRadius()));

            if ((pactor->getWorldPosition().x - real_southwest.x) *
                        (pactor->getWorldPosition().x - real_northeast.x) <
                    0 &&
                (pactor->getWorldPosition().y - real_southwest.y) *
                        (pactor->getWorldPosition().y - real_northeast.y) <
                    0)
            {
                return true;
            }
            it++;
        }
        return false;
    }
    void close_attack()
    {
        Actor *refugee = nullptr;
        for (auto pactor : collidingActors)
        {
            if (main_world.GameActors.find(pactor) !=
                    main_world.GameActors.end() &&
                pactor && pactor->alive)
            {
                refugee = pactor;
                break;
            }
        }
        if (refugee == nullptr)
            return;
        for (auto &p_actor : getCollidingActors())
        {
            if (main_world.GameActors.find(p_actor) ==
                    main_world.GameActors.end() ||
                p_actor == nullptr || !p_actor->alive)
                continue;
            if (p_actor->getComponentByClass< Property >()->getCurHP() <
                refugee->getComponentByClass< Property >()->getCurHP())
                refugee = p_actor;
        }  // 先打血量最少的
        auto refugee_property = refugee->getComponentByClass< Property >();
        refugee_property->addHP(-property->getCurDMG());

        main_world.world_render.signals_to_draw.push_back(
            {pOwner->getWorldPosition().x, pOwner->getWorldPosition().y,
             refugee->getWorldPosition().x, refugee->getWorldPosition().y,
             main_world.timer.getCurrrentTime().count() + 0.1});

        if (refugee_property->getCurHP() <= 0)
        {
            main_world.number_of_buff[refugee_property->getBuff()]++;
            refugee->alive = false;
            refugee->Destroy();
        }
    }
    void distant_attack()
    {
        Actor *refugee = nullptr;
        for (auto pactor : detectedActors)
        {
            if (main_world.GameActors.find(pactor) !=
                    main_world.GameActors.end() &&
                pactor && pactor->alive)
            {
                refugee = pactor;
                break;
            }
        }
        if (refugee == nullptr)
            return;
        for (auto &p_actor : getDetectedActors())
        {
            if (main_world.GameActors.find(p_actor) ==
                    main_world.GameActors.end() ||
                p_actor == nullptr || !p_actor->alive)
                continue;
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

        main_world.world_render.signals_to_draw.push_back(
            {pOwner->getWorldPosition().x, pOwner->getWorldPosition().y,
             refugee->getWorldPosition().x, refugee->getWorldPosition().y,
             main_world.timer.getCurrrentTime().count() + 0.1});

        refugee_property->addHP(-property->getCurDMG());
        if (refugee_property->getCurHP() <= 0)
        {
            main_world.number_of_buff[refugee_property->getBuff()]++;
            refugee->alive = false;
            refugee->Destroy();
        }
    }
    void Attack()
    {
        if (timer.getCurrrentTime().count() - last_attack >
            property->getAttackInterval())
        {
            if (!getCollidingActors().empty())
            {
                close_attack();
                last_attack = timer.getCurrrentTime().count();
            } else if (!getDetectedActors().empty())
            {
                distant_attack();
                last_attack = timer.getCurrrentTime().count();
            }
        }
    }
    void Recycle()
    {
        // 回收已经死掉的actor
        for (auto iter = collidingActors.begin();
             iter != collidingActors.end();)
        {
            if (main_world.GameActors.find(*iter) ==
                    main_world.GameActors.end() ||
                (*iter) == nullptr || !(*iter)->alive)
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
                    main_world.GameActors.end() ||
                (*iter) == nullptr || !(*iter)->alive)
                iter = detectedActors.erase(iter);
            else
            {
                if (!in_range(*iter))
                {
                    iter = detectedActors.erase(iter);
                } else
                    iter++;
            }
        }
    }

    void detectCollide()
    {
        for (auto &actor : main_world.GameActors)
        {
            if (main_world.GameActors_to_delete.find(actor) !=
                    main_world.GameActors_to_delete.end() ||
                actor == nullptr || !actor->alive)
            {
                continue;
            }
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
            if (main_world.GameActors_to_delete.find(actor) !=
                    main_world.GameActors_to_delete.end() ||
                actor == nullptr || !actor->alive)
            {
                continue;
            }
            Collider *other = actor->getComponentByClass< Collider >();
            if (other && other->getLayer() == detectlayer)
            {
                bool find = false;
                if (!detectedActors.empty())
                {
                    for (auto &d_actors : detectedActors)
                    {
                        if (d_actors == actor)
                        {
                            find = true;
                        }
                    }
                }
                if (find)
                    continue;

                if (in_range(actor))
                    detectedActors.push_back(actor);
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
    void setLayer(int l)
    {
        layer = l;
    }
    void setDetectLayer(int dl)
    {
        detectlayer = dl;
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