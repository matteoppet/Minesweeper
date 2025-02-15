#include <iostream>
#include "raylib.h"
#include "map.h"

constexpr int WINDOW_WIDTH = 635;
constexpr int WINDOW_HEIGHT = 800; 

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minesweeper");
    SetTargetFPS(60);
    
    Map map;
    map.resetMap();

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_R)) {
            map.resetMap();
        }

        BeginDrawing();
            map.drawMapAndMouseDetection(map.map_grid);
            
            DrawText("Minesweeper", 10, 670, 25, BLACK);
            DrawText("Map size: 16x18", 10, 710, 20, BLACK);
            DrawText(TextFormat("Flag remaining: %02i", map.flag_remaining), 440, 670, 20, BLACK);
            DrawFPS(440, 710);

            if (map.game_lost) {
                DrawText("GAME LOST", 245, 700, 20, RED);
                DrawText("Press R to restart the game!", 160, 760, 20, RED);
            }

            ClearBackground(WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}