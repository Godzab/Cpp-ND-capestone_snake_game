#include <ncurses.h>

#include "Board.h"
#include "Drawable.h"

auto seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator(seed);

Board::Board(int h, int w): height(h), width(w){
    keypad(board_window, true);
    getmaxyx(stdscr, y_max, x_max);
    start_end_y[0] = (y_max/2)-(height/2);
    start_end_y[1] = (y_max/2)-(height/2) + height;
    start_end_x[0] = (x_max/2) - (width/2);
    start_end_x[1] = (x_max/2) - (width/2) + width;
    board_window = newwin(height, width, start_end_y[0], start_end_x[0]);
    w_distribution = std::uniform_int_distribution<int>(0, start_end_y[0]);
    h_distribution = std::uniform_int_distribution<int>(0, start_end_x[0]);
    initialize();
}

void Board::initialize(){
    printw("y start: %d, y end: %d \n", start_end_y[0], start_end_y[1]);
    printw("x start: %d, x end: %d \n", start_end_x[0], start_end_x[1]);
    clear();
    Refresh();
}

void Board::addBorder(){
    box(board_window, 0, 0);
}

void Board::clear(){
    wclear(board_window);
    addBorder();
}

void Board::Refresh(){
    refresh();
    wrefresh(board_window);
}

void Board::add(Drawable d){
    mvwaddch(board_window, d.getY(), d.getX(), d.getIcon());
}

void Board::addAt(int y, int x, char chr){
    mvwaddch(board_window, y, x, chr);
}

/**
 * We get a refresh for free with this.
 * Grabs input from selected window.
 */
char Board::getInput(){
    return wgetch(board_window);
}

void Board::getEmptyCoordinates(int &y, int &x){
    //Not too readable
    while((mvwinch(board_window,y = w_distribution(generator), x = h_distribution(generator))) != ' ');
}