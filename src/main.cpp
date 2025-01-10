#include <iostream>
#include "../include/mask.hpp"
#include "../include/logging.hpp"
#include "../include/movement.hpp"
#include "../include/FEN.hpp"
int main()
{
    Board board(FEN::TRICKY_POSITION);
    int color = 0;
    AttackMaskUtils::mapAttackMasks();
    MovementUtils::mapMoves(board, color);
    Log::printChessboard(board);
    Log::printMoves(board, color);
    Log::printAttackedSquares(board, color);
    // Log::printPieceOccupancy(board, ChessEncoding::n);
    return 0;
}