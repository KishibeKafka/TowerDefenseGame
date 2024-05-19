#include "enemy_move.h"
#include "Engine/Vector2D.h"
#include "property.h"
#include <iostream>
void EnemyMove::move_to(Vector2D next)
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

void EnemyMove::Update()
{
    if (property->getStatus() == Moving)
    {
        if (step_counts == 0 && !property->getRoute().empty())
        {
            move_to(property->getRoute().front());
        }
        if (finished)
        {
            // 扣血
            std::cout << "Enemy Entered your HOME!\n";
            pOwner->Destroy();
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
            delta = Vector2D(property->getCurrentVelocity(), 0);
        else if (property->getDirection() == North)
            delta = Vector2D(0, property->getCurrentVelocity());
        else if (property->getDirection() == West)
            delta = Vector2D(-property->getCurrentVelocity(), 0);
        else
            delta = Vector2D(0, -property->getCurrentVelocity());
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