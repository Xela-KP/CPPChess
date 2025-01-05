#pragma once
#include "types.hpp"
#include "bitboard.hpp"

namespace mask
{
    static const U64 NOT_A_FILE = 18374403900871474942ULL;
    static const U64 NOT_H_FILE = 9187201950435737471ULL;
    static const U64 NOT_HG_FILE = 4557430888798830399ULL;
    static const U64 NOT_AB_FILE = 18229723555195321596ULL;
    static inline U64 evaluate_masked_occupancy(int occupany_index, U64 attack_mask);
    static inline U64 evaluate_pawn_attack_mask(int color, int source_square);
    static inline U64 evaluate_knight_attack_mask(int source_square);
    static inline U64 evaluate_king_attack_mask(int source_square);
    static inline U64 evaluate_bishop_unblocked_attack_mask(int source_square);
    static inline U64 evaluate_bishop_blocked_attack_mask(int source_square, U64 occupancy);
    static inline U64 evaluate_rook_unblocked_attack_mask(int source_square);
    static inline U64 evaluate_rook_blocked_attack_mask(int source_square, U64 occupancy);
}

class MaskUtils
{
    static U64 pawn_attack_masks[2][BOARD_SIZE];
    static U64 knight_attack_masks[BOARD_SIZE];
    static U64 king_attack_masks[BOARD_SIZE];
    static U64 bishop_attack_masks[BOARD_SIZE][4096];
    static U64 rook_attack_masks[BOARD_SIZE][4096];
    static U64 queen_attack_masks[BOARD_SIZE][4096];
    static U64 bishop_unblocked_attack_masks[BOARD_SIZE];
    static U64 rook_unblocked_attack_masks[BOARD_SIZE];

private:
    static void map_leap_attack_masks();
    static void map_slide_attack_masks();

public:
    static void map_attack_masks();
    static U64 get_pawn_attack_mask(int side, int source_square);
    static U64 get_knight_attack_mask(int source_square);
    static U64 get_king_attack_mask(int source_square);
    static U64 get_bishop_attack_mask(int source_square, U64 occupancy);
    static U64 get_rook_attack_mask(int source_square, U64 occupancy);
    static U64 get_queen_attack_mask(int source_square, U64 occupancy);
    static U64 get_bishop_unblocked_attack_mask(int source_square);
    static U64 get_rook_unblocked_attack_mask(int source_square);
};
