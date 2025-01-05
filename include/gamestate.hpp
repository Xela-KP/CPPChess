
#pragma once
#include <vector>
#include <string>
#include "types.hpp"
class GameState
{
private:
    int color;
    int enpassant_square;
    int castle_privelage;
    U64 piece_occupancies[12];
    U64 color_occupancies[3];
    std::vector<int> moves;

public:
    GameState();
    int get_color();
    int get_enpassant_square();
    int get_castle_privelage();
    U64 get_piece_occupancy(int piece);
    U64 get_color_occupancy(int color);
    std::vector<int> get_moves();
    void parse_fen(std::string fen);
};