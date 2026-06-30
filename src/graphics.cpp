#include "raylib.h"
#include "grid.h"
#include "graphics.h"

//int cell_size = 30;

// add bool to turn borders inside the frame on/off
// fix float conversion

void DrawGrid(const Grid& gr, int origin_x, int origin_y) { 
    // let the user change the cell_size, but auto-resize by default
    int cell_size = GetScreenWidth() / 8 / gr.width() > 5 ? GetScreenWidth() / 8 / gr.width() : 5;
    // borders

    //top hor
    DrawLineEx( Vector2{(float) origin_x, (float) origin_y - 5},
                Vector2{(float) origin_x + 1 + (gr.width() * cell_size), (float) origin_y - 5},
                10.0f, BLACK);
    //bottom hor
    DrawLineEx( Vector2{(float) origin_x, (float) origin_y + 5 + (gr.height() * cell_size)},
                Vector2{(float) origin_x + 1 + (gr.width() * cell_size), (float) origin_y + 5 + (gr.height() * cell_size)},
                10.0f, BLACK);
    //left vert
    DrawLineEx( Vector2{(float) origin_x - 5, (float) origin_y - 10},
                Vector2{(float) origin_x - 5, (float) origin_y + 10 + (gr.height() * cell_size)},
                10.0f, BLACK);

    //right vert
    DrawLineEx( Vector2{(float) origin_x + 5 + (gr.width() * cell_size), (float) origin_y - 10},
                Vector2{(float) origin_x + 5 + (gr.width() * cell_size), (float) origin_y + 10 + (gr.height() * cell_size)},
                10.0f, BLACK);

    // insides

    for (int i = 0; i < gr.size(); ++i) {
        if (gr.get_status(gr.get_x(i), gr.get_y(i))) {

            DrawRectangle(  origin_x + gr.get_x(i) * cell_size,
                            origin_y + gr.get_y(i) * cell_size,
                            cell_size, cell_size, BLUE);  
        }
    }
}



