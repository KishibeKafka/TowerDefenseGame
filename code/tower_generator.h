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
            t->init(unit.tower_id);
            Property *t_p = t->getComponentByClass< Property >();
            t_p->setCurHP(unit.curHP);
            t_p->setCurDMG(unit.curDMG);
            t_p->setDirection(unit.direction);
            t_p->setBuff(unit.buff);
            existing_towers.pop();
        }
    }
    static void build_tower(int id, int i, int j, int dir)
    {
        Tower *tower = GameStatics::createActor< Tower >(
            main_world.game_map->grids[i][j].getlocation());
        tower->init(id);
        tower->getComponentByClass< Property >()->setDirection((Direction)dir);
        main_world.current_cost -= 100;
        main_world.game_map->grids[i][j].status = 1;  // 改变地块状态
        main_world.game_map->grids[i][j].pTower = tower;
        std::cout << "Tower Built!\n";
    }
    static void input(int _id, int i, int j, int dir)
    {
        if (i <= 0 || i > main_world.game_map->size_x || j <= 0 ||
            j > main_world.game_map->size_y)
            return;
        int id = _id;
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
                return;
            }
            build_tower(id, i, j, dir);
            break;
        case 2:
            if (main_world.current_cost < 200)
                return;
            if (main_world.game_map->grids[i][j].type == 0 ||
                main_world.game_map->grids[i][j].type == 1 ||
                main_world.game_map->grids[i][j].status == 1)
                return;
            build_tower(id, i, j, dir);
            break;
        default: std::cout << "no such tower id!\n"; return;
        }
    }
};