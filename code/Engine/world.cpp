#include "world.h"

World main_world;

void World::Render()
{
    ;
}

void World::Update()
{
    for (auto actor : GameActors)
        actor->Update();
}

void World::Input()
{
    ;
}