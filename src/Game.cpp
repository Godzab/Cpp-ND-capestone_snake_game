#include <random>
#include <chrono>
#include <iostream>
#include <ncurses.h>
#include <mutex>

#include "Game.h"
#include "Apple.h"
#include "Player.h"
#include "Drawable.h"
  
Game::Game(std::unique_ptr<Board> bd, std::shared_ptr<Player> plr){
    this->board = std::move(bd);
    this->player = plr;
    game_over = false;
    this->initialize();
}

Game::~Game(){
    if(apple != nullptr)
        delete apple;
}

void Game::processInput(){
    char input = board->getInput();
    wprintw(stdscr, "Input Received: %d", input);
    std::lock_guard<std::mutex> lock(mtx);
    switch (input)
    {
    case 119:
        player->updateDirection(Direction::UP);
        break;
    case 115:
        player->updateDirection(Direction::DOWN);
        break;
    case 97:
        player->updateDirection(Direction::LEFT);
        break;
    case 100:
        player->updateDirection(Direction::RIGHT);
        break;
    default:
        break;
    }
    //Will process input later on.
}

void Game::updateState(){
    int y;
    int x;

    PlayerPiece player_head = player->head();
    //Place the apple in an area not outside 
    //arena and not on snake body.
    board->getEmptyCoordinates(y, x);

    //Clear previous apple location if snake-head is at apple location.
    if(apple != nullptr && (player_head.getX() == apple->getX() && player_head.getY() == apple->getY())){
        board->add(Empty(apple->getY(), apple->getX()));
        delete apple;
        PlayerPiece pc(player->tail().getY() + 1, player->tail().getX());
        player->addPiece(pc);
        apple = new Apple(y, x);
        board->add(*apple);
    }

    //Snake placement
    //Clear previos state on board
    for(PlayerPiece pp : player->body){
        board->add(Empty(pp.getY(), pp.getX()));
    }

    //Populate new position.
    player->update();
    for(PlayerPiece pp : player->body){
        board->add(pp);
    }

    board->Refresh();
}
void Game::redraw(){
    board->Refresh();
}
bool Game::isOver(){
    return this->game_over;
}

void Game::initialize(){
    int x; 
    int y;
    board->getEmptyCoordinates(y, x);
    apple = new Apple(y, x);
    board->add(*apple);
}