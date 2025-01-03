#pragma once
#include "encodings.hpp"
#include <vector>
namespace state
{
    int color = chess::WHITE;
    int enpassant_square = chess::NO_SQUARE;
    int castle_privelage = chess::NO_CASTLE;
    U64 pawn_attack_mask[2][BOARD_SIZE];
    U64 knight_attack_mask[BOARD_SIZE];
    U64 king_attack_mask[BOARD_SIZE];
    U64 bishop_attack_mask[BOARD_SIZE][4096];
    U64 rook_attack_mask[BOARD_SIZE][4096];
    U64 queen_attack_mask[BOARD_SIZE][4096];
    U64 bishop_unblocked_attack_mask[BOARD_SIZE];
    U64 rook_unblocked_attack_mask[BOARD_SIZE];
    U64 piece_occupancies[12];
    U64 side_occupancies[3];
    std::vector<int> moves;
}