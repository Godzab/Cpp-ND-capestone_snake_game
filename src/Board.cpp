#include <ncurses.h>
#include<string>

#include "Board.h"
#include "Drawable.h"

auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

Board::Board(int h, int w): height(h), width(w){
    keypad(board_window, true);
    getmaxyx(stdscr, y_max, x_max);
    start_end_y = (y_max/2)-(height/2);
    start_end_x = (x_max/2) - (width/2);

    //Ensure random coodiantes fall withinn the
    w_distribution = std::uniform_int_distribution<int>(0, start_end_y);
    h_distribution = std::uniform_int_distribution<int>(0, start_end_x);
    initialize();
}

void Board::initialize(){
    clear();
    board_window = newwin(height, width, start_end_y, start_end_x);
    stats_window = newwin(5, width, start_end_y + height, start_end_x);
    addBorder();
    Refresh();
    writeToStats(0);
}

void Board::addBorder(){
    box(board_window, 0, 0);
    box(stats_window, 0, 0);
}

void Board::clear(){
    wclear(board_window);
    wclear(stats_window);
    addBorder();
}

void Board::Refresh(){
    refresh();
    wrefresh(board_window);
    wrefresh(stats_window);
}

void Board::add(Drawable d){
    mvwaddch(board_window, d.getY(), d.getX(), d.getIcon());
}

void Board::addAt(int y, int x, char chr){
    mvwaddch(board_window, y, x, chr);
}

void Board::writeToStats(int score){
    // Window height is 5 so middle is after 2 rows.
    mvwprintw(stats_window, 2, 2, "SCORES: %d", score);
}

char Board::getInput(){
    return wgetch(board_window);
}

/**
 * Randomly find the first unoccupied location on the board.
 */
void Board::getEmptyCoordinates(int &y, int &x){
    //Not too readable
    while((mvwinch(board_window,y = w_distribution(generator), x = h_distribution(generator))) != ' ');
}