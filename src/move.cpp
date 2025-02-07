#include "../include/move.hpp"

Move::Move(int source_square, int target_square, int piece,
           int promotion_piece, int is_capture,
           int is_double_pawn_push, int is_enpassant, int is_castle)
{
    Encode(source_square, target_square, piece, promotion_piece, is_capture, is_double_pawn_push, is_enpassant, is_castle);
}
int Move::Encode(int source_square, int target_square, int piece,
             int promotion_piece, int is_capture,
             int is_double_pawn_push, int is_enpassant, int is_castle)
{
    encoding = (source_square |
                target_square << 6 |
                piece << 12 |
                promotion_piece << 16 |
                is_capture << 20 |
                is_double_pawn_push << 21 |
                is_enpassant << 22 |
                is_castle << 23);
    return encoding;
}
int Move::DecodeTargetSquare(Move move) const { return (move & 0xfc0) >> 6; }
int Move::DecodeSourceSquare(Move move) const { return move & 0x3f; }
int Move::DecodePiece(Move move) const { return (move & 0xf000) >> 12; }
int Move::DecodePromotionPiece(Move move) const { return (move & 0xf0000) >> 16; }
int Move::DecodeCaptureFlag(Move move) const { return move & 0x100000; }
int Move::DecodeDoublePawnPushFlag(Move move) const { return move & 0x200000; }
int Move::DecodeEnpassantFlag(Move move) const { return move & 0x400000; }
int Move::DecodeCastleFlag(Move move) const { return move & 0x800000; }
Move::operator int() const { return encoding; }