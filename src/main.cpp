#include <iostream>
#include <vector>
#include "../include/mask.hpp"
#include "../include/logging.hpp"
#include "../include/movement.hpp"
#include "../include/FEN.hpp"
int main()
{
    int color = 0;
    std::vector<Board> history;
    AttackMaskUtils::mapAttackMasks();
    Board board(FEN::TRICKY_POSITION);
    MovementUtils::mapMoves(board, color);
    history.push_back(board.copy());
    Log::printChessboard(board);
    Log::printMoves(board, color);
    Log::printAttackedSquares(board, color);
    // Log::printPieceOccupancy(board, ChessEncoding::n);
    return 0;
}