#pragma once
#include "types.hpp"
#include "encodings.hpp"
namespace util
{
    void print_bitboard(U64 bitboard);
    void print_piece_chessboard(chess::Piece piece);
    void print_chessboard();
    void print_attacked_squares(int color);
}