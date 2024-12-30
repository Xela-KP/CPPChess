#include <iostream>
#include "mask.hpp"
#include "bitboard.hpp"
#include "magic.hpp"
#include "encodings.hpp"
namespace mask
{
    U64 get_masked_occupancy(int occupied, U64 attack_mask)
    {
        U64 occupancy = 0ULL;
        int num_attacks = get_bit_count(attack_mask);
        for (int count = 0; count < num_attacks; count++)
        {
            int square = bitboard::pop_least_significant_bit(attack_mask);
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
        bitboard::set_bit(bitboard, from_square);
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
        bitboard::set_bit(bitboard, from_square);
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
        bitboard::set_bit(bitboard, from_square);
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
        occupancy *= magic::BISHOP_MAGIC_NUMBERS[square];
        occupancy >>= 64 - magic::BISHOP_ATTACK_COUNT_MASK[square];
        return bishop_attack_mask[square][occupancy];
    }

    static inline U64 get_rook_attack_mask(U64 square, U64 occupancy)
    {
        occupancy &= rook_unblocked_attack_mask[square];
        occupancy *= magic::ROOK_MAGIC_NUMBERS[square];
        occupancy >>= 64 - magic::ROOK_ATTACK_COUNT_MASK[square];
        return rook_attack_mask[square][occupancy];
    }

    void map_leap_attacks()
    {
        for (int from_square = chess::a8; from_square <= chess::h1; from_square++)
        {
            pawn_attack_mask[chess::WHITE][from_square] = get_pawn_attack_mask(chess::WHITE, from_square);
            pawn_attack_mask[chess::BLACK][from_square] = get_pawn_attack_mask(chess::BLACK, from_square);
            knight_attack_mask[from_square] = get_knight_attack_mask(from_square);
            king_attack_mask[from_square] = get_king_attack_mask(from_square);
        }
    }

    void map_slide_attacks(int bishop)
    {
        for (int from_square = chess::a8; from_square <= chess::h1; from_square++)
        {
            bishop_unblocked_attack_mask[from_square] = get_bishop_unblocked_attack_mask(from_square);
            rook_unblocked_attack_mask[from_square] = get_rook_unblocked_attack_mask(from_square);
            U64 unblocked_attack_mask = bishop ? bishop_unblocked_attack_mask[from_square] : rook_unblocked_attack_mask[from_square];
            int num_attacks = get_bit_count(unblocked_attack_mask);
            int occupancy_indicies = (1 << num_attacks);
            for (int occupancy_index = 0; occupancy_index < occupancy_indicies; occupancy_index++)
            {
                U64 masked_occupancy = get_masked_occupancy(occupancy_index, unblocked_attack_mask);
                if (bishop)
                {
                    int magic_index = (masked_occupancy * magic::BISHOP_MAGIC_NUMBERS[from_square]) >> (64 - magic::BISHOP_ATTACK_COUNT_MASK[from_square]);
                    bishop_attack_mask[from_square][magic_index] = get_bishop_blocked_attack_mask(from_square, masked_occupancy);
                }
                else
                {
                    int magic_index = (masked_occupancy * magic::ROOK_MAGIC_NUMBERS[from_square]) >> (64 - magic::ROOK_ATTACK_COUNT_MASK[from_square]);
                    rook_attack_mask[from_square][magic_index] = get_rook_blocked_attack_mask(from_square, masked_occupancy);
                }
            }
        }
    }

    void initialize_occupancies()
    {
        for (int i = chess::a2; i <= chess::h2; i++)
        {
            bitboard::set_bit(piece_occupancies[chess::P], i);
        }
        for (int i = chess::a7; i <= chess::h7; i++)
        {
            bitboard::set_bit(piece_occupancies[chess::p], i);
        }

        bitboard::set_bit(piece_occupancies[chess::N], chess::b1);
        bitboard::set_bit(piece_occupancies[chess::N], chess::g1);
        bitboard::set_bit(piece_occupancies[chess::n], chess::b8);
        bitboard::set_bit(piece_occupancies[chess::n], chess::g8);

        bitboard::set_bit(piece_occupancies[chess::R], chess::a1);
        bitboard::set_bit(piece_occupancies[chess::R], chess::h1);
        bitboard::set_bit(piece_occupancies[chess::r], chess::a8);
        bitboard::set_bit(piece_occupancies[chess::r], chess::h8);

        bitboard::set_bit(piece_occupancies[chess::B], chess::c1);
        bitboard::set_bit(piece_occupancies[chess::B], chess::f1);
        bitboard::set_bit(piece_occupancies[chess::b], chess::c8);
        bitboard::set_bit(piece_occupancies[chess::b], chess::f8);

        bitboard::set_bit(piece_occupancies[chess::K], chess::d1);
        bitboard::set_bit(piece_occupancies[chess::k], chess::d8);
        bitboard::set_bit(piece_occupancies[chess::Q], chess::e1);
        bitboard::set_bit(piece_occupancies[chess::q], chess::e8);

        for (int i = chess::P; i <= chess::K; i++)
        {
            side_occupancies[chess::WHITE] |= piece_occupancies[i];
            side_occupancies[chess::BOTH] |= piece_occupancies[i];
        }
        for (int i = chess::p; i <= chess::k; i++)
        {
            side_occupancies[chess::BLACK] |= piece_occupancies[i];
            side_occupancies[chess::BOTH] |= piece_occupancies[i];
        }
    }
}