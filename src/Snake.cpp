#include <memory>
#include <thread>
#include <chrono>

#include "Board.h"
#include "Game.h"
#include "Player.h"

#define BOARD_W 50
#define BOARD_H 20

using namespace std;

int main() {
    Board::startRenderer();
    unique_ptr<Board> board = make_unique<Board>(BOARD_H, BOARD_W);
    shared_ptr<Player> player = make_shared<Player>();
    Game snk_game(move(board), player);

    /**
     * Side-car game loop. 
     * non-blocking thread to monitor input.
     */
    thread gameInputThread([&snk_game]() {
        while (!snk_game.isOver()) {
            snk_game.processInput();
        }
        this_thread::sleep_for(chrono::milliseconds(1));
    });

    /**
     * Main game loop, updates interface, handles state.
     */
    while (!snk_game.isOver()) {
        snk_game.updateState();
        snk_game.checkRules();
        snk_game.redraw();
        this_thread::sleep_for(chrono::milliseconds(200));
    }

    gameInputThread.join();
    Board::terminateRenderer();
    return 0;
}