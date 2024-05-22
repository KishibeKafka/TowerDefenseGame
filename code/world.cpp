#include "world.h"
#include "enemy_generator.h"
#include "tower_generator.h"
#include <iostream>

World main_world;

void World::Render()
{
    ;
}

void World::Update()
{
    std::cout << "Current cost: " << current_cost << '\n';
    current_cost++;
    EnemyGenerator::update();
    for (auto actor : GameActors)
        actor->Update();
}

void World::Input()
{
    TowerGenerator::input();
}