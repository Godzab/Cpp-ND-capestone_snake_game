#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "Drawable.h"

enum Direction{UP, DOWN, LEFT,RIGHT};

class PlayerPiece: public Drawable{
public:
    PlayerPiece();
    PlayerPiece(int y, int x);
    void moveNext(int width, int height);
    void setIcon(char icon);
    void setDirection(Direction dir);
    Direction getDirection(char icon);
private:
     Direction cur_direction;
};

/**
 * This will represent the snake on the board.
 * It is build up of individual pieces as defined above.
 */
class Player{
public:
    Player(){ cur_direction = Direction::DOWN; }
    void addPiece(PlayerPiece piece);
    void removePiece();
    void updateDirection(Direction);
    void update(const int &width, const int &height);
    PlayerPiece tail();
    PlayerPiece head();
    std::vector<PlayerPiece> body;
    bool should_grow{false};
private:
    Direction cur_direction;
};

#endif