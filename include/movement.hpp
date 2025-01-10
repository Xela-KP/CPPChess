#pragma once
#include "board.hpp"
class MovementUtils
{
    static inline int encodeMove(int source_square, int target_square, int piece,
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
    static inline int decodeSourceSquare(int move) { return move & 0x3f; }
    static inline int decodePiece(int move) { return (move & 0xf000) >> 12; }
    static inline int decodePromotionPiece(int move) { return (move & 0xf0000) >> 16; }
    static inline int decodeCaptureFlag(int move) { return move & 0x100000; }
    static inline int decodeDoublePawnPushFlag(int move) { return move & 0x200000; }
    static inline int decodeEnpassantFlag(int move) { return move & 0x400000; }
    static inline int decodeCastleFlag(int move) { return move & 0x800000; }

public:
    // public for logging purposes
    static inline int decodeTargetSquare(int move) { return (move & 0xfc0) >> 6; }

    static int isAttacked(Board board, int square, int color);
    static void mapPawnMoves(Board &board, int color);
    static void mapKingMoves(Board &board, int color);
    static void mapKnightMoves(Board &board, int color);
    static void mapBishopMoves(Board &board, int color);
    static void mapRookMoves(Board &board, int color);
    static void mapQueenMoves(Board &board, int color);
    static void mapMoves(Board &board, int color);
};