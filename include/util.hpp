#pragma once
#include "types.hpp"
#include "gamestate.hpp"
namespace util
{
    void print_bitboard(U64 bitboard);
    void print_piece_chessboard(GameState gamestate, int piece);
    void print_chessboard(GameState gamestate);
    void print_attacked_squares(GameState gamestate, int color);
    void print_moves(GameState gamestate, int color);
}