#include "enemy.h"
#include "property.h"

Enemy::Enemy()
{
    constructComponent< Property >();
}

void Enemy::Update()
{
    Actor::Update();
}

void Enemy::init(unsigned i, bool is_e, double mH, double mD, double aI,
                 double v, int mbn)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    property->setType(true);
    property->setMaxHP(mH);
    property->setCurHP(mH);
    property->setMaxDMG(mD);
    property->setCurDMG(mD);
    property->setAttackInterval(aI);
    property->setVelocity(v);
    property->setCurrentVelocity(0);
    property->setMaxBlock(mbn);
    property->setCurrentBlock(mbn);
}