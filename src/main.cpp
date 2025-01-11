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
    Board board(FEN::TRICKY_POSITION);
    history.push_back(board.copy());
    Log::printChessboard(board);
    // Log::printMoves(board, color);
    // Log::printAttackedSquares(board, color);

    std::vector<int> moves = MoveGen::getMoves(board, color);
    Log::printMoveEncoding(moves[1]);
    board.makeMove(moves[1], color);
    Log::printChessboard(board);
    return 0;
}

/*
Move: 1
P d5 e6
Promote: 0
Capture: Yes
DPP: No
Castle: No
Enpassant: No
*/