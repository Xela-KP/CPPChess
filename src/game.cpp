#include "../include/game.hpp"
#include "../include/mask.hpp"

Game::Game()
{
    MaskUtils::map_attack_masks();
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
void Game::undo() {}
