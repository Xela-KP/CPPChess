#include <iostream>
#include "../include/bitboard.h"
int main()
{
    map_slide_attacks(ROOK);
    map_slide_attacks(BISHOP);
    map_leap_attacks();
    initialize_occupancies();
    for (int i = P; i <= k; i++)
    {
        print_bitboard(piece_occupancies[i]);
    }
    print_bitboard(side_occupancies[WHITE]);
    print_bitboard(side_occupancies[BLACK]);
    print_bitboard(side_occupancies[BOTH]);
    // print_bitboard(piece_occupancies[P]);
    // print_bitboard(piece_occupancies[p]);
    return 0;
}