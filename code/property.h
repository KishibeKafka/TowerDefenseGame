#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "component.h"
#include <queue>
#include <string>
#include <utility>
#include <vector>

enum Direction
{
    East = 0,
    North = 90,
    West = 180,
    South = 270
};

struct AttackRange
{
    // 相对于锚点
    Vector2D southwest;
    Vector2D northeast;
};

enum BuffType
{
    Empty = 0,
    addHP,
    addDMG,
    addVelocity,
    quickAttack
};

class Property : public Component
{
private:
    int id;
    std::string name;
    int type;        // 0 tower 1 enemy
    int tower_type;  // 0 远战 1 近战
    double max_HP;
    double cur_HP;
    double max_DMG;
    double cur_DMG;
    double attack_interval;  // 单位: s

    double velocity;
    double cur_v;

    int cost;  // 建塔花费

    double collider_radius;  // 碰撞体积

    std::vector< AttackRange > attackRange;           // 攻击范围
    std::vector< AttackRange >::iterator range_iter;  // 迭代器
    std::queue< Vector2D > route;  // 路径节点，相对于地图
    Direction direction;           // 朝向
    BuffType buff;                 // 词缀
public:
    Property()
        : id(0), name("unkown"), type(1), tower_type(0), max_HP(100),
          cur_HP(100), max_DMG(20), cur_DMG(20), attack_interval(3),
          velocity(0.01), cur_v(0), cost(0), collider_radius(PPU / 2),
          direction(East), buff(Empty)
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
    void Update() {}
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }

    void setID(int i)
    {
        id = i;
    }
    int getID()
    {
        return id;
    }
    void setName(const std::string n)
    {
        name = n;
    }
    std::string getName()
    {
        return name;
    }

    void setType(int t)
    {
        type = t;
    }
    int getType()
    {
        return type;
    }

    void setTowerType(int t)
    {
        tower_type = t;
    }
    int getTowerType()
    {
        return tower_type;
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
    BuffType getBuff()
    {
        return buff;
    }
    void setBuff(BuffType b)
    {
        buff = b;
    }
};