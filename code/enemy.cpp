#include "enemy.h"
#include "Vector2D.h"

Enemy::Enemy()
{
    velocity_x = 5;
}

void Enemy::Update()
{
    root->addPosition(Vector2D(velocity_x * 0.001, 0));
    Actor::Update();
}