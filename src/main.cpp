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
    util::print_chessboard();
    util::print_attacked_squares(1);
    return 0;
}