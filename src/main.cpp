#include <iostream>
#include "../include/mask.hpp"
#include "../include/logging.hpp"

int main()
{
    AttackMaskUtils::mapAttackMasks();
    Board b;
    Log::printChessboard(b);
    Log::printAttackedSquares(b, 0);
    return 0;
}