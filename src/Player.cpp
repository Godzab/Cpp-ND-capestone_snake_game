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

void PlayerPiece::setX(int x){
    this->x = x; 
}

void PlayerPiece::setY(int y){
    this->y = y; 
}

/**
 * Sets the next direction of the piece
 * Mainly used by snake's head.
 */
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
Direction PlayerPiece::getDirection(){
    return this->cur_direction;
}

/**
 * Player Class methods
 */

PlayerPiece Player::tail(){
    return body.front();
}

PlayerPiece Player::head(){
    body.back().setIcon('@');
    return body.back();
}

Player::Player(){
    this->addPiece(PlayerPiece(4, 7));
    this->addPiece(PlayerPiece(5, 7));
    this->addPiece(PlayerPiece(6, 7));
    cur_direction = Direction::DOWN;
}

void Player::addPiece(PlayerPiece piece){
    body.insert(body.begin(), piece);
}

void Player::removePiece(){
    body.pop_back();
}

void Player::updateDirection(Direction dir){
    this->cur_direction = dir;
}

Direction Player::getDirection(){
    return this->cur_direction;
}

void Player::update(const int &width, const int &height){
    int y_x[2] = {this->head().getY(), this->head().getX()}; 
    if(should_grow){
        should_grow = !should_grow;
        body.push_back(PlayerPiece(tail().getY() + 1, tail().getX()));
    }
    for(PlayerPiece &pc : body){
        if(pc.getX() == this->head().getX() && pc.getY() == this->head().getY()){
            pc.setDirection(this->cur_direction);
            pc.moveNext(width-1, height);
        } else{
            pc.setIcon('#');
            int tmp[2] = {pc.getY(), pc.getX()};
            pc.setY(y_x[0]);
            pc.setX(y_x[1]);
            y_x[0] = tmp[0];
            y_x[1] = tmp[1];
        }
    }
}