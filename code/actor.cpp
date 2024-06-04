#include "actor.h"
#include "Vector2D.h"
#include "world.h"

extern World main_world;

Vector2D Actor::getWorldPosition() const
{
    return getLocalPosition();
}
double Actor::getWorldRotation() const
{
    return getLocalRotation();
}
Vector2D Actor::getWorldScale() const
{
    return getLocalScale();
}

void Actor::Destroy()
{
    main_world.GameActors_to_delete.insert(this);
}