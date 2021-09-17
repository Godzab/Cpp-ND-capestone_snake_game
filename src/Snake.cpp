#include <memory>
#include <thread>
#include <chrono>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#define BOARD_W 50
#define BOARD_H 20

using namespace std;

int main(){
    initscr();
    noecho();

    //Initializes the board on construction
    unique_ptr<Board> board = make_unique<Board>(20, 50);
    shared_ptr<Player> player = make_shared<Player>();
    Game snk_game(move(board), player);

    /**
     * Side-car game loop. 
     * non-blocking thread to monitor input.
     */
    thread gameInputThread([&snk_game](){
        while(!snk_game.isOver()){
            snk_game.processInput();
        }
    }); 

    /**
     * Main game loop, updates interface, handles state.
     */
    while(!snk_game.isOver()){
        snk_game.updateState();
        snk_game.checkSelf();
        snk_game.redraw();
        //More elaborate game ticks strategy required.
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    getch();
    gameInputThread.join();
    endwin();
    return 0;
}