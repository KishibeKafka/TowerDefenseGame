#pragma once
#include "actor.h"
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
#include <string>
#include <thread>

class Engine
{
public:
    static std::string save;
    static Enemy *enemy;
    static bool end;

    static void Init(std::string path);
    static void Update();
    static void End();
};

extern World main_world;
