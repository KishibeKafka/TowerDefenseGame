#include "tower.h"
#include "property.h"

Tower::Tower()
{
    setName("Tower");
    constructComponent< Property >();
}

void Tower::Update()
{
    Actor::Update();
}

void Tower::init(unsigned i, bool is_e, double mH, double mD, double aI,
                 int mbn, int c)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    property->setType(false);
    property->setMaxHP(mH);
    property->setCurHP(mH);
    property->setMaxDMG(mD);
    property->setCurDMG(mD);
    property->setAttackInterval(aI);
    property->setVelocity(0);
    property->setCurrentVelocity(0);
    property->setMaxBlock(mbn);
    property->setCurrentBlock(mbn);
    property->setCost(c);
}