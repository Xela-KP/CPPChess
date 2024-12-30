#include "fen.hpp"
#include "mask.hpp"
#include "encodings.hpp"
#include "state.hpp"
namespace fen
{
    void parse_fen(std::string fen)
    {
        memset(mask::piece_occupancies, 0ULL, sizeof(mask::piece_occupancies));
        memset(mask::side_occupancies, 0ULL, sizeof(mask::side_occupancies));
        state::side = 0;
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
                    bitboard::set_bit(mask::piece_occupancies[piece], square);
                    i++;
                }
                if (fen[i] >= '0' && fen[i] <= '9')
                {
                    int offset = fen[i] - '0';
                    int piece = -1;
                    for (int bb_piece = chess::P; bb_piece <= chess::k; bb_piece++)
                    {
                        if (bitboard::get_bit(mask::piece_occupancies[bb_piece], square))
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
        (fen[i] == 'w') ? (state::side = chess::BLACK) : (state::side = chess::BLACK);
        fen += 2;
        while (fen[i] != ' ')
        {
            switch (fen[i])
            {
            case 'K':
                state::castle |= chess::KK;
                break;
            case 'Q':
                state::castle |= chess::KQ;
                break;
            case 'k':
                state::castle |= chess::kk;
                break;
            case 'q':
                state::castle |= chess::kq;
                break;
            case '-':
                break;
            }
            i++;
        }
        i++;
        if (fen[i] != '-')
        {
            int file = fen[0] - 'a';
            int rank = 8 - (fen[1] - '0');
            state::enpassant = rank * 8 + file;
        }
        else
            state::enpassant = chess::NO_SQUARE;
        for (int piece = chess::P; piece <= chess::K; piece++)
            mask::side_occupancies[chess::WHITE] |= mask::piece_occupancies[piece];
        for (int piece = chess::p; piece <= chess::k; piece++)
            mask::side_occupancies[chess::BLACK] |= mask::piece_occupancies[piece];
        mask::side_occupancies[chess::BOTH] |= mask::side_occupancies[chess::WHITE];
        mask::side_occupancies[chess::BOTH] |= mask::side_occupancies[chess::WHITE];
    }
}