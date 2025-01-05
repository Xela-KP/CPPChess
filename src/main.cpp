#include <iostream>
#include "../include/util.hpp"
#include "../include/game.hpp"
#include "../include/encodings.hpp"
int main()
{
    Game game = Game();
    util::print_bitboard(game.get_state().get_color_occupancy(chess::BOTH));
    return 0;
}