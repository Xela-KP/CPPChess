#include <iostream>
#include "../include/bitboard.h"
int main()
{
    U64 bitboard = 1ULL;
    map_leap_attacks();
    print_bitboard(knight_attacks[a8]);
    return 0;
}