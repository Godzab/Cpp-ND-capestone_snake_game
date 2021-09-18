#include <ncurses.h>
#include<string>

#include "Board.h"
#include "Drawable.h"

#define SCORES_WINDOW_HEIGHT 5
#define SEED std::chrono::system_clock::now().time_since_epoch().count()

Board::Board() : height(20), width(20) {
    getmaxyx(stdscr, y_max, x_max);
    start_end_y = (y_max / 2) - (height / 2);
    start_end_x = (x_max / 2) - (width / 2);

    //To confine randomised location within game window.
    w_distribution = std::uniform_int_distribution<int>(0, start_end_y);
    h_distribution = std::uniform_int_distribution<int>(0, start_end_x);
    initialize();
}

Board::Board(int h, int w) : height(h), width(w) {
    getmaxyx(stdscr, y_max, x_max);
    start_end_y = (y_max / 2) - (height / 2);
    start_end_x = (x_max / 2) - (width / 2);

    //To confine randomised location within game window.
    w_distribution = std::uniform_int_distribution<int>(0, start_end_y);
    h_distribution = std::uniform_int_distribution<int>(0, start_end_x);
    initialize();
}


void Board::initialize() {
    clear();
    board_window = newwin(height, width, start_end_y, start_end_x);
    stats_window = newwin(SCORES_WINDOW_HEIGHT, width, start_end_y + height, start_end_x);

    addBorder();
    Refresh();
}

void Board::addBorder() {
    box(board_window, 0, 0);
    box(stats_window, 0, 0);
}

void Board::clear() {
    wclear(board_window);
    wclear(stats_window);
    addBorder();
}

void Board::Refresh() {
    refresh();
    wrefresh(board_window);
    wrefresh(stats_window);
}

void Board::add(Drawable d) {
    mvwaddch(board_window, d.getY(), d.getX(), d.getIcon());
}

void Board::writeToStats(char * score) {
    mvwprintw(stats_window, 2, 2, score);
}

char Board::getInput() {
    return wgetch(board_window);
}

/**
 * Randomly find the first unoccupied location on the board.
 */
void Board::getEmptyCoordinates(int &y, int &x) {
    std::default_random_engine generator(SEED);
    while ((mvwinch(board_window, y = w_distribution(generator), x = h_distribution(generator))) != ' ');
}