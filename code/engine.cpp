#include "engine.h"
#include "world.h"

std::string Engine::save;

bool Engine::end;

void Engine::Init(std::string path)
{
    main_world = new World;
    save = path;
    end = false;
    Loader::loadSave(path);
    TowerGenerator::init();
    main_world->world_render.init();
    main_world->timer.start_timer();
}

void render()
{
    for (; is_run() && !Engine::end; delay_fps(60))
    {
        main_world->Render();
    }
}

void update()
{
    for (; is_run() && !Engine::end; delay(60))
    {
        if (main_world->enemy_number <= 0)
        {
            Engine::end = true;
        }
        main_world->Update();
    }
}

void input()
{
    for (; is_run() && !Engine::end; delay(60))
    {
        main_world->Input();
    }
}

void add()
{
    for (; is_run() && !Engine::end; delay(20))
    {
        if (!main_world->GameActors_to_add.empty())
        {
            for (auto &pActor : main_world->GameActors_to_add)
                main_world->GameActors.insert(pActor);
        }
        main_world->GameActors_to_add.clear();
    }
}

void trash()
{
    for (; is_run() && !Engine::end; delay(20))
    {
        if (!main_world->GameActors_to_delete.empty())
        {
            for (auto &pActor : main_world->GameActors_to_delete)
            {
                delete pActor;
                for (auto &toremove : main_world->GameActors)
                {
                    if (toremove == pActor)
                        main_world->GameActors.erase(toremove);
                }
            }
        }
        main_world->GameActors_to_delete.clear();
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
    for (auto pActor : main_world->GameActors)
        pActor->Destroy();
    main_world->GameActors.clear();
    if (!main_world->GameActors_to_delete.empty())
    {
        for (auto &pActor : main_world->GameActors_to_delete)
            delete pActor;  // ~Actor
    }
    main_world->GameActors_to_delete.clear();
    delete main_world->game_map;
    delete main_world;
}