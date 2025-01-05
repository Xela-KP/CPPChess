#include <iostream>
#include "../include/util.hpp"
#include "../include/bitboard.hpp"
#include "../include/mask.hpp"
#include "../include/gamestate.hpp"
#include "../include/encodings.hpp"
#include "../include/movement.hpp"

void util::print_bitboard(U64 bitboard)
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
void util::print_piece_chessboard(GameState gamestate, int piece)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << (bitboard::get_bit(gamestate.get_piece_occupancy(piece), square)
                              ? chess::ASCII_PIECES[piece]
                              : '.')
                      << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n decimal value = " << std::dec << gamestate.get_piece_occupancy(piece) << '\n';
}
void util::print_chessboard(GameState gamestate)
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
                if (bitboard::get_bit(gamestate.get_piece_occupancy(piece), square))
                    ascii = chess::ASCII_PIECES[piece];
            }
            std::cout << (ascii < 0 ? '+' : ascii) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    side:       " << (gamestate.get_color() ? "black" : "white");
    std::cout << "\n    enpassant:  " << (chess::SQUARE_TO_ALGEBRAIC_NOTATION[gamestate.get_enpassant_square()]);
    std::cout << "\n    castle:     "
              << (gamestate.get_castle_privelage() & chess::wk ? "K" : "-")
              << (gamestate.get_castle_privelage() & chess::wq ? "Q" : "-")
              << (gamestate.get_castle_privelage() & chess::bk ? "k" : "-")
              << (gamestate.get_castle_privelage() & chess::bq ? "q" : "-")
              << "\n\n";
}
void util::print_attacked_squares(GameState gamestate, int color)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            std::cout << movement::get_num_attackers_on(gamestate, square, color) << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    attacks from: " << (color ? "black" : "white\n");
};
void util::print_moves(GameState gamestate, int color)
{
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        std::cout << DIMENSION - rank << "   ";
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            int target_square = -1;
            for (int i = 0; i < gamestate.get_moves().size(); i++)
            {
                target_square = movement::decode_target_square(gamestate.get_move(i));
                if (square == target_square)
                    break;
                target_square = -1;
            }
            std::cout << (target_square >= 0 ? 'X' : '+') << ' ';
        }
        std::cout << ('\n');
    }
    std::cout << "\n    a b c d e f g h\n";
    std::cout << "\n    moves for: " << (color ? "black" : "white\n");
}
