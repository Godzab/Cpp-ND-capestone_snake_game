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
    void setX(int x);
    void setY(int y);
    Direction getDirection();
private:
     Direction cur_direction;
};

/**
 * This will represent the snake on the board.
 * It is build up of individual pieces as defined above.
 */
class Player{
public:
    Player();
    void addPiece(PlayerPiece piece);
    void updateDirection(Direction);
    Direction getDirection();
    void update(const int &width, const int &height);
    PlayerPiece tail();
    PlayerPiece head();
    std::vector<PlayerPiece> body;
private:
    Direction cur_direction;
};

#endif