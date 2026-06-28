#include "grid.h"

#include <vector>

Grid::Grid() :size_x{10}, size_y{10} {
    cellv = std::vector<int>(size_x * size_y, 0);
    tempv = cellv;
}

Grid::Grid(int s_x, int s_y) :size_x{s_x}, size_y{s_y} {
    cellv = std::vector<int>(size_x * size_y, 0);
    tempv = cellv;
}

int Grid::size() const {
    return size_x * size_y;
}

int Grid::width() const {
    return size_x;
}

int Grid::height() const {
    return size_y;
}

int Grid::get_x(int index) const {
    return index % size_x;
}

int Grid::get_y(int index) const {
    return index / size_x;
}

int Grid::get_status(int x, int y) const {
    return cellv[x + y * size_x];
}

void Grid::set_alive(int x, int y) {
    cellv[x + y * size_x] = 1;
}

void Grid::set_dead(int x, int y) {
    cellv[x + y * size_x] = 0;
}


