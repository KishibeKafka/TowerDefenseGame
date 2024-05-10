#include "component.h"

void Component::Destruct()
{
    pOwner->UnregisterComponent(this);
    delete this;
}