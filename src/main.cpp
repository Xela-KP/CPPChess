#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
#include "../include/movement.cpp"
int main()
{
    mask::map_slide_attacks();
    mask::map_leap_attacks();
    fen::parse_fen(TRICKY_POSITION);
    movement::get_moves(0);
    util::print_chessboard();
    util::print_moves(0);
    return 0;
}