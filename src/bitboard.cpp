#include "../include/bitboard.hpp"

int BitboardUtils::getLSB(Bitboard bitboard) { return __builtin_ctzll(bitboard); }
int BitboardUtils::getBitCount(Bitboard bitboard) { return __builtin_popcountll(bitboard); }
int BitboardUtils::getSquare(int rank, int file) { return rank * 8 + file; }
bool BitboardUtils::getBit(Bitboard bitboard, int square) { return (bitboard & 1ULL << (square)) != 0; }
void BitboardUtils::setBit(Bitboard &bitboard, int square) { bitboard |= (1ULL << square); }
void BitboardUtils::clearBit(Bitboard &bitboard, int square) { bitboard &= ~(1ULL << square); }
int BitboardUtils::popLSB(Bitboard &bitboard)
{
    int i = getLSB(bitboard);
    bitboard &= bitboard - 1;
    return i == 64 ? -1 : i;
}
