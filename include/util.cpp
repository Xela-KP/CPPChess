
#include <iostream>
#include "bitboard.hpp"
#include "util.hpp"
#include "mask.hpp"
#include "state.hpp"
#include "movement.hpp"
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

    void print_piece_chessboard(chess::Piece piece)
    {
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            std::cout << DIMENSION - rank << "   ";
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                std::cout << (bitboard::get_bit(state::piece_occupancies[piece], square)
                                  ? chess::ASCII_PIECES[piece]
                                  : '.')
                          << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n decimal value = " << std::dec << state::piece_occupancies[piece] << '\n';
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
                    if (bitboard::get_bit(state::piece_occupancies[piece], square))
                        ascii = chess::ASCII_PIECES[piece];
                }
                std::cout << (ascii < 0 ? '+' : ascii) << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n    side:       " << (state::color ? "black" : "white");
        std::cout << "\n    enpassant:  " << (chess::SQUARE_TO_ALGEBRAIC_NOTATION[state::enpassant_square]);
        std::cout << "\n    castle:     "
                  << (state::castle_privelage & chess::wk ? "K" : "-")
                  << (state::castle_privelage & chess::wq ? "Q" : "-")
                  << (state::castle_privelage & chess::bk ? "k" : "-")
                  << (state::castle_privelage & chess::bq ? "q" : "-")
                  << "\n\n";
    }

    void print_attacked_squares(int color)
    {
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            std::cout << DIMENSION - rank << "   ";
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                std::cout << movement::get_num_attackers_on(square, color) << ' ';
            }
            std::cout << ('\n');
        }
        std::cout << "\n    a b c d e f g h\n";
        std::cout << "\n    attacks from: " << (color ? "black" : "white\n");
    };
}