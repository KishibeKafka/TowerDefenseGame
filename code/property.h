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

class Property : public Component
{
private:
    unsigned id;
    bool is_enemy;
    double max_HP;
    double cur_HP;
    double max_DMG;
    double cur_DMG;
    double attack_interval;

    double velocity;
    double cur_v;

    int max_block_number;  // 最大可阻挡敌人数
    int current_block_number;

    int cost;  // 建塔花费

    std::vector< AttackRange > attackRange;           // 攻击范围
    std::vector< AttackRange >::iterator range_iter;  // 迭代器
    std::queue< Vector2D > route;  // 路径节点，相对于地图
    Direction direction;           // 朝向
public:
    Property()
        : id(0), is_enemy(true), max_HP(100), cur_HP(100), max_DMG(10),
          cur_DMG(10), attack_interval(1), velocity(0.5 * PPU), cur_v(0),
          max_block_number(1), current_block_number(0), cost(0), direction(East)
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

    void setID(unsigned i)
    {
        id = i;
    }
    unsigned getID()
    {
        return id;
    }
    void setType(bool is_e)
    {
        is_enemy = is_e;
    }
    bool getType()
    {
        return is_enemy;
    }
    void setMaxHP(double val)
    {
        max_HP = val;
    }
    void setCurHP(double val)
    {
        cur_HP = val;
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
    std::vector< AttackRange >::iterator getAttackRange()
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

    void setMaxBlock(int mb)
    {
        max_block_number = mb;
    }
    int getMaxBlock()
    {
        return max_block_number;
    }
    void setCurrentBlock(int cb)
    {
        current_block_number = cb;
    }
    int getCurrentBlock()
    {
        return current_block_number;
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
};