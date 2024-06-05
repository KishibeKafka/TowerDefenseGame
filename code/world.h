#pragma once
#include "Vector2D.h"
#include "actor.h"
#include "game_map.h"
#include "timer.h"
#include <graphics.h>
#include <list>
#include <unordered_set>
#include <vector>

class Engine;

struct attack_signal
{
    double x1;
    double y1;
    double x2;
    double y2;
    double end_time;
};

class WorldRender
{
private:
    PIMAGE path;
    PIMAGE highplace;
    PIMAGE tower1;
    PIMAGE tower2;
    PIMAGE enemy1;
    PIMAGE enemy2;
    PIMAGE home;
    PIMAGE dollar;
    PIMAGE buff1;
    PIMAGE buff2;
    PIMAGE buff3;
    PIMAGE buff4;
    PIMAGE save_bar;
    PIMAGE close_bar;
    int drag_tower;
    int drag_buff;
    int angle;
public:
    mouse_msg mm;
    key_msg km;
    std::list< attack_signal > signals_to_draw;
    WorldRender()
    {
        ;
    }
    ~WorldRender()
    {
        delimage(path);
        delimage(highplace);
        delimage(tower1);
        delimage(enemy1);
        delimage(tower2);
        delimage(enemy2);
        delimage(home);
        delimage(dollar);
        delimage(buff1);
        delimage(buff2);
        delimage(buff3);
        delimage(buff4);
        delimage(save_bar);
        delimage(close_bar);
    }
    void init();
    void rend();
};

class World final
{
public:
    Timer timer;
    GameMap *game_map;
    int current_cost;
    int enemy_number;
    int number_of_buff[5];
    std::unordered_set< Actor * > GameActors;
    std::vector< Actor * > GameActors_to_add;
    std::unordered_set< Actor * > GameActors_to_delete;
    WorldRender world_render;
    friend class Engine;

    World() : current_cost(0), enemy_number(0)
    {
        for (int i = 0; i <= 4; ++i)
            number_of_buff[i] = 0;
    }

    void Render();

    void Update();

    void Input();
};

extern World *main_world;

class GameStatics final
{
public:
    template < typename T >
    static T *createActor(Vector2D pos = Vector2D(0, 0));
};

template < typename T > inline T *GameStatics::createActor(Vector2D pos)
{
    T *pActor = new T;
    if (pActor && static_cast< Actor * >(pActor))
    {
        main_world->GameActors_to_add.push_back(pActor);
        pActor->setLocalPosition(pos);
        // play
        return pActor;
    }
    return nullptr;
}