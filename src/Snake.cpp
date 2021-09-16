#include <memory>
#include <thread>
#include <chrono>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#define BOARD_SIZE 20
#define BOARD_W BOARD_SIZE * 2.5
#define BOARD_H BOARD_SIZE

using namespace std;

int main(){
    initscr();
    noecho();

    //Initializes the board on construction
    unique_ptr<Board> board = make_unique<Board>(20, 50);
    shared_ptr<Player> player = make_shared<Player>();
    player->addPiece(PlayerPiece(4, 7));
    player->addPiece(PlayerPiece(5, 7));
    player->addPiece(PlayerPiece(6, 7));
    
    Game snk_game(move(board), player);
    
    /**
     * Separate thread to monitor input which is non-blocking.
     */
    thread t([&snk_game](){
        while(!snk_game.isOver()){
            snk_game.processInput();
        }
    }); 

    /**
     * Main game loop, updates interface, handles state.
     */
    while(!snk_game.isOver()){
        snk_game.updateState();

        snk_game.redraw();

        //More elaborate game ticks strategy required.
        this_thread::sleep_for(chrono::milliseconds(250));
    }

    t.join();
    getch();
    endwin();
    return 0;
}