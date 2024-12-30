
#include <iostream>
#include "mask.hpp"
#include "bitboard.hpp"
#include "magic.hpp"
#include "encodings.hpp"
namespace Mask
{
    U64 get_masked_occupancy(int occupied, U64 attack_mask)
    {
        U64 occupancy = 0ULL;
        int num_attacks = get_bit_count(attack_mask);
        for (int count = 0; count < num_attacks; count++)
        {
            int square = Bitboard::pop_least_significant_bit(attack_mask);
            if (occupied & (1 << count))
            {
                occupancy |= (1ULL << square);
            }
        }
        return occupancy;
    }

    U64 get_pawn_attack_mask(int side, int from_square)
    {
        U64 bitboard = 0ULL;
        U64 attack_mask = 0ULL;
        Bitboard::set_bit(bitboard, from_square);
        if (!side)
        {
            if (bitboard >> 7 & NOT_A_FILE)
                attack_mask |= bitboard >> 7;
            if (bitboard >> 9 & NOT_H_FILE)
                attack_mask |= bitboard >> 9;
        }
        else
        {
            if (bitboard << 9 & NOT_A_FILE)
                attack_mask |= bitboard << 9;
            if (bitboard >> 7 & NOT_H_FILE)
                attack_mask |= bitboard << 7;
        }
        return attack_mask;
    }

    U64 get_knight_attack_mask(int from_square)
    {
        U64 bitboard = 0ULL;
        U64 attack_mask = 0ULL;
        Bitboard::set_bit(bitboard, from_square);
        if (bitboard >> 6 & NOT_AB_FILE)
            attack_mask |= bitboard >> 6;
        if (bitboard << 6 & NOT_HG_FILE)
            attack_mask |= bitboard << 6;
        if (bitboard << 10 & NOT_AB_FILE)
            attack_mask |= bitboard << 10;
        if (bitboard >> 10 & NOT_HG_FILE)
            attack_mask |= bitboard >> 10;
        if (bitboard >> 15 & NOT_A_FILE)
            attack_mask |= bitboard >> 15;
        if (bitboard << 15 & NOT_H_FILE)
            attack_mask |= bitboard << 15;
        if (bitboard << 17 & NOT_A_FILE)
            attack_mask |= bitboard << 17;
        if (bitboard >> 17 & NOT_H_FILE)
            attack_mask |= bitboard >> 17;
        return attack_mask;
    }

    U64 get_king_attack_mask(int from_square)
    {
        U64 bitboard = 0ULL;
        U64 attack_mask = 0ULL;
        Bitboard::set_bit(bitboard, from_square);
        if (bitboard >> 8)
            attack_mask |= bitboard >> 8;
        if (bitboard << 8)
            attack_mask |= bitboard << 8;
        if (bitboard << 1 & NOT_A_FILE)
            attack_mask |= bitboard << 1;
        if (bitboard >> 1 & NOT_H_FILE)
            attack_mask |= bitboard >> 1;
        if (bitboard >> 7 & NOT_A_FILE)
            attack_mask |= bitboard >> 7;
        if (bitboard << 7 & NOT_H_FILE)
            attack_mask |= bitboard << 7;
        if (bitboard << 9 & NOT_A_FILE)
            attack_mask |= bitboard << 9;
        if (bitboard >> 9 & NOT_H_FILE)
            attack_mask |= bitboard >> 9;
        return attack_mask;
    }

    U64 get_bishop_unblocked_attack_mask(int from_square)
    {
        U64 attack_mask = 0ULL;
        int rank, file;
        int target_rank = from_square / DIMENSION;
        int target_file = from_square % DIMENSION;
        for (rank = target_rank + 1, file = target_file + 1;
             rank < DIMENSION - 1 && file < DIMENSION - 1;
             rank++, file++)
            attack_mask |= (1ULL << (rank * 8 + file));
        for (rank = target_rank - 1, file = target_file + 1;
             rank > 0 && file < DIMENSION - 1;
             rank--, file++)
            attack_mask |= (1ULL << (rank * 8 + file));
        for (rank = target_rank + 1, file = target_file - 1;
             rank < DIMENSION - 1 && file > 0;
             rank++, file--)
            attack_mask |= (1ULL << (rank * 8 + file));
        for (rank = target_rank - 1, file = target_file - 1;
             rank > 0 && file > 0;
             rank--, file--)
            attack_mask |= (1ULL << (rank * 8 + file));
        return attack_mask;
    }

    U64 get_bishop_blocked_attack_mask(int from_square, U64 occupancy)
    {
        U64 attack_mask = 0ULL;
        int rank, file;
        int target_rank = from_square / DIMENSION;
        int target_file = from_square % DIMENSION;

        for (rank = target_rank + 1, file = target_file + 1;
             rank < DIMENSION && file < DIMENSION;
             rank++, file++)
        {
            attack_mask |= (1ULL << (rank * 8 + file));
            if ((1ULL << (rank * 8 + file)) & occupancy)
                break;
        }
        for (rank = target_rank + 1, file = target_file - 1;
             rank < DIMENSION && file >= 0;
             rank++, file--)
        {
            attack_mask |= (1ULL << (rank * 8 + file));
            if ((1ULL << (rank * 8 + file)) & occupancy)
                break;
        }
        for (rank = target_rank - 1, file = target_file + 1;
             rank >= 0 && file < DIMENSION;
             rank--, file++)
        {
            attack_mask |= (1ULL << (rank * 8 + file));
            if ((1ULL << (rank * 8 + file)) & occupancy)
                break;
        }
        for (rank = target_rank - 1, file = target_file - 1;
             rank >= 0 && file >= 0;
             rank--, file--)
        {
            attack_mask |= (1ULL << (rank * 8 + file));
            if ((1ULL << (rank * 8 + file)) & occupancy)
                break;
        }

        return attack_mask;
    }

    U64 get_rook_unblocked_attack_mask(int from_square)
    {
        U64 attack_mask = 0ULL;
        int rank, file;
        int target_rank = from_square / DIMENSION;
        int target_file = from_square % DIMENSION;
        for (rank = target_rank + 1; rank < DIMENSION - 1; rank++)
            attack_mask |= (1ULL << (rank * 8 + target_file));
        for (rank = target_rank - 1; rank > 0; rank--)
            attack_mask |= (1ULL << (rank * 8 + target_file));
        for (file = target_file + 1; file < DIMENSION - 1; file++)
            attack_mask |= (1ULL << (target_rank * 8 + file));
        for (file = target_file - 1; file > 0; file--)
            attack_mask |= (1ULL << (target_rank * 8 + file));
        return attack_mask;
    }

    U64 get_rook_blocked_attack_mask(int from_square, U64 occupancy)
    {
        U64 attack_mask = 0ULL;
        int rank, file;
        int target_rank = from_square / DIMENSION;
        int target_file = from_square % DIMENSION;
        for (rank = target_rank + 1; rank < DIMENSION; rank++)
        {
            attack_mask |= (1ULL << (rank * 8 + target_file));
            if ((1ULL << (rank * 8 + target_file)) & occupancy)
                break;
        }
        for (rank = target_rank - 1; rank >= 0; rank--)
        {
            attack_mask |= (1ULL << (rank * 8 + target_file));
            if ((1ULL << (rank * 8 + target_file)) & occupancy)
                break;
        }
        for (file = target_file + 1; file < DIMENSION; file++)
        {
            attack_mask |= (1ULL << (target_rank * 8 + file));
            if ((1ULL << (target_rank * 8 + file)) & occupancy)
                break;
        }
        for (file = target_file - 1; file >= 0; file--)
        {
            attack_mask |= (1ULL << (target_rank * 8 + file));
            if ((1ULL << (target_rank * 8 + file)) & occupancy)
                break;
        }
        return attack_mask;
    }

    static inline U64 get_bishop_attack_mask(U64 square, U64 occupancy)
    {
        occupancy &= bishop_unblocked_attack_mask[square];
        occupancy *= Magic::BISHOP_MAGIC_NUMBERS[square];
        occupancy >>= 64 - Magic::BISHOP_ATTACK_COUNT_MASK[square];
        return bishop_attack_mask[square][occupancy];
    }

    static inline U64 get_rook_attack_mask(U64 square, U64 occupancy)
    {
        occupancy &= rook_unblocked_attack_mask[square];
        occupancy *= Magic::ROOK_MAGIC_NUMBERS[square];
        occupancy >>= 64 - Magic::ROOK_ATTACK_COUNT_MASK[square];
        return rook_attack_mask[square][occupancy];
    }

    void map_leap_attacks()
    {
        for (int from_square = ChessEncoding::a8; from_square <= ChessEncoding::h1; from_square++)
        {
            pawn_attack_mask[ChessEncoding::WHITE][from_square] = get_pawn_attack_mask(ChessEncoding::WHITE, from_square);
            pawn_attack_mask[ChessEncoding::BLACK][from_square] = get_pawn_attack_mask(ChessEncoding::BLACK, from_square);
            knight_attack_mask[from_square] = get_knight_attack_mask(from_square);
            king_attack_mask[from_square] = get_king_attack_mask(from_square);
        }
    }

    void map_slide_attacks(int bishop)
    {
        for (int from_square = ChessEncoding::a8; from_square <= ChessEncoding::h1; from_square++)
        {
            bishop_unblocked_attack_mask[from_square] = get_bishop_unblocked_attack_mask(from_square);
            rook_unblocked_attack_mask[from_square] = get_rook_unblocked_attack_mask(from_square);
            U64 attack_mask = bishop ? bishop_unblocked_attack_mask[from_square] : rook_unblocked_attack_mask[from_square];
            int num_attacks = get_bit_count(attack_mask);
            int occupancy_indicies = (1 << num_attacks);
            for (int index = 0; index < occupancy_indicies; index++)
            {
                U64 masked_occupancy = get_masked_occupancy(index, attack_mask);
                if (bishop)
                {
                    int magic_index = (masked_occupancy * Magic::BISHOP_MAGIC_NUMBERS[from_square]) >> (64 - Magic::BISHOP_ATTACK_COUNT_MASK[from_square]);
                    bishop_attack_mask[from_square][magic_index] = get_bishop_blocked_attack_mask(from_square, masked_occupancy);
                }
                else
                {
                    int magic_index = (masked_occupancy * Magic::ROOK_MAGIC_NUMBERS[from_square]) >> (64 - Magic::ROOK_ATTACK_COUNT_MASK[from_square]);
                    rook_attack_mask[from_square][magic_index] = get_rook_blocked_attack_mask(from_square, masked_occupancy);
                }
            }
        }
    }

    void initialize_occupancies()
    {
        for (int i = ChessEncoding::a2; i <= ChessEncoding::h2; i++)
        {
            Bitboard::set_bit(piece_occupancies[ChessEncoding::P], i);
        }
        for (int i = ChessEncoding::a7; i <= ChessEncoding::h7; i++)
        {
            Bitboard::set_bit(piece_occupancies[ChessEncoding::p], i);
        }

        Bitboard::set_bit(piece_occupancies[ChessEncoding::N], ChessEncoding::b1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::N], ChessEncoding::g1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::n], ChessEncoding::b8);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::n], ChessEncoding::g8);

        Bitboard::set_bit(piece_occupancies[ChessEncoding::R], ChessEncoding::a1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::R], ChessEncoding::h1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::r], ChessEncoding::a8);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::r], ChessEncoding::h8);

        Bitboard::set_bit(piece_occupancies[ChessEncoding::B], ChessEncoding::c1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::B], ChessEncoding::f1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::b], ChessEncoding::c8);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::b], ChessEncoding::f8);

        Bitboard::set_bit(piece_occupancies[ChessEncoding::K], ChessEncoding::d1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::k], ChessEncoding::d8);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::Q], ChessEncoding::e1);
        Bitboard::set_bit(piece_occupancies[ChessEncoding::q], ChessEncoding::e8);

        for (int i = ChessEncoding::P; i <= ChessEncoding::K; i++)
        {
            side_occupancies[ChessEncoding::WHITE] |= piece_occupancies[i];
            side_occupancies[ChessEncoding::BOTH] |= piece_occupancies[i];
        }
        for (int i = ChessEncoding::p; i <= ChessEncoding::k; i++)
        {
            side_occupancies[ChessEncoding::BLACK] |= piece_occupancies[i];
            side_occupancies[ChessEncoding::BOTH] |= piece_occupancies[i];
        }
    }
}