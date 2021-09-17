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

Game::Game(Game &game_cp){
    apple = new Apple(0, 0);
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
}
    //copy assignment constructor
Game &Game::operator = (Game &game_cp){
    if (this == &game_cp)
        return *this;

    apple = new Apple(0, 0);
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    score = game_cp.score;
    return *this;
}
    //move constructor
Game::Game(Game &&game_cp){
    apple = new Apple(0, 0);
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    score = game_cp.score;
    game_cp.player.reset();
}
    //move assignment constructor
Game &Game::operator = (Game &&game_cp){
    if (this == &game_cp)
        return *this;
    apple = new Apple(0, 0);
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    score = game_cp.score;
    game_cp.player.reset();

    return *this;
}

/**
 * Handles Snake controls as input from keyboard.
 * Captures the ASCII character codes for W, D, S, A to act as direction keys.
 * Prevent direction reversal. (You cannot navigate left while travelling right e.t.c)
 */
void Game::processInput(){
    char input = board->getInput();
    wprintw(stdscr, "Input Received: %d", input);
    std::lock_guard<std::mutex> lock(mtx);
    Direction cur_dir = player->getDirection();
    switch (input)
    {
    case GameContols::K_UP:
        if (cur_dir != Direction::DOWN)
        player->updateDirection(Direction::UP);
        break;
    case GameContols::K_DOWN:
        if (cur_dir != Direction::UP)
        player->updateDirection(Direction::DOWN);
        break;
    case GameContols::K_LEFT:
        if (cur_dir != Direction::RIGHT)
        player->updateDirection(Direction::LEFT);
        break;
    case GameContols::K_RIGHT:
        if (cur_dir != Direction::LEFT)
        player->updateDirection(Direction::RIGHT);
        break;
    default:
        break;
    }
    //Will process input later on.
}

void Game::checkSelf() {
    PlayerPiece head = player->head();
    for (auto pc : this->player->body) {
        if(pc.getIcon() == '@') continue;
        if (pc.getX() == head.getX() && pc.getY() == head.getY()) {
            game_over = 1;
        }
    }
}

void Game::updateState(){
    int y;
    int x;

    PlayerPiece player_head = player->head();
    //Place the apple in an area not outside 
    //arena and not on snake body.

    //Clear previous apple location if snake-head is at apple location.
    if(apple != nullptr && (player_head.getX() == apple->getX() && player_head.getY() == apple->getY())){
        score++;
        board->add(Empty(apple->getY(), apple->getX()));
        delete apple;
        PlayerPiece pc(player->tail().getY(), player->tail().getX());
        player->addPiece(pc);
        board->getEmptyCoordinates(y, x);
        board->writeToStats(score);
        apple = new Apple(y, x);
        board->add(*apple);
    }

    //Snake placement
    //Clear previous state on board
    for(PlayerPiece pp : player->body){
        board->add(Empty(pp.getY(), pp.getX()));
    }

    //Populate new position.
    player->update(50, 20);
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