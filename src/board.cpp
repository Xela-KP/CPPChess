#include <algorithm>
#include "../include/board.hpp"
#include "../include/moveutils.hpp"
Board::Board(std::string fen)
{
    enpassant_square = ChessEncoding::NO_SQUARE;
    castle_privelage = ChessEncoding::NO_CASTLE;
    sideToMove = 0;
    parseFEN(fen);
}
Board Board::copy() { return *this; };
Bitboard Board::getPieceOccupancy(int piece) { return piece_occupancies[piece]; }
Bitboard Board::getColorOccupancy(int color) { return color_occupancies[color]; }
int Board::getSideToMove() { return sideToMove; }
int Board::getEnpassantSquare() { return enpassant_square; }
int Board::getCastlePrivelage() { return castle_privelage; }
void Board::parseFEN(std::string fen)
{
    std::fill(std::begin(piece_occupancies), std::end(piece_occupancies), 0ULL);
    std::fill(std::begin(color_occupancies), std::end(color_occupancies), 0ULL);
    sideToMove = ChessEncoding::WHITE;
    enpassant_square = ChessEncoding::NO_SQUARE;
    castle_privelage = ChessEncoding::NO_CASTLE;
    int i = 0;
    for (int rank = 0; rank < DIMENSION; rank++)
    {
        for (int file = 0; file < DIMENSION; file++)
        {
            int square = rank * DIMENSION + file;
            if ((fen[i] >= 'a' && fen[i] <= 'z') || (fen[i] >= 'A' && fen[i] <= 'Z'))
            {
                int piece = ChessEncoding::ASCII_INT[fen[i]];
                BitboardUtils::setBit(piece_occupancies[piece], square);
                i++;
            }
            if (fen[i] >= '0' && fen[i] <= '9')
            {
                int offset = fen[i] - '0';
                int piece = -1;
                for (int bb_piece = ChessEncoding::P; bb_piece <= ChessEncoding::k; bb_piece++)
                {
                    if (BitboardUtils::getBit(piece_occupancies[bb_piece], square))
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
    sideToMove = fen[i] == 'w' ? ChessEncoding::WHITE : ChessEncoding::BLACK;
    i += 2;
    while (fen[i] != ' ')
    {
        switch (fen[i])
        {
        case 'K':
            castle_privelage |= ChessEncoding::wk;
            break;
        case 'Q':
            castle_privelage |= ChessEncoding::wq;
            break;
        case 'k':
            castle_privelage |= ChessEncoding::bk;
            break;
        case 'q':
            castle_privelage |= ChessEncoding::bq;
            break;
        case '-':
            castle_privelage |= ChessEncoding::NO_CASTLE;
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
        enpassant_square = ChessEncoding::NO_SQUARE;
    for (int piece = ChessEncoding::P; piece <= ChessEncoding::K; piece++)
        color_occupancies[ChessEncoding::WHITE] |= piece_occupancies[piece];
    for (int piece = ChessEncoding::p; piece <= ChessEncoding::k; piece++)
        color_occupancies[ChessEncoding::BLACK] |= piece_occupancies[piece];
    color_occupancies[ChessEncoding::BOTH] |= color_occupancies[ChessEncoding::WHITE];
    color_occupancies[ChessEncoding::BOTH] |= color_occupancies[ChessEncoding::BLACK];
}
void Board::makeMove(int move, int color)
{
    int source_square = MoveUtils::decodeSourceSquare(move);
    int target_square = MoveUtils::decodeTargetSquare(move);
    int piece = MoveUtils::decodePiece(move);
    int promotion_piece = MoveUtils::decodePromotionPiece(move);
    int is_capture = MoveUtils::decodeCaptureFlag(move);
    int is_double_pawn_push = MoveUtils::decodeDoublePawnPushFlag(move);
    int is_castle = MoveUtils::decodeCastleFlag(move);
    int is_enpassant = MoveUtils::decodeEnpassantFlag(move);

    if (is_capture)
    {

        BitboardUtils::clearBit(color_occupancies[color], source_square);
        BitboardUtils::clearBit(piece_occupancies[piece], source_square);
        BitboardUtils::setBit(color_occupancies[color], target_square);
        BitboardUtils::setBit(piece_occupancies[piece], target_square);
        int captured_piece = color ? ChessEncoding::P : ChessEncoding::p;
        if (is_enpassant && enpassant_square != ChessEncoding::NO_SQUARE)
        {
            /*
                I don't know if redundancy exists:
                In case of enpassant: target_square === enpassant_square.
                Also: enpassant_square is not the square holding the captured pawn, it's the capturing_pawns intended destination.
            */
            BitboardUtils::clearBit(piece_occupancies[captured_piece], color ? enpassant_square - 8 : enpassant_square + 8);
            BitboardUtils::clearBit(color_occupancies[!color], color ? enpassant_square - 8 : enpassant_square + 8);
        }
        else
        {
            int last_piece = captured_piece + 6;
            while (captured_piece < last_piece)
            {
                BitboardUtils::clearBit(piece_occupancies[captured_piece], target_square);
                captured_piece++;
            }
            BitboardUtils::clearBit(color_occupancies[!color], target_square);
        }
    }
}