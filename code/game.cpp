#include "actor.h"
#include "attack.h"
#include "collider.h"
#include "enemy.h"
#include "enemy_generator.h"
#include "loader.h"
#include "saver.h"
#include "say.h"
#include "timer.h"
#include "tower_generator.h"
#include "world.h"
#include <cstdlib>
#include <thread>

class Engine
{
public:
    static Enemy *enemy;

    static void Init();
    static void Update();
    static void End();
};

extern World main_world;

int main()
{
    Engine::Init();
    Engine::Update();
    Engine::End();
    return 0;
}

void Engine::Init()
{
    Loader::loadSave("..\\resources\\data\\map1.json");
    TowerGenerator::init();
    main_world.world_render.init();
    main_world.timer.start_timer();
}

void render()
{
    for (; is_run(); delay_fps(60))
    {
        main_world.Render();
    }
}

void update()
{
    for (; is_run(); delay(60))
    {
        if (main_world.enemy_number <= 0)
        {
            Engine::End();
        }
        main_world.Update();
    }
}

void input()
{
    for (; is_run(); delay(60))
    {
        main_world.Input();
    }
}

void add()
{
    for (; is_run(); delay(60))
    {
        if (!main_world.GameActors_to_add.empty())
        {
            for (auto &pActor : main_world.GameActors_to_add)
                main_world.GameActors.insert(pActor);
        }
        main_world.GameActors_to_add.clear();
    }
}

void trash()
{
    for (; is_run(); delay(60))
    {
        if (!main_world.GameActors_to_delete.empty())
        {
            for (auto &pActor : main_world.GameActors_to_delete)
            {
                delete pActor;
                for (auto &toremove : main_world.GameActors)
                {
                    if (toremove == pActor)
                        main_world.GameActors.erase(toremove);
                }
            }
        }
        main_world.GameActors_to_delete.clear();
    }
}

void Engine::Update()
{
    std::cout << "updating\n";
    std::thread ad(add);
    std::thread rend(render);
    std::thread upd(update);
    std::thread inp(input);
    std::thread tra(trash);
    ad.join();
    rend.join();
    upd.join();
    inp.join();
    tra.join();
}

void Engine::End()
{
    std::cout << "input y or n to save : ";
    char decide;
    std::cin >> decide;
    if (decide == 'y')
    {
        Saver::save("..\\resources\\save\\save1.json");
    }

    for (auto pActor : main_world.GameActors)
        pActor->Destroy();
    main_world.GameActors.clear();
    if (!main_world.GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world.GameActors_to_delete)
            delete pActor;  // ~Actor
    }
    main_world.GameActors_to_delete.clear();
    delete main_world.game_map;
    std::cout << "Game End!\n";
    system("pause");
    exit(0);
}
