#include <iostream>
#include "../include/util.hpp"
#include "../include/game.hpp"
#include "../include/encodings.hpp"
#include "../include/fen.hpp"
#include "../include/mask.hpp"

int main()
{
    MaskUtils::map_attack_masks();
    GameState gs;
    util::print_chessboard(gs);
    return 0;
}