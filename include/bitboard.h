#include "types.h"
#define DIMENSION 8
#define BOARD_SIZE 64
#define get_bit(bitboard, square) (bitboard & (1ULL << square) ? 1 : 0)
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define clear_bit(bitborad, square) (bitboard &= ~(1ULL << square))
#define get_LSB(b) (__builtin_ctzll(bitboard))
#define get_bit_count(bitboard) (__builtin_popcountll(bitboard))

const U64 NOT_A_FILE = 18374403900871474942ULL;
const U64 NOT_H_FILE = 9187201950435737471ULL;
const U64 NOT_HG_FILE = 4557430888798830399ULL;
const U64 NOT_AB_FILE = 18229723555195321596ULL;
U64 pawn_attack_mask[2][BOARD_SIZE];
U64 knight_attack_mask[BOARD_SIZE];
U64 king_attack_mask[BOARD_SIZE];
U64 bishop_unblocked_attack_mask[BOARD_SIZE];
U64 rook_unblocked_attack_mask[BOARD_SIZE];
U64 bishop_attack_mask[BOARD_SIZE][4096];
U64 rook_attack_mask[BOARD_SIZE][4096];

unsigned int random_number_state = 1804289383;

unsigned int get_pseudo_RNG()
{
    unsigned int number = random_number_state;
    number ^= number << 13;
    number ^= number >> 17;
    number ^= number << 5;
    random_number_state = number;
    return number;
}

static inline int pop_LSB(U64 &bitboard)
{
    int i = get_LSB(bitboard);
    bitboard &= bitboard - 1;
    return i == 64 ? -1 : i;
}

void print_bitboard(U64 bitboard)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << get_bit(bitboard, square) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n decimal value = " << std::dec << bitboard << '\n';
}

U64 get_masked_occupancy(int occupied, U64 attack_mask)
{
    U64 occupancy = 0ULL;
    int num_attacks = get_bit_count(attack_mask);
    for (int count = 0; count < num_attacks; count++)
    {
        int square = pop_LSB(attack_mask);
        if (occupied & (1 << count))
        {
            occupancy |= (1ULL << square);
        }
    }
    return occupancy;
}

U64 get_pawn_attack_mask(int side, int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_mask = 0ULL;
    set_bit(bitboard, from_square);
    if (!side)
    {
        if (bitboard >> 7 & NOT_A_FILE)
            attack_mask |= bitboard >> 7;
        if (bitboard >> 9 & NOT_H_FILE)
            attack_mask |= bitboard >> 9;
    }
    else
    {
        if (bitboard << 9 & NOT_A_FILE)
            attack_mask |= bitboard << 9;
        if (bitboard >> 7 & NOT_H_FILE)
            attack_mask |= bitboard << 7;
    }
    return attack_mask;
}

U64 get_knight_attack_mask(int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_mask = 0ULL;
    set_bit(bitboard, from_square);
    if (bitboard >> 6 & NOT_AB_FILE)
        attack_mask |= bitboard >> 6;
    if (bitboard << 6 & NOT_HG_FILE)
        attack_mask |= bitboard << 6;
    if (bitboard << 10 & NOT_AB_FILE)
        attack_mask |= bitboard << 10;
    if (bitboard >> 10 & NOT_HG_FILE)
        attack_mask |= bitboard >> 10;
    if (bitboard >> 15 & NOT_A_FILE)
        attack_mask |= bitboard >> 15;
    if (bitboard << 15 & NOT_H_FILE)
        attack_mask |= bitboard << 15;
    if (bitboard << 17 & NOT_A_FILE)
        attack_mask |= bitboard << 17;
    if (bitboard >> 17 & NOT_H_FILE)
        attack_mask |= bitboard >> 17;
    return attack_mask;
}

U64 get_king_attack_mask(int from_square)
{
    U64 bitboard = 0ULL;
    U64 attack_mask = 0ULL;
    set_bit(bitboard, from_square);
    if (bitboard >> 8)
        attack_mask |= bitboard >> 8;
    if (bitboard << 8)
        attack_mask |= bitboard << 8;
    if (bitboard << 1 & NOT_A_FILE)
        attack_mask |= bitboard << 1;
    if (bitboard >> 1 & NOT_H_FILE)
        attack_mask |= bitboard >> 1;
    if (bitboard >> 7 & NOT_A_FILE)
        attack_mask |= bitboard >> 7;
    if (bitboard << 7 & NOT_H_FILE)
        attack_mask |= bitboard << 7;
    if (bitboard << 9 & NOT_A_FILE)
        attack_mask |= bitboard << 9;
    if (bitboard >> 9 & NOT_H_FILE)
        attack_mask |= bitboard >> 9;
    return attack_mask;
}

U64 get_bishop_unblocked_attack_mask(int from_square)
{
    U64 attack_mask = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSION;
    int target_file = from_square % DIMENSION;
    for (rank = target_rank + 1, file = target_file + 1;
         rank < DIMENSION - 1 && file < DIMENSION - 1;
         rank++, file++)
        attack_mask |= (1ULL << (rank * 8 + file));
    for (rank = target_rank - 1, file = target_file + 1;
         rank > 0 && file < DIMENSION - 1;
         rank--, file++)
        attack_mask |= (1ULL << (rank * 8 + file));
    for (rank = target_rank + 1, file = target_file - 1;
         rank < DIMENSION - 1 && file > 0;
         rank++, file--)
        attack_mask |= (1ULL << (rank * 8 + file));
    for (rank = target_rank - 1, file = target_file - 1;
         rank > 0 && file > 0;
         rank--, file--)
        attack_mask |= (1ULL << (rank * 8 + file));
    return attack_mask;
}

U64 get_bishop_blocked_attack_mask(int from_square, U64 occupancy)
{
    U64 attack_mask = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSION;
    int target_file = from_square % DIMENSION;

    for (rank = target_rank + 1, file = target_file + 1;
         rank < DIMENSION && file < DIMENSION;
         rank++, file++)
    {
        attack_mask |= (1ULL << (rank * 8 + file));
        if ((1ULL << (rank * 8 + file)) & occupancy)
            break;
    }
    for (rank = target_rank + 1, file = target_file - 1;
         rank < DIMENSION && file >= 0;
         rank++, file--)
    {
        attack_mask |= (1ULL << (rank * 8 + file));
        if ((1ULL << (rank * 8 + file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1, file = target_file + 1;
         rank >= 0 && file < DIMENSION;
         rank--, file++)
    {
        attack_mask |= (1ULL << (rank * 8 + file));
        if ((1ULL << (rank * 8 + file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1, file = target_file - 1;
         rank >= 0 && file >= 0;
         rank--, file--)
    {
        attack_mask |= (1ULL << (rank * 8 + file));
        if ((1ULL << (rank * 8 + file)) & occupancy)
            break;
    }

    return attack_mask;
}

U64 get_rook_unblocked_attack_mask(int from_square)
{
    U64 attack_mask = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSION;
    int target_file = from_square % DIMENSION;
    for (rank = target_rank + 1; rank < DIMENSION - 1; rank++)
        attack_mask |= (1ULL << (rank * 8 + target_file));
    for (rank = target_rank - 1; rank > 0; rank--)
        attack_mask |= (1ULL << (rank * 8 + target_file));
    for (file = target_file + 1; file < DIMENSION - 1; file++)
        attack_mask |= (1ULL << (target_rank * 8 + file));
    for (file = target_file - 1; file > 0; file--)
        attack_mask |= (1ULL << (target_rank * 8 + file));
    return attack_mask;
}

U64 get_rook_blocked_attack_mask(int from_square, U64 occupancy)
{
    U64 attack_mask = 0ULL;
    int rank, file;
    int target_rank = from_square / DIMENSION;
    int target_file = from_square % DIMENSION;
    for (rank = target_rank + 1; rank < DIMENSION; rank++)
    {
        attack_mask |= (1ULL << (rank * 8 + target_file));
        if ((1ULL << (rank * 8 + target_file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1; rank >= 0; rank--)
    {
        attack_mask |= (1ULL << (rank * 8 + target_file));
        if ((1ULL << (rank * 8 + target_file)) & occupancy)
            break;
    }
    for (file = target_file + 1; file < DIMENSION; file++)
    {
        attack_mask |= (1ULL << (target_rank * 8 + file));
        if ((1ULL << (target_rank * 8 + file)) & occupancy)
            break;
    }
    for (file = target_file - 1; file >= 0; file--)
    {
        attack_mask |= (1ULL << (target_rank * 8 + file));
        if ((1ULL << (target_rank * 8 + file)) & occupancy)
            break;
    }
    return attack_mask;
}

static inline U64 get_bishop_attack_mask(U64 square, U64 occupancy)
{
    occupancy &= bishop_unblocked_attack_mask[square];
    occupancy *= BISHOP_MAGIC_NUMBERS[square];
    occupancy >>= 64 - BISHOP_ATTACK_COUNT_MASK[square];
    return bishop_attack_mask[square][occupancy];
}

static inline U64 get_rook_attack_mask(U64 square, U64 occupancy)
{
    occupancy &= rook_unblocked_attack_mask[square];
    occupancy *= ROOK_MAGIC_NUMBERS[square];
    occupancy >>= 64 - ROOK_ATTACK_COUNT_MASK[square];
    return rook_attack_mask[square][occupancy];
}

void map_leap_attacks()
{
    for (int from_square = a8; from_square <= h1; from_square++)
    {
        pawn_attack_mask[white][from_square] = get_pawn_attack_mask(white, from_square);
        pawn_attack_mask[black][from_square] = get_pawn_attack_mask(black, from_square);
        knight_attack_mask[from_square] = get_knight_attack_mask(from_square);
        king_attack_mask[from_square] = get_king_attack_mask(from_square);
    }
}

void map_slide_attacks(int bishop)
{
    for (int from_square = a8; from_square <= h1; from_square++)
    {
        bishop_unblocked_attack_mask[from_square] = get_bishop_unblocked_attack_mask(from_square);
        rook_unblocked_attack_mask[from_square] = get_rook_unblocked_attack_mask(from_square);
        U64 attack_mask = bishop ? bishop_unblocked_attack_mask[from_square] : rook_unblocked_attack_mask[from_square];
        int num_attacks = get_bit_count(attack_mask);
        int occupancy_indicies = (1 << num_attacks);
        for (int index = 0; index < occupancy_indicies; index++)
        {
            U64 masked_occupancy = get_masked_occupancy(index, attack_mask);
            if (bishop)
            {
                int magic_index = (masked_occupancy * BISHOP_MAGIC_NUMBERS[from_square]) >> (64 - BISHOP_ATTACK_COUNT_MASK[from_square]);
                bishop_attack_mask[from_square][magic_index] = get_bishop_blocked_attack_mask(from_square, masked_occupancy);
            }
            else
            {
                int magic_index = (masked_occupancy * ROOK_MAGIC_NUMBERS[from_square]) >> (64 - ROOK_ATTACK_COUNT_MASK[from_square]);
                rook_attack_mask[from_square][magic_index] = get_rook_blocked_attack_mask(from_square, masked_occupancy);
            }
        }
    }
}