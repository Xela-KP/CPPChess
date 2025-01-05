#pragma once
#include "gamestate.hpp"
namespace movement
{
    static inline int encode_move(int source_square, int target_square, int piece,
                                  int promotion_piece, int is_capture,
                                  int is_double_pawn_push, int is_enpassant, int is_castle)
    {
        return (source_square |
                target_square << 6 |
                piece << 12 |
                promotion_piece << 16 |
                is_capture << 20 |
                is_double_pawn_push << 21 |
                is_enpassant << 22 |
                is_castle << 23);
    };
    static inline int decode_source_square(int move) { return move & 0x3f; }
    static inline int decode_target_square(int move) { return (move & 0xfc0) >> 6; }
    static inline int decode_piece(int move) { return (move & 0xf000) >> 12; }
    static inline int decode_promotion_piece(int move) { return (move & 0xf0000) >> 16; }
    static inline int decode_capture_flag(int move) { return move & 0x100000; }
    static inline int decode_double_pawn_push_flag(int move) { return move & 0x200000; }
    static inline int decode_enpassant_flag(int move) { return move & 0x400000; }
    static inline int decode_castle_flag(int move) { return move & 0x800000; }
    int get_num_attackers_on(GameState gamestate, int square, int color);
    void get_pawn_moves(GameState &gamestate, int color);
    void get_king_moves(GameState &gamestate, int color);
    void get_knight_moves(GameState &gamestate, int color);
    void get_bishop_moves(GameState &gamestate, int color);
    void get_rook_moves(GameState &gamestate, int color);
    void get_queen_moves(GameState &gamestate, int color);
    void get_moves(GameState &gamestate, int color);
}