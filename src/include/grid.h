#ifndef GRID_H
#define GRID_H

#include <vector>

class Grid {

public:
    Grid();
    Grid(int s_x, int s_y);

    int size() const;
    int width() const;
    int height() const;
    int get_status(int x, int y) const;
    int get_x(int index) const;
    int get_y(int index) const;

    void set_alive(int x, int y);
    void set_dead(int x, int y);
    

private:
    int size_x;
    int size_y;
    
    std::vector<int> cellv;
    std::vector<int> tempv;

};
#endif
