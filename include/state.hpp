#pragma once
#include "encodings.hpp"
namespace state
{
    int side = chess::WHITE;
    int enpassant = chess::NO_SQUARE;
    int castle = chess::NO_CASTLE;
    U64 piece_occupancies[12];
    U64 side_occupancies[3];
}