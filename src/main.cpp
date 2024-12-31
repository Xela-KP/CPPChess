#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    U64 bitboard = 0ULL;
    mask::map_slide_attacks();
    mask::initialize_occupancies();
    bitboard::set_bit(bitboard, chess::d5);
    bitboard::set_bit(bitboard, chess::d3);
    util::print_bitboard(mask::get_queen_attack_mask(chess::d4, bitboard));
    // util::print_bitboard(mask::queen_attack_mask[]);
    // fen::parse_fen(KILLER_POSITION);
    // util::print_chessboard();
    return 0;
}