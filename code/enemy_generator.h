#pragma once
#include "Vector2D.h"
#include "enemy.h"
#include "property.h"
#include "world.h"
#include <queue>

struct EnemyUnit
{
    int enemy_id;
    double time_point;
    int i;
    int j;
    std::queue< Vector2D > route_point;
};

class EnemyGenerator
{
private:
    static std::queue< EnemyUnit > enemies_to_generate;
public:
    static void update()
    {
        if (main_world.timer.getCurrrentTime().count() >
            enemies_to_generate.front().time_point)
        {
            EnemyUnit unit = enemies_to_generate.front();
            Enemy *e = GameStatics::createActor< Enemy >(
                main_world.game_map->grids[unit.i][unit.j].getlocation());
            e->init(unit.enemy_id);
            while (!unit.route_point.empty())
            {
                e->getComponentByClass< Property >()->addRoutePoint(
                    unit.route_point.front());
                unit.route_point.pop();
            }
            enemies_to_generate.pop();
        }
    }

    static void init()
    {
        ;
    }
};