#include "raylib.h"

constexpr int SCREEN_WIDTH  = 640;
constexpr int SCREEN_HEIGHT = 480;

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("hello raylib w/ cmake!\n", 200, 200, 18, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
