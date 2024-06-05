#pragma once
#include "actor.h"
#include "world.h"

extern World *main_world;

class Tower : public Actor
{
public:
    Tower();
    ~Tower()
    {
        int i = (int)(getWorldPosition().x / PPU + 0.5);
        int j = (int)(getWorldPosition().y / PPU + 0.5);
        main_world->game_map->grids[i][j].status = 0;  // 恢复地块状态
        main_world->game_map->grids[i][j].pTower = nullptr;
    }
    void Update();
    void init(unsigned i);
};