#include <iostream>
#include "../include/bitboard.h"
int main()
{
    map_slide_attacks(ROOK);
    map_slide_attacks(BISHOP);
    map_leap_attacks();
    initialize_occupancies();
    print_chessboard();
    return 0;
}