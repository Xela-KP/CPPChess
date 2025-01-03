#pragma once
namespace movement
{
    static inline int encode_move(int source_square, int target_square, int piece,
                                  int promotion_piece, int is_capture,
                                  int is_double_pawn_push, int is_enpassant, int is_castle);
    static inline int decode_source_square(int move);
    static inline int decode_target_square(int move);
    static inline int decode_piece(int move);
    static inline int decode_promotion_piece(int move);
    static inline int decode_capture_flag(int move);
    static inline int decode_double_pawn_push_flag(int move);
    static inline int decode_enpassant_flag(int move);
    static inline int decode_castle_flag(int move);
    int get_num_attackers_on(int color, int square);
    void get_pawn_moves(int color);
    void get_king_moves(int color);
    void get_knight_moves(int color);
    // void get_bishop_moves(int color);
    // void get_rook_moves(int color);
    // void get_queen_moves(int color);
    void get_moves(int color);
}