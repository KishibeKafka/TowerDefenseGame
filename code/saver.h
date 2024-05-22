#pragma once

#include "Vector2D.h"
#include "actor.h"
#include "enemy_generator.h"
#include "game_map.h"
#include "property.h"
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include "tower_generator.h"
#include "world.h"
#include <cstdio>

extern World main_world;

class Saver
{
public:
    static void save(std::string filename);
};