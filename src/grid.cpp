#include "grid.h"

#include <vector>
#include <iostream>
#include <utility>

Grid::Grid() :orgn_x{100}, orgn_y{100}, size_x{10}, size_y{10} {
    cellv = std::vector<int>(size_x * size_y, 0);
    tempv = cellv;
}

Grid::Grid(int or_x, int or_y, int s_x, int s_y) :orgn_x{or_x}, orgn_y{or_y}, size_x{s_x}, size_y{s_y} {
    cellv = std::vector<int>(size_x * size_y, 0);
    tempv = cellv;
}

// remove unused

int Grid::size() const {
    return size_x * size_y;
}

int Grid::width() const {
    return size_x;
}

int Grid::height() const {
    return size_y;
}

int Grid::origin_x() const {
    return orgn_x;
}

int Grid::origin_y() const {
    return orgn_y;
}

int Grid::get_x(int index) const {
    return index % size_x;
}

int Grid::get_y(int index) const {
    return index / size_x;
}

int Grid::get_index(int x, int y) const {
    while (x < 0) {
        x += size_x;
    }

    while (y < 0) {
        y += size_y;
    }

    x %= size_x;
    y %= size_y;
    return x + y * size_x;
}

int Grid::get_status(int x, int y) const {
    return cellv[x + y * size_x];
}

void Grid::set_alive(int x, int y) {
    cellv[x + y * size_x] = 1;
    return;
}

void Grid::set_dead(int x, int y) {
    cellv[x + y * size_x] = 0;
    return;
}

// update method implementation
int Grid::count_neighbors(int index) {
    int result = 0;

    int c_x = this->get_x(index);
    int c_y = this->get_y(index);

    // std::cout << "x: " << c_x << ", y: " << c_y << "\n";

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int x = c_x + i;
            int y = c_y + j;

            if (i == 0 && j == 0) {
                continue;
            }
            // std::cout << "x: " << x << ", y: " << y << "\n";
            if (cellv[get_index(x, y)] == 1) {
                result++;
            }
        }
    }
    // for (int i = -1; i < 2; ++i) {
    //     for (int j = -1; j < 2; ++j) {
    //         if (i == 0 && j == 0)
    //             continue;
    //         if (cellv[((this->get_x(index) + i + size_x) % size_x) + (((this->get_y(index) + j + size_y)) % size_y) * size_x]) {
    //             ++result;
    //         }
    //     }
    // }

    // if (cellv[(this->get_x(index) + 1 + size_x) % size_x + (this->get_y(index) + 1 + size_y) % size_y * size_x]) {
    //     result++;
    // }
    return result;
}

void Grid::update() {
    for (int i = 0; i < this->size(); ++i) {
       int neighbors = this->count_neighbors(i);
       // std::cout << "cell #" << i << " -> " << neighbors << " neighbors\n";

       if (neighbors < 2) {
            tempv[i] = 0;
       }

       if (neighbors == 2 && cellv[i] == 1) {
           tempv[i] = 1;
       }

       if (neighbors == 3) {
            tempv[i] = 1;
       }

       if (neighbors > 3) {
            tempv[i] = 0;
       }
    }
    cellv = tempv;
    tempv = std::vector<int>(this->size(), 0);
    return;
}

void Grid::resize(int new_width, int new_height) {
    if (new_width < 1 || new_height < 1) {
        return;
    }

    int old_width = this->width();
    int old_height = this->height();

    int min_width = new_width >= old_width ? old_width : new_width;
    int min_height = new_height >= old_height ? old_height : new_height;

    std::vector<int> new_cellv = std::vector<int>(new_width * new_height, 0);

    for (int i = 0; i < min_width; ++i) {
        for (int j = 0; j < min_height; ++j) {
            new_cellv[i + j * new_width] = cellv[i + j * old_width];
        }
    }

    size_x = new_width;
    size_y = new_height;
    cellv = std::move(new_cellv);
    tempv = std::vector<int>(new_width * new_height, 0);
    return;
}
