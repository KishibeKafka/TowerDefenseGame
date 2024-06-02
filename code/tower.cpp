#include "tower.h"
#include "attack.h"
#include "buff_manager.h"
#include "collider.h"
#include "loader.h"
#include "property.h"
#include "say.h"

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
    constructComponent< Attack >()->init();
    constructComponent< Say >();
    constructComponent< BuffManager >()->init();
}