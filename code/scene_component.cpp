#include "scene_component.h"
#include "Vector2D.h"
#include "actor.h"

Vector2D SceneComponent::getWorldPosition() const
{
    if (parent)
        return parent->getWorldPosition() + getLocalPosition();
    else
    {
        if (pOwner)
            return pOwner->getWorldPosition();
        else
            return getLocalPosition();
    }
}

double SceneComponent::getWorldRotation() const
{
    if (parent)
        return parent->getWorldRotation() + getLocalRotation();
    else
    {
        if (pOwner)
            return pOwner->getWorldRotation();
        else
            return getLocalRotation();
    }
}

Vector2D SceneComponent::getWorldScale() const
{
    if (parent)
        return parent->getWorldScale() * getWorldScale();
    else
    {
        if (pOwner)
            return pOwner->getWorldScale();
        else
            return getLocalScale();
    }
}

void SceneComponent::attachTo(SceneComponent *par)
{
    if (par)
    {
        par->children.insert(this);
        parent = par;
        setOwner(par->pOwner);
    }
}

void SceneComponent::detachFrom(SceneComponent *par)
{
    // find or not ?
    if (par)
    {
        par->children.erase(this);
        parent = nullptr;
    }
}

void SceneComponent::process_Destruct()
{
    if (!children.empty())
    {
        for (auto &child : children)
            child->process_Destruct();  // 递归销毁
    }
    Component::Destruct();
}

void SceneComponent::Destruct()
{
    if (parent)
        parent->children.erase(this);
    process_Destruct();
}

void SceneComponent::Update()
{
    ;
}