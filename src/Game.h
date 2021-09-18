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
    ~Game();
    //copy constructor
    Game(Game &game);
    //copy assignment constructor
    Game &operator = (Game const &game);
    //move constructor
    Game(Game &&game) noexcept;
    //move assignment constructor
    Game &operator = (Game &&game) noexcept;
    Game(std::unique_ptr<Board> bd, std::shared_ptr<Player> plr);

    //Getters and mutators
    void processInput();
    void updateState();
    void redraw();
    bool isOver() const;
    void checkRules();


private:
    void initialize();
    std::unique_ptr<Board> board;
    std::shared_ptr<Player> player;
    Apple *apple;

    std::mutex mtx;
    bool game_over{false};
    int score{0};
};

#endif