#include "world.h"
#include "Vector2D.h"
#include "buff_manager.h"
#include "enemy_generator.h"
#include "engine.h"
#include "property.h"
#include "saver.h"
#include "tower_generator.h"
#include <cstddef>

World *main_world;

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
    initgraph(main_world->game_map->size_x * PPU,
              main_world->game_map->size_y * PPU + PPU);
    setrendermode(ege::RENDER_MANUAL);
    setbkcolor(WHITE);
    setcolor(BLACK);
    setfont(12, 0, "宋体");
    path = newimage();
    highplace = newimage();
    tower1 = newimage();
    tower2 = newimage();
    enemy1 = newimage();
    enemy2 = newimage();
    home = newimage();
    dollar = newimage();
    buff1 = newimage();
    buff2 = newimage();
    buff3 = newimage();
    buff4 = newimage();
    save_bar = newimage();
    close_bar = newimage();

    getimage(path, "../resources/sprite/path.png");
    getimage(highplace, "../resources/sprite/highplace.png");
    getimage(tower1, "../resources/sprite/tower1.png");
    getimage(tower2, "../resources/sprite/tower2.png");
    getimage(enemy1, "../resources/sprite/enemy1.png");
    getimage(enemy2, "../resources/sprite/enemy2.png");
    getimage(home, "../resources/sprite/home.png");
    getimage(dollar, "../resources/sprite/dollar.png");
    getimage(buff1, "../resources/sprite/addHP.png");
    getimage(buff2, "../resources/sprite/addDMG.png");
    getimage(buff3, "../resources/sprite/addVelocity.png");
    getimage(buff4, "../resources/sprite/quickAttack.png");
    getimage(save_bar, "../resources/sprite/save.png");
    getimage(close_bar, "../resources/sprite/close.png");
    drag_tower = 0;
    drag_buff = 0;
    angle = 0;
}

void draw_attack(attack_signal signal)
{
    setcolor(RED);
    int x1 = signal.x1;
    int y1 = main_world->game_map->size_y * PPU + PPU - signal.y1;
    int x2 = signal.x2;
    int y2 = main_world->game_map->size_y * PPU + PPU - signal.y2;
    line(x1, y1, x2, y2);
    setcolor(BLACK);
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

            if (x >= main_world->game_map->size_x * PPU - 48 &&
                x < main_world->game_map->size_x * PPU && y >= 0 && y < 48)
            {
                Saver::save(Engine::save);
                Engine::end = true;
                ;  // save
            }
            if (x >= main_world->game_map->size_x * PPU - 48 &&
                x < main_world->game_map->size_x * PPU && y >= 48 && y < 96)
            {
                Engine::end = true;
                // closegraph();  // no save
            }

            if (y >= 0 && y <= PPU)
            {
                if (x >= 0 && x < PPU)
                {
                    drag_tower = 1;
                } else if (x >= PPU && x < 2 * PPU)
                {
                    drag_tower = 2;
                }
            }
            if (y >= 0 && y <= 0.25 * PPU)
            {
                int x1 = main_world->game_map->size_x * PPU - 6 * PPU;
                int x2 = x1 + PPU;
                int x3 = x2 + PPU;
                int x4 = x3 + PPU;
                if (x >= x1 && x < x1 + 0.25 * PPU &&
                    main_world->number_of_buff[1] > 0)
                {
                    drag_buff = 1;
                } else if (x >= x2 && x < x2 + 0.25 * PPU &&
                           main_world->number_of_buff[2] > 0)
                {
                    drag_buff = 2;
                } else if (x >= x3 && x < x3 + 0.25 * PPU &&
                           main_world->number_of_buff[3] > 0)
                {
                    drag_buff = 3;
                } else if (x >= x4 && x < x4 + 0.25 * PPU &&
                           main_world->number_of_buff[4] > 0)
                {
                    drag_buff = 4;
                }
            }
        } else if (mm.is_right())
        {
            drag_tower = 0;
            drag_buff = 0;
        }
    }

    // key board message
    while (kbmsg())
    {
        km = getkey();
        // if (km.key == key_esc)
        // {
        //     outtextxy(main_world->game_map->size_x * PPU * 0.5 - PPU * 0.5,
        //               main_world->game_map->size_y * PPU * 0.5 - PPU * 0.5,
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
    putimage_withalpha(NULL, tower2, PPU, 0);
    setfont(12, 0, "宋体");
    outtextxy(0, 54, "100");
    outtextxy(PPU, 54, "200");
    // 绘制可选buff
    for (int i = 1; i <= 4; ++i)
    {
        int x = main_world->game_map->size_x * PPU - (7 - i) * PPU;
        if (i == 1)
        {
            putimage_withalpha(NULL, buff1, x, 0);
        } else if (i == 2)
        {
            putimage_withalpha(NULL, buff2, x, 0);
        } else if (i == 3)
        {
            putimage_withalpha(NULL, buff3, x, 0);
        } else if (i == 4)
        {
            putimage_withalpha(NULL, buff4, x, 0);
        }
        xyprintf(x, 0.5 * PPU, " %d ", main_world->number_of_buff[i]);
    }

    // 绘制地图
    for (int i = 1; i <= main_world->game_map->size_x; ++i)
    {
        for (int j = 1; j <= main_world->game_map->size_y; ++j)
        {
            if (main_world->game_map->grids[i][j].type == 1)
                putimage(i * PPU - PPU,
                         (main_world->game_map->size_y - j + 1) * PPU,
                         highplace);
            else if (main_world->game_map->grids[i][j].type == 2)
                putimage(i * PPU - PPU,
                         (main_world->game_map->size_y - j + 1) * PPU, path);
            else
                putimage(i * PPU - PPU,
                         (main_world->game_map->size_y - j + 1) * PPU, home);
        }
    }
    // 绘制塔和敌人和buff
    for (auto pactor : main_world->GameActors)
    {
        if (main_world->GameActors_to_delete.find(pactor) !=
                main_world->GameActors_to_delete.end() ||
            pactor == nullptr || !pactor->alive)
            continue;
        Property *property = pactor->getComponentByClass< Property >();
        double x = pactor->getWorldPosition().x;
        double y = main_world->game_map->size_y * PPU + PPU -
                   pactor->getWorldPosition().y;
        if (property->getType() == 0)
        {
            if (property->getID() == 1)
            {
                putimage_rotate(NULL, tower1, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            } else if (property->getID() == 2)
            {
                putimage_rotate(NULL, tower2, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            }
            if (property->getBuff() == addHP)
            {
                putimage_rotate(NULL, buff1, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == addDMG)
            {
                putimage_rotate(NULL, buff2, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == addVelocity)
            {
                putimage_rotate(NULL, buff3, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == quickAttack)
            {
                putimage_rotate(NULL, buff4, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            }
        } else
        {
            if (property->getID() == 1)
            {
                putimage_rotate(NULL, enemy1, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            } else if (property->getID() == 2)
            {
                putimage_rotate(NULL, enemy2, x, y, 0.5, 0.5,
                                (double)property->getDirection() * PI / 180, 1);
            }
            if (property->getBuff() == addHP)
            {
                putimage_rotate(NULL, buff1, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == addDMG)
            {
                putimage_rotate(NULL, buff2, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == addVelocity)
            {
                putimage_rotate(NULL, buff3, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            } else if (property->getBuff() == quickAttack)
            {
                putimage_rotate(NULL, buff4, x + 0.5 * PPU, y + 0.5 * PPU, 1, 1,
                                0, 1);
            }
        }
    }

    // 绘制攻击轨迹
    for (auto it = signals_to_draw.begin(); it != signals_to_draw.end();)
    {
        if (main_world->timer.getCurrrentTime().count() > it->end_time)
        {
            it = signals_to_draw.erase(it);
        } else
        {
            draw_attack(*it);
            ++it;
        }
    }

    // 绘制拖动的塔
    if (drag_tower)
    {
        if (drag_tower == 1)
        {
            putimage_rotate(NULL, tower1, mm.x, mm.y, 0.5, 0.5,
                            (double)angle * PI / 180, 1);
        } else if (drag_tower == 2)
        {
            putimage_rotate(NULL, tower2, mm.x, mm.y, 0.5, 0.5,
                            (double)angle * PI / 180, 1);
        }
    } else if (drag_buff)
    {
        if (drag_buff == 1)
            putimage_rotate(NULL, buff1, mm.x, mm.y, 0.5, 0.5, 0, 1);
        else if (drag_buff == 2)
            putimage_rotate(NULL, buff2, mm.x, mm.y, 0.5, 0.5, 0, 1);
        else if (drag_buff == 3)
            putimage_rotate(NULL, buff3, mm.x, mm.y, 0.5, 0.5, 0, 1);
        else if (drag_buff == 4)
            putimage_rotate(NULL, buff4, mm.x, mm.y, 0.5, 0.5, 0, 1);
    }
    if (drag_tower && mm.is_left())
    {
        int i, j;
        i = (int)(mm.x / PPU) + 1;
        j = main_world->game_map->size_y + 1 - (int)(mm.y / PPU);
        TowerGenerator::input(drag_tower, i, j, angle);
        // xyprintf(mm.x, mm.y, "i: %d, j: %d", i, j);
    } else if (drag_buff && mm.is_left())
    {
        int i, j;
        i = (int)(mm.x / PPU) + 1;
        j = main_world->game_map->size_y + 1 - (int)(mm.y / PPU);
        BuffManager::setBuffforTower(main_world->game_map->grids[i][j].pTower,
                                     drag_buff);
    }

    // 绘制其他

    putimage_withalpha(NULL, dollar,
                       main_world->game_map->size_x * PPU - 2 * PPU, 0);
    setfont(20, 0, "宋体");
    xyprintf(main_world->game_map->size_x * PPU - PPU, 0, "%d",
             main_world->current_cost);
    setfont(12, 0, "宋体");
    xyprintf(main_world->game_map->size_x * PPU - PPU, 32, "left:%d",
             main_world->enemy_number);
    putimage(main_world->game_map->size_x * PPU - 48, 0, save_bar);
    putimage(main_world->game_map->size_x * PPU - 48, 48, close_bar);
}