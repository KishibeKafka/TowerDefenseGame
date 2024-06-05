#include "loader.h"
#include "property.h"
#include "rapidjson/document.h"
#include "rapidjson/rapidjson.h"
#include "world.h"

void Loader::getEnemy(int id, Property *e_p)
{
    rapidjson::Document document;
    FILE *fp = fopen("..\\resources\\data\\property.json", "rb");
    if (!fp)
        exit(-2);
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    document.ParseStream(is);
    fclose(fp);
    const rapidjson::Value &enemies = document["enemy"];
    for (rapidjson::SizeType i = 0; i < enemies.Size(); i++)
    {
        if (enemies[i]["id"].GetInt() == id)
        {
            const rapidjson::Value &e = enemies[i];
            e_p->setType(1);
            e_p->setName(e["name"].GetString());
            e_p->setMaxHP(e["maxHP"].GetDouble());
            e_p->setMaxDMG(e["maxDMG"].GetDouble());
            e_p->setCurHP(e_p->getMaxHP());
            e_p->setCurDMG(e_p->getMaxDMG());
            e_p->setAttackInterval(e["attack_interval"].GetDouble());
            e_p->setVelocity(e["velocity"].GetDouble());
            e_p->setCurrentVelocity(e_p->getVelocity());
            e_p->setRadius(e["radius"].GetDouble() * PPU);
            const rapidjson::Value &range = e["attack_range"];
            for (rapidjson::SizeType i = 0; i < range.Size(); i++)
            {
                double x1 = range[i][0][0].GetDouble() * PPU;
                double y1 = range[i][0][1].GetDouble() * PPU;
                double x2 = range[i][1][0].GetDouble() * PPU;
                double y2 = range[i][1][1].GetDouble() * PPU;
                e_p->addAttackRange({Vector2D(x1, y1), Vector2D(x2, y2)});
            }
        }
    }
}
void Loader::getTower(int id, Property *t_p)
{
    rapidjson::Document document;
    FILE *fp = fopen("..\\resources\\data\\property.json", "rb");
    if (!fp)
        exit(-2);
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    document.ParseStream(is);
    fclose(fp);
    const rapidjson::Value &towers = document["tower"];
    for (rapidjson::SizeType i = 0; i < towers.Size(); i++)
    {
        if (towers[i]["id"].GetInt() == id)
        {
            const rapidjson::Value &t = towers[i];
            t_p->setType(0);
            t_p->setName(t["name"].GetString());
            t_p->setTowerType(t["tower_type"].GetInt());
            t_p->setMaxHP(t["maxHP"].GetDouble());
            t_p->setMaxDMG(t["maxDMG"].GetDouble());
            t_p->setCurHP(t_p->getMaxHP());
            t_p->setCurDMG(t_p->getMaxDMG());
            t_p->setAttackInterval(t["attack_interval"].GetDouble());
            t_p->setVelocity(0);
            t_p->setCurrentVelocity(0);
            t_p->setRadius(t["radius"].GetDouble() * PPU);
            t_p->setCost(t["cost"].GetInt());
            const rapidjson::Value &range = t["attack_range"];
            for (rapidjson::SizeType i = 0; i < range.Size(); i++)
            {
                double x1 = range[i][0][0].GetDouble() * PPU;
                double y1 = range[i][0][1].GetDouble() * PPU;
                double x2 = range[i][1][0].GetDouble() * PPU;
                double y2 = range[i][1][1].GetDouble() * PPU;
                t_p->addAttackRange({Vector2D(x1, y1), Vector2D(x2, y2)});
            }
        }
    }
}
void Loader::loadSave(std::string filename)
{
    rapidjson::Document document;
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp)
        exit(-2);
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    document.ParseStream(is);
    fclose(fp);
    main_world->game_map =
        new GameMap(document["size"][0].GetInt(), document["size"][1].GetInt());
    main_world->enemy_number = document["enemy_number"].GetInt();
    main_world->current_cost = document["current_cost"].GetInt();

    const rapidjson::Value &buffs = document["buff"];
    for (rapidjson::SizeType i = 0; i < buffs.Size(); i++)
    {
        main_world->number_of_buff[i + 1] = buffs[i].GetInt();
    }

    const rapidjson::Value &paths = document["path"];
    for (rapidjson::SizeType i = 0; i < paths.Size(); i++)
    {
        int x1 = paths[i][0][0].GetInt();
        int y1 = paths[i][0][1].GetInt();
        int x2 = paths[i][1][0].GetInt();
        int y2 = paths[i][1][1].GetInt();
        main_world->game_map->addPath(x1, y1, x2, y2);
    }
    const rapidjson::Value &high = document["highplace"];
    for (rapidjson::SizeType i = 0; i < high.Size(); i++)
    {
        int x1 = high[i][0][0].GetInt();
        int y1 = high[i][0][1].GetInt();
        int x2 = high[i][1][0].GetInt();
        int y2 = high[i][1][1].GetInt();
        main_world->game_map->addHighPlace(x1, y1, x2, y2);
    }
    const rapidjson::Value &enemies = document["enemies"];
    if (enemies.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < enemies.Size(); i++)
        {
            std::queue< Vector2D > route_points;
            const rapidjson::Value &r = enemies[i]["route"];
            for (rapidjson::SizeType i = 0; i < r.Size(); i++)
            {
                route_points.push(
                    Vector2D(r[i][0].GetDouble(), r[i][1].GetDouble()));
            }
            EnemyUnit unit = {enemies[i]["id"].GetInt(),
                              enemies[i]["spawn_time"].GetDouble(),
                              enemies[i]["curHP"].GetDouble(),
                              enemies[i]["curDMG"].GetDouble(),
                              enemies[i]["curVelocity"].GetDouble(),
                              enemies[i]["spawn_position"][0].GetInt(),
                              enemies[i]["spawn_position"][1].GetInt(),
                              route_points,
                              (BuffType)enemies[i]["buff"].GetInt()};
            EnemyGenerator::enemies_to_generate.push(unit);
        }
    }

    const rapidjson::Value &towers = document["towers"];
    if (towers.IsArray())
    {
        for (rapidjson::SizeType i = 0; i < towers.Size(); i++)
        {
            TowerUnit unit = {towers[i]["id"].GetInt(),
                              towers[i]["curHP"].GetDouble(),
                              towers[i]["curDMG"].GetDouble(),
                              towers[i]["spawn_position"][0].GetInt(),
                              towers[i]["spawn_position"][1].GetInt(),
                              (Direction)towers[i]["direction"].GetInt(),
                              (BuffType)towers[i]["buff"].GetInt()};
            TowerGenerator::existing_towers.push(unit);
        }
    }
}
