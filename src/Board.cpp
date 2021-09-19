#include <ncurses.h>
#include<string>

#include "Board.h"
#include "Drawable.h"

#define SCORES_WINDOW_HEIGHT 5
#define SEED std::chrono::system_clock::now().time_since_epoch().count()

Board::Board() : height(20), width(20), stats_buffer("") {
    getmaxyx(stdscr, y_max, x_max);
    start_end_y = (y_max / 2) - (height / 2);
    start_end_x = (x_max / 2) - (width / 2);

    //To confine randomised location within game window.
    w_distribution = std::uniform_int_distribution<int>(0, start_end_y);
    h_distribution = std::uniform_int_distribution<int>(0, start_end_x);
    initialize();
}

void Board::startRenderer() {
    initscr();      // start ncurses
    noecho();       // do not print input values
    cbreak();       // terminate ncurses on ctrl + c
    start_color();  // enable color

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
}

void Board::terminateRenderer() {
    //Block to show final score.
    getch();
    endwin();
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

    //Onetime board static board for Title and instructions
    WINDOW *title_window = newwin(SCORES_WINDOW_HEIGHT + 1, width, start_end_y - SCORES_WINDOW_HEIGHT - 1, start_end_x);
    box(title_window, 0, 0);
    wattron(title_window, COLOR_PAIR(3));
    mvwprintw(title_window, 1, 2, "PLAY ASCII SNAKE ");
    wattroff(title_window, COLOR_PAIR(3));
    mvwprintw(title_window, 3, 2, "Controls:");
    mvwprintw(title_window, 4, 2, "W => up, S => down, A => left, D => right");

    //Dynamic boards used throughout game.
    board_window = newwin(height, width, start_end_y, start_end_x);
    stats_window = newwin(SCORES_WINDOW_HEIGHT, width, start_end_y + height, start_end_x);

    addBorder();
    Refresh();
    wrefresh(title_window);
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

void Board::add(Drawable d, int color_code = 1) {
    wattron(board_window, COLOR_PAIR(color_code));
    mvwaddch(board_window, d.getY(), d.getX(), d.getIcon());
    wattroff(board_window, COLOR_PAIR(color_code));
}

void Board::writeToStats(char *score, bool is_top_score) {
    if (is_top_score) {
        wattron(stats_window, COLOR_PAIR(1));
        mvwprintw(stats_window, 3, 2, score);
        wattroff(stats_window, COLOR_PAIR(1));
    } else {
        wattron(stats_window, COLOR_PAIR(3));
        mvwprintw(stats_window, 1, 2, score);
        wattroff(stats_window, COLOR_PAIR(3));
    }
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