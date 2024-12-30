#include <iostream>
#include "../include/mask.cpp"
#include "../include/util.cpp"
#include "../include/fen.cpp"
int main()
{
    fen::parse_fen(KILLER_POSITION);
    util::print_chessboard();
    return 0;
}