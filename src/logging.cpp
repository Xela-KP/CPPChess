#include <iostream>
#include "../include/logging.hpp"
#include "../include/movement.hpp"

void Log::printBitboard(Bitboard bitboard)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << BitboardUtils::getBit(bitboard, square) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n decimal value = " << std::dec << bitboard << '\n';
}
void Log::printPieceOccupancy(Board board, int piece)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << (BitboardUtils::getBit(board.getPieceOccupancy(piece), square)
                              ? ChessEncoding::ASCII_PIECES[piece]
                              : '.')
                      << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n decimal value = " << std::dec << board.getPieceOccupancy(piece) << '\n';
}
void Log::printChessboard(Board board)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            char ascii = -1;
            for (int piece = ChessEncoding::P; piece <= ChessEncoding::k; piece++)
            {
                if (BitboardUtils::getBit(board.getPieceOccupancy(piece), square))
                    ascii = ChessEncoding::ASCII_PIECES[piece];
            }
            std::cout << (ascii < 0 ? '.' : ascii) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    side:       " << (board.getSideToMove() ? "black" : "white");
    int eps = board.getEnpassantSquare();
    std::cout << "\n    enpassant:  " << (eps < 64 ? ChessEncoding::SQUARE_TO_ALGEBRAIC_NOTATION[eps] : "No Square");
    std::cout << "\n    castle:     "
              << (board.getCastlePrivelage() & ChessEncoding::wk ? "K" : "-")
              << (board.getCastlePrivelage() & ChessEncoding::wq ? "Q" : "-")
              << (board.getCastlePrivelage() & ChessEncoding::bk ? "k" : "-")
              << (board.getCastlePrivelage() & ChessEncoding::bq ? "q" : "-")
              << "\n\n";
}
void Log::printAttackedSquares(Board board, int color)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << (MovementUtils::isAttacked(board, square, color) ? 'x' : '.') << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    attacks from: " << (color ? "black" : "white\n");
};
void Log::printMoves(Board board, int color)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            int target_square = -1;
            for (int i = 0; i < board.getMoves().size(); i++)
            {
                target_square = MovementUtils::decodeTargetSquare(board.getMove(i));
                if (square == target_square)
                    break;
                target_square = -1;
            }
            std::cout << (target_square >= 0 ? 'x' : '.') << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    moves for: " << (color ? "black" : "white\n");
}
