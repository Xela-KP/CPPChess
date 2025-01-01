#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    mask::map_slide_attacks();
    mask::map_leap_attacks();
    fen::parse_fen(TRICKY_POSITION);
    util::print_chessboard();
    return 0;
}