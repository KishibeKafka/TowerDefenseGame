#pragma once
#include "Vector2D.h"
#include "component.h"
#include "transform.h"
#include <unordered_set>

class SceneComponent : public Component
{
    Transform transform;

    std::unordered_set< SceneComponent * > children;  // 子场景
    SceneComponent *parent = nullptr;                 // 父场景
public:
    virtual void Update() override;
    virtual void Destruct() override;
    virtual void process_Destruct();
    // 组件相关
    // 设置所属组件
    void attachTo(SceneComponent *par);
    // 解除所属
    void detachFrom(SceneComponent *par);

    // transform相关
    Vector2D getLocalPosition() const
    {
        return transform.position;
    }
    double getLocalRotation() const
    {
        return transform.rotation;
    }
    Vector2D getLocalScale() const
    {
        return transform.scale;
    }

    Vector2D getWorldPosition() const;
    double getWorldRotation() const;
    Vector2D getWorldScale() const;
    // 设置transform
    void setLocalPosition(const Vector2D &pos)
    {
        transform.position = pos;
    }
    void setLocalRotation(double rot)
    {
        transform.rotation = rot;
    }
    void setLocalScale(const Vector2D &sca)
    {
        transform.scale = sca;
    }
    // 加值
    void addPosition(const Vector2D &pos)
    {
        transform.position += pos;
    }
    void addRotation(double rot)
    {
        transform.rotation += rot;
    }
};