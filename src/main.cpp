#include <iostream>
#include <vector>
// #include "../include/mask.hpp"
#include "../include/attack_mask.hpp"
#include "../include/movegen.hpp"
#include "../include/logging.hpp"
#include "../include/fen.hpp"
#include "../include/chess_board.hpp"
#include "../include/controller.hpp"

int main()
{
    int color = 0;
    AttackMask::initialize();
    ChessBoard chess_board;
    Controller controller(chess_board);
    controller.ParseFen(Fen::TRICKY_POSITION);

    Log::PrintChessBoard(chess_board);

    std::cout << "P: " << MoveGen::GetPawnMoves(chess_board, 0).size() << std::endl;
    std::cout << "p: " << MoveGen::GetPawnMoves(chess_board, 1).size() << std::endl;

    std::cout << "K: " << MoveGen::GetKingMoves(chess_board, 0).size() << std::endl;
    std::cout << "k: " << MoveGen::GetKingMoves(chess_board, 1).size() << std::endl;

    // Log::PrintMoves(chess_board, color);

    // Log::PrintMoves(chess_board, color);
    // Log::PrintAttackedSquares(chess_board, color);

    // std::vector<Move> moves = MoveGen::GetMoves(chess_board, color);
    // // Log::printMovesEncoding(moves);
    // Log::PrintMoveEncoding(moves[4]);
    // controller.MakeMove(moves[4], color);
    // Log::PrintChessBoard(chess_board);
    return 0;
}