#include <iostream>
#include "../include/bitboard.h"
int main()
{
    map_slide_attacks(rook);
    map_slide_attacks(bishop);
    U64 bitboard = 0ULL;
    set_bit(bitboard, d2);
    set_bit(bitboard, d7);
    set_bit(bitboard, b4);
    set_bit(bitboard, f4);
    print_bitboard(bitboard);
    print_bitboard(get_rook_attack_mask(d4, bitboard));
    // for (int i = 0; i < 64; i++)
    // {
    //     print_bitboard(rook_attack_mask[0][i]);
    // }

    return 0;
}