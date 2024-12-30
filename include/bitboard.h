#include "types.h"
#define DIMENSTION 8
#define BOARD_SIZE 64
#define get_bit(bitboard, square) (bitboard & (1ULL << square) ? 1 : 0)
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define clear_bit(bitborad, square) (bitboard &= ~(1ULL << square))

const U64 NOT_A_FILE = 18374403900871474942ULL;
const U64 NOT_H_FILE = 9187201950435737471ULL;
const U64 NOT_HG_FILE = 4557430888798830399ULL;
const U64 NOT_AB_FILE = 18229723555195321596ULL;
U64 pawn_attacks[2][BOARD_SIZE];
U64 knight_attacks[BOARD_SIZE];
U64 king_attacks[BOARD_SIZE];

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
        if (bitboard >> 7 & NOT_A_FILE)
            attack_bitboard |= bitboard >> 7;
        if (bitboard >> 9 & NOT_H_FILE)
            attack_bitboard |= bitboard >> 9;
    }
    else
    {
        if (bitboard << 9 & NOT_A_FILE)
            attack_bitboard |= bitboard << 9;
        if (bitboard >> 7 & NOT_H_FILE)
            attack_bitboard |= bitboard << 7;
    }
    return attack_bitboard;
}

U64 mask_knight_attacks(int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, from_square);
    if (bitboard >> 6 & NOT_AB_FILE)
        attack_bitboard |= bitboard >> 6;
    if (bitboard << 6 & NOT_HG_FILE)
        attack_bitboard |= bitboard << 6;
    if (bitboard << 10 & NOT_AB_FILE)
        attack_bitboard |= bitboard << 10;
    if (bitboard >> 10 & NOT_HG_FILE)
        attack_bitboard |= bitboard >> 10;
    if (bitboard >> 15 & NOT_A_FILE)
        attack_bitboard |= bitboard >> 15;
    if (bitboard << 15 & NOT_H_FILE)
        attack_bitboard |= bitboard << 15;
    if (bitboard << 17 & NOT_A_FILE)
        attack_bitboard |= bitboard << 17;
    if (bitboard >> 17 & NOT_H_FILE)
        attack_bitboard |= bitboard >> 17;
    return attack_bitboard;
}

U64 mask_king_attacks(int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_bitboard = 0ULL;
    set_bit(bitboard, from_square);

    if (bitboard >> 8)
        attack_bitboard |= bitboard >> 8;
    if (bitboard << 8)
        attack_bitboard |= bitboard << 8;

    if (bitboard << 1 & NOT_A_FILE)
        attack_bitboard |= bitboard << 1;
    if (bitboard >> 1 & NOT_H_FILE)
        attack_bitboard |= bitboard >> 1;
    if (bitboard >> 7 & NOT_A_FILE)
        attack_bitboard |= bitboard >> 7;
    if (bitboard << 7 & NOT_H_FILE)
        attack_bitboard |= bitboard << 7;
    if (bitboard << 9 & NOT_A_FILE)
        attack_bitboard |= bitboard << 9;
    if (bitboard >> 9 & NOT_H_FILE)
        attack_bitboard |= bitboard >> 9;
    return attack_bitboard;
}

U64 mask_bishop_attacks(int from_square)
{
    U64 attack_bitboard = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSTION;
    int target_file = from_square % DIMENSTION;

    for (rank = target_rank + 1, file = target_file + 1;
         rank < DIMENSTION - 1 && file < DIMENSTION - 1;
         rank++, file++)
        attack_bitboard |= (1ULL << (rank * 8 + file));

    for (rank = target_rank - 1, file = target_file + 1;
         rank > 0 && file < DIMENSTION - 1;
         rank--, file++)
        attack_bitboard |= (1ULL << (rank * 8 + file));

    for (rank = target_rank + 1, file = target_file - 1;
         rank < DIMENSTION - 1 && file > 0;
         rank++, file--)
        attack_bitboard |= (1ULL << (rank * 8 + file));

    for (rank = target_rank - 1, file = target_file - 1;
         rank > 0 && file > 0;
         rank--, file--)
        attack_bitboard |= (1ULL << (rank * 8 + file));

    return attack_bitboard;
}

U64 mask_rook_attacks(int from_square)
{
    U64 attack_bitboard = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSTION;
    int target_file = from_square % DIMENSTION;

    for (rank = target_rank + 1; rank < DIMENSTION - 1; rank++)
        attack_bitboard |= (1ULL << (rank * 8 + target_file));

    for (rank = target_rank - 1; rank > 0; rank--)
        attack_bitboard |= (1ULL << (rank * 8 + target_file));

    for (file = target_file + 1; file < DIMENSTION - 1; file++)
        attack_bitboard |= (1ULL << (target_rank * 8 + file));

    for (file = target_file - 1; file > 0; file--)
        attack_bitboard |= (1ULL << (target_rank * 8 + file));

    return attack_bitboard;
}

U64 mask_queen_attacks()
{
    return 0ULL;
}

U64 mask_pawn_promotions()
{
    return 0ULL;
}

U64 mask_pawn_enpassant()
{
    return 0ULL;
}

void map_leap_attacks()
{
    for (int from_square = a8; from_square <= h1; from_square++)
    {
        pawn_attacks[white][from_square] = mask_pawn_attacks(white, from_square);
        pawn_attacks[black][from_square] = mask_pawn_attacks(black, from_square);
        knight_attacks[from_square] = mask_knight_attacks(from_square);
        king_attacks[from_square] = mask_king_attacks(from_square);
    }
}