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

    Grid my_grid(200, 200, 100, 50);

    int sim_speed = 24;
    bool auto_sim = false;
    float time_counter = 0.0f;

    my_grid.set_alive(4, 1);
    my_grid.set_alive(5, 2);
    my_grid.set_alive(3, 3);
    my_grid.set_alive(4, 3);
    my_grid.set_alive(5, 3);

    // std::cout << "neighbors: " << my_grid.count_neighbors(my_grid.get_index(4, 2)) << "\n";

    // for (int i = 0; i < my_grid.size(); ++i) {
    //     std::cout << "cell #" << i << " value: " << my_grid.get_status(my_grid.get_x(i), my_grid.get_y(i)) << "\n";
    // }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        int current_ind = GetGridIndexFromPoint(my_grid, GetMouseX() - 5, GetMouseY() - 5);

        if (auto_sim) {
            time_counter += GetFrameTime();
            if (time_counter * sim_speed >= 1.0f) {
                time_counter = 0.0f;
                my_grid.update();
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

            if (current_ind>= 0) {
                my_grid.set_alive(my_grid.get_x(current_ind), my_grid.get_y(current_ind));
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {

            if (current_ind >= 0) {
                my_grid.set_dead(my_grid.get_x(current_ind), my_grid.get_y(current_ind));
            }
        }

        // update grid
        if (IsKeyPressed(KEY_R)) {
            my_grid.update();
        }

        if (IsKeyPressed(KEY_U)) {
            auto_sim = !auto_sim;
        }

        // debug information
        DrawFPS(10, 10);
        DrawText(TextFormat("%d, %d", GetMouseX() - 5, GetMouseY() - 5), 100, 10, 18, GREEN);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 5, RED);
        //

        DrawGrid(my_grid);
        DrawCellSelection(my_grid, current_ind);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
