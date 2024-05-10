#include "actor.h"
#include "Vector2D.h"
#include "component.h"
#include "world.h"
#include <stack>

template < typename T > T *Actor::constructComponent()
{
    T *pCom = new T;
    if (pCom && static_cast< Component * >(pCom))
    {
        pCom->setOwner(this);
        registerComponent(pCom);
        return pCom;
    }
    return nullptr;
}

template < typename T > T *Actor::getComponentByClass()
{
    for (auto &com : components)
    {
        T *pCom = dynamic_cast< T * >(com);
        if (pCom)
            return pCom;
    }
    return nullptr;
}

Vector2D Actor::getWorldPosition() const
{
    if (parent)
        return parent->getWorldPosition() + getLocalPosition();
    else
    {
        return getLocalPosition();
    }
}
double Actor::getWorldRotation() const
{
    if (parent)
        return parent->getWorldRotation() + getLocalRotation();
    else
        return getLocalRotation();
}
Vector2D Actor::getWorldScale() const
{
    if (parent)
        return parent->getWorldScale() + getLocalScale();
    else
        return getLocalScale();
}

void Actor::Destroy()
{
    if (parent)
        parent->children.erase(this);
    std::stack< Actor * > actors_to_delete;
    actors_to_delete.push(this);
    while (!actors_to_delete.empty())
    {
        Actor *current_actor = actors_to_delete.top();
        actors_to_delete.pop();
        if (!current_actor->children.empty())
        {
            for (auto &child : current_actor->children)
            {
                actors_to_delete.push(child);
            }
        }
        main_world.GameActors_to_delete.insert(current_actor);
    }
}