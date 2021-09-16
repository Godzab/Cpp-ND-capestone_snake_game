#include <ncurses.h>

#include "Board.h"
#include "Drawable.h"

Board::Board(int h, int w): height(h), width(w){
    keypad(board_window, true);
    getmaxyx(stdscr, y_max, x_max);
    board_window = newwin(height, width, (y_max/2)-(height/2), (x_max/2) - (width/2));
    w_distribution = std::uniform_int_distribution<int>(0, (y_max/2) - (height/2));
    h_distribution = std::uniform_int_distribution<int>(0, (x_max/2) - (width/2));
    initialize();
}

Board::~Board(){
    delete board_window;
}

void Board::initialize(){
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
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    
    //Not too readable
    while((mvwinch(board_window,y = w_distribution(generator), x = h_distribution(generator))) != ' ');
}