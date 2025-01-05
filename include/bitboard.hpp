#pragma once
#include "types.hpp"
#define DIMENSION 8
#define BOARD_SIZE 64
#define get_least_significant_bit(bitboard) (__builtin_ctzll((bitboard)))
#define get_bit_count(bitboard) (__builtin_popcountll((bitboard)))
namespace bitboard
{
    inline bool get_bit(U64 bitboard, int square) { return (bitboard & 1ULL << (square)) != 0; }
    inline void set_bit(U64 &bitboard, int square) { bitboard |= (1ULL << square); }
    inline void clear_bit(U64 &bitboard, int square) { bitboard &= ~(1ULL << square); }
    inline int pop_least_significant_bit(U64 &bitboard)
    {
        int i = get_least_significant_bit(bitboard);
        bitboard &= bitboard - 1;
        return i == 64 ? -1 : i;
    }
}