#include "enemy.h"
#include "property.h"

Enemy::Enemy()
{
    Base::setName("Enemy");
    constructComponent< Property >();
}

void Enemy::Update()
{
    Actor::Update();
}

void Enemy::init(unsigned i)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    property->setType(1);
    // ...
}