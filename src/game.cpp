#include "../include/game.hpp"
#include "../include/mask.hpp"

Game::Game() : gamestate(GameState())
{
    MaskUtils::map_attack_masks();
    history.push(gamestate);
}
GameState Game::get_state() { return history.top(); }
GameState Game::pop_state()
{
    GameState popped_state = history.top();
    history.pop();
    return popped_state;
}
void Game::push_state(GameState gamestate) { history.push(gamestate); }
void Game::undo() { gamestate = pop_state(); }
