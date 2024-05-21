#pragma once
#include "Vector2D.h"
#include "loader.h"
#include "property.h"
#include "tower.h"
#include "world.h"
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
        ;
    }
};