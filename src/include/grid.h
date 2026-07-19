#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class Grid {

public:
    Grid();
    Grid(int or_x, int or_y, int s_x, int s_y);

    int size() const;
    int width() const;
    int height() const;
    int origin_x() const;
    int origin_y() const;

    int get_status(int x, int y) const;
    int get_x(int index) const;
    int get_y(int index) const;
    int get_index(int x, int y) const;

    void set_alive(int x, int y);
    void set_dead(int x, int y);
    
    int count_neighbors(int index);
    void resize(int new_width, int new_height);
    void update();

    void save(std::string filename);
    void load(std::string filename);

private:
    int orgn_x;
    int orgn_y;

    int size_x;
    int size_y;
    
    std::vector<int> cellv;
    std::vector<int> tempv;

};
#endif
