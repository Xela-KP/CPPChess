#include "fen.hpp"
#include "mask.hpp"
#include "encodings.hpp"
#include "bitboard.hpp"
#include "state.hpp"
namespace fen
{
    void parse_fen(std::string fen)
    {
        memset(state::piece_occupancies, 0ULL, sizeof(state::piece_occupancies));
        memset(state::side_occupancies, 0ULL, sizeof(state::side_occupancies));
        state::side = chess::WHITE;
        state::enpassant = chess::NO_SQUARE;
        state::castle = chess::NO_CASTLE;
        int i = 0;
        for (int rank = 0; rank < DIMENSION; rank++)
        {
            for (int file = 0; file < DIMENSION; file++)
            {
                int square = rank * DIMENSION + file;
                if ((fen[i] >= 'a' && fen[i] <= 'z') || (fen[i] >= 'A' && fen[i] <= 'Z'))
                {
                    int piece = chess::ASCII_INT[fen[i]];
                    bitboard::set_bit(state::piece_occupancies[piece], square);
                    i++;
                }
                if (fen[i] >= '0' && fen[i] <= '9')
                {
                    int offset = fen[i] - '0';
                    int piece = -1;
                    for (int bb_piece = chess::P; bb_piece <= chess::k; bb_piece++)
                    {
                        if (bitboard::get_bit(state::piece_occupancies[bb_piece], square))
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
        state::side = fen[i] == 'w' ? chess::WHITE : chess::BLACK;
        i += 2;
        while (fen[i] != ' ')
        {
            switch (fen[i])
            {
            case 'K':
                state::castle |= chess::wk;
                break;
            case 'Q':
                state::castle |= chess::wq;
                break;
            case 'k':
                state::castle |= chess::bk;
                break;
            case 'q':
                state::castle |= chess::bq;
                break;
            case '-':
                state::castle |= chess::NO_CASTLE;
                break;
            }
            i++;
        }
        i++;
        if (fen[i] != '-')
        {
            int file = fen[i] - 'a';
            int rank = DIMENSION - (fen[i + 1] - '0');
            state::enpassant = rank * DIMENSION + file;
        }
        else
            state::enpassant = chess::NO_SQUARE;
        for (int piece = chess::P; piece <= chess::K; piece++)
            state::side_occupancies[chess::WHITE] |= state::piece_occupancies[piece];
        for (int piece = chess::p; piece <= chess::k; piece++)
            state::side_occupancies[chess::BLACK] |= state::piece_occupancies[piece];
        state::side_occupancies[chess::BOTH] |= state::side_occupancies[chess::WHITE];
        state::side_occupancies[chess::BOTH] |= state::side_occupancies[chess::BLACK];
    }
}