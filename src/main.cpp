#include <iostream>
#include <vector>
#include "../include/mask.hpp"
#include "../include/logging.hpp"
#include "../include/movegen.hpp"
#include "../include/FEN.hpp"
int main()
{
    int color = 0;
    std::vector<Board> history;
    AttackMaskUtils::mapAttackMasks();
    Board board(FEN::KILLER_POSITION);
    history.push_back(board.copy());
    Log::printChessboard(board);
    // Log::printMoves(board, color);
    // Log::printAttackedSquares(board, color);

    std::vector<int> moves = MoveGen::getMoves(board, color);
    // Log::printMovesEncoding(moves);
    Log::printMoveEncoding(moves[4]);
    board.makeMove(moves[4], color);
    Log::printChessboard(board);
    return 0;
}

/*
Move: 4
P f5 e6
Promote: 0
Capture: Yes
DPP: No
Castle: No
Enpassant: Yes
*/