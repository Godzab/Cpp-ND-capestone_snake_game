#ifndef _BOARD_H_
#define _BOARD_H_

#include "Drawable.h"
#include <chrono>
#include <random>
#include <ncurses.h>

class Board{
public:
    Board(){
        Board(0, 0);
    }
    Board(int h, int w);
    ~Board();
    void addBorder();
    void clear();
    void Refresh();
    void initialize();
    void getEmptyCoordinates(int &y, int &x);
    void add(Drawable drawable);
    void addAt(int, int, char);
    char getInput();

private:
    int x_max;  
    int y_max;
    int height;
    int width;

    std::uniform_int_distribution<int> w_distribution;
    std::uniform_int_distribution<int> h_distribution;

    WINDOW* board_window;
};
#endif