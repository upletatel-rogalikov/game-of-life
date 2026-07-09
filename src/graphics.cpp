#include "raylib.h"
#include "grid.h"
#include "graphics.h"

//int cell_size = 30;

// add bool to turn borders inside the frame on/off

int GetCellSize(const Grid& gr) {
    int result_x = (GetRenderWidth() - 2 * gr.origin_x()) / gr.width();
    int result_y = (GetRenderHeight() - 2 * gr.origin_y()) / gr.height();

    if (result_x < 1 || result_y < 1)
        return 1;

    return result_x > result_y ? result_y : result_x;
}

int GetGridIndexFromPoint(const Grid& gr, int screen_x, int screen_y) {
	const int cell_size = GetCellSize(gr);
	int x, y;

	x = (screen_x - gr.origin_x());
	y = (screen_y - gr.origin_y());

	if (x < 0 || y < 0)
		return -1;

	x /= cell_size; 
	y /= cell_size; 

	if (x < 0 || x >= gr.width() || y < 0 || y >= gr.height())
	{
		return -1;
	}

	return gr.get_index(x, y);
}

void DrawCellSelection(const Grid& gr, int index) {
    if (index < 0)
        return;
    DrawRectangleLinesEx(Rectangle{(float) gr.origin_x() + GetCellSize(gr) * gr.get_x(index),
                                  (float) gr.origin_y() + GetCellSize(gr) * gr.get_y(index),
                                  (float) GetCellSize(gr), (float) GetCellSize(gr)}, (float) GetCellSize(gr) / 8, BLUE);
    return;
}

void DrawGrid(const Grid& gr) { 

    const int cell_size = GetCellSize(gr);

    // borders

    //top hor
    DrawLineEx( Vector2{(float) gr.origin_x(), (float) gr.origin_y() - 5},
                Vector2{(float) gr.origin_x() + 1 + (gr.width() * cell_size), (float) gr.origin_y() - 5},
                10.0f, GRAY);
    //bottom hor
    DrawLineEx( Vector2{(float) gr.origin_x(), (float) gr.origin_y() + 5 + (gr.height() * cell_size)},
                Vector2{(float) gr.origin_x() + 1 + (gr.width() * cell_size), (float) gr.origin_y() + 5 + (gr.height() * cell_size)},
                10.0f, GRAY);
    //left vert
    DrawLineEx( Vector2{(float) gr.origin_x() - 5, (float) gr.origin_y() - 10},
                Vector2{(float) gr.origin_x() - 5, (float) gr.origin_y() + 10 + (gr.height() * cell_size)},
                10.0f, GRAY);

    //right vert
    DrawLineEx( Vector2{(float) gr.origin_x() + 5 + (gr.width() * cell_size), (float) gr.origin_y() - 10},
                Vector2{(float) gr.origin_x() + 5 + (gr.width() * cell_size), (float) gr.origin_y() + 10 + (gr.height() * cell_size)},
                10.0f, GRAY);

    // insides
    for (int i = 0; i < gr.size(); ++i) {
        if (gr.get_status(gr.get_x(i), gr.get_y(i))) {

            DrawRectangle(  gr.origin_x() + gr.get_x(i) * cell_size,
                            gr.origin_y() + gr.get_y(i) * cell_size,
                            cell_size, cell_size, BLACK);  
        }
    }
    return;
}



