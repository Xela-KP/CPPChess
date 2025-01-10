#include "../include/bitboard.hpp"
namespace BitboardUtils
{
    int getLSB(Bitboard bitboard) { return __builtin_ctzll(bitboard); }
    int getBitCount(Bitboard bitboard) { return __builtin_popcountll(bitboard); }
    int getSquare(int rank, int file) { return rank * 8 + file; }
    bool getBit(Bitboard bitboard, int square) { return (bitboard & 1ULL << (square)) != 0; }
    void setBit(Bitboard &bitboard, int square) { bitboard |= (1ULL << square); }
    void clearBit(Bitboard &bitboard, int square) { bitboard &= ~(1ULL << square); }
    int popLSB(Bitboard &bitboard)
    {
        int i = getLSB(bitboard);
        bitboard &= bitboard - 1;
        return i == 64 ? -1 : i;
    }
}
