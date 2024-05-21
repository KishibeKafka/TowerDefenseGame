#pragma once

#include "Vector2D.h"
#include "enemy_generator.h"
#include "game_map.h"
#include "property.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "tower_generator.h"
#include "world.h"
#include <cstdio>
#include <queue>
#include <string>

extern World main_world;

class Loader
{
public:
    static void getEnemy(int i, Property *e_p);
    static void getTower(int i, Property *t_p);
    static void loadSave(std::string filename);
};