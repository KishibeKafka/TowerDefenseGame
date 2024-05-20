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

void Tower::init(unsigned i)
{
    Property *property = getComponentByClass< Property >();
    property->setID(i);
    property->setType(0);
    property->setVelocity(0);
    property->setCurrentVelocity(0);
}