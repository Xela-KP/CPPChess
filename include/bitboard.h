#include "types.h"
#define DIMENSTION 8
#define BOARD_SIZE 64
#define get_bit(bitboard, square) (bitboard & (1ULL << square) ? 1 : 0)
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define clear_bit(bitborad, square) (bitboard &= ~(1ULL << square))

U64 pawn_attacks[2][BOARD_SIZE];
const U64 NOT_A_FILE = 18374403900871474942ULL;
const U64 NOT_H_FILE = 9187201950435737471ULL;
const U64 NOT_HG_FILE = 4557430888798830399ULL;
const U64 NOT_AB_FILE = 18229723555195321596ULL;

void print_bitboard(U64 bitboard)
{
    for (int rank = 0; rank < DIMENSTION; rank++)
    {
        std::cout << DIMENSTION - rank << "   ";
        for (int file = 0; file < DIMENSTION; file++)
        {
            int square = rank * DIMENSTION + file;
            std::cout << get_bit(bitboard, square) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n decimal value = " << std::dec << bitboard << '\n';
}

U64 mask_pawn_attacks(int side, int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, from_square);
    if (!side)
    {
        if (bitboard & NOT_A_FILE)
            attack_bitboard |= bitboard >> 9;
        if (bitboard & NOT_H_FILE)
            attack_bitboard |= bitboard >> 7;
    }
    else
    {
        if (bitboard & NOT_A_FILE)
            attack_bitboard |= bitboard << 7;
        if (bitboard & NOT_H_FILE)
            attack_bitboard |= bitboard << 9;
    }
    return attack_bitboard;
}

void map_leap_attacks()
{
    for (int from_square = a8; from_square != h1; from_square++)
    {
        pawn_attacks[white][from_square] = mask_pawn_attacks(white, from_square);
        pawn_attacks[black][from_square] = mask_pawn_attacks(black, from_square);
    }
}