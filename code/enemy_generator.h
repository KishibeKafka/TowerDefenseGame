#pragma once
#include "Vector2D.h"
#include "enemy.h"
#include "loader.h"
#include "property.h"
#include "saver.h"
#include "world.h"
#include <queue>
#include <utility>

extern World main_world;

struct EnemyUnit
{
    int enemy_id;
    double time_point;
    double curHP;
    double curDMG;
    double curVelocity;  // no ppu
    int i;
    int j;
    std::queue< Vector2D > route_point;  // no ppu
};

class EnemyGenerator
{
private:
    static std::queue< EnemyUnit > enemies_to_generate;
public:
    friend class Loader;
    friend class Saver;
    static void update()
    {
        if (!enemies_to_generate.empty() &&
            main_world.timer.getCurrrentTime().count() >=
                enemies_to_generate.front().time_point)
        {
            EnemyUnit unit = enemies_to_generate.front();
            Enemy *e = GameStatics::createActor< Enemy >(
                main_world.game_map->grids[unit.i][unit.j].getlocation());
            e->init(unit.enemy_id);
            Property *e_p = e->getComponentByClass< Property >();

            e_p->setCurHP(unit.curHP);
            e_p->setCurDMG(unit.curDMG);
            e_p->setCurrentVelocity(unit.curVelocity * PPU);
            while (!unit.route_point.empty())
            {
                e_p->addRoutePoint(main_world.game_map
                                       ->grids[unit.route_point.front().x]
                                              [unit.route_point.front().y]
                                       .getlocation());
                unit.route_point.pop();
            }
            enemies_to_generate.pop();
        }
    }
};