#include <ncurses.h>
#include "Player.h"

/**
 * Playerpiece methods
 */
PlayerPiece::PlayerPiece(){
    PlayerPiece(0, 0);
}

PlayerPiece::PlayerPiece(int y, int x):cur_direction(Direction::DOWN){
    this->x = x;
    this->y = y;
    this->icon = '#';
}

void PlayerPiece::moveNext(int width, int height){
    switch (this->cur_direction)
    {
        case Direction::DOWN:
            this->y = (this->y + 1) % (height + 1) == height - 1 ? 1 : (this->y + 1) % (height + 1);
            break;
        case Direction::UP:
            this->y = abs(this->y - 1) % (height) == 0 ? height-1 : abs(this->y - 1) % (height-1);
            break;
        case Direction::LEFT:
            this->x = abs(this->x - 1) % (width) == 0 ? width-2 : abs(this->x - 1) % (width-1);
            break;
        case Direction::RIGHT:
            this->x = (this->x + 1) % (width) == width ? 1 : (this->x + 1) % (width);
            break;
        default:
            break;
    }
}

void PlayerPiece::setIcon(char c){
    this->icon = c;
}

void PlayerPiece::setDirection(Direction dir){
    this->cur_direction = dir;
}
Direction PlayerPiece::getDirection(char icon){
    return this->cur_direction;
}

/**
 * Player methods
 */

PlayerPiece Player::tail(){
    return body.back();
}

PlayerPiece Player::head(){
    return body.front();
}

void Player::addPiece(PlayerPiece piece){
    body.push_back(piece);
}
void Player::removePiece(){
    body.pop_back();
}
void Player::updateDirection(Direction dir){
    this->cur_direction = dir;
}
void Player::update(const int &width, const int &height){
    if(should_grow){
        should_grow = !should_grow;
        body.push_back(PlayerPiece(tail().getY() + 1, tail().getX()));
    }
    for(PlayerPiece &pc : body){
        if(pc.getX() == this->head().getX() && pc.getY() == this->head().getY()){
            pc.setDirection(this->cur_direction);
        }
        pc.moveNext(width, height);
    }
}