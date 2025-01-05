#include <iostream>
#include "../include/util.hpp"
#include "../include/game.hpp"
#include "../include/encodings.hpp"
#include "../include/fen.hpp"
int main()
{
    Game game;
    game.get_state()->parse_fen(TRICKY_POSITION);
    game.set_state(*game.get_state());
    // game.get_state()->parse_fen(CMK_POSITION);
    // game.set_state(*game.get_state());
    util::print_chessboard(*game.get_state());
    util::print_moves(*game.get_state(), 1);
    // util::print_bitboard(game.pop_state().get_color_occupancy(chess::BOTH));
    // util::print_bitboard(game.pop_state().get_color_occupancy(chess::BOTH));
    // util::print_bitboard(game.pop_state().get_color_occupancy(chess::BOTH));
    return 0;
}