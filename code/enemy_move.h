#pragma once
#include "Vector2D.h"
#include "component.h"
#include "engine.h"
#include "property.h"
#include "world.h"
#include <iostream>
class EnemyMove : public Component
{
private:
    bool reached;
    bool finished;
    int step_counts;
public:
    Property *property;
    EnemyMove()
    {
        // DO NOT USE pOwner in Constructor!!! it is nullptr
    }
    void init()
    {
        property = pOwner->getComponentByClass< Property >();
        reached = false;
        finished = false;
        step_counts = 0;
    }
    void start_move()
    {
        property->setCurrentVelocity(property->getVelocity());
    }
    void stop_move()
    {
        property->setCurrentVelocity(0);
    }
    void turn_to(Direction dir)  // 转向
    {
        property->setDirection(dir);
    }
    void move_to(Vector2D next)
    {
        Vector2D now = pOwner->getWorldPosition();
        double angle = Vector2D::getAngle(now, next);
        if (angle <= 45 || angle > 315)
            turn_to(East);
        else if (angle <= 135)
            turn_to(North);
        else if (angle <= 225)
            turn_to(West);
        else
            turn_to(South);
    }

    ~EnemyMove() {}
    void Update()
    {
        if (property->getRoute().empty())
        {
            property->setCurrentVelocity(0);
            pOwner->Destroy();
        }
        if (property->getCurrentVelocity() > 0)
        {
            if (step_counts == 0 && !property->getRoute().empty())
            {
                move_to(property->getRoute().front());
            }
            if (finished)
            {
                // 扣血
                std::cout << "Enemy Entered your HOME!\n";
                property->setCurrentVelocity(0);
                pOwner->Destroy();
                // 结束
                Engine::end = true;
            }
            if (reached)
            {
                // pOwner->addPosition(property->getRoute().front() +
                //                     -pOwner->getWorldPosition());
                property->getRoute().pop();
                move_to(property->getRoute().front());
                reached = false;
            }
            Vector2D delta;
            if (property->getDirection() == East)
                delta = Vector2D(property->getCurrentVelocity() * PPU, 0);
            else if (property->getDirection() == North)
                delta = Vector2D(0, property->getCurrentVelocity() * PPU);
            else if (property->getDirection() == West)
                delta = Vector2D(-property->getCurrentVelocity() * PPU, 0);
            else
                delta = Vector2D(0, -property->getCurrentVelocity() * PPU);
            pOwner->addPosition(delta);

            if (Vector2D::Distance(pOwner->getWorldPosition(),
                                   property->getRoute().front()) < 0.1 * PPU)
            {
                reached = true;
                if (property->getRoute().size() == 1)
                    finished = true;
            }

            step_counts++;
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
};