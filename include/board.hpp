#pragma once
#include <vector>
#include "bitboard.hpp"
#include "encodings.hpp"
class Board
{
    Bitboard piece_occupancies[12];
    Bitboard color_occupancies[3];
    Bitboard zobrist_hash;
    int enpassant_square;
    int castle_privelage;
    int sideToMove;
    std::vector<int> moves;

public:
    Board();
    Bitboard getPieceOccupancy(int piece);
    Bitboard getColorOccupancy(int color);
    int getSideToMove();
    int getEnpassantSquare();
    int getCastlePrivelage();
    std::vector<int> getMoves();
    int getMove(int i);
    void pushMove(int move);
    void clearMoves();
    void parseFEN(std::string fen);
};
