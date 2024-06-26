#include "tower.h"
#include "buff_manager.h"
#include "collider.h"
#include "loader.h"
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
    Loader::getTower(i, property);
    constructComponent< Collider >()->init();
    constructComponent< BuffManager >()->init();
}