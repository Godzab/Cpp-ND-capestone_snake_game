#ifndef _BOARD_H_
#define _BOARD_H_

#include "Drawable.h"
#include <chrono>
#include <random>
#include <string>
#include <ncurses.h>

class Board {
public:
    Board();

    Board(int h, int w);

    void addBorder();

    void clear();

    void Refresh();

    void initialize();

    void getEmptyCoordinates(int &, int &);

    void add(Drawable drawable, int color_code);

    void writeToStats(char *);

    char getInput();

    int height;
    int width;
    char stats_buffer[50];

    static void startRenderer();

    static void terminateRenderer();

private:
    int x_max{};
    int y_max{};
    int start_end_y{};
    int start_end_x{};

    std::uniform_int_distribution<int> w_distribution;
    std::uniform_int_distribution<int> h_distribution;

    //Game window
    WINDOW *board_window{};
    //Scores window
    WINDOW *stats_window{};
};

#endif