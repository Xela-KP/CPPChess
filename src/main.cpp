#include <iostream>
#include "../include/bitboard.h"
int main()
{
    U64 bitboard = 0ULL;
    map_leap_attacks();
    print_bitboard(pawn_attacks[white][a2]);
    return 0;
}