#include <iostream>
#include "../include/util.hpp"
#include "../include/game.hpp"
#include "../include/encodings.hpp"
#include "../include/fen.hpp"
int main()
{
    Game game;
    util::print_bitboard(game.get_state().get_color_occupancy(chess::BOTH));
    return 0;
}