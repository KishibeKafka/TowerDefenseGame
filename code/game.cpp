#include "Vector2D.h"
#include "actor.h"
#include "enemy.h"
#include "say.h"
#include "world.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m;

class Engine
{
public:
    static Enemy *enemy;

    static void Init();
    static void Update();
    static void End();
};

Enemy *Engine::enemy;

int main()
{
    Engine::Init();
    Engine::Update();
    Engine::End();
    return 0;
}

void Engine::Init()
{
    enemy = GameStatics::createActor< Enemy >(Vector2D(1, 1));
    // assert(enemy != nullptr);
    enemy->constructComponent< Say >();
    main_world.GameActors_to_add.push_back(enemy);
    // assert(!enemy->components.empty());
    std::cout << "finished init.\n";
}

void render()
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        main_world.Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void update()
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        main_world.Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void input()
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        main_world.Input();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void add()
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        if (!main_world.GameActors_to_add.empty())
        {
            for (auto &pActor : main_world.GameActors_to_add)
                main_world.GameActors.insert(pActor);
        }
        main_world.GameActors_to_add.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void trash()
{
    while (true)
    {
        std::lock_guard< std::mutex > mutex(m);
        if (!main_world.GameActors_to_delete.empty())
        {
            for (auto &pActor : main_world.GameActors_to_delete)
                pActor->~Actor();
        }
        main_world.GameActors_to_delete.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Engine::Update()
{
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
    for (auto pActor : main_world.GameActors)
        pActor->Destroy();
    main_world.GameActors.clear();
    if (!main_world.GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world.GameActors_to_delete)
            delete pActor;  // ~Actor
    }
    main_world.GameActors_to_delete.clear();
}