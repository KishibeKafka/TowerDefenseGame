#include "enemy.h"

Enemy::Enemy()
{
    constructComponent< EnemyProperty >();
}

void Enemy::Update()
{
    Actor::Update();
}