#pragma once
#include <vector>
#include "bitboard.hpp"
#include "encodings.hpp"
#include "FEN.hpp"
class Board
{
    Bitboard piece_occupancies[12];
    Bitboard color_occupancies[3];
    Bitboard zobrist_hash;
    std::vector<int> moves;
    int enpassant_square;
    int castle_privelage;
    int sideToMove;

public:
    Board(std::string fen = FEN::START_POSITION);
    Board copy();
    Bitboard getPieceOccupancy(int piece);
    Bitboard getColorOccupancy(int color);
    std::vector<int> getMoves();
    int getSideToMove();
    int getEnpassantSquare();
    int getCastlePrivelage();
    int getMove(int i);
    void pushMove(int move);
    void clearMoves();
    void parseFEN(std::string fen);
};
