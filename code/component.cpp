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

int get_random(unsigned a, unsigned b)  // [1,100]
{
    std::default_random_engine e(std::random_device{}());
    std::uniform_int_distribution< int > dis(a, b);
    return dis(e);
}