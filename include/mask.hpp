#pragma once
#include "types.hpp"
#include "encodings.hpp"
namespace mask
{
    const U64 NOT_A_FILE = 18374403900871474942ULL;
    const U64 NOT_H_FILE = 9187201950435737471ULL;
    const U64 NOT_HG_FILE = 4557430888798830399ULL;
    const U64 NOT_AB_FILE = 18229723555195321596ULL;
    static inline U64 get_masked_occupancy(int occupany_index, U64 attack_mask);
    static inline U64 get_pawn_attack_mask(chess::Color color, chess::Square from_square);
    static inline U64 get_knight_attack_mask(chess::Square from_square);
    static inline U64 get_king_attack_mask(chess::Square from_square);
    static inline U64 get_queen_attack_mask(chess::Square square, U64 occupancy);
    static inline U64 get_bishop_attack_mask(chess::Square square, U64 occupancy);
    static inline U64 get_rook_attack_mask(chess::Square square, U64 occupancy);
    U64 get_bishop_unblocked_attack_mask(chess::Square from_square);
    U64 get_bishop_blocked_attack_mask(chess::Square from_square, U64 occupancy);
    U64 get_rook_unblocked_attack_mask(chess::Square from_square);
    U64 get_rook_blocked_attack_mask(chess::Square from_square, U64 occupancy);
    void map_leap_attacks();
    void map_slide_attacks();
}
