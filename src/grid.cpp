#include "grid.h"

#include <vector>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>

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

    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int x = c_x + i;
            int y = c_y + j;

            if (i == 0 && j == 0) {
                continue;
            }

            if (cellv[get_index(x, y)] == 1) {
                result++;
            }
        }
    }
    return result;
}

void Grid::update() {
    for (int i = 0; i < this->size(); ++i) {
       int neighbors = this->count_neighbors(i);

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

    if (old_width == new_width && old_height == new_height) {
        return;
    }

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

void Grid::save(std::string filename) {
    std::ofstream out_file(filename, std::ios::binary);

    out_file.write(reinterpret_cast<char*>(&orgn_x), sizeof orgn_x);
    out_file.write(reinterpret_cast<char*>(&orgn_y), sizeof orgn_y);
    out_file.write(reinterpret_cast<char*>(&size_x), sizeof size_x);
    out_file.write(reinterpret_cast<char*>(&size_y), sizeof size_y);
    // out_file << this->orgn_x;
    // out_file << this->orgn_y;
    // out_file << this->size_x;
    // out_file << this->size_y;

    std::cout << "saving 1 step complete\n";
    std::cout << "origin_x: " << this->orgn_x << "\n";
    std::cout << "origin_y: " << this->orgn_y << "\n";
    std::cout << "size_x: " << this->size_x << "\n";
    std::cout << "size_y: " << this->size_y << "\n";

    for (int i = 0; i < this->cellv.size(); ++i) {
        out_file.write(reinterpret_cast<char*>(&cellv[i]), sizeof cellv[i]);
        // out_file << this->cellv[i];
    }
    std::cout << "saving complete\n";

    return;
}

void Grid::load(std::string filename) {
    std::ifstream in_file(filename, std::ios::binary);

    in_file.read(reinterpret_cast<char*>(&orgn_x), sizeof orgn_x);
    in_file.read(reinterpret_cast<char*>(&orgn_y), sizeof orgn_y);
    in_file.read(reinterpret_cast<char*>(&size_x), sizeof size_x);
    in_file.read(reinterpret_cast<char*>(&size_y), sizeof size_y);
    // in_file >> this->orgn_x;
    // in_file >> this->orgn_y;
    // in_file >> this->size_x;
    // in_file >> this->size_y;

    std::cout << "loading 1 step complete\n";
    std::cout << "origin_x: " << this->orgn_x << "\n";
    std::cout << "origin_y: " << this->orgn_y << "\n";
    std::cout << "size_x: " << this->size_x << "\n";
    std::cout << "size_y: " << this->size_y << "\n";

    this->cellv = std::vector<int>(size_x * size_y, 0);
    this->tempv = cellv;


    for (int i = 0; i < this->cellv.size(); ++i) {
        in_file.read(reinterpret_cast<char*>(&cellv[i]), sizeof cellv[i]);
        // in_file >> this->cellv[i];
    }
    std::cout << "loading complete\n";

    return;
}
