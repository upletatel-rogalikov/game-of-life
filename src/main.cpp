#include "raylib.h"

constexpr int SCREEN_WIDTH  = 1280;
constexpr int SCREEN_HEIGHT = 720;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(10, 10);
        DrawText("Hello raylib!\nBuilt on windows and linux using cmake!", 50, 200, 32, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
