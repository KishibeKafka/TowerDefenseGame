#pragma once
#include "Vector2D.h"
#include "loader.h"
#include "property.h"
#include "tower.h"
#include "world.h"
#include <iostream>
#include <queue>
#include <utility>

struct TowerUnit
{
    int tower_id;
    double curHP;
    double curDMG;
    int i;
    int j;
    Direction direction;
    BuffType buff;
};

extern World main_world;

class TowerGenerator
{
private:
    static std::queue< TowerUnit > existing_towers;
public:
    friend class Loader;
    static void init()
    {
        while (!existing_towers.empty())
        {
            TowerUnit unit = existing_towers.front();
            Tower *t = GameStatics::createActor< Tower >(
                main_world.game_map->grids[unit.i][unit.j].getlocation());
            Property *t_p = t->getComponentByClass< Property >();
            t_p->setCurHP(unit.curHP);
            t_p->setCurDMG(unit.curDMG);
            t_p->setDirection(unit.direction);
            existing_towers.pop();
        }
    }

    static void input(int _id, int i, int j, int dir)
    {
        if (i <= 0 || i > main_world.game_map->size_x || j <= 0 ||
            j > main_world.game_map->size_y)
            return;
        int id = _id;
        Tower *tower;
        switch (id)
        {
        case 1:
            if (main_world.current_cost < 100)
            {
                return;
            }
            if (main_world.game_map->grids[i][j].type == 0 ||
                main_world.game_map->grids[i][j].type == 2 ||
                main_world.game_map->grids[i][j].status == 1)
            {
                std::cout << "cannot build here!\n";
                return;
            }
            main_world.game_map->grids[i][j].status = 1;  // 改变地块状态
            tower = GameStatics::createActor< Tower >(
                main_world.game_map->grids[i][j].getlocation());
            tower->init(id);
            tower->getComponentByClass< Property >()->setDirection(
                (Direction)dir);
            main_world.current_cost -= 100;
            std::cout << "Tower Built!\n";
            break;
        default: std::cout << "no such tower id!\n"; return;
        }
    }
};