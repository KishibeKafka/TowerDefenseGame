#include "saver.h"
#include "Vector2D.h"
#include <queue>

void Saver::save(std::string filename)
{
    FILE *fp = fopen(filename.c_str(), "wb");
    if (!fp)
        exit(-1);
    char writeBuffer[65536];
    rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer< rapidjson::FileWriteStream > writer(os);

    rapidjson::Document document;
    document.SetObject();

    int size_x = 10, size_y = 10;
    size_x = main_world.game_map->size_x;
    size_y = main_world.game_map->size_y;
    double current_time = main_world.timer.getCurrrentTime().count();
    int enemy_number = main_world.enemy_number;
    int current_cost = main_world.current_cost;

    rapidjson::Document::AllocatorType &allo = document.GetAllocator();
    rapidjson::Value size_j(rapidjson::kArrayType);
    size_j.PushBack(size_x, allo);
    size_j.PushBack(size_y, allo);
    document.AddMember("size", size_j, allo);
    document.AddMember("current_time", 0, allo);
    document.AddMember("enemy_number", enemy_number, allo);
    document.AddMember("current_cost", current_cost, allo);

    rapidjson::Value paths(rapidjson::kArrayType);
    for (int i = 0; i < main_world.game_map->paths.size(); i++)
    {
        Path &p = main_world.game_map->paths[i];
        rapidjson::Value pairs(rapidjson::kArrayType);
        rapidjson::Value first(rapidjson::kArrayType);
        rapidjson::Value second(rapidjson::kArrayType);
        first.PushBack(p.x1, allo);
        first.PushBack(p.y1, allo);
        second.PushBack(p.x2, allo);
        second.PushBack(p.y2, allo);
        pairs.PushBack(first, allo);
        pairs.PushBack(second, allo);
        paths.PushBack(pairs, allo);
    }
    document.AddMember("path", paths, allo);

    rapidjson::Value highplaces(rapidjson::kArrayType);
    for (int i = 0; i < main_world.game_map->highplaces.size(); i++)
    {
        HighPlace &h = main_world.game_map->highplaces[i];
        rapidjson::Value pairs(rapidjson::kArrayType);
        rapidjson::Value first(rapidjson::kArrayType);
        rapidjson::Value second(rapidjson::kArrayType);
        first.PushBack(h.x1, allo);
        first.PushBack(h.y1, allo);
        second.PushBack(h.x2, allo);
        second.PushBack(h.y2, allo);
        pairs.PushBack(first, allo);
        pairs.PushBack(second, allo);
        highplaces.PushBack(pairs, allo);
    }
    document.AddMember("highplace", highplaces, allo);

    rapidjson::Value enemies(rapidjson::kArrayType);
    for (auto &p_a : main_world.GameActors)
    {
        if (p_a == nullptr || !p_a->alive)
            continue;
        Property *e_p = p_a->getComponentByClass< Property >();
        if (e_p->getType() == 1)
        {
            std::queue< Vector2D > temp = e_p->getRoute();
            std::queue< Vector2D > enemy_route;
            while (!temp.empty())
            {
                enemy_route.push(Vector2D((int)(temp.front().x / PPU + 0.5),
                                          (int)(temp.front().y / PPU + 0.5)));
                temp.pop();
            }
            EnemyUnit unit = {e_p->getID(),
                              0,
                              e_p->getCurHP(),
                              e_p->getCurDMG(),
                              e_p->getCurrentVelocity(),
                              (int)(p_a->getWorldPosition().x / PPU + 0.5),
                              (int)(p_a->getWorldPosition().y / PPU + 0.5),
                              enemy_route,
                              e_p->getBuff()};
            rapidjson::Value enemy(rapidjson::kObjectType);
            enemy.AddMember("id", unit.enemy_id, allo);
            enemy.AddMember("spawn_time", 0, allo);
            rapidjson::Value spawn_position(rapidjson::kArrayType);
            spawn_position.PushBack(unit.i, allo);
            spawn_position.PushBack(unit.j, allo);
            enemy.AddMember("spawn_position", spawn_position, allo);
            enemy.AddMember("curHP", unit.curHP, allo);
            enemy.AddMember("curDMG", unit.curDMG, allo);
            enemy.AddMember("curVelocity", unit.curVelocity, allo);
            rapidjson::Value route(rapidjson::kArrayType);
            while (!unit.route_point.empty())
            {
                rapidjson::Value point(rapidjson::kArrayType);
                point.PushBack((int)unit.route_point.front().x, allo);
                point.PushBack((int)unit.route_point.front().y, allo);
                route.PushBack(point, allo);
                unit.route_point.pop();
            }
            enemy.AddMember("route", route, allo);
            enemy.AddMember("buff", (int)unit.buff, allo);
            enemies.PushBack(enemy, allo);
        }
    }

    while (!EnemyGenerator::enemies_to_generate.empty())
    {
        EnemyUnit &unit = EnemyGenerator::enemies_to_generate.front();
        unit.time_point -= current_time;
        rapidjson::Value enemy(rapidjson::kObjectType);
        enemy.AddMember("id", unit.enemy_id, allo);
        enemy.AddMember("spawn_time", unit.time_point, allo);
        rapidjson::Value spawn_position(rapidjson::kArrayType);
        spawn_position.PushBack(unit.i, allo);
        spawn_position.PushBack(unit.j, allo);
        enemy.AddMember("spawn_position", spawn_position, allo);
        enemy.AddMember("curHP", unit.curHP, allo);
        enemy.AddMember("curDMG", unit.curDMG, allo);
        enemy.AddMember("curVelocity", unit.curVelocity, allo);
        rapidjson::Value route(rapidjson::kArrayType);
        while (!unit.route_point.empty())
        {
            rapidjson::Value point(rapidjson::kArrayType);
            point.PushBack(static_cast< int >(unit.route_point.front().x),
                           allo);
            point.PushBack(static_cast< int >(unit.route_point.front().y),
                           allo);
            route.PushBack(point, allo);
            unit.route_point.pop();
        }
        enemy.AddMember("route", route, allo);
        enemy.AddMember("buff", (int)unit.buff, allo);
        enemies.PushBack(enemy, allo);
        EnemyGenerator::enemies_to_generate.pop();
    }
    document.AddMember("enemies", enemies, allo);

    rapidjson::Value towers(rapidjson::kArrayType);
    for (auto &p_a : main_world.GameActors)
    {
        if (p_a == nullptr || !p_a->alive)
            continue;
        Property *t_p = p_a->getComponentByClass< Property >();
        if (t_p->getType() == 0)
        {
            TowerUnit unit = {t_p->getID(),
                              t_p->getCurHP(),
                              t_p->getCurDMG(),
                              (int)(p_a->getWorldPosition().x / PPU + 0.5),
                              (int)(p_a->getWorldPosition().y / PPU + 0.5),
                              t_p->getDirection(),
                              t_p->getBuff()};
            rapidjson::Value tower(rapidjson::kObjectType);
            tower.AddMember("id", unit.tower_id, allo);
            rapidjson::Value spawn_position(rapidjson::kArrayType);
            spawn_position.PushBack(unit.i, allo);
            spawn_position.PushBack(unit.j, allo);
            tower.AddMember("spawn_position", spawn_position, allo);
            tower.AddMember("direction", unit.direction, allo);
            tower.AddMember("curHP", unit.curHP, allo);
            tower.AddMember("curDMG", unit.curDMG, allo);
            tower.AddMember("buff", unit.buff, allo);
            towers.PushBack(tower, allo);
        }
    }
    document.AddMember("towers", towers, allo);

    document.Accept(writer);
    fclose(fp);
}