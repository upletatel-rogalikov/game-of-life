#include <iostream>
#include <string>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

    Grid my_grid(100, 60, 100, 50);

    bool show_help = false;
    int sim_speed = 4;
    int resize_factor = 1;
    bool auto_sim = false;
    float time_counter = 0.0f;

    bool file_save_dialog = false;
    bool file_load_dialog = false;

    char *text_input = new char[256]{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        if (file_save_dialog || file_load_dialog) {
            GuiLock();
        }
        int current_key = GetKeyPressed();

        // int current_ind = GetGridIndexFromPoint(my_grid, GetMouseX() - 5, GetMouseY() - 5);
    if (!(file_save_dialog || file_load_dialog)) {
            switch (current_key) {
                case KEY_R: // update once
                    if (!auto_sim) // do nothing if auto_sim is enabled
                        my_grid.update();
                    break;

                case KEY_H:
                    show_help = !show_help;
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
                    if (sim_speed < 10)
                        sim_speed += 1;
                    break;

                case KEY_COMMA: // decrease auto simulation speed
                    if (sim_speed > 0)
                        sim_speed -= 1;
                    break;

                case KEY_RIGHT: // increase width
                    my_grid.resize(my_grid.width() + resize_factor, my_grid.height());
                    break;

                case KEY_LEFT: // decrease width
                    my_grid.resize(my_grid.width() - resize_factor, my_grid.height());
                    break;

                case KEY_DOWN: // increase height
                    my_grid.resize(my_grid.width(), my_grid.height() + resize_factor);
                    break;

                case KEY_UP: // decrease height
                    my_grid.resize(my_grid.width(), my_grid.height() - resize_factor);
                    break;

                case KEY_S: // save level
                    // my_grid.save("level.dat");
                    file_save_dialog = !file_save_dialog;
                    break;

                case KEY_L: // load level
                    // my_grid.load("level.dat");
                    file_load_dialog = !file_load_dialog;
                    break;

                default:
                    break;
            }
        }

        if (auto_sim && !file_save_dialog) {
            if (sim_speed > 10) 
                sim_speed = 10;

            if (sim_speed < 0)
                sim_speed = 0;

            time_counter += GetFrameTime() * sim_speed * 6;
            if (time_counter >= 1.0f) {
                time_counter = 0.0f;
                my_grid.update();
            }
        }

        int current_ind = GetGridIndexFromPoint(my_grid, GetMouseX() - 5, GetMouseY() - 5);

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !(show_help || file_save_dialog || file_load_dialog)) {
            if (current_ind >= 0) {
                my_grid.set_alive(my_grid.get_x(current_ind), my_grid.get_y(current_ind));
            }
        }

        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && !(show_help || file_save_dialog || file_load_dialog)) {
            if (current_ind >= 0) {
                my_grid.set_dead(my_grid.get_x(current_ind), my_grid.get_y(current_ind));
            }
        }

        DrawGrid(my_grid);
        DrawCellSelection(my_grid, current_ind);

        if (show_help) {
            DrawHelpMenu(my_grid);
        }

        // debug information
        DrawRectangle(5, 5, GetRenderWidth() - 10, 30, WHITE);
        DrawFPS(10, 10);
        DrawText(TextFormat("X: %4d Y: %4d", GetMouseX() - 5, GetMouseY() - 5), 100, 10, 21, GREEN);
        DrawText(TextFormat("speed: %2d", sim_speed), 290, 10, 21, DARKGREEN);
        DrawText(TextFormat("cell #%4d neighbors: %d", current_ind, my_grid.count_neighbors(current_ind)), 420, 10, 21, DARKGREEN);
        DrawText(TextFormat("size: %dx%d", my_grid.width(), my_grid.height()), 780, 10, 21, DARKGREEN);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 5, RED);
        DrawPixel(GetMouseX() - 4, GetMouseY() - 5, RED);
        DrawPixel(GetMouseX() - 5, GetMouseY() - 4, RED);
        DrawPixel(GetMouseX() - 4, GetMouseY() - 4, RED);
        //

        // GUI hell
        DrawRectangle(5, 50, 80, GetRenderHeight() - 55, WHITE);
        float button_height = GetRenderHeight() / 16 > 40 ? GetRenderHeight() / 16 : 40;

        GuiToggle(Rectangle{10.0f, 55.0f, 70.0f, button_height}, "SHOW\nHELP", &show_help);

        GuiToggle(Rectangle{10.0f, 55.0f + button_height * 1.3f, 70.0f, button_height}, "AUTO\nUPDATE", &auto_sim);

        bool speed_edit_mode = false;
        if (GuiSpinner(Rectangle{10.0f, 55.0f + button_height * 2.6f, 70.0f, button_height}, "", &sim_speed, 0, 10, speed_edit_mode)) {
           speed_edit_mode = !speed_edit_mode; 
        }

        bool resize_edit_mode = false;
        if (GuiSpinner(Rectangle{10.0f, 55.0f + button_height * 3.9f, 70.0f, button_height}, "", &resize_factor, 1, 10, resize_edit_mode)) {
           resize_edit_mode = !resize_edit_mode; 
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 5.2f, 70.0f, button_height}, "CLEAR")) {
            for (int i = 0; i < my_grid.size(); ++i) {
                my_grid.set_dead(my_grid.get_x(i), my_grid.get_y(i));
            }
        }


        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 6.5f, 70.0f, button_height}, "#6# SAVE")) {
            file_save_dialog = true;
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 7.8f, 70.0f, button_height}, "#5# LOAD")) {
            file_load_dialog = true;
        }

        if (file_save_dialog) {
            GuiUnlock();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));

            int button_active = -1;

                GuiTextInputBox(Rectangle{(float) GetScreenWidth() / 2 - 120, (float) GetScreenHeight() / 2 - 80.0f, 240, 160}, 
                    "#6# SAVE FILE", "Introduce output file name:", text_input, 255, "Ok;Cancel", &button_active, nullptr);

                if (button_active == 1)
                {
                    std::string fname(text_input);
                    my_grid.save(fname);
                }

                if ((button_active == 0) || (button_active == 1) || (button_active == 2))
                {
                    TextCopy(text_input, "\0");
                    file_save_dialog = false;
                }
        }

        if (file_load_dialog) {
            GuiUnlock();
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));

            int button_active = -1;

                GuiTextInputBox(Rectangle{(float) GetScreenWidth() / 2 - 120, GetScreenHeight() / 2 - 80.0f, 240, 160}, 
                    "#5# LOAD FILE", "Introduce input file name:", text_input, 255, "Ok;Cancel", &button_active, nullptr);

                if (button_active == 1)
                {
                    std::string fname(text_input);
                    my_grid.load(fname);
                }

                if ((button_active == 0) || (button_active == 1) || (button_active == 2))
                {
                    TextCopy(text_input, "\0");
                    file_load_dialog = false;
                }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
