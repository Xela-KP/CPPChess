#pragma once
#include <cstdint>
typedef unsigned long long Bitboard;
constexpr int BOARD_SIZE = 64;
constexpr int DIMENSION = 8;
constexpr Bitboard EMPTY_BOARD = 0ULL;
constexpr Bitboard FULL_BOARD = ~EMPTY_BOARD;
namespace BitboardUtils
{
    int getLSB(Bitboard bitboard);
    int getBitCount(Bitboard bitboard);
    int getSquare(int rank, int file);
    int popLSB(Bitboard &bitboard);
    bool getBit(Bitboard bitboard, int square);
    void setBit(Bitboard &bitboard, int square);
    void clearBit(Bitboard &bitboard, int square);
}