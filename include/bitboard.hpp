#pragma once
#include <bitset>
#include <cstdint>
// typedef unsigned long long Bitboard;
// constexpr int BOARD_SIZE = 64;
// constexpr int DIMENSION = 8;
// constexpr Bitboard EMPTY_BOARD = 0ULL;
// constexpr Bitboard FULL_BOARD = ~EMPTY_BOARD;
// namespace BitboardUtils
// {
//     int getLSB(Bitboard bitboard);
//     int getBitCount(Bitboard bitboard);
//     int getSquare(int rank, int file);
//     int popLSB(Bitboard &bitboard);
//     bool getBit(Bitboard bitboard, int square);
//     void setBit(Bitboard &bitboard, int square);
//     void clearBit(Bitboard &bitboard, int square);
// }

class Bitboard
{
public:
    Bitboard();
    Bitboard(uint64_t value);
    inline operator uint64_t() const;

    class BitProxy;

    inline bool operator[](int square) const;
    inline BitProxy operator[](int square);

    inline Bitboard operator&(const Bitboard &other) const;
    inline Bitboard operator|(const Bitboard &other) const;
    inline Bitboard operator^(const Bitboard &other) const;
    inline Bitboard operator~() const;
    inline Bitboard operator<<(int shift) const;
    inline Bitboard operator>>(int shift) const;

    inline Bitboard &operator&=(const Bitboard &other);
    inline Bitboard &operator|=(const Bitboard &other);
    inline Bitboard &operator^=(const Bitboard &other);
    inline Bitboard &operator<<=(int shift);
    inline Bitboard &operator>>=(int shift);

    inline Bitboard &Set(int square);
    inline Bitboard &Clear(int square);

    inline int GetLsbIndex() const;
    inline int PopLsbIndex();

    void print() const;

    class BitProxy
    {
    public:
        BitProxy(Bitboard &bb, int sq);
        BitProxy &operator=(bool value);
        operator bool() const;
    private:
        Bitboard &bitboard;
        int square;
    };

private:
    uint64_t value;
};