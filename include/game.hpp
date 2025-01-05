#pragma once
#include <stack>
#include "gamestate.hpp"
class Game
{
    GameState gamestate;
    std::stack<GameState> history;

public:
    Game();
    GameState pop_state();
    GameState *get_state();
    void push_state(GameState gamestate);
    void undo();
    void set_state(GameState gamestate);
};