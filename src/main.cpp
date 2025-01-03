#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
#include "../include/movement.cpp"
int main()
{
    mask::map_slide_attacks();
    mask::map_leap_attacks();
    fen::parse_fen(KILLER_POSITION);
    util::print_chessboard();
    movement::get_moves(0);
    // movement::get_moves(1);
    // std::cout << state::moves.size();
    util::print_pawn_moves(0);
    return 0;
}