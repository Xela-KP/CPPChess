#pragma once
#include "gamestate.hpp"
#include "encodings.hpp"
#include "bitboard.hpp"
#include "fen.hpp"
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
    GameState()
    {
        parse_fen(START_POSITION);
        color = chess::WHITE;
        enpassant_square = chess::NO_SQUARE;
        castle_privelage = chess::NO_CASTLE;
    }
    int get_color() { return color; }
    int get_enpassant_square() { return enpassant_square; }
    int get_castle_privelage() { return castle_privelage; }
    U64 get_piece_occupancy(int piece) { return piece_occupancies[piece]; }
    U64 get_color_occupancy(int color) { return color_occupancies[color]; }
    std::vector<int> get_moves() { return moves; }
    void parse_fen(std::string fen)
    {
        memset(piece_occupancies, 0ULL, sizeof(piece_occupancies));
        memset(color_occupancies, 0ULL, sizeof(color_occupancies));
        color = chess::WHITE;
        enpassant_square = chess::NO_SQUARE;
        castle_privelage = chess::NO_CASTLE;
        int i = 0;
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                if ((fen[i] >= 'a' && fen[i] <= 'z') || (fen[i] >= 'A' && fen[i] <= 'Z'))
                {
                    int piece = chess::ASCII_INT[fen[i]];
                    bitboard::set_bit(piece_occupancies[piece], square);
                    i++;
                }
                if (fen[i] >= '0' && fen[i] <= '9')
                {
                    int offset = fen[i] - '0';
                    int piece = -1;
                    for (int bb_piece = chess::P; bb_piece <= chess::k; bb_piece++)
                    {
                        if (bitboard::get_bit(piece_occupancies[bb_piece], square))
                            piece = bb_piece;
                    }
                    if (piece == -1)
                        file--;
                    file += offset;
                    i++;
                }
                if (fen[i] == '/')
                    i++;
            }
        }
        i++;
        color = fen[i] == 'w' ? chess::WHITE : chess::BLACK;
        i += 2;
        while (fen[i] != ' ')
        {
            switch (fen[i])
            {
            case 'K':
                castle_privelage |= chess::wk;
                break;
            case 'Q':
                castle_privelage |= chess::wq;
                break;
            case 'k':
                castle_privelage |= chess::bk;
                break;
            case 'q':
                castle_privelage |= chess::bq;
                break;
            case '-':
                castle_privelage |= chess::NO_CASTLE;
                break;
            }
            i++;
        }
        i++;
        if (fen[i] != '-')
        {
            int file = fen[i] - 'a';
            int rank = DIMENSION - (fen[i + 1] - '0');
            enpassant_square = rank * DIMENSION + file;
        }
        else
            enpassant_square = chess::NO_SQUARE;
        for (int piece = chess::P; piece <= chess::K; piece++)
            color_occupancies[chess::WHITE] |= piece_occupancies[piece];
        for (int piece = chess::p; piece <= chess::k; piece++)
            color_occupancies[chess::BLACK] |= piece_occupancies[piece];
        color_occupancies[chess::BOTH] |= color_occupancies[chess::WHITE];
        color_occupancies[chess::BOTH] |= color_occupancies[chess::BLACK];
    }
};