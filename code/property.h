#pragma once
#include "Engine/Vector2D.h"
#include "Engine/actor.h"
#include "Engine/component.h"
#include <utility>
#include <vector>

#define PPU 32.0;  // Pixel per Unit

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
    double max_HP;
    double cur_HP;
    double max_DMG;
    double cur_DMG;
    double attack_interval;

    std::vector< AttackRange > attackRange;           // 攻击范围
    std::vector< AttackRange >::iterator range_iter;  // 迭代器
    Direction direction;                              // 朝向
public:
    Property()
        : max_HP(100), cur_HP(100), max_DMG(10), cur_DMG(10),
          attack_interval(1), direction(East)
    {
        // set attackRange
    }
    Property(double mH, double mD, double ai, Direction dir = East)
        : max_HP(mH), cur_HP(max_HP), max_DMG(mD), cur_DMG(max_DMG),
          attack_interval(ai), direction(dir)
    {
    }
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
        range_iter = attackRange.begin();
        return range_iter;
    }
};