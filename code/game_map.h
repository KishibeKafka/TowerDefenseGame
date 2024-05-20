#pragma once
#include "Vector2D.h"
#include <vector>

struct Grid
{
    int type;  // 0 : cannot build 1 : 远程 2 : path
    int i;
    int j;
    Grid() : type(0), i(1), j(1) {}
    Vector2D getlocation()
    {
        return Vector2D(i * PPU - PPU / 2, j * PPU - PPU / 2);
    }
};

class GameMap
{
public:
    std::vector< std::vector< Grid > > grids;
    GameMap(int x = 10, int y = 10)
    {
        grids.resize(x);
        for (int i = 1; i <= x; i++)
        {
            grids[i].resize(y);
            for (int j = 1; j <= y; j++)
            {
                grids[i][j].i = i;
                grids[i][j].j = j;
                grids[i][j].type = 0;
            }
        }
    }

    void addPath(int x1, int y1, int x2, int y2)
    {
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
                grids[i][j].type = 2;
        }
    }

    void addHighPlace(int x1, int y1, int x2, int y2)
    {
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
                grids[i][j].type = 1;
        }
    }
};