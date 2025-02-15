#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include "raylib.h"
#include <iostream>

constexpr int DEFAULT_MAP_ROWS = 16;
constexpr int DEFAULT_MAP_COLS = 18; 
constexpr int DEFAULT_NUM_BOMBS = 26;

struct Cell {
    int row;
    int col;
    bool is_open;
    bool is_bomb;
    bool is_flagged;
};
 
class Map {
    public:
        std::vector<std::vector<int>> map_grid;
        std::vector<Cell> cells; 
        int flag_remaining;
        bool game_lost = false;

        void createMap(std::vector<std::vector<int>>& map_grid, int rows=DEFAULT_MAP_ROWS, int cols=DEFAULT_MAP_COLS);
        void insertBombs(std::vector<std::vector<int>>& map_grid, int num_bombs=DEFAULT_NUM_BOMBS);
        void drawMapAndMouseDetection(std::vector<std::vector<int>>& map_grid);
        int checkForBombs(int row, int col);
        void resetMap();
};

