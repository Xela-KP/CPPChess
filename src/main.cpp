#include <iostream>
#include "../include/util.hpp"
#include "../include/game.hpp"
#include "../include/encodings.hpp"
#include "../include/fen.hpp"
int main()
{
    GameState gs;
    util::print_chessboard(gs);
    return 0;
}