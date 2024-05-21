#pragma once
#include "Vector2D.h"
#include "base.h"
#include "component.h"
#include "scene_component.h"
#include <stack>
#include <unordered_set>

class Actor : public Base
{
    // actor关系
public:
    std::unordered_set< Actor * > children;
    Actor *parent = nullptr;
    // 组件
    std::unordered_set< Component * > components;
    std::unordered_set< Component * >::iterator components_iter;
    SceneComponent *const root = new SceneComponent;
    Actor()
    {
        root->setOwner(this);
    }
    virtual ~Actor()
    {
        for (auto &compo : components)
        {
            delete compo;  // ~Component
        }
        delete root;
    }

    virtual void Update() override
    {
        components_iter = components.begin();
        for (; components_iter != components.end(); components_iter++)
        {
            (*components_iter)->Update();
        }
    }

    void attachTo(Actor *par);
    void detachFrom(Actor *par);

    void registerComponent(Component *pCom)
    {
        components.insert(pCom);
    }
    void UnregisterComponent(Component *pCom)
    {
        components_iter = components.erase(components.find(pCom));
    }

    template < typename T > T *constructComponent()
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

    template < typename T > T *getComponentByClass()
    {
        for (auto &com : components)
        {
            T *pCom = dynamic_cast< T * >(com);
            if (pCom)
                return pCom;
        }
        return nullptr;
    }

    // 删除对象 queue_free?
    void Destroy();

    Vector2D getLocalPosition() const
    {
        return root->getLocalPosition();
    }
    double getLocalRotation() const
    {
        return root->getLocalRotation();
    }
    Vector2D getLocalScale() const
    {
        return root->getLocalScale();
    }

    Vector2D getWorldPosition() const;
    double getWorldRotation() const;
    Vector2D getWorldScale() const;

    void setLocalPosition(const Vector2D &pos)
    {
        root->setLocalPosition(pos);
    }
    void setLocalRotation(double rot)
    {
        root->setLocalRotation(rot);
    }
    void setLocalScale(const Vector2D &sca)
    {
        root->setLocalScale(sca);
    }
    // 加值
    void addPosition(const Vector2D &pos)
    {
        root->addPosition(pos);
    }
    void addRotation(double rot)
    {
        root->addRotation(rot);
    }
};