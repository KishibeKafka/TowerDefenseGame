#pragma once
#include "Engine/Vector2D.h"
#include "Engine/actor.h"
#include "Engine/component.h"
#include <queue>
#include <utility>
#include <vector>

#define PPU 32.0  // Pixel per Unit

enum Direction
{
    East = 0,
    North = 90,
    West = 180,
    South = 360
};

struct AttackRange
{
    // 相对于锚点
    Vector2D southwest;
    Vector2D northeast;
};

enum Status
{
    Moving = 0,
    Staying = 1,
    Attacking = 2,
    Dead = 3
};

class Property : public Component
{
private:
    unsigned id;
    int type;  // 0 tower 1 enemy
    double max_HP;
    double cur_HP;
    double max_DMG;
    double cur_DMG;
    double attack_interval;  // 单位: s

    double velocity;
    double cur_v;

    int cost;  // 建塔花费

    double collider_radius;  // 碰撞体积

    Status status;

    std::vector< AttackRange > attackRange;           // 攻击范围
    std::vector< AttackRange >::iterator range_iter;  // 迭代器
    std::queue< Vector2D > route;  // 路径节点，相对于地图
    Direction direction;           // 朝向
public:
    Property()
        : id(0), type(1), max_HP(100), cur_HP(100), max_DMG(10), cur_DMG(10),
          attack_interval(1), velocity(0.5 * PPU), cur_v(0), cost(0),
          collider_radius(PPU / 2), status(Moving), direction(East)
    {
        // set attackRange
        // set Route
        // set Collider
    }
    // Property(double mH, double mD, double ai, Direction dir = East)
    //     : max_HP(mH), cur_HP(max_HP), max_DMG(mD), cur_DMG(max_DMG),
    //       attack_interval(ai), direction(dir)
    // {
    // }
    ~Property()
    {
        attackRange.clear();
    }
    void Update()
    {
        if (status == Moving)
        {
            setCurrentVelocity(getVelocity());
        } else if (status == Staying)
        {
            setCurrentVelocity(0);
        } else if (status == Attacking)
        {
            setCurrentVelocity(0);
        } else if (status == Dead)
        {
            pOwner->Destroy();
        }
    }
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }

    void setID(unsigned i)
    {
        id = i;
    }
    unsigned getID()
    {
        return id;
    }
    void setType(int t)
    {
        type = t;
    }
    int getType()
    {
        return type;
    }
    void setMaxHP(double val)
    {
        max_HP = val;
    }
    void setCurHP(double val)
    {
        cur_HP = val;
    }
    void addHP(double delta)
    {
        cur_HP += delta;
    }
    void setMaxDMG(double val)
    {
        max_DMG = val;
    }
    void setCurDMG(double val)
    {
        cur_DMG = val;
    }
    double getMaxHP()
    {
        return max_HP;
    }
    double getCurHP()
    {
        return cur_HP;
    }
    double getMaxDMG()
    {
        return max_DMG;
    }
    double getCurDMG()
    {
        return cur_DMG;
    }
    void setAttackInterval(double ai)
    {
        attack_interval = ai;
    }
    double getAttackInterval()
    {
        return attack_interval;
    }
    void setDirection(Direction dir)
    {
        direction = dir;
    }
    Direction getDirection()
    {
        return direction;
    }
    void addAttackRange(AttackRange new_range)
    {
        attackRange.push_back(new_range);
    }
    std::vector< AttackRange > &getAttackRange()
    {
        return attackRange;
    }
    std::vector< AttackRange >::iterator getRangeIter()
    {
        return attackRange.begin();
    }
    void addRoutePoint(Vector2D p)
    {
        route.push(p);
    }
    std::queue< Vector2D > &getRoute()
    {
        return route;
    }

    void setVelocity(double v)
    {
        velocity = v;
    }
    double getVelocity()
    {
        return velocity;
    }
    void setCurrentVelocity(double v)
    {
        cur_v = v;
    }
    double getCurrentVelocity()
    {
        return cur_v;
    }
    void setCost(int c)
    {
        cost = c;
    }
    int getCost()
    {
        return cost;
    }
    void setRadius(double r)
    {
        collider_radius = r;
    }
    double getRadius()
    {
        return collider_radius;
    }

    void setStatus(Status s)
    {
        status = s;
    }
    Status getStatus()
    {
        return status;
    }
};