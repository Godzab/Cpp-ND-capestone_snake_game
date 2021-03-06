#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <mutex>

#include "Board.h"
#include "Apple.h"
#include "Empty.h"
#include "Player.h"

//Mapping to Ascii character codes.
enum GameContols {
    K_UP = 119,     // W
    K_DOWN = 115,   // S
    K_LEFT = 97,    // A
    K_RIGHT = 100   // D
};

class Game {
public:
    Game(std::unique_ptr<Board> bd, std::shared_ptr<Player> plr);

    //Destructor
    ~Game();

    //copy constructor
    Game(Game &game);

    //copy assignment constructor
    Game &operator=(Game const &game);

    //move constructor
    Game(Game &&game) noexcept;

    //move assignment constructor
    Game &operator=(Game &&game) noexcept;

    //Getters and mutators
    void processInput();

    void updateState();

    void redraw();

    bool isOver() const;

    void checkRules();

    void getTopScore();

    void setTopScore();

private:
    void initialize();

    std::unique_ptr<Board> board;
    std::shared_ptr<Player> player;
    Apple *apple;

    std::mutex mtx;
    bool game_over{false};
    int score{0};
    int top_score{0};
};

#endif