
#include <iostream>
#include "util.hpp"
#include "mask.hpp"
#include "encodings.hpp"
namespace Util
{
    void print_bitboard(U64 bitboard)
    {
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            std::cout << DIMENSION - rank << "   ";
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                std::cout << Bitboard::get_bit(bitboard, square) << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n decimal value = " << std::dec << bitboard << '\n';
    }

    void print_piece_chessboard(int piece)
    {
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            std::cout << DIMENSION - rank << "   ";
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                std::cout << (Bitboard::get_bit(Mask::piece_occupancies[piece], square)
                                  ? ChessEncoding::ASCII_PIECES[piece]
                                  : '.')
                          << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n decimal value = " << std::dec << Mask::piece_occupancies[piece] << '\n';
    }

    void print_chessboard()
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
                    if (Bitboard::get_bit(Mask::piece_occupancies[piece], square))
                        ascii = ChessEncoding::ASCII_PIECES[piece];
                }
                std::cout << (ascii < 0 ? '+' : ascii) << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n decimal value = " << std::dec << (Mask::side_occupancies[ChessEncoding::WHITE] | Mask::side_occupancies[ChessEncoding::BLACK]) << '\n';
    }
}