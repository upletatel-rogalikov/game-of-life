#ifndef GRAPHICS_H
#define GRAPHICS_H

void DrawGrid(const Grid& gr);

int GetCellSize(const Grid& gr);

int GetGridIndexFromPoint(const Grid& gr, int screen_x, int screen_y);

void DrawCellSelection(const Grid& gr, int index);

#endif
