#pragma once
#include <stack>
#include "game.hpp"

class Game
{
    GameState gamestate;
    std::stack<GameState> history;

public:
    Game()
    {
        GameState gamestate = GameState();
        history.push(gamestate);
    };
    GameState get_state() { return history.top(); }
    GameState pop_state()
    {
        GameState popped_state = history.top();
        history.pop();
        return popped_state;
    }
    void push_state(GameState gamestate) { history.push(gamestate); }
    void undo() { gamestate = pop_state(); };
};