#include "world.h"
#include "Vector2D.h"
#include "enemy_generator.h"
#include "property.h"
#include "tower_generator.h"
#include <cstddef>
#include <wingdi.h>

World main_world;

void World::Render()
{
    cleardevice();
    world_render.rend();
}

void World::Update()
{
    current_cost++;
    EnemyGenerator::update();
    for (auto actor : GameActors)
        actor->Update();
}

void World::Input() {}

void WorldRender::init()
{
    initgraph(main_world.game_map->size_x * PPU,
              main_world.game_map->size_y * PPU + PPU);
    setrendermode(ege::RENDER_MANUAL);
    setbkcolor(WHITE);
    setcolor(BLACK);
    setfont(12, 0, "宋体");
    path = newimage();
    highplace = newimage();
    tower1 = newimage();
    enemy1 = newimage();
    home = newimage();
    getimage(path, "../resources/sprite/path.png");
    getimage(highplace, "../resources/sprite/highplace.png");
    getimage(tower1, "../resources/sprite/tower1.png");
    getimage(enemy1, "../resources/sprite/enemy1.png");
    getimage(home, "../resources/sprite/home.png");
    drag = false;
    angle = 0;
    id = 1;
}

void WorldRender::rend()
{
    // mouse message
    while (mousemsg())
    {
        mm = getmouse();
        if (mm.is_left())
        {
            int x = mm.x;
            int y = mm.y;
            if (y >= 0 && y <= PPU)
            {
                if (x >= 0 && x < PPU)
                {
                    drag = true;
                    id = 1;
                }
            }
        } else if (mm.is_right())
        {
            drag = false;
        }
    }

    // key board message
    while (kbmsg())
    {
        km = getkey();
        // if (km.key == key_esc)
        // {
        //     outtextxy(main_world.game_map->size_x * PPU * 0.5 - PPU * 0.5,
        //               main_world.game_map->size_y * PPU * 0.5 - PPU * 0.5,
        //               "PAUSE");
        //     getch();
        // }
        if (km.key == key_right)
            angle = 0;
        else if (km.key == key_up)
            angle = 90;
        else if (km.key == key_left)
            angle = 180;
        else if (km.key == key_down)
            angle = 270;
    }
    // xyprintf(PPU, 0, "x: %d y: %d", mm.x, mm.y);
    // xyprintf(PPU, PPU * 0.5, "%c", km.key);
    // 绘制可选塔
    putimage_withalpha(NULL, tower1, 0, 0);
    outtextxy(0, 54, "100");

    // 绘制地图
    for (int i = 1; i <= main_world.game_map->size_x; ++i)
    {
        for (int j = 1; j <= main_world.game_map->size_y; ++j)
        {
            if (main_world.game_map->grids[i][j].type == 1)
                putimage(i * PPU - PPU,
                         (main_world.game_map->size_y - j + 1) * PPU,
                         highplace);
            else if (main_world.game_map->grids[i][j].type == 2)
                putimage(i * PPU - PPU,
                         (main_world.game_map->size_y - j + 1) * PPU, path);
            else
                putimage(i * PPU - PPU,
                         (main_world.game_map->size_y - j + 1) * PPU, home);
        }
    }
    // 绘制塔和敌人
    for (auto pactor : main_world.GameActors)
    {
        Property *property = pactor->getComponentByClass< Property >();
        double x = pactor->getWorldPosition().x;
        double y = main_world.game_map->size_y * PPU + PPU -
                   pactor->getWorldPosition().y;
        if (property->getType() == 0)
        {
            if (property->getID() == 1)
            {
                putimage_rotate(NULL, tower1, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            }
        } else
        {
            if (property->getID() == 1)
            {
                putimage_rotate(NULL, enemy1, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            }
        }
    }
    // 绘制拖动的塔
    if (drag)
    {
        putimage_rotate(NULL, tower1, mm.x, mm.y, 0.5, 0.5,
                        (double)angle * PI / 180, 1);
    }
    if (drag && mm.is_left())
    {
        int i, j;
        i = (int)(mm.x / PPU) + 1;
        j = main_world.game_map->size_y + 1 - (int)(mm.y / PPU);
        TowerGenerator::input(id, i, j, angle);
        // xyprintf(mm.x, mm.y, "i: %d, j: %d", i, j);
    }

    // 绘制其他
    xyprintf(main_world.game_map->size_x * PPU - PPU, 0, "COST: %d",
             main_world.current_cost);
}