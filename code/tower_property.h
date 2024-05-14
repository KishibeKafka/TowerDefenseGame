#pragma once
#include "property.h"

class TowerProperty : public Property
{
private:
    int max_block_number;  // 最大可阻挡敌人数
    int current_block_number;
public:
    TowerProperty() : max_block_number(1), current_block_number(1) {}
    TowerProperty(double mH, double mD, double ai, int mb, Direction dir = East)
        : Property(mH, mD, ai, dir), max_block_number(mb),
          current_block_number(mb)
    {
    }
    ~TowerProperty();
    void Update() {}
    void Destruct()
    {
        pOwner->UnregisterComponent(this);
        delete this;
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
};