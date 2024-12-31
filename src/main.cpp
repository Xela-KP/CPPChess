#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    mask::map_slide_attacks();
    mask::map_leap_attacks();

    fen::parse_fen(TRICKY_POSITION);
    // bitboard::clear_bit(mask::piece_occupancies[chess::r], chess::h8);
    // bitboard::clear_bit(mask::piece_occupancies[chess::n], chess::f6);
    // bitboard::clear_bit(mask::piece_occupancies[chess::p], chess::g6);
    util::print_chessboard();
    std::cout << (mask::get_attackers_on(chess::BLACK, chess::d5));
    return 0;
}