#pragma once
#include "types.hpp"
#include "bitboard.hpp"
namespace Mask
{
    U64 get_masked_occupancy(int occupied, U64 attack_mask);
    U64 get_pawn_attack_mask(int side, int from_square);
    U64 get_knight_attack_mask(int from_square);
    U64 get_king_attack_mask(int from_square);
    U64 get_bishop_unblocked_attack_mask(int from_square);
    U64 get_bishop_blocked_attack_mask(int from_square, U64 occupancy);
    U64 get_rook_unblocked_attack_mask(int from_square);
    U64 get_rook_blocked_attack_mask(int from_square, U64 occupancy);
    static inline U64 get_bishop_attack_mask(U64 square, U64 occupancy);
    static inline U64 get_rook_attack_mask(U64 square, U64 occupancy);
    void map_leap_attacks();
    void map_slide_attacks(int bishop);
    void initialize_occupancies();
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
    U64 piece_occupancies[12];
    U64 side_occupancies[3];
}
