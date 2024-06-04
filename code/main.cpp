#include "engine.h"
#include <chrono>
#include <ege/sys_edit.h>
#include <graphics.h>
#include <string>
#include <wingdi.h>
struct Save
{
    std::string path;
    std::chrono::system_clock update_time;
};

class Manual
{
public:
    int status;

    PIMAGE bk;
    PIMAGE start_bar;

    PIMAGE select_bar;
    PIMAGE end_bar;
    PIMAGE back_bar;
    Save src_save;   // 加载的存档
    Save dest_save;  // 目标存档

    sys_edit editbox;
    mouse_msg mm;

    void init()
    {
        initgraph(640, 480);
        setrendermode(ege::RENDER_MANUAL);
        bk = newimage();
        start_bar = newimage();
        select_bar = newimage();
        end_bar = newimage();
        back_bar = newimage();
        getimage(bk, "../resources/sprite/background.png");
        getimage(start_bar, "../resources/sprite/start.png");
        getimage(select_bar, "../resources/sprite/select.png");
        getimage(end_bar, "../resources/sprite/close.png");
        getimage(back_bar, "../resources/sprite/back.png");
        editbox.create(false);
        editbox.setfont(20, 0, "宋体");
        editbox.size(324, 48);
        editbox.move(150, 216);
        editbox.visible(false);
    }

    void start()
    {
        status = 1;
        initgraph(640, 480);
        setrendermode(ege::RENDER_MANUAL);

        editbox.visible(false);
    }

    void update()
    {
        for (; is_run(); delay_fps(60))
        {
            if (status != 2)
                cleardevice();
            if (status == 1)
            {
                main_manual();
            } else if (status == 2)
            {
                select_save();
            } else if (status == 3)
            {
                break;
            }
        }
        editbox.visible(false);
        closegraph();
        Engine::Init(src_save.path);
        Engine::Update();
        Engine::End();
    }
    void main_manual()
    {
        editbox.visible(false);
        putimage(0, 0, bk);
        putimage(266, 216, start_bar);
        putimage(0, 432, end_bar);
        while (mousemsg())
        {
            mm = getmouse();
            if (mm.is_left())
            {
                if (mm.x >= 266 && mm.x < 374 && mm.y >= 216 && mm.y < 264)
                {
                    status = 2;
                }
                if (mm.x >= 0 && mm.x < 48 && mm.y >= 432 && mm.y < 480)
                {
                    end();
                    closegraph();
                    exit(0);
                }
            }
        }
    }

    void select_save()
    {
        putimage(0, 0, bk);
        setfont(30, 0, "宋体");
        setbkcolor(WHITE);
        setcolor(RED);
        outtextxy(166, 100, "Enter Save File Path...");
        putimage(266, 280, select_bar);
        putimage(0, 432, back_bar);
        editbox.visible(true);

        char buffer[100];
        editbox.gettext(100, buffer);
        src_save.path = buffer;

        while (mousemsg())
        {
            mm = getmouse();
            if (mm.is_left())
            {
                if (mm.x >= 0 && mm.x < 48 && mm.y >= 432 && mm.y < 480)
                {
                    status = 1;
                } else if (mm.x >= 266 && mm.x < 374 && mm.y >= 280 &&
                           mm.y < 328)
                {
                    status = 3;
                }
            }
        }
    }

    void end()
    {
        delimage(bk);
        delimage(start_bar);
        delimage(select_bar);
        delimage(end_bar);
        editbox.destroy();
        closegraph();
    }
};

int main()
{
    Manual mygame;
    mygame.init();
    while (true)
    {
        mygame.start();
        mygame.update();
        closegraph();
    }
    mygame.end();
}