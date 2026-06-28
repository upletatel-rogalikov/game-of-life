#include <iostream>

#include "raylib.h"
#include "grid.h"
#include "graphics.h"

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(640, 480);
    SetTargetFPS(60);

    Grid my_grid(15, 10);

    my_grid.set_alive(0, 0);
    my_grid.set_alive(3, 3);
    my_grid.set_alive(4, 3);
    my_grid.set_alive(6, 6);
    my_grid.set_alive(14, 6);
    my_grid.set_alive(14, 7);
    my_grid.set_alive(14, 8);
    my_grid.set_alive(14, 9);
    my_grid.set_alive(13, 9);
    my_grid.set_alive(12, 9);
    my_grid.set_alive(9, 9);


    for (int i = 0; i < my_grid.size(); ++i) {
        std::cout << "cell #" << i << " value: " << my_grid.get_status(my_grid.get_x(i), my_grid.get_y(i)) << "\n";
    }


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        // DrawText("Hello raylib!\nBuilt on windows and linux using cmake!", 50, 200, 32, BLACK);

        // debug information
        DrawFPS(10, 10);
        DrawText(TextFormat("%d, %d", GetMouseX() - 5, GetMouseY() - 5), 100, 10, 18, GREEN);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 5, RED);
        //

        DrawGrid(my_grid, 200, 200);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
