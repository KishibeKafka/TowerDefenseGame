#include "world.h"

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