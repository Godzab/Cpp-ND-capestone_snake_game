#include <chrono>
#include <mutex>

#include "Game.h"
#include "Apple.h"
#include "Player.h"

Game::Game(std::unique_ptr<Board> bd, std::shared_ptr<Player> plr) : board(std::move(bd)), player(std::move(plr)) {
    apple = new Apple();
    this->initialize();
}

Game::~Game() {
    delete apple;
}

Game::Game(Game &game_cp) {
    apple = new Apple();
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    board = std::make_unique<Board>(game_cp.board->height, game_cp.board->width);
    score = game_cp.score;
}

//copy assignment constructor
Game &Game::operator=(Game const &game_cp) {
    if (this == &game_cp)
        return *this;

    apple = new Apple();
    *apple = *game_cp.apple;
    board = std::make_unique<Board>(game_cp.board->height, game_cp.board->width);
    player = game_cp.player;
    score = game_cp.score;
    return *this;
}

//move constructor
Game::Game(Game &&game_cp) noexcept {
    apple = new Apple();
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    score = game_cp.score;


    game_cp.player.reset();
    game_cp.score = 0;
    delete game_cp.apple;
}

//move assignment constructor
Game &Game::operator=(Game &&game_cp) noexcept {
    if (this == &game_cp)
        return *this;
    apple = new Apple(0, 0);
    *apple = *game_cp.apple;
    board = std::move(game_cp.board);
    player = game_cp.player;
    score = game_cp.score;

    game_cp.player.reset();
    game_cp.score = 0;
    delete game_cp.apple;

    return *this;
}

/**
 * Handles Snake controls as input from keyboard.
 * Captures the ASCII character codes for W, D, S, A to act as direction keys.
 * Prevent direction reversal. (You cannot navigate left while travelling right e.t.c)
 */
void Game::processInput() {
    char input = board->getInput();
    std::lock_guard<std::mutex> lock(mtx);
    Direction cur_dir = player->getDirection();
    switch (input) {
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
}

//Check if snake head has intersected with any body piece.
void Game::checkRules() {
    PlayerPiece head = player->head();
    for (auto pc : this->player->body) {
        //skip if current piece is the head piece.
        if (pc.getIcon() == '@') {
            continue;
        }
        if (pc.getX() == head.getX() && pc.getY() == head.getY()) {
            game_over = true;
            sprintf (board->stats_buffer, "GAME OVER - Final Score: %d", score);
            board->writeToStats(board->stats_buffer);
        }
    }
}

void Game::updateState() {
    int y;
    int x;

    PlayerPiece player_head = player->head();

    //Check if snake has eaten apple and place another on the board.
    //Update player score.
    if (apple != nullptr && (player_head.getX() == apple->getX() && player_head.getY() == apple->getY())) {
        score++;
        PlayerPiece pc(player->tail().getY(), player->tail().getX());
        player->addPiece(pc);
        board->getEmptyCoordinates(y, x);
        sprintf (board->stats_buffer, "Score: %d", score);
        board->writeToStats(board->stats_buffer);

        delete apple;
        apple = new Apple(y, x);
        board->add(*apple);
    }

    //Snake placement
    //Clear previous snake state from board
    for (Drawable pp : player->body) {
        board->add(Empty(pp.getY(), pp.getX()));
    }

    //Populate new position.
    player->update(board->width, board->height);
    for (Drawable pp : player->body) {
        board->add(pp);
    }
    board->Refresh();
}

void Game::redraw() {
    board->Refresh();
}

bool Game::isOver() const {
    return this->game_over;
}

void Game::initialize() {
    int x;
    int y;
    board->getEmptyCoordinates(y, x);
    apple = new Apple(y, x);
    board->add(*apple);
    sprintf (board->stats_buffer, "Score: %d", score);
    board->writeToStats(board->stats_buffer);
}
