#pragma once
#include "Vector2D.h"
#include "actor.h"
#include <cstdlib>
#include <vector>

struct Grid
{
    int type;    // 0 : cannot build 1 : 远程 2 : path
    int status;  // 0 avaiable 1 已被占用
    int i;
    int j;
    Actor *pTower;
    Grid() : type(0), status(0), i(1), j(1), pTower(nullptr) {}
    Vector2D getlocation()
    {
        return Vector2D(i * PPU - PPU / 2, j * PPU - PPU / 2);
    }
};

struct Path
{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct HighPlace
{
    int x1;
    int y1;
    int x2;
    int y2;
};

class GameMap
{
public:
    int size_x;
    int size_y;
    std::vector< Path > paths;
    std::vector< HighPlace > highplaces;
    std::vector< std::vector< Grid > > grids;
    GameMap(int x = 10, int y = 10)
    {
        grids.resize(x + 1);
        for (int i = 1; i <= x; i++)
        {
            grids[i].resize(y + 1);
            for (int j = 1; j <= y; j++)
            {
                grids[i][j].i = i;
                grids[i][j].j = j;
                grids[i][j].type = 0;
            }
        }
        size_x = x;
        size_y = y;
    }

    void addPath(int x1, int y1, int x2, int y2)
    {
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
                grids[i][j].type = 2;
        }
        paths.push_back({x1, y1, x2, y2});
    }

    void addHighPlace(int x1, int y1, int x2, int y2)
    {
        for (int i = x1; i <= x2; i++)
        {
            for (int j = y1; j <= y2; j++)
                grids[i][j].type = 1;
        }
        highplaces.push_back({x1, y1, x2, y2});
    }
};