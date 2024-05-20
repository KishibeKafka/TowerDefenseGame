#include "world.h"
#include "enemy_generator.h"

World main_world;

void World::Render()
{
    ;
}

void World::Update()
{
    EnemyGenerator::update();
    for (auto actor : GameActors)
        actor->Update();
}

void World::Input()
{
    ;
}