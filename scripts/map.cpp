#include "map.h"

void Map::createMap(std::vector<std::vector<int>>& map_grid, int rows, int cols) {
    map_grid.resize(rows, std::vector<int>(cols, 0));
    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            map_grid[row][col] = 0;
        }
    }   
}

void Map::insertBombs(std::vector<std::vector<int>>& map_grid, int num_bombs) {
    int random_row;
    int random_col;
    srand(time(0));
    for (int count_bomb=0; count_bomb<num_bombs; count_bomb++) {
        random_row = rand() % map_grid.size();
        random_col = rand() % map_grid.size();

        map_grid[random_row][random_col] = 1;
    }

    for (int row=0; row<map_grid.size(); row++) {
        for (int col=0; col<map_grid.size(); col++) {
            Cell new_cell;
            new_cell.row = row;
            new_cell.col = col;
            new_cell.is_open = false;
            new_cell.is_flagged = false;

            if (map_grid[row][col] == 1) {
                new_cell.is_bomb = true;
            } else {
                new_cell.is_bomb = false;
            }
            cells.emplace_back(new_cell);
        }
    }

    flag_remaining = num_bombs;
}

void Map::drawMapAndMouseDetection(std::vector<std::vector<int>>& map_grid) {
    int size_cell = 40;
    int num_of_bombs_found = 0;

    // * IF GAME LOST SHOW BOMBS AND STOP CHECK EVENT MOUSE
    if (game_lost) {
        for (auto& cell : cells) {
            if (!cell.is_open) {
                DrawRectangle(cell.row*size_cell, cell.col*size_cell, size_cell-5, size_cell-5, BLACK);
                if (cell.is_bomb) {
                    DrawText("B", cell.row*size_cell+12, cell.col*size_cell+10, 20, RED);
                }
                if (cell.is_flagged) {
                    DrawText("F", cell.row*size_cell+12, cell.col*size_cell+10, 20, ORANGE);
                }
            } else {
                if (cell.is_bomb) {
                    DrawText("B", cell.row*size_cell+12, cell.col*size_cell+10, 20, RED);
                } else {
                    num_of_bombs_found = checkForBombs(cell.row, cell.col);
                    DrawText(std::to_string(num_of_bombs_found).c_str(), cell.row*size_cell+12, cell.col*size_cell+10, 20, BLACK);
                }
            }
            
        }
    }
    else {
        for (auto& cell : cells) {
            // * OPEN CELL
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (GetMousePosition().x >= cell.row*size_cell-5 && GetMousePosition().x <= (cell.row*size_cell-5)+size_cell-5 && GetMousePosition().y >= cell.col*size_cell-5 && GetMousePosition().y <= (cell.col*size_cell-5)+size_cell-5) {
                    if (!cell.is_open) {
                        cell.is_open = true;
                    }
                    if (cell.is_bomb) {
                        game_lost = true;
                    }
                }
            } 
            // * PUT FLAG CELL
            else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                if (GetMousePosition().x >= cell.row*size_cell-5 && GetMousePosition().x <= (cell.row*size_cell-5)+size_cell-5 && GetMousePosition().y >= cell.col*size_cell-5 && GetMousePosition().y <= (cell.col*size_cell-5)+size_cell-5) {
                    if (!cell.is_open && !cell.is_flagged && flag_remaining > 0) {
                        cell.is_flagged = true;
                        flag_remaining -= 1;
                    } else if (cell.is_flagged) {
                        cell.is_flagged = false;
                        flag_remaining++;
                    }
                }
            }
            
            // * DRAW CELL
            if (!cell.is_open) {
                DrawRectangle(cell.row*size_cell, cell.col*size_cell, size_cell-5, size_cell-5, BLACK);
                if (cell.is_flagged) {
                    DrawText("F", cell.row*size_cell+12, cell.col*size_cell+10, 20, ORANGE);
                }
            } else {
                if (cell.is_bomb) {
                    DrawText("B", cell.row*size_cell+12, cell.col*size_cell+10, 20, RED);
                } else {
                    num_of_bombs_found = checkForBombs(cell.row, cell.col);
                    DrawText(std::to_string(num_of_bombs_found).c_str(), cell.row*size_cell+12, cell.col*size_cell+10, 20, BLACK);
                }
            }
        }
    }
}

int Map::checkForBombs(int row, int col) {
    /*
        The two for loops check for the cells above and below, also the diagonal, so after that
        loops, you have to check just the cell on the right and one on the left
    */
    int num_bombs_found = 0;

    // cells above
    for (int cols_above=col-1; cols_above<=col+1; cols_above++) {
        if (cols_above >= 0 && row-1>=0 && cols_above < map_grid.size()) {
            if (map_grid[row-1][cols_above] == 1) {
                num_bombs_found++;
            }
        }
    }

    // cells below
    for (int cols_below=col-1; cols_below<=col+1; cols_below++) {
        if (cols_below < map_grid.size() && row+1 < map_grid.size()) {
            if (map_grid[row+1][cols_below] == 1) {
                num_bombs_found++;
            }
        }
    }

    // cell right
    if (map_grid[row][col+1] == 1) {
        num_bombs_found++;
    }
    // cell left
    if (map_grid[row][col-1] == 1) {
        num_bombs_found++;
    }

    return num_bombs_found;
}

void Map::resetMap() {
    game_lost = false;
    createMap(map_grid);
    insertBombs(map_grid);
}