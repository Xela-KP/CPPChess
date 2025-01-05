
#include "../include/movement.hpp"
#include "../include/types.hpp"
#include "../include/encodings.hpp"
#include "../include/mask.hpp"
#include "../include/bitboard.hpp"

int movement::get_num_attackers_on(GameState gamestate, int square, int color)
{
    int num_attackers = 0;
    num_attackers +=
        (MaskUtils::get_pawn_attack_mask(!color, square) &
         gamestate.get_piece_occupancy(color ? chess::p : chess::P))
            ? 1
            : 0;
    num_attackers +=
        (MaskUtils::get_knight_attack_mask(square) &
         gamestate.get_piece_occupancy(color ? chess::n : chess::N))
            ? 1
            : 0;
    num_attackers +=
        (MaskUtils::get_king_attack_mask(square) &
         gamestate.get_piece_occupancy(color ? chess::k : chess::K))
            ? 1
            : 0;
    num_attackers +=
        (MaskUtils::get_bishop_attack_mask(square, gamestate.get_color_occupancy(chess::BOTH)) &
         gamestate.get_piece_occupancy(color ? chess::b : chess::B))
            ? 1
            : 0;
    num_attackers +=
        (MaskUtils::get_rook_attack_mask(square, gamestate.get_color_occupancy(chess::BOTH)) &
         gamestate.get_piece_occupancy(color ? chess::r : chess::R))
            ? 1
            : 0;
    num_attackers +=
        (MaskUtils::get_queen_attack_mask(square, gamestate.get_color_occupancy(chess::BOTH)) &
         gamestate.get_piece_occupancy(color ? chess::q : chess::Q))
            ? 1
            : 0;
    return num_attackers;
}
void movement::get_pawn_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::p : chess::P;
    U64 pawn_occupancy = gamestate.get_piece_occupancy(piece);
    U64 current_occupancy = gamestate.get_color_occupancy(chess::BOTH);
    int direction = color ? 1 : -1;
    while (pawn_occupancy)
    {
        int source_square = bitboard::pop_least_significant_bit(pawn_occupancy);
        int target_square = source_square + 8 * direction;
        int double_push_target_square = target_square + 8 * direction;
        U64 pawn_attack_mask = MaskUtils::get_pawn_attack_mask(color, source_square) & gamestate.get_color_occupancy(!color);
        if (!bitboard::get_bit(current_occupancy, target_square))
        {
            if ((color && source_square >= chess::a7 && source_square <= chess::h7 ||
                 !color && source_square >= chess::a2 && source_square <= chess::h2) &&
                !(bitboard::get_bit(current_occupancy, double_push_target_square)))
                gamestate.push_move(encode_move(source_square, double_push_target_square, piece, 0, 0, 1, 0, 0));
            if ((color && (source_square >= chess::a2 && source_square <= chess::h2)) ||
                (!color && (source_square >= chess::a8 && source_square <= chess::h8)))
            {
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::Q, 0, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::R, 0, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::B, 0, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::N, 0, 0, 0, 0));
            }
            gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
        }
        while (pawn_attack_mask)
        {
            target_square = bitboard::pop_least_significant_bit(pawn_attack_mask);
            if ((color && (source_square >= chess::a2 && source_square <= chess::h2)) ||
                (!color && (source_square >= chess::a8 && source_square <= chess::h8)))
            {
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::Q, 1, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::R, 1, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::B, 1, 0, 0, 0));
                gamestate.push_move(encode_move(source_square, target_square, piece, chess::N, 1, 0, 0, 0));
            }
            else
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
        if (!gamestate.get_enpassant_square())
            continue;
        U64 enpassant_attack_mask = MaskUtils::get_pawn_attack_mask(color, source_square) & (1ULL << gamestate.get_enpassant_square());
        if (enpassant_attack_mask)
        {
            target_square = get_least_significant_bit(enpassant_attack_mask);
            gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 1, 0));
        }
    }
}
void movement::get_king_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::k : chess::K;
    U64 king_occupancy = gamestate.get_piece_occupancy(piece);
    int source_square = bitboard::pop_least_significant_bit(king_occupancy);
    if (gamestate.get_castle_privelage() & chess::wk ||
        gamestate.get_castle_privelage() & chess::bk &&
            !get_num_attackers_on(gamestate, source_square, color))
    {
        if (!bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), source_square + 1) &&
            !bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), source_square + 2) &&
            !get_num_attackers_on(gamestate, source_square + 1, !color) &&
            !get_num_attackers_on(gamestate, source_square + 2, !color))
            gamestate.push_move(encode_move(source_square, source_square + 2, piece, 0, 0, 0, 0, 1));
        if (!bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), source_square - 1) &&
            !bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), source_square - 2) &&
            !bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), source_square - 3) &&
            !get_num_attackers_on(gamestate, source_square - 1, !color) &&
            !get_num_attackers_on(gamestate, source_square - 2, !color))
            gamestate.push_move(encode_move(source_square, source_square - 2, piece, 0, 0, 0, 0, 1));
    }
    U64 king_attack_mask = MaskUtils::get_king_attack_mask(source_square);
    while (king_attack_mask)
    {
        int target_square = bitboard::pop_least_significant_bit(king_attack_mask);
        if (!bitboard::get_bit(gamestate.get_color_occupancy(color), target_square) &&
            !get_num_attackers_on(gamestate, target_square, !color))
            gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
    }
}
void movement::get_knight_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::n : chess::N;
    U64 knight_occupancy = gamestate.get_piece_occupancy(piece);
    while (knight_occupancy)
    {
        int source_square = bitboard::pop_least_significant_bit(knight_occupancy);
        U64 knight_attack_mask = MaskUtils::get_knight_attack_mask(source_square);
        while (knight_attack_mask)
        {
            int target_square = bitboard::pop_least_significant_bit(knight_attack_mask);
            if (!bitboard::get_bit(gamestate.get_color_occupancy(chess::BOTH), target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (bitboard::get_bit(gamestate.get_color_occupancy(!color), target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void movement::get_bishop_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::b : chess::B;
    U64 bishop_occupancy = gamestate.get_piece_occupancy(piece);
    U64 current_occupancy = gamestate.get_color_occupancy(chess::BOTH);
    while (bishop_occupancy)
    {
        int source_square = bitboard::pop_least_significant_bit(bishop_occupancy);
        U64 bishop_attack_mask = MaskUtils::get_bishop_attack_mask(source_square, current_occupancy);
        while (bishop_attack_mask)
        {
            int target_square = bitboard::pop_least_significant_bit(bishop_attack_mask);
            if (!bitboard::get_bit(current_occupancy, target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (bitboard::get_bit(gamestate.get_color_occupancy(!color), target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void movement::get_rook_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::r : chess::R;
    U64 rook_occupancy = gamestate.get_piece_occupancy(piece);
    U64 current_occupancy = gamestate.get_color_occupancy(chess::BOTH);
    while (rook_occupancy)
    {
        int source_square = bitboard::pop_least_significant_bit(rook_occupancy);
        U64 rook_attack_mask = MaskUtils::get_rook_attack_mask(source_square, current_occupancy);
        while (rook_attack_mask)
        {
            int target_square = bitboard::pop_least_significant_bit(rook_attack_mask);
            if (!bitboard::get_bit(current_occupancy, target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (bitboard::get_bit(gamestate.get_color_occupancy(!color), target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void movement::get_queen_moves(GameState &gamestate, int color)
{
    int piece = color ? chess::q : chess::Q;
    U64 queen_occupancy = gamestate.get_piece_occupancy(piece);
    U64 current_occupancy = gamestate.get_color_occupancy(chess::BOTH);
    while (queen_occupancy)
    {
        int source_square = bitboard::pop_least_significant_bit(queen_occupancy);
        U64 queen_attack_mask = MaskUtils::get_queen_attack_mask(source_square, current_occupancy);
        while (queen_attack_mask)
        {
            int target_square = bitboard::pop_least_significant_bit(queen_attack_mask);
            if (!bitboard::get_bit(current_occupancy, target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
            if (bitboard::get_bit(gamestate.get_color_occupancy(!color), target_square))
                gamestate.push_move(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
        }
    }
}
void movement::get_moves(GameState &gamestate, int color)
{
    gamestate.clear_moves();
    get_pawn_moves(gamestate, color);
    get_king_moves(gamestate, color);
    get_knight_moves(gamestate, color);
    get_bishop_moves(gamestate, color);
    get_rook_moves(gamestate, color);
    get_queen_moves(gamestate, color);
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