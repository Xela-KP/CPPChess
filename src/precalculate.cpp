#include "../include/precalculate.hpp"
Bitboard PreCalculate::evaluateMaskedOccupancy(int occupancy_index, Bitboard attack_mask)
{
    Bitboard occupancy = EMPTY_BOARD;
    int num_attacks = BitboardUtils::getBitCount(attack_mask);
    for (int count = 0; count < num_attacks; count++)
    {
        int square = BitboardUtils::popLSB(attack_mask);
        if (occupancy_index & (1 << count))
        {
            occupancy |= (1ULL << square);
        }
    }
    return occupancy;
}
Bitboard PreCalculate::evaluatePawnAttackMask(int color, int source_square)
{
    Bitboard bitboard = EMPTY_BOARD;
    Bitboard attack_mask = EMPTY_BOARD;
    BitboardUtils::setBit(bitboard, source_square);
    if (!color)
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
Bitboard PreCalculate::evaluateKnightAttackMask(int source_square)
{
    Bitboard bitboard = EMPTY_BOARD;
    Bitboard attack_mask = EMPTY_BOARD;
    BitboardUtils::setBit(bitboard, source_square);
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
Bitboard PreCalculate::evaluateKingAttackMask(int source_square)
{
    Bitboard bitboard = EMPTY_BOARD;
    Bitboard attack_mask = EMPTY_BOARD;
    BitboardUtils::setBit(bitboard, source_square);
    if (bitboard >> DIMENSION)
        attack_mask |= bitboard >> DIMENSION;
    if (bitboard << DIMENSION)
        attack_mask |= bitboard << DIMENSION;
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
Bitboard PreCalculate::evaluateRawBishopAttackMask(int source_square)
{
    Bitboard attack_mask = EMPTY_BOARD;
    int rank, file;
    int target_rank = source_square / DIMENSION;
    int target_file = source_square % DIMENSION;
    for (rank = target_rank + 1, file = target_file + 1;
         rank < DIMENSION - 1 && file < DIMENSION - 1;
         rank++, file++)
        attack_mask |= (1ULL << (rank * DIMENSION + file));
    for (rank = target_rank - 1, file = target_file + 1;
         rank > 0 && file < DIMENSION - 1;
         rank--, file++)
        attack_mask |= (1ULL << (rank * DIMENSION + file));
    for (rank = target_rank + 1, file = target_file - 1;
         rank < DIMENSION - 1 && file > 0;
         rank++, file--)
        attack_mask |= (1ULL << (rank * DIMENSION + file));
    for (rank = target_rank - 1, file = target_file - 1;
         rank > 0 && file > 0;
         rank--, file--)
        attack_mask |= (1ULL << (rank * DIMENSION + file));
    return attack_mask;
}
Bitboard PreCalculate::evaluateBishopAttackMask(int source_square, Bitboard occupancy)
{
    Bitboard attack_mask = EMPTY_BOARD;
    int rank, file;
    int target_rank = source_square / DIMENSION;
    int target_file = source_square % DIMENSION;

    for (rank = target_rank + 1, file = target_file + 1;
         rank < DIMENSION && file < DIMENSION;
         rank++, file++)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + file));
        if ((1ULL << (rank * DIMENSION + file)) & occupancy)
            break;
    }
    for (rank = target_rank + 1, file = target_file - 1;
         rank < DIMENSION && file >= 0;
         rank++, file--)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + file));
        if ((1ULL << (rank * DIMENSION + file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1, file = target_file + 1;
         rank >= 0 && file < DIMENSION;
         rank--, file++)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + file));
        if ((1ULL << (rank * DIMENSION + file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1, file = target_file - 1;
         rank >= 0 && file >= 0;
         rank--, file--)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + file));
        if ((1ULL << (rank * DIMENSION + file)) & occupancy)
            break;
    }

    return attack_mask;
}
Bitboard PreCalculate::evaluateRawRookAttackMask(int source_square)
{
    Bitboard attack_mask = EMPTY_BOARD;
    int rank, file;
    int target_rank = source_square / DIMENSION;
    int target_file = source_square % DIMENSION;
    for (rank = target_rank + 1; rank < DIMENSION - 1; rank++)
        attack_mask |= (1ULL << (rank * DIMENSION + target_file));
    for (rank = target_rank - 1; rank > 0; rank--)
        attack_mask |= (1ULL << (rank * DIMENSION + target_file));
    for (file = target_file + 1; file < DIMENSION - 1; file++)
        attack_mask |= (1ULL << (target_rank * DIMENSION + file));
    for (file = target_file - 1; file > 0; file--)
        attack_mask |= (1ULL << (target_rank * DIMENSION + file));
    return attack_mask;
}
Bitboard PreCalculate::evaluateRookAttackMask(int source_square, Bitboard occupancy)
{
    Bitboard attack_mask = EMPTY_BOARD;
    int rank, file;
    int target_rank = source_square / DIMENSION;
    int target_file = source_square % DIMENSION;
    for (rank = target_rank + 1; rank < DIMENSION; rank++)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + target_file));
        if ((1ULL << (rank * DIMENSION + target_file)) & occupancy)
            break;
    }
    for (rank = target_rank - 1; rank >= 0; rank--)
    {
        attack_mask |= (1ULL << (rank * DIMENSION + target_file));
        if ((1ULL << (rank * DIMENSION + target_file)) & occupancy)
            break;
    }
    for (file = target_file + 1; file < DIMENSION; file++)
    {
        attack_mask |= (1ULL << (target_rank * DIMENSION + file));
        if ((1ULL << (target_rank * DIMENSION + file)) & occupancy)
            break;
    }
    for (file = target_file - 1; file >= 0; file--)
    {
        attack_mask |= (1ULL << (target_rank * DIMENSION + file));
        if ((1ULL << (target_rank * DIMENSION + file)) & occupancy)
            break;
    }
    return attack_mask;
}