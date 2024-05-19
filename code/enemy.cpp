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

void Enemy::init(unsigned i, double mH, double mD, double aI, double v)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    property->setType(1);
    property->setMaxHP(mH);
    property->setCurHP(mH);
    property->setMaxDMG(mD);
    property->setCurDMG(mD);
    property->setAttackInterval(aI);
    property->setVelocity(v);
    property->setCurrentVelocity(0);
}