#include "component.h"
#include "actor.h"

void Component::Update()
{
    ;
}

void Component::Destruct()
{
    pOwner->UnregisterComponent(this);
    delete this;
}