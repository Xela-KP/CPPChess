#pragma once
#include "board.hpp"
class MoveGen
{
public:
    // public for logging purposes

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