
#include <iostream>
#include "util.hpp"
#include "mask.hpp"
#include "encodings.hpp"
#include "state.hpp"
namespace util
{
    void print_bitboard(U64 bitboard)
    {
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            std::cout << DIMENSION - rank << "   ";
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                std::cout << bitboard::get_bit(bitboard, square) << ' ';
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
                std::cout << (bitboard::get_bit(mask::piece_occupancies[piece], square)
                                  ? chess::ASCII_PIECES[piece]
                                  : '.')
                          << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n decimal value = " << std::dec << mask::piece_occupancies[piece] << '\n';
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
                for (int piece = chess::P; piece <= chess::k; piece++)
                {
                    if (bitboard::get_bit(mask::piece_occupancies[piece], square))
                        ascii = chess::ASCII_PIECES[piece];
                }
                std::cout << (ascii < 0 ? '+' : ascii) << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n    side:       " << (state::side ? "black" : "white");
        std::cout << "\n    enpassant:  " << (chess::SQUARE_TO_ALGEBRAIC_NOTATION[state::enpassant]);
        std::cout << "\n    castle:     "
                  << (state::castle & chess::wk ? "K" : "-")
                  << (state::castle & chess::wq ? "Q" : "-")
                  << (state::castle & chess::bk ? "k" : "-")
                  << (state::castle & chess::bq ? "q" : "-")
                  << "\n\n";
    }
}