#include "actor.h"
#include "attack.h"
#include "collider.h"
#include "enemy.h"
#include "enemy_generator.h"
#include "loader.h"
#include "say.h"
#include "timer.h"
#include "tower_generator.h"
#include "world.h"
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
    Loader::loadSave("..\\resources\\save\\save1.json");
    TowerGenerator::init();
    main_world.timer.start_timer();
}

void render()
{
    main_world.Render();
}

void update()
{
    main_world.Update();
}

void input()
{
    main_world.Input();
}

void add()
{
    if (!main_world.GameActors_to_add.empty())
    {
        for (auto &pActor : main_world.GameActors_to_add)
            main_world.GameActors.insert(pActor);
    }
    main_world.GameActors_to_add.clear();
}

void trash()
{
    if (!main_world.GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world.GameActors_to_delete)
        {
            pActor->~Actor();
            for (auto &toremove : main_world.GameActors)
            {
                if (toremove == pActor)
                    main_world.GameActors.erase(toremove);
            }
        }
    }
    main_world.GameActors_to_delete.clear();
}

void Engine::Update()
{
    std::cout << "updating\n";
    std::thread ad(
        [](void) -> void
        {
            main_world.timer.fixedExecute(add);
        });
    std::thread rend(
        [](void) -> void
        {
            main_world.timer.fixedExecute(render);
        });
    std::thread upd(
        [](void) -> void
        {
            main_world.timer.fixedExecute(update);
        });
    std::thread inp(
        [](void) -> void
        {
            main_world.timer.fixedExecute(input);
        });
    std::thread tra(
        [](void) -> void
        {
            main_world.timer.fixedExecute(trash);
        });
    ad.join();
    rend.join();
    upd.join();
    inp.join();
    tra.join();
}

void Engine::End()
{
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
}
