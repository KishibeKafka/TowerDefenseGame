#pragma once
#include "property.h"

class EnemyProperty : public Property
{
private:
    double velocity;
    bool blocked;      // 是否被阻挡
    int block_number;  // 需要多少阻挡值
public:
    EnemyProperty()
    {
        velocity = PPU;
        blocked = false;
        block_number = 1;
    }
    EnemyProperty(double mH, double mD, double ai, double v, bool b, int bn,
                  Direction dir = East)
        : Property(mH, mD, ai, dir), velocity(v), blocked(b), block_number(bn)
    {
    }
    ~EnemyProperty() {}
    void Update() {}
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
    }

    void setBlocked(bool b)
    {
        blocked = b;
    }
    bool getBlocked()
    {
        return blocked;
    }
    void setBlockNumber(int bn)
    {
        block_number = bn;
    }
    int getBlockNumber()
    {
        return block_number;
    }
};