#pragma once
#include "Engine/Vector2D.h"
#include "Engine/component.h"
#include "property.h"

class EnemyMove : public Component
{
private:
    bool reached;
    bool finished;
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
    }
    void start_move()
    {
        property->setCurrentVelocity(property->getVelocity());
    }
    void stop_move()
    {
        property->setCurrentVelocity(0);
    }
    bool on_move()  // 正在移动
    {
        return property->getCurrentVelocity() != 0;
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