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

    static void input()
    {
        // if (std::cin.get() == 1)
        // {
        //     std::cout << "enter tower id: ";
        //     int id = 0;
        //     std::cin >> id;
        //     int i = 1, j = 1;
        //     int dir = 0;
        //     Tower *tower;
        //     switch (id)
        //     {
        //     case 1:
        //         if (main_world.current_cost < 100)
        //         {
        //             std::cout << "you dont have enough cost!\n";
        //             return;
        //         }
        //         std::cout << "enter x and y: ";
        //         std::cin >> i >> j;
        //         if (main_world.game_map->grids[i][j].type == 0 ||
        //             main_world.game_map->grids[i][j].type == 2 ||
        //             main_world.game_map->grids[i][j].status == 1)
        //         {
        //             std::cout << "cannot build here!\n";
        //             return;
        //         }
        //         main_world.game_map->grids[i][j].status = 1;  // 改变地块状态
        //         std::cout << "enter direction(0,90,180,360):";
        //         std::cin >> dir;
        //         tower = GameStatics::createActor< Tower >(
        //             main_world.game_map->grids[i][j].getlocation());
        //         tower->init(i);
        //         tower->getComponentByClass< Property >()->setDirection(
        //             (Direction)dir);
        //         std::cout << "Tower Built!\n";
        //         break;
        //     default: std::cout << "no such tower id!\n"; return;
        //     }
        // }
    }
};