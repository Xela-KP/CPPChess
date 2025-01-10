#include <iostream>
#include "../include/mask.hpp"
#include "../include/logging.hpp"
#include "../include/movement.hpp"
int main()
{
    AttackMaskUtils::mapAttackMasks();
    Board b;
    MovementUtils::mapMoves(b, 0);
    Log::printChessboard(b);
    Log::printAttackedSquares(b, 0);
    Log::printMoves(b, 0);
    Log::printPieceOccupancy(b, ChessEncoding::n);
    return 0;
}