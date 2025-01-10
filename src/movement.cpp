#include "../include/movement.hpp"
#include "../include/mask.hpp"
int MovementUtils::isAttacked(Board board, int square, int color)
{
    Bitboard pawn_attack_mask = AttackMaskUtils::getPawnAttackMask(!color, square);
    Bitboard knight_attack_mask = AttackMaskUtils::getKnightAttackMask(square);
    Bitboard king_attack_mask = AttackMaskUtils::getKingAttackMask(square);
    Bitboard bishop_attack_mask = AttackMaskUtils::getBishopAttackMask(square, board.getColorOccupancy(ChessEncoding::BOTH));
    Bitboard rook_attack_mask = AttackMaskUtils::getRookAttackMask(square, board.getColorOccupancy(ChessEncoding::BOTH));
    Bitboard queen_attack_mask = AttackMaskUtils::getQueenAttackMask(square, board.getColorOccupancy(ChessEncoding::BOTH));
    if (pawn_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::p : ChessEncoding::P))
        return 1;
    if (knight_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::n : ChessEncoding::N))
        return 1;
    if (king_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::k : ChessEncoding::K))
        return 1;
    if (bishop_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::b : ChessEncoding::B))
        return 1;
    if (rook_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::r : ChessEncoding::R))
        return 1;
    if (queen_attack_mask &
        board.getPieceOccupancy(color ? ChessEncoding::q : ChessEncoding::Q))
        return 1;
    return 0;
}
void MovementUtils::mapPawnMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::p : ChessEncoding::P;
    Bitboard pawn_occupancy = board.getPieceOccupancy(piece);
    Bitboard current_occupancy = board.getColorOccupancy(ChessEncoding::BOTH);
    int direction = color ? 1 : -1;
    while (pawn_occupancy)
    {
        int source_square = BitboardUtils::popLSB(pawn_occupancy);
        int target_square = source_square + 8 * direction;
        int double_push_target_square = target_square + 8 * direction;
        Bitboard pawn_attack_mask = AttackMaskUtils::getPawnAttackMask(color, source_square) & board.getColorOccupancy(!color);
        if (!BitboardUtils::getBit(current_occupancy, target_square))
        {
            if ((color && source_square >= ChessEncoding::a7 && source_square <= ChessEncoding::h7 ||
                 !color && source_square >= ChessEncoding::a2 && source_square <= ChessEncoding::h2) &&
                !(BitboardUtils::getBit(current_occupancy, double_push_target_square)))
                board.pushMove(encodeMove(source_square, double_push_target_square, piece, 0, 0, 1, 0, 0));
            if ((color && (source_square >= ChessEncoding::a2 && source_square <= ChessEncoding::h2)) ||
                (!color && (source_square >= ChessEncoding::a8 && source_square <= ChessEncoding::h8)))
            {
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::Q, 0, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::R, 0, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::B, 0, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::N, 0, 0, 0, 0));
            }
            board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
        }
        while (pawn_attack_mask)
        {
            target_square = BitboardUtils::popLSB(pawn_attack_mask);
            if ((color && (source_square >= ChessEncoding::a2 && source_square <= ChessEncoding::h2)) ||
                (!color && (source_square >= ChessEncoding::a8 && source_square <= ChessEncoding::h8)))
            {
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::Q, 1, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::R, 1, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::B, 1, 0, 0, 0));
                board.pushMove(encodeMove(source_square, target_square, piece, ChessEncoding::N, 1, 0, 0, 0));
            }
            else
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
        if (!board.getEnpassantSquare())
            continue;
        Bitboard enpassant_attack_mask = AttackMaskUtils::getPawnAttackMask(color, source_square) & (1ULL << board.getEnpassantSquare());
        if (enpassant_attack_mask)
        {
            target_square = BitboardUtils::getLSB(enpassant_attack_mask);
            board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 1, 0));
        }
    }
}
void MovementUtils::mapKingMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::k : ChessEncoding::K;
    Bitboard king_occupancy = board.getPieceOccupancy(piece);
    int source_square = BitboardUtils::popLSB(king_occupancy);
    if (board.getCastlePrivelage() & ChessEncoding::wk ||
        board.getCastlePrivelage() & ChessEncoding::bk &&
            !isAttacked(board, source_square, color))
    {
        if (!BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), source_square + 1) &&
            !BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), source_square + 2) &&
            !isAttacked(board, source_square + 1, !color) &&
            !isAttacked(board, source_square + 2, !color))
            board.pushMove(encodeMove(source_square, source_square + 2, piece, 0, 0, 0, 0, 1));
        if (!BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), source_square - 1) &&
            !BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), source_square - 2) &&
            !BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), source_square - 3) &&
            !isAttacked(board, source_square - 1, !color) &&
            !isAttacked(board, source_square - 2, !color))
            board.pushMove(encodeMove(source_square, source_square - 2, piece, 0, 0, 0, 0, 1));
    }
    Bitboard king_attack_mask = AttackMaskUtils::getKingAttackMask(source_square);
    while (king_attack_mask)
    {
        int target_square = BitboardUtils::popLSB(king_attack_mask);
        if (!BitboardUtils::getBit(board.getColorOccupancy(color), target_square) &&
            !isAttacked(board, target_square, !color))
            board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
    }
}
void MovementUtils::mapKnightMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::n : ChessEncoding::N;
    Bitboard knight_occupancy = board.getPieceOccupancy(piece);
    while (knight_occupancy)
    {
        int source_square = BitboardUtils::popLSB(knight_occupancy);
        Bitboard knight_attack_mask = AttackMaskUtils::getKnightAttackMask(source_square);
        while (knight_attack_mask)
        {
            int target_square = BitboardUtils::popLSB(knight_attack_mask);
            if (!BitboardUtils::getBit(board.getColorOccupancy(ChessEncoding::BOTH), target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (BitboardUtils::getBit(board.getColorOccupancy(!color), target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void MovementUtils::mapBishopMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::b : ChessEncoding::B;
    Bitboard bishop_occupancy = board.getPieceOccupancy(piece);
    Bitboard current_occupancy = board.getColorOccupancy(ChessEncoding::BOTH);
    while (bishop_occupancy)
    {
        int source_square = BitboardUtils::popLSB(bishop_occupancy);
        Bitboard bishop_attack_mask = AttackMaskUtils::getBishopAttackMask(source_square, current_occupancy);
        while (bishop_attack_mask)
        {
            int target_square = BitboardUtils::popLSB(bishop_attack_mask);
            if (!BitboardUtils::getBit(current_occupancy, target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (BitboardUtils::getBit(board.getColorOccupancy(!color), target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void MovementUtils::mapRookMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::r : ChessEncoding::R;
    Bitboard rook_occupancy = board.getPieceOccupancy(piece);
    Bitboard current_occupancy = board.getColorOccupancy(ChessEncoding::BOTH);
    while (rook_occupancy)
    {
        int source_square = BitboardUtils::popLSB(rook_occupancy);
        Bitboard rook_attack_mask = AttackMaskUtils::getRookAttackMask(source_square, current_occupancy);
        while (rook_attack_mask)
        {
            int target_square = BitboardUtils::popLSB(rook_attack_mask);
            if (!BitboardUtils::getBit(current_occupancy, target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (BitboardUtils::getBit(board.getColorOccupancy(!color), target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void MovementUtils::mapQueenMoves(Board &board, int color)
{
    int piece = color ? ChessEncoding::q : ChessEncoding::Q;
    Bitboard queen_occupancy = board.getPieceOccupancy(piece);
    Bitboard current_occupancy = board.getColorOccupancy(ChessEncoding::BOTH);
    while (queen_occupancy)
    {
        int source_square = BitboardUtils::popLSB(queen_occupancy);
        Bitboard queen_attack_mask = AttackMaskUtils::getQueenAttackMask(source_square, current_occupancy);
        while (queen_attack_mask)
        {
            int target_square = BitboardUtils::popLSB(queen_attack_mask);
            if (!BitboardUtils::getBit(current_occupancy, target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (BitboardUtils::getBit(board.getColorOccupancy(!color), target_square))
                board.pushMove(encodeMove(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void MovementUtils::mapMoves(Board &board, int color)
{
    board.clearMoves();
    mapPawnMoves(board, color);
    mapKingMoves(board, color);
    mapKnightMoves(board, color);
    mapBishopMoves(board, color);
    mapRookMoves(board, color);
    mapQueenMoves(board, color);
}

/*
          binary move bits                               hexidecimal constants
    0000 0000 0000 0000 0011 1111    source square       0x3f
    0000 0000 0000 1111 1100 0000    target square       0xfc0
    0000 0000 1111 0000 0000 0000    piece               0xf000
    0000 1111 0000 0000 0000 0000    promoted piece      0xf0000
    0001 0000 0000 0000 0000 0000    capture flag        0x100000
    0010 0000 0000 0000 0000 0000    double push flag    0x200000
    0100 0000 0000 0000 0000 0000    enpassant flag      0x400000
    1000 0000 0000 0000 0000 0000    castling flag       0x800000
*/