#pragma once
class MoveUtils
{
public:
    static int encodeMove(int source_square, int target_square, int piece,
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
    static int decodeSourceSquare(int move) { return move & 0x3f; }
    static int decodePiece(int move) { return (move & 0xf000) >> 12; }
    static int decodePromotionPiece(int move) { return (move & 0xf0000) >> 16; }
    static int decodeCaptureFlag(int move) { return move & 0x100000; }
    static int decodeDoublePawnPushFlag(int move) { return move & 0x200000; }
    static int decodeEnpassantFlag(int move) { return move & 0x400000; }
    static int decodeCastleFlag(int move) { return move & 0x800000; }
};