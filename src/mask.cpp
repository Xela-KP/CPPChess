#include <iostream>
#include "../include/mask.hpp"
#include "../include/magic.hpp"
#include "../include/encodings.hpp"
U64 MaskUtils::pawn_attack_masks[2][BOARD_SIZE];
U64 MaskUtils::knight_attack_masks[BOARD_SIZE];
U64 MaskUtils::king_attack_masks[BOARD_SIZE];
U64 MaskUtils::bishop_attack_masks[BOARD_SIZE][4096];
U64 MaskUtils::rook_attack_masks[BOARD_SIZE][4096];
U64 MaskUtils::queen_attack_masks[BOARD_SIZE][4096];
U64 MaskUtils::bishop_unblocked_attack_masks[BOARD_SIZE];
U64 MaskUtils::rook_unblocked_attack_masks[BOARD_SIZE];
void MaskUtils::map_leap_attack_masks()
{
    for (int from_square = chess::a8; from_square <= chess::h1; from_square++)
    {
        pawn_attack_masks[chess::WHITE][from_square] =
            mask::evaluate_pawn_attack_mask(chess::WHITE, from_square);
        pawn_attack_masks[chess::BLACK][from_square] =
            mask::evaluate_pawn_attack_mask(chess::BLACK, from_square);
        knight_attack_masks[from_square] =
            mask::evaluate_knight_attack_mask(from_square);
        king_attack_masks[from_square] =
            mask::evaluate_king_attack_mask(from_square);
    }
}
void MaskUtils::map_slide_attack_masks()
{
    for (int from_square = chess::a8; from_square <= chess::h1; from_square++)
    {
        bishop_unblocked_attack_masks[from_square] =
            mask::evaluate_bishop_unblocked_attack_mask(from_square);
        rook_unblocked_attack_masks[from_square] =
            mask::evaluate_rook_unblocked_attack_mask(from_square);
        U64 bishop_unblocked_mask = get_bishop_unblocked_attack_mask(from_square);
        for (int occupancy_index = 0;
             occupancy_index < (1 << get_bit_count(bishop_unblocked_mask));
             occupancy_index++)
        {
            U64 masked_occupancy =
                mask::evaluate_masked_occupancy(occupancy_index, bishop_unblocked_mask);
            int magic_index =
                (masked_occupancy * magic::BISHOP_MAGIC_NUMBERS[from_square]) >>
                (64 - magic::BISHOP_ATTACK_COUNT_MASK[from_square]);
            bishop_attack_masks[from_square][magic_index] =
                mask::evaluate_bishop_blocked_attack_mask(from_square, masked_occupancy);
            queen_attack_masks[from_square][magic_index] |=
                bishop_attack_masks[from_square][magic_index];
        }
        U64 rook_unblocked_attack_mask = rook_unblocked_attack_masks[from_square];
        for (int occupancy_index = 0;
             occupancy_index < (1 << get_bit_count(rook_unblocked_attack_mask));
             occupancy_index++)
        {
            U64 masked_occupancy =
                mask::evaluate_masked_occupancy(occupancy_index, rook_unblocked_attack_mask);
            int magic_index =
                (masked_occupancy * magic::ROOK_MAGIC_NUMBERS[from_square]) >>
                (64 - magic::ROOK_ATTACK_COUNT_MASK[from_square]);
            rook_attack_masks[from_square][magic_index] =
                mask::evaluate_rook_blocked_attack_mask(from_square, masked_occupancy);
            queen_attack_masks[from_square][magic_index] |=
                rook_attack_masks[from_square][magic_index];
        }
    }
}
void MaskUtils::map_attack_masks()
{
    map_leap_attack_masks();
    map_slide_attack_masks();
}
U64 MaskUtils::get_pawn_attack_mask(int side, int source_square) { return pawn_attack_masks[side][source_square]; }
U64 MaskUtils::get_knight_attack_mask(int source_square) { return knight_attack_masks[source_square]; }
U64 MaskUtils::get_king_attack_mask(int source_square) { return king_attack_masks[source_square]; }
U64 MaskUtils::get_bishop_attack_mask(int source_square, U64 occupancy)
{
    occupancy &= bishop_unblocked_attack_masks[source_square];
    occupancy *= magic::BISHOP_MAGIC_NUMBERS[source_square];
    occupancy >>= 64 - magic::BISHOP_ATTACK_COUNT_MASK[source_square];
    return bishop_attack_masks[source_square][occupancy];
}
U64 MaskUtils::get_rook_attack_mask(int source_square, U64 occupancy)
{
    occupancy &= rook_unblocked_attack_masks[source_square];
    occupancy *= magic::ROOK_MAGIC_NUMBERS[source_square];
    occupancy >>= 64 - magic::ROOK_ATTACK_COUNT_MASK[source_square];
    return rook_attack_masks[source_square][occupancy];
};
U64 MaskUtils::get_queen_attack_mask(int source_square, U64 occupancy) { return get_bishop_attack_mask(source_square, occupancy) | get_rook_attack_mask(source_square, occupancy); }
U64 MaskUtils::get_bishop_unblocked_attack_mask(int source_square) { return bishop_unblocked_attack_masks[source_square]; }
U64 MaskUtils::get_rook_unblocked_attack_mask(int source_square) { return rook_unblocked_attack_masks[source_square]; }
