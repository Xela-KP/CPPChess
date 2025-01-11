#pragma once
#include "bitboard.hpp"
#include "board.hpp"
namespace Log
{
    void printBitboard(Bitboard bitboard);
    void printPieceOccupancy(Board board, int piece);
    void printChessboard(Board board);
    void printAttackedSquares(Board board, int color);
    void printMoves(Board board, int color);
    void printMoveEncoding(int move);
    void printMovesEncoding(std::vector<int> moves);
}