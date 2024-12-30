#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    // mask::map_slide_attacks(chess::ROOK);
    // mask::map_slide_attacks(chess::BISHOP);
    // mask::map_leap_attacks();
    // mask::initialize_occupancies();
    // util::print_chessboard();
    fen::parse_fen(CMK_POSITION);
    util::print_chessboard();
    return 0;
}