#include <iostream>
#include "../include/bitboard.hpp"
#include "../include/encodings.hpp"
#include "../include/mask.cpp"
#include "../include/util.cpp"
int main()
{
    Mask::map_slide_attacks(ChessEncoding::ROOK);
    Mask::map_slide_attacks(ChessEncoding::BISHOP);
    Mask::map_leap_attacks();
    Mask::initialize_occupancies();
    Util::print_chessboard();
    return 0;
}