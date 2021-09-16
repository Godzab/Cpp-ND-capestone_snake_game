#include "Player.h"

/**
 * Playerpiece methods
 */
PlayerPiece::PlayerPiece(){
    PlayerPiece(0, 0);
}

PlayerPiece::PlayerPiece(int y, int x){
    this->x = x;
    this->y = y;
    this->icon = '#';
}

void PlayerPiece::moveNext(Direction dir){
    if(dir == Direction::DOWN){
        this->y += 1;
    } else if(dir == Direction::UP){
        this->y -= 1;
    } else if(dir == Direction::LEFT){
        this->x -= 1;
    } else {
        this->x += 1;
    }
}

void PlayerPiece::setIcon(char c){
    this->icon = c;
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
void Player::update(){
    if(should_grow){
        should_grow = !should_grow;
        body.push_back(PlayerPiece(tail().getY() + 1, tail().getX()));
    }
    for(PlayerPiece &pc : body){
        pc.moveNext(this->cur_direction);
    }
}