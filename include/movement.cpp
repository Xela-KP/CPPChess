
#include "state.hpp"
#include "encodings.hpp"
#include "mask.hpp"
#include "bitboard.hpp"
namespace movement
{
    int get_num_attackers_on(int square, int color)
    {
        int num_attackers = 0;
        num_attackers +=
            (state::pawn_attack_mask[!color][square] &
             state::piece_occupancies[color ? chess::p : chess::P])
                ? 1
                : 0;
        num_attackers +=
            (state::knight_attack_mask[square] &
             state::piece_occupancies[color ? chess::n : chess::N])
                ? 1
                : 0;
        num_attackers +=
            (state::king_attack_mask[square] &
             state::piece_occupancies[color ? chess::k : chess::K])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_bishop_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::b : chess::B])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_rook_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::r : chess::R])
                ? 1
                : 0;
        num_attackers +=
            (mask::get_queen_attack_mask(square, state::side_occupancies[chess::BOTH]) &
             state::piece_occupancies[color ? chess::q : chess::Q])
                ? 1
                : 0;
        return num_attackers;
    }

    static inline int encode_move(int source_square, int target_square, int piece,
                                  int promotion_piece, int is_capture,
                                  int is_double_pawn_push, int is_enpassant, int is_castle)
    {
        return (source_square |
                target_square << 6 |
                piece << 12 |
                promotion_piece << 16 |
                is_capture << 20 |
                is_double_pawn_push << 21 |
                is_enpassant << 22 |
                is_castle << 23);
    };

    static inline int decode_source_square(int move) { return move & 0x3f; }
    static inline int decode_target_square(int move) { return (move & 0xfc0) >> 6; }
    static inline int decode_piece(int move) { return (move & 0xf000) >> 12; }
    static inline int decode_promotion_piece(int move) { return (move & 0xf0000) >> 16; }
    static inline int decode_capture_flag(int move) { return move & 0x100000; }
    static inline int decode_double_pawn_push_flag(int move) { return move & 0x200000; }
    static inline int decode_enpassant_flag(int move) { return move & 0x400000; }
    static inline int decode_castle_flag(int move) { return move & 0x800000; }

    void get_pawn_moves(int color)
    {
        int piece = color ? chess::p : chess::P;
        U64 pawn_occupancy = state::piece_occupancies[piece];
        U64 current_occupancy = state::side_occupancies[chess::BOTH];
        int direction = color ? 1 : -1;
        while (pawn_occupancy)
        {
            int source_square = bitboard::pop_least_significant_bit(pawn_occupancy);
            int target_square = source_square + 8 * direction;
            int double_push_target_square = target_square + 8 * direction;
            U64 pawn_attack_mask = state::pawn_attack_mask[color][source_square] & state::side_occupancies[!color];
            if (!bitboard::get_bit(current_occupancy, target_square))
            {
                if ((color && source_square >= chess::a7 && source_square <= chess::h7 ||
                     !color && source_square >= chess::a2 && source_square <= chess::h2) &&
                    !(bitboard::get_bit(current_occupancy, double_push_target_square)))
                    state::moves.push_back(encode_move(source_square, double_push_target_square, piece, 0, 0, 1, 0, 0));
                if ((color && (source_square >= chess::a2 && source_square <= chess::h2)) ||
                    (!color && (source_square >= chess::a8 && source_square <= chess::h8)))
                {
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::Q, 0, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::R, 0, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::B, 0, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::N, 0, 0, 0, 0));
                }
                state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
            }
            while (pawn_attack_mask)
            {
                target_square = bitboard::pop_least_significant_bit(pawn_attack_mask);
                if ((color && (source_square >= chess::a2 && source_square <= chess::h2)) ||
                    (!color && (source_square >= chess::a8 && source_square <= chess::h8)))
                {
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::Q, 1, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::R, 1, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::B, 1, 0, 0, 0));
                    state::moves.push_back(encode_move(source_square, target_square, piece, chess::N, 1, 0, 0, 0));
                }
                else
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
            }
            if (!state::enpassant_square)
                continue;
            U64 enpassant_attack_mask = state::pawn_attack_mask[color][source_square] & (1ULL << state::enpassant_square);
            if (enpassant_attack_mask)
            {
                target_square = get_least_significant_bit(enpassant_attack_mask);
                state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 1, 0));
            }
        }
    }

    void get_king_moves(int color)
    {
        int piece = color ? chess::k : chess::K;
        U64 king_occupancy = state::piece_occupancies[piece];
        int source_square = bitboard::pop_least_significant_bit(king_occupancy);
        if (state::castle_privelage & chess::wk ||
            state::castle_privelage & chess::bk &&
                !get_num_attackers_on(source_square, color))
        {
            if (!bitboard::get_bit(state::side_occupancies[chess::BOTH], source_square + 1) &&
                !bitboard::get_bit(state::side_occupancies[chess::BOTH], source_square + 2) &&
                !get_num_attackers_on(source_square + 1, !color) &&
                !get_num_attackers_on(source_square + 2, !color))
                state::moves.push_back(encode_move(source_square, source_square + 2, piece, 0, 0, 0, 0, 1));
            if (!bitboard::get_bit(state::side_occupancies[chess::BOTH], source_square - 1) &&
                !bitboard::get_bit(state::side_occupancies[chess::BOTH], source_square - 2) &&
                !bitboard::get_bit(state::side_occupancies[chess::BOTH], source_square - 3) &&
                !get_num_attackers_on(source_square - 1, !color) &&
                !get_num_attackers_on(source_square - 2, !color))
                state::moves.push_back(encode_move(source_square, source_square - 2, piece, 0, 0, 0, 0, 1));
        }
        U64 king_attack_mask = state::king_attack_mask[source_square];
        while (king_attack_mask)
        {
            int target_square = bitboard::pop_least_significant_bit(king_attack_mask);
            if (!bitboard::get_bit(state::side_occupancies[color], target_square) &&
                !get_num_attackers_on(target_square, !color))
                state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
        }
    }

    void get_knight_moves(int color)
    {
        int piece = color ? chess::n : chess::N;
        U64 knight_occupancy = state::piece_occupancies[piece];
        while (knight_occupancy)
        {
            int source_square = bitboard::pop_least_significant_bit(knight_occupancy);
            U64 knight_attack_mask = state::knight_attack_mask[source_square];
            while (knight_attack_mask)
            {
                int target_square = bitboard::pop_least_significant_bit(knight_attack_mask);
                if (!bitboard::get_bit(state::side_occupancies[chess::BOTH], target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                if (bitboard::get_bit(state::side_occupancies[!color], target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
            }
        }
    }

    void get_bishop_moves(int color)
    {
        int piece = color ? chess::b : chess::B;
        U64 bishop_occupancy = state::piece_occupancies[piece];
        U64 current_occupancy = state::side_occupancies[chess::BOTH];
        while (bishop_occupancy)
        {
            int source_square = bitboard::pop_least_significant_bit(bishop_occupancy);
            U64 bishop_attack_mask = state::bishop_attack_mask[source_square][current_occupancy];
            while (bishop_attack_mask)
            {
                int target_square = bitboard::pop_least_significant_bit(bishop_attack_mask);
                if (!bitboard::get_bit(current_occupancy, target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                if (bitboard::get_bit(state::side_occupancies[!color], target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
            }
        }
    }

    void get_rook_moves(int color)
    {
        int piece = color ? chess::r : chess::R;
        U64 rook_occupancy = state::piece_occupancies[piece];
        U64 current_occupancy = state::side_occupancies[chess::BOTH];
        while (rook_occupancy)
        {
            int source_square = bitboard::pop_least_significant_bit(rook_occupancy);
            U64 rook_attack_mask = state::rook_attack_mask[source_square][current_occupancy];
            while (rook_attack_mask)
            {
                int target_square = bitboard::pop_least_significant_bit(rook_attack_mask);
                if (!bitboard::get_bit(current_occupancy, target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                if (bitboard::get_bit(state::side_occupancies[!color], target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
            }
        }
    }

    void get_queen_moves(int color)
    {
        int piece = color ? chess::q : chess::Q;
        U64 queen_occupancy = state::piece_occupancies[piece];
        U64 current_occupancy = state::side_occupancies[chess::BOTH];
        while (queen_occupancy)
        {
            int source_square = bitboard::pop_least_significant_bit(queen_occupancy);
            U64 queen_attack_mask = state::queen_attack_mask[source_square][current_occupancy];
            while (queen_attack_mask)
            {
                int target_square = bitboard::pop_least_significant_bit(queen_attack_mask);
                if (!bitboard::get_bit(current_occupancy, target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                if (bitboard::get_bit(state::side_occupancies[!color], target_square))
                    state::moves.push_back(encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0, 0));
            }
        }
    }

    void get_moves(int color)
    {
        state::moves.clear();
        U64 piece_occupancy;
        get_pawn_moves(color);
        get_king_moves(color);
        get_knight_moves(color);
        get_bishop_moves(color);
        get_rook_moves(color);
        get_queen_moves(color);
    }
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