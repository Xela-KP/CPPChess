#include "../include/game.hpp"
#include "../include/mask.hpp"

Game::Game()
{
    // TODO: Should Game Map Attack Masks?
    // MaskUtils::map_attack_masks();
    push_state(gamestate);
}
GameState Game::get_state() { return gamestate; }
GameState Game::pop_state()
{
    GameState popped_state = history.top();
    history.pop();
    return popped_state;
}
void Game::push_state(GameState gamestate) { history.push(gamestate); }
void Game::update_state(GameState gamestate)
{
    push_state(gamestate);
    this->gamestate = gamestate;
}
// TODO: Implement
void Game::undo() {}