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

    int current_ind = 0; // index of the cell pointed by the mouse (-1 if outside the grid)
    int current_key = 0; // current key pressed

    int resize_factor = 1;

    bool auto_sim = false;
    int sim_speed = 4;
    float time_counter = 0.0f;

    // GUI control
    bool show_help = false;
    bool show_debug = false;

    bool speed_edit_mode = false;
    bool resize_edit_mode = false;

    bool file_save_dialog = false;
    bool file_load_dialog = false;

    // filename input buffer
    char *text_input = new char[256]{0};

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(LIGHTGRAY);

        if (file_save_dialog || file_load_dialog) {
            GuiLock();
        }

        
        if (auto_sim && !file_save_dialog) {
            time_counter += GetFrameTime() * sim_speed * 6;
            if (time_counter >= 1.0f) {
                time_counter = 0.0f;
                my_grid.update();
            }
        }

        // mouse control
        current_ind = GetGridIndexFromPoint(my_grid, GetMouseX(), GetMouseY());

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

        // keyboard controls
        current_key = GetKeyPressed();

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

        // GUI hell
        // horizontal bar

        DrawRectangle(5, 5, GetRenderWidth() - 10, 40, WHITE);
        float button_width = GetScreenWidth() / 24 > 48 ? GetScreenWidth() / 24 : 48;

        // quit
        if (GuiButton(Rectangle{10.0f, 10.0f, 30.0f, 30.0f}, "#159#")) {
            EndDrawing();
            break;
        }

        if (GuiButton(Rectangle{50.0f, 10.0f, 90.0f, 30.0f}, TextFormat("SIZE: %dx%d", my_grid.width(), my_grid.height()))) {
            my_grid.resize(100, 50); // resize to default width and height
        }

        GuiStatusBar(Rectangle{150.0f, 10.0f, 60.0f, 30.0f}, TextFormat("FPS: %d", GetFPS()));

        GuiStatusBar(Rectangle{220.0f, 10.0f, button_width * 2.5f, 30.0f}, TextFormat("ALIVE: %d/%d", my_grid.count_alive(), my_grid.size()));

        GuiToggle(Rectangle{230.0f + button_width * 2.5f, 10.0f, button_width * 1.5f, 30.0f}, "#140# DEBUG", &show_debug);

        if (show_debug) {
            GuiStatusBar(Rectangle{240.0f + button_width * 4.0f, 10.0f, button_width * 2.5f, 12.0f},
                         TextFormat("X: %4d Y: %4d", GetMouseX(), GetMouseY()));

            GuiStatusBar(Rectangle{240.0f + button_width * 4.0f, 28.0f, button_width * 2.5f, 12.0f},
                         TextFormat("#%-5d {%-4d, %-4d}", current_ind, my_grid.get_x(current_ind), my_grid.get_y(current_ind)));

            GuiStatusBar(Rectangle{250.0f + button_width * 6.5f, 10.0f, 50.0f, 12.0f}, TextFormat("#186# %1d", my_grid.get_status(current_ind)));
            GuiStatusBar(Rectangle{250.0f + button_width * 6.5f, 28.0f, 50.0f, 12.0f}, TextFormat("#89# %1d", my_grid.count_neighbors(current_ind)));
        }


        // vertical bar
        DrawRectangle(5, 50, 80, GetRenderHeight() - 55, WHITE);
        float button_height = GetRenderHeight() / 16 > 36 ? GetRenderHeight() / 16 : 36;

        GuiToggle(Rectangle{10.0f, 55.0f, 70.0f, button_height}, "#193#HELP", &show_help);

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 1.3f, 30.0f, button_height}, "#119#")) {
            if (!auto_sim) {
                my_grid.update();
            }
        }

        GuiToggle(Rectangle{50.0f, 55.0f + button_height * 1.3f, 30.0f, button_height}, "#77#", &auto_sim);

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 2.6f, 70.0f, button_height / 2}, "SPEED")) {
            sim_speed = 4;
        }
        if (GuiSpinner(Rectangle{10.0f, 55.0f + button_height * 3.2f, 70.0f, button_height / 2}, "", &sim_speed, 0, 10, speed_edit_mode)) {
            speed_edit_mode = !speed_edit_mode; 
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 4.0f, 70.0f, button_height / 2}, "RESIZE BY:")) {
            resize_factor = 1;
        }
        if (GuiSpinner(Rectangle{10.0f, 55.0f + button_height * 4.6f, 70.0f, button_height / 2}, "", &resize_factor, 1, 10, resize_edit_mode)) {
            resize_edit_mode = !resize_edit_mode; 
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 5.4f, 70.0f, button_height}, "CLEAR")) {
            for (int i = 0; i < my_grid.size(); ++i) {
                my_grid.set_dead(my_grid.get_x(i), my_grid.get_y(i));
            }
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 6.7f, 70.0f, button_height}, "#6# SAVE")) {
            file_save_dialog = true;
        }

        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 8.1f, 70.0f, button_height}, "#5# LOAD")) {
            file_load_dialog = true;
        }

        // resize controls
        // up
        if (GuiButton(Rectangle{30.0f, 55.0f + button_height * 9.4f, 30.0f, button_height / 2}, "#117#")) {
            my_grid.resize(my_grid.width(), my_grid.height() - resize_factor);
        }

        // left
        if (GuiButton(Rectangle{10.0f, 55.0f + button_height * 10.1f, 30.0f, button_height / 2}, "#114#")) {
            my_grid.resize(my_grid.width() - resize_factor, my_grid.height());
        }

        // right
        if (GuiButton(Rectangle{50.0f, 55.0f + button_height * 10.1f, 30.0f, button_height / 2}, "#115#")) {
            my_grid.resize(my_grid.width() + resize_factor, my_grid.height());
        }

        // down
        if (GuiButton(Rectangle{30.0f, 55.0f + button_height * 10.8f, 30.0f, button_height / 2}, "#116#")) {
            my_grid.resize(my_grid.width(), my_grid.height() + resize_factor);
        }

        DrawGrid(my_grid);
        DrawCellSelection(my_grid, current_ind);

        if (show_help) {
            DrawHelpMenu(my_grid);
        }

        if (file_save_dialog) {
            GuiUnlock();
            
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.8f));

            int button_active = -1;

                GuiTextInputBox(Rectangle{(float) GetScreenWidth() / 2 - 120, (float) GetScreenHeight() / 2 - 80.0f, 240, 160}, 
                    "#6# SAVE FILE", "Enter a filename:", text_input, 255, "Save;Cancel", &button_active, nullptr);

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
                    "#5# LOAD FILE", "Enter a filename:", text_input, 255, "Load;Cancel", &button_active, nullptr);

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
