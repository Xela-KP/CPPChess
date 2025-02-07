#include "../include/bitboard.hpp"
#include <iostream>

// int BitboardUtils::getLSB(Bitboard bitboard) { return __builtin_ctzll(bitboard); }
// int BitboardUtils::getBitCount(Bitboard bitboard) { return __builtin_popcountll(bitboard); }
// int BitboardUtils::getSquare(int rank, int file) { return rank * 8 + file; }
// bool BitboardUtils::getBit(Bitboard bitboard, int square) { return (bitboard & 1ULL << (square)) != 0; }
// void BitboardUtils::setBit(Bitboard &bitboard, int square) { bitboard |= (1ULL << square); }
// void BitboardUtils::clearBit(Bitboard &bitboard, int square) { bitboard &= ~(1ULL << square); }
// int BitboardUtils::popLSB(Bitboard &bitboard)
// {
//     int i = getLSB(bitboard);
//     bitboard &= bitboard - 1;
//     return i == 64 ? -1 : i;
// }



Bitboard::Bitboard() : value(0) {}
Bitboard::Bitboard(uint64_t value) : value(value) {}
Bitboard::operator uint64_t() const { return value; }

bool Bitboard::operator[](int square) const { return (value & (1ULL << square)) != 0; }
Bitboard::BitProxy::BitProxy(Bitboard &bitbaord, int square) : bitboard(bitboard), square(square) {}
Bitboard::BitProxy &Bitboard::BitProxy::operator=(bool value)
{
    value ? bitboard.value |= (1ULL << square) : bitboard.value &= ~(1ULL << square);
    return *this;
}

 // (bitboard.value & (1ULL << square)) != 0;
Bitboard::BitProxy::operator bool() const { return (bitboard.value & (1ULL << square)); }
Bitboard::BitProxy Bitboard::operator[](int square) { return BitProxy(*this, square); }

// Bitwise operators
Bitboard Bitboard::operator&(const Bitboard &other) const { return Bitboard(value & other.value); }
Bitboard Bitboard::operator|(const Bitboard &other) const { return Bitboard(value | other.value); }
Bitboard Bitboard::operator^(const Bitboard &other) const { return Bitboard(value ^ other.value); }
Bitboard Bitboard::operator~() const { return Bitboard(~value); }
Bitboard Bitboard::operator<<(int shift) const { return Bitboard(value << shift); }
Bitboard Bitboard::operator>>(int shift) const { return Bitboard(value >> shift); }

// Compound assignment operators
Bitboard &Bitboard::operator&=(const Bitboard &other)
{
    value &= other.value;
    return *this;
}

Bitboard &Bitboard::operator|=(const Bitboard &other)
{
    value |= other.value;
    return *this;
}

Bitboard &Bitboard::operator^=(const Bitboard &other)
{
    value ^= other.value;
    return *this;
}

Bitboard &Bitboard::operator<<=(int shift)
{
    value <<= shift;
    return *this;
}

Bitboard &Bitboard::operator>>=(int shift)
{
    value >>= shift;
    return *this;
}

int Bitboard::GetLsbIndex() const { return __builtin_ctzll(value); }

int Bitboard::PopLsbIndex()
{
    if (value <= 0)
        return -1;
    int index = GetLsbIndex();
    value &= value - 1;
    return (index >= 64) ? -1 : index; 
}


void Bitboard::print() const
{
    std::bitset<64> bits(value);
    for (int rank = 7; rank >= 0; --rank)
    {
        for (int file = 0; file < 8; ++file)
        {
            int square = rank * 8 + file;
            std::cout << (*this)[square] << " ";
        }
        std::cout << std::endl;
    }
}