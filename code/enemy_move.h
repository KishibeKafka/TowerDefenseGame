#pragma once
#include "Vector2D.h"
#include "component.h"
#include "property.h"

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
        property = pOwner->constructComponent< Property >();
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
    void move_to(Vector2D next);  // 移动到世界坐标下一点

    ~EnemyMove() {}
    void Update();
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }
};