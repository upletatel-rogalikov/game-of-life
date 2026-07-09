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
    SetTargetFPS(144);

    Grid my_grid(200, 200, 100, 50);

    int sim_speed = 24;
    bool auto_sim = false;
    float time_counter = 0.0f;

    my_grid.resize(40, 40);

    // std::cout << "neighbors: " << my_grid.count_neighbors(my_grid.get_index(4, 2)) << "\n";

    // for (int i = 0; i < my_grid.size(); ++i) {
    //     std::cout << "cell #" << i << " value: " << my_grid.get_status(my_grid.get_x(i), my_grid.get_y(i)) << "\n";
    // }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        int current_ind = GetGridIndexFromPoint(my_grid, GetMouseX() - 5, GetMouseY() - 5);
        int current_key = GetKeyPressed();

        switch (current_key) {
            case KEY_R: // update once
                if (!auto_sim) // do nothing if auto_sim is enabled
                    my_grid.update();
                break;

            case KEY_C: // clear grid
                for (int i = 0; i < my_grid.size(); ++i) {
                    my_grid.set_dead(my_grid.get_x(i), my_grid.get_y(i));
                }
                break;

            case KEY_U: // toggle automatic simulation
                auto_sim = !auto_sim;
                break;

            case KEY_PERIOD: // increase auto simulation speed
                if (sim_speed < 60)
                    sim_speed += 6;
                break;

            case KEY_COMMA: // decrease auto simulation speed
                if (sim_speed > 0)
                    sim_speed -= 6;
                break;

            case KEY_RIGHT: // increase width
                my_grid.resize(my_grid.width() + 1, my_grid.height());
                break;

            case KEY_LEFT: // decrease width
                my_grid.resize(my_grid.width() - 1, my_grid.height());
                break;

            case KEY_DOWN: // increase height
                my_grid.resize(my_grid.width(), my_grid.height() + 1);
                break;

            case KEY_UP: // decrease height
                my_grid.resize(my_grid.width(), my_grid.height() - 1);
                break;

            default:
                break;
        }

        if (auto_sim) {
            time_counter += GetFrameTime() * sim_speed;
            if (time_counter >= 1.0f) {
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

        DrawGrid(my_grid);
        DrawCellSelection(my_grid, current_ind);

        // debug information
        DrawFPS(10, 10);
        DrawText(TextFormat("X: %d Y: %d", GetMouseX() - 5, GetMouseY() - 5), 100, 10, 18, GREEN);
        DrawText(TextFormat("speed: %d", sim_speed), 250, 10, 18, GREEN);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 5, RED);
        DrawPixel(GetMouseX() - 4, GetMouseY() - 5, RED);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 4, RED);
        DrawPixel(GetMouseX() - 4, GetMouseY() - 4, RED);
        //

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
