#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <mutex>

#include "Board.h"
#include "Apple.h"
#include "Empty.h"
#include "Player.h"

//Mapping to Ascii character codes.
enum GameContols{
    K_UP = 119,
    K_DOWN = 115,
    K_LEFT = 97,
    K_RIGHT = 100
};

class Game{
public:
    Game();
    ~Game();
    Game(std::unique_ptr<Board> bd, std::shared_ptr<Player> plr);
    void processInput();
    void updateState();
    void redraw();
    bool isOver();

private:
    void initialize();
    std::unique_ptr<Board> board;
    bool game_over;
    Apple *apple;
    std::shared_ptr<Player> player;
    std::mutex mtx;
};

#endif