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
    static std::vector<int> getPawnMoves(Board board, int color);
    static std::vector<int> getKingMoves(Board board, int color);
    static std::vector<int> getKnightMoves(Board board, int color);
    static std::vector<int> getBishopMoves(Board board, int color);
    static std::vector<int> getRookMoves(Board board, int color);
    static std::vector<int> getQueenMoves(Board board, int color);
    static std::vector<int> getMoves(Board board, int color);
};

/*
          binary move encoding                           hexidecimal constants
    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000
*/