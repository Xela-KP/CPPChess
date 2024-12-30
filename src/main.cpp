#include <iostream>
#include "../include/bitboard.h"
int main()
{
    U64 bitboard = 0ULL;
    print_bitboard(get_rook_attack_mask(0) & ROOK_MAGIC_NUMBERS[0]);
    return 0;
}