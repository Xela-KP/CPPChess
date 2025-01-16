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
    int enpassant_square;
    int castle_privelage;
    int sideToMove;

public:
    Board(std::string fen = FEN::START_POSITION);
    Board copy();
    Bitboard getPieceOccupancy(int piece) const;
    Bitboard getColorOccupancy(int color) const;
    int getSideToMove() const;
    int getEnpassantSquare() const;
    int getCastlePrivelage() const;
    void parseFEN(std::string fen);
    // TODO: Implement makeMove. Make sure Board is only ever handling things related to the state.
    void makeMove(int move, int color);
    bool isLegalPosition(Bitboard occupancy);
};
